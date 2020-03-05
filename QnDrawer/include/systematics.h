//
// Created by mikhail on 26.11.2019.
//

#ifndef QNDRAWER_SYSTEMATICS_H
#define QNDRAWER_SYSTEMATICS_H

#include "TStyle.h"
#include "flow_helper.h"
#include "observable.h"
#include "painter.h"
#include <DataContainer.h>
#include <Stats.h>
#include <TF1.h>
#include <TLegend.h>
#include <TMultiGraph.h>
#include <exception>
#include <utility>
#include <vector>

class Systematics : public Painter {
 public:
  Systematics() = default;
  explicit Systematics(std::string name) : name_(std::move(name)) {}
  ~Systematics() override = default;
  void SetName(const std::string &name) { name_ = name; }
  void DrawSystematics() {
    auto stack_title = ";" + x_axis_title_ + ";" + y_axis_title_;
    auto result_stack = new TMultiGraph("result", stack_title.data());
    stack_title = ";" + x_axis_title_;
    auto ratio_stack = new TMultiGraph("ratio", stack_title.data());
    TGraphAsymmErrors *graph{nullptr};
    graph = reference_observable_.GetGraph({kFullCircle, kBlack});
    result_stack->Add(graph);
    graph = FileManager::ToGraph(reference_observable_.GetAveraged() /reference_observable_.GetAveraged(), reference_observable_.GetName(), {kFullCircle, kBlack});
    ratio_stack->Add(graph);
    int i=0;
    for( auto &observable : observables_){
      graph = observable.GetGraph({marker_styles_.at(i), marker_colors_.at(i)});
      result_stack->Add(graph);
      i++;
    }
    auto ratios = Observable::Ratio(reference_observable_, observables_);
    i=0;
    for( auto &ratio : ratios){
      graph = FileManager::ToGraph(ratio, "", {marker_styles_.at(i), marker_colors_.at(i)});
      ratio_stack->Add(graph);
      i++;
    }
    DrawWithRatio(result_stack, ratio_stack);
  }

  void AddObservable(std::string title, std::string prefix,
                     std::vector<std::string> components) {
    observables_.emplace_back(title, rebin_projection_rule_);
    observables_.back().SetFileIn(file_);
    observables_.back().Init(prefix, components);
  }
  void AddReference(std::string title, std::string prefix,
                     std::vector<std::string> components,
                     std::shared_ptr<TFile> file) {
    reference_observable_ = Observable(title, rebin_projection_rule_);
    reference_observable_.SetFileIn(file);
    reference_observable_.Init(prefix, components);
  }
  void AddObservables(std::vector<std::string> title,
                      std::vector<std::string> prefix,
                      std::vector<std::string> components) {
    try {
      for (size_t i = 0; i < title.size(); i++)
        AddObservable(title.at(i), prefix.at(i), components);
    } catch (const std::exception &e) {
      std::cout << e.what() << std::endl;
      std::cout << "The vectors are not same size:" << std::endl;
      std::cout << "title:" << title.size() << std::endl;
      std::cout << "prefix:" << prefix.size() << std::endl;
    }
  }
  void SetFile(const std::shared_ptr<TFile> &file) { file_ = file; }
  void SetReferenceObservable(const Observable &reference_observable) {
    reference_observable_ = reference_observable;
  }
  void SetRebinProjectionRule(
      const std::function<Qn::DataContainer<Qn::Stats>(
          Qn::DataContainer<Qn::Stats>)> &rebin_projection_rule) {
    rebin_projection_rule_ = rebin_projection_rule;
  }

private:
  std::string name_;
  std::shared_ptr<TFile> file_;
  Observable reference_observable_;
  std::vector<Observable> observables_;

  std::function<Qn::DataContainer<Qn::Stats>(
      Qn::DataContainer<Qn::Stats>)>
      rebin_projection_rule_ =
      [](Qn::DataContainer<Qn::Stats> container) {
        return container;
      };
};

#endif // QNDRAWER_SYSTEMATICS_H
