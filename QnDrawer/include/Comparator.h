//
// Created by mikhail on 09.11.2019.
//

#ifndef QNDRAWER_COMPARATOR_H
#define QNDRAWER_COMPARATOR_H

#include <TCanvas.h>
#include <TGraphAsymmErrors.h>
#include <DataContainer.h>
#include <Stats.h>
#include <utility>
#include <vector>
class Comparator {
public:
  Comparator() = default;
  explicit Comparator(std::vector<std::string> name) : name_(std::move(name)) {}
  ~Comparator() = default;
  void MergeDataContainers(std::vector<Qn::DataContainer<Qn::Stats>> for_merge){

  }
  void AddDataContainer(const Qn::DataContainer<Qn::Stats>& container){ data_containers_.push_back(container); }
  void AddGraph(TGraph* graph){ graphs_.emplace_back(graph); }
private:
  std::vector<std::string> name_;
  std::vector<Qn::DataContainer<Qn::Stats>> data_containers_;
  std::vector<TGraph*> graphs_;
  TCanvas* canvas_;

};

#endif // QNDRAWER_COMPARATOR_H
