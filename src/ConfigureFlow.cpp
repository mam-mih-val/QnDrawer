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
  std::vector<std::vector<std::string>> resolution_components = {
      {"_XXX", "_XX", "_XX"},
      {"_XYY", "_YY", "_YY"},
      {"_YXY", "_XX", "_YY"},
      {"_YYX", "_YY", "_XX"}
  };
  std::vector<std::string> first_names{
    "FWs1(MDCf,MDCb)",
    "FWs1(MDCf,FWs2)",
    "FWs1(MDCf,FWs3)",
    "FWs1(MDCb,FWs2)",
    "FWs1(MDCb,FWs3)",
    "FWs1(FWs2,FWs3)"
  };
  std::vector<std::string> second_names{
    "FWs2(MDCf,MDCb)",
    "FWs2(MDCf,FWs1)",
    "FWs2(MDCf,FWs3)",
    "FWs2(MDCb,FWs1)",
    "FWs2(MDCb,FWs3)",
    "FWs2(FWs1,FWs3)"
  };
  std::vector<std::string> third_names{
    "FWs3(MDCf,MDCb)",
    "FWs3(MDCf,FWs1)",
    "FWs3(MDCf,FWs2)",
    "FWs3(MDCb,FWs1)",
    "FWs3(MDCb,FWs2)",
    "FWs3(FWs1,FWs2)"
  };
  std::vector<std::vector<std::string>> first_resolutions{
      {"MdcFw_Fw1", "MdcBw_Fw1", "MdcFw_MdcBw"},  // FWs1(MDCf, MDCb)
      {"MdcFw_Fw1", "Fw1_Fw2", "MdcFw_Fw2"},      // FWs1(MDCf, FWs2)
      {"MdcFw_Fw1", "Fw1_Fw3", "MdcFw_Fw3"},      // FWs1(MDCf, FWs3)
      {"MdcBw_Fw1", "Fw1_Fw2", "MdcBw_Fw2"},      // FWs1(MDCb, FWs2)
      {"MdcBw_Fw1", "Fw1_Fw3", "MdcBw_Fw3"},      // FWs1(MDCb, FWs3)
      {"Fw1_Fw2", "Fw1_Fw3", "Fw2_Fw3"}           // FWs1(FWs2, FWs3)
  };
  std::vector<std::vector<std::string>> second_resolutions{
      {"MdcFw_Fw2", "MdcBw_Fw2", "MdcFw_MdcBw"},  // FWs2(MDCf, MDCb)
      {"MdcFw_Fw2", "Fw1_Fw2", "MdcFw_Fw1"},      // FWs2(MDCf, FWs1)
      {"MdcFw_Fw2", "Fw2_Fw3", "MdcFw_Fw3"},      // FWs2(MDCf, FWs3)
      {"MdcBw_Fw2", "Fw1_Fw2", "MdcBw_Fw1"},      // FWs2(MDCb, FWs1)
      {"MdcBw_Fw2", "Fw2_Fw3", "MdcBw_Fw3"},      // FWs2(MDCb, FWs3)
      {"Fw1_Fw2", "Fw2_Fw3", "Fw1_Fw3"}           // FWs2(FWs1, FWs3)
  };
  std::vector<std::vector<std::string>> third_resolutions{
      {"MdcFw_Fw3", "MdcBw_Fw3", "MdcFw_MdcBw"},  // FWs3(MDCf, MDCb)
      {"MdcFw_Fw3", "Fw1_Fw3", "MdcFw_Fw1"},      // FWs3(MDCf, FWs1)
      {"MdcFw_Fw3", "Fw2_Fw3", "MdcFw_Fw2"},      // FWs3(MDCf, FWs2)
      {"MdcBw_Fw3", "Fw1_Fw3", "MdcBw_Fw1"},      // FWs3(MDCb, FWs1)
      {"MdcBw_Fw3", "Fw2_Fw3", "MdcBw_Fw2"},      // FWs3(MDCb, FWs2)
      {"Fw1_Fw3", "Fw2_Fw3", "Fw1_Fw2"}           // FWs3(FWs1, FWs2)
  };
  for( auto component : resolution_components ) {
    for(size_t i=0; i<first_names.size(); ++i){
      for(size_t j=0; j<second_names.size(); ++j){
        configurations.emplace_back( first_names.at(i)+"_"+second_names.at(j)+component.at(0)+"_Sp" );
        std::vector<std::string> resolution;
        std::vector<std::string> first_resolution = first_resolutions.at(i);
        std::for_each(first_resolution.begin(), first_resolution.end(), [component](std::string& str){str+=component.at(1)+"_Sp";});
        std::vector<std::string> second_resolution = second_resolutions.at(j);
        std::for_each(second_resolution.begin(), second_resolution.end(), [component](std::string& str){str+=component.at(2)+"_Sp";});
        resolution.insert(resolution.end(), first_resolution.begin(), first_resolution.end());
        resolution.insert(resolution.end(), second_resolution.begin(), second_resolution.end());
        configurations.back().SetQnQnNames( resolution );
        configurations.back().SetUnQnNames( {"TracksMdcPt_Fw1_Fw2"+component.at(0)+"_Sp"} );
        configurations.back().SetProjectionAxisName("Centrality");
      }
    }
    for(size_t i=0; i<second_names.size(); ++i){
      for(size_t j=0; j<third_names.size(); ++j){
        configurations.emplace_back( second_names.at(i)+"_"+third_names.at(j)+component.at(0)+"_Sp" );
        std::vector<std::string> resolution;
        std::vector<std::string> third_resolution = third_resolutions.at(j);
        std::for_each(third_resolution.begin(), third_resolution.end(), [component](std::string& str){str+=component.at(2)+"_Sp";});
        std::vector<std::string> second_resolution = second_resolutions.at(i);
        std::for_each(second_resolution.begin(), second_resolution.end(), [component](std::string& str){str+=component.at(1)+"_Sp";});
        resolution.insert(resolution.end(), third_resolution.begin(), third_resolution.end());
        resolution.insert(resolution.end(), second_resolution.begin(), second_resolution.end());
        configurations.back().SetQnQnNames( resolution );
        configurations.back().SetUnQnNames( {"TracksMdcPt_Fw2_Fw3"+component.at(0)+"_Sp"} );
        configurations.back().SetProjectionAxisName("Centrality");
      }
    }
    for(size_t i=0; i<first_names.size(); ++i){
      for(size_t j=0; j<third_names.size(); ++j){
        configurations.emplace_back( first_names.at(i)+"_"+third_names.at(j)+component.at(0)+"_Sp" );
        std::vector<std::string> resolution;
        std::vector<std::string> first_resolution = first_resolutions.at(i);
        std::for_each(first_resolution.begin(), first_resolution.end(), [component](std::string& str){str+=component.at(1)+"_Sp";});
        std::vector<std::string> second_resolution = second_resolutions.at(j);
        std::for_each(second_resolution.begin(), second_resolution.end(), [component](std::string& str){str+=component.at(2)+"_Sp";});
        resolution.insert(resolution.end(), first_resolution.begin(), first_resolution.end());
        resolution.insert(resolution.end(), second_resolution.begin(), second_resolution.end());
        configurations.back().SetQnQnNames( resolution );
        configurations.back().SetUnQnNames( {"TracksMdcPt_Fw1_Fw3"+component.at(0)+"_Sp"} );
        configurations.back().SetProjectionAxisName("Centrality");
      }
    }
  }
  resolution_components = {
    {"_XXXX", "_XX", "_XX", "_XX"},
    {"_XYYX", "_YY", "_YY", "_XX"},
    {"_XYXY", "_YY", "_XX", "_YY"},
    {"_XXYY", "_XX", "_YY", "_XX"},
    {"_YYXX", "_YY", "_XX", "_XX"},
    {"_YXYX", "_XX", "_YY", "_XX"},
    {"_YXXY", "_XX", "_XX", "_YY"},
    {"_YYYY", "_YY", "_YY", "_YY"}
  };
  for( auto component : resolution_components ) {
    for (size_t i = 0; i < first_resolutions.size(); ++i) {
      for (size_t j = 0; j < second_resolutions.size(); ++j) {
        for( size_t k = 0; k < third_resolutions.size(); ++k ){
        configurations.emplace_back(first_names.at(i) + "_" +
                                    second_names.at(j) + "_" + third_names.at(k) + component.at(0) +
                                    "_Sp");
        std::vector<std::string> resolution;
        std::vector<std::string> first_resolution = first_resolutions.at(i);
        std::for_each(
            first_resolution.begin(), first_resolution.end(),
            [component](std::string &str) { str += component.at(1) + "_Sp"; });
        std::vector<std::string> second_resolution = second_resolutions.at(j);
        std::for_each(
            second_resolution.begin(), second_resolution.end(),
            [component](std::string &str) { str += component.at(2) + "_Sp"; });
        std::vector<std::string> third_resolution = third_resolutions.at(k);
        std::for_each(
            third_resolution.begin(), third_resolution.end(),
            [component](std::string &str) { str += component.at(3) + "_Sp"; });
        resolution.insert(resolution.end(), first_resolution.begin(),
                          first_resolution.end());
        resolution.insert(resolution.end(), second_resolution.begin(),
                          second_resolution.end());
        resolution.insert(resolution.end(), third_resolution.begin(),
                          third_resolution.end());
        configurations.back().SetQnQnNames(resolution);
        configurations.back().SetUnQnNames(
            {"TracksMdcPt_Fw1_Fw2_Fw3" + component.at(0) + "_Sp"});
        configurations.back().SetProjectionAxisName("Centrality");
        }
      }
    }
  }
  file->cd();
  for( auto &configuration : configurations )
    configuration.SaveToFile(file);
  std::cout << "Configurations written in " << file_name << std::endl;
  file->Close();
}
