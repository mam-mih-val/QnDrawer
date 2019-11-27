//
// Created by mikhail on 26.11.2019.
//
#include <Systematics.h>

int main(){
  auto file_in = TFile::Open("../Output_Files/ProtonFlow.root");
  Systematics three_sub( "Three sub" );
  three_sub.SetRebinProjection([](std::vector<Qn::DataContainer<Qn::Stats>> container){
    container.back() = container.back().Rebin({"0_Pt", 32, 0.2, 1.8});
    return container.back();
  });
  three_sub.GetFlowHelper().SetFile(file_in);
  three_sub.Init("flow_TracksMdcPt_", {"Fw1_Fw2_", "Fw2_Fw3_", "Fw3_Fw1_"}, {"XXX_Sp", "XYY_Sp", "YXY_Sp", "YYX_Sp"});
  auto file_out = TFile::Open("systematics.root", "recreate");
  three_sub.SaveGraphsToFile(file_out);
  file_in->Close();
  file_out->Close();
  return 0;
}