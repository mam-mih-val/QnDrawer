//
// Created by mikhail on 13.10.2019.
//

#ifndef QNDRAWER_SUBEVENT_H
#define QNDRAWER_SUBEVENT_H

#include <string>
#include <array>
#include "Container.h"
#include "DataContainer.h"
#include "Stats.h"

class SubEvent {
public:
    enum eComponents{
        x_=0,
        y_,
        number_of_components_
    };
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
        auto flow = []( std::vector<Qn::DataContainer<Qn::Stats>> corr ){
            Qn::DataContainer<Qn::Stats> result;
            if(corr.size()!=2)
                std::cout << "errors argument in QnDrawer::SubEvent::ComputeFlow" << std::endl;
            result = corr.at(0)/corr.at(1);
            return result;
        };
        for(auto &v : flow_)
            v.SetRule(flow);
    }
    void SetResolutionRule( std::function<Qn::DataContainer<Qn::Stats>(std::vector<Qn::DataContainer<Qn::Stats>>)> rule ){
        for(auto &r : resolution_)
            r.SetRule(rule);
    }
    void SetName(std::string name){name_=name;}
    Container& Resolution(unsigned int idx) { return resolution_.at(idx); }
    Container& Flow(unsigned int idx) { return flow_.at(idx); }
private:
    std::string name_;
    std::array<Container, 2> resolution_; // x&y components
    std::array<Container, 2> flow_; // x&y components
};


#endif //QNDRAWER_SUBEVENT_H
