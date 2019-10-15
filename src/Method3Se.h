//
// Created by mikhail on 14.10.2019.
//

#ifndef QNDRAWER_METHOD3SE_H
#define QNDRAWER_METHOD3SE_H

#include "Method.h"

class Method3Se : public Method {
public:
    Method3Se() = default;
    Method3Se(std::string name){
        name_=name;
    }
    ~Method3Se() override = default;
    void Compute() override {
        std::vector<int> idx{0, 2, 1};
        for(int i=0; i<3; i++){
            std::vector<Qn::DataContainer<Qn::Stats>> qn_correlations_1{qn_correlations_.at(1), qn_correlations_.at(2), qn_correlations_.at(0)};
            sub_events_.at(idx.at(i)).Resolution().Compute(qn_correlations_1);
        }
        int i=0;
        for( auto se : sub_events_ )
        {
            se.Flow().Compute( {un_correlations_.at(i), se.Resolution().GetContainer()} );
            i++;
        }
    }
    void Init() override {
        auto resolution = []( std::vector<Qn::DataContainer<Qn::Stats>> correlations ){
            Qn::DataContainer<Qn::Stats> result;
            result = correlations.at(0) * correlations.at(1) / ( correlations.at(2)*2 );
            result = Sqrt(result);
            return result;
        };
        for(int i=0; i<3; i++)
        {
            sub_events_.at(i).SetName(name_+std::to_string(i));
            sub_events_.at(i).SetResolutionRule(resolution);
            sub_events_.at(i).Init();
        }
    }
};

#endif //QNDRAWER_METHOD3SE_H
