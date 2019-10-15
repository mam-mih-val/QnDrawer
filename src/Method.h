//
// Created by mikhail on 13.10.2019.
//

#ifndef QNDRAWER_METHOD_H
#define QNDRAWER_METHOD_H

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
    void SetQnCorrelations(std::vector<Qn::DataContainer<Qn::Stats>> qn_correlations){
        qn_correlations_=qn_correlations;
    }
    void SetUnCorrelations(std::vector<Qn::DataContainer<Qn::Stats>> un_correlations){
        un_correlations_=un_correlations;
    }
    void SetName(std::string name) {
        name_=name;
    }
    SubEvent Se(int idx) {return sub_events_.at(idx);}

protected:
    std::string name_;
    std::vector<SubEvent> sub_events_;
    std::vector<Qn::DataContainer<Qn::Stats>> qn_correlations_; // Qn1Qn2, Qn1Qn3, Qn2Qn3
    std::vector<Qn::DataContainer<Qn::Stats>> un_correlations_;
};


#endif //QNDRAWER_METHOD_H
