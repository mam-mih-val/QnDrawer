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
    auto file = TFile::Open("/home/mikhail/QnDrawer/Input_Files/gt80Rnd_3Se_Sp_Ep_WithGap.root");
    CorrelationMananger mananger;
    mananger.SetFile(file);
    Method3Se method_3se;
    method_3se.SetName("3_Sub_Event");
    std::vector<std::string> q_correlations{
        "Fw1Sp_Fw2Sp_XX",
        "Fw3Sp_Fw1Sp_XX",
        "Fw2Sp_Fw3Sp_XX"
    };
    std::vector<std::string> u_correlations{
        "TracksMdc_Fw1Sp_XX",
        "TracksMdc_Fw2Sp_XX",
        "TracksMdc_Fw3Sp_XX"
    };

    method_3se.SetQnCorrelations( mananger.GetDataContainerVector(q_correlations) );
    method_3se.SetUnCorrelations( mananger.GetDataContainerVector(u_correlations) );
    return 0;
}

