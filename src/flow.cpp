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
  std::vector<std::string> axis_names{"Pt", "Ycm"};
  std::vector<std::string> sub_events{"Fw1", "Fw2", "Fw3"};
  std::vector<std::string> components{"_XX", "_YY"};
  std::vector<std::string> methods{"_Sp", "_Ep"};

  // ******************************** Method of 3 Sub-Events in MDC ******************************** //

    for(auto method : methods){
      for( auto axis : axis_names ){
        for( auto component : components ){
          builder.AddMethod("TracksMdc"+axis+"_Full_3mdc"+component+method, [](std::vector<Qn::DataContainer<Qn::Stats>> corr){
            Qn::DataContainer<Qn::Stats> result;
            result = Sqrt(corr.at(0)*corr.at(1)/(corr.at(2))*2);
            return result;
          },[](std::vector<Qn::DataContainer<Qn::Stats>> corr){
            Qn::DataContainer<Qn::Stats> result;
            result = corr.at(0)*2/corr.at(1);
            return result;
          });
        }
      }
    }
  // ******************************** Method of 3 Sub-Events ******************************** //
  for( auto se : sub_events ){
    for(auto method : methods){
      for( auto axis : axis_names ){
        for( auto component : components ){
          builder.AddMethod("TracksMdc"+axis+"_"+se+component+method, [](std::vector<Qn::DataContainer<Qn::Stats>> corr){
            Qn::DataContainer<Qn::Stats> result;
            result = Sqrt(corr.at(0)*corr.at(1)/(corr.at(2))*2);
            return result;
          },[](std::vector<Qn::DataContainer<Qn::Stats>> corr){
            Qn::DataContainer<Qn::Stats> result;
            result = corr.at(0)*2/corr.at(1);
            return result;
          });
        }
      }
    }
  }
// ******************************** Method of 3 Sub-Events, Second Harmonic ******************************** //
  sub_events = { "Fw1_Fw2", "Fw3_Fw1", "Fw2_Fw3" };
  std::vector<std::string> un_qn_components = {"_XXX", "_XYY", "_YXY", "_YYX"};
  for( auto se : sub_events ){
    for(auto method : methods){
      for( auto axis : axis_names ){
        for( int i=0; i<un_qn_components.size(); i++ ){
          builder.AddMethod( "TracksMdc"+axis+"_"+se+un_qn_components.at(i)+method,
          [](std::vector<Qn::DataContainer<Qn::Stats>> corr){
            Qn::DataContainer<Qn::Stats> result;
            Qn::DataContainer<Qn::Stats> R1 = Sqrt(corr.at(0)*corr.at(1)/corr.at(2) * 2);
            Qn::DataContainer<Qn::Stats> R2 = Sqrt(corr.at(3)*corr.at(4)/corr.at(5) * 2);
            result = R1*R2;
            return result;
          },[]( std::vector<Qn::DataContainer<Qn::Stats>> corr ){
            Qn::DataContainer<Qn::Stats> result;
            result = corr.at(0) * 4 / corr.at(1);
            return result;
          });
        }
      }
    }
  }
  // ******************************** Method of 3 Sub-Events, Third Harmonic ******************************** //
  sub_events = { "Fw1_Fw2_Fw3" };
  un_qn_components = {"_XXXX", "_XYYX", "_XYXY", "_XXYY", "_YYXX", "_YXYX", "_YXXY", "_YYYY"};
  for( auto se : sub_events ){
    for( auto method : methods ){
      for( auto axis : axis_names ){
        for( int i=0; i<un_qn_components.size(); i++ ){
          builder.AddMethod( "TracksMdc"+axis+"_"+se+un_qn_components.at(i)+method,
            []( std::vector<Qn::DataContainer<Qn::Stats>> corr ){
              Qn::DataContainer<Qn::Stats> result;
              Qn::DataContainer<Qn::Stats> R1 = Sqrt(corr.at(0)*corr.at(1)/corr.at(2) * 2);
              Qn::DataContainer<Qn::Stats> R2 = Sqrt(corr.at(3)*corr.at(4)/corr.at(5) * 2);
              Qn::DataContainer<Qn::Stats> R3 = Sqrt(corr.at(6)*corr.at(7)/corr.at(8) * 2);
              result = R1*R2*R3;
              return result;
          },
           []( std::vector<Qn::DataContainer<Qn::Stats>> corr ){
             Qn::DataContainer<Qn::Stats> result;
             result = corr.at(0) * 8 / corr.at(1);
             return result;
          });
        }
      }
    }
  }

// ******************************** Random Sub-Event method ******************************** //
  sub_events = { "Rs1", "Rs2" };
  components = {"_XX", "_YY"};
  for( auto se : sub_events ){
    for(auto method : methods){
      for( auto axis : axis_names ){
        for( auto comp : components ){
          builder.AddMethod( "TracksMdc"+axis+"_"+se+comp+method, [](std::vector<Qn::DataContainer<Qn::Stats>> corr){
            Qn::DataContainer<Qn::Stats> result;
            result = Sqrt(corr.at(0)*0.5);
            return result;
          });
        }
      }
    }
  }
  for( auto axis : axis_names ) {
    for (auto comp : components) {
      builder.AddMethod("TracksMdc" + axis + "_Full" + comp + "_Ep",[](std::vector<Qn::DataContainer<Qn::Stats>> corr){
        Qn::DataContainer<Qn::Stats> result;
        result = ResFullEvent(corr.at(0));
        return result;
      },[](std::vector<Qn::DataContainer<Qn::Stats>> corr) {
        auto result = corr.at(0) * 2 / corr.at(1) ;
        return result;
      });
    }
  }
  builder.Compute();
  builder.Rebin();
  builder.Projection();
  builder.SaveToFile(output_file_name);
//  builder.SaveGraphsToFile(output_file_name);
  auto end = std::chrono::system_clock::now();
  std::chrono::duration<double> elapsed_seconds = end - start;
  std::cout << "elapsed time: " << elapsed_seconds.count() << " s\n";
  return 0;
}
