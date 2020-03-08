//
// Created by mikhail on 3/4/20.
//

#include <TFile.h>
#include <string>
#include <systematics.h>
void BuildDirected(const std::string& file_in_name, const std::string& file_out_name);
void BuildElliptic(const std::string& file_in_name, const std::string& file_out_name);
void BuildDirectedResolution(const std::string& file_in_name, const std::string& file_out_name);
void BuildEllipticResolution(const std::string& file_in_name, const std::string& file_out_name);

int main(int n_args, char** args){
  std::string flag = args[1];
  std::string file_in_name = args[2];
  std::string file_out_name = args[3];
  if( flag == "--V1" )
    BuildDirected(file_in_name, file_out_name);
  if( flag == "--V2" )
    BuildElliptic(file_in_name, file_out_name);
  if( flag == "--R1" )
    BuildDirectedResolution(file_in_name, file_out_name);
  if( flag == "--R2" )
    BuildEllipticResolution(file_in_name, file_out_name);
  return 0;
}

void BuildDirected(const std::string& file_in_name, const std::string& file_out_name){
  std::shared_ptr<TFile> file_in{TFile::Open(file_in_name.data())};
  std::vector<Systematics> systematics;
  std::vector<std::string> systematics_names{ "FWs1", "FWs2", "FWs3", "MDCf", "MDCb", "Favorite" };
  std::string prefix{"flow_"};
  std::vector<std::vector<std::string>> sub_events_names{
      {"FWs1(MDCf,MDCb)", "FWs1(MDCf,FWs2)", "FWs1(MDCf,FWs3)", "FWs1(MDCb,FWs2)", "FWs1(MDCb,FWs3)", "FWs1(FWs2,FWs3)"},
      {"FWs2(MDCf,MDCb)", "FWs2(MDCf,FWs1)", "FWs2(MDCf,FWs3)", "FWs2(MDCb,FWs1)", "FWs2(MDCb,FWs3)", "FWs2(FWs1,FWs3)"},
      {"FWs3(MDCf,MDCb)", "FWs3(MDCf,FWs1)", "FWs3(MDCf,FWs2)", "FWs3(MDCb,FWs1)", "FWs3(MDCb,FWs2)", "FWs3(FWs1,FWs2)"},
      {"MDCf(MDCb,Fws1)", "MDCf(MDCb,FWs2)", "MDCf(MDCb,FWs3)", "MDCf(FWs1,FWs2)", "MDCf(FWs1,FWs3)", "MDCf(FWs2,FWs3)"},
      {"MDCb(MDCf,Fws1)", "MDCb(MDCf,FWs2)", "MDCb(MDCf,FWs3)", "MDCb(FWs1,FWs2)", "MDCb(FWs1,FWs3)", "MDCb(FWs2,FWs3)"},
      // Good combinations
      {"FWs1(MDCf,MDCb)", "FWs1(MDCf,FWs3)", "FWs1(MDCb,FWs3)", "FWs2(MDCf,MDCb)", "FWs3(MDCf,MDCb)", "FWs3(MDCf,FWs1)", "FWs3(MDCb,FWs1)"},

  };
  std::vector<std::vector<std::string>> sub_events_titles{
      { // <u, W1>
          "W1 (Mf, Mb)", "W1 (Mf, W2)", "W1 (Mf, W3)", "W1 (Mb, W2)", "W1 (Mb, W3)", "W1 (W2, W3)"},
      {// <u, W2>
          "W2 (Mf, Mb)", "W2 (Mf, W1)", "W2 (Mf, W3)", "W2 (Mb, W1)", "W2 (Mb, W3)", "W2 (W1, W3)"},
      {// <u, W3>
          "W3 (Mf, Mb)", "W3 (Mf, W1)", "W3 (Mf, W2)", "W3 (Mb, W1)", "W3 (Mb, W2)", "W3 (W1, W2)"},
      {// <u, Mf>
          "Mf (Mb, W1)", "Mf (Mb, W2)", "Mf (Mb, W3)", "Mf (W1, W2)", "Mf (W1, W3)", "Mf (W2, W3)"},
      {// <u, Mb>
          "Mb (Mf, W1)", "Mb (Mf, W2)", "Mb (Mf, W3)", "Mb (W1, W2)", "Mb (W1, W3)", "Mb (W2, W3)"},
      {// Good combinations
          "W1 (Mf, Mb)", "W1 (Mf, W3)", "W1 (Mb, W3)", "W3 (Mf, W1)", "W3 (Mb, W1)", "W2 (Mf, Mb)", "W3 (Mf, Mb)"},
  };
  std::vector<std::vector<std::string>> components_names{
      {"_XX_Sp", "_YY_Sp"},
      {"_XX_Sp", "_YY_Sp"},
      {"_XX_Sp", "_YY_Sp"},
      {"_XX_Sp", "_YY_Sp"},
      {"_XX_Sp", "_YY_Sp"},
      {"_XX_Sp", "_YY_Sp"},
  };
  auto rebin_proj = [](Qn::DataContainer<Qn::Stats> container){
    container = container.Rebin({"0_Ycm", 1, -0.25, -0.15});
    container = container.Projection({"Centrality"});
    return container;
  };
  std::shared_ptr<TFile> file_ref{TFile::Open("../Output_Files/RND_PT2_bunches.root")};
  std::vector<std::shared_ptr<TCanvas>> canvases;
  auto file_name = file_out_name+".root";
  std::shared_ptr<TFile> file_out{TFile::Open(file_name.data(), "recreate")};
  for( size_t i=0; i<systematics_names.size(); i++ ){
    systematics.emplace_back(systematics_names.at(i));
    systematics.back().SetRebinProjectionRule(rebin_proj);
    systematics.back().SetXAxisRange({0.0, 40.0});
    systematics.back().SetResultPlotRange({-0.149, -0.071});
    systematics.back().SetRatioPlotRange({0.81, 1.19});
    systematics.back().SetFile(file_in);
    auto prefixes = sub_events_names.at(i);
    std::for_each( prefixes.begin(), prefixes.end(), [prefix](std::string& str){
      str=prefix+str;
    });
    systematics.back().AddObservables( sub_events_titles.at(i), prefixes, components_names.at(i) );
    std::string canvas_name{systematics_names.at(i)+"_comp"};
    canvases.emplace_back( new TCanvas(canvas_name.data(), "", 1000, 1200) );
    systematics.back().AddReference( "RND-Sub", "flow_RND",
                                     {"_XX_Ep", "_YY_Ep"}, file_ref );
    systematics.back().SetMarkerStyles({
                                           kFullSquare,
                                           kFullTriangleUp,
                                           kFullTriangleDown,
                                           kOpenTriangleUp,
                                           kOpenTriangleDown,
                                           kFullCross,
                                           kFullCrossX,
                                       });
    systematics.back().SetMarkerColors({
                                           kBlue+1,
                                           kRed+1,
                                           kGreen+1,
                                           kRed+1,
                                           kGreen+1,
                                           kMagenta+1,
                                           kCyan+1,
                                       });
    systematics.back().SetLegendPosition({0.4, 0.5, 0.75, 0.89});
    systematics.back().SetAxisTitles("centrality (%)", "v_{1}");
    systematics.back().SetCanvas(canvases.back());
    systematics.back().DrawSystematics();
    canvas_name = file_out_name+"_"+systematics_names.at(i)+"_sub_evt.png";
    canvases.back()->Print(canvas_name.data());
    systematics.back().SaveToFile(file_out);
  }
  systematics.clear();
  file_in->Close();
  file_ref->Close();
  file_out->Close();
}

