
#include <TH1.h>
#include <TH2.h>
#include <TFile.h>


class MMefficiencies {

public:
  TFile* effs; 
  TFile* effs_old;
  TFile* effs_new_el; 

  TH1* el_fakeEff1D_pt_1516; 
  TH1* el_fakeEff1D_pt_17; 
  TH1* el_fakeEff1D_pt_18; 
  TH1* mu_fakeEff1D_pt_1516; 
  TH1* mu_fakeEff1D_pt_17; 
  TH1* mu_fakeEff1D_pt_18; 

  TH1* el_fakeEff1D_pt_xsecup_1516; 
  TH1* el_fakeEff1D_pt_xsecup_17; 
  TH1* el_fakeEff1D_pt_xsecup_18; 
  TH1* mu_fakeEff1D_pt_xsecup_1516; 
  TH1* mu_fakeEff1D_pt_xsecup_17; 
  TH1* mu_fakeEff1D_pt_xsecup_18; 

  TH1* el_fakeEff1D_pt_xsecdw_1516; 
  TH1* el_fakeEff1D_pt_xsecdw_17; 
  TH1* el_fakeEff1D_pt_xsecdw_18; 
  TH1* mu_fakeEff1D_pt_xsecdw_1516; 
  TH1* mu_fakeEff1D_pt_xsecdw_17; 
  TH1* mu_fakeEff1D_pt_xsecdw_18; 
  
  TH1* mu_fakeEff1D_1mutrig_pt_1516; 
  TH1* mu_fakeEff1D_1mutrig_pt_17; 
  TH1* mu_fakeEff1D_1mutrig_pt_18; 
  
  TH2* el_fakeEff2D_pt_eta;

  TH2* el_realEff2D_pt_eta_1516; 
  TH2* el_realEff2D_pt_eta_17; 
  TH2* el_realEff2D_pt_eta_18; 

  TH2* mu_realEff2D_pt_eta_1516; 
  TH2* mu_realEff2D_pt_eta_17; 
  TH2* mu_realEff2D_pt_eta_18; 

  TH2* mu_realEff2D_1mutrig_pt_eta_1516; 
  TH2* mu_realEff2D_1mutrig_pt_eta_17; 
  TH2* mu_realEff2D_1mutrig_pt_eta_18; 

  TH1* fake_effs = new TH1F(); 
  TH2* fake_effs_2D = new TH2F(); 
  TH2* real_effs = new TH2F(); 
    
