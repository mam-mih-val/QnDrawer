//
// Created by mikhail on 05.11.2019.
//

#ifndef QNDRAWER_FLOW_BUILDER_H
#define QNDRAWER_FLOW_BUILDER_H

#include <utility>

#include "correlation_mananger.h"
#include "method.h"
#include <Axis.h>
#include <iostream>
#include <string>
#include <vector>
class FlowBuilder {
public:
  FlowBuilder() = default;
  virtual ~FlowBuilder() = default;
  void SetInputName(const std::string& file_name){manager_.SetFile(file_name);}
  inline void SetConfigFileName( const std::string& file_name ){ manager_.SetConfigFile(file_name); }
  const std::string &GetName() const { return name_; }
  void SetName(const std::string &name) { name_ = name; }
  void AddMethod(const std::string& method_name,
    const std::function<Qn::DataContainer<Qn::Stats>(std::vector<Qn::DataContainer<Qn::Stats>>)>&  resolutionRule){
    methods_.emplace_back(manager_.MakeMethod(method_name) );
    methods_.back().SetResolutionRule(resolutionRule);
  }
  void ComputeMethodFast(const std::string& method_name,
    const std::function<Qn::DataContainer<Qn::Stats>(std::vector<Qn::DataContainer<Qn::Stats>>)>&  resolutionRule,
    const std::function<Qn::DataContainer<Qn::Stats>(std::vector<Qn::DataContainer<Qn::Stats>>)>&  flowRule){
    methods_.emplace_back(manager_.MakeMethod(method_name) );
    methods_.back().SetResolutionRule(resolutionRule);
    methods_.back().SetFlowRule(flowRule);
    std::cout << "Flow estimation with " << methods_.back().GetName() << std::endl;
    methods_.back().Compute();
  }
  void ComputeMethodRamSaving(const std::string& method_name,
    const std::function<Qn::DataContainer<Qn::Stats>(std::vector<Qn::DataContainer<Qn::Stats>>)>&  resolutionRule,
    const std::function<Qn::DataContainer<Qn::Stats>(std::vector<Qn::DataContainer<Qn::Stats>>)>&  flowRule,
    TFile* file_out){
    methods_.emplace_back(manager_.MakeMethod(method_name) );
    methods_.back().SetResolutionRule(resolutionRule);
    methods_.back().SetFlowRule(flowRule);
    std::cout << "Flow estimation with " << methods_.back().GetName() << std::endl;
    methods_.back().Compute();
    methods_.back().SaveToFile(file_out);
    methods_.pop_back();
  }
  void Compute(){
    for(auto &method: methods_)
    {
      std::cout << "Flow estimation with " << method.GetName() << std::endl;
      method.Compute();
    }
  }
  void Rebin(){
    for(auto &method : methods_){
      auto axis = manager_.GetRebinAxis(method.GetName());
      method.Rebin(axis);
    }
  }
  void Projection(){
    for(auto &method : methods_){
      auto axis_name = manager_.GetProjectionAxisName(method.GetName());
      method.Projection(axis_name);
    }
  }
  void SaveToFile(TFile* file){
    for(auto &method: methods_)
      method.SaveToFile(file);
  }
  void SaveToFile(const std::string& file_name){
    auto file = TFile::Open(file_name.data(), "recreate");
    for(auto &method: methods_)
      method.SaveToFile(file);
    file->Close();
    std::cout << "Built flow wrote to " << file_name << std::endl;
  }
  void SaveGraphsToFile(const std::string& file_name){
    auto file = TFile::Open(file_name.data(), "recreate");
    for(auto &method : methods_)
      method.SaveGraphsToFile(file);
    file->Close();
    std::cout << "Built flow wrote to " << file_name << std::endl;
  }
protected:
  std::string         name_;
  CorrelationMananger manager_;
  std::vector<Method> methods_;
};

#endif // QNDRAWER_FLOW_BUILDER_H
