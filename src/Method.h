//
// Created by mikhail on 13.10.2019.
//

#ifndef QNDRAWER_METHOD_H
#define QNDRAWER_METHOD_H

#include <utility>

#include "SubEvent.h"
#include "DataContainer.h"
#include "Stats.h"

class Method {
public:
    Method() = default;
    virtual ~Method() = default;
    std::string Name(){return name_;}
    virtual void Init(){};
    virtual void Compute(){};
    void SetQnCorrelations(uint idx, std::vector<Qn::DataContainer<Qn::Stats>> qn_correlations){
        qn_correlations_.at(idx)=std::move(qn_correlations);
    }
    void SetUnCorrelations(uint idx, std::vector<Qn::DataContainer<Qn::Stats>> un_correlations){
        un_correlations_.at(idx)=std::move(un_correlations);
    }
    void SetName(std::string name) {
        name_=std::move(name);
    }
    SubEvent& Se(int idx) {return sub_events_.at(idx);}
    unsigned int GetNumberOfSe() { return sub_events_.size(); }
    void SaveToFile(TFile* file){
        for(auto se : sub_events_){
            se.SaveToFile(file);
        }
    }
protected:
    std::string name_;
    std::vector<SubEvent> sub_events_;
    std::array<std::vector<Qn::DataContainer<Qn::Stats>>,2> qn_correlations_; // Qn1Qn2, Qn1Qn3, Qn2Qn3
    std::array<std::vector<Qn::DataContainer<Qn::Stats>>,2> un_correlations_;
};


#endif //QNDRAWER_METHOD_H
