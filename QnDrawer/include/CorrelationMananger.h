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
#include <map>
#include <memory>
#include <string>
#include <utility>
#include <vector>
#include <algorithm>

class CorrelationMananger {
public:
  CorrelationMananger() = default;
  virtual ~CorrelationMananger(){ heap_.clear(); }
  void SetFile(const std::string& fileName) { file_.reset(TFile::Open(fileName.data())); }
  void SetFile(std::shared_ptr<TFile> file) { file_ = std::move(file); }
  void SetFile(TFile* file) { file_.reset(file); }
  Qn::DataContainer<Qn::Stats>& GetDataContainer(const std::string& name){
    Qn::DataContainer<Qn::Stats>* ptr{nullptr};
    if( heap_.count(name) !=0 )
      return heap_.at(name);
    if(!file_)
      return *ptr;
    file_->GetObject( name.data(), ptr );
    if(!ptr)
    {
      std::cout << "No such a data container: " << name << std::endl;
      return *ptr;
    }
    heap_.insert( make_pair(name, *ptr) );
    return *ptr;
  }
  std::vector<Qn::DataContainer<Qn::Stats>> GetDataContainerVector(const std::vector<std::string>& names){
    std::vector<Qn::DataContainer<Qn::Stats>> result;
    result.reserve(names.size());
    for(const auto& name: names){
      result.push_back(GetDataContainer(name));
    }
    return result;
  };
  void SetConfigFile(const std::string& file_name){
    config_file_.reset( TFile::Open(file_name.data()) );
    std::cout << "Configuration file is set: " << file_name << std::endl;
  }
  std::vector<Qn::DataContainer<Qn::Stats>> GetQnQnContainers(const std::string& config_name, unsigned int component){
    FlowConfiguration* config;
    config_file_->GetObject(config_name.data(), config);
    std::cout << "Reading " << config_name << " configuration" << std::endl;
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
  void SaveToFile(const std::string& fileName){
    auto* file = new TFile( fileName.data(),"recreate" );
    file->cd();
    for(auto &container : heap_)
    {
        container.second.Write(container.first.data());
    }
  }
  Method Make3SeMethod( const std::string& config_name ){
    FlowConfiguration* config;
    config_file_->GetObject(config_name.data(), config);
    Method method(config_name);
    method.SetNumberOfSe(config->GetNumberOfSe());
    method.SetResolutionRule([](std::vector<Qn::DataContainer<Qn::Stats>> correlations){
      Qn::DataContainer<Qn::Stats> result;
      result = correlations.at(0) * correlations.at(1) / ( correlations.at(2)*2 );
      result = Sqrt(result);
      return result;
    });
    method.SetResolutionIndicesMatrix(config->GetResolutionIndicesMatrix());
    for(int i=0; i<2; i++)
    {
      method.SetQnQnCorrelations( GetQnQnContainers(config_name, i), i );
      method.SetUnQnCorrelations( GetUnQnContainers(config_name, i), i );
    }
    return method;
  }
protected:
  std::map<std::string, Qn::DataContainer<Qn::Stats> > heap_;
  std::shared_ptr<TFile> file_;
  std::shared_ptr<TFile> config_file_;
  // ClassDef(CorrelationMananger, 1)
};


#endif //QNDRAWER_CORRELATIONMANANGER_H
