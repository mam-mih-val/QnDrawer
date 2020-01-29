//
// Created by mikhail on 26.12.2019.
//

#ifndef QNDRAWER_OBSERVED_H
#define QNDRAWER_OBSERVED_H

#include "Systematics.h"
#include <vector>

class Observed {

private:
  std::string name_;
  std::vector<Qn::DataContainer<Qn::Stats>> components_;

};

#endif // QNDRAWER_OBSERVED_H
