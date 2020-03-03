//
// Created by mikhail on 26.11.2019.
//
#include <Comparator.h>
#include <Systematics.h>
void BuildElliptic(const std::string& file_in_name, const std::string& file_out_name);
void BuildDirected(const std::string& file_in_name, const std::string& file_out_name);
void BuildDirectedResolution(const std::string& file_in_name, const std::string& file_out_name);
void BuildEllipticResolution(const std::string& file_in_name, const std::string& file_out_name);
void BuildEllipticExtra(const std::string& file_in_name, const std::string& file_out_name);

int main(int n_args, char** args){
  std::string flag = args[1];
  std::string file_in_name = args[2];
  std::string file_out_name = args[3];
  if( flag == "--V1" )
    BuildDirected(file_in_name, file_out_name);
  if( flag == "--V2" )
    BuildElliptic(file_in_name, file_out_name);
  if( flag == "--X2" )
    BuildEllipticExtra(file_in_name, file_out_name);
  if( flag == "--R1" )
    BuildDirectedResolution(file_in_name, file_out_name);
  if( flag == "--R2" )
    BuildEllipticResolution(file_in_name, file_out_name);
  return 0;
}

void BuildDirected(const std::string& file_in_name, const std::string& file_out_name){
  auto file_in = TFile::Open(file_in_name.data());
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
  auto rebin_proj = [](std::vector<Qn::DataContainer<Qn::Stats>> container){
    container.back() = container.back().Rebin({"0_Ycm", 1, -0.25, -0.15});
    container.back() = container.back().Projection({"Centrality"});
    return container.back();
  };
  auto file_ref = new TFile("../Output_Files/RND_PT2_bunches.root");
  Systematics default_value("RND-Sub");
  default_value.GetFlowHelper().SetFile(file_ref);
  default_value.SetRebinProjection(rebin_proj);
  default_value.Init(prefix, {"RND"},
                     {"_XX_Ep", "_YY_Ep"});
  std::vector<TCanvas*> canvases;
  auto file_name = file_out_name+".root";
  auto file_out = TFile::Open(file_name.data(), "recreate");
  for( size_t i=0; i<systematics_names.size(); i++ ){
    systematics.emplace_back(systematics_names.at(i));
    systematics.back().SetRebinProjection(rebin_proj);
    systematics.back().SetXAxisRange({0.0, 40.0});
    systematics.back().SetResultPlotRange({-0.149, -0.071});
    systematics.back().SetRatioPlotRange({0.81, 1.19});
    systematics.back().GetFlowHelper().SetFile(file_in);
    systematics.back().Init(prefix, sub_events_names.at(i), components_names.at(i));
    std::string canvas_name{systematics_names.at(i)+"_comp"};
    canvases.push_back( new TCanvas(canvas_name.data(), "", 1000, 1200) );
    systematics.back().SetDefault( default_value.GetAveraged() );
    systematics.back().SetSubEventsNames(sub_events_titles.at(i));
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
    systematics.back().SetDefaultTitle("RND-sub");
    systematics.back().SetLegendPosition({0.4, 0.5, 0.75, 0.89});
    systematics.back().SetAxisTitles("centrality (%)", "v_{1}");
    systematics.back().DrawSubEvents(canvases.back());
    canvas_name = file_out_name+"_"+systematics_names.at(i)+"_sub_evt.png";
    canvases.back()->Print(canvas_name.data());
    systematics.back().SaveToFile(file_out);
  }
  systematics.clear();
  file_in->Close();
  file_out->Close();
}

void BuildDirectedResolution(const std::string& file_in_name, const std::string& file_out_name){
  auto file_in = TFile::Open(file_in_name.data());
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
      {// Good combinations
          "W1 (Mf, Mb)", "W1 (Mf, W3)", "W1 (Mb, W3)", "W3 (Mf, W1)", "W3 (Mb, W1)", "W2 (Mf, Mb)", "W3 (Mf, Mb)"},
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
  auto rebin_proj = [](std::vector<Qn::DataContainer<Qn::Stats>> container){
    container.back() = container.back().Projection({"Centrality"});
    return container.back();
  };
  std::vector<TCanvas*> canvases;
  auto file_name = file_out_name+".root";
  auto file_out = TFile::Open(file_name.data(), "recreate");
  for( size_t i=0; i<systematics_names.size(); i++ ){
    systematics.emplace_back(systematics_names.at(i));
    systematics.back().SetRebinProjection(rebin_proj);
    systematics.back().SetXAxisRange({0.0, 40.0});
    systematics.back().SetResultPlotRange({0.051, 0.419});
    systematics.back().SetRatioPlotRange({0.81, 1.19});
    systematics.back().GetFlowHelper().SetFile(file_in);
    systematics.back().Init(prefix, sub_events_names.at(i), components_names.at(i));
    std::string canvas_name{systematics_names.at(i)+"_comp"};
    canvases.push_back( new TCanvas(canvas_name.data(), "", 1000, 1200) );
    systematics.back().SetSubEventsNames(sub_events_titles.at(i));
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
    systematics.back().SetDefaultTitle(reference_names.at(i));
    systematics.back().SetLegendPosition({0.4, 0.01, 0.75, 0.5});
    systematics.back().SetAxisTitles("centrality (%)", "R_{1}");
    systematics.back().DrawSubEvents(canvases.back());
    canvas_name = file_out_name+"_"+systematics_names.at(i)+"_sub_evt.png";
    canvases.back()->Print(canvas_name.data());
    systematics.back().SaveToFile(file_out);
  }
  systematics.clear();
  file_in->Close();
  file_out->Close();
}

