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
#include <utility>
#include <vector>
class Comparator {
public:
  Comparator() = default;
  explicit Comparator(std::vector<std::string> name) : name_(std::move(name)) {}
  ~Comparator() = default;
  void AddGraph(TGraph* graph, const std::string& graph_title="graph"){
    graph->SetTitle(graph_title.data());
    graphs_->Add(graph);
  }
  void AddFile(std::string file_name_){ flow_helpers_.emplace( file_name_, file_name_ ); }
  void PutOnCanvas( const std::string& file_name_, const std::string& container_name, const std::string& graph_title="graph" ){
    Qn::DataContainer<Qn::Stats> container{ flow_helpers_.at(file_name_).GetDataContainer(container_name) };
    container.SetSetting(Qn::Stats::Settings::CORRELATEDERRORS);
    auto graph = Qn::DataContainerHelper::ToTGraph( container );
    AddGraph(graph, graph_title);
  }
  void PutOnCanvas( const std::string& file_name_, const std::vector<std::string>& container_names, const std::vector<std::string>& container_titles ){
    for( int i=0; i<container_names.size(); i++ ){
      PutOnCanvas(file_name_, container_names.at(i), container_titles.at(i));
    }
  }
  void MergeAndPutOnCanvas(const std::string& file_name_, const std::vector<std::string>& container_names, const std::string& graph_title){
    Qn::DataContainer<Qn::Stats> container{ flow_helpers_.at(file_name_).Merge(container_names) };
    container.SetSetting(Qn::Stats::Settings::CORRELATEDERRORS);
    auto graph = Qn::DataContainerHelper::ToTGraph( container );
    AddGraph(graph, graph_title);
  }
  void Draw(){
    canvas_->cd();
    graphs_->Draw("AP+PMC+PLC");
  }
  void SetCanvas(TCanvas *canvas) { canvas_ = canvas; }
  TCanvas *GetCanvas() const { return canvas_; }
private:
  std::vector<std::string> name_;
  std::map<std::string, FlowHelper> flow_helpers_;
  TMultiGraph* graphs_;
  TCanvas* canvas_;

};

#endif // QNDRAWER_COMPARATOR_H
