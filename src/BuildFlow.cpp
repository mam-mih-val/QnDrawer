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
  auto file_out = new TFile(output_file_name.data(), "recreate");
  FlowBuilder builder;
  std::vector<std::string> first_names{"FWs1(MDCf,MDCb)", "FWs1(MDCf,FWs2)",
                                       "FWs1(MDCf,FWs3)", "FWs1(MDCb,FWs2)",
                                       "FWs1(MDCb,FWs3)", "FWs1(FWs2,FWs3)"};
  std::vector<std::string> second_names{"FWs2(MDCf,MDCb)", "FWs2(MDCf,FWs1)",
                                        "FWs2(MDCf,FWs3)", "FWs2(MDCb,FWs1)",
                                        "FWs2(MDCb,FWs3)", "FWs2(FWs1,FWs3)"};
  std::vector<std::string> third_names{"FWs3(MDCf,MDCb)", "FWs3(MDCf,FWs1)",
                                       "FWs3(MDCf,FWs2)", "FWs3(MDCb,FWs1)",
                                       "FWs3(MDCb,FWs2)", "FWs3(FWs1,FWs2)"};
  std::vector<std::string> forward_names{"MDCf(MDCb,Fws1)", "MDCf(MDCb,FWs2)",
                                         "MDCf(MDCb,FWs3)", "MDCf(FWs1,FWs2)",
                                         "MDCf(FWs1,FWs3)", "MDCf(FWs2,FWs3)"};
  std::vector<std::string> backward_names{"MDCb(MDCf,Fws1)", "MDCb(MDCf,FWs2)",
                                          "MDCb(MDCf,FWs3)", "MDCb(FWs1,FWs2)",
                                          "MDCb(FWs1,FWs3)", "MDCb(FWs2,FWs3)"};
  builder.SetName("FlowBuilder");
  builder.SetInputName(input_file_name);
  builder.SetConfigFileName(config_file_name);
  std::vector<std::string> components{"_XX", "_YY"};
  std::vector<std::string> methods{"_Sp"};

  // ******************************** Method of 3 Sub-Events in MDC+FW ******************************** //
  for (auto component : components) {
    for(const auto & first_name : first_names){
      builder.ComputeMethodRamSaving(
          first_name + component + "_Sp",
          [](std::vector<Qn::DataContainer<Qn::Stats>> corr) {
            Qn::DataContainer<Qn::Stats> result;
            result = Sqrt(corr.at(0) * corr.at(1) / (corr.at(2)) * 2);
            return result;
          },
          [](std::vector<Qn::DataContainer<Qn::Stats>> corr) {
            Qn::DataContainer<Qn::Stats> result;
            result = corr.at(0) * 2 / corr.at(1);
            return result;
          },
          file_out);
    }
    for(const auto & second_name : second_names){
      builder.ComputeMethodRamSaving(
          second_name + component + "_Sp",
          [](std::vector<Qn::DataContainer<Qn::Stats>> corr) {
            Qn::DataContainer<Qn::Stats> result;
            result = Sqrt(corr.at(0) * corr.at(1) / (corr.at(2)) * 2);
            return result;
          },
          [](std::vector<Qn::DataContainer<Qn::Stats>> corr) {
            Qn::DataContainer<Qn::Stats> result;
            result = corr.at(0) * 2 / corr.at(1);
            return result;
          },
          file_out);
    }
    for(const auto & third_name : third_names){
      builder.ComputeMethodRamSaving(
          third_name + component + "_Sp",
          [](std::vector<Qn::DataContainer<Qn::Stats>> corr) {
            Qn::DataContainer<Qn::Stats> result;
            result = Sqrt(corr.at(0) * corr.at(1) / (corr.at(2)) * 2);
            return result;
          },
          [](std::vector<Qn::DataContainer<Qn::Stats>> corr) {
            Qn::DataContainer<Qn::Stats> result;
            result = corr.at(0) * 2 / corr.at(1);
            return result;
          }, 
          file_out);
    }
    for(const auto & forward_name : forward_names){
      builder.ComputeMethodRamSaving(
          forward_name + component + "_Sp",
          [](std::vector<Qn::DataContainer<Qn::Stats>> corr) {
            Qn::DataContainer<Qn::Stats> result;
            result = Sqrt(corr.at(0) * corr.at(1) / (corr.at(2)) * 2);
            return result;
          },
          [](std::vector<Qn::DataContainer<Qn::Stats>> corr) {
            Qn::DataContainer<Qn::Stats> result;
            result = corr.at(0) * 2 / corr.at(1);
            return result;
          }, 
          file_out);
    }
    for(const auto & backward_name : backward_names){
      builder.ComputeMethodRamSaving(
          backward_name + component + "_Sp",
          [](std::vector<Qn::DataContainer<Qn::Stats>> corr) {
            Qn::DataContainer<Qn::Stats> result;
            result = Sqrt(corr.at(0) * corr.at(1) / (corr.at(2)) * 2);
            return result;
          },
          [](std::vector<Qn::DataContainer<Qn::Stats>> corr) {
            Qn::DataContainer<Qn::Stats> result;
            result = corr.at(0) * 2 / corr.at(1);
            return result;
          }, 
          file_out);
    }
  }
  /*
  // ******************************** Second Harmonics ******************************** //
  components = {"_XXX", "_XYY", "_YXY", "_YYX"};
  for( const auto& component : components ) {
    for(const auto & first_name : first_names){
      for(const auto & second_name : second_names){
        builder.ComputeMethodRamSaving(
            first_name + "_" + second_name + component + "_Sp",
            [](std::vector<Qn::DataContainer<Qn::Stats>> corr) {
              Qn::DataContainer<Qn::Stats> result;
              result = Sqrt(corr.at(0) * corr.at(1) / corr.at(2) * corr.at(3) *
                            corr.at(4) / corr.at(5)) *
                       2;
              return result;
            },
            [](std::vector<Qn::DataContainer<Qn::Stats>> corr) {
              Qn::DataContainer<Qn::Stats> result;
              result = corr.at(0) * 4 / corr.at(1);
              return result;
            });
      }
    }
    for(const auto & second_name : second_names){
      for(const auto & third_name : third_names){
        builder.ComputeMethodRamSaving(
            second_name + "_" + third_name + component + "_Sp",
            [](std::vector<Qn::DataContainer<Qn::Stats>> corr) {
              Qn::DataContainer<Qn::Stats> result;
              result = Sqrt(corr.at(0) * corr.at(1) / corr.at(2) * corr.at(3) *
                            corr.at(4) / corr.at(5)) *
                       2;
              return result;
            },
            [](std::vector<Qn::DataContainer<Qn::Stats>> corr) {
              Qn::DataContainer<Qn::Stats> result;
              result = corr.at(0) * 4 / corr.at(1);
              return result;
            });
      }
    }
    for(const auto & first_name : first_names){
      for(const auto & third_name : third_names){
        builder.ComputeMethodRamSaving(
            first_name + "_" + third_name + component + "_Sp",
            [](std::vector<Qn::DataContainer<Qn::Stats>> corr) {
              Qn::DataContainer<Qn::Stats> result;
              result = Sqrt(corr.at(0) * corr.at(1) / corr.at(2) * corr.at(3) *
                            corr.at(4) / corr.at(5)) *
                       2;
              return result;
            },
            [](std::vector<Qn::DataContainer<Qn::Stats>> corr) {
              Qn::DataContainer<Qn::Stats> result;
              result = corr.at(0) * 4 / corr.at(1);
              return result;
            });
      }
    }
  }
  /*
  components = {"_XXXX", "_XYYX", "_XYXY", "_XXYY", "_YYXX", "_YXYX", "_YXXY", "_YYYY"};
  for( auto component : components ) {
    for (size_t i = 0; i < first_names.size(); ++i) {
      for (size_t j = 0; j < second_names.size(); ++j) {
        for( size_t k = 0; k < third_names.size(); ++k ){
          builder.ComputeMethodRamSaving(first_names.at(i) + "_" +
                                      second_names.at(j) + "_" +
                                      third_names.at(k) + component +
                                      "_Sp",
                            [](std::vector<Qn::DataContainer<Qn::Stats>> corr){
                              Qn::DataContainer<Qn::Stats> result;
                              result = Sqrt(corr.at(0)*corr.at(1)/corr.at(2) * corr.at(3)*corr.at(4)/corr.at(5) * corr.at(6)*corr.at(7)/corr.at(8) ) * 2*sqrt(2);
                              return result;
                            },
                            [](std::vector<Qn::DataContainer<Qn::Stats>> corr){
                Qn::DataContainer<Qn::Stats> result;
                result = corr.at(0)*8/corr.at(1);
                return result;
          });
        }
      }
    }
  }*/
//  builder.Compute();
//  builder.Rebin();
//  builder.Projection();
//  builder.SaveGraphsToFile(output_file_name);
//  builder.SaveToFile(output_file_name);
file_out->Close();
  auto end = std::chrono::system_clock::now();
  std::chrono::duration<double> elapsed_seconds = end - start;
  std::cout << "elapsed time: " << elapsed_seconds.count() << " s\n";
  return 0;
}
