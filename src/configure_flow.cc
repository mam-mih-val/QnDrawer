//
// Created by mikhail on 18.10.2019.
//
#include "flow_configuration.h"
#include <TFile.h>
#include <iostream>

void ConfigureFw3s(const std::string& file_name);
void ConfigureFw3x(const std::string& file_name);
void ConfigureRnd(std::string);

int main(int argv, char **argc) {
  if (argv < 2) {
    std::cout << "Error: Incorrect number of arguments." << std::endl;
    return 1;
  }
  std::string flag{argc[1]};
  std::string file_name{argc[2]};
  if(flag == "--RND")
    ConfigureRnd(file_name);
  if(flag == "--FW3S")
    ConfigureFw3s(file_name);
  if(flag == "--FW3X")
    ConfigureFw3x(file_name);
  return 0;
}

void ConfigureFw3s(const std::string& file_name){
  TFile *file = TFile::Open(file_name.data(), "recreate");
  std::vector<FlowConfiguration> configurations;
  std::vector<std::string> components{"_XX", "_YY"};
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
  std::map<std::string, std::string> correlations_names{
      std::make_pair("<MDCf,MDCb>","MdcQ_MdcQ"),
      std::make_pair("<MDCf,FWs1>","MdcQ_Fw1"),
      std::make_pair("<MDCf,FWs2>","MdcQ_Fw2"),
      std::make_pair("<MDCf,FWs3>","MdcQ_Fw3"),
      std::make_pair("<MDCb,FWs1>","MdcQ_Fw1"),
      std::make_pair("<MDCb,FWs2>","MdcQ_Fw2"),
      std::make_pair("<MDCb,FWs3>","MdcQ_Fw3"),
      std::make_pair("<FWs1,FWs2>","Fw1_Fw2"),
      std::make_pair("<FWs1,FWs3>","Fw1_Fw3"),
      std::make_pair("<FWs2,FWs3>","Fw2_Fw3")
  };
  std::map<std::string, std::vector<Qn::Axis>> rebin_axis{
      std::make_pair<std::string, std::vector<Qn::Axis>>( "<MDCf,MDCb>", { {"0_Ycm", 1, -0.55, -0.35}, {"1_Ycm", 1, 0.35, 0.55} }),
      std::make_pair<std::string, std::vector<Qn::Axis>>( "<MDCf,FWs1>", { {"0_Ycm", 1, 0.35, 0.55} }),
      std::make_pair<std::string, std::vector<Qn::Axis>>( "<MDCf,FWs2>", { {"0_Ycm", 1, 0.35, 0.55} }),
      std::make_pair<std::string, std::vector<Qn::Axis>>( "<MDCf,FWs3>", { {"0_Ycm", 1, 0.35, 0.55} }),
      std::make_pair<std::string, std::vector<Qn::Axis>>( "<MDCb,FWs1>", { {"0_Ycm", 1, -0.55, -0.35} }),
      std::make_pair<std::string, std::vector<Qn::Axis>>( "<MDCb,FWs2>", { {"0_Ycm", 1, -0.55, -0.35} }),
      std::make_pair<std::string, std::vector<Qn::Axis>>( "<MDCb,FWs3>", { {"0_Ycm", 1, -0.55, -0.35} }),
      std::make_pair<std::string, std::vector<Qn::Axis>>( "<FWs1,FWs2>", {}),
      std::make_pair<std::string, std::vector<Qn::Axis>>( "<FWs1,FWs3>", {}),
      std::make_pair<std::string, std::vector<Qn::Axis>>( "<FWs2,FWs3>", {})
  };
  std::vector<std::vector<std::string>> first_resolutions{
      {"<MDCf,FWs1>", "<MDCb,FWs1>", "<MDCf,MDCb>"}, // FWs1(MDCf, MDCb)
      {"<MDCf,FWs1>", "<FWs1,FWs2>", "<MDCf,FWs2>"},     // FWs1(MDCf, FWs2)
      {"<MDCf,FWs1>", "<FWs1,FWs3>", "<MDCf,FWs3>"},     // FWs1(MDCf, FWs3)
      {"<MDCb,FWs1>", "<FWs1,FWs2>", "<MDCb,FWs2>"},     // FWs1(MDCb, FWs2)
      {"<MDCb,FWs1>", "<FWs1,FWs3>", "<MDCb,FWs3>"},     // FWs1(MDCb, FWs3)
      {"<FWs1,FWs2>", "<FWs1,FWs3>", "<FWs2,FWs3>"}      // FWs1(FWs2, FWs3)
  };
  std::vector<std::vector<std::string>> second_resolutions{
      {"<MDCf,FWs2>", "<MDCb,FWs2>", "<MDCf,MDCb>"},     // FWs2(MDCf, MDCb)
      {"<MDCf,FWs2>", "<FWs1,FWs2>", "<MDCf,FWs1>"},     // FWs2(MDCf, FWs1)
      {"<MDCf,FWs2>", "<FWs2,FWs3>", "<MDCf,FWs3>"},     // FWs2(MDCf, FWs3)
      {"<MDCb,FWs2>", "<FWs1,FWs2>", "<MDCb,FWs1>"},     // FWs2(MDCb, FWs1)
      {"<MDCb,FWs2>", "<FWs2,FWs3>", "<MDCb,FWs3>"},     // FWs2(MDCb, FWs3)
      {"<FWs1,FWs2>", "<FWs2,FWs3>", "<FWs1,FWs3>"}      // FWs2(FWs1, FWs3)
  };
  std::vector<std::vector<std::string>> third_resolutions{
      {"<MDCf,FWs3>", "<MDCb,FWs3>", "<MDCf,MDCb>"},     // FWs3(MDCf, MDCb)
      {"<MDCf,FWs3>", "<FWs1,FWs3>", "<MDCf,FWs1>"},     // FWs3(MDCf, FWs1)
      {"<MDCf,FWs3>", "<FWs2,FWs3>", "<MDCf,FWs2>"},     // FWs3(MDCf, FWs2)
      {"<MDCb,FWs3>", "<FWs1,FWs3>", "<MDCb,FWs1>"},     // FWs3(MDCb, FWs1)
      {"<MDCb,FWs3>", "<FWs2,FWs3>", "<MDCb,FWs2>"},     // FWs3(MDCb, FWs2)
      {"<FWs1,FWs3>", "<FWs2,FWs3>", "<FWs1,FWs2>"}      // FWs3(FWs1, FWs2)
  };
  std::vector<std::vector<std::string>> forward_resolutions{
      {"<MDCf,FWs1>", "<MDCf,MDCb>", "<MDCb,FWs1>"},      // MDCf(MDCb,FWs1)
      {"<MDCf,FWs2>", "<MDCf,MDCb>", "<MDCb,FWs2>"},      // MDCf(MDCb,FWs2)
      {"<MDCf,FWs3>", "<MDCf,MDCb>", "<MDCb,FWs3>"},      // MDCf(MDCb,FWs3)
      {"<MDCf,FWs1>", "<MDCf,FWs2>", "<FWs1,FWs2>"},      // MDCf(FWs1,FWs2)
      {"<MDCf,FWs1>", "<MDCf,FWs3>", "<FWs1,FWs3>"},      // MDCf(FWs1,FWs3)
      {"<MDCf,FWs2>", "<MDCf,FWs3>", "<FWs2,FWs3>"}       // MDCf(FWs2,FWs3)
  };
  std::vector<std::vector<std::string>> backward_resolutions{
      {"<MDCb,FWs1>", "<MDCf,MDCb>", "<MDCf,FWs1>"},      // MDCb(MDCf,FWs1)
      {"<MDCb,FWs2>", "<MDCf,MDCb>", "<MDCf,FWs2>"},      // MDCb(MDCf,FWs2)
      {"<MDCb,FWs3>", "<MDCf,MDCb>", "<MDCf,FWs3>"},      // MDCb(MDCf,FWs3)
      {"<MDCb,FWs1>", "<MDCb,FWs2>", "<FWs1,FWs2>"},      // MDCb(FWs1,FWs2)
      {"<MDCb,FWs1>", "<MDCb,FWs3>", "<FWs1,FWs3>"},      // MDCb(FWs1,FWs3)
      {"<MDCb,FWs2>", "<MDCb,FWs3>", "<FWs2,FWs3>"}       // MDCb(FWs2,FWs3)
  };
  for(auto component : components){
    configurations.emplace_back("<MDCf,MDCb>(FWs1,FWs3)"+component);
    configurations.back().SetQnQnNames({"TracksMdc_Fw1"+component+"_Sp",
                                        "TracksMdc_Fw3"+component+"_Sp",
                                        "Fw1_Fw3"+component+"_Sp",});
    configurations.back().SetUnQnNames({"TracksMdc_TracksMdc"+ component + "_Sp"});

    configurations.emplace_back("<MDCb,MDCf>(FWs1,FWs3)"+component);
    configurations.back().SetQnQnNames({"TracksMdc_Fw1"+component+"_Sp",
                                        "TracksMdc_Fw3"+component+"_Sp",
                                        "Fw1_Fw3"+component+"_Sp",});
    configurations.back().SetUnQnNames({"TracksMdc_TracksMdc"+ component + "_Sp"});

    configurations.emplace_back("<MDCf,FWs1>(MDCb,FWs3)"+component);
    configurations.back().SetQnQnNames({"TracksMdc_Fw1"+component+"_Sp",
                                        "Fw1_Fw3"+component+"_Sp",
                                        "TracksMdc_Fw3"+component+"_Sp",});
    configurations.back().SetUnQnNames({"TracksMdc_Fw1"+ component + "_Sp"});

    configurations.emplace_back("<MDCb,FWs1>(MDCf,FWs3)"+component);
    configurations.back().SetQnQnNames({"TracksMdc_Fw1"+component+"_Sp",
                                        "Fw1_Fw3"+component+"_Sp",
                                        "TracksMdc_Fw3"+component+"_Sp",});
    configurations.back().SetUnQnNames({"TracksMdc_Fw1"+ component + "_Sp"});

    configurations.emplace_back("<MDCf,FWs3>(MDCb,FWs1)"+component);
    configurations.back().SetQnQnNames({"TracksMdc_Fw3"+component+"_Sp",
                                        "Fw1_Fw3"+component+"_Sp",
                                        "TracksMdc_Fw1"+component+"_Sp",});
    configurations.back().SetUnQnNames({"TracksMdc_Fw3"+ component + "_Sp"});

    configurations.emplace_back("<MDCb,FWs3>(MDCf,FWs1)"+component);
    configurations.back().SetQnQnNames({"TracksMdc_Fw3"+component+"_Sp",
                                        "Fw1_Fw3"+component+"_Sp",
                                        "TracksMdc_Fw1"+component+"_Sp",});
    configurations.back().SetUnQnNames({"TracksMdc_Fw3"+ component + "_Sp"});
  }
  // ******************************** Method of 3 Sub-Events in MDC+FW
  // ******************************** //
  for (const auto& component : components) {
    for(size_t i=0; i<first_names.size(); ++i){
      configurations.emplace_back(first_names.at(i) + component +"_Sp");
      std::vector<std::string> resolution = first_resolutions.at(i);
      std::vector<std::string> qn_qn_correlations;
      std::vector<std::vector<Qn::Axis>> qn_qn_rebin_axis;
      qn_qn_correlations.reserve(resolution.size());
      for(const auto& correlation : resolution){
        qn_qn_correlations.push_back(correlations_names.at(correlation)+component+"_Sp");
        qn_qn_rebin_axis.push_back(rebin_axis.at(correlation));
      }
      configurations.back().SetQnQnNames(qn_qn_correlations);
      configurations.back().SetQnQnRebinAxis(qn_qn_rebin_axis);
      configurations.back().SetUnQnNames({"TracksMdc_Fw1" + component + "_Sp"});
    }
    for(size_t i=0; i<second_names.size(); ++i){
      configurations.emplace_back(second_names.at(i) + component +"_Sp");
      std::vector<std::string> resolution = second_resolutions.at(i);
      std::vector<std::string> qn_qn_correlations;
      std::vector<std::vector<Qn::Axis>> qn_qn_rebin_axis;
      qn_qn_correlations.reserve(resolution.size());
      for(const auto& correlation : resolution){
        qn_qn_correlations.push_back(correlations_names.at(correlation)+component+"_Sp");
        qn_qn_rebin_axis.push_back(rebin_axis.at(correlation));
      }
      configurations.back().SetQnQnNames(qn_qn_correlations);
      configurations.back().SetQnQnRebinAxis(qn_qn_rebin_axis);
      configurations.back().SetUnQnNames({"TracksMdc_Fw2" + component + "_Sp"});
    }
    for(size_t i=0; i<third_names.size(); ++i){
      configurations.emplace_back(third_names.at(i) + component +"_Sp");
      std::vector<std::string> resolution = third_resolutions.at(i);
      std::vector<std::string> qn_qn_correlations;
      std::vector<std::vector<Qn::Axis>> qn_qn_rebin_axis;
      qn_qn_correlations.reserve(resolution.size());
      for(const auto& correlation : resolution){
        qn_qn_correlations.push_back(correlations_names.at(correlation)+component+"_Sp");
        qn_qn_rebin_axis.push_back(rebin_axis.at(correlation));
      }
      configurations.back().SetQnQnNames(qn_qn_correlations);
      configurations.back().SetQnQnRebinAxis(qn_qn_rebin_axis);
      configurations.back().SetUnQnNames({"TracksMdc_Fw3" + component + "_Sp"});
    }
    for(size_t i=0; i<forward_names.size(); ++i){
      configurations.emplace_back(forward_names.at(i) + component +"_Sp");
      std::vector<std::string> resolution = forward_resolutions.at(i);
      std::vector<std::string> qn_qn_correlations;
      std::vector<std::vector<Qn::Axis>> qn_qn_rebin_axis;
      qn_qn_correlations.reserve(resolution.size());
      for(const auto& correlation : resolution){
        qn_qn_correlations.push_back(correlations_names.at(correlation)+component+"_Sp");
        qn_qn_rebin_axis.push_back(rebin_axis.at(correlation));
      }
      configurations.back().SetQnQnNames(qn_qn_correlations);
      configurations.back().SetQnQnRebinAxis(qn_qn_rebin_axis);
      configurations.back().SetUnQnNames({"TracksMdc_MdcQ" + component + "_Sp"});
    }
    for(size_t i=0; i<backward_names.size(); ++i){
      configurations.emplace_back(backward_names.at(i) + component +"_Sp");
      std::vector<std::string> resolution = backward_resolutions.at(i);
      std::vector<std::string> qn_qn_correlations;
      std::vector<std::vector<Qn::Axis>> qn_qn_rebin_axis;
      qn_qn_correlations.reserve(resolution.size());
      for(const auto& correlation : resolution){
        qn_qn_correlations.push_back(correlations_names.at(correlation)+component+"_Sp");
        qn_qn_rebin_axis.push_back(rebin_axis.at(correlation));
      }
      configurations.back().SetQnQnNames(qn_qn_correlations);
      configurations.back().SetQnQnRebinAxis(qn_qn_rebin_axis);
      configurations.back().SetUnQnNames({"TracksMdc_MdcQ" + component + "_Sp"});
    }
  }
  // Second Harmoinc
  std::vector<std::vector<std::string>> resolution_components = {
      {"_XXX", "_XX", "_XX"},
      {"_XYY", "_YY", "_YY"},
      {"_YXY", "_XX", "_YY"},
      {"_YYX", "_YY", "_XX"}};

  for (auto component : resolution_components) {
    for (size_t i = 0; i < first_names.size(); ++i) {
      for (size_t j = 0; j < second_names.size(); ++j) {
        configurations.emplace_back(first_names.at(i) + "_" +
                                    second_names.at(j) + component.at(0) +
                                    "_Sp");
        std::vector<std::string> resolution_first = first_resolutions.at(i);
        std::vector<std::string> resolution_second = second_resolutions.at(j);
        std::vector<std::string> qn_qn_correlations;
        std::vector<std::vector<Qn::Axis>> qn_qn_rebin_axis;
        qn_qn_correlations.reserve(resolution_first.size());
        for(const auto& correlation : resolution_first){
          qn_qn_correlations.push_back(correlations_names.at(correlation)+component.at(1)+"_Sp");
          qn_qn_rebin_axis.push_back(rebin_axis.at(correlation));
        }
        for(const auto& correlation : resolution_second){
          qn_qn_correlations.push_back(correlations_names.at(correlation)+component.at(2)+"_Sp");
          qn_qn_rebin_axis.push_back(rebin_axis.at(correlation));
        }
        configurations.back().SetQnQnNames(qn_qn_correlations);
        configurations.back().SetQnQnRebinAxis(qn_qn_rebin_axis);
        configurations.back().SetUnQnNames(
            {"TracksMdc_Fw1_Fw2" + component.at(0) + "_Sp"});
      }
    }
    for (size_t i = 0; i < second_names.size(); ++i) {
      for (size_t j = 0; j < third_names.size(); ++j) {
        configurations.emplace_back(second_names.at(i) + "_" +
                                    third_names.at(j) + component.at(0) +
                                    "_Sp");
        std::vector<std::string> resolution_second = second_resolutions.at(i);
        std::vector<std::string> resolution_third = third_resolutions.at(j);
        std::vector<std::string> qn_qn_correlations;
        std::vector<std::vector<Qn::Axis>> qn_qn_rebin_axis;
        qn_qn_correlations.reserve(resolution_third.size());
        for(const auto& correlation : resolution_second){
          qn_qn_correlations.push_back(correlations_names.at(correlation)+component.at(1)+"_Sp");
          qn_qn_rebin_axis.push_back(rebin_axis.at(correlation));
        }
        for(const auto& correlation : resolution_third){
          qn_qn_correlations.push_back(correlations_names.at(correlation)+component.at(2)+"_Sp");
          qn_qn_rebin_axis.push_back(rebin_axis.at(correlation));
        }
        configurations.back().SetQnQnNames(qn_qn_correlations);
        configurations.back().SetQnQnRebinAxis(qn_qn_rebin_axis);
        configurations.back().SetUnQnNames(
            {"TracksMdc_Fw2_Fw3" + component.at(0) + "_Sp"});
      }
    }
    for (size_t i = 0; i < first_names.size(); ++i) {
      for (size_t j = 0; j < third_names.size(); ++j) {
        configurations.emplace_back(first_names.at(i) + "_" +
                                    third_names.at(j) + component.at(0) +
                                    "_Sp");
        std::vector<std::string> resolution_first = first_resolutions.at(i);
        std::vector<std::string> resolution_third = third_resolutions.at(j);
        std::vector<std::string> qn_qn_correlations;
        std::vector<std::vector<Qn::Axis>> qn_qn_rebin_axis;
        qn_qn_correlations.reserve(resolution_first.size());
        for(const auto& correlation : resolution_first){
          qn_qn_correlations.push_back(correlations_names.at(correlation)+component.at(1)+"_Sp");
          qn_qn_rebin_axis.push_back(rebin_axis.at(correlation));
        }
        for(const auto& correlation : resolution_third){
          qn_qn_correlations.push_back(correlations_names.at(correlation)+component.at(2)+"_Sp");
          qn_qn_rebin_axis.push_back(rebin_axis.at(correlation));
        }
        configurations.back().SetQnQnNames(qn_qn_correlations);
        configurations.back().SetQnQnRebinAxis(qn_qn_rebin_axis);
        configurations.back().SetUnQnNames(
            {"TracksMdc_Fw1_Fw3" + component.at(0) + "_Sp"});
      }
    }
  }
  /*
  resolution_components = {
      {"_XXXX", "_XX", "_XX", "_XX"}, {"_XYYX", "_YY", "_YY", "_XX"},
      {"_XYXY", "_YY", "_XX", "_YY"}, {"_XXYY", "_XX", "_YY", "_XX"},
      {"_YYXX", "_YY", "_XX", "_XX"}, {"_YXYX", "_XX", "_YY", "_XX"},
      {"_YXXY", "_XX", "_XX", "_YY"}, {"_YYYY", "_YY", "_YY", "_YY"}};
  for (auto component : resolution_components) {
    for (size_t i = 0; i < first_resolutions.size(); ++i) {
      for (size_t j = 0; j < second_resolutions.size(); ++j) {
        for (size_t k = 0; k < third_resolutions.size(); ++k) {
          configurations.emplace_back(
              first_names.at(i) + "_" + second_names.at(j) + "_" +
              third_names.at(k) + component.at(0) + "_Sp");
          std::vector<std::string> resolution;
          std::vector<std::string> first_resolution = first_resolutions.at(i);
          std::for_each(first_resolution.begin(), first_resolution.end(),
                        [component](std::string &str) {
                          str += component.at(1) + "_Sp";
                        });
          std::vector<std::string> second_resolution = second_resolutions.at(j);
          std::for_each(second_resolution.begin(), second_resolution.end(),
                        [component](std::string &str) {
                          str += component.at(2) + "_Sp";
                        });
          std::vector<std::string> third_resolution = third_resolutions.at(k);
          std::for_each(third_resolution.begin(), third_resolution.end(),
                        [component](std::string &str) {
                          str += component.at(3) + "_Sp";
                        });
          resolution.insert(resolution.end(), first_resolution.begin(),
                            first_resolution.end());
          resolution.insert(resolution.end(), second_resolution.begin(),
                            second_resolution.end());
          resolution.insert(resolution.end(), third_resolution.begin(),
                            third_resolution.end());
          configurations.back().SetQnQnNames(resolution);
          configurations.back().SetUnQnNames(
              {"TracksMdc_Fw1_Fw2_Fw3" + component.at(0) + "_Sp"});
          configurations.back().SetProjectionAxisName("Centrality");
        }
      }
    }
  }
   */
  file->cd();
  for (auto &configuration : configurations)
    configuration.SaveToFile(file);
  std::cout << "Configurations written in " << file_name << std::endl;
  file->Close();
}
void ConfigureFw3x(const std::string& file_name){
  TFile *file = TFile::Open(file_name.data(), "recreate");
  std::vector<FlowConfiguration> configurations;
  std::vector<std::string> forward_names{"MDCf(FWs1,FWs2)", "MDCf(FWs1,FWs3)", "MDCf(FWs2,FWs3)"};
  std::vector<std::string> backward_names{"MDCb(FWs1,FWs2)", "MDCb(FWs1,FWs3)", "MDCb(FWs2,FWs3)"};
  std::map<std::string, std::string> correlations_names{
      std::make_pair("<MDCf,FWs1,FWs2>","MdcQ_Fw1_Fw2"),
      std::make_pair("<MDCf,FWs1,FWs3>","MdcQ_Fw1_Fw3"),
      std::make_pair("<MDCf,FWs2,FWs3>","MdcQ_Fw2_Fw3"),
      std::make_pair("<MDCb,FWs1,FWs2>","MdcQ_Fw1_Fw2"),
      std::make_pair("<MDCb,FWs1,FWs3>","MdcQ_Fw1_Fw3"),
      std::make_pair("<MDCb,FWs2,FWs3>","MdcQ_Fw2_Fw3"),
      std::make_pair("<FWs1,FWs2>","Fw1_Fw2"),
      std::make_pair("<FWs1,FWs3>","Fw1_Fw3"),
      std::make_pair("<FWs2,FWs3>","Fw2_Fw3")
  };
  std::map<std::string, std::vector<Qn::Axis>> rebin_axis{
      std::make_pair<std::string, std::vector<Qn::Axis>>( "<MDCf,FWs1,FWs2>", { {"0_Ycm", 1, 0.35, 0.55} }),
      std::make_pair<std::string, std::vector<Qn::Axis>>( "<MDCf,FWs1,FWs3>", { {"0_Ycm", 1, 0.35, 0.55} }),
      std::make_pair<std::string, std::vector<Qn::Axis>>( "<MDCf,FWs2,FWs3>", { {"0_Ycm", 1, 0.35, 0.55} }),
      std::make_pair<std::string, std::vector<Qn::Axis>>( "<MDCb,FWs1,FWs2>", { {"0_Ycm", 1, -0.55, -0.35} }),
      std::make_pair<std::string, std::vector<Qn::Axis>>( "<MDCb,FWs1,FWs3>", { {"0_Ycm", 1, -0.55, -0.35} }),
      std::make_pair<std::string, std::vector<Qn::Axis>>( "<MDCb,FWs2,FWs3>", { {"0_Ycm", 1, -0.55, -0.35} }),
      std::make_pair<std::string, std::vector<Qn::Axis>>( "<FWs1,FWs2>", {}),
      std::make_pair<std::string, std::vector<Qn::Axis>>( "<FWs1,FWs3>", {}),
      std::make_pair<std::string, std::vector<Qn::Axis>>( "<FWs2,FWs3>", {})
  };
  std::vector<std::vector<std::string>> forward_resolutions{
      {"<MDCf,FWs1,FWs2>", "<FWs1,FWs2>"},      // MDCf(FWs1,FWs2)
      {"<MDCf,FWs1,FWs3>", "<FWs1,FWs3>"},      // MDCf(FWs1,FWs3)
      {"<MDCf,FWs2,FWs3>", "<FWs2,FWs3>"},      // MDCf(FWs2,FWs3)
  };
  std::vector<std::vector<std::string>> backward_resolutions{
      {"<MDCb,FWs1,FWs2>", "<FWs1,FWs2>"},      // MDCb(FWs1,FWs2)
      {"<MDCb,FWs1,FWs3>", "<FWs1,FWs3>"},      // MDCb(FWs1,FWs3)
      {"<MDCb,FWs2,FWs3>", "<FWs2,FWs3>"},      // MDCb(FWs2,FWs3)
  };
  std::vector<std::vector<std::string>> resolution_components = {
      {"_XXx", "_XX", "_XXX", "_XX"},
      {"_XXy", "_XX", "_XYY", "_YY"},
  };
  for (const auto &component : resolution_components) {
    for (size_t i = 0; i < forward_names.size(); ++i) {
      configurations.emplace_back(forward_names.at(i) + component.at(0) +
                                  "_Sp");
      std::vector<std::string> resolution = forward_resolutions.at(i);
      std::vector<std::string> qn_qn_correlations;
      std::vector<std::vector<Qn::Axis>> qn_qn_rebin_axis;
      qn_qn_correlations.reserve(resolution.size());
      int j = 2;
      for (const auto &correlation : resolution) {
        qn_qn_correlations.push_back(correlations_names.at(correlation) +
                                     component.at(j) + "_Sp");
        qn_qn_rebin_axis.push_back(rebin_axis.at(correlation));
        j++;
      }
      configurations.back().SetQnQnNames(qn_qn_correlations);
      configurations.back().SetQnQnRebinAxis(qn_qn_rebin_axis);
      configurations.back().SetUnQnNames(
          {"TracksMdc2_MdcQ2" + component.at(1) + "_Sp"});
    }
    for (size_t i = 0; i < backward_names.size(); ++i) {
      configurations.emplace_back(backward_names.at(i) + component.at(0) +
                                  "_Sp");
      std::vector<std::string> resolution = backward_resolutions.at(i);
      std::vector<std::string> qn_qn_correlations;
      std::vector<std::vector<Qn::Axis>> qn_qn_rebin_axis;
      qn_qn_correlations.reserve(resolution.size());
      int j = 2;
      for (const auto &correlation : resolution) {
        qn_qn_correlations.push_back(correlations_names.at(correlation) +
                                     component.at(j) + "_Sp");
        qn_qn_rebin_axis.push_back(rebin_axis.at(correlation));
        j++;
      }
      configurations.back().SetQnQnNames(qn_qn_correlations);
      configurations.back().SetQnQnRebinAxis(qn_qn_rebin_axis);
      configurations.back().SetUnQnNames(
          {"TracksMdc2_MdcQ2" + component.at(1) + "_Sp"});
    }
  }

  file->cd();
  for (auto &configuration : configurations)
    configuration.SaveToFile(file);
  std::cout << "Configurations written in " << file_name << std::endl;
  file->Close();
}