  MMefficiencies() {

    effs = new TFile("MatrixMethod/Efficiencies/FNPntuple_ZMET_NOV2022_R21_v3.root");

    //-------------------//
    // Fake efficiencies //
    //-------------------//
    
    // Electron 
    el_fakeEff1D_pt_1516 = (TH1*)effs->Get("eff_pt_em_lhloose_2015_FAKE2L21_data15-16");
    el_fakeEff1D_pt_17 = (TH1*)effs->Get("eff_pt_em_lhloose_2017_FAKE2L21_data17");
    el_fakeEff1D_pt_18 = (TH1*)effs->Get("eff_pt_em_lhloose_2018_FAKE2L21_data18");
    // Muon (2mu trig.) 
    mu_fakeEff1D_pt_1516 = (TH1*)effs->Get("eff_pt_m_dimu_2015_FAKE2L21_data15-16");
    mu_fakeEff1D_pt_17 = (TH1*)effs->Get("eff_pt_m_dimu_2017_FAKE2L21_data17");
    mu_fakeEff1D_pt_18 = (TH1*)effs->Get("eff_pt_m_dimu_2018_FAKE2L21_data18");
    // Muon (1mu trig.) 
    mu_fakeEff1D_1mutrig_pt_1516 = (TH1*)effs->Get("eff_pt_m_ivarmed_2015_FAKE2L21_data15-16");
    mu_fakeEff1D_1mutrig_pt_17 = (TH1*)effs->Get("eff_pt_m_ivarmed_2017_FAKE2L21_data17");
    mu_fakeEff1D_1mutrig_pt_18 = (TH1*)effs->Get("eff_pt_m_ivarmed_2018_FAKE2L21_data18");

    // X-sec variations 

    // Electron 
    el_fakeEff1D_pt_xsecup_1516 = (TH1*)effs->Get("eff_pt_em_lhloose_2015_FAKE2L21_xsecup_data15-16");
    el_fakeEff1D_pt_xsecup_17 = (TH1*)effs->Get("eff_pt_em_lhloose_2017_FAKE2L21_xsecup_data17");
    el_fakeEff1D_pt_xsecup_18 = (TH1*)effs->Get("eff_pt_em_lhloose_2018_FAKE2L21_xsecup_data18");
    el_fakeEff1D_pt_xsecdw_1516 = (TH1*)effs->Get("eff_pt_em_lhloose_2015_FAKE2L21_xsecdw_data15-16");
    el_fakeEff1D_pt_xsecdw_17 = (TH1*)effs->Get("eff_pt_em_lhloose_2017_FAKE2L21_xsecdw_data17");
    el_fakeEff1D_pt_xsecdw_18 = (TH1*)effs->Get("eff_pt_em_lhloose_2018_FAKE2L21_xsecdw_data18");
    // Muon (2mu trig.) 
    mu_fakeEff1D_pt_xsecup_1516 = (TH1*)effs->Get("eff_pt_m_dimu_2015_FAKE2L21_xsecup_data15-16");
    mu_fakeEff1D_pt_xsecup_17 = (TH1*)effs->Get("eff_pt_m_dimu_2017_FAKE2L21_xsecup_data17");
    mu_fakeEff1D_pt_xsecup_18 = (TH1*)effs->Get("eff_pt_m_dimu_2018_FAKE2L21_xsecup_data18");
    mu_fakeEff1D_pt_xsecdw_1516 = (TH1*)effs->Get("eff_pt_m_dimu_2015_FAKE2L21_xsecdw_data15-16");
    mu_fakeEff1D_pt_xsecdw_17 = (TH1*)effs->Get("eff_pt_m_dimu_2017_FAKE2L21_xsecdw_data17");
    mu_fakeEff1D_pt_xsecdw_18 = (TH1*)effs->Get("eff_pt_m_dimu_2018_FAKE2L21_xsecdw_data18");

    
    //-------------------//
    // Real efficiencies //
    //-------------------//

    // Electron
    el_realEff2D_pt_eta_1516 = (TH2*)effs->Get("eff_pt_eta_em_lhloose_2015_REAL2L04_mc16a");
    el_realEff2D_pt_eta_17 = (TH2*)effs->Get("eff_pt_eta_em_lhloose_2017_REAL2L04_mc16d");
    el_realEff2D_pt_eta_18 = (TH2*)effs->Get("eff_pt_eta_em_lhloose_2018_REAL2L04_mc16e");
    // Muon (2mu trig) 
    mu_realEff2D_pt_eta_1516 = (TH2*)effs->Get("eff_pt_eta_m_dimu_2015_REAL2L04_mc16a");
    mu_realEff2D_pt_eta_17 = (TH2*)effs->Get("eff_pt_eta_m_dimu_2017_REAL2L04_mc16d");
    mu_realEff2D_pt_eta_18 = (TH2*)effs->Get("eff_pt_eta_m_dimu_2018_REAL2L04_mc16e");
    // Muon (1mu trig) 
    mu_realEff2D_1mutrig_pt_eta_1516 = (TH2*)effs->Get("eff_pt_eta_m_ivarmed_2015_REAL2L04_mc16a");
    mu_realEff2D_1mutrig_pt_eta_17 = (TH2*)effs->Get("eff_pt_eta_m_ivarmed_2017_REAL2L04_mc16d");
    mu_realEff2D_1mutrig_pt_eta_18 = (TH2*)effs->Get("eff_pt_eta_m_ivarmed_2018_REAL2L04_mc16e");

  }

  ~MMefficiencies() {

    effs->Close(); //effs_old->Close(); effs_new_el->Close(); 
    delete effs; //delete effs_old; delete effs_new_el; 
  }

