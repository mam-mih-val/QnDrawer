//
// Created by mikhail on 17.10.2019.
//

//
// Created by mikhail on 13.10.2019.
//

#include <vector>
#include <string>
#include <iostream>
#include "TFile.h"
#include "CorrelationMananger.h"
#include "Method3Se.h"

int main( int argv, char** argc )
{
    auto file = TFile::Open("/home/mikhail/QnDrawer/Input_Files/PionMinus_Gt80.root");
    CorrelationMananger mananger;
    mananger.SetFile(file);
    Method3Se method_3se;
    method_3se.Init();
    method_3se.SetName("3_Sub_Event");
    std::vector<std::string> q_correlations{
            "Fw1Sp_Fw2Sp",
            "Fw3Sp_Fw1Sp",
            "Fw2Sp_Fw3Sp"
    };
    std::vector<std::string> u_correlations{
            "TracksMdcPt_Fw1Sp",
            "TracksMdcPt_Fw2Sp",
            "TracksMdcPt_Fw3Sp"
    };
    std::vector<std::string> components{
            "_XX",
            "_YY"
    };
    for(unsigned int i=0; i<components.size(); i++)
    {
        std::vector<std::string> corr_names=q_correlations;
        for(auto &corr: corr_names)
            corr+=components.at(i);
        method_3se.SetQnCorrelations( i, mananger.GetDataContainerVector(corr_names) );
        corr_names=u_correlations;
        for(auto &corr: corr_names)
            corr+=components.at(i);
        method_3se.SetUnCorrelations( i, mananger.GetDataContainerVector(corr_names) );
    }
    method_3se.Compute();
    TFile* file1 = new TFile("out.root", "recreate");
    file1->cd();
    method_3se.Se(1).Flow(0).Rebin("Centrality", 2, 20.0, 30.0);
    method_3se.Se(1).Flow(0).Projection("0_Pt");
    method_3se.Se(1).Flow(0).GetContainer().SetSetting(Qn::Stats::Settings::CORRELATEDERRORS);
    method_3se.Se(1).Flow(0).GetContainer().Write();
    file1->Close();

    return 0;
}

