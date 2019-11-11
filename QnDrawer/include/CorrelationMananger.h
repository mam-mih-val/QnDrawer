//
// Created by mikhail on 15.10.2019.
//
#ifndef QNDRAWER_CORRELATIONMANANGER_H
#define QNDRAWER_CORRELATIONMANANGER_H

#include "DataContainer.h"
#include "FlowConfiguration.h"
#include "Method.h"
#include "Stats.h"
#include "TFile.h"
#include "FlowHelper.h"
#include <map>
#include <memory>
#include <string>
#include <utility>
#include <vector>
#include <algorithm>

class CorrelationMananger : public FlowHelper{
public:
  CorrelationMananger() = default;
  virtual ~CorrelationMananger() = default;
  void SetConfigFile(const std::string& file_name){
    config_file_.reset( TFile::Open(file_name.data()) );
    std::cout << "Configuration file is set: " << file_name << std::endl;
  }
  std::vector<Qn::DataContainer<Qn::Stats>> GetQnQnContainers(const std::string& config_name, unsigned int component){
    FlowConfiguration* config;
    config_file_->GetObject(config_name.data(), config);
//    std::cout << "Reading " << config_name << " configuration" << std::endl;
    std::vector<std::string> qn_qn_names{ config->GetQnQnNames() };
    std::vector<std::string> components_names{ config->GetComponentsNames() };
    std::for_each( qn_qn_names.begin(), qn_qn_names.end(), [components_names, component]( std::string &str ){
      str+=components_names.at(component);
    } );
    return  GetDataContainerVector(qn_qn_names);
  }
  std::vector<Qn::DataContainer<Qn::Stats>> GetUnQnContainers(const std::string& config_name, unsigned int component){
    FlowConfiguration* config;
    config_file_->GetObject(config_name.data(), config);
    std::vector<std::string> un_qn_names{ config->GetUnQnNames() };
    std::vector<std::string> components_names{ config->GetComponentsNames() };
    std::for_each( un_qn_names.begin(), un_qn_names.end(), [components_names, component]( std::string &str ){
      str+=components_names.at(component);
    } );
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
    method.SetNumberOfSe(config->GetNumberOfSe());
    method.SetResolutionIndicesMatrix(config->GetResolutionIndicesMatrix());
    for(int i=0; i<2; i++)
    {
      method.SetQnQnCorrelations( GetQnQnContainers(config_name, i), i );
      method.SetUnQnCorrelations( GetUnQnContainers(config_name, i), i );
    }
    return method;
  }
protected:
  std::shared_ptr<TFile> config_file_;
//  ClassDefOverride(CorrelationMananger, 1)
};


#endif //QNDRAWER_CORRELATIONMANANGER_H
