//
// Created by mikhail on 13.10.2019.
//

#ifndef QNDRAWER_METHOD_H
#define QNDRAWER_METHOD_H

#include <utility>

#include "SubEvent.h"
#include "DataContainer.h"
#include "Stats.h"

class Method {
public:
  enum kComponents{
    X=0,
    Y,
    NUM_OF_COMPONENTS
  };
  Method() = default;
  explicit Method(const std::string &name){name_=name;};
  virtual ~Method() = default;
  Method(std::string name, ushort numberOfSe)
      : name_(std::move(name)), number_of_se_(numberOfSe) {}
  const std::string &GetName() const { return name_; }
  void SetName(const std::string &name) { name_ = name; }
  void SetNumberOfSe(ushort numberOfSe) { number_of_se_ = numberOfSe; }
  ushort GetNumberOfSe() const { return number_of_se_; }
  const std::array<std::vector<Qn::DataContainer<Qn::Stats>>, NUM_OF_COMPONENTS> &
  GetResolution() const {
    return resolution_;
  }
  const std::array<std::vector<Qn::DataContainer<Qn::Stats>>, NUM_OF_COMPONENTS> &
  GetFlow() const {
    return flow_;
  }
  void SetResolutionRule(
      const std::function<Qn::DataContainer<Qn::Stats>(
          std::vector<Qn::DataContainer<Qn::Stats>>)> &resolutionRule) {
    resolution_rule_ = resolutionRule;
  }
  void SetResolutionIndicesMatrix(
      const std::vector<std::vector<ushort>> &resolutionIndicesMatrix) {
    resolution_indices_matrix_ = resolutionIndicesMatrix;
  }
  void SetQnQnCorrelations(const std::vector<Qn::DataContainer<Qn::Stats>> &qnQnCorrelations, ushort component) {
    qn_qn_correlations.at(component) = qnQnCorrelations;
  }
  void SetUnQnCorrelations(const std::vector<Qn::DataContainer<Qn::Stats>> &unQnCorrelations, ushort component) {
    un_qn_correlations.at(component) = unQnCorrelations;
  }
  void Compute(){
    if(!resolution_rule_){
      std::cout << "Empty resolution rule" << std::endl;
      return;
    }
    for(int i=0; i<2; i++){
      resolution_.at(i).clear();
      flow_.at(i).clear();}
    for( ushort k=0; k<NUM_OF_COMPONENTS; k++ ){
      for(ushort i=0; i<number_of_se_; i++){
        std::vector<ushort> idx{ resolution_indices_matrix_.at(i) };
        std::vector<Qn::DataContainer<Qn::Stats>> values;
        for(unsigned short j : idx)
          values.push_back( qn_qn_correlations.at(k).at(j) );
        resolution_.at(k).emplace_back( resolution_rule_(values) );
        flow_.at(k).emplace_back( un_qn_correlations.at(k).at(i)/resolution_.at(k).back() );
      }
    }
  }
  void Rebin( const Qn::Axis& axis ){
    for( const auto& vec : flow_ )
      for(const auto& container : vec)
        container.Rebin(axis);
  }
  void Projection( const std::string& axis_name ){
    for( const auto& vec : flow_ )
      for(const auto& container : vec)
        container.Projection({axis_name});
  }
  void SaveToFile(TFile* file){
    file->cd();
    std::vector<std::string> comp_name{"_X", "_Y"};
    for(ushort i=0; i<NUM_OF_COMPONENTS; i++){
      for( ushort j=0; j<number_of_se_; j++ ){
        std::string save_name{
          "resolution_"+name_+"+"+std::to_string(j)+comp_name.at(i)
        };
        resolution_.at(i).at(j).Write(save_name.data());
        save_name="flow_"+name_+"+"+std::to_string(j)+comp_name.at(i);
        flow_.at(i).at(j).Write(save_name.data());
      }
    }
  }
protected:
  std::string name_;
  ushort number_of_se_;
  std::function<Qn::DataContainer<Qn::Stats>(std::vector<Qn::DataContainer<Qn::Stats>>)> resolution_rule_;
  std::vector<std::vector<ushort>> resolution_indices_matrix_;
  std::array<std::vector<Qn::DataContainer<Qn::Stats>>, NUM_OF_COMPONENTS> resolution_;
  std::array<std::vector<Qn::DataContainer<Qn::Stats>>, NUM_OF_COMPONENTS> flow_;
  std::array<std::vector<Qn::DataContainer<Qn::Stats>>, NUM_OF_COMPONENTS> qn_qn_correlations;
  std::array<std::vector<Qn::DataContainer<Qn::Stats>>, NUM_OF_COMPONENTS> un_qn_correlations;
  ClassDef(Method, 1);
};


#endif //QNDRAWER_METHOD_H