void BuildElliptic(const std::string& file_in_name, const std::string& file_out_name){
  std::shared_ptr<TFile> file_in{TFile::Open(file_in_name.data())};
  std::vector<Systematics> systematics;
  std::vector<std::string> systematics_names{  "FWs1_FWs2", "FWs1_FWs3", "FWs2_FWs3"  };
  std::string prefix{"flow_"};
  std::vector<std::vector<std::string>> sub_events_names{
      {"FWs1(MDCf,MDCb)_FWs2(MDCf,MDCb)", "FWs1(MDCf,FWs3)_FWs2(MDCf,MDCb)", "FWs1(MDCb,FWs3)_FWs2(MDCf,MDCb)", "FWs1(MDCb,FWs2)_FWs2(MDCb,FWs1)", "FWs1(MDCb,FWs3)_FWs2(MDCb,FWs3)", "FWs1(FWs2,FWs3)_FWs2(FWs1,FWs3)"},
      {"FWs1(MDCf,MDCb)_FWs3(MDCf,MDCb)", "FWs1(MDCf,MDCb)_FWs3(MDCf,FWs1)", "FWs1(MDCf,MDCb)_FWs3(MDCb,FWs1)", "FWs1(MDCf,FWs3)_FWs3(MDCf,MDCb)", "FWs1(MDCb,FWs3)_FWs3(MDCf,MDCb)", "FWs1(MDCf,FWs3)_FWs3(MDCf,FWs1)"},
      {"FWs2(MDCf,MDCb)_FWs3(MDCf,MDCb)", "FWs2(MDCf,MDCb)_FWs3(MDCf,FWs1)", "FWs2(MDCf,MDCb)_FWs3(MDCb,FWs1)", "FWs2(MDCb,FWs3)_FWs3(MDCb,FWs2)", "FWs2(MDCb,FWs1)_FWs3(MDCb,FWs1)", "FWs2(FWs1,FWs3)_FWs3(FWs1,FWs2)"}
  };
  std::vector<std::vector<std::string>> sub_events_titles{
      { // <u,FWs1,FWs2>
          "W1(Mf,Mb) #times W2(Mf,Mb)",
          "W1(Mf,W3) #times W2(Mf,Mb)",
          "W1(Mb,W3) #times W2(Mf,Mb)",
          "W1(Mb,W2) #times W2(Mb,W1)",
          "W1(Mb,W3) #times W2(Mb,W3)",
          "W1(W2,W3) #times W2(W1,W3)"},
      {// <u, W1, W3>
          "W1(Mf,Mb) #times W3(Mf,Mb)",
          "W1(Mf,Mb) #times W3(Mf,W1)",
          "W1(Mf,Mb) #times W3(Mb,W1)",
          "W1(Mf,W3) #times W3(Mf,Mb)",
          "W1(Mb,W3) #times W3(Mf,Mb)",
          "W1(Mf,W3) #times W3(Mf,W1)",
      },
      {// <u, W2, W3>
          "W2(Mf,Mb) #times W3(Mf,Mb)",
          "W2(Mf,Mb) #times W3(Mf,W1)",
          "W2(Mf,Mb) #times W3(Mb,W1)",
          "W2(Mb,W3) #times W3(Mb,W2)",
          "W2(Mb,W1) #times W3(Mb,W1)",
          "W2(W1,W3) #times W3(W1,W2)"}
  };
  std::vector<std::vector<std::string>> components_names{
      {"_XXX_Sp", "_XYY_Sp", "_YXY_Sp", "_YYX_Sp"},
      {"_XXX_Sp", "_XYY_Sp", "_YXY_Sp", "_YYX_Sp"},
      {"_XXX_Sp", "_XYY_Sp", "_YXY_Sp", "_YYX_Sp"}
  };
  auto rebin_proj = [](Qn::DataContainer<Qn::Stats> container){
    container = container.Rebin({"0_Ycm", 1, -0.25, -0.15});
    container = container.Projection({"Centrality"});
    return container;
  };
  std::shared_ptr<TFile> file_ref{TFile::Open("../Output_Files/RND_PT2_bunches.root")};
  std::vector<std::shared_ptr<TCanvas>> canvases;
  auto file_name = file_out_name+".root";
  std::shared_ptr<TFile> file_out{TFile::Open(file_name.data(), "recreate")};
  for( size_t i=0; i<systematics_names.size(); i++ ){
    systematics.emplace_back(systematics_names.at(i));
    systematics.back().SetRebinProjectionRule(rebin_proj);
    systematics.back().SetXAxisRange({0.0, 40.0});
    systematics.back().SetResultPlotRange({-0.139, -0.011});
    systematics.back().SetRatioPlotRange({0.81, 1.19});
    systematics.back().SetFile(file_in);
    auto prefixes = sub_events_names.at(i);
    std::for_each( prefixes.begin(), prefixes.end(), [prefix](std::string& str){
      str=prefix+str;
    });
    systematics.back().AddObservables( sub_events_titles.at(i), prefixes, components_names.at(i) );
    std::string canvas_name{systematics_names.at(i)+"_comp"};
    canvases.emplace_back( new TCanvas(canvas_name.data(), "", 1000, 1200) );
    systematics.back().AddReference( "RND-Sub", "flow_RND_2",
                                     {"_XX_Ep", "_YY_Ep"}, file_ref );
    systematics.back().SetMarkerStyles({
                                           kFullSquare,
                                           kFullTriangleUp,
                                           kFullTriangleDown,
                                           kOpenTriangleUp,
                                           kOpenTriangleDown,
                                           kFullCross,
                                           kFullCrossX,
                                       });
    systematics.back().SetMarkerColors({
                                           kBlue+1,
                                           kRed+1,
                                           kGreen+1,
                                           kRed+1,
                                           kGreen+1,
                                           kMagenta+1,
                                           kCyan+1,
                                       });
    systematics.back().SetLegendPosition({0.4, 0.5, 0.75, 0.89});
    systematics.back().SetAxisTitles("centrality (%)", "v_{1}");
    systematics.back().SetCanvas(canvases.back());
    systematics.back().DrawSystematics();
    canvas_name = file_out_name+"_"+systematics_names.at(i)+"_sub_evt.png";
    canvases.back()->Print(canvas_name.data());
    systematics.back().SaveToFile(file_out);
  }
  systematics.clear();
  file_in->Close();
  file_ref->Close();
  file_out->Close();
}

