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
        "Fw1Sp_Fw2Sp_XX",
        "Fw3Sp_Fw1Sp_XX",
        "Fw2Sp_Fw3Sp_XX"
    };
    std::vector<std::string> u_correlations{
        "TracksMdcPt_Fw1Sp_XX",
        "TracksMdcPt_Fw2Sp_XX",
        "TracksMdcPt_Fw3Sp_XX"
    };
    method_3se.SetQnCorrelations( mananger.GetDataContainerVector(q_correlations) );
    method_3se.SetUnCorrelations( mananger.GetDataContainerVector(u_correlations) );
    method_3se.Compute();
    TFile* file1 = new TFile("out.root", "recreate");
    file1->cd();
    method_3se.Se(1).Flow().Rebin("Centrality", 2, 20.0, 30.0);
    method_3se.Se(1).Flow().Projection("0_Pt");
    method_3se.Se(1).Flow().GetContainer().SetSetting(Qn::Stats::Settings::CORRELATEDERRORS);
    method_3se.Se(1).Flow().GetContainer().Write();
    file1->Close();

    return 0;
}

