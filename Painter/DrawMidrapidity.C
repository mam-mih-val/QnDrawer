#include "SetStyle.h"
#include <string>

void DrawMidrapidity(){
  SetStyle();
  enum particles{
    PROTON=0,
    PION_PLUS,
    PION_MINUS
  };
  std::vector<std::string> file_name{
    "../Output_Files/ProtonMr.root",
    "../Output_Files/PionPlusMr.root",
    "../Output_Files/PionMinusMr.root"
  };
  std::vector<std::string> histo_title{
    "Proton",
    "Pion Plus",
    "Pion Minus"
  };
  std::vector<int> histo_color{kBlue+1, kRed+1, kGreen+1};
  std::vector<int> histo_style{21, 22, 23};
  std::vector<TFile*> file;
  std::vector<TH1F*> histo;
  for(auto name : file_name){
    file.emplace_back( TFile::Open(name.data()) );
  }
  auto stack = new THStack("stack", ";pt, [Gev/c]; v_{1}");
  for( auto f : file ){
    histo.emplace_back( (TH1F*) f->Get("histo_") );
    stack->Add(histo.back());
  }
  for(int i=0; i<histo.size(); i++){
    histo.at(i)->SetTitle( histo_title.at(i).data() );
    histo.at(i)->SetMarkerStyle( histo_style.at(i) );
    histo.at(i)->SetMarkerColor( histo_color.at(i) );
    histo.at(i)->SetLineColor( histo_color.at(i) );
    histo.at(i)->SetMarkerSize( 1.5 );
    histo.at(i)->SetLineWidth( 2 );
  }
  stack->SetMinimum(-0.2);
  stack->SetMaximum(0.15);
  auto text = new TPaveText(0.2, 0.8, 0.82, 0.9, "blNDC");
  text->SetBorderSize(0);
  text->SetFillColor(0);
  text->SetFillStyle(0);
  std::string text_str{ "Centrality [20-30], -0.05<y_{cm}<0.05" };
  text->AddText(text_str.data());

  auto canvas = new TCanvas("canvas", "", 1100, 1000);
  canvas->cd();
  stack->Draw("NOSTACK");
  gPad->BuildLegend();
  text->Draw();
  canvas->Print("Midrapidity.png");
}