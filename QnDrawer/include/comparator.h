//
// Created by mikhail on 09.11.2019.
//

#ifndef QNDRAWER_COMPARATOR_H
#define QNDRAWER_COMPARATOR_H

#include "flow_helper.h"
#include <DataContainer.h>
#include <Stats.h>
#include <TCanvas.h>
#include <TGraphAsymmErrors.h>
#include <THStack.h>
#include <TStyle.h>
#include <utility>
#include <vector>

class Comparator {
public:
  Comparator() = default;
  explicit Comparator(std::string name) : name_(std::move(name)) {}
  ~Comparator() = default;
  void AddGraph(TGraph* graph, const std::string& graph_title="graph", const std::vector<int>& marker={}){
    if(!graphs_)
      graphs_ = new TMultiGraph("stack", "");
    graph->SetTitle(graph_title.data());
    if( !marker.empty() ){
      graph->SetMarkerStyle(marker.at(0));
      graph->SetMarkerColor(marker.at(1));
      graph->SetLineColor(marker.at(1));
      graph->SetMarkerSize(marker_size_);
      graph->SetLineWidth(line_width_);
    }
    graphs_->Add(graph);
  }
  void AddTh1(TH1* histo, const std::vector<int>& marker={}){
    if(!histos_)
      histos_ = new THStack("histo_stack", "");
    histos_->Add(histo);
    if( !marker.empty() ){
      histo->SetMarkerStyle(marker.at(0));
      histo->SetMarkerColor(marker.at(1));
      histo->SetLineColor(marker.at(1));
      histo->SetMarkerSize(marker_size_);
      histo->SetLineWidth(line_width_);
    }
  }
  void AddFile(const std::string& file_name_){ flow_helpers_.emplace( file_name_, file_name_ ); }
  void AddFile(TFile* file, const std::string& file_name_){ flow_helpers_.emplace( file_name_, file ); }
  void MergeAddContainers(const std::string& file_name_,
      const std::vector<std::string>& container_names,
      const std::string& graph_title,
      const std::vector<int>& marker={}){
    Qn::DataContainer<Qn::Stats> container{ flow_helpers_.at(file_name_).Merge(container_names) };
    AddContainer(container, graph_title, marker);
  }
  void AddContainer( Qn::DataContainer<Qn::Stats> container, const std::string& title, const std::vector<int>& marker={}){
    TGraphAsymmErrors* graph{nullptr};
    if( rebin_projection_ ){
      container = rebin_projection_(container);
    }
    container.SetSetting(Qn::Stats::Settings::CORRELATEDERRORS);
    graph = Qn::DataContainerHelper::ToTGraph( container );
    AddGraph(graph, title, marker);
  }
  void Draw(){
    canvas_->cd();
    gStyle->SetLegendBorderSize(0);
    gStyle->SetPadLeftMargin(0.0);
    gStyle->SetTitleSize(0.035,"X");
    gStyle->SetTitleSize(0.035,"Y");
    gStyle->SetTitleOffset(1.8,"Y");
    gStyle->SetTitleOffset(1.0,"X");
    gStyle->SetErrorX(0);
    gPad->SetLeftMargin(0.15);
    if( graphs_ ){
      graphs_->Draw();
      std::string title = ";"+x_axis_title_+";"+y_axis_title_;
      graphs_->SetTitle(title.data());
      if( !y_axis_range_.empty() ){
        graphs_->GetHistogram()->SetMinimum(y_axis_range_.at(0));
        graphs_->GetHistogram()->SetMaximum(y_axis_range_.at(1));
      }
      if( !x_axis_range_.empty() )
        graphs_->GetXaxis()->SetLimits(x_axis_range_.at(0), x_axis_range_.at(1));
      graphs_->Draw("AP+E5");
    }
    if( histos_ )
      histos_->Draw("SAME+NOSTACK");

    if( histos_ && !graphs_ )
      histos_->Draw("NOSTACK");
    if( !legend_position_.empty() )
      gPad->BuildLegend(legend_position_.at(0),
                      legend_position_.at(1),
                      legend_position_.at(2),
                      legend_position_.at(3));
    else
      gPad->BuildLegend();
  }
  void SetCanvas(TCanvas *canvas) { canvas_ = canvas; }
  TCanvas *GetCanvas() const { return canvas_; }
  TMultiGraph *GetGraphs() const { return graphs_; }
  void SetGraphs(TMultiGraph *graphs) { graphs_ = graphs; }
  void SetRebinProjection(
      const std::function<Qn::DataContainer<Qn::Stats>(Qn::DataContainer<Qn::Stats>)>
          &rebinProjection) {
    rebin_projection_ = rebinProjection;
  }
  void SetXAxisTitle(const std::string &xAxisTitle) {
    x_axis_title_ = xAxisTitle;
  }
  void SetYAxisTitle(const std::string &yAxisTitle) {
    y_axis_title_ = yAxisTitle;
  }
  void SetXAxisRange(const std::vector<float> &xAxisRange) {
    x_axis_range_ = xAxisRange;
  }
  void SetYAxisRange(const std::vector<float> &yAxisRange) {
    y_axis_range_ = yAxisRange;
  }
  void SetLegendPosition(const std::vector<float> &legendPosition) {
    legend_position_ = legendPosition;
  }
  void SetMarkerSize(float markerSize) { marker_size_ = markerSize; }
  void SetLineWidth(float lineWidth) { line_width_ = lineWidth; }

private:
  std::string name_;
  float marker_size_{2.0};
  float line_width_{2.0};
  std::string x_axis_title_;
  std::string y_axis_title_;
  std::vector<float> legend_position_{};
  std::vector<float> x_axis_range_{};
  std::vector<float> y_axis_range_{};
  std::function<Qn::DataContainer<Qn::Stats>(Qn::DataContainer<Qn::Stats>)>
      rebin_projection_ = {};
  std::map<std::string, FlowHelper> flow_helpers_;
  TMultiGraph* graphs_{nullptr};
  THStack* histos_{nullptr};
  TCanvas* canvas_;
  // ClassDef(Comparator, 1);
};

#endif // QNDRAWER_COMPARATOR_H
