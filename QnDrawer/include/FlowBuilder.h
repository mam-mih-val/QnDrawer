//
// Created by mikhail on 05.11.2019.
//

#ifndef QNDRAWER_FLOWBUILDER_H
#define QNDRAWER_FLOWBUILDER_H

#include <utility>

#include "CorrelationMananger.h"
#include "Method3Se.h"
#include "MethodRs.h"
#include <Axis.h>
#include <vector>
#include <string>
#include <iostream>
class FlowBuilder {
public:
  FlowBuilder() = default;
  virtual ~FlowBuilder() = default;
  void SetInputName(const std::string& file_name){manager_.SetFile(file_name);}
  inline void SetConfigFileName( const std::string& file_name ){ manager_.SetConfigFile(file_name); }
  inline void SetMethod3SeName(std::string name){
    method_3se_.SetName(std::move(name));
  }void SetMethodRndName(std::string name){
    method_rnd_.SetName(std::move(name));
  }
  void Init(){
    method_3se_.Init();
    method_rnd_.Init();
    for(unsigned int i=0; i<2; i++)
    {
      method_3se_.SetQnCorrelations( i, manager_.GetQnQnContainers(method_3se_.GetName(), i) );
      method_3se_.SetUnCorrelations( i, manager_.GetUnQnContainers(method_3se_.GetName(), i) );

      method_rnd_.SetQnCorrelations( i, manager_.GetQnQnContainers(method_rnd_.GetName(), i) );
      method_rnd_.SetUnCorrelations( i, manager_.GetUnQnContainers(method_rnd_.GetName(), i) );
    }
  }
  void ComputeFlow(){
    method_3se_.Compute();
    method_rnd_.Compute();
  }
  void RebinProjection(){
    std::vector<Qn::Axis> rebin_axis_3se{manager_.GetRebinAxis(method_3se_.GetName())};
    for(auto axis:rebin_axis_3se)
      method_3se_.Rebin(axis);
    std::vector<Qn::Axis> rebin_axis_rnd{manager_.GetRebinAxis(method_rnd_.GetName())};
    for(auto axis:rebin_axis_rnd)
      method_rnd_.Rebin(axis);
    method_3se_.Projection(manager_.GetProjectionAxisName(method_3se_.GetName()));
    method_rnd_.Projection(manager_.GetProjectionAxisName(method_rnd_.GetName()));
  }
  void SaveToFile(const std::string& file_name){
    auto file = TFile::Open(file_name.data());
    method_rnd_.SaveToFile(file);
    method_3se_.SaveToFile(file);
    file->Close();
    std::cout << "Results saved to " << file_name << std::endl;
  }
protected:
  std::string         name_;
  CorrelationMananger manager_;
  Method3Se           method_3se_;
  MethodRs            method_rnd_;
  ClassDef(FlowBuilder, 1)
};

#endif // QNDRAWER_FLOWBUILDER_H
