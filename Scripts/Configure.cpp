//
// Created by mikhail on 27.10.2019.
//

#include "../src/FlowConfiguration.h"

void Configure(std::string out_file){
  TFile* file = TFile::Open(out_file.data(), "recreate");
  FlowConfiguration configuration;
  configuration.SetQnQnNames({
                                 "Fw1Sp_Fw2Sp",
                                 "Fw3Sp_Fw1Sp",
                                 "Fw2Sp_Fw3Sp"
                             });
  configuration.SetUnQnNames({
                                 "TracksMdcPtFw_Fw1Sp",
                                 "TracksMdcPtFw_Fw2Sp",
                                 "TracksMdcPtFw_Fw3Sp"
                             });
  configuration.SetComponentsNames({
                                       "_XX",
                                       "_YY"
                                   });
  configuration.SetProjectionAxisName("0_Pt");
  configuration.SetRebinAxis({{"Centrality", 2, 20, 30}});
  file->cd();
  configuration.Write("config");
}
