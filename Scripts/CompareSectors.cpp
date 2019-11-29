//
// Created by mikhail on 29.11.2019.
//

void CompareSectors(){
  std::vector<TFile*> files{
    TFile::Open("../cmake-build-debug/six_sectors.root"),
    TFile::Open("../cmake-build-debug/five_sectors.root"),
    TFile::Open("../cmake-build-debug/five_sectors_no_corrections.root")
  };
  std::vector<std::string> titles{
    "six sectors (default)",
    "five sectors with u_{n} corrections",
    "five sectors no u_{n} correction"
  };
  std::vector<TMultiGraph*> stacks{
    new TMultiGraph("tree_sub", ";pt, [GeV/c]; v_{1}"),
    new TMultiGraph("rand_sub", ";pt, [GeV/c]; v_{1}"),
    new TMultiGraph("elliptic", ";pt, [GeV/c]; v_{2}")
  };
  for( int i=0; i<files.size(); i++ ){
    Qn::DataContainer<Qn::Stats> *container;
    container = files.at(i)->GetObject();
  }
}