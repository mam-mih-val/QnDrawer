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
    void Init() override {
        auto R = []( std::vector<Qn::DataContainer<Qn::Stats>> correlations ){
            Qn::DataContainer<Qn::Stats> result;
            result = correlations.at(0) * correlations.at(1) / ( correlations.at(2)*2 );
            result = Sqrt(result);
            return result;
        };
        for(unsigned int i=0; i<3; i++)
        {
            sub_events_.emplace_back();
            sub_events_.at(i).SetName(name_+std::to_string(i));
            sub_events_.at(i).SetResolutionRule(R);
            sub_events_.at(i).Init();
        }
        std::cout << "3 sub-event method is initialized" << std::endl;
    }
    void Compute() override {
        std::cout << "Computing flow via 3 sub-event method" << std::endl;
        std::vector<int> idx{0, 2, 1};
        for(unsigned int comp=0; comp<2; comp++ ){
            std::vector<Qn::DataContainer<Qn::Stats>> qn_correlations_1{
                qn_correlations_.at(comp).at(1),
                qn_correlations_.at(comp).at(2),
                qn_correlations_.at(comp).at(0)
            };
            for(unsigned int i=0; i<3; i++){
                sub_events_.at(idx.at(i)).Resolution(comp).Compute(qn_correlations_1);
                qn_correlations_1={
                    qn_correlations_1.at(1),
                    qn_correlations_1.at(2),
                    qn_correlations_1.at(0)
                };
            }
            for(unsigned int i=0; i<sub_events_.size(); i++ )
                sub_events_.at(i).Flow(comp).Compute( {un_correlations_.at(comp).at(i), sub_events_.at(i).Resolution(comp).GetContainer()} );
        }
    }
};

#endif //QNDRAWER_METHOD3SE_H
