//
// Created by mikhail on 17.10.2019.
//

#include <vector>
#include <chrono>
#include <string>
#include <iostream>
#include "FlowBuilder.h"

// ./Build_Flow input_file output_file config_file

int main( int argc, char** argv )
{
  auto start = std::chrono::system_clock::now();
  if( argc < 3 ){
    std::cout << "Error: Incorrecet number of arguments, " << argc-1 <<
    " given, 3 is required" << std::endl;
    std::cout << "Exit." << std::endl;
    return 1;
  }
  std::string input_file_name=argv[1];
  std::string output_file_name=argv[2];
  std::string config_file_name=argv[3];

  FlowBuilder builder;
  builder.SetName("FlowBuilder");
  builder.SetInputName(input_file_name);
  builder.SetConfigFileName(config_file_name);
  builder.AddMethod("3Se", [](std::vector<Qn::DataContainer<Qn::Stats>> corr){
    Qn::DataContainer<Qn::Stats> result;
    result = Sqrt(corr.at(0)*corr.at(1)/(corr.at(2))*0.5);
    return result;
  });
  builder.AddMethod("RndSub", [](std::vector<Qn::DataContainer<Qn::Stats>> corr){
    Qn::DataContainer<Qn::Stats> result;
    result = Sqrt(corr.front()*0.5);
    return result;
  });
  builder.AddMethod("FullEvt", [](std::vector<Qn::DataContainer<Qn::Stats>> corr){
    Qn::DataContainer<Qn::Stats> result;
    result = ResFullEvent( corr.front() );
    return result;
  });

  builder.Compute();
  builder.Rebin();
  builder.Projection();
  builder.SaveToFile(output_file_name);
  auto end = std::chrono::system_clock::now();
  std::chrono::duration<double> elapsed_seconds = end - start;
  std::cout << "elapsed time: " << elapsed_seconds.count() << " s\n";
  return 0;
}
