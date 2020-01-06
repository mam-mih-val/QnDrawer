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
  std::vector<std::string> components{"_XX", "_YY"};
  // ******************************** Method of 3 Sub-Events in MDC+FW ******************************** //
  for( auto component : components ){
    configurations.emplace_back( "TracksMdcPt_Fw1_MdcFw_MdcBw_"+component+"_Sp" );
    configurations.back().SetQnQnNames( {"MdcFw_Fw1"+component+"_Sp", "MdcBw_Fw1"+component+"_Sp", "MdcFw_MdcBw"+component+"_Sp" } );
    configurations.back().SetUnQnNames( {"TracksMdcPt_Fw1"+component+"_Sp"} );
    configurations.back().SetProjectionAxisName("Centrality");

    configurations.emplace_back( "TracksMdcPt_Fw1_MdcFw_Fw2_"+component+"_Sp" );
    configurations.back().SetQnQnNames( {"MdcFw_Fw1"+component+"_Sp", "Fw1_Fw2"+component+"_Sp", "MdcFw_Fw2"+component+"_Sp" } );
    configurations.back().SetUnQnNames( {"TracksMdcPt_Fw1"+component+"_Sp"} );
    configurations.back().SetProjectionAxisName("Centrality");

    configurations.emplace_back( "TracksMdcPt_Fw1_MdcFw_Fw3_"+component+"_Sp" );
    configurations.back().SetQnQnNames( {"MdcFw_Fw1"+component+"_Sp", "Fw1_Fw3"+component+"_Sp", "MdcFw_Fw3"+component+"_Sp" } );
    configurations.back().SetUnQnNames( {"TracksMdcPt_Fw1"+component+"_Sp"} );
    configurations.back().SetProjectionAxisName("Centrality");

    configurations.emplace_back( "TracksMdcPt_Fw1_MdcBw_Fw2_"+component+"_Sp" );
    configurations.back().SetQnQnNames( {"MdcBw_Fw1"+component+"_Sp", "Fw1_Fw2"+component+"_Sp", "MdcBw_Fw2"+component+"_Sp" } );
    configurations.back().SetUnQnNames( {"TracksMdcPt_Fw1"+component+"_Sp"} );
    configurations.back().SetProjectionAxisName("Centrality");

    configurations.emplace_back( "TracksMdcPt_Fw1_MdcBw_Fw3_"+component+"_Sp" );
    configurations.back().SetQnQnNames( {"MdcBw_Fw1"+component+"_Sp", "Fw1_Fw3"+component+"_Sp", "MdcBw_Fw3"+component+"_Sp" } );
    configurations.back().SetUnQnNames( {"TracksMdcPt_Fw1"+component+"_Sp"} );
    configurations.back().SetProjectionAxisName("Centrality");

    configurations.emplace_back( "TracksMdcPt_Fw1_Fw2_Fw3_"+component+"_Sp" );
    configurations.back().SetQnQnNames( {"Fw1_Fw2"+component+"_Sp", "Fw1_Fw3"+component+"_Sp", "Fw2_Fw3"+component+"_Sp" } );
    configurations.back().SetUnQnNames( {"TracksMdcPt_Fw1"+component+"_Sp"} );
    configurations.back().SetProjectionAxisName("Centrality");
  }

  for( auto component : components ){
    configurations.emplace_back( "TracksMdcPt_Fw2_MdcFw_MdcBw_"+component+"_Sp" );
    configurations.back().SetQnQnNames( {"MdcFw_Fw2"+component+"_Sp", "MdcBw_Fw2"+component+"_Sp", "MdcFw_MdcBw"+component+"_Sp" } );
    configurations.back().SetUnQnNames( {"TracksMdcPt_Fw2"+component+"_Sp"} );
    configurations.back().SetProjectionAxisName("Centrality");

    configurations.emplace_back( "TracksMdcPt_Fw2_MdcFw_Fw1_"+component+"_Sp" );
    configurations.back().SetQnQnNames( {"MdcFw_Fw2"+component+"_Sp", "Fw1_Fw2"+component+"_Sp", "MdcFw_Fw1"+component+"_Sp" } );
    configurations.back().SetUnQnNames( {"TracksMdcPt_Fw2"+component+"_Sp"} );
    configurations.back().SetProjectionAxisName("Centrality");

    configurations.emplace_back( "TracksMdcPt_Fw2_MdcFw_Fw3_"+component+"_Sp" );
    configurations.back().SetQnQnNames( {"MdcFw_Fw2"+component+"_Sp", "Fw2_Fw3"+component+"_Sp", "MdcFw_Fw3"+component+"_Sp" } );
    configurations.back().SetUnQnNames( {"TracksMdcPt_Fw2"+component+"_Sp"} );
    configurations.back().SetProjectionAxisName("Centrality");

    configurations.emplace_back( "TracksMdcPt_Fw2_MdcBw_Fw1_"+component+"_Sp" );
    configurations.back().SetQnQnNames( {"MdcBw_Fw2"+component+"_Sp", "Fw1_Fw2"+component+"_Sp", "MdcBw_Fw1"+component+"_Sp" } );
    configurations.back().SetUnQnNames( {"TracksMdcPt_Fw2"+component+"_Sp"} );
    configurations.back().SetProjectionAxisName("Centrality");

    configurations.emplace_back( "TracksMdcPt_Fw2_MdcBw_Fw3_"+component+"_Sp" );
    configurations.back().SetQnQnNames( {"MdcBw_Fw2"+component+"_Sp", "Fw2_Fw3"+component+"_Sp", "MdcBw_Fw3"+component+"_Sp" } );
    configurations.back().SetUnQnNames( {"TracksMdcPt_Fw2"+component+"_Sp"} );
    configurations.back().SetProjectionAxisName("Centrality");

    configurations.emplace_back( "TracksMdcPt_Fw2_Fw1_Fw3_"+component+"_Sp" );
    configurations.back().SetQnQnNames( {"Fw1_Fw2"+component+"_Sp", "Fw2_Fw3"+component+"_Sp", "Fw1_Fw3"+component+"_Sp" } );
    configurations.back().SetUnQnNames( {"TracksMdcPt_Fw2"+component+"_Sp"} );
    configurations.back().SetProjectionAxisName("Centrality");
  }

  for( auto component : components ){
    configurations.emplace_back( "TracksMdcPt_Fw3_MdcFw_MdcBw_"+component+"_Sp" );
    configurations.back().SetQnQnNames( {"MdcFw_Fw3"+component+"_Sp", "MdcBw_Fw3"+component+"_Sp", "MdcFw_MdcBw"+component+"_Sp" } );
    configurations.back().SetUnQnNames( {"TracksMdcPt_Fw3"+component+"_Sp"} );
    configurations.back().SetProjectionAxisName("Centrality");

    configurations.emplace_back( "TracksMdcPt_Fw3_MdcFw_Fw1_"+component+"_Sp" );
    configurations.back().SetQnQnNames( {"MdcFw_Fw3"+component+"_Sp", "Fw1_Fw3"+component+"_Sp", "MdcFw_Fw1"+component+"_Sp" } );
    configurations.back().SetUnQnNames( {"TracksMdcPt_Fw3"+component+"_Sp"} );
    configurations.back().SetProjectionAxisName("Centrality");

    configurations.emplace_back( "TracksMdcPt_Fw3_MdcFw_Fw2_"+component+"_Sp" );
    configurations.back().SetQnQnNames( {"MdcFw_Fw3"+component+"_Sp", "Fw2_Fw3"+component+"_Sp", "MdcFw_Fw2"+component+"_Sp" } );
    configurations.back().SetUnQnNames( {"TracksMdcPt_Fw3"+component+"_Sp"} );
    configurations.back().SetProjectionAxisName("Centrality");

    configurations.emplace_back( "TracksMdcPt_Fw3_MdcBw_Fw1_"+component+"_Sp" );
    configurations.back().SetQnQnNames( {"MdcBw_Fw3"+component+"_Sp", "Fw1_Fw3"+component+"_Sp", "MdcBw_Fw1"+component+"_Sp" } );
    configurations.back().SetUnQnNames( {"TracksMdcPt_Fw3"+component+"_Sp"} );
    configurations.back().SetProjectionAxisName("Centrality");

    configurations.emplace_back( "TracksMdcPt_Fw3_MdcBw_Fw2_"+component+"_Sp" );
    configurations.back().SetQnQnNames( {"MdcBw_Fw3"+component+"_Sp", "Fw2_Fw3"+component+"_Sp", "MdcBw_Fw2"+component+"_Sp" } );
    configurations.back().SetUnQnNames( {"TracksMdcPt_Fw3"+component+"_Sp"} );
    configurations.back().SetProjectionAxisName("Centrality");

    configurations.emplace_back( "TracksMdcPt_Fw3_Fw1_Fw2_"+component+"_Sp" );
    configurations.back().SetQnQnNames( {"Fw1_Fw3"+component+"_Sp", "Fw2_Fw3"+component+"_Sp", "Fw1_Fw2"+component+"_Sp" } );
    configurations.back().SetUnQnNames( {"TracksMdcPt_Fw3"+component+"_Sp"} );
    configurations.back().SetProjectionAxisName("Centrality");
  }
  for( auto component : components ){
    configurations.emplace_back( "TracksMdcPt_MdcFw_MdcBw_Fw1_"+component+"_Sp" );
    configurations.back().SetQnQnNames( {"MdcFw_MdcBw"+component+"_Sp", "MdcFw_Fw1"+component+"_Sp", "MdcBw_Fw1"+component+"_Sp" } );
    configurations.back().SetUnQnNames( {"TracksMdcPt_MdcFw"+component+"_Sp"} );
    configurations.back().SetProjectionAxisName("Centrality");

    configurations.emplace_back( "TracksMdcPt_MdcFw_MdcBw_Fw2_"+component+"_Sp" );
    configurations.back().SetQnQnNames( {"MdcFw_MdcBw"+component+"_Sp", "MdcFw_Fw2"+component+"_Sp", "MdcBw_Fw2"+component+"_Sp" } );
    configurations.back().SetUnQnNames( {"TracksMdcPt_MdcFw"+component+"_Sp"} );
    configurations.back().SetProjectionAxisName("Centrality");

    configurations.emplace_back( "TracksMdcPt_MdcFw_MdcBw_Fw3_"+component+"_Sp" );
    configurations.back().SetQnQnNames( {"MdcFw_MdcBw"+component+"_Sp", "MdcFw_Fw3"+component+"_Sp", "MdcBw_Fw3"+component+"_Sp" } );
    configurations.back().SetUnQnNames( {"TracksMdcPt_MdcFw"+component+"_Sp"} );
    configurations.back().SetProjectionAxisName("Centrality");

    configurations.emplace_back( "TracksMdcPt_MdcFw_Fw1_Fw2_"+component+"_Sp" );
    configurations.back().SetQnQnNames( {"MdcFw_Fw1"+component+"_Sp", "MdcFw_Fw2"+component+"_Sp", "Fw1_Fw2"+component+"_Sp" } );
    configurations.back().SetUnQnNames( {"TracksMdcPt_MdcFw"+component+"_Sp"} );
    configurations.back().SetProjectionAxisName("Centrality");

    configurations.emplace_back( "TracksMdcPt_MdcFw_Fw2_Fw3_"+component+"_Sp" );
    configurations.back().SetQnQnNames( {"MdcFw_Fw2"+component+"_Sp", "MdcFw_Fw3"+component+"_Sp", "Fw2_Fw3"+component+"_Sp" } );
    configurations.back().SetUnQnNames( {"TracksMdcPt_MdcFw"+component+"_Sp"} );
    configurations.back().SetProjectionAxisName("Centrality");

    configurations.emplace_back( "TracksMdcPt_MdcFw_Fw1_Fw3_"+component+"_Sp" );
    configurations.back().SetQnQnNames( {"MdcFw_Fw1"+component+"_Sp", "MdcFw_Fw3"+component+"_Sp", "Fw1_Fw3"+component+"_Sp" } );
    configurations.back().SetUnQnNames( {"TracksMdcPt_MdcFw"+component+"_Sp"} );
    configurations.back().SetProjectionAxisName("Centrality");
  }

  for( auto component : components ){
    configurations.emplace_back( "TracksMdcPt_MdcBw_MdcFw_Fw1_"+component+"_Sp" );
    configurations.back().SetQnQnNames( {"MdcFw_MdcBw"+component+"_Sp", "MdcBw_Fw1"+component+"_Sp", "MdcFw_Fw1"+component+"_Sp" } );
    configurations.back().SetUnQnNames( {"TracksMdcPt_MdcBw"+component+"_Sp"} );
    configurations.back().SetProjectionAxisName("Centrality");

    configurations.emplace_back( "TracksMdcPt_MdcBw_MdcFw_Fw2_"+component+"_Sp" );
    configurations.back().SetQnQnNames( {"MdcFw_MdcBw"+component+"_Sp", "MdcBw_Fw2"+component+"_Sp", "MdcFw_Fw2"+component+"_Sp" } );
    configurations.back().SetUnQnNames( {"TracksMdcPt_MdcBw"+component+"_Sp"} );
    configurations.back().SetProjectionAxisName("Centrality");

    configurations.emplace_back( "TracksMdcPt_MdcBw_MdcFw_Fw3_"+component+"_Sp" );
    configurations.back().SetQnQnNames( {"MdcFw_MdcBw"+component+"_Sp", "MdcBw_Fw3"+component+"_Sp", "MdcFw_Fw3"+component+"_Sp" } );
    configurations.back().SetUnQnNames( {"TracksMdcPt_MdcBw"+component+"_Sp"} );
    configurations.back().SetProjectionAxisName("Centrality");

    configurations.emplace_back( "TracksMdcPt_MdcBw_Fw1_Fw2_"+component+"_Sp" );
    configurations.back().SetQnQnNames( {"MdcBw_Fw1"+component+"_Sp", "MdcBw_Fw2"+component+"_Sp", "Fw1_Fw2"+component+"_Sp" } );
    configurations.back().SetUnQnNames( {"TracksMdcPt_MdcBw"+component+"_Sp"} );
    configurations.back().SetProjectionAxisName("Centrality");

    configurations.emplace_back( "TracksMdcPt_MdcBw_Fw1_Fw3_"+component+"_Sp" );
    configurations.back().SetQnQnNames( {"MdcBw_Fw1"+component+"_Sp", "MdcBw_Fw3"+component+"_Sp", "Fw1_Fw3"+component+"_Sp" } );
    configurations.back().SetUnQnNames( {"TracksMdcPt_MdcBw"+component+"_Sp"} );
    configurations.back().SetProjectionAxisName("Centrality");

    configurations.emplace_back( "TracksMdcPt_MdcBw_Fw2_Fw3_"+component+"_Sp" );
    configurations.back().SetQnQnNames( {"MdcBw_Fw2"+component+"_Sp", "MdcBw_Fw3"+component+"_Sp", "Fw2_Fw3"+component+"_Sp" } );
    configurations.back().SetUnQnNames( {"TracksMdcPt_MdcBw"+component+"_Sp"} );
    configurations.back().SetProjectionAxisName("Centrality");
  }
  file->cd();
  for( auto &configuration : configurations )
    configuration.SaveToFile(file);
  std::cout << "Configurations written in " << file_name << std::endl;
  file->Close();
}