void BuildElliptic(const std::string& file_in_name, const std::string& file_out_name){
  auto file_in = TFile::Open(file_in_name.data());
  std::vector<Systematics> systematics;
  std::vector<std::string> systematics_names{ "FWs1_FWs2", "FWs1_FWs3", "FWs2_FWs3" };
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
  std::vector<std::string> averaged_names{
    "all W1 #times W2 estimates’ average",
    "all W1 #times W3 estimates’ average",
    "all W2 #times W3 estimates’ average"
  };
  auto rebin_proj = [](std::vector<Qn::DataContainer<Qn::Stats>> container){
    container.back() = container.back().Rebin({"0_Ycm", 1, -0.25, -0.15});
//    container.back() = container.back().Rebin({"Centrality", 1, 20.0, 30.0});
    container.back() = container.back().Projection({"Centrality"});
    return container.back()*(1);
  };
  auto file_ref = new TFile("../Output_Files/RND_PT2_statistics.root");
  Systematics default_value("RND-Sub");
  default_value.GetFlowHelper().SetFile(file_ref);
  default_value.SetRebinProjection(rebin_proj);
  default_value.Init(prefix, {"RND_2"},
                     {"_XX_Ep", "_YY_Ep"});
  std::vector<TCanvas*> canvases;
  auto file_name = file_out_name+".root";
  auto file_out = TFile::Open(file_name.data(), "recreate");
  for( size_t i=0; i<systematics_names.size(); i++ ){
    systematics.emplace_back(systematics_names.at(i));
    systematics.back().SetRebinProjection(rebin_proj);
    systematics.back().SetXAxisRange({0., 40.});
    systematics.back().SetResultPlotRange({-0.139, -0.011});
    systematics.back().SetRatioPlotRange({0.71, 1.29});
    systematics.back().GetFlowHelper().SetFile(file_in);
    systematics.back().Init(prefix, sub_events_names.at(i), components_names.at(i));
    std::string canvas_name{systematics_names.at(i)+"_comp"};
    canvases.push_back( new TCanvas(canvas_name.data(), "", 1000, 1200) );
    systematics.back().SetDefault( default_value.GetAveraged() );
    systematics.back().SetSubEventsNames(sub_events_titles.at(i));
    systematics.back().SetMarkerStyles({
                                           kFullSquare,
                                           kFullTriangleUp,
                                           kFullTriangleDown,
                                           kOpenTriangleUp,
                                           kOpenTriangleDown,
                                           kFullCross
                                       });
    systematics.back().SetMarkerColors({
                                           kBlue+1,
                                           kRed+1,
                                           kGreen+1,
                                           kRed+1,
                                           kGreen+1,
                                           kMagenta+1
                                       });
    systematics.back().SetDefaultTitle("RND-Sub");
    systematics.back().SetAxisTitles("centrality (%)", "v_{2}");
    systematics.back().SetLegendPosition({0.16, 0.01, 0.5, 0.5});
    systematics.back().DrawSubEvents(canvases.back());
    canvas_name = file_out_name+"_"+systematics_names.at(i)+"_sub_evt.png";
    canvases.back()->Print(canvas_name.data());
    systematics.back().SaveToFile(file_out);
  }
  systematics.clear();
  file_in->Close();
  file_out->Close();
}

