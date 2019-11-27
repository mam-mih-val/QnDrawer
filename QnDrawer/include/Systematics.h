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
  std::vector<TMultiGraph*> DrawSubEvents(std::string title=";pt, [GeV/c]; v_{1}"){
    std::vector<TMultiGraph*> vec;
    auto stack = new TMultiGraph("sub_events", title.data());
    auto ratio = new TMultiGraph("ratio", title.data());
    return vec;
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
};

#endif // QNDRAWER_SYSTEMATICS_H
