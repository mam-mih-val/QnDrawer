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
  explicit FlowHelper(std::shared_ptr<TFile> file) : file_(std::move(file)) {}
  explicit FlowHelper(std::string file_name){
    file_.reset( TFile::Open(file_name.data()) );
  }
  virtual ~FlowHelper() = default;
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

protected:
  std::map<std::string, Qn::DataContainer<Qn::Stats> > heap_;
  std::shared_ptr<TFile> file_;
 ClassDef(FlowHelper,1)
};

#endif // QNDRAWER_FLOWHELPER_H
