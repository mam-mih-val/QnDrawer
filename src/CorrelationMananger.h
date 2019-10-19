//
// Created by mikhail on 15.10.2019.
//

#ifndef QNDRAWER_CORRELATIONMANANGER_H
#define QNDRAWER_CORRELATIONMANANGER_H

#include <string>
#include <utility>
#include <vector>
#include <memory>
#include <map>
#include "TFile.h"
#include "DataContainer.h"
#include "Stats.h"

class CorrelationMananger {
public:
    CorrelationMananger() = default;
    ~CorrelationMananger(){ heap_.clear(); }
    void SetFile(const std::string& fileName) { file_.reset(TFile::Open(fileName.data())); }
    void SetFile(std::shared_ptr<TFile> file) { file_ = std::move(file); }
    void SetFile(TFile* file) { file_.reset(file); }
    Qn::DataContainer<Qn::Stats>& GetDataContainer(const std::string& name){
      Qn::DataContainer<Qn::Stats> empty;
      Qn::DataContainer<Qn::Stats>* ptr{nullptr};
      if( heap_.count(name) !=0 )
        return heap_.at(name);
      if(!file_)
        return empty;
      file_->GetObject( name.data(), ptr );
      if(!ptr)
      {
        std::cout << "No such a data container: " << name << std::endl;
        return empty;
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
protected:
    std::map<std::string, Qn::DataContainer<Qn::Stats> > heap_;
    std::shared_ptr<TFile> file_;
};


#endif //QNDRAWER_CORRELATIONMANANGER_H
