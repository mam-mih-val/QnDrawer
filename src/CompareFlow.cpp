//
// Created by mikhail on 12.11.2019.
//

#include <Comparator.h>
#include <vector>
#include <TFile.h>

TGraphErrors*MakeBkGraphV1();
TGraphErrors* MakeBkGraphV2();
TGraphErrors* MakeBkGraphV3();
TH1F* MakeOgHisto();
Comparator Compare3Se(TFile* file);
Comparator CompareRs(TFile* file);
Comparator CompareElliptic(TFile* file);
Comparator CompareTriangular(TFile* file);

int main( int n_args, char** args ){
  std::string input_file_name=args[1];
  std::string output_file_name=args[2];
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
  comparators.push_back( Compare3Se(file) );
  comparators.push_back( CompareRs(file) );
  comparators.push_back( CompareElliptic(file) );
//  comparators.push_back( CompareTriangular(file) );
  std::vector<std::vector<float>> canv_edges{
    {-0.4, 0.1},
    {-0.4, 0.1},
    {-0.4, 0.1},
    {0.0, 0.1}
  };
  int i=0;
  for(auto comparator: comparators){
    std::string canvas_name = "canv"+std::to_string(i);
    comparator.SetCanvas(new TCanvas(canvas_name.data(), "", 1100, 1000));
    comparator.Draw();
    comparator.GetGraphs()->SetMinimum(canv_edges.at(i).at(0));
    comparator.GetGraphs()->SetMaximum(canv_edges.at(i).at(1));
    std::string save_name = output_file_name+std::to_string(i)+".png";
    comparator.GetCanvas()->Print(save_name.data());
    i++;
  }
  file->Close();
  return 0;
}

Comparator Compare3Se(TFile* file){
  Comparator comparator("Three Sub");
  comparator.AddFile(file, "old");
  std::vector<std::string> axis_names{"Pt", "Ycm"};
  std::vector<std::string> sub_events{"Fw1", "Fw2", "Fw3"};
  std::vector<std::string> components{"_XX", "_YY"};
  std::vector<std::string> methods{"_Sp", "_Ep"};
  std::vector<std::string> three_sub;
  // ******************************** Method of 3 Sub-Events ******************************** //
  for( auto se : sub_events ){
    for( auto component : components ){
      three_sub.push_back("flow_TracksMdcPt_"+se+component+"_Sp");
    }
  }
  comparator.MergeAndPutOnCanvas("old", three_sub, "Three SE");
  comparator.PutOnCanvas("old", three_sub, three_sub);
  comparator.AddGraph(MakeBkGraphV1(), "Behruz Kardan HADES CM2019");
  return comparator;
}
Comparator CompareRs(TFile* file){
  Comparator comparator("Three Sub");
  comparator.AddFile(file, "old");
  std::vector<std::string> rand_sub;
  std::vector<std::string> extrapolate;
  // ******************************** Random Sub-Event method ******************************** //
  std::vector<std::string> sub_events{ "Rs1", "Rs2" };
  std::vector<std::string> components{"_XX", "_YY"};
  for( auto se : sub_events ){
    for( auto comp : components ){
      rand_sub.push_back( "flow_TracksMdcPt_"+se+comp+"_Sp");
    }
  }
  for (auto comp : components) {
    extrapolate.push_back("flow_TracksMdcPt_Full" + comp + "_Ep");
  }
  comparator.MergeAndPutOnCanvas("old", extrapolate, "Rnd Sub Extrapolation");
  comparator.PutOnCanvas("old", rand_sub, rand_sub);
  comparator.PutOnCanvas("old", extrapolate, extrapolate);
  comparator.AddGraph(MakeBkGraphV1(), "Behruz Kardan HADES CM2019");
  return comparator;
}

