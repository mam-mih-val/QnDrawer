//
// Created by mikhail on 13.10.2019.
//

#include "Container.h"

void Container::FillHisto(){
    container_.SetSetting(Qn::Stats::Settings::CORRELATEDERRORS);
    std::vector<Qn::Axis> axes = container_.GetAxes();
    if( axes.size() > 1 )
    {
        std::cout << "Error: There are more than 1 axis" << std::endl;
        return;
    }
    int  	nbins = axes.at(0).size();
    float  	xmin = axes.at(0).GetLowerBinEdge(0);
    float  	xmax = axes.at(0).GetUpperBinEdge(nbins-1);
    std::string histoName = name_+"_histo";
    // std::cout << "xmin=" << xmin << " xmax=" << xmax << " nbins=" << nbins << endl;
    auto histo_ = new TH1F(histoName.data(), axes.at(0).Name().data(), nbins, xmin, xmax);
    int entries = 0;
    for( unsigned int i=0; i<container_.size(); i++ )
    {
        Qn::Stats bin = container_.At(i);
        entries+=bin.GetProfile().Entries();
        float mean = bin.Mean();
        float error = bin.Error();
        std::cout << "bin: " << i << " mean:" << mean << " error:" << error << std::endl;
        if( mean != mean )
            continue;
        histo_->SetBinContent(i+1, mean);
        histo_->SetBinError(i+1, error);
    }
    histo_->SetEntries(entries);
    axes.clear();
}

void Container::FillGraph() {
    graph_ = Qn::DataContainerHelper::ToTGraph(container_);
}

