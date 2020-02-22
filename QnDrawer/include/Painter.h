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
  const SetXAxisRange(const std::vector<float> &xAxisRange) {
    x_axis_range_ = xAxisRange;
  }
  void SetResultPlotRange(const std::vector<float> &resultPlotRange) {
    result_plot_range_ = resultPlotRange;
  }
  void SetRatioPlotRange(const std::vector<float> &ratioPlotRange) {
    ratio_plot_range_ = ratioPlotRange;
  }
  void Draw(TCanvas *canvas) {
    gStyle->SetPadLeftMargin(0.15);
    gStyle->SetTitleSize(0.08,"X");
    gStyle->SetTitleSize(0.04,"Y");
    gStyle->SetTitleOffset(1.6,"Y");
    gStyle->SetTitleOffset(1.0,"X");
    TLegend* legend = nullptr;
    THStack* stack = nullptr;
    TMultiGraph* graph = nullptr;
    if( !legend_positon_.empty() )
      legend = new TLegend(legend_positon_.at(0), legend_positon_.at(1),
                           legend_positon_.at(2), legend_positon_.at(3));
    else
      legend = new TLegend(0.35, 0.0, 0.7, 0.35);

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
  std::string name_;
  std::vectot<TH1*> histograms_;
  std::vector<TGraph*> tgraphs_;
  std::vector<Qn::DataContainer<Qn::Stats>> containers_;
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
