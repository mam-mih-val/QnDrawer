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
  std::vector<std::string> systematics_names{ "Fw1", "Fw2", "Fw3" };
  std::string prefix{"flow_TracksMdcPt_"};
  std::vector<std::vector<std::string>> sub_events_names{
      {"Fw1_MdcFw_MdcBw_", "Fw1_MdcFw_Fw2_", "Fw1_MdcFw_Fw3_", "Fw1_MdcBw_Fw2_", "Fw1_MdcBw_Fw3_"},
      {"Fw2_MdcFw_MdcBw_", "Fw2_MdcFw_Fw1_", "Fw2_MdcFw_Fw3_", "Fw2_MdcBw_Fw1_", "Fw2_MdcBw_Fw3_"},
      {"Fw3_MdcFw_MdcBw_", "Fw3_MdcFw_Fw1_", "Fw3_MdcFw_Fw2_", "Fw3_MdcBw_Fw1_", "Fw3_MdcBw_Fw2_"}
  };
  std::vector<std::vector<std::string>> components_names{
      {"_XX_Sp", "_YY_Sp"},
      {"_XX_Sp", "_YY_Sp"},
      {"_XX_Sp", "_YY_Sp"}
  };
  auto file_compare = TFile::Open("~/Painter/Mdc3S_GoodTrigger_pt.root");
  TGraphErrors* graph;
  file_compare->GetObject("Mdc_averaged", graph);
  std::vector<TCanvas*> canvases;
  auto file_name = file_out_name+".root";
  auto file_out = TFile::Open(file_name.data(), "recreate");
  for( int i=0; i<systematics_names.size(); i++ ){
    systematics.emplace_back(systematics_names.at(i));
    systematics.back().SetRebinProjection([](std::vector<Qn::DataContainer<Qn::Stats>> container){
//      container.back() = container.back().Rebin({"0_Pt", 32, 0.2, 1.8});
      return container.back();
    });
    systematics.back().GetFlowHelper().SetFile(file_in);
    systematics.back().Init(prefix, sub_events_names.at(i), components_names.at(i));
    std::string canvas_name{systematics_names.at(i)+"_comp"};
    canvases.push_back( new TCanvas(canvas_name.data(), "", 600, 1000) );
    systematics.back().SetCompareGraph(graph);
    systematics.back().DrawSubEvents(canvases.back());
    canvas_name = file_out_name+"_"+systematics_names.at(i)+"_sub_evt.png";
    canvases.back()->Print(canvas_name.data());
    systematics.back().SaveToFile(file_out);
  }
  systematics.clear();
  file_in->Close();
  file_out->Close();
  return 0;
}