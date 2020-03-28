//
// Created by mikhail on 26.12.2019.
//

#ifndef QNDRAWER_OBSERVABLE_H
#define QNDRAWER_OBSERVABLE_H

#include "file_manager.h"
#include <utility>
#include <vector>

class Observable : public FileManager {
public:
  Observable() = default;
  explicit Observable( const std::string& name ) : FileManager(name) {}
  Observable(std::string name, TFile *fileIn) : FileManager(name, fileIn) {}
  Observable(std::string name,
                      std::function<Qn::DataContainer<Qn::Stats>(
                          Qn::DataContainer<Qn::Stats>)> rebinProjectionRule)
      : FileManager( name, rebinProjectionRule ) {}
  ~Observable() override = default;
  void Init(const std::string& prefix, std::vector<std::string> component_names){
    std::for_each(component_names.begin(), component_names.end(), [prefix](std::string& str){
      str = prefix +str;
    } );
    components_ = GetDataContainerVector(component_names);
    averaged_ = MergeDataContainers( components_ );
  }
  const Qn::DataContainer<Qn::Stats> &GetAveraged() const { return averaged_; }
  const std::vector<Qn::DataContainer<Qn::Stats>> &GetComponents() const {
    return components_;
  }
  TGraphAsymmErrors* GetGraph( std::array<int, 2> marker ){
    auto graph = ToGraph(averaged_, name_, marker);
    return graph;
  }
  void SaveToFile(std::shared_ptr<TFile> file){
    file->cd();
    averaged_.Write(name_.data());
  }
  void SetContainer(const Qn::DataContainer<Qn::Stats> &averaged) {
    averaged_ = averaged;
  }
  static Qn::DataContainer<Qn::Stats> Merge( const std::vector<Observable> observables ){
    std::vector<Qn::DataContainer<Qn::Stats>> containers;
    for( auto observable : observables )
      containers.push_back( observable.averaged_ );
    return MergeDataContainers(containers);
  }
  static Qn::DataContainer<Qn::Stats> Ratio( const Qn::DataContainer<Qn::Stats>& reference, const Observable& value ){
    return value.averaged_/reference;
  };
  static std::vector<Qn::DataContainer<Qn::Stats>> Ratio( const Qn::DataContainer<Qn::Stats>& reference, const std::vector<Observable>& values ){
    std::vector<Qn::DataContainer<Qn::Stats>> ratio_vector;
    ratio_vector.reserve(values.size());
    for( const auto& value : values )
      ratio_vector.push_back(value.averaged_/reference);
    return ratio_vector;
  };
  static std::vector<Qn::DataContainer<Qn::Stats>> Ratio( const Observable& reference, const std::vector<Observable>& values ){
    std::vector<Qn::DataContainer<Qn::Stats>> ratio_vector;
    ratio_vector.reserve(values.size());
    for( const auto& value : values )
      ratio_vector.push_back(value.averaged_/reference.averaged_);
    return ratio_vector;
  };
protected:
  Qn::DataContainer<Qn::Stats> averaged_;
  std::vector<Qn::DataContainer<Qn::Stats>> components_;
};

#endif // QNDRAWER_OBSERVED_H
