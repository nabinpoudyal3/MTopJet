#include "UHH2/MTopJet/include/CorrectionHists_subjets.h"
#include <vector>

CorrectionHists_subjets::CorrectionHists_subjets(uhh2::Context & ctx, const std::string & dirname): Hists(ctx, dirname){

  // setup hists for every pt-eta bin
  unsigned int no_ptbins = 6; // rows
  unsigned int no_etabins = 12; // columns
  TH1F* initial_value;
  TH2F* initial_value_2d;
  pt_reso.resize(no_ptbins, std::vector<TH1F*>(no_etabins, initial_value));
  pt_eta.resize(no_ptbins, std::vector<TH2F*>(no_etabins, initial_value_2d));
  event_count.resize(no_ptbins, std::vector<TH1F*>(no_etabins, initial_value));

  /* 
     TO DO

     -add pt_rec[pt_bin][eta_bin]
     -get pt_bins to pt_gen bins
     -define arrays with binning -> set [pt_bin][eta_bin] in a loop

  */

  for(unsigned int pt_bin = 0; pt_bin < no_ptbins; pt_bin++){
    for(unsigned int eta_bin = 0; eta_bin < no_etabins; eta_bin++){
      std::string pt_string = std::to_string(pt_bin);
      std::string eta_string = std::to_string(eta_bin);
      pt_reso[pt_bin][eta_bin] = book<TH1F>("PtReso_"+pt_string +eta_string, "p^{rec}_{T, jet} / p^{gen}_{T, jet}", 90, -1.5, 1.5);
      pt_eta[pt_bin][eta_bin] = book<TH2F>("pt_eta_"+pt_string +eta_string, "x=pt y=eta",  50, 0, 500, 20, -4, 4);
      event_count[pt_bin][eta_bin] = book<TH1F>("Count_"+pt_string +eta_string, "a.u.", 1, 0.5, 1.5);
    }
  }

 book<TH2F>("TopJetMass1_TopJetMass2", "x=M_Top1 y=M_Top2", 30, 0, 300., 30, 0, 300.);


  // handle for clustered jets
  h_recjets=ctx.get_handle<std::vector<TopJet>>("XConeTopJets");
  h_recjets_noJEC=ctx.get_handle<std::vector<TopJet>>("XConeTopJets_noJEC");
  h_hadjets=ctx.get_handle<std::vector<Jet>>("XCone33_had_Combined_noJEC");
  h_genjets=ctx.get_handle<std::vector<GenTopJet>>("genXCone33TopJets");
  h_hadgenjets=ctx.get_handle<std::vector<Particle>>("GEN_XCone33_had_Combined");

}



