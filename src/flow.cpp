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
    auto file = TFile::Open("/home/mikhail/QnDrawer/Input_Files/PionPlus_Gt80.root");
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
            "TracksMdcPtFw_Fw1Sp",
            "TracksMdcPtFw_Fw2Sp",
            "TracksMdcPtFw_Fw3Sp"
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
    for(unsigned int i=0; i<method_3se.GetNumberOfSe(); i++)
    {
        method_3se.Se(i).SetName("Fw_"+std::to_string(i));
    }
    method_3se.Compute();
    TFile* file_out = new TFile("PiPlus.root", "recreate");
    method_3se.SaveToFile(file_out);
    file_out->Close();

    return 0;
}

