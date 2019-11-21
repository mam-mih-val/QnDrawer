//
// Created by mikhail on 12.11.2019.
//

#include <Comparator.h>
#include <vector>
#include <TFile.h>

TGraphErrors* MakeBkGraph();
TH1F* MakeOgHisto();

int main( int n_args, char** args ){
  std::string input_file_name=args[1];
  auto file = TFile::Open( input_file_name.data() );

  std::vector<std::string> axis_names{"Pt", "Ycm"};
  std::vector<std::string> sub_events{"Fw1", "Fw2", "Fw3"};
  std::vector<std::string> components{"_XX", "_YY"};
  std::vector<std::string> methods{"_Sp", "_Ep"};
  std::vector<std::string> three_sub;
  std::vector<std::string> rand_sub;
  std::vector<std::string> extrapolate;

  // ******************************** Method of 3 Sub-Events ******************************** //
  for( auto se : sub_events ){
    for( auto component : components ){
      three_sub.push_back("flow_TracksMdcPt_"+se+component+"_Sp");
    }
  }
  // ******************************** Random Sub-Event method ******************************** //
  sub_events = { "Rs1", "Rs2" };
  components = {"_XX", "_YY"};
  for( auto se : sub_events ){
    for( auto comp : components ){
      rand_sub.push_back( "flow_TracksMdcPt_"+se+comp+"_Sp");
    }
  }
  for (auto comp : components) {
    extrapolate.push_back("flow_TracksMdcPt_Full" + comp + "_Ep");
  }
  std::vector<Comparator> comparators;
  comparators.emplace_back();
  comparators.back().AddFile(file, "old");
  comparators.back().MergeAndPutOnCanvas("old", three_sub, "Three SE");
  comparators.back().MergeAndPutOnCanvas("old", rand_sub, "Random SE");
  comparators.back().MergeAndPutOnCanvas("old", extrapolate, "Extrapolation");
  comparators.back().AddGraph( MakeBkGraph(), "Behruz Kardan HADES CM2019");
  comparators.back().AddTh1( MakeOgHisto() );
  comparators.back().SetCanvas(new TCanvas("canv", "", 1200, 1000));
  comparators.back().Draw();
  comparators.back().GetCanvas()->Print("canv_flow.png");
  return 0;
}

TGraphErrors* MakeBkGraph(){
  Double_t BK_fx1001[35] = {0.1741150442477875,0.22389380530973452,0.2736725663716814,0.3254424778761061,0.3752212389380531,0.4249999999999999,0.4747787610619469,0.5245575221238938,0.5763274336283184,0.6241150442477876,0.6738938053097345,0.7236725663716814,0.7754424778761062,0.8252212389380531,0.875,0.9247787610619471,0.9745575221238938,1.0243362831858407,1.0761061946902655,1.1238938053097347,1.1736725663716814,1.2234513274336283,1.2752212389380533,1.3250000000000002,1.374778761061947,1.4245575221238937,1.4743362831858409,1.5241150442477878,1.5738938053097347,1.6256637168141592,1.6734513274336287,1.7252212389380532,1.775,1.824778761061947,1.8745575221238941};
  Double_t BK_fy1001[35] = {-0.040000000000000036,-0.05529411764705883,-0.07176470588235295,-0.08588235294117641,-0.09647058823529409,-0.10705882352941176,-0.1164705882352941,-0.12470588235294111,-0.13294117647058823,-0.13882352941176468,-0.1435294117647059,-0.14823529411764702,-0.1517647058823529,-0.15647058823529414,-0.1588235294117647,-0.1623529411764706,-0.16588235294117648,-0.16941176470588237,-0.17176470588235293,-0.17294117647058826,-0.17647058823529416,-0.1776470588235295,-0.18117647058823527,-0.18352941176470594,-0.18470588235294105,-0.18823529411764706,-0.1894117647058824,-0.19529411764705873,-0.19882352941176473,-0.20235294117647062,-0.20823529411764707,-0.21058823529411763,-0.21882352941176475,-0.21529411764705886,-0.22941176470588243};
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