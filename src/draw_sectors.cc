//
// Created by mikhail on 3/9/20.
//

#include <TFile.h>
#include <string>
#include <systematics.h>

int main(){
  std::vector<Systematics> systematics;
  std::vector<std::string> systematics_names{ "FWs1", "FWs2", "FWs3", "FWs1_FWs2", "FWs1_FWs3", "FWs2_FWs3", "RND1", "RND2" };
  std::string prefix{"flow_"};
  std::vector<std::string> file_names{"FW3S_PT2_5sectors", "FW3S_PT2_5sectors", "FW3S_PT2_5sectors",
                                      "FW3S_PT2_5sectors", "FW3S_PT2_5sectors", "FW3S_PT2_5sectors",
                                      "RND_PT2_NC_5sectors", "RND_PT2_NC_5sectors"};

  std::vector<std::vector<std::string>> sub_events_names{
      {"FWs1(MDCf,MDCb)", "FWs1(MDCf,FWs2)", "FWs1(MDCf,FWs3)", "FWs1(MDCb,FWs2)", "FWs1(MDCb,FWs3)", "FWs1(FWs2,FWs3)"},
      {"FWs2(MDCf,MDCb)", "FWs2(MDCf,FWs1)", "FWs2(MDCf,FWs3)", "FWs2(MDCb,FWs1)", "FWs2(MDCb,FWs3)", "FWs2(FWs1,FWs3)"},
      {"FWs3(MDCf,MDCb)", "FWs3(MDCf,FWs1)", "FWs3(MDCf,FWs2)", "FWs3(MDCb,FWs1)", "FWs3(MDCb,FWs2)", "FWs3(FWs1,FWs2)"},
      {"FWs1(MDCf,MDCb)_FWs2(MDCf,MDCb)", "FWs1(MDCf,FWs3)_FWs2(MDCf,MDCb)", "FWs1(MDCb,FWs3)_FWs2(MDCf,MDCb)", "FWs1(MDCb,FWs2)_FWs2(MDCb,FWs1)", "FWs1(MDCb,FWs3)_FWs2(MDCb,FWs3)", "FWs1(FWs2,FWs3)_FWs2(FWs1,FWs3)"},
      {"FWs1(MDCf,MDCb)_FWs3(MDCf,MDCb)", "FWs1(MDCf,MDCb)_FWs3(MDCf,FWs1)", "FWs1(MDCf,MDCb)_FWs3(MDCb,FWs1)", "FWs1(MDCf,FWs3)_FWs3(MDCf,MDCb)", "FWs1(MDCb,FWs3)_FWs3(MDCf,MDCb)", "FWs1(MDCf,FWs3)_FWs3(MDCf,FWs1)"},
      {"FWs2(MDCf,MDCb)_FWs3(MDCf,MDCb)", "FWs2(MDCf,MDCb)_FWs3(MDCf,FWs1)", "FWs2(MDCf,MDCb)_FWs3(MDCb,FWs1)", "FWs2(MDCb,FWs3)_FWs3(MDCb,FWs2)", "FWs2(MDCb,FWs1)_FWs3(MDCb,FWs1)", "FWs2(FWs1,FWs3)_FWs3(FWs1,FWs2)"},
      {"RND"},
      {"RND_2"},
  };
  std::vector<std::vector<std::string>> sub_events_titles{
      { // <u, W1>
          "W1 (Mf, Mb)", "W1 (Mf, W2)", "W1 (Mf, W3)", "W1 (Mb, W2)", "W1 (Mb, W3)", "W1 (W2, W3)"},
      {// <u, W2>
          "W2 (Mf, Mb)", "W2 (Mf, W1)", "W2 (Mf, W3)", "W2 (Mb, W1)", "W2 (Mb, W3)", "W2 (W1, W3)"},
      {// <u, W3>
          "W3 (Mf, Mb)", "W3 (Mf, W1)", "W3 (Mf, W2)", "W3 (Mb, W1)", "W3 (Mb, W2)", "W3 (W1, W2)"},
      { // <u,FWs1,FWs2>
          "W1(Mf,Mb) #times W2(Mf,Mb)",
          "W1(Mf,W3) #times W2(Mf,Mb)",
          "W1(Mb,W3) #times W2(Mf,Mb)",
          "W1(Mb,W2) #times W2(Mb,W1)",
          "W1(Mb,W3) #times W2(Mb,W3)",
          "W1(W2,W3) #times W2(W1,W3)"},
      {// <u, W1, W3>
          "W1(Mf,Mb) #times W3(Mf,Mb)",
          "W1(Mf,Mb) #times W3(Mf,W1)",
          "W1(Mf,Mb) #times W3(Mb,W1)",
          "W1(Mf,W3) #times W3(Mf,Mb)",
          "W1(Mb,W3) #times W3(Mf,Mb)",
          "W1(Mf,W3) #times W3(Mf,W1)",
      },
      {// <u, W2, W3>
          "W2(Mf,Mb) #times W3(Mf,Mb)",
          "W2(Mf,Mb) #times W3(Mf,W1)",
          "W2(Mf,Mb) #times W3(Mb,W1)",
          "W2(Mb,W3) #times W3(Mb,W2)",
          "W2(Mb,W1) #times W3(Mb,W1)",
          "W2(W1,W3) #times W3(W1,W2)"},
      {"RND, 5 sectors"},
      {"RND, 5 sectors"},
  };
  std::vector<std::vector<std::string>> components_names{
      {"_XX_Sp", "_YY_Sp"},
      {"_XX_Sp", "_YY_Sp"},
      {"_XX_Sp", "_YY_Sp"},
      {"_XXX_Sp", "_XYY_Sp", "_YXY_Sp", "_YYX_Sp"},
      {"_XXX_Sp", "_XYY_Sp", "_YXY_Sp", "_YYX_Sp"},
      {"_XXX_Sp", "_XYY_Sp", "_YXY_Sp", "_YYX_Sp"},
      {"_XX_Ep", "_YY_Ep"},
      {"_XX_Ep", "_YY_Ep"},
  };
  std::vector<std::vector<float>> y_axis_ranges{
      {-0.149, -0.071},
      {-0.149, -0.071},
      {-0.149, -0.071},

      {-0.139, -0.011},
      {-0.139, -0.011},
      {-0.139, -0.011},

      {-0.149, -0.071},
      {-0.139, -0.011},
  };
  std::vector<std::vector<float>> legend_positions{
      {0.4, 0.5, 0.75, 0.89},
      {0.4, 0.5, 0.75, 0.89},
      {0.4, 0.5, 0.75, 0.89},
      {0.16, 0.01, 0.5, 0.5},
      {0.16, 0.01, 0.5, 0.5},
      {0.16, 0.01, 0.5, 0.5},
      {0.4, 0.5, 0.75, 0.89},
      {0.16, 0.01, 0.5, 0.5}
  };
  std::vector<std::string> reference_prefixes{
    "flow_RND", "flow_RND", "flow_RND",
    "flow_RND_2", "flow_RND_2", "flow_RND_2",
    "flow_RND", "flow_RND_2"
  };
  std::vector<std::string> y_axis_titles{"v_{1}","v_{1}","v_{1}",
                                         "v_{2}","v_{2}","v_{2}",
                                         "v_{1}","v_{2}"};
  auto rebin_proj = [](Qn::DataContainer<Qn::Stats> container){
    container = container.Rebin({"0_Ycm", 1, -0.25, -0.15});
    container = container.Projection({"Centrality"});
    return container;
  };
  std::shared_ptr<TFile> file_ref{TFile::Open("../Output_Files/RND_PT2_corrections.root")};
  std::vector<std::shared_ptr<TCanvas>> canvases;
  for( size_t i=0; i<systematics_names.size(); i++ ){
    auto file_name = "../Output_Files/"+file_names.at(i)+".root";
    std::shared_ptr<TFile> file{ TFile::Open( file_name.data() ) };
    systematics.emplace_back(systematics_names.at(i));
    systematics.back().SetRebinProjectionRule(rebin_proj);
    systematics.back().SetXAxisRange({0.0, 40.0});
    systematics.back().SetResultPlotRange(y_axis_ranges.at(i));
    systematics.back().SetRatioPlotRange({0.81, 1.19});
    systematics.back().SetFile(file);
    auto prefixes = sub_events_names.at(i);
    std::for_each( prefixes.begin(), prefixes.end(), [prefix](std::string& str){
      str=prefix+str;
    });
    systematics.back().AddObservables( sub_events_titles.at(i), prefixes, components_names.at(i) );
    std::string canvas_name{systematics_names.at(i)+"_comp"};
    canvases.emplace_back( new TCanvas(canvas_name.data(), "", 1000, 1200) );
    systematics.back().AddReference( "RND, 6 sectors", reference_prefixes.at(i),
                                     {"_XX_Ep", "_YY_Ep"}, file_ref );
    systematics.back().SetMarkerStyles({
                                           kFullSquare,
                                           kFullTriangleUp,
                                           kFullTriangleDown,
                                           kOpenTriangleUp,
                                           kOpenTriangleDown,
                                           kFullCross,
                                           kFullCrossX,
                                       });
    systematics.back().SetMarkerColors({
                                           kBlue+1,
                                           kRed+1,
                                           kGreen+1,
                                           kRed+1,
                                           kGreen+1,
                                           kMagenta+1,
                                           kCyan+1,
                                       });
    systematics.back().SetLegendPosition(legend_positions.at(i));
    systematics.back().SetAxisTitles("centrality (%)", y_axis_titles.at(i));
    systematics.back().SetCanvas(canvases.back());
    systematics.back().DrawSystematics();
    canvas_name = "Sectors_NC_"+systematics_names.at(i)+"_sub_evt.png";
    canvases.back()->Print(canvas_name.data());
//    systematics.back().SaveToFile(file_out);
    file->Close();
  }
  systematics.clear();
  file_ref->Close();
//  file_out->Close();
  return 0;
}