#include "SetStyle.h"

void DrawFwBw(){
  SetStyle();
  auto file_fw = TFile::Open("../Output_Files/PionPlusFw.root");
  auto file_bw = TFile::Open("../Output_Files/PionPlusBw.root");
  if( !file_fw ) {
    return;
  }
  if( !file_bw ) {
    return;
  }
  TH1F *histo_fw, *histo_bw;
  file_fw->GetObject( "histo_", histo_fw );
  histo_fw->Scale(-1.0);
  file_bw->GetObject( "histo_", histo_bw );
  auto stack = new THStack("stack", ";pt, [Gev/c]; v_{1}");
  stack->Add( histo_fw );
  stack->Add( histo_bw );
  stack->SetMinimum(-0.1);
  stack->SetMaximum(0.2);
  histo_fw->SetTitle("forward rapidity");
  histo_fw->SetMarkerStyle(21);
  histo_fw->SetMarkerSize(1.5);
  histo_fw->SetMarkerColor(kBlue+1);
  histo_fw->SetLineWidth(2);
  histo_fw->SetLineColor(kBlue+1);

  histo_bw->SetTitle("backward rapidity");
  histo_bw->SetMarkerStyle(22);
  histo_bw->SetMarkerSize(1.5);
  histo_bw->SetMarkerColor(kRed+1);
  histo_bw->SetLineWidth(2);
  histo_bw->SetLineColor(kRed+1);

  auto canvas = new TCanvas("canvas", "", 1100, 1000);
  canvas->cd();
  stack->Draw("NOSTACK");
  gPad->BuildLegend();
  canvas->Print("PionPlus.png");
}