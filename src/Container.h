//
// Created by mikhail on 13.10.2019.
//

#ifndef QNDRAWER_CONTAINER_H
#define QNDRAWER_CONTAINER_H

#include <utility>
#include <vector>
#include <string>
#include <algorithm>
#include "TH1F.h"
#include "TGraphAsymmErrors.h"
#include "DataContainer.h"
#include "Stats.h"

class Container {
public:
    Container() = default;
    Container(const Container &otherContainer) = default;
    Container& operator=(const Container& other) = default;
    explicit Container(std::string name) :
        name_(std::move(name))
    {
        // none
    }
    virtual ~Container() = default;
    Qn::DataContainer<Qn::Stats>& GetContainer() { return container_;}
    TH1F* GetHistogram(){
        if(!histo_)
            FillHisto();
        return histo_;
    }
    TGraphAsymmErrors* GetGraph(){
        if(!graph_)
            FillGraph();
        return graph_;
    }
    void Compute( std::vector< Qn::DataContainer<Qn::Stats> > containers ){
        if(!rule_)
            std::cout << "empty container function" << std::endl;
        container_=rule_( std::move(containers) );
    }
    void SetName( std::string name ) {name_=std::move(name);}
    void SetRule( std::function<Qn::DataContainer<Qn::Stats>(std::vector<Qn::DataContainer<Qn::Stats>>)> rule ) {
        rule_=std::move(rule);
    }
    void Rebin( std::string axis, int bins, float min, float max ){
        container_=container_.Rebin({std::move(axis), bins, min, max});
    }
    void Projection( std::string axis ){
        container_=container_.Projection({std::move(axis)});
    }
    void SetContainer( const Qn::DataContainer<Qn::Stats>& container ) { container_=container; }
    void FillHisto();
    void FillGraph();
    void SaveToFile(TFile* file){
        container_.Write(name_.data());
    };
    friend Container operator+(const Container& term_1, const Container& term_2 ){
        Container result;
        auto* array = new TList;
        Qn::DataContainer<Qn::Stats> out{(Qn::DataContainer<Qn::Stats>) term_1.container_};
        array->AddLast( (Qn::DataContainer<Qn::Stats>*) &(term_2.container_) );
        out.Merge( (TList*) array );
        result.container_=out;
        return result;
    };

    void SaveToFile();

private:
    std::string name_;
    Qn::DataContainer<Qn::Stats> container_;
    TH1F* histo_{nullptr};
    TGraphAsymmErrors* graph_{nullptr};
    std::function<Qn::DataContainer<Qn::Stats>(std::vector<Qn::DataContainer<Qn::Stats>>)> rule_;
};

#endif //QNDRAWER_CONTAINER_H
