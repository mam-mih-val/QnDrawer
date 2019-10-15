//
// Created by mikhail on 15.10.2019.
//

#include "CorrelationMananger.h"

Qn::DataContainer<Qn::Stats>& CorrelationMananger::GetDataContainer(std::string name){
    Qn::DataContainer<Qn::Stats> empty;
    Qn::DataContainer<Qn::Stats>* ptr{nullptr};
    if( heap_.count(name) !=0 )
        return heap_.at(name);
    if(!file_)
        return empty;
    file_->GetObject( name.data(), ptr );
    if(!ptr)
    {
        std::cout << "No such a data container: " << name << std::endl;
        return empty;
    }
    heap_.insert( make_pair(name, *ptr) );
    return GetDataContainer(name);
}

std::vector<Qn::DataContainer<Qn::Stats>> CorrelationMananger::GetDataContainerVector(std::vector<std::string> names){
    std::vector<Qn::DataContainer<Qn::Stats>> result;
    for(auto name: names){
        result.push_back(GetDataContainer(name));
    }
    return result;
}