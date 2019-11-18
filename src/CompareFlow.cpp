//
// Created by mikhail on 12.11.2019.
//

#include <Comparator.h>
#include <TFile.h>

TGraphErrors* MakeBkGraph();
TH1F* MakeOgHisto();

int main( int n_args, char** args ){
  auto file = TFile::Open( "../Output_Files/ProtonOldCent_80_120.root" );
  std::vector<std::string> names_3se{
    "flow_3Se_0_X",
    "flow_3Se_0_Y",
    "flow_3Se_1_X",
    "flow_3Se_1_Y",
    "flow_3Se_2_X",
    "flow_3Se_2_Y"
  };
  std::vector<std::string> names_rnd{
    "flow_RndSub_0_X",
    "flow_RndSub_0_Y",
    "flow_RndSub_1_X",
    "flow_RndSub_1_Y"
  };
  std::vector<std::string> names_full{
    "flow_FullEvt_0_X",
    "flow_FullEvt_0_Y"
  };
  Comparator comparator;
  comparator.AddFile(file, "old");
  comparator.AddGraph( MakeBkGraph(), "Behruz Kardan QM2018");
  comparator.AddTh1( MakeOgHisto() );
  comparator.MergeAndPutOnCanvas("old", names_3se, "3 sub-event");
  comparator.MergeAndPutOnCanvas("old", names_rnd, "Rnd sub-event");
  comparator.MergeAndPutOnCanvas("old", names_full, "Rnd extrapolation");
  comparator.SetCanvas(new TCanvas("canv", "", 1200, 1000));
  comparator.Draw();
  comparator.GetCanvas()->Print("canv_flow.png");
  return 0;
}

TGraphErrors* MakeBkGraph(){
  Double_t BK_fx1001[35] = {0.2815451,0.3297382,0.3809376,0.4291514,0.4803508,0.5315502,0.5827703,0.6309841,0.6791979,0.7304283,0.7816794,0.8299242,0.8811752,0.9324263,0.9806401,1.028885,1.080146,1.131418,1.179652,1.227856,1.279179,1.330348,1.378603,1.42691,1.47813,1.529453,1.580714,1.628908,1.680159,1.731244,1.779696,1.827786,1.879026,1.929978,1.978605};
  Double_t BK_fy1001[35] = {-0.08407534,-0.09246575,-0.1020548,-0.1080479,-0.117637,-0.127226,-0.1344178,-0.140411,-0.1464041,-0.1523973,-0.1559931,-0.1583904,-0.1619863,-0.1655822,-0.1715753,-0.1739726,-0.1763699,-0.1775685,-0.1811644,-0.1883562,-0.1835616,-0.1967466,-0.1979452,-0.1931507,-0.2003425,-0.1955479,-0.1979452,-0.2063356,-0.2099315,-0.2327055,-0.2111301,-0.2315069,-0.2363014,-0.2746575,-0.2327055};
  Double_t BK_fex1001[35] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
  Double_t BK_fey1001[35] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0.00479452,0.007191781,0.008390411,0.009589041,0.01078767,0.01318493,0.01438356,0.01797945,0.01917808,0.0239726,0.03116438};

  auto *gre = new TGraphErrors(35, BK_fx1001, BK_fy1001, BK_fex1001, BK_fey1001);
  gre->SetMarkerStyle(20);
  return gre;
}

TH1F* MakeOgHisto(){
  TH1F *hV1cPtCent_EP__4 = new TH1F("hV1cPtCent_EP__4", "V_{1} (p_{T}) (no_weight, MDC3S)", 19, 0.09, 1.99);
  hV1cPtCent_EP__4->SetBinContent(1, 0.07123203);
  hV1cPtCent_EP__4->SetBinContent(2, 0.07448349);
  hV1cPtCent_EP__4->SetBinContent(3, 0.07994775);
  hV1cPtCent_EP__4->SetBinContent(4, 0.09119512);
  hV1cPtCent_EP__4->SetBinContent(5, 0.104499);
  hV1cPtCent_EP__4->SetBinContent(6, 0.1142554);
  hV1cPtCent_EP__4->SetBinContent(7, 0.1221631);
  hV1cPtCent_EP__4->SetBinContent(8, 0.1300836);
  hV1cPtCent_EP__4->SetBinContent(9, 0.1349282);
  hV1cPtCent_EP__4->SetBinContent(10, 0.1435793);
  hV1cPtCent_EP__4->SetBinContent(11, 0.1459274);
  hV1cPtCent_EP__4->SetBinContent(12, 0.1527939);
  hV1cPtCent_EP__4->SetBinContent(13, 0.1526);
  hV1cPtCent_EP__4->SetBinContent(14, 0.1653417);
  hV1cPtCent_EP__4->SetBinContent(15, 0.1652416);
  hV1cPtCent_EP__4->SetBinContent(16, 0.1767017);
  hV1cPtCent_EP__4->SetBinContent(17, 0.1868607);
  hV1cPtCent_EP__4->SetBinContent(18, 0.1902347);
  hV1cPtCent_EP__4->SetBinContent(19, 0.2012614);
  hV1cPtCent_EP__4->SetBinError(1, 0.002920876);
  hV1cPtCent_EP__4->SetBinError(2, 0.001333387);
  hV1cPtCent_EP__4->SetBinError(3, 0.001143938);
  hV1cPtCent_EP__4->SetBinError(4, 0.001117931);
  hV1cPtCent_EP__4->SetBinError(5, 0.001196258);
  hV1cPtCent_EP__4->SetBinError(6, 0.001333432);
  hV1cPtCent_EP__4->SetBinError(7, 0.001585704);
  hV1cPtCent_EP__4->SetBinError(8, 0.001939541);
  hV1cPtCent_EP__4->SetBinError(9, 0.002441875);
  hV1cPtCent_EP__4->SetBinError(10, 0.003153039);
  hV1cPtCent_EP__4->SetBinError(11, 0.004245421);
  hV1cPtCent_EP__4->SetBinError(12, 0.005838706);
  hV1cPtCent_EP__4->SetBinError(13, 0.008079265);
  hV1cPtCent_EP__4->SetBinError(14, 0.01098048);
  hV1cPtCent_EP__4->SetBinError(15, 0.0152335);
  hV1cPtCent_EP__4->SetBinError(16, 0.02350668);
  hV1cPtCent_EP__4->SetBinError(17, 0.02969512);
  hV1cPtCent_EP__4->SetBinError(18, 0.04676262);
  hV1cPtCent_EP__4->SetBinError(19, 0.2403557);
  hV1cPtCent_EP__4->SetEntries(109.4879);
  hV1cPtCent_EP__4->Scale(-1);
  hV1cPtCent_EP__4->SetMarkerStyle(29);
  hV1cPtCent_EP__4->SetMarkerSize(2.5);
  hV1cPtCent_EP__4->SetLineWidth(2.0);
  hV1cPtCent_EP__4->SetMarkerColor(kBlue+2);
  hV1cPtCent_EP__4->SetLineColor(kBlue+2);
  return hV1cPtCent_EP__4;
}