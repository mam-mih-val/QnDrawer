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
  std::vector<FlowConfiguration> configurations;
  // ******************************** Method of 3 Sub-Events ******************************** //
  configurations.emplace_back("3Se", 3);
  configurations.back().SetQnQnNames({
    "Fw1Sp_Fw2Sp", // 0
    "Fw3Sp_Fw1Sp", // 1
    "Fw2Sp_Fw3Sp"  // 2
  });
  configurations.back().SetUnQnNames({
    "TracksMdcPtMr_Fw1Sp",
    "TracksMdcPtMr_Fw2Sp",
    "TracksMdcPtMr_Fw3Sp"
  });
  configurations.back().SetComponentsNames({
    "_XX",
    "_YY"
  });
  configurations.back().SetProjectionAxisName("0_Pt");
  configurations.back().SetRebinAxis({{"Centrality", 2, 20, 30}});
  configurations.back().SetResolutionIndicesMatrix({
    {0, 1, 2},
    {0, 2, 1},
    {1, 2, 0}
  });
  // ******************************** Method of Random Sub-Events ******************************** //
  configurations.emplace_back("RndSub", 2);
  configurations.back().SetQnQnNames({
    "Rs1Sp_Rs2Sp" // 0
  });
  configurations.back().SetUnQnNames({
    "TracksMdcPtMr_Rs1Sp",
    "TracksMdcPtMr_Rs2Sp",
  });
  configurations.back().SetComponentsNames({
     "_XX",
     "_YY"
  });
  configurations.back().SetProjectionAxisName("0_Pt");
  configurations.back().SetRebinAxis({{"Centrality", 2, 20, 30}});
  configurations.back().SetResolutionIndicesMatrix({
    {0},
    {0}
  });
  // ******************************** Full event resolution ******************************** //
  configurations.emplace_back("FullEvt", 1);
  configurations.back().SetQnQnNames({
    "Rs1Ep_Rs2Ep" // 0
  });
  configurations.back().SetUnQnNames({
    "TracksMdcPtMr_Full"
  });
  configurations.back().SetComponentsNames({
     "_XX",
     "_YY"
  });
  configurations.back().SetProjectionAxisName("0_Pt");
  configurations.back().SetRebinAxis({{"Centrality", 2, 20, 30}});
  configurations.back().SetResolutionIndicesMatrix({
    {0}
  });

  // ******************************** Saving to File ******************************** //
  file->cd();
  for( auto &configuration : configurations )
    configuration.SaveToFile(file);
  std::cout << "Configurations written in " << file_name << std::endl;
  file->Close();
}
