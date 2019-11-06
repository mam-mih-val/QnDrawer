//
// Created by mikhail on 17.10.2019.
//

#include <vector>
#include <string>
#include <iostream>
#include "FlowBuilder.h"

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

  FlowBuilder builder;
  builder.SetName("FlowBuilder");
  builder.SetInputName(input_file_name);
  builder.SetConfigFileName(config_file_name);
  builder.AddMethod("3Se");
  builder.Compute();
  builder.SaveToFile(output_file_name);
  return 0;
}
