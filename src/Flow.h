#pragma once
#include <vector>
#include <string>
#include <algorithm>
#include "CorrelationHelper.h"

class Flow : public CorrelationHelper{
public:
    enum method_{
        k3SubSp=0,
        k3SubEp,
        kRndSp,
        kRndEp,
        kFullEvt,
        kNumberOfMethods
    };
    Flow() = default;
    ~Flow() = default;
    void SetUname(std::string str) { u_=str; }
    void SetQname(std::vector<std::string> vec, int method) { q_.at(method) = vec; }
    void MergeComponents(std::string q_name);
    void MergeSubEvents(std::string method);
    void ComputeFlow(int method);
    void ComputeFlow();
private:
    std::string u_;
    std::array<std::vector<std::string>, kNumberOfMethods> q_;
    std::string axis_;
};