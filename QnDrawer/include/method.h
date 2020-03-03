//
// Created by mikhail on 19.11.2019.
//

#ifndef QNDRAWER_METHOD_H
#define QNDRAWER_METHOD_H

#include <DataContainer.h>
class Method {
public:
  Method() = default;
  explicit Method(const std::string &name){name_=name;};
  virtual ~Method() = default;
  Method(std::string name, ushort numberOfSe) : name_(std::move(name)) {}
  const std::string &GetName() const { return name_; }
  void SetName(const std::string &name) { name_ = name; }
  const Qn::DataContainer<Qn::Stats>& GetResolution() const { return resolution_; }
  const Qn::DataContainer<Qn::Stats>& GetFlow() const { return flow_; }
  void SetResolutionRule(
      const std::function<Qn::DataContainer<Qn::Stats>(
          std::vector<Qn::DataContainer<Qn::Stats>>)> &resolutionRule) {
    resolution_rule_ = resolutionRule;
  }
  void SetFlowRule(const std::function<Qn::DataContainer<Qn::Stats>(
      std::vector<Qn::DataContainer<Qn::Stats>>)> &flowRule) {
    flow_rule_ = flowRule;
  }
  void SetQnQnCorrelations(const std::vector<Qn::DataContainer<Qn::Stats>> &qnQnCorrelations) {
    qn_qn_correlations_ = qnQnCorrelations;
  }
  void SetQnQnRebinAxis(const std::vector<std::vector<Qn::Axis>> &qnQnRebinAxis) {
    qn_qn_rebin_axis_ = qnQnRebinAxis;
  }
  void SetUnQnCorrelations(const std::vector<Qn::DataContainer<Qn::Stats>> &unQnCorrelations) {
    un_qn_correlations_ = unQnCorrelations; }
  void Compute(){
    if(!resolution_rule_){
      std::cout << "Empty resolution rule" << std::endl;
      return;
    }
    if(!flow_rule_){
      std::cout<< "Empty resolution rule" << std::endl;
      return;
    }
    for(size_t i=0; i< qn_qn_rebin_axis_.size(); ++i){
      for( const auto& axis : qn_qn_rebin_axis_.at(i) )
        qn_qn_correlations_.at(i) = qn_qn_correlations_.at(i).Rebin(axis);
      qn_qn_correlations_.at(i) = qn_qn_correlations_.at(i).Projection({"Centrality"});
    }
    resolution_ = resolution_rule_(qn_qn_correlations_);
    std::vector<Qn::DataContainer<Qn::Stats>> values{un_qn_correlations_};
    values.push_back(resolution_);

    flow_ = flow_rule_( values );
    qn_qn_correlations_.clear();
    un_qn_correlations_.clear();
  }
  void Rebin( const Qn::Axis& axis ){
    flow_.Rebin(axis);
  }
  void Rebin( const std::vector<Qn::Axis>& axis_vec ){
    for( auto axis : axis_vec )
      flow_ = flow_.Rebin(axis);
  }
  void Projection( const std::vector<std::string>& axis_name ){
    flow_ = flow_.Projection(axis_name);
  }
  void SaveGraphsToFile(TFile* file){
    file->cd();
    std::string save_name{ "resolution_"+name_ };
    resolution_.SetSetting(Qn::Stats::Settings::CORRELATEDERRORS);
    auto graph = Qn::DataContainerHelper::ToTGraph(resolution_);
    graph->Write(save_name.data());
    save_name="flow_"+name_;
    flow_.SetSetting(Qn::Stats::Settings::CORRELATEDERRORS);
    graph = Qn::DataContainerHelper::ToTGraph(flow_);
    graph->Write(save_name.data());
  }
  void SaveToFile(TFile* file){
    file->cd();
    std::string save_name{ "resolution_"+name_ };
    resolution_.Write(save_name.data());
    save_name="flow_"+name_;
    flow_.Write(save_name.data());
  }
protected:
  std::string name_;
  std::function<Qn::DataContainer<Qn::Stats>(std::vector<Qn::DataContainer<Qn::Stats>>)> resolution_rule_;
  std::function<Qn::DataContainer<Qn::Stats>(std::vector<Qn::DataContainer<Qn::Stats>>)> flow_rule_{
    []( std::vector<Qn::DataContainer<Qn::Stats>> corr){
      Qn::DataContainer<Qn::Stats> result;
      result = corr.at(0)/corr.at(1);
      return result;
    }
  };
  Qn::DataContainer<Qn::Stats> resolution_;
  Qn::DataContainer<Qn::Stats> flow_;
  std::vector<std::vector<Qn::Axis>> un_qn_rebin_axis_;
  std::vector<std::vector<Qn::Axis>> qn_qn_rebin_axis_;
  std::vector<Qn::DataContainer<Qn::Stats>> qn_qn_correlations_;
  std::vector<Qn::DataContainer<Qn::Stats>> un_qn_correlations_;
  ClassDef(Method, 1);
};

#endif // QNDRAWER_METHOD_H
