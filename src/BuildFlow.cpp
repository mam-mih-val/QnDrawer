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
    // ******************************** FW First Sub-Event ******************************** //
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
  // ******************************** FW Second Sub-Event ******************************** //
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
  // ******************************** FW Third Sub-Event ******************************** //
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
    // ******************************** Method of 3 Sub-Events in FW ******************************** //
    builder.AddMethod( "TracksMdcPt_Fw1_Fw2_Fw3_"+component+"_Sp", [](std::vector<Qn::DataContainer<Qn::Stats>> corr){
      Qn::DataContainer<Qn::Stats> result;
      result = Sqrt(corr.at(0)*corr.at(1)/(corr.at(2))*2);
      return result;
    },[](std::vector<Qn::DataContainer<Qn::Stats>> corr){
      Qn::DataContainer<Qn::Stats> result;
      result = corr.at(0)*2/corr.at(1);
      return result;
    } );

    builder.AddMethod( "TracksMdcPt_Fw2_Fw1_Fw3_"+component+"_Sp", [](std::vector<Qn::DataContainer<Qn::Stats>> corr){
      Qn::DataContainer<Qn::Stats> result;
      result = Sqrt(corr.at(0)*corr.at(1)/(corr.at(2))*2);
      return result;
    },[](std::vector<Qn::DataContainer<Qn::Stats>> corr){
      Qn::DataContainer<Qn::Stats> result;
      result = corr.at(0)*2/corr.at(1);
      return result;
    } );

    builder.AddMethod( "TracksMdcPt_Fw3_Fw1_Fw2_"+component+"_Sp", [](std::vector<Qn::DataContainer<Qn::Stats>> corr){
      Qn::DataContainer<Qn::Stats> result;
      result = Sqrt(corr.at(0)*corr.at(1)/(corr.at(2))*2);
      return result;
    },[](std::vector<Qn::DataContainer<Qn::Stats>> corr){
      Qn::DataContainer<Qn::Stats> result;
      result = corr.at(0)*2/corr.at(1);
      return result;
    } );

    // ******************************** MDC Forward Rapidity ******************************** //
    builder.AddMethod( "TracksMdcPt_MdcFw_MdcBw_Fw1_"+component+"_Sp", [](std::vector<Qn::DataContainer<Qn::Stats>> corr){
      Qn::DataContainer<Qn::Stats> result;
      result = Sqrt(corr.at(0)*corr.at(1)/(corr.at(2))*2);
      return result;
    },[](std::vector<Qn::DataContainer<Qn::Stats>> corr){
      Qn::DataContainer<Qn::Stats> result;
      result = corr.at(0)*2/corr.at(1);
      return result;
    } );
    builder.AddMethod( "TracksMdcPt_MdcFw_MdcBw_Fw2_"+component+"_Sp", [](std::vector<Qn::DataContainer<Qn::Stats>> corr){
      Qn::DataContainer<Qn::Stats> result;
      result = Sqrt(corr.at(0)*corr.at(1)/(corr.at(2))*2);
      return result;
    },[](std::vector<Qn::DataContainer<Qn::Stats>> corr){
      Qn::DataContainer<Qn::Stats> result;
      result = corr.at(0)*2/corr.at(1);
      return result;
    } );
    builder.AddMethod( "TracksMdcPt_MdcFw_MdcBw_Fw3_"+component+"_Sp", [](std::vector<Qn::DataContainer<Qn::Stats>> corr){
      Qn::DataContainer<Qn::Stats> result;
      result = Sqrt(corr.at(0)*corr.at(1)/(corr.at(2))*2);
      return result;
    },[](std::vector<Qn::DataContainer<Qn::Stats>> corr){
      Qn::DataContainer<Qn::Stats> result;
      result = corr.at(0)*2/corr.at(1);
      return result;
    } );
    builder.AddMethod( "TracksMdcPt_MdcFw_Fw1_Fw2_"+component+"_Sp", [](std::vector<Qn::DataContainer<Qn::Stats>> corr){
      Qn::DataContainer<Qn::Stats> result;
      result = Sqrt(corr.at(0)*corr.at(1)/(corr.at(2))*2);
      return result;
    },[](std::vector<Qn::DataContainer<Qn::Stats>> corr){
      Qn::DataContainer<Qn::Stats> result;
      result = corr.at(0)*2/corr.at(1);
      return result;
    } );
    builder.AddMethod( "TracksMdcPt_MdcFw_Fw1_Fw3_"+component+"_Sp", [](std::vector<Qn::DataContainer<Qn::Stats>> corr){
      Qn::DataContainer<Qn::Stats> result;
      result = Sqrt(corr.at(0)*corr.at(1)/(corr.at(2))*2);
      return result;
    },[](std::vector<Qn::DataContainer<Qn::Stats>> corr){
      Qn::DataContainer<Qn::Stats> result;
      result = corr.at(0)*2/corr.at(1);
      return result;
    } );
    builder.AddMethod( "TracksMdcPt_MdcFw_Fw2_Fw3_"+component+"_Sp", [](std::vector<Qn::DataContainer<Qn::Stats>> corr){
      Qn::DataContainer<Qn::Stats> result;
      result = Sqrt(corr.at(0)*corr.at(1)/(corr.at(2))*2);
      return result;
    },[](std::vector<Qn::DataContainer<Qn::Stats>> corr){
      Qn::DataContainer<Qn::Stats> result;
      result = corr.at(0)*2/corr.at(1);
      return result;
    } );
    // ******************************** MDC Backward Rapidity ******************************** //
    builder.AddMethod( "TracksMdcPt_MdcBw_MdcFw_Fw1_"+component+"_Sp", [](std::vector<Qn::DataContainer<Qn::Stats>> corr){
      Qn::DataContainer<Qn::Stats> result;
      result = Sqrt(corr.at(0)*corr.at(1)/(corr.at(2))*2);
      return result;
    },[](std::vector<Qn::DataContainer<Qn::Stats>> corr){
      Qn::DataContainer<Qn::Stats> result;
      result = corr.at(0)*-2/corr.at(1);
      return result;
    } );
    builder.AddMethod( "TracksMdcPt_MdcBw_MdcFw_Fw2_"+component+"_Sp", [](std::vector<Qn::DataContainer<Qn::Stats>> corr){
      Qn::DataContainer<Qn::Stats> result;
      result = Sqrt(corr.at(0)*corr.at(1)/(corr.at(2))*2);
      return result;
    },[](std::vector<Qn::DataContainer<Qn::Stats>> corr){
      Qn::DataContainer<Qn::Stats> result;
      result = corr.at(0)*-2/corr.at(1);
      return result;
    } );
    builder.AddMethod( "TracksMdcPt_MdcBw_MdcFw_Fw3_"+component+"_Sp", [](std::vector<Qn::DataContainer<Qn::Stats>> corr){
      Qn::DataContainer<Qn::Stats> result;
      result = Sqrt(corr.at(0)*corr.at(1)/(corr.at(2))*2);
      return result;
    },[](std::vector<Qn::DataContainer<Qn::Stats>> corr){
      Qn::DataContainer<Qn::Stats> result;
      result = corr.at(0)*-2/corr.at(1);
      return result;
    } );
    builder.AddMethod( "TracksMdcPt_MdcBw_Fw1_Fw2_"+component+"_Sp", [](std::vector<Qn::DataContainer<Qn::Stats>> corr){
      Qn::DataContainer<Qn::Stats> result;
      result = Sqrt(corr.at(0)*corr.at(1)/(corr.at(2))*2);
      return result;
    },[](std::vector<Qn::DataContainer<Qn::Stats>> corr){
      Qn::DataContainer<Qn::Stats> result;
      result = corr.at(0)*-2/corr.at(1);
      return result;
    } );
    builder.AddMethod( "TracksMdcPt_MdcBw_Fw1_Fw3_"+component+"_Sp", [](std::vector<Qn::DataContainer<Qn::Stats>> corr){
      Qn::DataContainer<Qn::Stats> result;
      result = Sqrt(corr.at(0)*corr.at(1)/(corr.at(2))*2);
      return result;
    },[](std::vector<Qn::DataContainer<Qn::Stats>> corr){
      Qn::DataContainer<Qn::Stats> result;
      result = corr.at(0)*-2/corr.at(1);
      return result;
    } );
    builder.AddMethod( "TracksMdcPt_MdcBw_Fw2_Fw3_"+component+"_Sp", [](std::vector<Qn::DataContainer<Qn::Stats>> corr){
      Qn::DataContainer<Qn::Stats> result;
      result = Sqrt(corr.at(0)*corr.at(1)/(corr.at(2))*2);
      return result;
    },[](std::vector<Qn::DataContainer<Qn::Stats>> corr){
      Qn::DataContainer<Qn::Stats> result;
      result = corr.at(0)*-2/corr.at(1);
      return result;
    } );
  }
  // ******************************** Second Harmonics ******************************** //
  components = {"_XXX", "_XYY", "_YXY", "_YYX"};
  std::vector<std::string> first_names{
      "FWs1(MDCf,MDCb)",
      "FWs1(MDCf,FWs2)",
      "FWs1(MDCf,FWs3)",
      "FWs1(MDCb,FWs2)",
      "FWs1(MDCb,FWs3)",
      "FWs1(FWs2,FWs3)"
  };
  std::vector<std::string> second_names{
      "FWs2(MDCf,MDCb)",
      "FWs2(MDCf,FWs1)",
      "FWs2(MDCf,FWs3)",
      "FWs2(MDCb,FWs1)",
      "FWs2(MDCb,FWs3)",
      "FWs2(FWs1,FWs3)"
  };
  std::vector<std::string> third_names{
      "FWs3(MDCf,MDCb)",
      "FWs3(MDCf,FWs1)",
      "FWs3(MDCf,FWs2)",
      "FWs3(MDCb,FWs1)",
      "FWs3(MDCb,FWs2)",
      "FWs3(FWs1,FWs2)"
  };
  for( const auto& component : components ) {
    for(const auto & first_name : first_names){
      for(const auto & second_name : second_names){
        builder.AddMethod( first_name+"_"+second_name+component+"_Sp",
            [](std::vector<Qn::DataContainer<Qn::Stats>> corr){
          Qn::DataContainer<Qn::Stats> result;
          result = Sqrt(corr.at(0)*corr.at(1)/corr.at(2) * corr.at(3)*corr.at(4)/corr.at(5) ) * 2;
          return result;
        },[](std::vector<Qn::DataContainer<Qn::Stats>> corr){
          Qn::DataContainer<Qn::Stats> result;
          result = corr.at(0)*4/corr.at(1);
          return result;
        }  );
      }
    }
    for(const auto & second_name : second_names){
      for(const auto & third_name : third_names){
        builder.AddMethod( second_name+"_"+third_name+component+"_Sp",
                           [](std::vector<Qn::DataContainer<Qn::Stats>> corr){
                             Qn::DataContainer<Qn::Stats> result;
                             result = Sqrt(corr.at(0)*corr.at(1)/corr.at(2) * corr.at(3)*corr.at(4)/corr.at(5) ) * 2;
                             return result;
                           },[](std::vector<Qn::DataContainer<Qn::Stats>> corr){
              Qn::DataContainer<Qn::Stats> result;
              result = corr.at(0)*4/corr.at(1);
              return result;
            }  );
      }
    }
    for(const auto & first_name : first_names){
      for(const auto & third_name : third_names){
        builder.AddMethod( first_name+"_"+third_name+component+"_Sp",
                           [](std::vector<Qn::DataContainer<Qn::Stats>> corr){
                             Qn::DataContainer<Qn::Stats> result;
                             result = Sqrt(corr.at(0)*corr.at(1)/corr.at(2) * corr.at(3)*corr.at(4)/corr.at(5) ) * 2;
                             return result;
                           },[](std::vector<Qn::DataContainer<Qn::Stats>> corr){
              Qn::DataContainer<Qn::Stats> result;
              result = corr.at(0)*4/corr.at(1);
              return result;
            }  );
      }
    }
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