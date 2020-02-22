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

  TH1D *prof__1 = new TH1D("prof__1","PtY_v1EPcent2030_v1_p_ref",40,0,2.0);
  prof__1->SetBinContent(5,-0.056689);
  prof__1->SetBinContent(6,-0.0724462);
  prof__1->SetBinContent(7,-0.0857622);
  prof__1->SetBinContent(8,-0.0974916);
  prof__1->SetBinContent(9,-0.107819);
  prof__1->SetBinContent(10,-0.117258);
  prof__1->SetBinContent(11,-0.125603);
  prof__1->SetBinContent(12,-0.133623);
  prof__1->SetBinContent(13,-0.13969);
  prof__1->SetBinContent(14,-0.144322);
  prof__1->SetBinContent(15,-0.148571);
  prof__1->SetBinContent(16,-0.152733);
  prof__1->SetBinContent(17,-0.156673);
  prof__1->SetBinContent(18,-0.159905);
  prof__1->SetBinContent(19,-0.163119);
  prof__1->SetBinContent(20,-0.166127);
  prof__1->SetBinContent(21,-0.168766);
  prof__1->SetBinContent(22,-0.171514);
  prof__1->SetBinContent(23,-0.173814);
  prof__1->SetBinContent(24,-0.176317);
  prof__1->SetBinContent(25,-0.178319);
  prof__1->SetBinContent(26,-0.181242);
  prof__1->SetBinContent(27,-0.183801);
  prof__1->SetBinContent(28,-0.185713);
  prof__1->SetBinContent(29,-0.188883);
  prof__1->SetBinContent(30,-0.190504);
  prof__1->SetBinContent(31,-0.196477);
  prof__1->SetBinContent(32,-0.198697);
  prof__1->SetBinContent(33,-0.202736);
  prof__1->SetBinContent(34,-0.209534);
  prof__1->SetBinContent(35,-0.210355);
  prof__1->SetBinContent(36,-0.218307);
  prof__1->SetBinContent(37,-0.214754);
  prof__1->SetBinContent(38,-0.228763);
  prof__1->SetBinError(5,0.000100112);
  prof__1->SetBinError(6,9.00023e-05);
  prof__1->SetBinError(7,8.56353e-05);
  prof__1->SetBinError(8,8.36696e-05);
  prof__1->SetBinError(9,8.33004e-05);
  prof__1->SetBinError(10,8.43943e-05);
  prof__1->SetBinError(11,8.68007e-05);
  prof__1->SetBinError(12,9.0422e-05);
  prof__1->SetBinError(13,9.5733e-05);
  prof__1->SetBinError(14,0.000103389);
  prof__1->SetBinError(15,0.000112835);
  prof__1->SetBinError(16,0.000124382);
  prof__1->SetBinError(17,0.000138099);
  prof__1->SetBinError(18,0.000154591);
  prof__1->SetBinError(19,0.000174109);
  prof__1->SetBinError(20,0.000197741);
  prof__1->SetBinError(21,0.00022648);
  prof__1->SetBinError(22,0.00026123);
  prof__1->SetBinError(23,0.000303788);
  prof__1->SetBinError(24,0.000355307);
  prof__1->SetBinError(25,0.000417879);
  prof__1->SetBinError(26,0.000493254);
  prof__1->SetBinError(27,0.000583958);
  prof__1->SetBinError(28,0.000693991);
  prof__1->SetBinError(29,0.000828552);
  prof__1->SetBinError(30,0.000989711);
  prof__1->SetBinError(31,0.00118674);
  prof__1->SetBinError(32,0.0014243);
  prof__1->SetBinError(33,0.00171553);
  prof__1->SetBinError(34,0.00206693);
  prof__1->SetBinError(35,0.00249372);
  prof__1->SetBinError(36,0.00299973);
  prof__1->SetBinError(37,0.00363269);
  prof__1->SetBinError(38,0.00453434);
  prof__1->SetEntries(480554);

  Comparator comparator("comparator");
  comparator.SetRebinProjection([](Qn::DataContainer<Qn::Stats> container){
    container = container.Rebin({"Centrality", 1, 20.0, 30.0});
    container = container.Rebin({"0_Ycm", 1, -0.25, -0.15});
    container = container.Projection({"0_Pt"});
    return container;
  });
  comparator.SetLegendPosition({0.15, 0.15, 0.5, 0.4});
  comparator.SetXAxisTitle("pt, [GeV/c]");
  comparator.SetYAxisTitle("v_{1}");
  comparator.AddFile(file_in, "fw3s");
  comparator.MergeAddContainers("fw3s", {"flow_RND_XX_Ep",
                                        "flow_RND_YY_Ep"}, "Mamaev RND", {kFullCircle, kBlack});
  comparator.AddTh1((TH1*) prof__1, {kFullTriangleUp, kRed});
  auto canvas = new TCanvas("canv", "", 1000, 1100);
  comparator.SetCanvas(canvas);
  comparator.Draw();
  canvas->Print("someshit.png");
  return 0;
}

