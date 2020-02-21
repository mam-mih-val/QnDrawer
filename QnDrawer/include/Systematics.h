//
// Created by mikhail on 26.11.2019.
//

#ifndef QNDRAWER_SYSTEMATICS_H
#define QNDRAWER_SYSTEMATICS_H

#include "FlowHelper.h"
#include "Painter.h"
#include "TStyle.h"
#include <DataContainer.h>
#include <Stats.h>
#include <TF1.h>
#include <TLegend.h>
#include <TMultiGraph.h>
#include <utility>
#include <vector>

class Systematics {
public:
  Systematics() = default;
  explicit Systematics(std::string name) : name_(std::move(name)) {}
  virtual ~Systematics() = default;
  void Init(const std::string &prefix,
            const std::vector<std::string> &subEventsNames,
            const std::vector<std::string> &componentsNames) {
    {
      sub_events_names_ = subEventsNames;
      components_names_ = componentsNames;
      std::vector<std::string> for_merge;
      for (const auto &component : componentsNames)
        for (const auto &sub_event : subEventsNames)
          for_merge.push_back(prefix + sub_event + component);
      averaged_ = flow_helper_.Merge(for_merge, "merged");
      averaged_ = rebin_projection_({averaged_});
    }
    for (const auto &sub_event : subEventsNames) {
      std::vector<std::string> for_merge;
      for_merge.reserve(componentsNames.size());
      for (const auto &component : componentsNames) {
        for_merge.push_back(prefix + sub_event + component);
      }
      flow_helper_.Merge(for_merge, sub_event + "_merged");
      sub_events_.push_back(flow_helper_.Merge(for_merge, sub_event + "_merged"));
      sub_events_.back() = rebin_projection_({sub_events_.back()});
    }
    for (const auto &component : componentsNames) {
      std::vector<std::string> for_merge;
      for_merge.reserve(subEventsNames.size());
      for (const auto &sub_event : subEventsNames) {
        for_merge.push_back(prefix + sub_event + component);
      }
      components_.push_back(flow_helper_.Merge(for_merge, component + "_merged"));
      components_.back() = rebin_projection_({components_.back()});
    }
    RebuildRatios();
  }
  void RebuildRatios() {
    ratio_sub_events_.clear();
    for (const auto& sub_event : sub_events_) {
      ratio_sub_events_.push_back(sub_event / averaged_);
    }
    ratio_components_.clear();
    for (const auto& component : components_) {
      ratio_components_.push_back(component / averaged_);
    }
  }
  FlowHelper &GetFlowHelper() { return flow_helper_; }
  void SetFlowHelper(FlowHelper &flowHelper) { flow_helper_ = flowHelper; }
  const std::string &GetName() const { return name_; }
  const Qn::DataContainer<Qn::Stats> &GetAveraged() const { return averaged_; }
  const std::vector<Qn::DataContainer<Qn::Stats>> &GetSubEvents() const {
    return sub_events_;
  }
  const std::vector<Qn::DataContainer<Qn::Stats>> &GetComponents() const {
    return components_;
  }
  const std::vector<Qn::DataContainer<Qn::Stats>> &GetRatioSubEvents() const {
    return ratio_sub_events_;
  }
  const std::vector<Qn::DataContainer<Qn::Stats>> &GetRatioComponents() const {
    return ratio_components_;
  }
  void SetName(const std::string &name) { name_ = name; }
  void SetRebinProjection(
      const std::function<Qn::DataContainer<Qn::Stats>(
          std::vector<Qn::DataContainer<Qn::Stats>>)> &rebinProjection) {
    rebin_projection_ = rebinProjection;
  }
  void SetDefault(const Qn::DataContainer<Qn::Stats> &averaged) {
    averaged_ = averaged;
    RebuildRatios();
  }
  void SaveToFile(TFile *file) {
    file->cd();
    std::string save_name = name_ + "_averaged";
    averaged_.Write(save_name.data());
    int i = 0;
    for (const auto &sub_event : sub_events_) {
      save_name = name_ + sub_events_names_.at(i);
      sub_event.Write(save_name.data());
      i++;
    }
    i = 0;
    for (const auto &ratio : ratio_sub_events_) {
      save_name = name_ + sub_events_names_.at(i) + "_ratio";
      ratio.Write(save_name.data());
      i++;
    }
    i = 0;
    for (const auto &component : components_) {
      save_name = name_ + components_names_.at(i);
      component.Write(save_name.data());
      i++;
    }
    i = 0;
    for (const auto &ratio : ratio_components_) {
      save_name = name_ + components_names_.at(i) + "ratio_";
      ratio.Write(save_name.data());
      i++;
    }
  }
  void SetCompareGraph(TGraph *compareGraph) { compare_graph_ = compareGraph; }
  void SetSubEventsNames(const std::vector<std::string> &subEventsNames) {
    sub_events_names_ = subEventsNames;
  }
  void SetComponentsNames(const std::vector<std::string> &componentsNames) {
    components_names_ = componentsNames;
  }
  void SaveGraphsToFile(TFile *file) {
    file->cd();
    TGraphAsymmErrors *graph{nullptr};
    std::string save_name = name_ + "_averaged";
    averaged_.SetSetting(Qn::Stats::Settings::CORRELATEDERRORS);
    graph = Qn::DataContainerHelper::ToTGraph(averaged_);
    graph->Write(save_name.data());
    int i = 0;
    for (auto &sub_event : sub_events_) {
      save_name = name_ + sub_events_names_.at(i);
      sub_event.SetSetting(Qn::Stats::Settings::CORRELATEDERRORS);
      graph = Qn::DataContainerHelper::ToTGraph(sub_event);
      graph->Write(save_name.data());
      i++;
    }
    i = 0;
    for (auto &ratio : ratio_sub_events_) {
      save_name = name_ + sub_events_names_.at(i) + "_ratio";
      ratio.SetSetting(Qn::Stats::Settings::CORRELATEDERRORS);
      graph = Qn::DataContainerHelper::ToTGraph(ratio);
      graph->Write(save_name.data());
      i++;
    }
    i = 0;
    for (auto &component : components_) {
      save_name = name_ + components_names_.at(i);
      component.SetSetting(Qn::Stats::Settings::CORRELATEDERRORS);
      graph = Qn::DataContainerHelper::ToTGraph(component);
      graph->Write(save_name.data());
      i++;
    }
    i = 0;
    for (auto &ratio : ratio_components_) {
      save_name = name_ + components_names_.at(i) + "ratio_";
      ratio.SetSetting(Qn::Stats::Settings::CORRELATEDERRORS);
      graph = Qn::DataContainerHelper::ToTGraph(ratio);
      graph->Write(save_name.data());
      i++;
    }
  }
  void DrawSystematics(TCanvas *canvas,
                       std::vector<Qn::DataContainer<Qn::Stats>> results,
                       std::vector<Qn::DataContainer<Qn::Stats>> ratios,
                       std::vector<std::string> results_names) {
    gStyle->SetPadLeftMargin(0.15);
    gStyle->SetTitleSize(0.08,"X");
    gStyle->SetTitleSize(0.04,"Y");
    gStyle->SetTitleOffset(1.6,"Y");
    gStyle->SetTitleOffset(1.0,"X");
    TLegend* legend;
    if( !legend_position_.empty() )
      legend = new TLegend(legend_position_.at(0), legend_position_.at(1),
                           legend_position_.at(2), legend_position_.at(3));
    else
      legend = new TLegend(0.5, 0.5, 0.9, 0.9);
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
    TGraphAsymmErrors *graph;
    averaged_.SetSetting(Qn::Stats::Settings::CORRELATEDERRORS);
    graph = Qn::DataContainerHelper::ToTGraph(averaged_);
    graph->SetTitle("Default");
    if( !default_title_.empty() )
      graph->SetTitle(default_title_.data() );
    graph->SetMarkerSize(2.0);
    graph->SetLineWidth(4);
    result_stack->Add(graph);
    legend->AddEntry(graph, default_title_.data(), "P");
    auto averaged_ratio = averaged_/averaged_;
    averaged_ratio.SetSetting(Qn::Stats::Settings::CORRELATEDERRORS);
    graph = Qn::DataContainerHelper::ToTGraph(averaged_ratio);
    graph->SetMarkerSize(2.0);
    graph->SetMarkerColor(kBlack);
    graph->SetLineColor(kBlack);
    ratio_stack->Add(graph);
    for (size_t i = 0; i < results.size(); i++) {
      results.at(i).SetSetting(Qn::Stats::Settings::CORRELATEDERRORS);
      graph = Qn::DataContainerHelper::ToTGraph(results.at(i));
      graph->SetTitle(results_names.at(i).data());
      graph->SetMarkerSize(2.0);
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
      graph->SetMarkerSize(2.0);
      graph->SetLineWidth(4);
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
    if(marker_colors_.size()==0)
      result_stack->Draw("AP+PMC+PLC");
    else
      result_stack->Draw("AP+E5");
    if (compare_graph_) {
      compare_graph_->SetMarkerColor(kBlack);
      compare_graph_->SetLineColor(kBlack);
      compare_graph_->Draw("same");
    }
//    result_pad->BuildLegend("P");
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
    ratio_pad->Draw();
    canvas->Draw();
  }
  void DrawSubEvents(TCanvas *canvas) {
    DrawSystematics(canvas, sub_events_, ratio_sub_events_, sub_events_names_);
  }
  void DrawComponents(TCanvas *canvas) {
    DrawSystematics(canvas, components_, ratio_components_, components_names_);
  }
  void SetResultPlotRange(const std::vector<float> &resultPlotRange) {
    result_plot_range_ = resultPlotRange;
  }
  void SetRatioPlotRange(const std::vector<float> &ratioPlotRange) {
    ratio_plot_range_ = ratioPlotRange;
  }
  void SetSubEventsTitles(const std::vector<std::string> &subEventsTitles) {
    sub_events_titles_ = subEventsTitles;
  }
  void SetComponentsTitles(const std::vector<std::string> &componentsTitles) {
    components_titles_ = componentsTitles;
  }
  void SetXAxisTitle(const std::string &xAxisTitle) {
    x_axis_title_ = xAxisTitle;
  }
  void SetYAxisTitle(const std::string &yAxisTitle) {
    y_axis_title_ = yAxisTitle;
  }
  void SetAxisTitles(const std::string &xAxisTitle,
                     const std::string &yAxisTitle) {
    x_axis_title_ = xAxisTitle;
    y_axis_title_ = yAxisTitle;
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
  void SetDefaultTitle(const std::string &defaultTitle) {
    default_title_ = defaultTitle;
  }
  void SetLegendPosition(const std::vector<float> &legendPosition) {
    legend_position_ = legendPosition;
  }

private:
  std::string name_;
  std::string x_axis_title_;
  std::string y_axis_title_;
  FlowHelper flow_helper_;
  std::function<Qn::DataContainer<Qn::Stats>(
      std::vector<Qn::DataContainer<Qn::Stats>>)>
      rebin_projection_ =
          [](std::vector<Qn::DataContainer<Qn::Stats>> container) {
            return container.at(0);
          };
  Qn::DataContainer<Qn::Stats> averaged_;
  std::vector<Qn::DataContainer<Qn::Stats>> sub_events_;
  std::vector<std::string> sub_events_titles_;
  std::string default_title_;
  std::vector<Qn::DataContainer<Qn::Stats>> components_;
  std::vector<std::string> components_titles_;
  std::vector<Qn::DataContainer<Qn::Stats>> ratio_sub_events_;
  std::vector<Qn::DataContainer<Qn::Stats>> ratio_components_;
  std::vector<std::string> sub_events_names_;
  std::vector<std::string> components_names_;
  TGraph *compare_graph_{nullptr};
  std::vector<int> marker_styles_{};
  std::vector<int> marker_colors_{};
  std::vector<float> x_axis_range_{};
  std::vector<float> result_plot_range_{0.0, 0.0};
  std::vector<float> ratio_plot_range_{0.0, 0.0};
  std::vector<float> legend_position_{};
};

#endif // QNDRAWER_SYSTEMATICS_H
