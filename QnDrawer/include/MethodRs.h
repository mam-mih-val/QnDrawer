//
// Created by mikhail on 26.10.2019.
//

#ifndef QNDRAWER_METHODRS_H
#define QNDRAWER_METHODRS_H

#include "Method.h"

class MethodRs : public Method {
public:
  MethodRs() = default;
  ~MethodRs() override = default;
  void Init() override {
    auto R = []( const std::vector<Qn::DataContainer<Qn::Stats>>& correlations ){
      Qn::DataContainer<Qn::Stats> result;
      result = Sqrt(correlations.at(0) * 0.5 );
      return result;
    };
    for(unsigned int i=0; i<2; i++)
    {
      sub_events_.emplace_back();
      sub_events_.at(i).SetName(name_+std::to_string(i));
      sub_events_.at(i).SetResolutionRule(R);
      sub_events_.at(i).Init();
    }
    std::cout << "3 sub-event method is initialized" << std::endl;
  }
  void Compute() override {
    for(unsigned int i=0; i<sub_events_.size(); i++){
      for(unsigned int j=0; j<2; j++){
        sub_events_.at(i).Resolution(j).Compute( qn_correlations_.at(j) );
        sub_events_.at(i).Flow(j).Compute({qn_correlations_.at(j).at(i),sub_events_.at(i).Resolution(j).GetContainer()} );
      }
    }
  }
  ClassDef(MethodRs, 1)
};

#endif // QNDRAWER_METHODRS_H