void BuildDirectedResolution(const std::string& file_in_name, const std::string& file_out_name){
  std::shared_ptr<TFile> file_in{TFile::Open(file_in_name.data())};
  std::vector<Systematics> systematics;
  std::vector<std::string> systematics_names{ "FWs1", "FWs2", "FWs3", "MDCf", "MDCb" };
  std::string prefix{"resolution_"};
  std::vector<std::vector<std::string>> sub_events_names{
      {"FWs1(MDCf,MDCb)", "FWs1(MDCf,FWs2)", "FWs1(MDCf,FWs3)", "FWs1(MDCb,FWs2)", "FWs1(MDCb,FWs3)", "FWs1(FWs2,FWs3)"},
      {"FWs2(MDCf,MDCb)", "FWs2(MDCf,FWs1)", "FWs2(MDCf,FWs3)", "FWs2(MDCb,FWs1)", "FWs2(MDCb,FWs3)", "FWs2(FWs1,FWs3)"},
      {"FWs3(MDCf,MDCb)", "FWs3(MDCf,FWs1)", "FWs3(MDCf,FWs2)", "FWs3(MDCb,FWs1)", "FWs3(MDCb,FWs2)", "FWs3(FWs1,FWs2)"},
      {"MDCf(MDCb,Fws1)", "MDCf(MDCb,FWs2)", "MDCf(MDCb,FWs3)", "MDCf(FWs1,FWs2)", "MDCf(FWs1,FWs3)", "MDCf(FWs2,FWs3)"},
      {"MDCb(MDCf,Fws1)", "MDCb(MDCf,FWs2)", "MDCb(MDCf,FWs3)", "MDCb(FWs1,FWs2)", "MDCb(FWs1,FWs3)", "MDCb(FWs2,FWs3)"},
  };
  std::vector<std::vector<std::string>> sub_events_titles{
      { // <u, W1>
          "W1 (Mf, Mb)", "W1 (Mf, W2)", "W1 (Mf, W3)", "W1 (Mb, W2)", "W1 (Mb, W3)", "W1 (W2, W3)"},
      {// <u, W2>
          "W2 (Mf, Mb)", "W2 (Mf, W1)", "W2 (Mf, W3)", "W2 (Mb, W1)", "W2 (Mb, W3)", "W2 (W1, W3)"},
      {// <u, W3>
          "W3 (Mf, Mb)", "W3 (Mf, W1)", "W3 (Mf, W2)", "W3 (Mb, W1)", "W3 (Mb, W2)", "W3 (W1, W2)"},
      {// <u, Mf>
          "Mf (Mb, W1)", "Mf (Mb, W2)", "Mf (Mb, W3)", "Mf (W1, W2)", "Mf (W1, W3)", "Mf (W2, W3)"},
      {// <u, Mb>
          "Mb (Mf, W1)", "Mb (Mf, W2)", "Mb (Mf, W3)", "Mb (W1, W2)", "Mb (W1, W3)", "Mb (W2, W3)"},
  };
  std::vector<std::string> reference_names{
      "all W1 estimates' average",
      "all W2 estimates' average",
      "all W3 estimates' average",
      "all Mf estimates' average",
      "all Mb estimates' average",
  };
  std::vector<std::vector<std::string>> components_names{
      {"_XX_Sp", "_YY_Sp"},
      {"_XX_Sp", "_YY_Sp"},
      {"_XX_Sp", "_YY_Sp"},
      {"_XX_Sp", "_YY_Sp"},
      {"_XX_Sp", "_YY_Sp"},
      {"_XX_Sp", "_YY_Sp"},
  };
  auto rebin_proj = [](Qn::DataContainer<Qn::Stats> container){
    container = container.Projection({"Centrality"});
    return container;
  };
  std::vector<std::shared_ptr<TCanvas>> canvases;
  auto file_name = file_out_name+".root";
  std::shared_ptr<TFile> file_out{TFile::Open(file_name.data(), "recreate")};
  for( size_t i=0; i<systematics_names.size(); i++ ){
    systematics.emplace_back(systematics_names.at(i));
    systematics.back().SetRebinProjectionRule(rebin_proj);
    systematics.back().SetXAxisRange({0.0, 40.0});
    systematics.back().SetResultPlotRange({0.051, 0.419});
    systematics.back().SetRatioPlotRange({0.81, 1.19});
    systematics.back().SetFile(file_in);
    auto prefixes = sub_events_names.at(i);
    std::for_each( prefixes.begin(), prefixes.end(), [prefix](std::string& str){
      str=prefix+str;
    });
    systematics.back().AddObservables( sub_events_titles.at(i), prefixes, components_names.at(i) );
    std::string canvas_name{systematics_names.at(i)+"_comp"};
    canvases.emplace_back( new TCanvas(canvas_name.data(), "", 1000, 1200) );
    systematics.back().AddReference( reference_names.at(i), "AVERAGED", {},
                                    nullptr );
    systematics.back().SetMarkerStyles({
                                           kFullSquare,
                                           kFullTriangleUp,
                                           kFullTriangleDown,
                                           kOpenTriangleUp,
                                           kOpenTriangleDown,
                                           kFullCross,
                                           kFullCrossX,
                                       });
    systematics.back().SetMarkerColors({
                                           kBlue+1,
                                           kRed+1,
                                           kGreen+1,
                                           kRed+1,
                                           kGreen+1,
                                           kMagenta+1,
                                           kCyan+1,
                                       });
    systematics.back().SetLegendPosition({0.4, 0.01, 0.75, 0.5});
    systematics.back().SetAxisTitles("centrality (%)", "R_{1}");
    systematics.back().SetCanvas(canvases.back());
    systematics.back().DrawSystematics();
    canvas_name = file_out_name+"_"+systematics_names.at(i)+"_sub_evt.png";
    canvases.back()->Print(canvas_name.data());
    systematics.back().SaveToFile(file_out);
  }
  systematics.clear();
  file_in->Close();
  file_out->Close();
}

