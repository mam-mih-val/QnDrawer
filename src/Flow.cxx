#include "Flow.h"
/*
void MergeComponents(std::string q_name){
    std::vector<std::string> for_merging = components_ ;
    std::for_each(for_merging.begin(), for_merging.end(), [q_name](std::string &str){ "flow_"+q_name+str; });
    Merge( for_merging, q_name );
};
void MergeSubEvents(std::string method){

};
 */
void Flow::ComputeFlow(int method){
    switch( method )
    {
        case k3SubEp :
        {
            std::vector<std::string> qVecName = q_.at(k3SubEp);
            Flow3Se(u_, qVecName);
            break;
        }
        case k3SubSp :
        {
            std::vector<std::string> qVecName = q_.at(k3SubSp);
            Flow3Se(u_, qVecName);
            break;
        }
        case kRndEp :
        {
            std::vector<std::string> qVecName = q_.at(kRndEp);
            FlowRs(u_, qVecName);
            break;
        }
        case kRndSp :
        {
            std::vector<std::string> qVecName = q_.at(kRndSp);
            FlowRs(u_, qVecName);
            break;
        }
        case kFullEvt :
        {
            std::vector<std::string> qVecName = q_.at(kFullEvt);
            FlowRs(u_, qVecName);
            break;
        }
        default:
            std::cout << "unknown method" << std::endl;
    }
}

void Flow::ComputeFlow(){
    for( uint i=0; i<kNumberOfMethods; i++ )
        ComputeFlow(i);
}