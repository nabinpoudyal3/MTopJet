#include <iostream>
#include <memory>

#include <UHH2/core/include/AnalysisModule.h>
#include <UHH2/core/include/Event.h>
#include <UHH2/core/include/Selection.h>

#include <UHH2/common/include/CleaningModules.h>
#include <UHH2/common/include/NSelections.h>
#include <UHH2/common/include/LumiSelection.h>
#include <UHH2/common/include/TriggerSelection.h>
#include <UHH2/common/include/JetCorrections.h>
#include <UHH2/common/include/ObjectIdUtils.h>
#include <UHH2/common/include/MuonIds.h>
#include <UHH2/common/include/ElectronIds.h>
#include <UHH2/common/include/JetIds.h>
#include <UHH2/common/include/TopJetIds.h>
#include <UHH2/common/include/TTbarGen.h>
#include <UHH2/common/include/Utils.h>
#include <UHH2/common/include/AdditionalSelections.h>
#include <UHH2/common/include/TTbarGenHists.h>

#include <UHH2/MTopJet/include/ModuleBASE.h>
#include <UHH2/MTopJet/include/MTopJetSelections.h>
#include <UHH2/MTopJet/include/MTopJetGenSelections.h>
#include <UHH2/MTopJet/include/MTopJetUtils.h>
class MTopJetGenSelectionModule : public ModuleBASE {

 public:
  explicit MTopJetGenSelectionModule(uhh2::Context&);
  virtual bool process(uhh2::Event&) override;

 protected:

  // cleaners
  
  // selections
  std::unique_ptr<uhh2::AnalysisModule> ttgenprod;

  std::unique_ptr<uhh2::Selection> SemiLepDecay;


  // store Hist collection as member variables
  std::unique_ptr<Hists> h_TTbarGen_01;


};

MTopJetGenSelectionModule::MTopJetGenSelectionModule(uhh2::Context& ctx){

  //// CONFIGURATION

 
  ////

  //// COMMON MODULES

  const std::string ttbar_gen_label("ttbargen");

  ttgenprod.reset(new TTbarGenProducer(ctx, ttbar_gen_label, false));

  ////

  //// OBJ CLEANING
 
  //

  // set up Hists classes:
  h_TTbarGen_01.reset(new TTbarGenHists(ctx, "TTbarGen_01"));

  // EVENT SELECTION
  SemiLepDecay.reset(new TTbarSemilep(ctx)); // SemiLep but only muon and elec channel

}

bool MTopJetGenSelectionModule::process(uhh2::Event& event){

  //  COMMON MODULES
  ttgenprod->process(event);
  const bool pass_semilep = SemiLepDecay->passes(event);
  if(!pass_semilep) return false;
  h_TTbarGen_01->fill(event);
  return true;
}

UHH2_REGISTER_ANALYSIS_MODULE(MTopJetGenSelectionModule)