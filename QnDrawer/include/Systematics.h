//
// Created by mikhail on 26.11.2019.
//

#ifndef QNDRAWER_SYSTEMATICS_H
#define QNDRAWER_SYSTEMATICS_H

#include "FlowHelper.h"
#include <DataContainer.h>
#include <Stats.h>
#include <TMultiGraph.h>
#include <utility>
#include <vector>

class Systematics {
public:
  Systematics() = default;
  explicit Systematics(std::string name) : name_(std::move(name)) {}
  virtual ~Systematics() = default;
  void Init(
      const std::string& prefix,
      const std::vector<std::string>& subEventsNames,
      const std::vector<std::string>&componentsNames){
    {
      sub_events_names_ = subEventsNames;
      components_names_ = componentsNames;
      std::vector<std::string> for_merge;
      for( const auto& component : componentsNames )
        for( const auto& sub_event : subEventsNames )
          for_merge.push_back(prefix+sub_event+component);
      flow_helper_.Merge(for_merge, "merged");
      averaged_=flow_helper_.MakeComputations( {"merged"}, rebin_projection_, "averaged" );
    }
    for( const auto& sub_event : subEventsNames ){
      std::vector<std::string> for_merge;
      for_merge.reserve(componentsNames.size());
      for( const auto& component : componentsNames){
        for_merge.push_back(prefix+sub_event+component);
      }
      flow_helper_.Merge(for_merge, sub_event+"_merged");
      sub_events_.push_back( flow_helper_.MakeComputations({sub_event+"_merged"}, rebin_projection_, sub_event) );
      ratio_sub_events_.push_back( flow_helper_.Ratio({ "averaged", sub_event }, "ratio_"+sub_event) );
    }
    for( const auto& component : componentsNames ){
      std::vector<std::string> for_merge;
      for_merge.reserve(subEventsNames.size());
      for( const auto& sub_event : subEventsNames ){
        for_merge.push_back(prefix+sub_event+component);
      }
      flow_helper_.Merge(for_merge, component+"_merged");
      components_.push_back( flow_helper_.MakeComputations({component+"_merged"}, rebin_projection_, component) );
      ratio_components_.push_back( flow_helper_.Ratio({ "averaged", component }, "ratio_"+component) );
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
  void SaveToFile(TFile* file){
    file->cd();
    std::string save_name = name_+"_averaged";
    averaged_.Write(save_name.data());
    int i=0;
    for(const auto& sub_event : sub_events_){
      save_name=name_+sub_events_names_.at(i);
      sub_event.Write(save_name.data());
      i++;
    }
    i=0;
    for(const auto& ratio : ratio_sub_events_){
      save_name=name_+sub_events_names_.at(i)+"_ratio";
      ratio.Write(save_name.data());
      i++;
    }
    i=0;
    for(const auto&component : components_){
      save_name=name_+components_names_.at(i);
      component.Write(save_name.data());
      i++;
    }
    i=0;
    for(const auto& ratio : ratio_components_){
      save_name=name_+components_names_.at(i)+"ratio_";
      ratio.Write(save_name.data());
      i++;
    }
  }
  void SetCompareGraph(TGraphErrors *compareGraph) {
    compare_graph_ = compareGraph;
  }
  void SaveGraphsToFile(TFile* file){
    file->cd();
    TGraphAsymmErrors* graph{nullptr};
    std::string save_name = name_+"_averaged";
    averaged_.SetSetting(Qn::Stats::Settings::CORRELATEDERRORS);
    graph = Qn::DataContainerHelper::ToTGraph( averaged_ );
    graph->Write(save_name.data());
    int i=0;
    for(auto& sub_event : sub_events_){
      save_name=name_+sub_events_names_.at(i);
      sub_event.SetSetting(Qn::Stats::Settings::CORRELATEDERRORS);
      graph = Qn::DataContainerHelper::ToTGraph( sub_event );
      graph->Write(save_name.data());
      i++;
    }
    i=0;
    for(auto& ratio : ratio_sub_events_){
      save_name=name_+sub_events_names_.at(i)+"_ratio";
      ratio.SetSetting(Qn::Stats::Settings::CORRELATEDERRORS);
      graph = Qn::DataContainerHelper::ToTGraph( ratio );
      graph->Write(save_name.data());
      i++;
    }
    i=0;
    for(auto& component : components_){
      save_name=name_+components_names_.at(i);
      component.SetSetting(Qn::Stats::Settings::CORRELATEDERRORS);
      graph = Qn::DataContainerHelper::ToTGraph( component );
      graph->Write(save_name.data());
      i++;
    }
    i=0;
    for(auto& ratio : ratio_components_){
      save_name=name_+components_names_.at(i)+"ratio_";
      ratio.SetSetting(Qn::Stats::Settings::CORRELATEDERRORS);
      graph = Qn::DataContainerHelper::ToTGraph( ratio );
      graph->Write(save_name.data());
      i++;
    }
  }
  void DrawSystematics(TCanvas* canvas,
    std::vector<Qn::DataContainer<Qn::Stats>> results,
    std::vector<Qn::DataContainer<Qn::Stats>> ratios,
    std::vector<std::string> results_names)
  {
    std::string pad_name = name_+"_result";
    auto result_pad = new TPad(pad_name.data(), "result", 0.0, 0.35, 1.0, 1.0);
    auto result_stack = new TMultiGraph( "result", "" );
    pad_name = name_+"_ratio";
    auto ratio_pad = new TPad(pad_name.data(), "ratio", 0.0, 0.0, 1.0, .35);
    auto ratio_stack = new TMultiGraph( "ratio", "" );
    TGraphAsymmErrors *graph;
    averaged_.SetSetting(Qn::Stats::Settings::CORRELATEDERRORS);
    graph = Qn::DataContainerHelper::ToTGraph( averaged_ );
    graph->SetTitle( "averaged" );
    if(compare_graph_)
      result_stack->Add(compare_graph_);
    result_stack->Add(graph);
    auto averaged_ratio = flow_helper_.Ratio({"averaged", "averaged"}, "ref_ratio");
    averaged_ratio.SetSetting(Qn::Stats::Settings::CORRELATEDERRORS);
    graph = Qn::DataContainerHelper::ToTGraph( averaged_ratio );
    ratio_stack->Add(graph);
    for(int i=0; i<results.size(); i++){
      results.at(i).SetSetting(Qn::Stats::Settings::CORRELATEDERRORS);
      graph = Qn::DataContainerHelper::ToTGraph( results.at(i) );
      graph->SetTitle( results_names.at(i).data() );
      result_stack->Add(graph);
      ratios.at(i).SetSetting(Qn::Stats::Settings::CORRELATEDERRORS);
      graph = Qn::DataContainerHelper::ToTGraph( ratios.at(i) );
      ratio_stack->Add(graph);
    }
    result_pad->cd();
    result_pad->SetBottomMargin(0);
    result_stack->Draw("AP+PMC+PLC");
    result_pad->BuildLegend();
    result_stack->GetHistogram()->SetLabelSize(0.043, "Y");
    result_stack->GetHistogram()->SetMinimum(-0.29);
    result_stack->GetHistogram()->SetMaximum(0.0);
    ratio_pad->cd();
    ratio_pad->SetTopMargin(0);
    ratio_pad->SetBottomMargin(0.25);
    ratio_stack->Draw("AP+PMC+PLC");
    ratio_stack->GetHistogram()->SetLabelSize(0.08, "X");
    ratio_stack->GetHistogram()->SetLabelSize(0.08, "Y");
    ratio_stack->GetHistogram()->SetMinimum(0.81);
    ratio_stack->GetHistogram()->SetMaximum(1.19);
    canvas->cd();
    result_pad->Draw();
    ratio_pad->Draw();
    canvas->Draw();
  }
  void DrawSubEvents(TCanvas* canvas){
    DrawSystematics(canvas, sub_events_, ratio_sub_events_, sub_events_names_);
  }
  void DrawComponents(TCanvas* canvas){
    DrawSystematics(canvas, components_, ratio_components_, components_names_);
  }
private:
  std::string name_;
  FlowHelper flow_helper_;
  std::function<Qn::DataContainer<Qn::Stats>(std::vector<Qn::DataContainer<Qn::Stats>>)> rebin_projection_ =
      [](std::vector<Qn::DataContainer<Qn::Stats>> container){ return container.at(0); };
  Qn::DataContainer<Qn::Stats> averaged_;
  std::vector<Qn::DataContainer<Qn::Stats>> sub_events_;
  std::vector<Qn::DataContainer<Qn::Stats>> components_;
  std::vector<Qn::DataContainer<Qn::Stats>> ratio_sub_events_;
  std::vector<Qn::DataContainer<Qn::Stats>> ratio_components_;
  std::vector<std::string> sub_events_names_;
  std::vector<std::string> components_names_;
  TGraphErrors* compare_graph_{nullptr};
};

#endif // QNDRAWER_SYSTEMATICS_H
