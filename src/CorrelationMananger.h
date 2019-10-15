//
// Created by mikhail on 15.10.2019.
//

#ifndef QNDRAWER_CORRELATIONMANANGER_H
#define QNDRAWER_CORRELATIONMANANGER_H

#include <string>
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
    void SetFile(std::string fileName) { file_.reset(TFile::Open(fileName.data())); }
    void SetFile(std::shared_ptr<TFile> file) { file_ = file; }
    void SetFile(TFile* file) { file_.reset(file); }
    Qn::DataContainer<Qn::Stats>& GetDataContainer(std::string);
    std::vector<Qn::DataContainer<Qn::Stats>> GetDataContainerVector(std::vector<std::string>);
    void SaveToFile(std::string fileName){
        TFile* file = new TFile( fileName.data(),"recreate" );
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
