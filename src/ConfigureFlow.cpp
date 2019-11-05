//
// Created by mikhail on 18.10.2019.
//
#include <iostream>
#include "FlowConfiguration.h"
#include <TFile.h>
int main(int argv, char** argc){
  if(argv<2){
    std::cout << "Error: Incorrect number of arguments." << std::endl;
    return 1;
  }
  std::string file_name{argc[1]};
  TFile* file = TFile::Open(file_name.data(), "recreate");
  FlowConfiguration configuration;
  configuration.SetQnQnNames({
    "Fw1Sp_Fw2Sp",
    "Fw3Sp_Fw1Sp",
    "Fw2Sp_Fw3Sp"
  });
  configuration.SetUnQnNames({
    "TracksMdcPtMr_Fw1Sp",
    "TracksMdcPtMr_Fw2Sp",
    "TracksMdcPtMr_Fw3Sp"
  });
  configuration.SetComponentsNames({
    "_XX",
    "_YY"
  });
  configuration.SetProjectionAxisName("0_Pt");
  configuration.SetRebinAxis({{"Centrality", 2, 20, 30}});
  file->cd();
  configuration.Write("3Se");
  std::cout << "Configuration written in " << file_name << std::endl;
  file->Close();
}
