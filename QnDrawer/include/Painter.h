//
// Created by mikhail on 2/20/20.
//

#ifndef QNDRAWER_PAINTER_H
#define QNDRAWER_PAINTER_H

#include <DataContainer.h>
#include <Stats.h>
#include <TStyle.h>
#include <TLegend.h>
#include <string>
#include <utility>
#include <vector>

class Painter {
public:
  explicit Painter(std::string name) : name_(std::move(name)) {}
  virtual ~Painter() = default;
public:
  void SetTitles(const std::vector<std::string> &titles) {
    titles_ = titles;
  }
  void const SetMarkerStyles(const std::vector<int> &markerStyles) {
    marker_styles_ = markerStyles;
  }
  void const SetMarkerColors(const std::vector<int> &markerColors) {
    marker_colors_ = markerColors;
  }
  const void SetXAxisRange(const std::vector<float> &xAxisRange) {
    x_axis_range_ = xAxisRange;
  }
  void const SetResultPlotRange(const std::vector<float> &resultPlotRange) {
    result_plot_range_ = resultPlotRange;
  }
  void const SetRatioPlotRange(const std::vector<float> &ratioPlotRange) {
    ratio_plot_range_ = ratioPlotRange;
  }
  void DrawSystematics(TCanvas *canvas,
                       std::vector<Qn::DataContainer<Qn::Stats>> results,
                       std::vector<Qn::DataContainer<Qn::Stats>> ratios) {
    gStyle->SetPadLeftMargin(0.15);
    gStyle->SetTitleSize(0.08,"X");
    gStyle->SetTitleSize(0.04,"Y");
    gStyle->SetTitleOffset(1.6,"Y");
    gStyle->SetTitleOffset(1.0,"X");
    TLegend* legend = nullptr;
    if( !legend_positon_.empty() )
      legend = new TLegend(legend_positon_.at(0), legend_positon_.at(1),
                           legend_positon_.at(2), legend_positon_.at(3));
    else
      legend = new TLegend(0.35, 0.0, 0.7, 0.35);
    legend->SetBorderSize(0);
    std::string pad_name = name_ + "_result";
    auto result_pad = new TPad(pad_name.data(), "result", 0.0, 0.35, 1.0, 1.0);
    auto stack_title = ";" + x_axis_title_ + ";" + y_axis_title_;
    auto result_stack = new TMultiGraph("result", stack_title.data());
    pad_name = name_ + "_ratio";
    stack_title = ";" + x_axis_title_;
    auto ratio_pad = new TPad(pad_name.data(), "ratio", 0.0, 0.0, 1.0, .35);
    auto ratio_stack = new TMultiGraph("ratio", stack_title.data());
    TF1* line;
    if( x_axis_range_.size() == 2 )
      line = new TF1("line", "1", x_axis_range_.at(0), x_axis_range_.at(1));
    else
      line = new TF1("line", "1", -100, 100);
    TGraphAsymmErrors *graph = nullptr;
    graph->SetMarkerSize(1.6);
    graph->SetLineWidth(2);
    result_stack->Add(graph);
    for (size_t i = 0; i < results.size(); i++) {
      results.at(i).SetSetting(Qn::Stats::Settings::CORRELATEDERRORS);
      graph = Qn::DataContainerHelper::ToTGraph(results.at(i));
      graph->SetTitle(titles_.at(i).data());
      graph->SetMarkerSize(1.6);
      if( i<marker_styles_.size() )
        graph->SetMarkerStyle(marker_styles_.at(i));
      if( i<marker_colors_.size() ){
        graph->SetMarkerColor(marker_colors_.at(i));
        graph->SetLineColor(marker_colors_.at(i));
      }
      graph->SetLineWidth(2);
      result_stack->Add(graph);
      legend->AddEntry(graph, graph->GetTitle(), "P");
      ratios.at(i).SetSetting(Qn::Stats::Settings::CORRELATEDERRORS);
      graph = Qn::DataContainerHelper::ToTGraph(ratios.at(i));
      graph->SetMarkerStyle(marker_styles_.at(i));
      graph->SetMarkerSize(1.6);
      graph->SetLineWidth(3);
      ratio_stack->Add(graph);
      if( i<marker_styles_.size() )
        graph->SetMarkerStyle(marker_styles_.at(i));
      if( i<marker_colors_.size() ){
        graph->SetMarkerColor(marker_colors_.at(i));
        graph->SetLineColor(marker_colors_.at(i));
      }
    }

    result_pad->cd();
    result_pad->SetBottomMargin(0);
    if(marker_colors_.empty())
      result_stack->Draw("AP+PMC+PLC");
    else
      result_stack->Draw("AP+E5");
    legend->Draw();
    result_stack->GetHistogram()->SetLabelSize(0.035, "Y");
    if (result_plot_range_.at(0) != result_plot_range_.at(1)) {
      result_stack->GetHistogram()->SetMinimum(result_plot_range_.at(0));
      result_stack->GetHistogram()->SetMaximum(result_plot_range_.at(1));
    }
    if(x_axis_range_.size() == 2)
      result_stack->GetXaxis()->SetLimits(x_axis_range_.at(0), x_axis_range_.at(1));
    ratio_pad->cd();
    ratio_pad->SetTopMargin(0);
    ratio_pad->SetBottomMargin(0.25);
    if(marker_colors_.empty())
      ratio_stack->Draw("AP+PMC+PLC");
    else
      ratio_stack->Draw("AP+E5");
    line->Draw("same");
    ratio_stack->GetHistogram()->SetLabelSize(0.065, "X");
    ratio_stack->GetHistogram()->SetLabelSize(0.065, "Y");
    if (ratio_plot_range_.at(0) != ratio_plot_range_.at(1)) {
      ratio_stack->GetHistogram()->SetMinimum(ratio_plot_range_.at(0));
      ratio_stack->GetHistogram()->SetMaximum(ratio_plot_range_.at(1));
    }
    if(x_axis_range_.size() == 2)
      ratio_stack->GetXaxis()->SetLimits(x_axis_range_.at(0), x_axis_range_.at(1));
    canvas->cd();
    result_pad->Draw();
    legend->Draw();
    ratio_pad->Draw();
    canvas->Draw();
  }
  void DrawContainers(TCanvas *canvas,
                      std::vector<Qn::DataContainer<Qn::Stats>> results){
    gStyle->SetPadLeftMargin(0.15);
    gStyle->SetTitleSize(0.08,"X");
    gStyle->SetTitleSize(0.04,"Y");
    gStyle->SetTitleOffset(1.6,"Y");
    gStyle->SetTitleOffset(1.0,"X");
    TLegend* legend = nullptr;
    if( !legend_positon_.empty() )
      legend = new TLegend(legend_positon_.at(0), legend_positon_.at(1),
                           legend_positon_.at(2), legend_positon_.at(3));
    else
      legend = new TLegend(0.35, 0.0, 0.7, 0.35);
    legend->SetBorderSize(0);
    std::string pad_name = name_ + "_result";
    auto stack_title = ";" + x_axis_title_ + ";" + y_axis_title_;
    auto result_stack = new TMultiGraph("result", stack_title.data());
    TGraphAsymmErrors *graph = nullptr;
    graph->SetMarkerSize(1.6);
    graph->SetLineWidth(2);
    result_stack->Add(graph);
    for (size_t i = 0; i < results.size(); i++) {
      results.at(i).SetSetting(Qn::Stats::Settings::CORRELATEDERRORS);
      graph = Qn::DataContainerHelper::ToTGraph(results.at(i));
      graph->SetTitle(titles_.at(i).data());
      graph->SetMarkerSize(1.6);
      if( i<marker_styles_.size() )
        graph->SetMarkerStyle(marker_styles_.at(i));
      if( i<marker_colors_.size() ){
        graph->SetMarkerColor(marker_colors_.at(i));
        graph->SetLineColor(marker_colors_.at(i));
      }
      graph->SetLineWidth(2);
      result_stack->Add(graph);
      legend->AddEntry(graph, graph->GetTitle(), "P");
      if( i<marker_styles_.size() )
        graph->SetMarkerStyle(marker_styles_.at(i));
      if( i<marker_colors_.size() ){
        graph->SetMarkerColor(marker_colors_.at(i));
        graph->SetLineColor(marker_colors_.at(i));
      }
    }
    if(marker_colors_.empty())
      result_stack->Draw("AP+PMC+PLC");
    else
      result_stack->Draw("AP+E5");
    legend->Draw();
    result_stack->GetHistogram()->SetLabelSize(0.035, "Y");
    if (result_plot_range_.at(0) != result_plot_range_.at(1)) {
      result_stack->GetHistogram()->SetMinimum(result_plot_range_.at(0));
      result_stack->GetHistogram()->SetMaximum(result_plot_range_.at(1));
    }
    if(x_axis_range_.size() == 2)
      result_stack->GetXaxis()->SetLimits(x_axis_range_.at(0), x_axis_range_.at(1));
    canvas->cd();
    legend->Draw();
    canvas->Draw();
  }
  void SetXAxisTitle(const std::string &xAxisTitle) {
    x_axis_title_ = xAxisTitle;
  }
  void SetYAxisTitle(const std::string &yAxisTitle) {
    y_axis_title_ = yAxisTitle;
  }
  void SetLegendPositon(const std::vector<float> &legendPositon) {
    legend_positon_ = legendPositon;
  }

private:
  Painter() = default;
  std::string name_;
  std::string x_axis_title_;
  std::string y_axis_title_;
  std::vector<std::string> titles_;
  std::vector<int> marker_styles_{};
  std::vector<int> marker_colors_{};
  std::vector<float> x_axis_range_{};
  std::vector<float> result_plot_range_{0.0, 0.0};
  std::vector<float> ratio_plot_range_{0.0, 0.0};
  std::vector<float> legend_positon_{};
};

#endif // QNDRAWER_PAINTER_H
