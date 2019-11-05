//
// Created by mikhail on 17.10.2019.
//

#include <vector>
#include <string>
#include <iostream>
#include "TFile.h"
#include "CorrelationMananger.h"
#include "Method3Se.h"
#include <fstream>

// ./Build_Flow input_file output_file config_file

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

  auto file = TFile::Open(input_file_name.data());
  CorrelationMananger mananger;
  mananger.SetFile(file);
  mananger.SetConfigFile(config_file_name);
  Method3Se method_3se;
  method_3se.SetName("3Sub");
  method_3se.Init();
  for(unsigned int i=0; i<2; i++)
  {
    method_3se.SetQnCorrelations( i, mananger.GetQnQnContainers("3Se", i) );
    method_3se.SetUnCorrelations( i, mananger.GetUnQnContainers("3Se", i) );
  }
  method_3se.Compute();
  std::vector<Qn::Axis> rebin_axis{mananger.GetRebinAxis("3Se")};
  for( auto axis : rebin_axis ){
    method_3se.Rebin(axis);
  }
  method_3se.Projection(mananger.GetProjectionAxisName("3Se"));
  auto* file_out = new TFile(output_file_name.data(), "recreate");
  method_3se.Average();
  method_3se.SaveAveragedHistoToFile(file_out);
  file_out->Close();
  std::cout << "Results saved in " << output_file_name << std::endl;
  return 0;
}
