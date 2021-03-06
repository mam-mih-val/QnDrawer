//
// Created by mikhail on 15.10.2019.
//
#ifndef QNDRAWER_CORRELATION_MANANGER_H
#define QNDRAWER_CORRELATION_MANANGER_H

#include "DataContainer.h"
#include "Stats.h"
#include "TFile.h"
#include "flow_configuration.h"
#include "flow_helper.h"
#include "method.h"
#include <algorithm>
#include <map>
#include <memory>
#include <string>
#include <utility>
#include <vector>

class CorrelationMananger : public FlowHelper{
public:
  CorrelationMananger() = default;
  ~CorrelationMananger() override = default;
  void SetConfigFile(const std::string& file_name){
    config_file_ =  TFile::Open(file_name.data());
    std::cout << "Configuration file is set: " << file_name << std::endl;
  }
  std::vector<Qn::DataContainer<Qn::Stats>> GetQnQnContainers(const std::string& config_name){
    FlowConfiguration* config;
    config_file_->GetObject(config_name.data(), config);
    std::vector<std::string> qn_qn_names{ config->GetQnQnNames() };
    return  GetDataContainerVector(qn_qn_names);
  }
  std::vector<Qn::DataContainer<Qn::Stats>> GetUnQnContainers(const std::string& config_name){
    FlowConfiguration* config;
    config_file_->GetObject(config_name.data(), config);
    std::vector<std::string> un_qn_names{ config->GetUnQnNames() };
    return  GetDataContainerVector(un_qn_names);
  }
  const std::vector<Qn::Axis> &GetRebinAxis(const std::string& config_name) const{
    FlowConfiguration* config;
    config_file_->GetObject(config_name.data(), config);
//    return config->GetRebinAxis();
  }
  const std::vector<std::string> &GetProjectionAxisName(const std::string& config_name) const{
    FlowConfiguration* config;
    config_file_->GetObject(config_name.data(), config);
    return config->GetFlowProjectionAxisNames();
  }
  Method MakeMethod( const std::string& config_name ){
    FlowConfiguration* config;
    config_file_->GetObject(config_name.data(), config);
    Method method(config_name);
    method.SetQnQnCorrelations( GetQnQnContainers(config_name) );
    method.SetQnQnRebinAxis( config->GetQnQnRebinAxis() );
    method.SetUnQnCorrelations( GetUnQnContainers(config_name) );
    return method;
  }
protected:
  TFile* config_file_{nullptr};
//  ClassDefOverride(CorrelationMananger, 1)
};


#endif // QNDRAWER_CORRELATION_MANANGER_H
