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

int main( int argc, char** argv )
{
    if( argc==1 ){
        std::cout << "Error: Incorrecet number of arguments, " << argc-1 <<
        " given, 2 is required" << std::endl;
        std::cout << "Exit." << std::endl;
        return 1;
    }
    std::string input_file_name=argv[1];
    std::string output_file_name=argv[2];
    auto file = TFile::Open(input_file_name.data());
    CorrelationMananger mananger;
    mananger.SetFile(file);
    Method3Se method_3se;
    method_3se.SetName("3Sub");
    method_3se.Init();
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
    method_3se.Compute();
    auto* file_out = new TFile(output_file_name.data(), "recreate");
    method_3se.SaveToFile(file_out);
    file_out->Close();
    std::cout << "Results saved in " << output_file_name << std::endl;
    return 0;
}

