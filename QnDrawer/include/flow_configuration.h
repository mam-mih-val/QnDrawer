//
// Created by mikhail on 18.10.2019.
//
#ifndef QNDRAWER_FLOW_CONFIGURATION_H
#define QNDRAWER_FLOW_CONFIGURATION_H

#include "TObject.h"
#include <Axis.h>
#include <DataContainer.h>
#include <Stats.h>
#include <functional>
#include <string>
#include <utility>
#include <vector>

class FlowConfiguration : public TObject {
public:
  FlowConfiguration() = default;
  FlowConfiguration(std::string name)
      : name_(std::move(name)) {}
  ~FlowConfiguration() override = default;
  const std::vector<std::string> &GetQnQnNames() const { return qn_qn_names_; }
  void SetQnQnNames(const std::vector<std::string> &qnQnNames) {
    qn_qn_names_ = qnQnNames;
  }
  void SetName(const std::string &name) { name_ = name; }
  const std::vector<std::string> &GetUnQnNames() const { return un_qn_names_; }
  void SetUnQnNames(const std::vector<std::string> &unQnNames) {
    un_qn_names_ = unQnNames;
  }
  const std::vector<std::string> &GetFlowProjectionAxisNames() const {
    return flow_projection_axis_names_;
  }
  void
  SetFlowProjectionAxisNames(const std::vector<std::string> &projectionAxisNames) {
    flow_projection_axis_names_ = projectionAxisNames;
  }
  const std::vector<std::vector<Qn::Axis>> &GetFlowRebinAxis() const {
    return un_un_rebin_axis_;
  }
  void
  SetFlowRebinAxis(const std::vector<std::vector<Qn::Axis>> &flowRebinAxis) {
    un_un_rebin_axis_ = flowRebinAxis;
  }
  void SaveToFile( TFile* file ){
    file->cd();
    this->Write(name_.data());
  }
  const std::vector<std::vector<Qn::Axis>> &GetQnQnRebinAxis() const {
    return qn_qn_rebin_axis_;
  }
  void
  SetQnQnRebinAxis(const std::vector<std::vector<Qn::Axis>> &qnQnRebinAxis) {
    qn_qn_rebin_axis_ = qnQnRebinAxis;
  }


private:
  std::string name_;
  std::vector<std::string> qn_qn_names_;
  std::vector<std::string> un_qn_names_;

  std::vector<std::string> flow_projection_axis_names_;
  std::vector<std::vector<Qn::Axis>> un_un_rebin_axis_;
  std::vector<std::vector<Qn::Axis>> qn_qn_rebin_axis_;
  ClassDefOverride(FlowConfiguration, 1)
};

#endif // QNDRAWER_FLOW_CONFIGURATION_H