  double fakeEff1D(double pt, int lep, int year) {

    if(lep==1){
      if(year==2015 || year==2016){ fake_effs = el_fakeEff1D_pt_1516; }
      if(year==2017){ fake_effs = el_fakeEff1D_pt_17; }
      if(year==2018){ fake_effs = el_fakeEff1D_pt_18; }
    }
    if(lep==2){
      if(year==2015 || year==2016){ fake_effs = mu_fakeEff1D_pt_1516; }
      if(year==2017){ fake_effs = mu_fakeEff1D_pt_17; }
      if(year==2018){ fake_effs = mu_fakeEff1D_pt_18; }
    }
    if(lep==3){
      if(year==2015 || year==2016){ fake_effs = mu_fakeEff1D_1mutrig_pt_1516; }
      if(year==2017){ fake_effs = mu_fakeEff1D_1mutrig_pt_17; }
      if(year==2018){ fake_effs = mu_fakeEff1D_1mutrig_pt_18; }
    }

    Float_t f = fake_effs->GetBinContent(fake_effs->FindBin(pt));

    return f; 
  }

  double fakeEff1D_up(double pt, int lep, int year) {

    if(lep==1){
      if(year==2015 || year==2016){ fake_effs = el_fakeEff1D_pt_xsecup_1516; }
      if(year==2017){ fake_effs = el_fakeEff1D_pt_xsecup_17; }
      if(year==2018){ fake_effs = el_fakeEff1D_pt_xsecup_18; }
    }
    if(lep==2){
      if(year==2015 || year==2016){ fake_effs = mu_fakeEff1D_pt_xsecup_1516; }
      if(year==2017){ fake_effs = mu_fakeEff1D_pt_xsecup_17; }
      if(year==2018){ fake_effs = mu_fakeEff1D_pt_xsecup_18; }
    }

    Float_t f = fake_effs->GetBinContent(fake_effs->FindBin(pt));
    
    return f; 
  }


  double fakeEff1D_dw(double pt, int lep, int year) {

    if(lep==1){
      if(year==2015 || year==2016){ fake_effs = el_fakeEff1D_pt_xsecdw_1516; }
      if(year==2017){ fake_effs = el_fakeEff1D_pt_xsecdw_17; }
      if(year==2018){ fake_effs = el_fakeEff1D_pt_xsecdw_18; }
    }
    if(lep==2){
      if(year==2015 || year==2016){ fake_effs = mu_fakeEff1D_pt_xsecdw_1516; }
      if(year==2017){ fake_effs = mu_fakeEff1D_pt_xsecdw_17; }
      if(year==2018){ fake_effs = mu_fakeEff1D_pt_xsecdw_18; }
    }

    Float_t f = fake_effs->GetBinContent(fake_effs->FindBin(pt));

    return f; 
  }

  
  
  double fakeEff2D(double pt, double eta) {

    fake_effs_2D = el_fakeEff2D_pt_eta;

    if(pt<30){ pt=30.0; } // 

    return fake_effs_2D->GetBinContent(fake_effs->FindBin(pt, TMath::Abs(eta)));

  }


  double realEff2D(double pt, double eta, int lep, int year) {

    if(lep==1){
      //real_effs = el_realEff2D_pt_eta_18;
      if(year==2015 || year==2016){ real_effs = el_realEff2D_pt_eta_1516; }
      if(year==2017){ real_effs = el_realEff2D_pt_eta_17; }
      if(year==2018){ real_effs = el_realEff2D_pt_eta_18; }
    }
    if(lep==2){
      if(year==2015 || year==2016){ real_effs = mu_realEff2D_pt_eta_1516; }
      if(year==2017){ real_effs = mu_realEff2D_pt_eta_17; }
      if(year==2018){ real_effs = mu_realEff2D_pt_eta_18; }
    }
    if(lep==3){ // Muon with single-muon trigger
      if(year==2015 || year==2016){ real_effs = mu_realEff2D_1mutrig_pt_eta_1516; }
      if(year==2017){ real_effs = mu_realEff2D_1mutrig_pt_eta_17; }
      if(year==2018){ real_effs = mu_realEff2D_1mutrig_pt_eta_18; }
    }

    Float_t r = real_effs->GetBinContent(real_effs->FindBin(pt,TMath::Abs(eta)));

    return r; 
  }

};
