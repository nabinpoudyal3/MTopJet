#pragma once
#include "UHH2/core/include/Event.h"
#include "UHH2/common/include/Utils.h"
#include "UHH2/core/include/Jet.h"
#include "UHH2/core/include/TopJet.h"
#include "UHH2/core/include/AnalysisModule.h"

#include <vector>
#include <iostream>
#include <fstream>
#include <math.h>

using namespace std;
using namespace uhh2;

double get_factor(double, double);
Particle GetLepton(uhh2::Event & event);

class CorrectionFactor: public uhh2::AnalysisModule{
public:

  explicit CorrectionFactor(uhh2::Context &,  const std::string &);
  virtual bool process(uhh2::Event & ) override; 
    
private:

  uhh2::Event::Handle<std::vector<TopJet>>h_oldjets;
  uhh2::Event::Handle<std::vector<TopJet>>h_newjets;

};
