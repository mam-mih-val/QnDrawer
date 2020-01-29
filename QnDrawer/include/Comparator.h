//
// Created by mikhail on 09.11.2019.
//

#ifndef QNDRAWER_COMPARATOR_H
#define QNDRAWER_COMPARATOR_H

#include "FlowHelper.h"
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
  void AddGraph(TGraph* graph, const std::string& graph_title="graph"){
    if(!graphs_)
      graphs_ = new TMultiGraph("stack", "");
    graph->SetTitle(graph_title.data());
    graphs_->Add(graph);
  }
  void AddTh1(TH1* histo){
    if(!histos_)
      histos_ = new THStack("histo_stack", "");
    histos_->Add(histo);
  }
  void AddFile(const std::string& file_name_){ flow_helpers_.emplace( file_name_, file_name_ ); }
  void AddFile(TFile* file, const std::string& file_name_){ flow_helpers_.emplace( file_name_, file ); }
  void PutOnCanvas( const std::string& file_name_, const std::string& container_name, const std::string& graph_title="graph" ){
    Qn::DataContainer<Qn::Stats> container{ flow_helpers_.at(file_name_).GetDataContainer(container_name) };
    container.SetSetting(Qn::Stats::Settings::CORRELATEDERRORS);
    auto graph = Qn::DataContainerHelper::ToTGraph( container );
    AddGraph(graph, graph_title);
  }
  void PutOnCanvas( const std::string& file_name_, const std::vector<std::string>& container_names, const std::vector<std::string>& container_titles ){
    for( size_t i=0; i<container_names.size(); i++ ){
      PutOnCanvas(file_name_, container_names.at(i), container_titles.at(i));
    }
  }
  void MergeAndPutOnCanvas(const std::string& file_name_, const std::vector<std::string>& container_names, const std::string& graph_title){
    Qn::DataContainer<Qn::Stats> container{ flow_helpers_.at(file_name_).Merge(container_names) };
    container.SetSetting(Qn::Stats::Settings::CORRELATEDERRORS);
    auto graph = Qn::DataContainerHelper::ToTGraph( container );
    AddGraph(graph, graph_title);
  }
  void PutOnCanvas( Qn::DataContainer<Qn::Stats>& container, const std::string& title ){
    TGraphAsymmErrors* graph{nullptr};;
    container.SetSetting(Qn::Stats::Settings::CORRELATEDERRORS);
    graph = Qn::DataContainerHelper::ToTGraph( container );
    graph->SetTitle(title.data());
    graphs_->Add(graph);
  }
  void PutOnCanvas( std::vector<Qn::DataContainer<Qn::Stats>>& containers, std::vector<std::string> titles ){
    for(size_t i=0; i<containers.size(); i++){
      PutOnCanvas(containers.at(i), titles.at(i));
    }
  }
  void Draw(){
    SetStyle();
    canvas_->cd();
    if( graphs_ )
      graphs_->Draw("AP+PMC+PLC+NOSTACK");
    if( histos_ )
      histos_->Draw("NOSTACK+SAME");
    gPad->BuildLegend();
  }
  void SetCanvas(TCanvas *canvas) { canvas_ = canvas; }
  TCanvas *GetCanvas() const { return canvas_; }
  TMultiGraph *GetGraphs() const { return graphs_; }
  void SetGraphs(TMultiGraph *graphs) { graphs_ = graphs; }

private:
  void SetStyle(){
    gStyle->SetTitleSize(0.04,"T");
    gStyle->SetTitleSize(0.035,"X");
    gStyle->SetTitleSize(0.04,"Y");
    gStyle->SetTitleSize(0.035,"Z");
    gStyle->SetTitleOffset(1.6,"Y");
    gStyle->SetTitleOffset(1.0,"X");
    gStyle->SetFrameLineWidth(2);
    gStyle->SetFrameFillColor(0);
    gStyle->SetPadColor(0);
    gStyle->SetLabelSize(0.03,"X");
    gStyle->SetLabelSize(0.03,"Y");
    gStyle->SetLabelSize(0.03,"Z");
    gStyle->SetPadTopMargin(0.1);
    gStyle->SetPadBottomMargin(0.18);
    gStyle->SetPadLeftMargin(0.15);
    gStyle->SetPadRightMargin(0.15);
    gStyle->SetMarkerSize(2.0);
    gStyle->SetErrorX(0);
    gStyle->SetOptStat(0);
    gStyle->SetCanvasColor(0);
    gStyle->SetTitleFillColor(0);
    gStyle->SetTitleBorderSize(0);
    gStyle->SetHistLineWidth(3);
    gStyle->SetLineWidth(3);
    gStyle->SetCanvasBorderMode(0);
    gStyle->SetLegendBorderSize(0);
    gStyle->SetPadBorderMode(0);
    gStyle->SetEndErrorSize(5);
    gStyle->SetPadTickX(1);
    gStyle->SetPadTickY(1);
    gStyle->SetMarkerSize(2);
    gStyle->SetLineWidth(4);
  }
  std::string name_;
  std::map<std::string, FlowHelper> flow_helpers_;
  TMultiGraph* graphs_{nullptr};
  THStack* histos_{nullptr};
  TCanvas* canvas_;
  // ClassDef(Comparator, 1);
};

#endif // QNDRAWER_COMPARATOR_H
