#include "UHH2/MTopJet/include/RecoGenHists_subjets.h"


RecoGenHists_subjets::RecoGenHists_subjets(uhh2::Context & ctx, const std::string & dirname,  const std::string & type): Hists(ctx, dirname){
  // book all histograms here
  MassReso = book<TH1F>("MassResolution", "(M^{rec}_{jet} - M^{gen}_{jet}) / M^{gen}_{jet}) ", 90, -1.5, 1.5);
  PtReso = book<TH1F>("PtResolution", "(p^{rec}_{T, jet} - p^{gen}_{T, jet}) / p^{gen}_{T, jet}) ", 90, -1.5, 1.5);
  area_all = book<TH1F>("area_all", "area all jets", 50, 0., 1.0);

  PtReso_1 = book<TH1F>("PtResolution_1", "(p^{rec}_{T, jet} - p^{gen}_{T, jet}) / p^{gen}_{T, jet}) ", 90, -1.5, 1.5);
  PtReso_2 = book<TH1F>("PtResolution_2", "(p^{rec}_{T, jet} - p^{gen}_{T, jet}) / p^{gen}_{T, jet}) ", 90, -1.5, 1.5);
  PtReso_3 = book<TH1F>("PtResolution_3", "(p^{rec}_{T, jet} - p^{gen}_{T, jet}) / p^{gen}_{T, jet}) ", 90, -1.5, 1.5);
  PtReso_4 = book<TH1F>("PtResolution_4", "(p^{rec}_{T, jet} - p^{gen}_{T, jet}) / p^{gen}_{T, jet}) ", 90, -1.5, 1.5);
  PtReso_5 = book<TH1F>("PtResolution_5", "(p^{rec}_{T, jet} - p^{gen}_{T, jet}) / p^{gen}_{T, jet}) ", 90, -1.5, 1.5);
  PtReso_6 = book<TH1F>("PtResolution_6", "(p^{rec}_{T, jet} - p^{gen}_{T, jet}) / p^{gen}_{T, jet}) ", 90, -1.5, 1.5);
  PtReso_7 = book<TH1F>("PtResolution_7", "(p^{rec}_{T, jet} - p^{gen}_{T, jet}) / p^{gen}_{T, jet}) ", 90, -1.5, 1.5);
  PtReso_8 = book<TH1F>("PtResolution_8", "(p^{rec}_{T, jet} - p^{gen}_{T, jet}) / p^{gen}_{T, jet}) ", 90, -1.5, 1.5);
  PtReso_9 = book<TH1F>("PtResolution_9", "(p^{rec}_{T, jet} - p^{gen}_{T, jet}) / p^{gen}_{T, jet}) ", 90, -1.5, 1.5);
  PtReso_10 = book<TH1F>("PtResolution_10", "(p^{rec}_{T, jet} - p^{gen}_{T, jet}) / p^{gen}_{T, jet}) ", 90, -1.5, 1.5);

  PtReso_rec1 = book<TH1F>("PtResolution_rec1", "(p^{rec}_{T, jet} - p^{gen}_{T, jet}) / p^{gen}_{T, jet}) ", 90, -1.5, 1.5);
  PtReso_rec2 = book<TH1F>("PtResolution_rec2", "(p^{rec}_{T, jet} - p^{gen}_{T, jet}) / p^{gen}_{T, jet}) ", 90, -1.5, 1.5);
  PtReso_rec3 = book<TH1F>("PtResolution_rec3", "(p^{rec}_{T, jet} - p^{gen}_{T, jet}) / p^{gen}_{T, jet}) ", 90, -1.5, 1.5);
  PtReso_rec4 = book<TH1F>("PtResolution_rec4", "(p^{rec}_{T, jet} - p^{gen}_{T, jet}) / p^{gen}_{T, jet}) ", 90, -1.5, 1.5);
  PtReso_rec5 = book<TH1F>("PtResolution_rec5", "(p^{rec}_{T, jet} - p^{gen}_{T, jet}) / p^{gen}_{T, jet}) ", 90, -1.5, 1.5);
  PtReso_rec6 = book<TH1F>("PtResolution_rec6", "(p^{rec}_{T, jet} - p^{gen}_{T, jet}) / p^{gen}_{T, jet}) ", 90, -1.5, 1.5);
  PtReso_rec7 = book<TH1F>("PtResolution_rec7", "(p^{rec}_{T, jet} - p^{gen}_{T, jet}) / p^{gen}_{T, jet}) ", 90, -1.5, 1.5);
  PtReso_rec8 = book<TH1F>("PtResolution_rec8", "(p^{rec}_{T, jet} - p^{gen}_{T, jet}) / p^{gen}_{T, jet}) ", 90, -1.5, 1.5);
  PtReso_rec9 = book<TH1F>("PtResolution_rec9", "(p^{rec}_{T, jet} - p^{gen}_{T, jet}) / p^{gen}_{T, jet}) ", 90, -1.5, 1.5);
  PtReso_rec10 = book<TH1F>("PtResolution_rec10", "(p^{rec}_{T, jet} - p^{gen}_{T, jet}) / p^{gen}_{T, jet}) ", 90, -1.5, 1.5);

  min_mass_Wjet_rec = book<TH1F>("min_mass_Wjet_rec", "min M_{ij}", 60, 60, 120);
  min_mass_Wjet_gen = book<TH1F>("min_mass_Wjet_gen", "min M_{ij}", 60, 60, 120);
  WMassReso = book<TH1F>("WMassResolution", "(M^{rec}_{W} - M^{gen}_{W}) / M^{gen}_{W}) ", 90, -1.5, 1.5);

  // handle for clustered jets
  if(type == "jec"){
    h_hadjets=ctx.get_handle<std::vector<TopJet>>("XCone33_had_Combined");
    h_recjets=ctx.get_handle<std::vector<TopJet>>("xconeCHS");
  }
  else if(type == "raw"){
    h_hadjets=ctx.get_handle<std::vector<TopJet>>("XCone33_had_Combined_noJEC");
    h_recjets=ctx.get_handle<std::vector<TopJet>>("xconeCHS_noJEC");
  }
  else if(type == "cor"){
    h_hadjets=ctx.get_handle<std::vector<TopJet>>("XCone33_had_Combined_Corrected");
    h_recjets=ctx.get_handle<std::vector<TopJet>>("xconeCHS_Corrected");
  }
  h_genjets=ctx.get_handle<std::vector<GenTopJet>>("genXCone33TopJets");

}



