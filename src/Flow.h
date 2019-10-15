#pragma once
#include <vector>
#include <string>
#include <algorithm>
#include "CorrelationHelper.h"

class Flow{
public:
    Flow() = default;
    ~Flow() = default;
    virtual void ComputeFlow(Qn::DataContainer<Qn::Stats> unQn, Qn::DataContainer<Qn::Stats> resolution){
        flow_=unQn/resolution;
    }
    Qn::DataContainer<Qn::Stats> GetDataContainer() { return flow_; }
    TH1F* GetHistogram() { return nullptr; }
    TGraphAsymmErrors* GetHistogram() { return nullptr; }
private:
    Qn::DataContainer<Qn::Stats> flow_;
};