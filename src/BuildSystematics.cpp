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
  std::vector<std::string> systematics_names{ "Three_Sub", "Extrapolation" ,"Rnd_Sub", "Elliptic", "Triangular", "Mdc"};
  std::string prefix{"flow_TracksMdcPt_"};
  std::vector<std::vector<std::string>> sub_events_names{
      {"Fw1_", "Fw2_", "Fw3_"},
      {"Full_"},
      {"Rs1_", "Rs2_"},
      {"Fw1_Fw2_", "Fw2_Fw3_", "Fw3_Fw1_"},
      {"Fw1_Fw2_Fw3_"},
      {"Full_3mdc_"}
  };
  std::vector<std::vector<std::string>> components_names{
      {"XX_Sp", "YY_Sp"},
      {"XX_Ep", "YY_Ep"},
      {"XX_Ep", "YY_Ep"},
      {"XXX_Sp", "XYY_Sp", "YXY_Sp", "YYX_Sp"},
      {"XXXX_Sp", "XYYX_Sp", "XYXY_Sp", "XXYY_Sp", "YYXX_Sp", "YXYX_Sp", "YXXY_Sp", "YYYY_Sp"},
      {"XX_Ep", "YY_Ep"}
  };
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