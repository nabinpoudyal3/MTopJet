#include "UHH2/MTopJet/include/GenHists_particles.h"


GenHists_particles::GenHists_particles(uhh2::Context & ctx, const std::string & dirname): Hists(ctx, dirname){

  // book all histograms here
  number_top = book<TH1F>("number_top", "number of tops", 10, 0, 10);
  hadtop_pt = book<TH1F>("hadtop_pt", "p_{T}", 100, 0, 1000);
  leptop_pt = book<TH1F>("leptop_pt", "p_{T}", 100, 0, 1000);
  hadtop_mass = book<TH1F>("hadtop_mass", "Mass", 150, 100, 250);
  leptop_mass = book<TH1F>("leptop_mass", "Mass", 150, 100, 250);
  hadtop_phi = book<TH1F>("hadtop_phi", "#Phi", 30, -6, 6);
  leptop_phi = book<TH1F>("leptop_phi", "#Phi", 30, -6, 6);
  lepton_pt = book<TH1F>("lepton_pt", "p_{T}", 100, 0, 1000);
  deltaR_hadtop_b = book<TH1F>("deltaR_hadtop_b", "#Delta R(had. top, b)", 30, 0, 6);
  deltaR_leptop_b = book<TH1F>("deltaR_leptop_b", "#Delta R(lep. top, b)", 30, 0, 6);
  deltaR_lep_b = book<TH1F>("deltaR_lep_b", "#Delta R(lep, b)", 30, 0, 6);
  deltaR_lep_neu = book<TH1F>("deltaR_lep_neu", "#Delta R(lepton, neutrino)", 30, 0, 6);
  deltaR_hadtop_leptop = book<TH1F>("deltaR_hadtop_leptop", "#Delta R(had. top, lep. top)", 30, 0, 6);
  deltaPhi_hadtop_leptop = book<TH1F>("deltaPhi_hadtop_leptop", "#Delta #Phi(had. top, lep. top)", 60, 0, 6);
  deltaR_hadtop_jet1 = book<TH1F>("deltaR_hadtop_jet1", "#Delta R(had. top, jet1)", 60, 0, 6);
  deltaPT_hadtop_jet1 = book<TH1F>("deltaPT_hadtop_jet1", "p_{T,jet} - p_{T,top}", 50, -100, 100);
  deltaR_hadtop_genjet1 = book<TH1F>("deltaR_hadtop_genjet1", "#Delta R(had. top, gen jet)", 60, 0, 6);
  deltaPT_hadtop_genjet1 = book<TH1F>("deltaPT_hadtop_genjet1", "p_{T,gen jet} - p_{T,top}", 50, -100, 100);
  // handle for ttbargen class
  h_ttbargen=ctx.get_handle<TTbarGen>("ttbargen");

  // handle for jets
  h_hadjets=ctx.get_handle<std::vector<TopJet>>("XCone33_had_Combined_Corrected");
  h_hadjets_gen=ctx.get_handle<std::vector<GenTopJet>>("GEN_XCone33_had_Combined");

}



void GenHists_particles::fill(const Event & event){

  const auto & ttbargen = event.get(h_ttbargen);
  // get weight
  double weight = event.weight;

  // get jets
  std::vector<TopJet> hadjets = event.get(h_hadjets);
  std::vector<GenTopJet> hadjets_gen = event.get(h_hadjets_gen);

  // cout tops
  int n_top = 0;
  std::vector<GenParticle>* genparts = event.genparticles;
  for (unsigned int i=0; i<(genparts->size()); ++i){
    GenParticle p = genparts->at(i);
    if(abs(p.pdgId()) == 6){
      ++n_top;
    }
  }

  number_top->Fill(n_top, weight);

  // get particles from ttbargen class
  GenParticle tophad, toplep, bot, q1, q2, bot_lep, lep1, lep2, lepton, neutrino;
  if(ttbargen.IsTopHadronicDecay()){
    tophad = ttbargen.Top();
    toplep = ttbargen.Antitop();
    bot = ttbargen.bTop();
    q1 = ttbargen.Wdecay1();
    q2 = ttbargen.Wdecay2();
    bot_lep = ttbargen.bAntitop();
    lep1 = ttbargen.WMinusdecay1();
    lep2 = ttbargen.WMinusdecay2();
  }
  else if(ttbargen.IsAntiTopHadronicDecay()){
    tophad = ttbargen.Antitop();
    toplep = ttbargen.Top();
    bot = ttbargen.bAntitop();
    q1 = ttbargen.WMinusdecay1();
    q2 = ttbargen.WMinusdecay2();
    bot_lep = ttbargen.bTop();
    lep1 = ttbargen.Wdecay1();
    lep2 = ttbargen.Wdecay2();
  }
  else if(!(ttbargen.IsTopHadronicDecay() || ttbargen.IsAntiTopHadronicDecay())){
    return;
  }

  //check which lep is neutrino and which is elec/muon
  if(abs(lep1.pdgId()) == 11 || abs(lep1.pdgId()) == 13){
    lepton = lep1;
    neutrino = lep2;
  }
  else if(abs(lep2.pdgId()) == 11 || abs(lep2.pdgId()) == 13){
    lepton = lep2;
    neutrino = lep1;
  }

  hadtop_pt->Fill(tophad.pt(), weight);
  leptop_pt->Fill(toplep.pt(), weight);
  hadtop_mass->Fill(tophad.v4().M(), weight);
  leptop_mass->Fill(toplep.v4().M(), weight);
  lepton_pt->Fill(lepton.pt(), weight);
  hadtop_phi->Fill(tophad.phi(), weight);
  leptop_phi->Fill(toplep.phi(), weight);
  deltaR_hadtop_b->Fill(deltaR(tophad, bot), weight);
  deltaR_leptop_b->Fill(deltaR(toplep, bot_lep), weight);
  deltaR_lep_b->Fill(deltaR(lepton, bot_lep), weight);
  deltaR_lep_neu->Fill(deltaR(lepton, neutrino), weight);
  deltaR_hadtop_leptop->Fill(deltaR(tophad, toplep), weight);

  if(hadjets.size()>0){
    deltaR_hadtop_jet1->Fill(deltaR(tophad, hadjets.at(0)), weight);
    deltaPT_hadtop_jet1->Fill(hadjets.at(0).pt() - tophad.pt(), weight);
  }
  if(hadjets_gen.size()>0){
    deltaR_hadtop_genjet1->Fill(deltaR(tophad, hadjets_gen.at(0)), weight);
    deltaPT_hadtop_genjet1->Fill(hadjets_gen.at(0).pt() - tophad.pt(), weight);
  }

  double had_phi, lep_phi, delta_phi;
  had_phi = tophad.phi() + M_PI;
  lep_phi = toplep.phi() + M_PI;
  delta_phi = abs(had_phi - lep_phi);
  deltaPhi_hadtop_leptop->Fill(delta_phi, weight);

  return;
}