Comparator CompareElliptic(TFile* file){
  Comparator comparator("v2");
  comparator.AddFile(file, "old");
  std::vector<std::string> elliptic;
  // ******************************** Random Sub-Event method ******************************** //
  std::vector<std::string> sub_events = { "Fw1_Fw2", "Fw3_Fw1", "Fw2_Fw3" };
  std::vector<std::string> un_qn_components = {"_XXX", "_XYY", "_YXY", "_YYX"};
  for( auto se : sub_events ){
    for( int i=0; i<un_qn_components.size(); i++ ){
      elliptic.push_back( "flow_TracksMdcPt_"+se+un_qn_components.at(i)+"_Sp" );
    }
  }
  comparator.MergeAndPutOnCanvas("old", elliptic, "Default");
  comparator.AddGraph( MakeBkGraphV2(), "Behruz Kardan HADES CM2019");
  return comparator;
}

Comparator CompareTriangular(TFile* file){
  Comparator comparator("v3");
  comparator.AddFile(file, "old");
  std::vector<std::string> triangular;
  // ******************************** Random Sub-Event method ******************************** //
  std::vector<std::string> sub_events = { "Fw1_Fw2_Fw3" };
  std::vector<std::string> un_qn_components = {"_XXXX", "_XYYX", "_XYXY", "_XXYY", "_YYXX", "_YXYX", "_YXXY", "_YYYY"};
  for( auto se : sub_events ){
    for( int i=0; i<un_qn_components.size(); i++ ){
      triangular.push_back( "flow_TracksMdcPt_"+se+un_qn_components.at(i)+"_Sp" );
    }
  }
  comparator.MergeAndPutOnCanvas("old", triangular, "Default");
  comparator.AddGraph( MakeBkGraphV3(), "Behruz Kardan HADES CM2019");
  return comparator;
}

TGraphErrors* MakeBkGraphV2(){
  Double_t BK_fx1001[35] = {0.17666636089962234,0.2254350926057191,0.27623022590625196,0.3270478747800563,0.37578658572179097,0.4245328018546162,0.4753054195818775,0.5260555217358673,0.5747717171043305,0.6255068088761395,0.6762343954568577,0.7249355804431399,0.7756706722149489,0.8263982587956671,0.8750994437819495,0.925834535553758,0.9765771325166577,1.0252933278851206,1.074009523253584,1.1247821409808452,1.175547253517016,1.2263348816264585,1.2750886029503743,1.3258762310598164,1.3746299523837322,1.4254476012575368,1.4741938173903617,1.5250489922196189,1.5758441255201516,1.6246578883727911,1.6754530216733248,1.724266784525964,1.775166990501764,1.8258870718913915,1.8748134126103893};
  Double_t BK_fy1001[35] = {-0.013581060233328113,-0.017989109133817627,-0.023134334581418836,-0.026065528657321313,-0.033425619386742544,-0.04004769965893079,-0.047406956478230844,-0.05698024466922952,-0.0665543667703496,-0.07760367587581413,-0.08939099543851164,-0.10044113845409747,-0.11149044755956211,-0.12327776712225952,-0.13432791013784545,-0.14537721924330999,-0.15568851789154176,-0.1652626399926615,-0.17483676209378157,-0.18219601891308163,-0.19029328618961455,-0.19617652209444875,-0.202060591909404,-0.2079438278142382,-0.21382789762919358,-0.21675909170509605,-0.2233811719772843,-0.22262231376702218,-0.2277675392146235,-0.22774752537171555,-0.23289275081931665,-0.2328727369764087,-0.22768581602274912,-0.24021114604267962,-0.22912097534127768};
  Double_t BK_fex1001[35] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
  Double_t BK_fey1001[35] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0.00479452,0.007191781,0.008390411,0.009589041,0.01078767,0.01318493,0.01438356,0.01797945,0.01917808,0.0239726,0.03116438};

  auto *gre = new TGraphErrors(35, BK_fx1001, BK_fy1001, BK_fex1001, BK_fey1001);
  gre->SetMarkerStyle(20);
  return gre;
}

