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
    std::string GetName(){return name_;}
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
    void Rebin(Qn::Axis axis){
      for(auto& se:sub_events_){
        se.Rebin(axis);
      }
    };
    void Projection(std::string axis){
      for(auto& se:sub_events_){
        se.Projection(axis);
      }
    }
    void SaveHistoToFile(TFile* file){
      for(auto &se:sub_events_){
        se.SaveHistoToFile(file);
      }
    }
  void Average(){
    averaged_.SetName("averaged_"+name_);
    for( unsigned int i=0; i<sub_events_.size(); i++ ){
      averaged_=sub_events_.at(i).Flow(0)+sub_events_.at(i).Flow(1);
      diff_sub_events_.push_back(sub_events_.at(i).Flow(0)+sub_events_.at(i).Flow(1));
      diff_sub_events_.back().SetName( "averaged_"+sub_events_.at(i).GetName() );
    }
  }

  Container& GetAveraged(){ return averaged_; }
  void SaveAveragedHistoToFile(TFile* file){
      averaged_.SaveHistoToFile(file);
      for(auto se : diff_sub_events_)
        se.SaveHistoToFile((file));
  }
  const Container &GetAverageSe(unsigned short idx ) const {
    return diff_sub_events_.at(idx);
  }
protected:
  std::string name_;
  std::vector<SubEvent> sub_events_;
  std::vector<Container> diff_sub_events_;
  std::vector<Container> diff_components_;
  Container averaged_;
  std::array<std::vector<Qn::DataContainer<Qn::Stats>>,2> qn_correlations_; // Qn1Qn2, Qn1Qn3, Qn2Qn3
  std::array<std::vector<Qn::DataContainer<Qn::Stats>>,2> un_correlations_;
};


#endif //QNDRAWER_METHOD_H
