//
// Created by mikhail on 18.10.2019.
//

#ifndef QNDRAWER_FLOWCONFIGURATION_H
#define QNDRAWER_FLOWCONFIGURATION_H

#include "TObject.h"
#include <vector>
#include <string>
#include <Axis.h>

class FlowConfiguration : public TObject {
public:
  FlowConfiguration() = default;
  ~FlowConfiguration() override {}
  const std::vector<std::string> &GetQnQnNames() const { return qn_qn_names_; }
  void SetQnQnNames(const std::vector<std::string> &qnQnNames) {
    qn_qn_names_ = qnQnNames;
  }
  const std::vector<std::string> &GetUnQnNames() const { return un_qn_names_; }
  void SetUnQnNames(const std::vector<std::string> &unQnNames) {
    un_qn_names_ = unQnNames;
  }
  const std::vector<std::string> &GetComponentsNames() const {
    return components_names_;
  }
  void SetComponentsNames(const std::vector<std::string> &componentsNames) {
    components_names_ = componentsNames;
  }
  const std::string &GetProjectionAxisName() const {
    return projection_axis_name_;
  }
  void SetProjectionAxisName(const std::string &projectionAxisName) {
    projection_axis_name_ = projectionAxisName;
  }
  const std::vector<Qn::Axis> &GetRebinAxis() const { return rebin_axis_; }
  void SetRebinAxis(const std::vector<Qn::Axis> &rebinAxis) {
    rebin_axis_ = rebinAxis;
  }
private:
  std::vector<std::string> qn_qn_names_;
  std::vector<std::string> un_qn_names_;
  std::vector<std::string> components_names_;
  std::string projection_axis_name_;
  std::vector<Qn::Axis> rebin_axis_;
};


#endif //QNDRAWER_FLOWCONFIGURATION_H
