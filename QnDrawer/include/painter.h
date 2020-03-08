//
// Created by mikhail on 2/20/20.
//

#ifndef QNDRAWER_PAINTER_H
#define QNDRAWER_PAINTER_H

#include <DataContainer.h>
#include <Stats.h>
#include <TLegend.h>
#include <TProfile2D.h>
#include <TStyle.h>
#include <string>
#include <utility>
#include <vector>

class Painter {
public:
  Painter() = default;
  explicit Painter(std::string name) : name_(std::move(name)) {}
  virtual ~Painter() = default;
public:
  void SetTitles(const std::vector<std::string> &titles) {
    titles_ = titles;
  }
  void SetMarkerStyles(const std::vector<int> &markerStyles) {
    marker_styles_ = markerStyles;
  }
  void SetMarkerColors(const std::vector<int> &markerColors) {
    marker_colors_ = markerColors;
  }
  void SetXAxisRange(const std::vector<float> &xAxisRange) {
    x_axis_range_ = xAxisRange;
  }
  void SetResultPlotRange(const std::vector<float> &resultPlotRange) {
    result_plot_range_ = resultPlotRange;
  }
  void SetRatioPlotRange(const std::vector<float> &ratioPlotRange) {
    ratio_plot_range_ = ratioPlotRange;
  }
  void SetAxisTitles(const std::string &xAxisTitle,
                     const std::string &yAxisTitle) {
    x_axis_title_ = xAxisTitle;
    y_axis_title_ = yAxisTitle;
  }
  void SetXAxisTitle(const std::string &xAxisTitle) {
    x_axis_title_ = xAxisTitle;
  }
  void SetYAxisTitle(const std::string &yAxisTitle) {
    y_axis_title_ = yAxisTitle;
  }
  void SetLegendPosition(const std::vector<float> &legendPositon) {
    legend_position_ = legendPositon;
  }
  void SetCanvas(const std::shared_ptr<TCanvas> &canvas) { canvas_ = canvas; }
  void SetLegend(TLegend *legend) { legend_ = legend; }

protected:
  TLegend* legend_{nullptr};
  void DrawWithRatio( TMultiGraph* result_stack, TMultiGraph* ratio_stack ){
    std::string pad_name = name_ + "_result";
    auto result_pad = new TPad(pad_name.data(), "result", 0.0, 0.35, 1.0, 1.0);
    auto stack_title = ";" + x_axis_title_ + ";" + y_axis_title_;
    pad_name = name_ + "_ratio";
    stack_title = ";" + x_axis_title_;
    auto ratio_pad = new TPad(pad_name.data(), "ratio", 0.0, 0.0, 1.0, .35);
    TF1* line_ratio;
    TF1* line_result;
    if( x_axis_range_.size() == 2 ){
      line_ratio = new TF1("line_ratio", "1", x_axis_range_.at(0), x_axis_range_.at(1));
      line_result = new TF1("line_result", "0", x_axis_range_.at(0), x_axis_range_.at(1));
    }
    else{
      line_ratio = new TF1("line_ratio", "1", -100, 100);
      line_result = new TF1("line_result", "0", -100, 100);
    }

    result_pad->cd();
    result_pad->SetBottomMargin(0);
    if(marker_colors_.empty())
      result_stack->Draw("AP+PMC+PLC");
    else
      result_stack->Draw("AP+E5");
    gPad->BuildLegend(legend_position_.at(0), legend_position_.at(1),
                      legend_position_.at(2), legend_position_.at(3),
                      "","P");
    line_result->Draw("same");
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
    line_ratio->Draw("same");
    ratio_stack->GetHistogram()->SetLabelSize(0.065, "X");
    ratio_stack->GetHistogram()->SetLabelSize(0.065, "Y");
    if (ratio_plot_range_.at(0) != ratio_plot_range_.at(1)) {
      ratio_stack->GetHistogram()->SetMinimum(ratio_plot_range_.at(0));
      ratio_stack->GetHistogram()->SetMaximum(ratio_plot_range_.at(1));
    }
    if(x_axis_range_.size() == 2)
      ratio_stack->GetXaxis()->SetLimits(x_axis_range_.at(0), x_axis_range_.at(1));
    if( !canvas_ ){
      std::cout << "Canvas is not set" << std::endl;
      abort();
    }
    canvas_->cd();
    result_pad->Draw();
    ratio_pad->Draw();
    canvas_->Draw();
  }
  std::string name_;
  std::shared_ptr<TCanvas> canvas_{nullptr};
  std::string x_axis_title_;
  std::string y_axis_title_;
  std::vector<std::string> titles_;
  std::vector<int> marker_styles_{};
  std::vector<int> marker_colors_{};
  std::vector<float> x_axis_range_{};
  std::vector<float> result_plot_range_{0.0, 0.0};
  std::vector<float> ratio_plot_range_{0.0, 0.0};
  std::vector<float> legend_position_{};
};

#endif // QNDRAWER_PAINTER_H