void ConfigureRnd(std::string file_name){
  TFile *file = TFile::Open(file_name.data(), "recreate");
  std::vector<FlowConfiguration> configurations;
  std::vector<std::string> components{"_XX", "_YY"};
  std::vector<std::string> first_names{"RND"};
  std::vector<std::string> second_names{"RND_2"};
  std::vector<std::string> third_names{"RND_2_NE"};
  std::vector<std::string> fourth_names{"RND_NE1", "RND_NE2"};

  std::vector<std::vector<std::string>> first_resolutions{
      {"Rs1_Rs2"},     // RND
  };
  std::vector<std::vector<std::string>> second_resolutions{
      {"Rs1_Rs2"},     // RND
  };
  std::vector<std::vector<std::string>> third_resolutions{
      {"Rs1_Rs2"},     // RND
  };
  std::vector<std::vector<std::string>> fourth_resolutions{
      {"Rs1_Rs2"},     // RND
      {"Rs1_Rs2"}     // RND
  };

  for (const auto& component : components) {
    for(size_t i=0; i<first_names.size(); ++i){
      configurations.emplace_back(first_names.at(i) + component +"_Ep");
      std::vector<std::string> resolution = first_resolutions.at(i);
      for(auto& correlation : resolution)
        correlation+=component+"_Ep";
      configurations.back().SetQnQnNames(resolution);
      configurations.back().SetUnQnNames({"TracksMdc_Full" + component + "_Ep"});
    }
    for(size_t i=0; i<second_names.size(); ++i){
      configurations.emplace_back(second_names.at(i) + component +"_Ep");
      std::vector<std::string> resolution = second_resolutions.at(i);
      for(auto& correlation : resolution)
        correlation+=component+"_Ep";
      configurations.back().SetQnQnNames(resolution);
      configurations.back().SetUnQnNames({"TracksMdc2_Full2" + component + "_Ep"});
    }
    for(size_t i=0; i<third_names.size(); ++i){
      configurations.emplace_back(third_names.at(i) + component +"_Ep");
      std::vector<std::string> resolution = third_resolutions.at(i);
      for(auto& correlation : resolution)
        correlation+=component+"_Ep";
      configurations.back().SetQnQnNames(resolution);
      configurations.back().SetUnQnNames({"TracksMdc_Rs1_Rs2" + component + "_Ep"});
    }
    for(size_t i=0; i< fourth_names.size(); ++i){
      configurations.emplace_back(fourth_names.at(i) + component +"_Ep");
      std::vector<std::string> resolution = fourth_resolutions.at(i);
      for(auto& correlation : resolution)
        correlation+=component+"_Ep";
      configurations.back().SetQnQnNames(resolution);
      configurations.back().SetUnQnNames({"TracksMdc_Rs"+std::to_string(i+1) + component + "_Ep"});
    }
  }
  components = {"XX", "YY"};
  for(const auto& component : components){
    for(size_t i=0; i<third_names.size(); ++i){
      configurations.emplace_back(third_names.at(i) + "_X" + component +"_Ep");
      std::vector<std::string> resolution = third_resolutions.at(i);
      for(auto& correlation : resolution)
        correlation+="_"+component+"_Ep";
      configurations.back().SetQnQnNames(resolution);
      configurations.back().SetUnQnNames({"TracksMdc_Rs1_Rs2_X" + component + "_Ep"});
    }
  }
  file->cd();
  for (auto &configuration : configurations)
    configuration.SaveToFile(file);
  std::cout << "Configurations written in " << file_name << std::endl;
  file->Close();
}