void CorrectionHists_subjets::fill(const Event & event){

  // get weight
  double weight = event.weight;
  //---------------------------------------------------------------------------------------
  //--------------------------------- define needed objects-----------------------------------
  //---------------------------------------------------------------------------------------
  // define all objects needed
  std::vector<TopJet> recjets = event.get(h_recjets);
  std::vector<TopJet> recjets_noJEC = event.get(h_recjets_noJEC);
  std::vector<Jet> hadjets = event.get(h_hadjets);

  std::vector<GenTopJet> genjets = event.get(h_genjets);
  std::vector<Particle> hadgenjets = event.get(h_hadgenjets);

  // first find had. jet and only use those subjets (without using JEC)
  double dRrec = 100;
  double dRrec_temp = 100;
  int i_had = 0;
  for(unsigned int i=0; i<recjets_noJEC.size(); i++){
    dRrec_temp = deltaR(recjets_noJEC.at(i), hadjets.at(0));
    if(dRrec_temp < dRrec){
      dRrec = dRrec_temp;
      i_had = i;
    }
  }

  std::vector<Jet> rec_sub_noJEC = recjets_noJEC.at(i_had).subjets();
  std::vector<Jet> rec_sub = recjets.at(i_had).subjets();

  // also get had subjets on gen level
  double dRgen = 100;
  double dRgen_temp = 100;
  int i_genhad = 0;
  for(unsigned int i=0; i<genjets.size(); i++){
    dRgen_temp = deltaR(genjets.at(i), hadgenjets.at(0));
    if(dRgen_temp < dRgen){
      dRgen = dRgen_temp;
      i_genhad = i;
    }
  }

  std::vector<Particle> gen_sub = genjets.at(i_genhad).subjets();

  // do pt cut on subjets without JEC, only continue for pt > 30
  bool pt_valid = true;
  for(unsigned int i=0; i<rec_sub_noJEC.size(); i++){
    if(rec_sub_noJEC.at(i).v4().Pt() < 30) pt_valid = false;
  }
  if(!pt_valid) return;


  /* ******************************************************************************
     matching between gen and reco jets:
     - a rec jet is called isolated if the next jet is not within 2R. An isolated jet should be spherical and more simelar to an ak4 jet
     - for each reco jet, calc distance to all other gen jets
     - gen jet with lowest distance is a match if distance is < 0.2
     - then calculate resolution with reco jet and matched gen jet
     - to do: account for double counting
  ********************************************************************************* */

  double dR;
  double dR_temp;
  int nearest_j;
  double gen_pt;
  //double gen_eta;
  double rec_pt;
  double rec_eta;
  double R;
  int pt_bin = 100;
  int eta_bin = 100;
  // do matching
  for(unsigned int i=0; i<rec_sub.size(); i++){
    dR = 1000;
    nearest_j = 100;
    for(unsigned int j=0; j<gen_sub.size(); j++){
      dR_temp = uhh2::deltaR(rec_sub.at(i), gen_sub.at(j));
      if(dR_temp < dR){
	dR = dR_temp;
	nearest_j = j;
      }
    }
    gen_pt=gen_sub.at(nearest_j).v4().Pt();
    //gen_eta=gen_sub.at(nearest_j).v4().Eta();
    rec_pt=rec_sub.at(i).v4().Pt();
    rec_eta=rec_sub.at(i).v4().Eta();
    R = rec_pt/gen_pt;
    if(nearest_j != 100 && dR <= 0.2){
      // bins in pt_rec
      if(rec_pt <= 80) pt_bin = 0;
      if(rec_pt > 80 && rec_pt <= 130) pt_bin = 1;
      if(rec_pt > 130 && rec_pt <= 180) pt_bin = 2; 
      if(rec_pt > 180 && rec_pt <= 250) pt_bin = 3;
      if(rec_pt > 250 && rec_pt <= 350) pt_bin = 4;
      if(rec_pt > 350) pt_bin = 5;
      // bins in eta_gen
      if(rec_eta <= -1.5) eta_bin = 0;
      if(rec_eta > -1.5 && rec_eta <= -1.0) eta_bin = 1;
      if(rec_eta > -1.0 && rec_eta <= -0.7) eta_bin = 2; 
      if(rec_eta > -0.7 && rec_eta <= -0.4) eta_bin = 3;
      if(rec_eta > -0.4 && rec_eta <= -0.2) eta_bin = 4;
      if(rec_eta > -0.2 && rec_eta <= -0.0) eta_bin = 5;
      if(rec_eta > 0.0 && rec_eta <= 0.2) eta_bin = 6;
      if(rec_eta > 0.2 && rec_eta <= 0.4) eta_bin = 7;
      if(rec_eta > 0.4 && rec_eta <= 0.7) eta_bin = 8;
      if(rec_eta > 0.7 && rec_eta <= 1.0) eta_bin = 9;
      if(rec_eta > 1.0 && rec_eta <= 1.5) eta_bin = 10;
      if(rec_eta > 1.5) eta_bin = 11;
      if(pt_bin != 100 && eta_bin != 100){
	pt_reso[pt_bin][eta_bin]->Fill(R, weight);
	pt_eta[pt_bin][eta_bin]->Fill(rec_pt, rec_eta, weight);
	event_count[pt_bin][eta_bin]->Fill(1, weight);

      }
    }

  }

  //---------------------------------------------------------------------------------------
  //---------------------------------------------------------------------------------------
 

}