void BuildEllipticExtra(const std::string& file_in_name, const std::string& file_out_name){
  auto file_in = TFile::Open(file_in_name.data());
  std::vector<Systematics> systematics;
  std::vector<std::string> systematics_names{ "MDCfx", "MDCbx" };
  std::string prefix{"flow_"};
  std::vector<std::vector<std::string>> sub_events_names{
      {"MDCf(FWs1,FWs2)", "MDCf(FWs1,FWs3)", "MDCf(FWs2,FWs3)"},
      {"MDCb(FWs1,FWs2)", "MDCb(FWs1,FWs3)", "MDCb(FWs2,FWs3)"},
  };
  std::vector<std::vector<std::string>> sub_events_titles{
      {// <u, Mf>
          "Mf (W1, W2)", "Mf (W1, W3)", "Mf (W2, W3)"},
      {// <u, Mb>
          "Mb (W1, W2)", "Mb (W1, W3)", "Mb (W2, W3)"},
  };
  std::vector<std::vector<std::string>> components_names{
      {"_XXx_Sp", "_XXy_Sp"},
      {"_XXx_Sp", "_XXy_Sp"},
  };
  auto rebin_proj = [](std::vector<Qn::DataContainer<Qn::Stats>> container){
    container.back() = container.back().Rebin({"Centrality", 1, 20.0, 30.0});
    container.back() = container.back().Projection({"0_Ycm"});
    return container.back();
  };
  auto file_ref = new TFile("../Output_Files/RND_PT2_bunches.root");
  Systematics default_value("RND-Sub");
  default_value.GetFlowHelper().SetFile(file_ref);
  default_value.SetRebinProjection(rebin_proj);
  default_value.Init(prefix, {"RND_2"},
                     {"_XX_Ep", "_YY_Ep"});
  std::vector<TCanvas*> canvases;
  auto file_name = file_out_name+".root";
  auto file_out = TFile::Open(file_name.data(), "recreate");
  for( size_t i=0; i<systematics_names.size(); i++ ){
    systematics.emplace_back(systematics_names.at(i));
    systematics.back().SetRebinProjection(rebin_proj);
    systematics.back().SetXAxisRange({-0.85, 0.85});
    systematics.back().SetResultPlotRange({-0.15, 0.05});
    systematics.back().SetRatioPlotRange({0.71, 1.29});
    systematics.back().GetFlowHelper().SetFile(file_in);
    systematics.back().Init(prefix, sub_events_names.at(i), components_names.at(i));
    std::string canvas_name{systematics_names.at(i)+"_comp"};
    canvases.push_back( new TCanvas(canvas_name.data(), "", 1000, 1200) );
    systematics.back().SetDefault( default_value.GetAveraged() );
    systematics.back().SetSubEventsNames(sub_events_titles.at(i));
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
    systematics.back().SetDefaultTitle("RND-sub");
    systematics.back().SetAxisTitles("centrality (%)", "v_{2}");
    systematics.back().SetLegendPosition({0.16, 0.01, 0.35, 0.35});
    systematics.back().DrawSubEvents(canvases.back());
    canvas_name = file_out_name+"_"+systematics_names.at(i)+"_sub_evt.png";
    canvases.back()->Print(canvas_name.data());
    systematics.back().SaveToFile(file_out);
  }
  systematics.clear();
  file_in->Close();
  file_out->Close();
}

void BuildEllipticResolution(const std::string& file_in_name, const std::string& file_out_name){
  auto file_in = TFile::Open(file_in_name.data());
  std::vector<Systematics> systematics;
  std::vector<std::string> systematics_names{ "FWs1_FWs2", "FWs1_FWs3", "FWs2_FWs3" };
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
  std::vector<std::string> averaged_names{
      "all W1 #times W2 estimates' average",
      "all W1 #times W3 estimates' average",
      "all W2 #times W3 estimates' average"
  };
  auto rebin_proj = [](std::vector<Qn::DataContainer<Qn::Stats>> container){
    container.back() = container.back().Projection({"Centrality"});
    return container.back();
  };
  std::vector<TCanvas*> canvases;
  auto file_name = file_out_name+".root";
  auto file_out = TFile::Open(file_name.data(), "recreate");
  for( size_t i=0; i<systematics_names.size(); i++ ){
    systematics.emplace_back(systematics_names.at(i));
    systematics.back().SetRebinProjection(rebin_proj);
    systematics.back().SetXAxisRange({0., 40.});
    systematics.back().SetResultPlotRange({0.01, 0.149});
    systematics.back().SetRatioPlotRange({0.71, 1.29});
    systematics.back().GetFlowHelper().SetFile(file_in);
    systematics.back().Init(prefix, sub_events_names.at(i), components_names.at(i));
    std::string canvas_name{systematics_names.at(i)+"_comp"};
    canvases.push_back( new TCanvas(canvas_name.data(), "", 1000, 1200) );
    systematics.back().SetSubEventsNames(sub_events_titles.at(i));
    systematics.back().SetMarkerStyles({
                                           kFullSquare,
                                           kFullTriangleUp,
                                           kFullTriangleDown,
                                           kOpenTriangleUp,
                                           kOpenTriangleDown,
                                           kFullCross
                                       });
    systematics.back().SetMarkerColors({
                                           kBlue+1,
                                           kRed+1,
                                           kGreen+1,
                                           kRed+1,
                                           kGreen+1,
                                           kMagenta+1
                                       });
    systematics.back().SetAxisTitles("centrality (%)", "R_{2}");
    systematics.back().SetLegendPosition({0.4, 0.0, 0.75, 0.5});
    systematics.back().SetDefaultTitle(averaged_names.at(i));
    systematics.back().DrawSubEvents(canvases.back());
    canvas_name = file_out_name+"_"+systematics_names.at(i)+"_sub_evt.png";
    canvases.back()->Print(canvas_name.data());
    systematics.back().SaveToFile(file_out);
  }
  systematics.clear();
  file_in->Close();
  file_out->Close();
}
