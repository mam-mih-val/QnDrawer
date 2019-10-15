//
// Created by mikhail on 13.10.2019.
//

#ifndef QNDRAWER_SUBEVENT_H
#define QNDRAWER_SUBEVENT_H

#include <string>
#include "Container.h"
#include "DataContainer.h"
#include "Stats.h"

class SubEvent {
public:
    SubEvent() = default;
    SubEvent(
        std::string name,
        std::function<Qn::DataContainer<Qn::Stats>(std::vector<Qn::DataContainer<Qn::Stats>>)> rule
    )
    {
        name_=name;
        SetResolutionRule(rule);
        Init();
    }
    ~SubEvent() = default;
    void Init(){
        flow_.SetRule([]( std::vector<Qn::DataContainer<Qn::Stats>> corr ){ return corr.at(0)/corr.at(1); });
    }
    void SetResolutionRule( std::function<Qn::DataContainer<Qn::Stats>(std::vector<Qn::DataContainer<Qn::Stats>>)> rule ){
        resolution_.SetRule(rule);
    }
    void SetName(std::string name){name_=name;}
    Container& Resolution() { return resolution_; }
    Container& Flow() { return flow_; }
private:
    std::string name_;
    Container resolution_;
    Container flow_;
};


#endif //QNDRAWER_SUBEVENT_H
