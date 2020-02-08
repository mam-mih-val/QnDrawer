//
// Created by mikhail on 26.11.2019.
//
#include <Comparator.h>
#include <Systematics.h>

int main(int n_args, char** args){
  std::string file_in_name = args[1];
  std::string file_out_name = args[2];
  auto file_in = TFile::Open(file_in_name.data());
  std::vector<Systematics> systematics;
  std::vector<std::string> systematics_names{ "FWs1,FWs2", "FWs1,FWs3", "FWs2,FWs3" };
  std::string prefix{"flow_"};
  std::vector<std::vector<std::string>> sub_events_names{
      {"FWs1(MDCf,MDCb)_FWs2(MDCf,MDCb)", "FWs1(MDCf,FWs2)_FWs2(MDCf,FWs1)", "FWs1(MDCf,FWs3)_FWs2(MDCf,FWs3)", "FWs1(MDCb,FWs2)_FWs2(MDCb,FWs1)", "FWs1(MDCb,FWs3)_FWs2(MDCb,FWs3)", "FWs1(FWs2,FWs3)_FWs2(FWs1,FWs3)"},
      {"FWs1(MDCf,MDCb)_FWs3(MDCf,MDCb)", "FWs1(MDCb,FWs3)_FWs3(MDCb,FWs1)", "FWs1(MDCf,FWs2)_FWs3(MDCf,FWs2)", "FWs1(MDCb,FWs3)_FWs3(MDCb,FWs1)", "FWs1(MDCb,FWs2)_FWs3(MDCb,FWs2)", "FWs1(FWs2,FWs3)_FWs3(FWs1,FWs2)"},
      {"FWs2(MDCf,MDCb)_FWs3(MDCf,MDCb)", "FWs2(MDCf,FWs3)_FWs3(MDCf,FWs2)", "FWs2(MDCf,FWs3)_FWs3(MDCf,FWs2)", "FWs2(MDCb,FWs3)_FWs3(MDCb,FWs2)", "FWs2(MDCb,FWs1)_FWs3(MDCb,FWs1)", "FWs2(FWs1,FWs3)_FWs3(FWs1,FWs2)"}
  };
  std::vector<std::vector<std::string>> sub_events_titles{
      {"FWs1,FWs2(MDCf,MDCb)", "FWs1,FWs2(MDCf)", "FWs1,FWs2(MDCf,FWs3)", "FWs1,FWs2(MDCb)", "FWs1,FWs2(MDCb,FWs3)", "FWs1,FWs2(FWs3)"},
      {"FWs1,FWs3(MDCf,MDCb)", "FWs1,FWs3(MDCf)", "FWs1,FWs3(MDCf,FWs2)", "FWs1,FWs3(MDCb)", "FWs1,FWs3(MDCb,FWs2)", "FWs1,FWs3(FWs2)"},
      {"FWs2,FWs3(MDCf,MDCb)", "FWs2,FWs3(MDCf)", "FWs2,FWs3(MDCf,FWs1)", "FWs2,FWs3(MDCb)", "FWs2,FWs3(MDCb,FWs1)", "FWs2,FWs3(FWs1)"}
  };
  std::vector<std::vector<std::string>> components_names{
      {"_XXX_Sp", "_XYY_Sp", "_YXY_Sp", "_YYX_Sp"},
      {"_XXX_Sp", "_XYY_Sp", "_YXY_Sp", "_YYX_Sp"},
      {"_XXX_Sp", "_XYY_Sp", "_YXY_Sp", "_YYX_Sp"}
  };
  Systematics default_value("FW-elliptic");
  default_value.GetFlowHelper().SetFile(file_in);
  default_value.Init(prefix, {"FWs1(FWs2,FWs3)_FWs2(FWs1,FWs3)",
                              "FWs1(FWs2,FWs3)_FWs3(FWs1,FWs2)",
                              "FWs2(FWs1,FWs3)_FWs3(FWs1,FWs2)"},
                              {"_XXX_Sp", "_XYY_Sp", "_YXY_Sp", "_YYX_Sp"});
  std::vector<TCanvas*> canvases;
  auto file_name = file_out_name+".root";
  auto file_out = TFile::Open(file_name.data(), "recreate");
  for( size_t i=0; i<systematics_names.size(); i++ ){
    systematics.emplace_back(systematics_names.at(i));
    systematics.back().SetRebinProjection([](std::vector<Qn::DataContainer<Qn::Stats>> container){
//      container.back() = container.back().Rebin({"0_Pt", 32, 0.2, 1.8});
      return container.back();
    });
    systematics.back().SetResultPlotRange({-0.139, -0.019});
    systematics.back().SetRatioPlotRange({0.51, 1.49});
    systematics.back().GetFlowHelper().SetFile(file_in);
    systematics.back().Init(prefix, sub_events_names.at(i), components_names.at(i));
    std::string canvas_name{systematics_names.at(i)+"_comp"};
    canvases.push_back( new TCanvas(canvas_name.data(), "", 600, 1000) );
    systematics.back().SetDefault( default_value.GetAveraged() );
    systematics.back().SetSubEventsNames(sub_events_titles.at(i));
    systematics.back().SetMarkerStyles({
      kFullSquare,
      kFullTriangleUp,
      kFullTriangleDown,
      kOpenTriangleUp,
      kOpenTriangleDown,
      kFullCross
    });
    systematics.back().SetMarkerColors({
      kBlue+1,
      kRed+1,
      kGreen+1,
      kRed+1,
      kGreen+1,
      kMagenta+1
    });
    systematics.back().SetAxisTitles("centrality (%)", "v_{2}");
    systematics.back().DrawSubEvents(canvases.back());
    canvas_name = file_out_name+"_"+systematics_names.at(i)+"_sub_evt.pdf";
    canvases.back()->Print(canvas_name.data());
    systematics.back().SaveToFile(file_out);
  }
  systematics.clear();
  file_in->Close();
  file_out->Close();
  return 0;
}