//
// Created by mikhail on 14.11.2019.
//
#include <TFile.h>
#include <comparator.h>

TGraphErrors*MakeBkGraphV1();
TH1F* MakeOgHisto();

int main( int n_args, char** args ){
  auto file = TFile::Open( "../Output_Files/ProtonOldCent_NotUnit.root" );
  std::vector<std::string> names_3se{
      "resolution_3Se_0_X",
      "resolution_3Se_0_Y",
      "resolution_3Se_1_X",
      "resolution_3Se_1_Y",
      "resolution_3Se_2_X",
      "resolution_3Se_2_Y"
  };
  std::vector<std::string> names_full{
      "resolution_FullEvt_0_X",
      "resolution_FullEvt_0_Y"
  };
  Comparator comparator;
  comparator.AddFile(file, "old");
  comparator.AddGraph(MakeBkGraphV1(), "Behruz Kardan QM2018");
  comparator.AddTh1( MakeOgHisto() );
  comparator.MergeAndPutOnCanvas("old", names_3se, "3 sub-event");
  comparator.MergeAndPutOnCanvas("old", names_full, "Rnd extrapolation");
  comparator.SetCanvas(new TCanvas("canv", "", 1200, 1000));
  comparator.Draw();
  comparator.GetCanvas()->Print("canv_reso.root");
  return 0;
}

TGraphErrors*MakeBkGraphV1(){
  Double_t R_BK_fx1001[4] = {5,15,25,35};
  Double_t R_BK_fy1001[4] = {0.608403,0.815295,0.859224,0.850258};
  Double_t R_BK_fex1001[4] = {0,0,0,0};
  Double_t R_BK_fey1001[4] = {0,0,0,0};
  TGraphErrors *greRes = new TGraphErrors(4,R_BK_fx1001,R_BK_fy1001,R_BK_fex1001,R_BK_fey1001);
  greRes->SetName("R_BK");
  greRes->SetTitle("RS extrapolation (BK)");
  greRes->SetMarkerStyle(20);
  return greRes;
}

TH1F* MakeOgHisto(){
  TH1F *hR1cCent_EP__4 = new TH1F("hR1cCent_EP__4","3Sub [protons] Code (OG)",10,0.375,50.375);
  hR1cCent_EP__4->SetBinContent(1,0.4301135);
  hR1cCent_EP__4->SetBinContent(2,0.6435736);
  hR1cCent_EP__4->SetBinContent(3,0.7657897);
  hR1cCent_EP__4->SetBinContent(4,0.8216761);
  hR1cCent_EP__4->SetBinContent(5,0.8446975);
  hR1cCent_EP__4->SetBinContent(6,0.8542153);
  hR1cCent_EP__4->SetBinContent(7,0.8488179);
  hR1cCent_EP__4->SetBinContent(8,0.8288646);
  hR1cCent_EP__4->SetBinContent(9,0.7856925);
  hR1cCent_EP__4->SetBinContent(10,0.6739708);
  hR1cCent_EP__4->SetBinError(1,0.002065585);
  hR1cCent_EP__4->SetBinError(2,0.001763485);
  hR1cCent_EP__4->SetBinError(3,0.001745763);
  hR1cCent_EP__4->SetBinError(4,0.001795579);
  hR1cCent_EP__4->SetBinError(5,0.001956967);
  hR1cCent_EP__4->SetBinError(6,0.002163557);
  hR1cCent_EP__4->SetBinError(7,0.002539424);
  hR1cCent_EP__4->SetBinError(8,0.002930148);
  hR1cCent_EP__4->SetBinError(9,0.003796161);
  hR1cCent_EP__4->SetBinError(10,0.01607744);
  hR1cCent_EP__4->SetEntries(181274.8);
  hR1cCent_EP__4->SetDirectory(0);
  hR1cCent_EP__4->SetMarkerStyle(34);
  hR1cCent_EP__4->SetMarkerSize(3);
  hR1cCent_EP__4->SetMarkerColor(kMagenta+2);
  hR1cCent_EP__4->SetLineColor(kMagenta+2);
  return hR1cCent_EP__4;
}
