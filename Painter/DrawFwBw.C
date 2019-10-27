#include "SetStyle.h"
#include <string>

void DrawFwBw(std::string file_prefix){
  SetStyle();
  std::string file_path="../Output_Files/";
  std::string fw_name{file_path+file_prefix+"Fw.root"};
  std::string bw_name{file_path+file_prefix+"Bw.root"};
  auto file_fw = TFile::Open(fw_name.data());
  auto file_bw = TFile::Open(bw_name.data());
  if( !file_fw ) {
    return;
  }
  if( !file_bw ) {
    return;
  }
  TH1F *histo_fw, *histo_bw;
  file_fw->GetObject( "histo_", histo_fw );
  file_bw->GetObject( "histo_", histo_bw );
  histo_bw->Scale(-1.0);
  auto stack = new THStack("stack", ";pt, [Gev/c]; v_{1}");
  stack->Add( histo_fw );
  stack->Add( histo_bw );
  stack->SetMinimum(-0.3);
  stack->SetMaximum(0.1);
  histo_fw->SetTitle("0.6 < y_{cm} < 0.7");
  histo_fw->SetMarkerStyle(21);
  histo_fw->SetMarkerSize(1.5);
  histo_fw->SetMarkerColor(kBlue+1);
  histo_fw->SetLineWidth(2);
  histo_fw->SetLineColor(kBlue+1);

  histo_bw->SetTitle("-0.6 > y_{cm} > -0.7 #times -1");
  histo_bw->SetMarkerStyle(22);
  histo_bw->SetMarkerSize(1.5);
  histo_bw->SetMarkerColor(kRed+1);
  histo_bw->SetLineWidth(2);
  histo_bw->SetLineColor(kRed+1);

  auto text = new TPaveText(0.2, 0.8, 0.82, 0.9, "blNDC");
  text->SetBorderSize(0);
  text->SetFillColor(0);
  text->SetFillStyle(0);
  std::string text_str{ file_prefix+"; Centrality [20-30]" };
  text->AddText(text_str.data());

  auto canvas = new TCanvas("canvas", "", 1100, 1000);
  canvas->cd();
  stack->Draw("NOSTACK");
  gPad->BuildLegend();
  text->Draw();
  std::string save_name=file_prefix+".png";
  canvas->Print(save_name.data());
}