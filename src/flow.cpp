//
// Created by mikhail on 17.10.2019.
//

#include <vector>
#include <chrono>
#include <string>
#include <iostream>
#include "FlowBuilder.h"

// ./Build_Flow input_file output_file config_file


int main( int argc, char** argv )
{
  auto start = std::chrono::system_clock::now();
  if( argc < 3 ){
    std::cout << "Error: Incorrecet number of arguments, " << argc-1 <<
    " given, 3 is required" << std::endl;
    std::cout << "Exit." << std::endl;
    return 1;
  }
  std::string input_file_name=argv[1];
  std::string output_file_name=argv[2];
  std::string config_file_name=argv[3];

  FlowBuilder builder;
  builder.SetName("FlowBuilder");
  builder.SetInputName(input_file_name);
  builder.SetConfigFileName(config_file_name);
  std::vector<std::string> components{"_XX", "_YY"};
  std::vector<std::string> methods{"_Sp"};

  // ******************************** Method of 3 Sub-Events in MDC+FW ******************************** //
  for( auto component : components ){
    builder.AddMethod( "TracksMdcPt_Fw1_MdcFw_MdcBw_"+component+"_Sp", [](std::vector<Qn::DataContainer<Qn::Stats>> corr){
      Qn::DataContainer<Qn::Stats> result;
      result = Sqrt(corr.at(0)*corr.at(1)/(corr.at(2))*2);
      return result;
    },[](std::vector<Qn::DataContainer<Qn::Stats>> corr){
      Qn::DataContainer<Qn::Stats> result;
      result = corr.at(0)*2/corr.at(1);
      return result;
    } );

    builder.AddMethod( "TracksMdcPt_Fw1_MdcFw_Fw2_"+component+"_Sp", [](std::vector<Qn::DataContainer<Qn::Stats>> corr){
      Qn::DataContainer<Qn::Stats> result;
      result = Sqrt(corr.at(0)*corr.at(1)/(corr.at(2))*2);
      return result;
    },[](std::vector<Qn::DataContainer<Qn::Stats>> corr){
      Qn::DataContainer<Qn::Stats> result;
      result = corr.at(0)*2/corr.at(1);
      return result;
    } );

    builder.AddMethod( "TracksMdcPt_Fw1_MdcFw_Fw3_"+component+"_Sp", [](std::vector<Qn::DataContainer<Qn::Stats>> corr){
      Qn::DataContainer<Qn::Stats> result;
      result = Sqrt(corr.at(0)*corr.at(1)/(corr.at(2))*2);
      return result;
    },[](std::vector<Qn::DataContainer<Qn::Stats>> corr){
      Qn::DataContainer<Qn::Stats> result;
      result = corr.at(0)*2/corr.at(1);
      return result;
    } );

    builder.AddMethod( "TracksMdcPt_Fw1_MdcBw_Fw2_"+component+"_Sp", [](std::vector<Qn::DataContainer<Qn::Stats>> corr){
      Qn::DataContainer<Qn::Stats> result;
      result = Sqrt(corr.at(0)*corr.at(1)/(corr.at(2))*2);
      return result;
    },[](std::vector<Qn::DataContainer<Qn::Stats>> corr){
      Qn::DataContainer<Qn::Stats> result;
      result = corr.at(0)*2/corr.at(1);
      return result;
    } );

    builder.AddMethod( "TracksMdcPt_Fw1_MdcBw_Fw3_"+component+"_Sp", [](std::vector<Qn::DataContainer<Qn::Stats>> corr){
      Qn::DataContainer<Qn::Stats> result;
      result = Sqrt(corr.at(0)*corr.at(1)/(corr.at(2))*2);
      return result;
    },[](std::vector<Qn::DataContainer<Qn::Stats>> corr){
      Qn::DataContainer<Qn::Stats> result;
      result = corr.at(0)*2/corr.at(1);
      return result;
    } );
  }

  for( auto component : components ){
    builder.AddMethod( "TracksMdcPt_Fw2_MdcFw_MdcBw_"+component+"_Sp", [](std::vector<Qn::DataContainer<Qn::Stats>> corr){
      Qn::DataContainer<Qn::Stats> result;
      result = Sqrt(corr.at(0)*corr.at(1)/(corr.at(2))*2);
      return result;
    },[](std::vector<Qn::DataContainer<Qn::Stats>> corr){
      Qn::DataContainer<Qn::Stats> result;
      result = corr.at(0)*2/corr.at(1);
      return result;
    } );

    builder.AddMethod( "TracksMdcPt_Fw2_MdcFw_Fw1_"+component+"_Sp", [](std::vector<Qn::DataContainer<Qn::Stats>> corr){
      Qn::DataContainer<Qn::Stats> result;
      result = Sqrt(corr.at(0)*corr.at(1)/(corr.at(2))*2);
      return result;
    },[](std::vector<Qn::DataContainer<Qn::Stats>> corr){
      Qn::DataContainer<Qn::Stats> result;
      result = corr.at(0)*2/corr.at(1);
      return result;
    } );

    builder.AddMethod( "TracksMdcPt_Fw2_MdcFw_Fw3_"+component+"_Sp", [](std::vector<Qn::DataContainer<Qn::Stats>> corr){
      Qn::DataContainer<Qn::Stats> result;
      result = Sqrt(corr.at(0)*corr.at(1)/(corr.at(2))*2);
      return result;
    },[](std::vector<Qn::DataContainer<Qn::Stats>> corr){
      Qn::DataContainer<Qn::Stats> result;
      result = corr.at(0)*2/corr.at(1);
      return result;
    } );

    builder.AddMethod( "TracksMdcPt_Fw2_MdcBw_Fw1_"+component+"_Sp", [](std::vector<Qn::DataContainer<Qn::Stats>> corr){
      Qn::DataContainer<Qn::Stats> result;
      result = Sqrt(corr.at(0)*corr.at(1)/(corr.at(2))*2);
      return result;
    },[](std::vector<Qn::DataContainer<Qn::Stats>> corr){
      Qn::DataContainer<Qn::Stats> result;
      result = corr.at(0)*2/corr.at(1);
      return result;
    } );

    builder.AddMethod( "TracksMdcPt_Fw2_MdcBw_Fw3_"+component+"_Sp", [](std::vector<Qn::DataContainer<Qn::Stats>> corr){
      Qn::DataContainer<Qn::Stats> result;
      result = Sqrt(corr.at(0)*corr.at(1)/(corr.at(2))*2);
      return result;
    },[](std::vector<Qn::DataContainer<Qn::Stats>> corr){
      Qn::DataContainer<Qn::Stats> result;
      result = corr.at(0)*2/corr.at(1);
      return result;
    } );
  }
  for( auto component : components ){
    builder.AddMethod( "TracksMdcPt_Fw3_MdcFw_MdcBw_"+component+"_Sp", [](std::vector<Qn::DataContainer<Qn::Stats>> corr){
      Qn::DataContainer<Qn::Stats> result;
      result = Sqrt(corr.at(0)*corr.at(1)/(corr.at(2))*2);
      return result;
    },[](std::vector<Qn::DataContainer<Qn::Stats>> corr){
      Qn::DataContainer<Qn::Stats> result;
      result = corr.at(0)*2/corr.at(1);
      return result;
    } );

    builder.AddMethod( "TracksMdcPt_Fw3_MdcFw_Fw1_"+component+"_Sp", [](std::vector<Qn::DataContainer<Qn::Stats>> corr){
      Qn::DataContainer<Qn::Stats> result;
      result = Sqrt(corr.at(0)*corr.at(1)/(corr.at(2))*2);
      return result;
    },[](std::vector<Qn::DataContainer<Qn::Stats>> corr){
      Qn::DataContainer<Qn::Stats> result;
      result = corr.at(0)*2/corr.at(1);
      return result;
    } );

    builder.AddMethod( "TracksMdcPt_Fw3_MdcFw_Fw2_"+component+"_Sp", [](std::vector<Qn::DataContainer<Qn::Stats>> corr){
      Qn::DataContainer<Qn::Stats> result;
      result = Sqrt(corr.at(0)*corr.at(1)/(corr.at(2))*2);
      return result;
    },[](std::vector<Qn::DataContainer<Qn::Stats>> corr){
      Qn::DataContainer<Qn::Stats> result;
      result = corr.at(0)*2/corr.at(1);
      return result;
    } );

    builder.AddMethod( "TracksMdcPt_Fw3_MdcBw_Fw1_"+component+"_Sp", [](std::vector<Qn::DataContainer<Qn::Stats>> corr){
      Qn::DataContainer<Qn::Stats> result;
      result = Sqrt(corr.at(0)*corr.at(1)/(corr.at(2))*2);
      return result;
    },[](std::vector<Qn::DataContainer<Qn::Stats>> corr){
      Qn::DataContainer<Qn::Stats> result;
      result = corr.at(0)*2/corr.at(1);
      return result;
    } );

    builder.AddMethod( "TracksMdcPt_Fw3_MdcBw_Fw2_"+component+"_Sp", [](std::vector<Qn::DataContainer<Qn::Stats>> corr){
      Qn::DataContainer<Qn::Stats> result;
      result = Sqrt(corr.at(0)*corr.at(1)/(corr.at(2))*2);
      return result;
    },[](std::vector<Qn::DataContainer<Qn::Stats>> corr){
      Qn::DataContainer<Qn::Stats> result;
      result = corr.at(0)*2/corr.at(1);
      return result;
    } );
  }

  builder.Compute();
//  builder.Rebin();
  builder.Projection();
//  builder.SaveGraphsToFile(output_file_name);
  builder.SaveToFile(output_file_name);
  auto end = std::chrono::system_clock::now();
  std::chrono::duration<double> elapsed_seconds = end - start;
  std::cout << "elapsed time: " << elapsed_seconds.count() << " s\n";
  return 0;
}
