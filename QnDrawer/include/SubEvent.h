//
// Created by mikhail on 13.10.2019.
//

#ifndef QNDRAWER_SUBEVENT_H
#define QNDRAWER_SUBEVENT_H

#include <string>
#include <array>
#include <utility>
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
        const std::function<Qn::DataContainer<Qn::Stats>(std::vector<Qn::DataContainer<Qn::Stats>>)>& rule
    )
    {
        name_=std::move(name);
        SetResolutionRule(rule);
        Init();
    }
    virtual ~SubEvent() = default;
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
        std::vector<std::string> componentsName{"_x", "_y"};
        for(int i=0; i<number_of_components_; i++)
        {
            resolution_.at(i).SetName("resolution_"+name_+componentsName.at(i));
            flow_.at(i).SetName("flow_"+name_+componentsName.at(i));
        }
    }
    void SetResolutionRule( const std::function<Qn::DataContainer<Qn::Stats>(std::vector<Qn::DataContainer<Qn::Stats>>)>& rule ){
        for(auto &r : resolution_)
            r.SetRule(rule);
    }
    void SetName(std::string name){name_=std::move(name);}
    void SaveToFile(TFile* file){
        for(int i=0; i<number_of_components_; i++)
        {
            resolution_.at(i).SaveToFile(file);
            flow_.at(i).SaveToFile(file);
        }
    }
    Container& Resolution(unsigned int idx) { return resolution_.at(idx); }
    Container& Flow(unsigned int idx) { return flow_.at(idx); }
    void Rebin(const Qn::Axis& axis){
      for(auto &flow : flow_)
        flow.Rebin(axis);
    }
    void Projection(const std::string axis){
      for(auto &flow : flow_)
        flow.Projection(axis);
    }
  const std::string &GetName() const { return name_; }
  void SaveHistoToFile(TFile* file){
      for(int i=0; i<2; i++){
        resolution_.at(i).SaveHistoToFile(file);
        flow_.at(i).SaveHistoToFile(file);
      }
    }
private:
  std::string name_;
  std::array<Container, 2> resolution_; // x&y components
  std::array<Container, 2> flow_; // x&y components
  ClassDef(SubEvent, 1)
};


#endif //QNDRAWER_SUBEVENT_H
