//
// Created by mikhail on 26.12.2019.
//

#ifndef QNDRAWER_OBSERVABLE_H
#define QNDRAWER_OBSERVABLE_H

#include "systematics.h"
#include <utility>
#include <vector>

class Observable{
public:
  explicit Observable(std::string name) : name_(std::move(name)) {}
  virtual ~Observable() = default;
  const std::vector<Qn::DataContainer<Qn::Stats>> &GetComponents() const {
    return components_;
  }

private:
  std::string name_;
  std::vector<Qn::DataContainer<Qn::Stats>> components_;

};

#endif // QNDRAWER_OBSERVED_H