TGraphErrors* MakeBkGraphV3(){
  Double_t BK_fx1001[35] = {0.17418498504278107,0.2229181426170404,0.27359548977218234,0.3223346202791018,0.37302689976589426,0.42371619278635647,0.4724493503606159,0.5231386433810781,0.5738219634688804,0.6245022970903524,0.6732264952656215,0.7239068288870936,0.7745811895759054,0.8233053877511742,0.8739767619736563,0.924645149729808,0.9733723343714074,1.024040722127559,1.0747091098837107,1.12344226745797,1.1741046822814614,1.224796961768254,1.2735092140782025,1.3222274393208115,1.3748549489894963,1.423600052429076,1.474283372516878,1.5229986112931568,1.5736580396503184,1.622400156623568,1.6730356932500887,1.723730959203211,1.7743903875603728,1.823090694005001,1.8739352832746274};
  Double_t BK_fy1001[35] = {-0.00245022970903519,-0.000306278713629371,0.00245022970903519,0.003981623277182267,0.005206738131699862,0.006738131699846883,0.008882082695252647,0.010413476263399724,0.012557427258805487,0.015007656967840732,0.018070444104134775,0.02052067381317002,0.023583460949464063,0.02664624808575805,0.03001531393568152,0.033690658499234305,0.03644716692189895,0.04012251148545179,0.0437978560490046,0.04594180704441045,0.05022970903522203,0.051454823889739654,0.05574272588055132,0.05941807044410416,0.06217457886676875,0.063093415007657,0.06523736600306279,0.06921898928024503,0.0738131699846861,0.07503828483920366,0.08208269525267997,0.08300153139356817,0.0875957120980092,0.09310872894333846,0.0787136294027565};
  Double_t BK_fex1001[35] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
  Double_t BK_fey1001[35] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0.00479452,0.007191781,0.008390411,0.009589041,0.01078767,0.01318493,0.01438356,0.01797945,0.01917808,0.0239726,0.03116438};

  auto *gre = new TGraphErrors(35, BK_fx1001, BK_fy1001, BK_fex1001, BK_fey1001);
  gre->SetMarkerStyle(20);
  return gre;
}

TGraphErrors*MakeBkGraphV1(){
  Double_t BK_fx1001[35] = {0.1741150442477875,0.22389380530973452,0.2736725663716814,0.3254424778761061,0.3752212389380531,0.4249999999999999,0.4747787610619469,0.5245575221238938,0.5763274336283184,0.6241150442477876,0.6738938053097345,0.7236725663716814,0.7754424778761062,0.8252212389380531,0.875,0.9247787610619471,0.9745575221238938,1.0243362831858407,1.0761061946902655,1.1238938053097347,1.1736725663716814,1.2234513274336283,1.2752212389380533,1.3250000000000002,1.374778761061947,1.4245575221238937,1.4743362831858409,1.5241150442477878,1.5738938053097347,1.6256637168141592,1.6734513274336287,1.7252212389380532,1.775,1.824778761061947,1.8745575221238941};
  Double_t BK_fy1001[35] = {-0.040000000000000036,-0.05529411764705883,-0.07176470588235295,-0.08588235294117641,-0.09647058823529409,-0.10705882352941176,-0.1164705882352941,-0.12470588235294111,-0.13294117647058823,-0.13882352941176468,-0.1435294117647059,-0.14823529411764702,-0.1517647058823529,-0.15647058823529414,-0.1588235294117647,-0.1623529411764706,-0.16588235294117648,-0.16941176470588237,-0.17176470588235293,-0.17294117647058826,-0.17647058823529416,-0.1776470588235295,-0.18117647058823527,-0.18352941176470594,-0.18470588235294105,-0.18823529411764706,-0.1894117647058824,-0.19529411764705873,-0.19882352941176473,-0.20235294117647062,-0.20823529411764707,-0.21058823529411763,-0.21882352941176475,-0.21529411764705886,-0.22941176470588243};
  Double_t BK_fex1001[35] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
  Double_t BK_fey1001[35] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0.00479452,0.007191781,0.008390411,0.009589041,0.01078767,0.01318493,0.01438356,0.01797945,0.01917808,0.0239726,0.03116438};
  auto *gre = new TGraphErrors(35, BK_fx1001, BK_fy1001, BK_fex1001, BK_fey1001);
  gre->SetMarkerStyle(20);
  gre->SetMarkerColor(kBlack);
  gre->SetLineColor(kBlack);
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