void BuildEllipticResolution(const std::string& file_in_name, const std::string& file_out_name){
  std::shared_ptr<TFile> file_in{TFile::Open(file_in_name.data())};
  std::vector<Systematics> systematics;
  std::vector<std::string> systematics_names{  "FWs1_FWs2", "FWs1_FWs3", "FWs2_FWs3"  };
  std::string prefix{"resolution_"};
  std::vector<std::vector<std::string>> sub_events_names{
      {"FWs1(MDCf,MDCb)_FWs2(MDCf,MDCb)", "FWs1(MDCf,FWs3)_FWs2(MDCf,MDCb)", "FWs1(MDCb,FWs3)_FWs2(MDCf,MDCb)", "FWs1(MDCb,FWs2)_FWs2(MDCb,FWs1)", "FWs1(MDCb,FWs3)_FWs2(MDCb,FWs3)", "FWs1(FWs2,FWs3)_FWs2(FWs1,FWs3)"},
      {"FWs1(MDCf,MDCb)_FWs3(MDCf,MDCb)", "FWs1(MDCf,MDCb)_FWs3(MDCf,FWs1)", "FWs1(MDCf,MDCb)_FWs3(MDCb,FWs1)", "FWs1(MDCf,FWs3)_FWs3(MDCf,MDCb)", "FWs1(MDCb,FWs3)_FWs3(MDCf,MDCb)", "FWs1(MDCf,FWs3)_FWs3(MDCf,FWs1)"},
      {"FWs2(MDCf,MDCb)_FWs3(MDCf,MDCb)", "FWs2(MDCf,MDCb)_FWs3(MDCf,FWs1)", "FWs2(MDCf,MDCb)_FWs3(MDCb,FWs1)", "FWs2(MDCb,FWs3)_FWs3(MDCb,FWs2)", "FWs2(MDCb,FWs1)_FWs3(MDCb,FWs1)", "FWs2(FWs1,FWs3)_FWs3(FWs1,FWs2)"}
  };
  std::vector<std::vector<std::string>> sub_events_titles{
      { // <u,FWs1,FWs2>
          "W1(Mf,Mb) #times W2(Mf,Mb)",
          "W1(Mf,W3) #times W2(Mf,Mb)",
          "W1(Mb,W3) #times W2(Mf,Mb)",
          "W1(Mb,W2) #times W2(Mb,W1)",
          "W1(Mb,W3) #times W2(Mb,W3)",
          "W1(W2,W3) #times W2(W1,W3)"},
      {// <u, W1, W3>
          "W1(Mf,Mb) #times W3(Mf,Mb)",
          "W1(Mf,Mb) #times W3(Mf,W1)",
          "W1(Mf,Mb) #times W3(Mb,W1)",
          "W1(Mf,W3) #times W3(Mf,Mb)",
          "W1(Mb,W3) #times W3(Mf,Mb)",
          "W1(Mf,W3) #times W3(Mf,W1)",
      },
      {// <u, W2, W3>
          "W2(Mf,Mb) #times W3(Mf,Mb)",
          "W2(Mf,Mb) #times W3(Mf,W1)",
          "W2(Mf,Mb) #times W3(Mb,W1)",
          "W2(Mb,W3) #times W3(Mb,W2)",
          "W2(Mb,W1) #times W3(Mb,W1)",
          "W2(W1,W3) #times W3(W1,W2)"}
  };
  std::vector<std::vector<std::string>> components_names{
      {"_XXX_Sp", "_XYY_Sp", "_YXY_Sp", "_YYX_Sp"},
      {"_XXX_Sp", "_XYY_Sp", "_YXY_Sp", "_YYX_Sp"},
      {"_XXX_Sp", "_XYY_Sp", "_YXY_Sp", "_YYX_Sp"}
  };
  std::vector<std::string> reference_names{
      "all W1 #times W2 estimates' average",
      "all W1 #times W3 estimates' average",
      "all W2 #times W3 estimates' average"
  };
  auto rebin_proj = [](Qn::DataContainer<Qn::Stats> container){
    container = container.Projection({"Centrality"});
    return container;
  };
  std::vector<std::shared_ptr<TCanvas>> canvases;
  auto file_name = file_out_name+".root";
  std::shared_ptr<TFile> file_out{TFile::Open(file_name.data(), "recreate")};
  for( size_t i=0; i<systematics_names.size(); i++ ){
    systematics.emplace_back(systematics_names.at(i));
    systematics.back().SetRebinProjectionRule(rebin_proj);
    systematics.back().SetXAxisRange({0.0, 40.0});
    systematics.back().SetResultPlotRange({0.01, 0.149});
    systematics.back().SetRatioPlotRange({0.81, 1.19});
    systematics.back().SetFile(file_in);
    auto prefixes = sub_events_names.at(i);
    std::for_each( prefixes.begin(), prefixes.end(), [prefix](std::string& str){
      str=prefix+str;
    });
    systematics.back().AddObservables( sub_events_titles.at(i), prefixes, components_names.at(i) );
    std::string canvas_name{systematics_names.at(i)+"_comp"};
    canvases.emplace_back( new TCanvas(canvas_name.data(), "", 1000, 1200) );
    systematics.back().AddReference( reference_names.at(i), "AVERAGED", {},
                                     nullptr );
    systematics.back().SetMarkerStyles({
                                           kFullSquare,
                                           kFullTriangleUp,
                                           kFullTriangleDown,
                                           kOpenTriangleUp,
                                           kOpenTriangleDown,
                                           kFullCross,
                                           kFullCrossX,
                                       });
    systematics.back().SetMarkerColors({
                                           kBlue+1,
                                           kRed+1,
                                           kGreen+1,
                                           kRed+1,
                                           kGreen+1,
                                           kMagenta+1,
                                           kCyan+1,
                                       });
    systematics.back().SetLegendPosition({0.4, 0.01, 0.75, 0.5});
    systematics.back().SetAxisTitles("centrality (%)", "R_{2}");
    systematics.back().SetCanvas(canvases.back());
    systematics.back().DrawSystematics();
    canvas_name = file_out_name+"_"+systematics_names.at(i)+"_sub_evt.png";
    canvases.back()->Print(canvas_name.data());
    systematics.back().SaveToFile(file_out);
  }
  systematics.clear();
  file_in->Close();
  file_out->Close();
}