//
// Created by mikhail on 3/3/20.
//

#ifndef QNDRAWER_FILE_MANAGER_H
#define QNDRAWER_FILE_MANAGER_H

#include <DataContainer.h>
#include <Stats.h>
#include <TFile.h>
#include <string>
#include <utility>
class FileManager {
public:
  FileManager() = default;
  explicit FileManager(std::string name) : name_(std::move(name)) {}
  FileManager(std::string name, TFile *fileIn)
      : name_(std::move(name)), file_in_(fileIn) {}
  FileManager(std::string name,
              std::function<Qn::DataContainer<Qn::Stats>(
                  Qn::DataContainer<Qn::Stats>)> rebinProjectionRule)
      : name_(std::move(name)), rebin_projection_rule_(std::move(rebinProjectionRule)) {}
  virtual ~FileManager() = default;
  Qn::DataContainer<Qn::Stats> GetDataContainer(const std::string& container_name){
    if( !file_in_ ){
      std::cout << "ERROR: file is not set" << std::endl;
      abort();
    }
    Qn::DataContainer<Qn::Stats>* container{nullptr};
    file_in_->GetObject(container_name.data(), container);
    if( !container ){
      std::cout << "ERROR: no such a data container \"" << container_name << "\"" << std::endl;
      abort();
    }
    if( rebin_projection_rule_ )
      *container = rebin_projection_rule_( *container );
    return *container;
  }
  std::vector<Qn::DataContainer<Qn::Stats>> GetDataContainerVector(const std::vector<std::string>& container_names){
    std::vector<Qn::DataContainer<Qn::Stats>> data_containers;
    data_containers.reserve(container_names.size());
    for( const auto& name : container_names )
      data_containers.push_back(GetDataContainer(name));
    return data_containers;
  }
  Qn::DataContainer<Qn::Stats> GetMergedDataContainer(const std::vector<std::string>& container_names){
    auto data_containers = GetDataContainerVector(container_names);
    return MergeDataContainers(data_containers);
  }
  const std::string &GetName() const { return name_; }
  void SetRebinProjectionRule(
      const std::function<Qn::DataContainer<Qn::Stats>(
          Qn::DataContainer<Qn::Stats>)> &rebinProjectionRule) {
    rebin_projection_rule_ = rebinProjectionRule;
  }
  void SetFileIn(const std::shared_ptr<TFile> &fileIn) { file_in_ = fileIn; }
  void ReSetFileIn(TFile* fileIn) { file_in_.reset(fileIn); }
  void SetFileIn(const std::string& file_name){
    file_in_.reset(  TFile::Open( file_name.data() ) );
  }
  static Qn::DataContainer<Qn::Stats> MergeDataContainers( std::vector<Qn::DataContainer<Qn::Stats>> data_containers ){
    auto* array = new TList;
    Qn::DataContainer<Qn::Stats> out{ data_containers.front() };
    data_containers.erase( data_containers.begin() );
    for( auto &container : data_containers )
      array->AddLast( (Qn::DataContainer<Qn::Stats>*) &container );
    out.Merge( (TList*) array );
    return out;
  }
  static TGraphAsymmErrors* ToGraph( Qn::DataContainer<Qn::Stats> container, std::string title, std::array<int, 2> marker ){
    container.SetSetting( Qn::Stats::Settings::CORRELATEDERRORS );
    auto graph = Qn::DataContainerHelper::ToTGraph(container);
    graph->SetTitle(title.data());
    graph->SetMarkerStyle(marker.at(0));
    graph->SetMarkerColor(marker.at(1));
    graph->SetLineColor(marker.at(1));
    return graph;
  }

protected:
  std::string name_;
  std::function<Qn::DataContainer<Qn::Stats>(Qn::DataContainer<Qn::Stats>)> rebin_projection_rule_;
  std::shared_ptr<TFile> file_in_;
};

#endif // QNDRAWER_FILE_MANAGER_H
