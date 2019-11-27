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
  std::vector<std::string> u_vector{"TracksMdcPt", "TracksMdcYcm"};
  std::vector<std::string> axis_names{"Pt", "Ycm"};
  std::vector<std::string> sub_events{"Fw1", "Fw2", "Fw3"};
  std::vector<std::string> qn_qn_correlations{ "Fw1_Fw2", "Fw3_Fw1", "Fw2_Fw3" };
  std::vector<std::string> components{"_XX", "_YY"};
  std::vector<std::string> methods{"_Sp", "_Ep"};

  // ******************************** Method of 3 Sub-Events ******************************** //

  for( auto se : sub_events ){
    for(auto method : methods){
      for( auto axis : axis_names ){
        for( auto component : components ){
          auto correlations = qn_qn_correlations;
          configurations.emplace_back( "TracksMdc"+axis+"_"+se+component+method );
          std::for_each( correlations.begin(), correlations.end(), [component, method]( std::string& str ){ str+=component+method; } );
          configurations.back().SetQnQnNames( correlations );
          configurations.back().SetUnQnNames( {"TracksMdc"+axis+"_"+se+component+method} );
          configurations.back().SetProjectionAxisName("0_"+axis);
          configurations.back().SetRebinAxis({{"Centrality", 2, 20, 30}});
        }
      }
    }
    qn_qn_correlations = { qn_qn_correlations.at(2), qn_qn_correlations.at(0), qn_qn_correlations.at(1) };
  }

  // ******************************** Method of 3 Sub-Events, Second Harmonic ******************************** //

  sub_events = { "Fw1_Fw2", "Fw3_Fw1", "Fw2_Fw3" };
  std::vector<std::string> first_resolution{ "Fw3_Fw1", "Fw1_Fw2", "Fw2_Fw3" };
  std::vector<std::string> second_resolution{ "Fw1_Fw2", "Fw2_Fw3", "Fw3_Fw1" };
  std::vector<std::string> un_qn_components = {"_XXX", "_XYY", "_YXY", "_YYX"};
  std::vector<std::string> first_components = {"_XX", "_YY", "_XX", "_YY"};
  std::vector<std::string> second_components = {"_XX", "_YY", "_YY", "_XX"};
  for( auto se : sub_events ){
    for(auto method : methods){
      for( auto axis : axis_names ){
        for( int i=0; i<un_qn_components.size(); i++ ){
          auto correlations_1 = first_resolution;
          auto correlations_2 = second_resolution;
          configurations.emplace_back( "TracksMdc"+axis+"_"+se+un_qn_components.at(i)+method );
          std::for_each( correlations_1.begin(), correlations_1.end(), [first_components, i, method]( std::string& str ){ str+=first_components.at(i)+method; } );
          std::for_each( correlations_2.begin(), correlations_2.end(), [second_components, i, method]( std::string& str ){ str+=second_components.at(i)+method; } );
          correlations_1.insert(correlations_1.end(), correlations_2.begin(), correlations_2.end());
          configurations.back().SetQnQnNames( correlations_1 );
          configurations.back().SetUnQnNames( {"TracksMdc"+axis+"_"+se+un_qn_components.at(i)+method} );
          configurations.back().SetProjectionAxisName("0_"+axis);
          configurations.back().SetRebinAxis({{"Centrality", 2, 20, 30}});
        }
      }
    }
    first_resolution = { first_resolution.at(2), first_resolution.at(0), first_resolution.at(1) };
    second_resolution = { second_resolution.at(2), second_resolution.at(0), second_resolution.at(1) };
  }

  // ******************************** Method of 3 Sub-Events, Third Harmonic ******************************** //
  sub_events = { "Fw1_Fw2_Fw3" };
  std::vector<std::string> resolution_first { "Fw3_Fw1", "Fw1_Fw2", "Fw2_Fw3" };
  std::vector<std::string> resolution_second{ "Fw1_Fw2", "Fw2_Fw3", "Fw3_Fw1" };
  std::vector<std::string> resolution_third { "Fw2_Fw3", "Fw3_Fw1", "Fw1_Fw2" };
  un_qn_components = {"_XXXX", "_XYYX", "_XYXY", "_XXYY", "_YYXX", "_YXYX", "_YXXY", "_YYYY"};
  std::vector<std::string> components_first = {"_XX", "_YY", "_YY", "_XX", "_YY", "_XX", "_XX", "_YY"};
  std::vector<std::string> components_second= {"_XX", "_YY", "_XX", "_YY", "_XX", "_YY", "_XX", "_YY"};
  std::vector<std::string> components_third = {"_XX", "_XX", "_YY", "_YY", "_XX", "_XX", "_YY", "_YY"};
  for( auto se : sub_events ){
    for( auto method : methods ){
      for( auto axis : axis_names ){
        for( int i=0; i<un_qn_components.size(); i++ ){
          auto correlations_1 = resolution_first;
          auto correlations_2 = resolution_second;
          auto correlations_3 = resolution_third;
          configurations.emplace_back( "TracksMdc"+axis+"_"+se+un_qn_components.at(i)+method );
          std::for_each( correlations_1.begin(), correlations_1.end(), [components_first, i, method]( std::string& str ){ str+=components_first.at(i)+method; } );
          std::for_each( correlations_2.begin(), correlations_2.end(), [components_second, i, method](std::string& str ){ str+=components_second.at(i)+method; } );
          std::for_each( correlations_3.begin(), correlations_3.end(), [components_third, i, method]( std::string& str ){ str+=components_third.at(i)+method; } );
          correlations_1.insert(correlations_1.end(), correlations_2.begin(), correlations_2.end());
          correlations_1.insert(correlations_1.end(), correlations_3.begin(), correlations_3.end());
          configurations.back().SetQnQnNames( correlations_1 );
          configurations.back().SetUnQnNames( {"TracksMdc"+axis+"_"+se+un_qn_components.at(i)+method} );
          configurations.back().SetProjectionAxisName("0_"+axis);
          configurations.back().SetRebinAxis({{"Centrality", 2, 20, 30}});
        }
      }
    }
    resolution_first = { first_resolution.at(2), first_resolution.at(0), first_resolution.at(1) };
    resolution_second = { second_resolution.at(2), second_resolution.at(0), second_resolution.at(1) };
    resolution_third = { second_resolution.at(2), second_resolution.at(0), second_resolution.at(1) };
  }

  // ******************************** Random Sub-Event method ******************************** //
  sub_events = { "Rs1", "Rs2" };
  qn_qn_correlations = { "Rs1_Rs2"};
  components = {"_XX", "_YY"};
  for( auto se : sub_events ){
    for(auto method : methods){
      for( auto axis : axis_names ){
        for( auto comp : components ){
          configurations.emplace_back( "TracksMdc"+axis+"_"+se+comp+method );
          auto correlations = qn_qn_correlations;
          std::for_each( correlations.begin(), correlations.end(), [comp, method]( std::string& str ){ str+=comp+method; } );
          configurations.back().SetQnQnNames( correlations );
          configurations.back().SetUnQnNames( {"TracksMdc"+axis+"_"+se+comp+method} );
          configurations.back().SetProjectionAxisName("0_"+axis);
          configurations.back().SetRebinAxis({{"Centrality", 2, 20, 30}});
        }
      }
    }
  }
  for( auto axis : axis_names ) {
    for (auto comp : components) {
      configurations.emplace_back("TracksMdc" + axis + "_Full" + comp + "_Ep");
      auto correlations = qn_qn_correlations;
      std::for_each(correlations.begin(), correlations.end(),
                    [comp](std::string &str) { str += comp + "_Ep"; });
      configurations.back().SetQnQnNames(correlations);
      configurations.back().SetUnQnNames(
          {"TracksMdc" + axis + "_Full" + comp + "_Ep"});
      configurations.back().SetProjectionAxisName("0_" + axis);
      configurations.back().SetRebinAxis({{"Centrality", 2, 20, 30}});
    }
  }
  file->cd();
  for( auto &configuration : configurations )
    configuration.SaveToFile(file);
  std::cout << "Configurations written in " << file_name << std::endl;
  file->Close();
}
