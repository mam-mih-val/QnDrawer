//
// Created by mikhail on 11.11.2019.
//

#ifndef QNDRAWER_FLOWHELPER_H
#define QNDRAWER_FLOWHELPER_H

#include <memory>
#include <string>
#include <utility>
#include <vector>
#include <algorithm>
#include <map>
#include <TFile.h>
#include <DataContainer.h>
#include <Stats.h>

class FlowHelper {
public:
  FlowHelper() = default;
  explicit FlowHelper(const std::string& file_name){ file_ = TFile::Open(file_name.data()); }
  explicit FlowHelper(TFile* file){ file_ = file; }
  virtual ~FlowHelper() = default;
  void SetFile(const std::string& fileName) { file_ = TFile::Open(fileName.data()); }
  void SetFile(TFile* file) { file_ = file; }
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
//    heap_.insert( make_pair(name, *ptr) );
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
  Qn::DataContainer<Qn::Stats> MakeComputations(
      std::vector<std::string> varNames,
      std::function<Qn::DataContainer<Qn::Stats>(std::vector<Qn::DataContainer<Qn::Stats>>)> lambda,
      std::string resultName
  )
  {
    auto arg = GetDataContainerVector(varNames);
    auto result = lambda(arg);
    heap_.insert(make_pair(resultName, result));
    return result;
  }

  void SaveToFile(const std::string& fileName){
    auto* file = new TFile( fileName.data(),"recreate" );
    file->cd();
    for(auto &container : heap_)
    {
      container.second.Write(container.first.data());
    }
  }
  Qn::DataContainer<Qn::Stats> Merge(std::vector<std::string> inputName, const std::string& outName="merged"){
    auto* array = new TList;
    Qn::DataContainer<Qn::Stats> out{GetDataContainer(inputName.at(0))};
    inputName.erase( inputName.begin() );
    std::vector<Qn::DataContainer<Qn::Stats>> forMerge;
    for( const auto& name : inputName )
      array->AddLast( (Qn::DataContainer<Qn::Stats>*) &(this->GetDataContainer(name)) );
    out.Merge( (TList*) array );
    heap_.insert(make_pair(outName, out));
    return out;
  }
  Qn::DataContainer<Qn::Stats> Ratio( std::vector<std::string> corr, std::string resultName ){
    auto ratio = []( std::vector<Qn::DataContainer<Qn::Stats>> corr ){
      Qn::DataContainer<Qn::Stats> result_;
      if( corr.size() != 2 )
      {
        std::cout << "Arguments amount error" << std::endl;
        return result_;
      }
      result_ = corr.at(0)/corr.at(1);
      result_.SetSetting(Qn::Stats::Settings::CORRELATEDERRORS);
      return result_;
    };
    return MakeComputations(corr, ratio, resultName);
  }

protected:
  std::map<std::string, Qn::DataContainer<Qn::Stats> > heap_;
  TFile* file_{nullptr};
 ClassDef(FlowHelper,1)
};

#endif // QNDRAWER_FLOWHELPER_H
