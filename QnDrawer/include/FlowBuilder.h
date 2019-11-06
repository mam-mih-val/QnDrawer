//
// Created by mikhail on 05.11.2019.
//

#ifndef QNDRAWER_FLOWBUILDER_H
#define QNDRAWER_FLOWBUILDER_H

#include <utility>

#include "CorrelationMananger.h"
#include <Axis.h>
#include <vector>
#include <string>
#include <iostream>
class FlowBuilder {
public:
  FlowBuilder() = default;
  virtual ~FlowBuilder() = default;
  void SetInputName(const std::string& file_name){manager_.SetFile(file_name);}
  inline void SetConfigFileName( const std::string& file_name ){ manager_.SetConfigFile(file_name); }
  const std::string &GetName() const { return name_; }
  void SetName(const std::string &name) { name_ = name; }
  void AddMethod(const std::string& method_name){
    methods_.emplace_back( manager_.MakeMethod(method_name) );
  }
  void Compute(){
    for(auto &method: methods_)
      method.Compute();
  }
  void SaveToFile(TFile* file){
    for(auto &method: methods_)
      method.SaveToFile(file);
  }
  void SaveToFile(const std::string& file_name){
    auto file = TFile::Open(file_name.data(), "recreate");
    for(auto &method: methods_)
      method.SaveToFile(file);
    file->Close();
  }
protected:
  std::string         name_;
  CorrelationMananger manager_;
  std::vector<Method> methods_;
};

#endif // QNDRAWER_FLOWBUILDER_H