void RecoGenHists_subjets::fill(const Event & event){

  // get weight
  double weight = event.weight;
  //---------------------------------------------------------------------------------------
  //--------------------------------- define needed objects-----------------------------------
  //---------------------------------------------------------------------------------------
  // define all objects needed
  std::vector<TopJet> rec = event.get(h_recjets);
  std::vector<TopJet> had = event.get(h_hadjets);
  std::vector<GenTopJet> gen = event.get(h_genjets);
  std::vector<Jet> rec_sub;
  std::vector<Particle> gen_sub;

  // only look in had subjets, to not correct for lepton
  int had_nr = 0;
  if(deltaR(had.at(0), rec.at(0)) > deltaR(had.at(0), rec.at(1))) had_nr = 1;

  for(unsigned int j=0; j<rec.at(had_nr).subjets().size(); j++){
    rec_sub.push_back(rec.at(had_nr).subjets().at(j));
  }
  // get all subjets on gen level
  for(unsigned int i=0; i<gen.size(); i++){
    for(unsigned int j=0; j<gen.at(i).subjets().size(); j++){
      gen_sub.push_back(gen.at(i).subjets().at(j));
    }
  }

  if(rec_sub.size() < 1) return;
  if(gen_sub.size() < 1) return;

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
  double gen_pt, rec_pt, R;

  // do matching
  for(unsigned int i=0; i<rec_sub.size(); i++){
    dR = 1000;
    nearest_j = 100;
    area_all->Fill(rec_sub.at(i).jetArea(), weight);
    for(unsigned int j=0; j<gen_sub.size(); j++){
      dR_temp = uhh2::deltaR(rec_sub.at(i), gen_sub.at(j));
      if(dR_temp < dR){
        dR = dR_temp;
        nearest_j = j;
      }
    }

    if(nearest_j == 100) return;
    gen_pt = gen_sub.at(nearest_j).v4().Pt();
    rec_pt = rec_sub.at(i).v4().Pt();
    R = (rec_pt - gen_pt) / gen_pt;

    if(nearest_j != 100 && dR <= 0.2){
      PtReso->Fill( R, weight );
      MassReso->Fill( (rec_sub.at(i).v4().M() - gen_sub.at(nearest_j).v4().M())/gen_sub.at(nearest_j).v4().M() , weight );
      if(gen_pt <= 50) PtReso_1->Fill( R, weight );
      if(gen_pt > 50 && gen_pt <= 80) PtReso_2->Fill( R, weight );
      if(gen_pt > 80 && gen_pt <= 120) PtReso_3->Fill( R, weight );
      if(gen_pt > 120 && gen_pt <= 170) PtReso_4->Fill( R, weight );
      if(gen_pt > 170 && gen_pt <= 220) PtReso_5->Fill( R, weight );
      if(gen_pt > 220 && gen_pt <= 270) PtReso_6->Fill( R, weight );
      if(gen_pt > 270 && gen_pt <= 320) PtReso_7->Fill( R, weight );
      if(gen_pt > 320 && gen_pt <= 370) PtReso_8->Fill( R, weight );
      if(gen_pt > 370 && gen_pt <= 420) PtReso_9->Fill( R, weight );
      if(gen_pt > 420) PtReso_10->Fill( R, weight );

      if(rec_pt <= 50) PtReso_rec1->Fill( R, weight );
      if(rec_pt > 50 && rec_pt <= 80) PtReso_rec2->Fill( R, weight );
      if(rec_pt > 80 && rec_pt <= 120) PtReso_rec3->Fill( R, weight );
      if(rec_pt > 120 && rec_pt <= 170) PtReso_rec4->Fill( R, weight );
      if(rec_pt > 170 && rec_pt <= 220) PtReso_rec5->Fill( R, weight );
      if(rec_pt > 220 && rec_pt <= 270) PtReso_rec6->Fill( R, weight );
      if(rec_pt > 270 && rec_pt <= 320) PtReso_rec7->Fill( R, weight );
      if(rec_pt > 320 && rec_pt <= 370) PtReso_rec8->Fill( R, weight );
      if(rec_pt > 370 && rec_pt <= 420) PtReso_rec9->Fill( R, weight );
      if(rec_pt > 420) PtReso_rec10->Fill( R, weight );
    }

  }
  //---------------------------------------------------------------------------------------
  //--------------------------------- add subjets to reconstruct W ------------------------
  //---------------------------------------------------------------------------------------
  TLorentzVector Wjet_rec;
  double M_min_rec = 1000;
  double M_temp = 0;
  double px, py, pz, E;
  for(unsigned int i=0; i<rec.at(0).subjets().size(); i++){
    for(unsigned int j=0; j<rec.at(0).subjets().size(); j++){
      if(i != j){
        px = rec.at(0).subjets().at(i).v4().Px() + rec.at(0).subjets().at(j).v4().Px();
        py = rec.at(0).subjets().at(i).v4().Py() + rec.at(0).subjets().at(j).v4().Py();
        pz = rec.at(0).subjets().at(i).v4().Pz() + rec.at(0).subjets().at(j).v4().Pz();
        E = rec.at(0).subjets().at(i).v4().E() + rec.at(0).subjets().at(j).v4().E();
        Wjet_rec.SetPxPyPzE(px, py, pz, E);
        M_temp = Wjet_rec.M();
        if(M_temp < M_min_rec) M_min_rec = M_temp;
      }
    }
  }
  TLorentzVector Wjet_gen;
  double M_min_gen = 1000;
  for(unsigned int i=0; i<gen.at(0).subjets().size(); i++){
    for(unsigned int j=0; j<gen.at(0).subjets().size(); j++){
      if(i != j){
        px = gen.at(0).subjets().at(i).v4().Px() + gen.at(0).subjets().at(j).v4().Px();
        py = gen.at(0).subjets().at(i).v4().Py() + gen.at(0).subjets().at(j).v4().Py();
        pz = gen.at(0).subjets().at(i).v4().Pz() + gen.at(0).subjets().at(j).v4().Pz();
        E = gen.at(0).subjets().at(i).v4().E() + gen.at(0).subjets().at(j).v4().E();
        Wjet_gen.SetPxPyPzE(px, py, pz, E);
        M_temp = Wjet_gen.M();
        if(M_temp < M_min_gen) M_min_gen = M_temp;
      }
    }
  }
  min_mass_Wjet_rec->Fill(M_min_rec, weight);
  min_mass_Wjet_gen->Fill(M_min_gen, weight);
  WMassReso->Fill( (M_min_rec - M_min_gen) / M_min_gen, weight);
  //---------------------------------------------------------------------------------------
  //---------------------------------------------------------------------------------------


}
