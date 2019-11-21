//
// Created by mikhail on 15.10.2019.
//
#ifndef QNDRAWER_CORRELATIONMANANGER_H
#define QNDRAWER_CORRELATIONMANANGER_H

#include "DataContainer.h"
#include "FlowConfiguration.h"
#include "FlowHelper.h"
#include "Method.h"
#include "Stats.h"
#include "TFile.h"
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
    config_file_.reset( TFile::Open(file_name.data()) );
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
    return config->GetRebinAxis();
  }
  const std::string &GetProjectionAxisName(const std::string& config_name) const{
    FlowConfiguration* config;
    config_file_->GetObject(config_name.data(), config);
    return config->GetProjectionAxisName();
  }
  Method MakeMethod( const std::string& config_name ){
    FlowConfiguration* config;
    config_file_->GetObject(config_name.data(), config);
    Method method(config_name);
    method.SetQnQnCorrelations( GetQnQnContainers(config_name) );
    method.SetUnQnCorrelations( GetUnQnContainers(config_name) );
    return method;
  }
protected:
  std::shared_ptr<TFile> config_file_;
//  ClassDefOverride(CorrelationMananger, 1)
};


#endif //QNDRAWER_CORRELATIONMANANGER_H
