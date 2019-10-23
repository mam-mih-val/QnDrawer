//
// Created by mikhail on 17.10.2019.
//

//
// Created by mikhail on 13.10.2019.
//

#include <vector>
#include <string>
#include <iostream>
#include "TFile.h"
#include "CorrelationMananger.h"
#include "Method3Se.h"
#include <fstream>

// ./Build_Flow input_file output_file config_file

std::vector<std::string> ReadConfig(const std::string& config_file_name);

int main( int argc, char** argv )
{
  if( argc < 3 ){
    std::cout << "Error: Incorrecet number of arguments, " << argc-1 <<
    " given, 3 is required" << std::endl;
    std::cout << "Exit." << std::endl;
    return 1;
  }
  std::string input_file_name=argv[1];
  std::string output_file_name=argv[2];
  std::string config_file_name=argv[3];

  std::vector<std::string> temp_vectors{ReadConfig(config_file_name)};
  std::string u_vector=temp_vectors.back();
  std::vector<std::string> q_vector;
  for(unsigned int i=0; i<temp_vectors.size()-1; i++){
    q_vector.push_back(temp_vectors.at(i));
  }
  auto file = TFile::Open(input_file_name.data());
  CorrelationMananger mananger;
  mananger.SetFile(file);
  Method3Se method_3se;
  method_3se.SetName("3Sub");
  method_3se.Init();
  std::vector<std::string> q_correlations{
    q_vector.at(0)+"_"+q_vector.at(1),
    q_vector.at(2)+"_"+q_vector.at(0),
    q_vector.at(1)+"_"+q_vector.at(2)
  };
  std::vector<std::string> u_correlations{
    u_vector+"_"+q_vector.at(0),
    u_vector+"_"+q_vector.at(1),
    u_vector+"_"+q_vector.at(2),
  };
  std::vector<std::string> components{
    "_XX",
    "_YY"
  };
  for(unsigned int i=0; i<components.size(); i++)
  {
    std::vector<std::string> corr_names=q_correlations;
    for(auto &corr: corr_names)
      corr+=components.at(i);
    method_3se.SetQnCorrelations( i, mananger.GetDataContainerVector(corr_names) );
    corr_names=u_correlations;
    for(auto &corr: corr_names)
      corr+=components.at(i);
    method_3se.SetUnCorrelations( i, mananger.GetDataContainerVector(corr_names) );
  }
  method_3se.Compute();
  method_3se.Rebin({"Centrality", 2, 20, 30});
  method_3se.Projection("0_Pt");
  auto* file_out = new TFile(output_file_name.data(), "recreate");
  //method_3se.SaveHistoToFile(file_out);
  //method_3se.SaveToFile(file_out);
  method_3se.Average();
  method_3se.SaveAveragedHistoToFile(file_out);
  file_out->Close();
  std::cout << "Results saved in " << output_file_name << std::endl;
  return 0;
}

std::vector<std::string> ReadConfig(const std::string& config_file_name){
  std::vector<std::string> temp_vectors;
  std::ifstream config_file(config_file_name);
  if(config_file.is_open()){
    std::string buff_line;
    while (getline(config_file, buff_line)) {
      temp_vectors.push_back(buff_line);
      std::cout << buff_line << std::endl;
    }
  }
  config_file.close();
  return temp_vectors;
}
