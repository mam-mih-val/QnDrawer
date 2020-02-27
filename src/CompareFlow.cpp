//
// Created by mikhail on 12.11.2019.
//

#include <Comparator.h>
#include <TFile.h>
#include <TH2D.h>
#include <vector>

int main( int n_args, char** args ){
  std::string input_file_name=args[1];
  std::string output_file_name=args[2];
  auto file_in = new TFile(input_file_name.data());
  TH1D *v1_y__1 = new TH1D("v1_y__1","B.Kardan",40,0,2.000);
  v1_y__1->SetBinContent(5,-0.056689);
  v1_y__1->SetBinContent(6,-0.0724462);
  v1_y__1->SetBinContent(7,-0.0857622);
  v1_y__1->SetBinContent(8,-0.0974916);
  v1_y__1->SetBinContent(9,-0.107819);
  v1_y__1->SetBinContent(10,-0.117258);
  v1_y__1->SetBinContent(11,-0.125603);
  v1_y__1->SetBinContent(12,-0.133623);
  v1_y__1->SetBinContent(13,-0.13969);
  v1_y__1->SetBinContent(14,-0.144322);
  v1_y__1->SetBinContent(15,-0.148571);
  v1_y__1->SetBinContent(16,-0.152733);
  v1_y__1->SetBinContent(17,-0.156673);
  v1_y__1->SetBinContent(18,-0.159905);
  v1_y__1->SetBinContent(19,-0.163119);
  v1_y__1->SetBinContent(20,-0.166127);
  v1_y__1->SetBinContent(21,-0.168766);
  v1_y__1->SetBinContent(22,-0.171514);
  v1_y__1->SetBinContent(23,-0.173814);
  v1_y__1->SetBinContent(24,-0.176317);
  v1_y__1->SetBinContent(25,-0.178319);
  v1_y__1->SetBinContent(26,-0.181242);
  v1_y__1->SetBinContent(27,-0.183801);
  v1_y__1->SetBinContent(28,-0.185713);
  v1_y__1->SetBinContent(29,-0.188883);
  v1_y__1->SetBinContent(30,-0.190504);
  v1_y__1->SetBinContent(31,-0.196477);
  v1_y__1->SetBinContent(32,-0.198697);
  v1_y__1->SetBinContent(33,-0.202736);
  v1_y__1->SetBinContent(34,-0.209534);
  v1_y__1->SetBinContent(35,-0.210355);
  v1_y__1->SetBinContent(36,-0.218307);
  v1_y__1->SetBinContent(37,-0.214754);
  v1_y__1->SetBinContent(38,-0.228763);
  v1_y__1->SetBinError(5,0.000100112);
  v1_y__1->SetBinError(6,9.00023e-05);
  v1_y__1->SetBinError(7,8.56353e-05);
  v1_y__1->SetBinError(8,8.36696e-05);
  v1_y__1->SetBinError(9,8.33004e-05);
  v1_y__1->SetBinError(10,8.43943e-05);
  v1_y__1->SetBinError(11,8.68007e-05);
  v1_y__1->SetBinError(12,9.0422e-05);
  v1_y__1->SetBinError(13,9.5733e-05);
  v1_y__1->SetBinError(14,0.000103389);
  v1_y__1->SetBinError(15,0.000112835);
  v1_y__1->SetBinError(16,0.000124382);
  v1_y__1->SetBinError(17,0.000138099);
  v1_y__1->SetBinError(18,0.000154591);
  v1_y__1->SetBinError(19,0.000174109);
  v1_y__1->SetBinError(20,0.000197741);
  v1_y__1->SetBinError(21,0.00022648);
  v1_y__1->SetBinError(22,0.00026123);
  v1_y__1->SetBinError(23,0.000303788);
  v1_y__1->SetBinError(24,0.000355307);
  v1_y__1->SetBinError(25,0.000417879);
  v1_y__1->SetBinError(26,0.000493254);
  v1_y__1->SetBinError(27,0.000583958);
  v1_y__1->SetBinError(28,0.000693991);
  v1_y__1->SetBinError(29,0.000828552);
  v1_y__1->SetBinError(30,0.000989711);
  v1_y__1->SetBinError(31,0.00118674);
  v1_y__1->SetBinError(32,0.0014243);
  v1_y__1->SetBinError(33,0.00171553);
  v1_y__1->SetBinError(34,0.00206693);
  v1_y__1->SetBinError(35,0.00249372);
  v1_y__1->SetBinError(36,0.00299973);
  v1_y__1->SetBinError(37,0.00363269);
  v1_y__1->SetBinError(38,0.00453434);
  v1_y__1->SetEntries(480554);

  Comparator directed("directed");
  directed.SetRebinProjection([](Qn::DataContainer<Qn::Stats> container){
    container = container.Rebin({"Centrality", 1, 20.0, 30.0});
    container = container.Rebin({"0_Ycm", 1, -0.25, -0.15});
    container = container.Projection({"0_Pt"});
    return container;
  });
  directed.SetLegendPosition({0.16, 0.11, 0.5, 0.4});
  directed.SetXAxisTitle("pt, [GeV/c]");
  directed.SetYAxisTitle("v_{1}");
  directed.AddFile(file_in, "fw3s");
  directed.MergeAddContainers("fw3s", {"flow_RND_XX_Ep",
                                        "flow_RND_YY_Ep"}, "RND Extrapolation", {kFullSquare, kRed});
  directed.MergeAddContainers("fw3s", {"flow_RND_NE1_XX_Ep",
                                        "flow_RND_NE1_YY_Ep"}, "RND No Extrapolation", {kOpenSquare, kRed});
  directed.AddTh1((TH1*)v1_y__1, {kFullCircle, kBlack});
  auto canvas_v1 = new TCanvas("canv", "", 1000, 1100);
  directed.SetCanvas(canvas_v1);
  directed.Draw();
  canvas_v1->Print("someshit.png");

  TH1D *v2_y__1 = new TH1D("v2_y__1","B. Kardan",40,0,2.000);
  v2_y__1->SetBinContent(5,-0.0189053);
  v2_y__1->SetBinContent(6,-0.0233687);
  v2_y__1->SetBinContent(7,-0.0279571);
  v2_y__1->SetBinContent(8,-0.0335884);
  v2_y__1->SetBinContent(9,-0.0406461);
  v2_y__1->SetBinContent(10,-0.0486808);
  v2_y__1->SetBinContent(11,-0.057656);
  v2_y__1->SetBinContent(12,-0.0678197);
  v2_y__1->SetBinContent(13,-0.0788776);
  v2_y__1->SetBinContent(14,-0.090098);
  v2_y__1->SetBinContent(15,-0.101583);
  v2_y__1->SetBinContent(16,-0.11268);
  v2_y__1->SetBinContent(17,-0.124154);
  v2_y__1->SetBinContent(18,-0.135397);
  v2_y__1->SetBinContent(19,-0.145976);
  v2_y__1->SetBinContent(20,-0.156573);
  v2_y__1->SetBinContent(21,-0.166349);
  v2_y__1->SetBinContent(22,-0.17573);
  v2_y__1->SetBinContent(23,-0.183076);
  v2_y__1->SetBinContent(24,-0.191517);
  v2_y__1->SetBinContent(25,-0.19774);
  v2_y__1->SetBinContent(26,-0.203159);
  v2_y__1->SetBinContent(27,-0.209011);
  v2_y__1->SetBinContent(28,-0.215316);
  v2_y__1->SetBinContent(29,-0.217934);
  v2_y__1->SetBinContent(30,-0.22476);
  v2_y__1->SetBinContent(31,-0.22394);
  v2_y__1->SetBinContent(32,-0.229186);
  v2_y__1->SetBinContent(33,-0.229121);
  v2_y__1->SetBinContent(34,-0.23456);
  v2_y__1->SetBinContent(35,-0.233714);
  v2_y__1->SetBinContent(36,-0.229067);
  v2_y__1->SetBinContent(37,-0.241356);
  v2_y__1->SetBinContent(38,-0.230453);
  v2_y__1->SetBinError(5,0.000138031);
  v2_y__1->SetBinError(6,0.00012447);
  v2_y__1->SetBinError(7,0.000118806);
  v2_y__1->SetBinError(8,0.000116496);
  v2_y__1->SetBinError(9,0.000116426);
  v2_y__1->SetBinError(10,0.000118453);
  v2_y__1->SetBinError(11,0.000122358);
  v2_y__1->SetBinError(12,0.000128069);
  v2_y__1->SetBinError(13,0.00013622);
  v2_y__1->SetBinError(14,0.000147752);
  v2_y__1->SetBinError(15,0.000161949);
  v2_y__1->SetBinError(16,0.000179281);
  v2_y__1->SetBinError(17,0.000199897);
  v2_y__1->SetBinError(18,0.000224663);
  v2_y__1->SetBinError(19,0.000253895);
  v2_y__1->SetBinError(20,0.000289445);
  v2_y__1->SetBinError(21,0.000332632);
  v2_y__1->SetBinError(22,0.000384886);
  v2_y__1->SetBinError(23,0.00044875);
  v2_y__1->SetBinError(24,0.000526522);
  v2_y__1->SetBinError(25,0.000620442);
  v2_y__1->SetBinError(26,0.000734167);
  v2_y__1->SetBinError(27,0.000871311);
  v2_y__1->SetBinError(28,0.00103732);
  v2_y__1->SetBinError(29,0.001241);
  v2_y__1->SetBinError(30,0.00148565);
  v2_y__1->SetBinError(31,0.00178536);
  v2_y__1->SetBinError(32,0.00214672);
  v2_y__1->SetBinError(33,0.00258648);
  v2_y__1->SetBinError(34,0.0031326);
  v2_y__1->SetBinError(35,0.0037717);
  v2_y__1->SetBinError(36,0.00455294);
  v2_y__1->SetBinError(37,0.00553213);
  v2_y__1->SetBinError(38,0.00690784);
  v2_y__1->SetEntries(179031);

  Comparator elliptic("elliptic");
  elliptic.SetRebinProjection([](Qn::DataContainer<Qn::Stats> container){
    container = container.Rebin({"Centrality", 1, 20.0, 30.0});
    container = container.Rebin({"0_Ycm", 1, -0.25, -0.15});
    container = container.Projection({"0_Pt"});
    return container;
  });
  elliptic.SetLegendPosition({0.16, 0.11, 0.5, 0.4});
  elliptic.SetXAxisTitle("pt, [GeV/c]");
  elliptic.SetYAxisTitle("v_{2}");
  elliptic.AddFile(file_in, "fw3s");
  elliptic.MergeAddContainers("fw3s", {"flow_RND_2_XX_Ep",
                                       "flow_RND_2_YY_Ep"}, "RND Extrapolation", {kFullSquare, kRed});
  elliptic.MergeAddContainers("fw3s", {"flow_RND_2_NE_XXX_Ep",
                                       "flow_RND_2_NE_XYY_Ep"}, "RND No Extrapolation", {kOpenSquare, kRed});
  elliptic.AddTh1((TH1*)v2_y__1, {kFullCircle, kBlack});
  auto canvas_v2 = new TCanvas("canv_v2", "", 1000, 1100);
  elliptic.SetCanvas(canvas_v2);
  elliptic.Draw();
  canvas_v2->Print("someshit_v2.png");

  float xxd10_[8]={5.00,15.00,25.00,35.00,45.00,55.00,65.00,75.00};
  float yyd10_1[8]={0.648119,0.846185,0.885663,0.870407,0.805356,0.729117,0.673409,0.662364};
  TGraphAsymmErrors* NEWresV1FEP10 = new TGraphAsymmErrors(8,xxd10_,yyd10_1);
  Comparator resolution_directed("resolution directed");
  resolution_directed.SetRebinProjection([](Qn::DataContainer<Qn::Stats> container){
//    container = container.Rebin({"Centrality", 5, 0.0, 50.0});
    return container;
  });
  resolution_directed.SetLegendPosition({0.35, 0.11, 0.75, 0.4});
  resolution_directed.SetXAxisRange({0.0, 50.0});
  resolution_directed.SetYAxisRange({0.59, .949});
  resolution_directed.SetXAxisTitle("centrality, (%)");
  resolution_directed.SetYAxisTitle("R_{1}");
  resolution_directed.AddFile(file_in, "fw3s");
  resolution_directed.MergeAddContainers("fw3s", {"resolution_RND_XX_Ep",
                                       "resolution_RND_YY_Ep"}, "Mamaev RND", {kFullSquare, kRed});
  resolution_directed.AddGraph( NEWresV1FEP10, "B. Kardan", {kFullCircle, kBlack});
  auto canvas_resolution_v1 = new TCanvas("canv_reso_v1", "", 1000, 1100);
  resolution_directed.SetCanvas(canvas_resolution_v1);
  resolution_directed.Draw();
  canvas_resolution_v1->Print("someshit_resol.png");

  float yyd10_2[8]={0.297805,0.571107,0.650323,0.618142,0.500789,0.391466,0.324983,0.312900};
  TGraphAsymmErrors* NEWresV2FEP10 = new TGraphAsymmErrors(8,xxd10_,yyd10_2);

  Comparator resolution_elliptic("resolution directed");
  resolution_elliptic.SetRebinProjection([](Qn::DataContainer<Qn::Stats> container){
//    container = container.Rebin({"Centrality", 5, 0.0, 50.0});
    return container;
  });
  resolution_elliptic.SetLegendPosition({0.35, 0.11, 0.75, 0.4});
  resolution_elliptic.SetXAxisRange({0.0, 50.0});
  resolution_elliptic.SetYAxisRange({0.249, .69});
  resolution_elliptic.SetXAxisTitle("centrality, (%)");
  resolution_elliptic.SetYAxisTitle("R_{2}");
  resolution_elliptic.AddFile(file_in, "fw3s");
  resolution_elliptic.MergeAddContainers("fw3s", {"resolution_RND_2_XX_Ep",
                                       "resolution_RND_2_YY_Ep"}, "Mamaev RND", {kFullSquare, kRed});
  resolution_elliptic.AddGraph( NEWresV2FEP10, "B. Kardan", {kFullCircle, kBlack});
  auto canvas_resolution_v2 = new TCanvas("canv_reso_v2", "", 1000, 1100);
  resolution_elliptic.SetCanvas(canvas_resolution_v2);
  resolution_elliptic.Draw();
  canvas_resolution_v2->Print("someshit_resol_v2.png");

  return 0;
}

