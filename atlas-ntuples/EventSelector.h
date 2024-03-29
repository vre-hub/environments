/////////////////////////////////////////////////////////
// This class has been automatically generated on
// Tue Jul 28 13:33:11 2020 by ROOT version 6.20/06
// from TTree nominal/
// found on file: minitree_nominal_final.root
//////////////////////////////////////////////////////////

#ifndef EventSelector_h
#define EventSelector_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TObjString.h>
#include <TSelector.h>
#include <TTreeReader.h>
#include <TTreeReaderValue.h>
#include <TTreeReaderArray.h>
#include <TH2.h>

// Headers needed by this particular selector
#include <vector>

class EventSelector : public TSelector {
public :
  TTreeReader     fReader;  //!the tree reader
  TTreeReader     fReader_nom; //! tree reader for branches only in nominal samples
  TTreeReader     fReader_sys; //! tree reader for branches only relevant with systematics 
  TTree          *fChain = 0;   //!pointer to the analyzed TTree or TChain

  // Trees
  TTree *tree; //!  
  TTree *tree_MUON_SCALE__1up; //!  
  TTree *tree_MUON_EFF_RECO_SYS__1up; //!
  
   // 1D histograms
   map<TString, TH1*> h_pt1; //!
   map<TString, TH1*> h_pt2; //!    
   map<TString, TH1*> h_eta1; //!
   map<TString, TH1*> h_eta2; //!    
   map<TString, TH1*> h_phi1; //!
   map<TString, TH1*> h_phi2; //!    
   map<TString, TH1*> h_met; //!  
   map<TString, TH1*> h_met_lin; //!  
   map<TString, TH1*> h_met_phi; //!    
   map<TString, TH1*> h_met_sig; //!       
   map<TString, TH1*> h_met_sig_log; //!       
   map<TString, TH1*> h_met_sig_rel; //!       
   map<TString, TH1*> h_met_ht; //!       
   map<TString, TH1*> h_met_rel; //!       
   map<TString, TH1*> h_met_res; //!    
   map<TString, TH1*> h_met_soft; //!    
   map<TString, TH1*> h_met_muon; //!    
   map<TString, TH1*> h_met_elec; //!    
   map<TString, TH1*> h_met_jet; //!    
   map<TString, TH1*> h_dphi; //!    
   map<TString, TH1*> h_dphi_rel; //!    
   map<TString, TH1*> h_mll; //!
   map<TString, TH1*> h_mll_low; //!
   map<TString, TH1*> h_mll_lin; //!
   map<TString, TH1*> h_bornMass; //! 
   map<TString, TH1*> h_ptll; //! 
   map<TString, TH1*> h_mt2; //!    
   map<TString, TH1*> h_mt; //! 
   map<TString, TH1*> h_dR_ll; //!    
   map<TString, TH1*> h_dphi_ll; //!    
   map<TString, TH1*> h_njets; //! 
   map<TString, TH1*> h_ncjets; //! 
   map<TString, TH1*> h_nfjets; //! 
   map<TString, TH1*> h_nbjets; //! 
   map<TString, TH1*> h_nljets; //!
   map<TString, TH1*> h_bjet_pt; //!  
   map<TString, TH1*> h_bjet_eta; //!  
   map<TString, TH1*> h_jet_pt; //!  
   map<TString, TH1*> h_jet_eta; //!  
   map<TString, TH1*> h_mcw; //!    
   map<TString, TH1*> h_mll40; //!    
   map<TString, TH1*> h_mll50; //!    
   map<TString, TH1*> h_mll60; //!    
  // 2D histograms
   /*
   map<TString, TH2*> h_met_mll; //! 
   map<TString, TH2*> h_metsig_mll; //! 
   map<TString, TH2*> h_met_metsig; //! 
   map<TString, TH2*> h_met_metrel; //! 
   map<TString, TH2*> h_mll_mcw; //! 
   map<TString, TH2*> h_dphi_dphirel; //!
   */ 
   // Real efficiencies 
   map<TString, TH1*> h_pt_loose; //!  
   map<TString, TH1*> h_pt_tight; //! 
   map<TString, TH2*> h_ptEta_loose; //!  
   map<TString, TH2*> h_ptEta_tight; //! 
   map<TString, TH1*> h_mll_loose; //!  
   map<TString, TH1*> h_mll_tight; //! 
   map<TString, TH1*> h_met_loose; //!  
   map<TString, TH1*> h_met_tight; //! 
   // Fake rates 
   map<TString, TH1*> h_pt3_loose; //!  
   map<TString, TH1*> h_pt3_tight; //! 

   // Readers to access the data (delete the ones you do not need).
   TTreeReaderValue<Float_t> mconly_weight = {fReader, "mconly_weight"};
   TTreeReaderArray<float> mconly_weights = {fReader, "mconly_weights"};
   TTreeReaderValue<Float_t> kF_weight = {fReader, "kF_weight"};
   TTreeReaderValue<Float_t> ttbarNNLOweight = {fReader, "ttbarNNLOweight"};
   TTreeReaderValue<Float_t> xsec = {fReader, "xsec"};
   TTreeReaderValue<Float_t> geneff = {fReader, "geneff"};
   TTreeReaderValue<Float_t> pu_weight = {fReader, "pu_weight"};
   TTreeReaderValue<Float_t> pu_weight_PRW_DATASF__1up = {fReader, "pu_weight_PRW_DATASF__1up"};
   TTreeReaderValue<Float_t> pu_weight_PRW_DATASF__1down = {fReader, "pu_weight_PRW_DATASF__1down"};
   TTreeReaderValue<Float_t> NLO_EW_corr_ASSEW = {fReader, "NLO_EW_corr_ASSEW"};
   TTreeReaderValue<Float_t> NLO_EW_corr_MULTIASSEW = {fReader, "NLO_EW_corr_MULTIASSEW"};
   TTreeReaderValue<Float_t> NLO_EW_corr_EXPASSEW = {fReader, "NLO_EW_corr_EXPASSEW"};
   TTreeReaderValue<Float_t> trig_1e_SF = {fReader, "trig_1e_SF"};
   TTreeReaderValue<Float_t> trig_1u_SF = {fReader, "trig_1u_SF"};
   TTreeReaderValue<Float_t> trig_ee_SF = {fReader, "trig_ee_SF"};
   TTreeReaderValue<Float_t> trig_uu_SF = {fReader, "trig_uu_SF"};
   TTreeReaderValue<Int_t> pass_e_trig = {fReader, "pass_e_trig"};
   TTreeReaderValue<Int_t> pass_ee_trig = {fReader, "pass_ee_trig"};
   TTreeReaderValue<Int_t> pass_u_trig = {fReader, "pass_u_trig"};
   TTreeReaderValue<Int_t> pass_uu_trig = {fReader, "pass_uu_trig"};
   TTreeReaderValue<Int_t> year = {fReader, "year"};
   TTreeReaderValue<TString> systName = {fReader, "systName"};
   TTreeReaderValue<Int_t> run = {fReader, "run"};
  //TTreeReaderValue<Int_t> randomRunNumber = {fReader_nom, "randomRunNumber"};
   TTreeReaderValue<ULong64_t> event = {fReader, "event"};
  //TTreeReaderValue<Int_t> last = {fReader, "last"};
  //TTreeReaderValue<Int_t> n_jet = {fReader, "n_jet"};
  // TTreeReaderValue<Int_t> n_bjet = {fReader, "n_bjet"};
  //TTreeReaderValue<Int_t> n_el = {fReader, "n_el"};
  //TTreeReaderValue<Int_t> n_mu = {fReader, "n_mu"};
  //TTreeReaderValue<Int_t> n_mu_baseline_bad = {fReader_nom, "n_mu_baseline_bad"};

  // Jet SF systematics 
  TTreeReaderValue<Float_t> btag_signal_jets_SF_syst_FT_EFF_Eigen_B_0__1down = {fReader_sys, "btag_signal_jets_SF_syst_FT_EFF_Eigen_B_0__1down"};
  TTreeReaderValue<Float_t> btag_signal_jets_SF_syst_FT_EFF_Eigen_B_0__1up = {fReader_sys, "btag_signal_jets_SF_syst_FT_EFF_Eigen_B_0__1up"};
  TTreeReaderValue<Float_t> btag_signal_jets_SF_syst_FT_EFF_Eigen_B_1__1down = {fReader_sys, "btag_signal_jets_SF_syst_FT_EFF_Eigen_B_1__1down"};
  TTreeReaderValue<Float_t> btag_signal_jets_SF_syst_FT_EFF_Eigen_B_1__1up = {fReader_sys, "btag_signal_jets_SF_syst_FT_EFF_Eigen_B_1__1up"};
  TTreeReaderValue<Float_t> btag_signal_jets_SF_syst_FT_EFF_Eigen_B_2__1down = {fReader_sys, "btag_signal_jets_SF_syst_FT_EFF_Eigen_B_2__1down"};
  TTreeReaderValue<Float_t> btag_signal_jets_SF_syst_FT_EFF_Eigen_B_2__1up = {fReader_sys, "btag_signal_jets_SF_syst_FT_EFF_Eigen_B_2__1up"};
  TTreeReaderValue<Float_t> btag_signal_jets_SF_syst_FT_EFF_Eigen_B_3__1down = {fReader_sys, "btag_signal_jets_SF_syst_FT_EFF_Eigen_B_3__1down"};
  TTreeReaderValue<Float_t> btag_signal_jets_SF_syst_FT_EFF_Eigen_B_3__1up = {fReader_sys, "btag_signal_jets_SF_syst_FT_EFF_Eigen_B_3__1up"};
  TTreeReaderValue<Float_t> btag_signal_jets_SF_syst_FT_EFF_Eigen_B_4__1down = {fReader_sys, "btag_signal_jets_SF_syst_FT_EFF_Eigen_B_4__1down"};
  TTreeReaderValue<Float_t> btag_signal_jets_SF_syst_FT_EFF_Eigen_B_4__1up = {fReader_sys, "btag_signal_jets_SF_syst_FT_EFF_Eigen_B_4__1up"};
  TTreeReaderValue<Float_t> btag_signal_jets_SF_syst_FT_EFF_Eigen_B_5__1down = {fReader_sys, "btag_signal_jets_SF_syst_FT_EFF_Eigen_B_5__1down"};
  TTreeReaderValue<Float_t> btag_signal_jets_SF_syst_FT_EFF_Eigen_B_5__1up = {fReader_sys, "btag_signal_jets_SF_syst_FT_EFF_Eigen_B_5__1up"};
  TTreeReaderValue<Float_t> btag_signal_jets_SF_syst_FT_EFF_Eigen_B_6__1down = {fReader_sys, "btag_signal_jets_SF_syst_FT_EFF_Eigen_B_6__1down"};
  TTreeReaderValue<Float_t> btag_signal_jets_SF_syst_FT_EFF_Eigen_B_6__1up = {fReader_sys, "btag_signal_jets_SF_syst_FT_EFF_Eigen_B_6__1up"};
  TTreeReaderValue<Float_t> btag_signal_jets_SF_syst_FT_EFF_Eigen_B_7__1down = {fReader_sys, "btag_signal_jets_SF_syst_FT_EFF_Eigen_B_7__1down"};
  TTreeReaderValue<Float_t> btag_signal_jets_SF_syst_FT_EFF_Eigen_B_7__1up = {fReader_sys, "btag_signal_jets_SF_syst_FT_EFF_Eigen_B_7__1up"};
  TTreeReaderValue<Float_t> btag_signal_jets_SF_syst_FT_EFF_Eigen_B_8__1down = {fReader_sys, "btag_signal_jets_SF_syst_FT_EFF_Eigen_B_8__1down"};
  TTreeReaderValue<Float_t> btag_signal_jets_SF_syst_FT_EFF_Eigen_B_8__1up = {fReader_sys, "btag_signal_jets_SF_syst_FT_EFF_Eigen_B_8__1up"};
  TTreeReaderValue<Float_t> btag_signal_jets_SF_syst_FT_EFF_Eigen_C_0__1down = {fReader_sys, "btag_signal_jets_SF_syst_FT_EFF_Eigen_C_0__1down"};
  TTreeReaderValue<Float_t> btag_signal_jets_SF_syst_FT_EFF_Eigen_C_0__1up = {fReader_sys, "btag_signal_jets_SF_syst_FT_EFF_Eigen_C_0__1up"};
  TTreeReaderValue<Float_t> btag_signal_jets_SF_syst_FT_EFF_Eigen_C_1__1down = {fReader_sys, "btag_signal_jets_SF_syst_FT_EFF_Eigen_C_1__1down"};
  TTreeReaderValue<Float_t> btag_signal_jets_SF_syst_FT_EFF_Eigen_C_1__1up = {fReader_sys, "btag_signal_jets_SF_syst_FT_EFF_Eigen_C_1__1up"};
  TTreeReaderValue<Float_t> btag_signal_jets_SF_syst_FT_EFF_Eigen_C_2__1down = {fReader_sys, "btag_signal_jets_SF_syst_FT_EFF_Eigen_C_2__1down"};
  TTreeReaderValue<Float_t> btag_signal_jets_SF_syst_FT_EFF_Eigen_C_2__1up = {fReader_sys, "btag_signal_jets_SF_syst_FT_EFF_Eigen_C_2__1up"};
  TTreeReaderValue<Float_t> btag_signal_jets_SF_syst_FT_EFF_Eigen_C_3__1down = {fReader_sys, "btag_signal_jets_SF_syst_FT_EFF_Eigen_C_3__1down"};
  TTreeReaderValue<Float_t> btag_signal_jets_SF_syst_FT_EFF_Eigen_C_3__1up = {fReader_sys, "btag_signal_jets_SF_syst_FT_EFF_Eigen_C_3__1up"};
  TTreeReaderValue<Float_t> btag_signal_jets_SF_syst_FT_EFF_Eigen_Light_0__1down = {fReader_sys, "btag_signal_jets_SF_syst_FT_EFF_Eigen_Light_0__1down"};
  TTreeReaderValue<Float_t> btag_signal_jets_SF_syst_FT_EFF_Eigen_Light_0__1up = {fReader_sys, "btag_signal_jets_SF_syst_FT_EFF_Eigen_Light_0__1up"};
  TTreeReaderValue<Float_t> btag_signal_jets_SF_syst_FT_EFF_Eigen_Light_1__1down = {fReader_sys, "btag_signal_jets_SF_syst_FT_EFF_Eigen_Light_1__1down"};
  TTreeReaderValue<Float_t> btag_signal_jets_SF_syst_FT_EFF_Eigen_Light_1__1up = {fReader_sys, "btag_signal_jets_SF_syst_FT_EFF_Eigen_Light_1__1up"};
  TTreeReaderValue<Float_t> btag_signal_jets_SF_syst_FT_EFF_Eigen_Light_2__1down = {fReader_sys, "btag_signal_jets_SF_syst_FT_EFF_Eigen_Light_2__1down"};
  TTreeReaderValue<Float_t> btag_signal_jets_SF_syst_FT_EFF_Eigen_Light_2__1up = {fReader_sys, "btag_signal_jets_SF_syst_FT_EFF_Eigen_Light_2__1up"};
  TTreeReaderValue<Float_t> btag_signal_jets_SF_syst_FT_EFF_Eigen_Light_3__1down = {fReader_sys, "btag_signal_jets_SF_syst_FT_EFF_Eigen_Light_3__1down"};
  TTreeReaderValue<Float_t> btag_signal_jets_SF_syst_FT_EFF_Eigen_Light_3__1up = {fReader_sys, "btag_signal_jets_SF_syst_FT_EFF_Eigen_Light_3__1up"};
  TTreeReaderValue<Float_t> btag_signal_jets_SF_syst_FT_EFF_extrapolation__1down = {fReader_sys, "btag_signal_jets_SF_syst_FT_EFF_extrapolation__1down"};
  TTreeReaderValue<Float_t> btag_signal_jets_SF_syst_FT_EFF_extrapolation__1up = {fReader_sys, "btag_signal_jets_SF_syst_FT_EFF_extrapolation__1up"};
  TTreeReaderValue<Float_t> btag_signal_jets_SF_syst_FT_EFF_extrapolation_from_charm__1down = {fReader_sys, "btag_signal_jets_SF_syst_FT_EFF_extrapolation_from_charm__1down"};
  TTreeReaderValue<Float_t> btag_signal_jets_SF_syst_FT_EFF_extrapolation_from_charm__1up = {fReader_sys, "btag_signal_jets_SF_syst_FT_EFF_extrapolation_from_charm__1up"};
  /*
  TTreeReaderValue<Float_t> btag_signal_jets_SF_syst_FT_EFF_B_systematics__1down = {fReader_sys, "btag_signal_jets_SF_syst_FT_EFF_B_systematics__1down"};
  TTreeReaderValue<Float_t> btag_signal_jets_SF_syst_FT_EFF_B_systematics__1up = {fReader_sys, "btag_signal_jets_SF_syst_FT_EFF_B_systematics__1up"};
  TTreeReaderValue<Float_t> btag_signal_jets_SF_syst_FT_EFF_C_systematics__1down = {fReader_sys, "btag_signal_jets_SF_syst_FT_EFF_C_systematics__1down"};
  TTreeReaderValue<Float_t> btag_signal_jets_SF_syst_FT_EFF_C_systematics__1up = {fReader_sys, "btag_signal_jets_SF_syst_FT_EFF_C_systematics__1up"};
  TTreeReaderValue<Float_t> btag_signal_jets_SF_syst_FT_EFF_Light_systematics__1down = {fReader_sys, "btag_signal_jets_SF_syst_FT_EFF_Light_systematics__1down"};
  TTreeReaderValue<Float_t> btag_signal_jets_SF_syst_FT_EFF_Light_systematics__1up = {fReader_sys, "btag_signal_jets_SF_syst_FT_EFF_Light_systematics__1up"};
  */ 
  TTreeReaderValue<Float_t> jvt_signal_jets_SF_syst_JET_JvtEfficiency__1down = {fReader_sys, "jvt_signal_jets_SF_syst_JET_JvtEfficiency__1down"};
  TTreeReaderValue<Float_t> jvt_signal_jets_SF_syst_JET_JvtEfficiency__1up = {fReader_sys, "jvt_signal_jets_SF_syst_JET_JvtEfficiency__1up"};
  TTreeReaderValue<Float_t> fjvt_signal_jets_SF_syst_JET_fJvtEfficiency__1down = {fReader_sys, "fjvt_signal_jets_SF_syst_JET_fJvtEfficiency__1down"};
  TTreeReaderValue<Float_t> fjvt_signal_jets_SF_syst_JET_fJvtEfficiency__1up = {fReader_sys, "fjvt_signal_jets_SF_syst_JET_fJvtEfficiency__1up"};


  //TTreeReaderValue<Float_t> btag_xAOD_jets_SF = {fReader_nom, "btag_xAOD_jets_SF"};
  //TTreeReaderValue<Float_t> btag_baseline_jets_SF = {fReader_nom, "btag_baseline_jets_SF"};
  TTreeReaderValue<Float_t> btag_signal_jets_SF = {fReader, "btag_signal_jets_SF"};
  //TTreeReaderValue<Float_t> jvt_xAOD_jets_SF = {fReader_nom, "jvt_xAOD_jets_SF"};
  //TTreeReaderValue<Float_t> jvt_baseline_jets_SF = {fReader_nom, "jvt_baseline_jets_SF"};
  TTreeReaderValue<Float_t> jvt_signal_jets_SF = {fReader, "jvt_signal_jets_SF"};
  //TTreeReaderValue<Float_t> fjvt_xAOD_jets_SF = {fReader_nom, "fjvt_xAOD_jets_SF"};
  //TTreeReaderValue<Float_t> fjvt_baseline_jets_SF = {fReader_nom, "fjvt_baseline_jets_SF"};
  TTreeReaderValue<Float_t> fjvt_signal_jets_SF = {fReader, "fjvt_signal_jets_SF"};
  //TTreeReaderValue<Float_t> averageIntPerXing = {fReader_nom, "averageIntPerXing"};
  //TTreeReaderValue<Float_t> corAverageIntPerXing = {fReader_nom, "corAverageIntPerXing"};
  /*
  TTreeReaderValue<Int_t> n_vx = {fReader, "n_vx"};
  TTreeReaderValue<Float_t> pu_hash = {fReader_nom, "pu_hash"};
  TTreeReaderValue<Int_t> trigger_HLT_2e12_lhloose_L12EM10VH = {fReader, "trigger_HLT_2e12_lhloose_L12EM10VH"};
  TTreeReaderValue<Int_t> trigger_HLT_2e17_lhvloose_nod0 = {fReader, "trigger_HLT_2e17_lhvloose_nod0"};
  TTreeReaderValue<Int_t> trigger_HLT_2e17_lhvloose_nod0_L12EM15VHI = {fReader, "trigger_HLT_2e17_lhvloose_nod0_L12EM15VHI"};
  TTreeReaderValue<Int_t> trigger_HLT_2e24_lhvloose_nod0 = {fReader, "trigger_HLT_2e24_lhvloose_nod0"};
  TTreeReaderValue<Int_t> trigger_HLT_e120_lhvloose_nod0 = {fReader, "trigger_HLT_e120_lhvloose_nod0"};
  TTreeReaderValue<Int_t> trigger_HLT_e140_lhvloose_nod0 = {fReader, "trigger_HLT_e140_lhvloose_nod0"};
  TTreeReaderValue<Int_t> trigger_HLT_e200_etcut = {fReader, "trigger_HLT_e200_etcut"};
  TTreeReaderValue<Int_t> trigger_HLT_e26_lhvloose_nod0_L1EM20VH = {fReader, "trigger_HLT_e26_lhvloose_nod0_L1EM20VH"};
  TTreeReaderValue<Int_t> trigger_HLT_e300_etcut = {fReader, "trigger_HLT_e300_etcut"};
  TTreeReaderValue<Int_t> trigger_HLT_e60_lhvloose_nod0 = {fReader, "trigger_HLT_e60_lhvloose_nod0"};
  TTreeReaderValue<Int_t> trigger_HLT_mu26_imedium = {fReader, "trigger_HLT_mu26_imedium"};
  TTreeReaderValue<Int_t> trigger_HLT_mu26_ivarmedium = {fReader, "trigger_HLT_mu26_ivarmedium"};
  TTreeReaderValue<Int_t> trigger_HLT_mu50 = {fReader, "trigger_HLT_mu50"};
  TTreeReaderValue<Int_t> lbn = {fReader_nom, "lbn"};
  */ 
  //TTreeReaderValue<Int_t> bcid = {fReader_nom, "bcid"};
  TTreeReaderValue<Float_t> bornMass = {fReader, "bornMass"};
  TTreeReaderValue<Float_t> ttbarMass = {fReader, "ttbarMass"};
  TTreeReaderValue<Float_t> ttbarGenFiltMET = {fReader, "ttbarGenFiltMET"};
  TTreeReaderValue<Float_t> ttbarTruthHT = {fReader, "ttbarTruthHT"};
  TTreeReaderValue<Float_t> truthMET_darkMatter_et = {fReader, "truthMET_darkMatter_et"};
  TTreeReaderValue<Float_t> truthMET_darkMatter_phi = {fReader, "truthMET_darkMatter_phi"};
  /*
  TTreeReaderValue<Float_t> pdf_x1 = {fReader_nom, "pdf_x1"};
  TTreeReaderValue<Float_t> pdf_x2 = {fReader_nom, "pdf_x2"};
  TTreeReaderValue<Float_t> pdf_pdf1 = {fReader_nom, "pdf_pdf1"};
  TTreeReaderValue<Float_t> pdf_pdf2 = {fReader_nom, "pdf_pdf2"};
  TTreeReaderValue<Float_t> pdf_scale = {fReader_nom, "pdf_scale"};
  */ 
  TTreeReaderValue<Int_t> jetCleaning_eventClean = {fReader, "jetCleaning_eventClean"};
  //TTreeReaderValue<Int_t> pdf_id1 = {fReader_nom, "pdf_id1"};
  //TTreeReaderValue<Int_t> pdf_id2 = {fReader_nom, "pdf_id2"};
  TTreeReaderArray<float> truth_mu_pt = {fReader_nom, "truth_mu_pt"};
  TTreeReaderArray<float> truth_mu_eta = {fReader_nom, "truth_mu_eta"};
  TTreeReaderArray<float> truth_mu_phi = {fReader_nom, "truth_mu_phi"};
  TTreeReaderArray<int> truth_mu_status = {fReader_nom, "truth_mu_status"};
  TTreeReaderArray<float> truth_el_pt = {fReader_nom, "truth_el_pt"};
  TTreeReaderArray<float> truth_el_eta = {fReader_nom, "truth_el_eta"};
  TTreeReaderArray<float> truth_el_phi = {fReader_nom, "truth_el_phi"};
  TTreeReaderArray<int> truth_el_status = {fReader_nom, "truth_el_status"};
  TTreeReaderValue<Float_t> evsf_signal_nominal_EL = {fReader, "evsf_signal_nominal_EL"};
  TTreeReaderValue<Float_t> evsf_signal_nominal_MU = {fReader, "evsf_signal_nominal_MU"};

  // Lepton SF systematics 
  /*
  TTreeReaderValue<Float_t> SF_cid_syst_EL_CHARGEID_STAT__1down = {fReader_sys, "SF_cid_syst_EL_CHARGEID_STAT__1down"};
  TTreeReaderValue<Float_t> SF_cid_syst_EL_CHARGEID_STAT__1up = {fReader_sys, "SF_cid_syst_EL_CHARGEID_STAT__1up"};
  TTreeReaderValue<Float_t> SF_cid_syst_EL_CHARGEID_SYStotal__1down = {fReader_sys, "SF_cid_syst_EL_CHARGEID_SYStotal__1down"};
  TTreeReaderValue<Float_t> SF_cid_syst_EL_CHARGEID_SYStotal__1up = {fReader_sys, "SF_cid_syst_EL_CHARGEID_SYStotal__1up"};
  TTreeReaderValue<Float_t> SF_cid_syst_EL_EFF_ChargeIDSel_TOTAL_1NPCOR_PLUS_UNCOR__1down = {fReader_sys, "SF_cid_syst_EL_EFF_ChargeIDSel_TOTAL_1NPCOR_PLUS_UNCOR__1down"};
  TTreeReaderValue<Float_t> SF_cid_syst_EL_EFF_ChargeIDSel_TOTAL_1NPCOR_PLUS_UNCOR__1up = {fReader_sys, "SF_cid_syst_EL_EFF_ChargeIDSel_TOTAL_1NPCOR_PLUS_UNCOR__1up"};
  //TTreeReaderValue<Float_t> evsf_signal0_syst_EL_EFF_ChargeIDSel_TOTAL_1NPCOR_PLUS_UNCOR__1down = {fReader_sys, "evsf_signal0_syst_EL_EFF_ChargeIDSel_TOTAL_1NPCOR_PLUS_UNCOR__1down"};
  //TTreeReaderValue<Float_t> evsf_signal0_syst_EL_EFF_ChargeIDSel_TOTAL_1NPCOR_PLUS_UNCOR__1up = {fReader_sys, "evsf_signal0_syst_EL_EFF_ChargeIDSel_TOTAL_1NPCOR_PLUS_UNCOR__1up"};
  TTreeReaderValue<Float_t> evsf_signal0_syst_EL_EFF_ID_TOTAL_1NPCOR_PLUS_UNCOR__1down = {fReader_sys, "evsf_signal0_syst_EL_EFF_ID_TOTAL_1NPCOR_PLUS_UNCOR__1down"};
  TTreeReaderValue<Float_t> evsf_signal0_syst_EL_EFF_ID_TOTAL_1NPCOR_PLUS_UNCOR__1up = {fReader_sys, "evsf_signal0_syst_EL_EFF_ID_TOTAL_1NPCOR_PLUS_UNCOR__1up"};
  TTreeReaderValue<Float_t> evsf_signal0_syst_EL_EFF_Iso_TOTAL_1NPCOR_PLUS_UNCOR__1down = {fReader_sys, "evsf_signal0_syst_EL_EFF_Iso_TOTAL_1NPCOR_PLUS_UNCOR__1down"};
  TTreeReaderValue<Float_t> evsf_signal0_syst_EL_EFF_Iso_TOTAL_1NPCOR_PLUS_UNCOR__1up = {fReader_sys, "evsf_signal0_syst_EL_EFF_Iso_TOTAL_1NPCOR_PLUS_UNCOR__1up"};
  TTreeReaderValue<Float_t> evsf_signal0_syst_EL_EFF_Reco_TOTAL_1NPCOR_PLUS_UNCOR__1down = {fReader_sys, "evsf_signal0_syst_EL_EFF_Reco_TOTAL_1NPCOR_PLUS_UNCOR__1down"};
  TTreeReaderValue<Float_t> evsf_signal0_syst_EL_EFF_Reco_TOTAL_1NPCOR_PLUS_UNCOR__1up = {fReader_sys, "evsf_signal0_syst_EL_EFF_Reco_TOTAL_1NPCOR_PLUS_UNCOR__1up"};
  //TTreeReaderValue<Float_t> evsf_signal0_syst_EL_EFF_TriggerEff_TOTAL_1NPCOR_PLUS_UNCOR__1down = {fReader_sys, "evsf_signal0_syst_EL_EFF_TriggerEff_TOTAL_1NPCOR_PLUS_UNCOR__1down"};
  //TTreeReaderValue<Float_t> evsf_signal0_syst_EL_EFF_TriggerEff_TOTAL_1NPCOR_PLUS_UNCOR__1up = {fReader_sys, "evsf_signal0_syst_EL_EFF_TriggerEff_TOTAL_1NPCOR_PLUS_UNCOR__1up"};
  //TTreeReaderValue<Float_t> evsf_signal0_syst_EL_EFF_Trigger_TOTAL_1NPCOR_PLUS_UNCOR__1down = {fReader_sys, "evsf_signal0_syst_EL_EFF_Trigger_TOTAL_1NPCOR_PLUS_UNCOR__1down"};
  //TTreeReaderValue<Float_t> evsf_signal0_syst_EL_EFF_Trigger_TOTAL_1NPCOR_PLUS_UNCOR__1up = {fReader_sys, "evsf_signal0_syst_EL_EFF_Trigger_TOTAL_1NPCOR_PLUS_UNCOR__1up"};
  */ 
  TTreeReaderValue<Float_t> SF_cid_syst_EL_CHARGEID_STAT__1down = {fReader_sys, "SF_cid_syst_EL_CHARGEID_STAT__1down"};
  TTreeReaderValue<Float_t> SF_cid_syst_EL_CHARGEID_STAT__1up = {fReader_sys, "SF_cid_syst_EL_CHARGEID_STAT__1up"};
  TTreeReaderValue<Float_t> SF_cid_syst_EL_CHARGEID_SYStotal__1down = {fReader_sys, "SF_cid_syst_EL_CHARGEID_SYStotal__1down"};
  TTreeReaderValue<Float_t> SF_cid_syst_EL_CHARGEID_SYStotal__1up = {fReader_sys, "SF_cid_syst_EL_CHARGEID_SYStotal__1up"};
  TTreeReaderValue<Float_t> SF_cid_syst_EL_EFF_ChargeIDSel_CorrUncertaintyNP0__1down = {fReader_sys, "SF_cid_syst_EL_EFF_ChargeIDSel_CorrUncertaintyNP0__1down"};
  TTreeReaderValue<Float_t> SF_cid_syst_EL_EFF_ChargeIDSel_CorrUncertaintyNP0__1up = {fReader_sys, "SF_cid_syst_EL_EFF_ChargeIDSel_CorrUncertaintyNP0__1up"};
  TTreeReaderValue<Float_t> SF_cid_syst_EL_EFF_ChargeIDSel_CorrUncertaintyNP10__1down = {fReader_sys, "SF_cid_syst_EL_EFF_ChargeIDSel_CorrUncertaintyNP10__1down"};
  TTreeReaderValue<Float_t> SF_cid_syst_EL_EFF_ChargeIDSel_CorrUncertaintyNP10__1up = {fReader_sys, "SF_cid_syst_EL_EFF_ChargeIDSel_CorrUncertaintyNP10__1up"};
  TTreeReaderValue<Float_t> SF_cid_syst_EL_EFF_ChargeIDSel_CorrUncertaintyNP1__1down = {fReader_sys, "SF_cid_syst_EL_EFF_ChargeIDSel_CorrUncertaintyNP1__1down"};
  TTreeReaderValue<Float_t> SF_cid_syst_EL_EFF_ChargeIDSel_CorrUncertaintyNP1__1up = {fReader_sys, "SF_cid_syst_EL_EFF_ChargeIDSel_CorrUncertaintyNP1__1up"};
  TTreeReaderValue<Float_t> SF_cid_syst_EL_EFF_ChargeIDSel_CorrUncertaintyNP2__1down = {fReader_sys, "SF_cid_syst_EL_EFF_ChargeIDSel_CorrUncertaintyNP2__1down"};
  TTreeReaderValue<Float_t> SF_cid_syst_EL_EFF_ChargeIDSel_CorrUncertaintyNP2__1up = {fReader_sys, "SF_cid_syst_EL_EFF_ChargeIDSel_CorrUncertaintyNP2__1up"};
  TTreeReaderValue<Float_t> SF_cid_syst_EL_EFF_ChargeIDSel_CorrUncertaintyNP3__1down = {fReader_sys, "SF_cid_syst_EL_EFF_ChargeIDSel_CorrUncertaintyNP3__1down"};
  TTreeReaderValue<Float_t> SF_cid_syst_EL_EFF_ChargeIDSel_CorrUncertaintyNP3__1up = {fReader_sys, "SF_cid_syst_EL_EFF_ChargeIDSel_CorrUncertaintyNP3__1up"};
  TTreeReaderValue<Float_t> SF_cid_syst_EL_EFF_ChargeIDSel_CorrUncertaintyNP4__1down = {fReader_sys, "SF_cid_syst_EL_EFF_ChargeIDSel_CorrUncertaintyNP4__1down"};
  TTreeReaderValue<Float_t> SF_cid_syst_EL_EFF_ChargeIDSel_CorrUncertaintyNP4__1up = {fReader_sys, "SF_cid_syst_EL_EFF_ChargeIDSel_CorrUncertaintyNP4__1up"};
  TTreeReaderValue<Float_t> SF_cid_syst_EL_EFF_ChargeIDSel_CorrUncertaintyNP5__1down = {fReader_sys, "SF_cid_syst_EL_EFF_ChargeIDSel_CorrUncertaintyNP5__1down"};
  TTreeReaderValue<Float_t> SF_cid_syst_EL_EFF_ChargeIDSel_CorrUncertaintyNP5__1up = {fReader_sys, "SF_cid_syst_EL_EFF_ChargeIDSel_CorrUncertaintyNP5__1up"};
  TTreeReaderValue<Float_t> SF_cid_syst_EL_EFF_ChargeIDSel_CorrUncertaintyNP6__1down = {fReader_sys, "SF_cid_syst_EL_EFF_ChargeIDSel_CorrUncertaintyNP6__1down"};
  TTreeReaderValue<Float_t> SF_cid_syst_EL_EFF_ChargeIDSel_CorrUncertaintyNP6__1up = {fReader_sys, "SF_cid_syst_EL_EFF_ChargeIDSel_CorrUncertaintyNP6__1up"};
  TTreeReaderValue<Float_t> SF_cid_syst_EL_EFF_ChargeIDSel_CorrUncertaintyNP7__1down = {fReader_sys, "SF_cid_syst_EL_EFF_ChargeIDSel_CorrUncertaintyNP7__1down"};
  TTreeReaderValue<Float_t> SF_cid_syst_EL_EFF_ChargeIDSel_CorrUncertaintyNP7__1up = {fReader_sys, "SF_cid_syst_EL_EFF_ChargeIDSel_CorrUncertaintyNP7__1up"};
  TTreeReaderValue<Float_t> SF_cid_syst_EL_EFF_ChargeIDSel_CorrUncertaintyNP8__1down = {fReader_sys, "SF_cid_syst_EL_EFF_ChargeIDSel_CorrUncertaintyNP8__1down"};
  TTreeReaderValue<Float_t> SF_cid_syst_EL_EFF_ChargeIDSel_CorrUncertaintyNP8__1up = {fReader_sys, "SF_cid_syst_EL_EFF_ChargeIDSel_CorrUncertaintyNP8__1up"};
  TTreeReaderValue<Float_t> SF_cid_syst_EL_EFF_ChargeIDSel_CorrUncertaintyNP9__1down = {fReader_sys, "SF_cid_syst_EL_EFF_ChargeIDSel_CorrUncertaintyNP9__1down"};
  TTreeReaderValue<Float_t> SF_cid_syst_EL_EFF_ChargeIDSel_CorrUncertaintyNP9__1up = {fReader_sys, "SF_cid_syst_EL_EFF_ChargeIDSel_CorrUncertaintyNP9__1up"};
  TTreeReaderValue<Float_t> SF_cid_syst_EL_EFF_ChargeIDSel_SIMPLIFIED_UncorrUncertaintyNP0__1down = {fReader_sys, "SF_cid_syst_EL_EFF_ChargeIDSel_SIMPLIFIED_UncorrUncertaintyNP0__1down"};
  TTreeReaderValue<Float_t> SF_cid_syst_EL_EFF_ChargeIDSel_SIMPLIFIED_UncorrUncertaintyNP0__1up = {fReader_sys, "SF_cid_syst_EL_EFF_ChargeIDSel_SIMPLIFIED_UncorrUncertaintyNP0__1up"};
  TTreeReaderValue<Float_t> SF_cid_syst_EL_EFF_ChargeIDSel_SIMPLIFIED_UncorrUncertaintyNP10__1down = {fReader_sys, "SF_cid_syst_EL_EFF_ChargeIDSel_SIMPLIFIED_UncorrUncertaintyNP10__1down"};
  TTreeReaderValue<Float_t> SF_cid_syst_EL_EFF_ChargeIDSel_SIMPLIFIED_UncorrUncertaintyNP10__1up = {fReader_sys, "SF_cid_syst_EL_EFF_ChargeIDSel_SIMPLIFIED_UncorrUncertaintyNP10__1up"};
  TTreeReaderValue<Float_t> SF_cid_syst_EL_EFF_ChargeIDSel_SIMPLIFIED_UncorrUncertaintyNP11__1down = {fReader_sys, "SF_cid_syst_EL_EFF_ChargeIDSel_SIMPLIFIED_UncorrUncertaintyNP11__1down"};
  TTreeReaderValue<Float_t> SF_cid_syst_EL_EFF_ChargeIDSel_SIMPLIFIED_UncorrUncertaintyNP11__1up = {fReader_sys, "SF_cid_syst_EL_EFF_ChargeIDSel_SIMPLIFIED_UncorrUncertaintyNP11__1up"};
  TTreeReaderValue<Float_t> SF_cid_syst_EL_EFF_ChargeIDSel_SIMPLIFIED_UncorrUncertaintyNP12__1down = {fReader_sys, "SF_cid_syst_EL_EFF_ChargeIDSel_SIMPLIFIED_UncorrUncertaintyNP12__1down"};
  TTreeReaderValue<Float_t> SF_cid_syst_EL_EFF_ChargeIDSel_SIMPLIFIED_UncorrUncertaintyNP12__1up = {fReader_sys, "SF_cid_syst_EL_EFF_ChargeIDSel_SIMPLIFIED_UncorrUncertaintyNP12__1up"};
  TTreeReaderValue<Float_t> SF_cid_syst_EL_EFF_ChargeIDSel_SIMPLIFIED_UncorrUncertaintyNP13__1down = {fReader_sys, "SF_cid_syst_EL_EFF_ChargeIDSel_SIMPLIFIED_UncorrUncertaintyNP13__1down"};
  TTreeReaderValue<Float_t> SF_cid_syst_EL_EFF_ChargeIDSel_SIMPLIFIED_UncorrUncertaintyNP13__1up = {fReader_sys, "SF_cid_syst_EL_EFF_ChargeIDSel_SIMPLIFIED_UncorrUncertaintyNP13__1up"};
  TTreeReaderValue<Float_t> SF_cid_syst_EL_EFF_ChargeIDSel_SIMPLIFIED_UncorrUncertaintyNP14__1down = {fReader_sys, "SF_cid_syst_EL_EFF_ChargeIDSel_SIMPLIFIED_UncorrUncertaintyNP14__1down"};
  TTreeReaderValue<Float_t> SF_cid_syst_EL_EFF_ChargeIDSel_SIMPLIFIED_UncorrUncertaintyNP14__1up = {fReader_sys, "SF_cid_syst_EL_EFF_ChargeIDSel_SIMPLIFIED_UncorrUncertaintyNP14__1up"};
  TTreeReaderValue<Float_t> SF_cid_syst_EL_EFF_ChargeIDSel_SIMPLIFIED_UncorrUncertaintyNP15__1down = {fReader_sys, "SF_cid_syst_EL_EFF_ChargeIDSel_SIMPLIFIED_UncorrUncertaintyNP15__1down"};
  TTreeReaderValue<Float_t> SF_cid_syst_EL_EFF_ChargeIDSel_SIMPLIFIED_UncorrUncertaintyNP15__1up = {fReader_sys, "SF_cid_syst_EL_EFF_ChargeIDSel_SIMPLIFIED_UncorrUncertaintyNP15__1up"};
  TTreeReaderValue<Float_t> SF_cid_syst_EL_EFF_ChargeIDSel_SIMPLIFIED_UncorrUncertaintyNP16__1down = {fReader_sys, "SF_cid_syst_EL_EFF_ChargeIDSel_SIMPLIFIED_UncorrUncertaintyNP16__1down"};
  TTreeReaderValue<Float_t> SF_cid_syst_EL_EFF_ChargeIDSel_SIMPLIFIED_UncorrUncertaintyNP16__1up = {fReader_sys, "SF_cid_syst_EL_EFF_ChargeIDSel_SIMPLIFIED_UncorrUncertaintyNP16__1up"};
  TTreeReaderValue<Float_t> SF_cid_syst_EL_EFF_ChargeIDSel_SIMPLIFIED_UncorrUncertaintyNP17__1down = {fReader_sys, "SF_cid_syst_EL_EFF_ChargeIDSel_SIMPLIFIED_UncorrUncertaintyNP17__1down"};
  TTreeReaderValue<Float_t> SF_cid_syst_EL_EFF_ChargeIDSel_SIMPLIFIED_UncorrUncertaintyNP17__1up = {fReader_sys, "SF_cid_syst_EL_EFF_ChargeIDSel_SIMPLIFIED_UncorrUncertaintyNP17__1up"};
  TTreeReaderValue<Float_t> SF_cid_syst_EL_EFF_ChargeIDSel_SIMPLIFIED_UncorrUncertaintyNP1__1down = {fReader_sys, "SF_cid_syst_EL_EFF_ChargeIDSel_SIMPLIFIED_UncorrUncertaintyNP1__1down"};
  TTreeReaderValue<Float_t> SF_cid_syst_EL_EFF_ChargeIDSel_SIMPLIFIED_UncorrUncertaintyNP1__1up = {fReader_sys, "SF_cid_syst_EL_EFF_ChargeIDSel_SIMPLIFIED_UncorrUncertaintyNP1__1up"};
  TTreeReaderValue<Float_t> SF_cid_syst_EL_EFF_ChargeIDSel_SIMPLIFIED_UncorrUncertaintyNP2__1down = {fReader_sys, "SF_cid_syst_EL_EFF_ChargeIDSel_SIMPLIFIED_UncorrUncertaintyNP2__1down"};
  TTreeReaderValue<Float_t> SF_cid_syst_EL_EFF_ChargeIDSel_SIMPLIFIED_UncorrUncertaintyNP2__1up = {fReader_sys, "SF_cid_syst_EL_EFF_ChargeIDSel_SIMPLIFIED_UncorrUncertaintyNP2__1up"};
  TTreeReaderValue<Float_t> SF_cid_syst_EL_EFF_ChargeIDSel_SIMPLIFIED_UncorrUncertaintyNP3__1down = {fReader_sys, "SF_cid_syst_EL_EFF_ChargeIDSel_SIMPLIFIED_UncorrUncertaintyNP3__1down"};
  TTreeReaderValue<Float_t> SF_cid_syst_EL_EFF_ChargeIDSel_SIMPLIFIED_UncorrUncertaintyNP3__1up = {fReader_sys, "SF_cid_syst_EL_EFF_ChargeIDSel_SIMPLIFIED_UncorrUncertaintyNP3__1up"};
  TTreeReaderValue<Float_t> SF_cid_syst_EL_EFF_ChargeIDSel_SIMPLIFIED_UncorrUncertaintyNP4__1down = {fReader_sys, "SF_cid_syst_EL_EFF_ChargeIDSel_SIMPLIFIED_UncorrUncertaintyNP4__1down"};
  TTreeReaderValue<Float_t> SF_cid_syst_EL_EFF_ChargeIDSel_SIMPLIFIED_UncorrUncertaintyNP4__1up = {fReader_sys, "SF_cid_syst_EL_EFF_ChargeIDSel_SIMPLIFIED_UncorrUncertaintyNP4__1up"};
  TTreeReaderValue<Float_t> SF_cid_syst_EL_EFF_ChargeIDSel_SIMPLIFIED_UncorrUncertaintyNP5__1down = {fReader_sys, "SF_cid_syst_EL_EFF_ChargeIDSel_SIMPLIFIED_UncorrUncertaintyNP5__1down"};
  TTreeReaderValue<Float_t> SF_cid_syst_EL_EFF_ChargeIDSel_SIMPLIFIED_UncorrUncertaintyNP5__1up = {fReader_sys, "SF_cid_syst_EL_EFF_ChargeIDSel_SIMPLIFIED_UncorrUncertaintyNP5__1up"};
  TTreeReaderValue<Float_t> SF_cid_syst_EL_EFF_ChargeIDSel_SIMPLIFIED_UncorrUncertaintyNP6__1down = {fReader_sys, "SF_cid_syst_EL_EFF_ChargeIDSel_SIMPLIFIED_UncorrUncertaintyNP6__1down"};
  TTreeReaderValue<Float_t> SF_cid_syst_EL_EFF_ChargeIDSel_SIMPLIFIED_UncorrUncertaintyNP6__1up = {fReader_sys, "SF_cid_syst_EL_EFF_ChargeIDSel_SIMPLIFIED_UncorrUncertaintyNP6__1up"};
  TTreeReaderValue<Float_t> SF_cid_syst_EL_EFF_ChargeIDSel_SIMPLIFIED_UncorrUncertaintyNP7__1down = {fReader_sys, "SF_cid_syst_EL_EFF_ChargeIDSel_SIMPLIFIED_UncorrUncertaintyNP7__1down"};
  TTreeReaderValue<Float_t> SF_cid_syst_EL_EFF_ChargeIDSel_SIMPLIFIED_UncorrUncertaintyNP7__1up = {fReader_sys, "SF_cid_syst_EL_EFF_ChargeIDSel_SIMPLIFIED_UncorrUncertaintyNP7__1up"};
  TTreeReaderValue<Float_t> SF_cid_syst_EL_EFF_ChargeIDSel_SIMPLIFIED_UncorrUncertaintyNP8__1down = {fReader_sys, "SF_cid_syst_EL_EFF_ChargeIDSel_SIMPLIFIED_UncorrUncertaintyNP8__1down"};
  TTreeReaderValue<Float_t> SF_cid_syst_EL_EFF_ChargeIDSel_SIMPLIFIED_UncorrUncertaintyNP8__1up = {fReader_sys, "SF_cid_syst_EL_EFF_ChargeIDSel_SIMPLIFIED_UncorrUncertaintyNP8__1up"};
  TTreeReaderValue<Float_t> SF_cid_syst_EL_EFF_ChargeIDSel_SIMPLIFIED_UncorrUncertaintyNP9__1down = {fReader_sys, "SF_cid_syst_EL_EFF_ChargeIDSel_SIMPLIFIED_UncorrUncertaintyNP9__1down"};
  TTreeReaderValue<Float_t> SF_cid_syst_EL_EFF_ChargeIDSel_SIMPLIFIED_UncorrUncertaintyNP9__1up = {fReader_sys, "SF_cid_syst_EL_EFF_ChargeIDSel_SIMPLIFIED_UncorrUncertaintyNP9__1up"};
  TTreeReaderValue<Float_t> evsf_signal0_syst_EL_EFF_ID_CorrUncertaintyNP0__1down = {fReader_sys, "evsf_signal0_syst_EL_EFF_ID_CorrUncertaintyNP0__1down"};
  TTreeReaderValue<Float_t> evsf_signal0_syst_EL_EFF_ID_CorrUncertaintyNP0__1up = {fReader_sys, "evsf_signal0_syst_EL_EFF_ID_CorrUncertaintyNP0__1up"};
  TTreeReaderValue<Float_t> evsf_signal0_syst_EL_EFF_ID_CorrUncertaintyNP10__1down = {fReader_sys, "evsf_signal0_syst_EL_EFF_ID_CorrUncertaintyNP10__1down"};
  TTreeReaderValue<Float_t> evsf_signal0_syst_EL_EFF_ID_CorrUncertaintyNP10__1up = {fReader_sys, "evsf_signal0_syst_EL_EFF_ID_CorrUncertaintyNP10__1up"};
  TTreeReaderValue<Float_t> evsf_signal0_syst_EL_EFF_ID_CorrUncertaintyNP11__1down = {fReader_sys, "evsf_signal0_syst_EL_EFF_ID_CorrUncertaintyNP11__1down"};
  TTreeReaderValue<Float_t> evsf_signal0_syst_EL_EFF_ID_CorrUncertaintyNP11__1up = {fReader_sys, "evsf_signal0_syst_EL_EFF_ID_CorrUncertaintyNP11__1up"};
  TTreeReaderValue<Float_t> evsf_signal0_syst_EL_EFF_ID_CorrUncertaintyNP12__1down = {fReader_sys, "evsf_signal0_syst_EL_EFF_ID_CorrUncertaintyNP12__1down"};
  TTreeReaderValue<Float_t> evsf_signal0_syst_EL_EFF_ID_CorrUncertaintyNP12__1up = {fReader_sys, "evsf_signal0_syst_EL_EFF_ID_CorrUncertaintyNP12__1up"};
  TTreeReaderValue<Float_t> evsf_signal0_syst_EL_EFF_ID_CorrUncertaintyNP13__1down = {fReader_sys, "evsf_signal0_syst_EL_EFF_ID_CorrUncertaintyNP13__1down"};
  TTreeReaderValue<Float_t> evsf_signal0_syst_EL_EFF_ID_CorrUncertaintyNP13__1up = {fReader_sys, "evsf_signal0_syst_EL_EFF_ID_CorrUncertaintyNP13__1up"};
  TTreeReaderValue<Float_t> evsf_signal0_syst_EL_EFF_ID_CorrUncertaintyNP14__1down = {fReader_sys, "evsf_signal0_syst_EL_EFF_ID_CorrUncertaintyNP14__1down"};
  TTreeReaderValue<Float_t> evsf_signal0_syst_EL_EFF_ID_CorrUncertaintyNP14__1up = {fReader_sys, "evsf_signal0_syst_EL_EFF_ID_CorrUncertaintyNP14__1up"};
  TTreeReaderValue<Float_t> evsf_signal0_syst_EL_EFF_ID_CorrUncertaintyNP15__1down = {fReader_sys, "evsf_signal0_syst_EL_EFF_ID_CorrUncertaintyNP15__1down"};
  TTreeReaderValue<Float_t> evsf_signal0_syst_EL_EFF_ID_CorrUncertaintyNP15__1up = {fReader_sys, "evsf_signal0_syst_EL_EFF_ID_CorrUncertaintyNP15__1up"};
  TTreeReaderValue<Float_t> evsf_signal0_syst_EL_EFF_ID_CorrUncertaintyNP1__1down = {fReader_sys, "evsf_signal0_syst_EL_EFF_ID_CorrUncertaintyNP1__1down"};
  TTreeReaderValue<Float_t> evsf_signal0_syst_EL_EFF_ID_CorrUncertaintyNP1__1up = {fReader_sys, "evsf_signal0_syst_EL_EFF_ID_CorrUncertaintyNP1__1up"};
  TTreeReaderValue<Float_t> evsf_signal0_syst_EL_EFF_ID_CorrUncertaintyNP2__1down = {fReader_sys, "evsf_signal0_syst_EL_EFF_ID_CorrUncertaintyNP2__1down"};
  TTreeReaderValue<Float_t> evsf_signal0_syst_EL_EFF_ID_CorrUncertaintyNP2__1up = {fReader_sys, "evsf_signal0_syst_EL_EFF_ID_CorrUncertaintyNP2__1up"};
  TTreeReaderValue<Float_t> evsf_signal0_syst_EL_EFF_ID_CorrUncertaintyNP3__1down = {fReader_sys, "evsf_signal0_syst_EL_EFF_ID_CorrUncertaintyNP3__1down"};
  TTreeReaderValue<Float_t> evsf_signal0_syst_EL_EFF_ID_CorrUncertaintyNP3__1up = {fReader_sys, "evsf_signal0_syst_EL_EFF_ID_CorrUncertaintyNP3__1up"};
  TTreeReaderValue<Float_t> evsf_signal0_syst_EL_EFF_ID_CorrUncertaintyNP4__1down = {fReader_sys, "evsf_signal0_syst_EL_EFF_ID_CorrUncertaintyNP4__1down"};
  TTreeReaderValue<Float_t> evsf_signal0_syst_EL_EFF_ID_CorrUncertaintyNP4__1up = {fReader_sys, "evsf_signal0_syst_EL_EFF_ID_CorrUncertaintyNP4__1up"};
  TTreeReaderValue<Float_t> evsf_signal0_syst_EL_EFF_ID_CorrUncertaintyNP5__1down = {fReader_sys, "evsf_signal0_syst_EL_EFF_ID_CorrUncertaintyNP5__1down"};
  TTreeReaderValue<Float_t> evsf_signal0_syst_EL_EFF_ID_CorrUncertaintyNP5__1up = {fReader_sys, "evsf_signal0_syst_EL_EFF_ID_CorrUncertaintyNP5__1up"};
  TTreeReaderValue<Float_t> evsf_signal0_syst_EL_EFF_ID_CorrUncertaintyNP6__1down = {fReader_sys, "evsf_signal0_syst_EL_EFF_ID_CorrUncertaintyNP6__1down"};
  TTreeReaderValue<Float_t> evsf_signal0_syst_EL_EFF_ID_CorrUncertaintyNP6__1up = {fReader_sys, "evsf_signal0_syst_EL_EFF_ID_CorrUncertaintyNP6__1up"};
  TTreeReaderValue<Float_t> evsf_signal0_syst_EL_EFF_ID_CorrUncertaintyNP7__1down = {fReader_sys, "evsf_signal0_syst_EL_EFF_ID_CorrUncertaintyNP7__1down"};
  TTreeReaderValue<Float_t> evsf_signal0_syst_EL_EFF_ID_CorrUncertaintyNP7__1up = {fReader_sys, "evsf_signal0_syst_EL_EFF_ID_CorrUncertaintyNP7__1up"};
  TTreeReaderValue<Float_t> evsf_signal0_syst_EL_EFF_ID_CorrUncertaintyNP8__1down = {fReader_sys, "evsf_signal0_syst_EL_EFF_ID_CorrUncertaintyNP8__1down"};
  TTreeReaderValue<Float_t> evsf_signal0_syst_EL_EFF_ID_CorrUncertaintyNP8__1up = {fReader_sys, "evsf_signal0_syst_EL_EFF_ID_CorrUncertaintyNP8__1up"};
  TTreeReaderValue<Float_t> evsf_signal0_syst_EL_EFF_ID_CorrUncertaintyNP9__1down = {fReader_sys, "evsf_signal0_syst_EL_EFF_ID_CorrUncertaintyNP9__1down"};
  TTreeReaderValue<Float_t> evsf_signal0_syst_EL_EFF_ID_CorrUncertaintyNP9__1up = {fReader_sys, "evsf_signal0_syst_EL_EFF_ID_CorrUncertaintyNP9__1up"};
  TTreeReaderValue<Float_t> evsf_signal0_syst_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP0__1down = {fReader_sys, "evsf_signal0_syst_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP0__1down"};
  TTreeReaderValue<Float_t> evsf_signal0_syst_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP0__1up = {fReader_sys, "evsf_signal0_syst_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP0__1up"};
  TTreeReaderValue<Float_t> evsf_signal0_syst_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP10__1down = {fReader_sys, "evsf_signal0_syst_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP10__1down"};
  TTreeReaderValue<Float_t> evsf_signal0_syst_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP10__1up = {fReader_sys, "evsf_signal0_syst_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP10__1up"};
  TTreeReaderValue<Float_t> evsf_signal0_syst_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP11__1down = {fReader_sys, "evsf_signal0_syst_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP11__1down"};
  TTreeReaderValue<Float_t> evsf_signal0_syst_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP11__1up = {fReader_sys, "evsf_signal0_syst_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP11__1up"};
  TTreeReaderValue<Float_t> evsf_signal0_syst_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP12__1down = {fReader_sys, "evsf_signal0_syst_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP12__1down"};
  TTreeReaderValue<Float_t> evsf_signal0_syst_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP12__1up = {fReader_sys, "evsf_signal0_syst_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP12__1up"};
  TTreeReaderValue<Float_t> evsf_signal0_syst_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP13__1down = {fReader_sys, "evsf_signal0_syst_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP13__1down"};
  TTreeReaderValue<Float_t> evsf_signal0_syst_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP13__1up = {fReader_sys, "evsf_signal0_syst_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP13__1up"};
  TTreeReaderValue<Float_t> evsf_signal0_syst_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP14__1down = {fReader_sys, "evsf_signal0_syst_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP14__1down"};
  TTreeReaderValue<Float_t> evsf_signal0_syst_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP14__1up = {fReader_sys, "evsf_signal0_syst_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP14__1up"};
  TTreeReaderValue<Float_t> evsf_signal0_syst_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP15__1down = {fReader_sys, "evsf_signal0_syst_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP15__1down"};
  TTreeReaderValue<Float_t> evsf_signal0_syst_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP15__1up = {fReader_sys, "evsf_signal0_syst_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP15__1up"};
  TTreeReaderValue<Float_t> evsf_signal0_syst_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP16__1down = {fReader_sys, "evsf_signal0_syst_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP16__1down"};
  TTreeReaderValue<Float_t> evsf_signal0_syst_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP16__1up = {fReader_sys, "evsf_signal0_syst_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP16__1up"};
  TTreeReaderValue<Float_t> evsf_signal0_syst_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP17__1down = {fReader_sys, "evsf_signal0_syst_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP17__1down"};
  TTreeReaderValue<Float_t> evsf_signal0_syst_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP17__1up = {fReader_sys, "evsf_signal0_syst_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP17__1up"};
  TTreeReaderValue<Float_t> evsf_signal0_syst_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP1__1down = {fReader_sys, "evsf_signal0_syst_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP1__1down"};
  TTreeReaderValue<Float_t> evsf_signal0_syst_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP1__1up = {fReader_sys, "evsf_signal0_syst_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP1__1up"};
  TTreeReaderValue<Float_t> evsf_signal0_syst_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP2__1down = {fReader_sys, "evsf_signal0_syst_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP2__1down"};
  TTreeReaderValue<Float_t> evsf_signal0_syst_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP2__1up = {fReader_sys, "evsf_signal0_syst_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP2__1up"};
  TTreeReaderValue<Float_t> evsf_signal0_syst_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP3__1down = {fReader_sys, "evsf_signal0_syst_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP3__1down"};
  TTreeReaderValue<Float_t> evsf_signal0_syst_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP3__1up = {fReader_sys, "evsf_signal0_syst_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP3__1up"};
  TTreeReaderValue<Float_t> evsf_signal0_syst_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP4__1down = {fReader_sys, "evsf_signal0_syst_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP4__1down"};
  TTreeReaderValue<Float_t> evsf_signal0_syst_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP4__1up = {fReader_sys, "evsf_signal0_syst_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP4__1up"};
  TTreeReaderValue<Float_t> evsf_signal0_syst_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP5__1down = {fReader_sys, "evsf_signal0_syst_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP5__1down"};
  TTreeReaderValue<Float_t> evsf_signal0_syst_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP5__1up = {fReader_sys, "evsf_signal0_syst_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP5__1up"};
  TTreeReaderValue<Float_t> evsf_signal0_syst_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP6__1down = {fReader_sys, "evsf_signal0_syst_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP6__1down"};
  TTreeReaderValue<Float_t> evsf_signal0_syst_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP6__1up = {fReader_sys, "evsf_signal0_syst_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP6__1up"};
  TTreeReaderValue<Float_t> evsf_signal0_syst_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP7__1down = {fReader_sys, "evsf_signal0_syst_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP7__1down"};
  TTreeReaderValue<Float_t> evsf_signal0_syst_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP7__1up = {fReader_sys, "evsf_signal0_syst_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP7__1up"};
  TTreeReaderValue<Float_t> evsf_signal0_syst_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP8__1down = {fReader_sys, "evsf_signal0_syst_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP8__1down"};
  TTreeReaderValue<Float_t> evsf_signal0_syst_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP8__1up = {fReader_sys, "evsf_signal0_syst_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP8__1up"};
  TTreeReaderValue<Float_t> evsf_signal0_syst_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP9__1down = {fReader_sys, "evsf_signal0_syst_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP9__1down"};
  TTreeReaderValue<Float_t> evsf_signal0_syst_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP9__1up = {fReader_sys, "evsf_signal0_syst_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP9__1up"};
  TTreeReaderValue<Float_t> evsf_signal0_syst_EL_EFF_ID_TOTAL_1NPCOR_PLUS_UNCOR__1down = {fReader_sys, "evsf_signal0_syst_EL_EFF_ID_TOTAL_1NPCOR_PLUS_UNCOR__1down"};
  TTreeReaderValue<Float_t> evsf_signal0_syst_EL_EFF_ID_TOTAL_1NPCOR_PLUS_UNCOR__1up = {fReader_sys, "evsf_signal0_syst_EL_EFF_ID_TOTAL_1NPCOR_PLUS_UNCOR__1up"};
  TTreeReaderValue<Float_t> evsf_signal0_syst_EL_EFF_Iso_CorrUncertaintyNP0__1down = {fReader_sys, "evsf_signal0_syst_EL_EFF_Iso_CorrUncertaintyNP0__1down"};
  TTreeReaderValue<Float_t> evsf_signal0_syst_EL_EFF_Iso_CorrUncertaintyNP0__1up = {fReader_sys, "evsf_signal0_syst_EL_EFF_Iso_CorrUncertaintyNP0__1up"};
  TTreeReaderValue<Float_t> evsf_signal0_syst_EL_EFF_Iso_CorrUncertaintyNP10__1down = {fReader_sys, "evsf_signal0_syst_EL_EFF_Iso_CorrUncertaintyNP10__1down"};
  TTreeReaderValue<Float_t> evsf_signal0_syst_EL_EFF_Iso_CorrUncertaintyNP10__1up = {fReader_sys, "evsf_signal0_syst_EL_EFF_Iso_CorrUncertaintyNP10__1up"};
  TTreeReaderValue<Float_t> evsf_signal0_syst_EL_EFF_Iso_CorrUncertaintyNP1__1down = {fReader_sys, "evsf_signal0_syst_EL_EFF_Iso_CorrUncertaintyNP1__1down"};
  TTreeReaderValue<Float_t> evsf_signal0_syst_EL_EFF_Iso_CorrUncertaintyNP1__1up = {fReader_sys, "evsf_signal0_syst_EL_EFF_Iso_CorrUncertaintyNP1__1up"};
  TTreeReaderValue<Float_t> evsf_signal0_syst_EL_EFF_Iso_CorrUncertaintyNP2__1down = {fReader_sys, "evsf_signal0_syst_EL_EFF_Iso_CorrUncertaintyNP2__1down"};
  TTreeReaderValue<Float_t> evsf_signal0_syst_EL_EFF_Iso_CorrUncertaintyNP2__1up = {fReader_sys, "evsf_signal0_syst_EL_EFF_Iso_CorrUncertaintyNP2__1up"};
  TTreeReaderValue<Float_t> evsf_signal0_syst_EL_EFF_Iso_CorrUncertaintyNP3__1down = {fReader_sys, "evsf_signal0_syst_EL_EFF_Iso_CorrUncertaintyNP3__1down"};
  TTreeReaderValue<Float_t> evsf_signal0_syst_EL_EFF_Iso_CorrUncertaintyNP3__1up = {fReader_sys, "evsf_signal0_syst_EL_EFF_Iso_CorrUncertaintyNP3__1up"};
  TTreeReaderValue<Float_t> evsf_signal0_syst_EL_EFF_Iso_CorrUncertaintyNP4__1down = {fReader_sys, "evsf_signal0_syst_EL_EFF_Iso_CorrUncertaintyNP4__1down"};
  TTreeReaderValue<Float_t> evsf_signal0_syst_EL_EFF_Iso_CorrUncertaintyNP4__1up = {fReader_sys, "evsf_signal0_syst_EL_EFF_Iso_CorrUncertaintyNP4__1up"};
  TTreeReaderValue<Float_t> evsf_signal0_syst_EL_EFF_Iso_CorrUncertaintyNP5__1down = {fReader_sys, "evsf_signal0_syst_EL_EFF_Iso_CorrUncertaintyNP5__1down"};
  TTreeReaderValue<Float_t> evsf_signal0_syst_EL_EFF_Iso_CorrUncertaintyNP5__1up = {fReader_sys, "evsf_signal0_syst_EL_EFF_Iso_CorrUncertaintyNP5__1up"};
  TTreeReaderValue<Float_t> evsf_signal0_syst_EL_EFF_Iso_CorrUncertaintyNP6__1down = {fReader_sys, "evsf_signal0_syst_EL_EFF_Iso_CorrUncertaintyNP6__1down"};
  TTreeReaderValue<Float_t> evsf_signal0_syst_EL_EFF_Iso_CorrUncertaintyNP6__1up = {fReader_sys, "evsf_signal0_syst_EL_EFF_Iso_CorrUncertaintyNP6__1up"};
  TTreeReaderValue<Float_t> evsf_signal0_syst_EL_EFF_Iso_CorrUncertaintyNP7__1down = {fReader_sys, "evsf_signal0_syst_EL_EFF_Iso_CorrUncertaintyNP7__1down"};
  TTreeReaderValue<Float_t> evsf_signal0_syst_EL_EFF_Iso_CorrUncertaintyNP7__1up = {fReader_sys, "evsf_signal0_syst_EL_EFF_Iso_CorrUncertaintyNP7__1up"};
  TTreeReaderValue<Float_t> evsf_signal0_syst_EL_EFF_Iso_CorrUncertaintyNP8__1down = {fReader_sys, "evsf_signal0_syst_EL_EFF_Iso_CorrUncertaintyNP8__1down"};
  TTreeReaderValue<Float_t> evsf_signal0_syst_EL_EFF_Iso_CorrUncertaintyNP8__1up = {fReader_sys, "evsf_signal0_syst_EL_EFF_Iso_CorrUncertaintyNP8__1up"};
  TTreeReaderValue<Float_t> evsf_signal0_syst_EL_EFF_Iso_CorrUncertaintyNP9__1down = {fReader_sys, "evsf_signal0_syst_EL_EFF_Iso_CorrUncertaintyNP9__1down"};
  TTreeReaderValue<Float_t> evsf_signal0_syst_EL_EFF_Iso_CorrUncertaintyNP9__1up = {fReader_sys, "evsf_signal0_syst_EL_EFF_Iso_CorrUncertaintyNP9__1up"};
  TTreeReaderValue<Float_t> evsf_signal0_syst_EL_EFF_Iso_SIMPLIFIED_UncorrUncertaintyNP0__1down = {fReader_sys, "evsf_signal0_syst_EL_EFF_Iso_SIMPLIFIED_UncorrUncertaintyNP0__1down"};
  TTreeReaderValue<Float_t> evsf_signal0_syst_EL_EFF_Iso_SIMPLIFIED_UncorrUncertaintyNP0__1up = {fReader_sys, "evsf_signal0_syst_EL_EFF_Iso_SIMPLIFIED_UncorrUncertaintyNP0__1up"};
  TTreeReaderValue<Float_t> evsf_signal0_syst_EL_EFF_Iso_SIMPLIFIED_UncorrUncertaintyNP10__1down = {fReader_sys, "evsf_signal0_syst_EL_EFF_Iso_SIMPLIFIED_UncorrUncertaintyNP10__1down"};
  TTreeReaderValue<Float_t> evsf_signal0_syst_EL_EFF_Iso_SIMPLIFIED_UncorrUncertaintyNP10__1up = {fReader_sys, "evsf_signal0_syst_EL_EFF_Iso_SIMPLIFIED_UncorrUncertaintyNP10__1up"};
  TTreeReaderValue<Float_t> evsf_signal0_syst_EL_EFF_Iso_SIMPLIFIED_UncorrUncertaintyNP11__1down = {fReader_sys, "evsf_signal0_syst_EL_EFF_Iso_SIMPLIFIED_UncorrUncertaintyNP11__1down"};
  TTreeReaderValue<Float_t> evsf_signal0_syst_EL_EFF_Iso_SIMPLIFIED_UncorrUncertaintyNP11__1up = {fReader_sys, "evsf_signal0_syst_EL_EFF_Iso_SIMPLIFIED_UncorrUncertaintyNP11__1up"};
  TTreeReaderValue<Float_t> evsf_signal0_syst_EL_EFF_Iso_SIMPLIFIED_UncorrUncertaintyNP12__1down = {fReader_sys, "evsf_signal0_syst_EL_EFF_Iso_SIMPLIFIED_UncorrUncertaintyNP12__1down"};
  TTreeReaderValue<Float_t> evsf_signal0_syst_EL_EFF_Iso_SIMPLIFIED_UncorrUncertaintyNP12__1up = {fReader_sys, "evsf_signal0_syst_EL_EFF_Iso_SIMPLIFIED_UncorrUncertaintyNP12__1up"};
  TTreeReaderValue<Float_t> evsf_signal0_syst_EL_EFF_Iso_SIMPLIFIED_UncorrUncertaintyNP13__1down = {fReader_sys, "evsf_signal0_syst_EL_EFF_Iso_SIMPLIFIED_UncorrUncertaintyNP13__1down"};
  TTreeReaderValue<Float_t> evsf_signal0_syst_EL_EFF_Iso_SIMPLIFIED_UncorrUncertaintyNP13__1up = {fReader_sys, "evsf_signal0_syst_EL_EFF_Iso_SIMPLIFIED_UncorrUncertaintyNP13__1up"};
  TTreeReaderValue<Float_t> evsf_signal0_syst_EL_EFF_Iso_SIMPLIFIED_UncorrUncertaintyNP14__1down = {fReader_sys, "evsf_signal0_syst_EL_EFF_Iso_SIMPLIFIED_UncorrUncertaintyNP14__1down"};
  TTreeReaderValue<Float_t> evsf_signal0_syst_EL_EFF_Iso_SIMPLIFIED_UncorrUncertaintyNP14__1up = {fReader_sys, "evsf_signal0_syst_EL_EFF_Iso_SIMPLIFIED_UncorrUncertaintyNP14__1up"};
  TTreeReaderValue<Float_t> evsf_signal0_syst_EL_EFF_Iso_SIMPLIFIED_UncorrUncertaintyNP15__1down = {fReader_sys, "evsf_signal0_syst_EL_EFF_Iso_SIMPLIFIED_UncorrUncertaintyNP15__1down"};
  TTreeReaderValue<Float_t> evsf_signal0_syst_EL_EFF_Iso_SIMPLIFIED_UncorrUncertaintyNP15__1up = {fReader_sys, "evsf_signal0_syst_EL_EFF_Iso_SIMPLIFIED_UncorrUncertaintyNP15__1up"};
  TTreeReaderValue<Float_t> evsf_signal0_syst_EL_EFF_Iso_SIMPLIFIED_UncorrUncertaintyNP16__1down = {fReader_sys, "evsf_signal0_syst_EL_EFF_Iso_SIMPLIFIED_UncorrUncertaintyNP16__1down"};
  TTreeReaderValue<Float_t> evsf_signal0_syst_EL_EFF_Iso_SIMPLIFIED_UncorrUncertaintyNP16__1up = {fReader_sys, "evsf_signal0_syst_EL_EFF_Iso_SIMPLIFIED_UncorrUncertaintyNP16__1up"};
  TTreeReaderValue<Float_t> evsf_signal0_syst_EL_EFF_Iso_SIMPLIFIED_UncorrUncertaintyNP17__1down = {fReader_sys, "evsf_signal0_syst_EL_EFF_Iso_SIMPLIFIED_UncorrUncertaintyNP17__1down"};
  TTreeReaderValue<Float_t> evsf_signal0_syst_EL_EFF_Iso_SIMPLIFIED_UncorrUncertaintyNP17__1up = {fReader_sys, "evsf_signal0_syst_EL_EFF_Iso_SIMPLIFIED_UncorrUncertaintyNP17__1up"};
  TTreeReaderValue<Float_t> evsf_signal0_syst_EL_EFF_Iso_SIMPLIFIED_UncorrUncertaintyNP1__1down = {fReader_sys, "evsf_signal0_syst_EL_EFF_Iso_SIMPLIFIED_UncorrUncertaintyNP1__1down"};
  TTreeReaderValue<Float_t> evsf_signal0_syst_EL_EFF_Iso_SIMPLIFIED_UncorrUncertaintyNP1__1up = {fReader_sys, "evsf_signal0_syst_EL_EFF_Iso_SIMPLIFIED_UncorrUncertaintyNP1__1up"};
  TTreeReaderValue<Float_t> evsf_signal0_syst_EL_EFF_Iso_SIMPLIFIED_UncorrUncertaintyNP2__1down = {fReader_sys, "evsf_signal0_syst_EL_EFF_Iso_SIMPLIFIED_UncorrUncertaintyNP2__1down"};
  TTreeReaderValue<Float_t> evsf_signal0_syst_EL_EFF_Iso_SIMPLIFIED_UncorrUncertaintyNP2__1up = {fReader_sys, "evsf_signal0_syst_EL_EFF_Iso_SIMPLIFIED_UncorrUncertaintyNP2__1up"};
  TTreeReaderValue<Float_t> evsf_signal0_syst_EL_EFF_Iso_SIMPLIFIED_UncorrUncertaintyNP3__1down = {fReader_sys, "evsf_signal0_syst_EL_EFF_Iso_SIMPLIFIED_UncorrUncertaintyNP3__1down"};
  TTreeReaderValue<Float_t> evsf_signal0_syst_EL_EFF_Iso_SIMPLIFIED_UncorrUncertaintyNP3__1up = {fReader_sys, "evsf_signal0_syst_EL_EFF_Iso_SIMPLIFIED_UncorrUncertaintyNP3__1up"};
  TTreeReaderValue<Float_t> evsf_signal0_syst_EL_EFF_Iso_SIMPLIFIED_UncorrUncertaintyNP4__1down = {fReader_sys, "evsf_signal0_syst_EL_EFF_Iso_SIMPLIFIED_UncorrUncertaintyNP4__1down"};
  TTreeReaderValue<Float_t> evsf_signal0_syst_EL_EFF_Iso_SIMPLIFIED_UncorrUncertaintyNP4__1up = {fReader_sys, "evsf_signal0_syst_EL_EFF_Iso_SIMPLIFIED_UncorrUncertaintyNP4__1up"};
  TTreeReaderValue<Float_t> evsf_signal0_syst_EL_EFF_Iso_SIMPLIFIED_UncorrUncertaintyNP5__1down = {fReader_sys, "evsf_signal0_syst_EL_EFF_Iso_SIMPLIFIED_UncorrUncertaintyNP5__1down"};
  TTreeReaderValue<Float_t> evsf_signal0_syst_EL_EFF_Iso_SIMPLIFIED_UncorrUncertaintyNP5__1up = {fReader_sys, "evsf_signal0_syst_EL_EFF_Iso_SIMPLIFIED_UncorrUncertaintyNP5__1up"};
  TTreeReaderValue<Float_t> evsf_signal0_syst_EL_EFF_Iso_SIMPLIFIED_UncorrUncertaintyNP6__1down = {fReader_sys, "evsf_signal0_syst_EL_EFF_Iso_SIMPLIFIED_UncorrUncertaintyNP6__1down"};
  TTreeReaderValue<Float_t> evsf_signal0_syst_EL_EFF_Iso_SIMPLIFIED_UncorrUncertaintyNP6__1up = {fReader_sys, "evsf_signal0_syst_EL_EFF_Iso_SIMPLIFIED_UncorrUncertaintyNP6__1up"};
  TTreeReaderValue<Float_t> evsf_signal0_syst_EL_EFF_Iso_SIMPLIFIED_UncorrUncertaintyNP7__1down = {fReader_sys, "evsf_signal0_syst_EL_EFF_Iso_SIMPLIFIED_UncorrUncertaintyNP7__1down"};
  TTreeReaderValue<Float_t> evsf_signal0_syst_EL_EFF_Iso_SIMPLIFIED_UncorrUncertaintyNP7__1up = {fReader_sys, "evsf_signal0_syst_EL_EFF_Iso_SIMPLIFIED_UncorrUncertaintyNP7__1up"};
  TTreeReaderValue<Float_t> evsf_signal0_syst_EL_EFF_Iso_SIMPLIFIED_UncorrUncertaintyNP8__1down = {fReader_sys, "evsf_signal0_syst_EL_EFF_Iso_SIMPLIFIED_UncorrUncertaintyNP8__1down"};
  TTreeReaderValue<Float_t> evsf_signal0_syst_EL_EFF_Iso_SIMPLIFIED_UncorrUncertaintyNP8__1up = {fReader_sys, "evsf_signal0_syst_EL_EFF_Iso_SIMPLIFIED_UncorrUncertaintyNP8__1up"};
  TTreeReaderValue<Float_t> evsf_signal0_syst_EL_EFF_Iso_SIMPLIFIED_UncorrUncertaintyNP9__1down = {fReader_sys, "evsf_signal0_syst_EL_EFF_Iso_SIMPLIFIED_UncorrUncertaintyNP9__1down"};
  TTreeReaderValue<Float_t> evsf_signal0_syst_EL_EFF_Iso_SIMPLIFIED_UncorrUncertaintyNP9__1up = {fReader_sys, "evsf_signal0_syst_EL_EFF_Iso_SIMPLIFIED_UncorrUncertaintyNP9__1up"};
  TTreeReaderValue<Float_t> evsf_signal0_syst_EL_EFF_Iso_TOTAL_1NPCOR_PLUS_UNCOR__1down = {fReader_sys, "evsf_signal0_syst_EL_EFF_Iso_TOTAL_1NPCOR_PLUS_UNCOR__1down"};
  TTreeReaderValue<Float_t> evsf_signal0_syst_EL_EFF_Iso_TOTAL_1NPCOR_PLUS_UNCOR__1up = {fReader_sys, "evsf_signal0_syst_EL_EFF_Iso_TOTAL_1NPCOR_PLUS_UNCOR__1up"};
  TTreeReaderValue<Float_t> evsf_signal0_syst_EL_EFF_Reco_CorrUncertaintyNP0__1down = {fReader_sys, "evsf_signal0_syst_EL_EFF_Reco_CorrUncertaintyNP0__1down"};
  TTreeReaderValue<Float_t> evsf_signal0_syst_EL_EFF_Reco_CorrUncertaintyNP0__1up = {fReader_sys, "evsf_signal0_syst_EL_EFF_Reco_CorrUncertaintyNP0__1up"};
  TTreeReaderValue<Float_t> evsf_signal0_syst_EL_EFF_Reco_CorrUncertaintyNP1__1down = {fReader_sys, "evsf_signal0_syst_EL_EFF_Reco_CorrUncertaintyNP1__1down"};
  TTreeReaderValue<Float_t> evsf_signal0_syst_EL_EFF_Reco_CorrUncertaintyNP1__1up = {fReader_sys, "evsf_signal0_syst_EL_EFF_Reco_CorrUncertaintyNP1__1up"};
  TTreeReaderValue<Float_t> evsf_signal0_syst_EL_EFF_Reco_CorrUncertaintyNP2__1down = {fReader_sys, "evsf_signal0_syst_EL_EFF_Reco_CorrUncertaintyNP2__1down"};
  TTreeReaderValue<Float_t> evsf_signal0_syst_EL_EFF_Reco_CorrUncertaintyNP2__1up = {fReader_sys, "evsf_signal0_syst_EL_EFF_Reco_CorrUncertaintyNP2__1up"};
  TTreeReaderValue<Float_t> evsf_signal0_syst_EL_EFF_Reco_CorrUncertaintyNP3__1down = {fReader_sys, "evsf_signal0_syst_EL_EFF_Reco_CorrUncertaintyNP3__1down"};
  TTreeReaderValue<Float_t> evsf_signal0_syst_EL_EFF_Reco_CorrUncertaintyNP3__1up = {fReader_sys, "evsf_signal0_syst_EL_EFF_Reco_CorrUncertaintyNP3__1up"};
  TTreeReaderValue<Float_t> evsf_signal0_syst_EL_EFF_Reco_CorrUncertaintyNP4__1down = {fReader_sys, "evsf_signal0_syst_EL_EFF_Reco_CorrUncertaintyNP4__1down"};
  TTreeReaderValue<Float_t> evsf_signal0_syst_EL_EFF_Reco_CorrUncertaintyNP4__1up = {fReader_sys, "evsf_signal0_syst_EL_EFF_Reco_CorrUncertaintyNP4__1up"};
  TTreeReaderValue<Float_t> evsf_signal0_syst_EL_EFF_Reco_CorrUncertaintyNP5__1down = {fReader_sys, "evsf_signal0_syst_EL_EFF_Reco_CorrUncertaintyNP5__1down"};
  TTreeReaderValue<Float_t> evsf_signal0_syst_EL_EFF_Reco_CorrUncertaintyNP5__1up = {fReader_sys, "evsf_signal0_syst_EL_EFF_Reco_CorrUncertaintyNP5__1up"};
  TTreeReaderValue<Float_t> evsf_signal0_syst_EL_EFF_Reco_CorrUncertaintyNP6__1down = {fReader_sys, "evsf_signal0_syst_EL_EFF_Reco_CorrUncertaintyNP6__1down"};
  TTreeReaderValue<Float_t> evsf_signal0_syst_EL_EFF_Reco_CorrUncertaintyNP6__1up = {fReader_sys, "evsf_signal0_syst_EL_EFF_Reco_CorrUncertaintyNP6__1up"};
  TTreeReaderValue<Float_t> evsf_signal0_syst_EL_EFF_Reco_CorrUncertaintyNP7__1down = {fReader_sys, "evsf_signal0_syst_EL_EFF_Reco_CorrUncertaintyNP7__1down"};
  TTreeReaderValue<Float_t> evsf_signal0_syst_EL_EFF_Reco_CorrUncertaintyNP7__1up = {fReader_sys, "evsf_signal0_syst_EL_EFF_Reco_CorrUncertaintyNP7__1up"};
  TTreeReaderValue<Float_t> evsf_signal0_syst_EL_EFF_Reco_SIMPLIFIED_UncorrUncertaintyNP0__1down = {fReader_sys, "evsf_signal0_syst_EL_EFF_Reco_SIMPLIFIED_UncorrUncertaintyNP0__1down"};
  TTreeReaderValue<Float_t> evsf_signal0_syst_EL_EFF_Reco_SIMPLIFIED_UncorrUncertaintyNP0__1up = {fReader_sys, "evsf_signal0_syst_EL_EFF_Reco_SIMPLIFIED_UncorrUncertaintyNP0__1up"};
  TTreeReaderValue<Float_t> evsf_signal0_syst_EL_EFF_Reco_SIMPLIFIED_UncorrUncertaintyNP10__1down = {fReader_sys, "evsf_signal0_syst_EL_EFF_Reco_SIMPLIFIED_UncorrUncertaintyNP10__1down"};
  TTreeReaderValue<Float_t> evsf_signal0_syst_EL_EFF_Reco_SIMPLIFIED_UncorrUncertaintyNP10__1up = {fReader_sys, "evsf_signal0_syst_EL_EFF_Reco_SIMPLIFIED_UncorrUncertaintyNP10__1up"};
  TTreeReaderValue<Float_t> evsf_signal0_syst_EL_EFF_Reco_SIMPLIFIED_UncorrUncertaintyNP11__1down = {fReader_sys, "evsf_signal0_syst_EL_EFF_Reco_SIMPLIFIED_UncorrUncertaintyNP11__1down"};
  TTreeReaderValue<Float_t> evsf_signal0_syst_EL_EFF_Reco_SIMPLIFIED_UncorrUncertaintyNP11__1up = {fReader_sys, "evsf_signal0_syst_EL_EFF_Reco_SIMPLIFIED_UncorrUncertaintyNP11__1up"};
  TTreeReaderValue<Float_t> evsf_signal0_syst_EL_EFF_Reco_SIMPLIFIED_UncorrUncertaintyNP12__1down = {fReader_sys, "evsf_signal0_syst_EL_EFF_Reco_SIMPLIFIED_UncorrUncertaintyNP12__1down"};
  TTreeReaderValue<Float_t> evsf_signal0_syst_EL_EFF_Reco_SIMPLIFIED_UncorrUncertaintyNP12__1up = {fReader_sys, "evsf_signal0_syst_EL_EFF_Reco_SIMPLIFIED_UncorrUncertaintyNP12__1up"};
  TTreeReaderValue<Float_t> evsf_signal0_syst_EL_EFF_Reco_SIMPLIFIED_UncorrUncertaintyNP13__1down = {fReader_sys, "evsf_signal0_syst_EL_EFF_Reco_SIMPLIFIED_UncorrUncertaintyNP13__1down"};
  TTreeReaderValue<Float_t> evsf_signal0_syst_EL_EFF_Reco_SIMPLIFIED_UncorrUncertaintyNP13__1up = {fReader_sys, "evsf_signal0_syst_EL_EFF_Reco_SIMPLIFIED_UncorrUncertaintyNP13__1up"};
  TTreeReaderValue<Float_t> evsf_signal0_syst_EL_EFF_Reco_SIMPLIFIED_UncorrUncertaintyNP14__1down = {fReader_sys, "evsf_signal0_syst_EL_EFF_Reco_SIMPLIFIED_UncorrUncertaintyNP14__1down"};
  TTreeReaderValue<Float_t> evsf_signal0_syst_EL_EFF_Reco_SIMPLIFIED_UncorrUncertaintyNP14__1up = {fReader_sys, "evsf_signal0_syst_EL_EFF_Reco_SIMPLIFIED_UncorrUncertaintyNP14__1up"};
  TTreeReaderValue<Float_t> evsf_signal0_syst_EL_EFF_Reco_SIMPLIFIED_UncorrUncertaintyNP15__1down = {fReader_sys, "evsf_signal0_syst_EL_EFF_Reco_SIMPLIFIED_UncorrUncertaintyNP15__1down"};
  TTreeReaderValue<Float_t> evsf_signal0_syst_EL_EFF_Reco_SIMPLIFIED_UncorrUncertaintyNP15__1up = {fReader_sys, "evsf_signal0_syst_EL_EFF_Reco_SIMPLIFIED_UncorrUncertaintyNP15__1up"};
  TTreeReaderValue<Float_t> evsf_signal0_syst_EL_EFF_Reco_SIMPLIFIED_UncorrUncertaintyNP16__1down = {fReader_sys, "evsf_signal0_syst_EL_EFF_Reco_SIMPLIFIED_UncorrUncertaintyNP16__1down"};
  TTreeReaderValue<Float_t> evsf_signal0_syst_EL_EFF_Reco_SIMPLIFIED_UncorrUncertaintyNP16__1up = {fReader_sys, "evsf_signal0_syst_EL_EFF_Reco_SIMPLIFIED_UncorrUncertaintyNP16__1up"};
  TTreeReaderValue<Float_t> evsf_signal0_syst_EL_EFF_Reco_SIMPLIFIED_UncorrUncertaintyNP17__1down = {fReader_sys, "evsf_signal0_syst_EL_EFF_Reco_SIMPLIFIED_UncorrUncertaintyNP17__1down"};
  TTreeReaderValue<Float_t> evsf_signal0_syst_EL_EFF_Reco_SIMPLIFIED_UncorrUncertaintyNP17__1up = {fReader_sys, "evsf_signal0_syst_EL_EFF_Reco_SIMPLIFIED_UncorrUncertaintyNP17__1up"};
  TTreeReaderValue<Float_t> evsf_signal0_syst_EL_EFF_Reco_SIMPLIFIED_UncorrUncertaintyNP1__1down = {fReader_sys, "evsf_signal0_syst_EL_EFF_Reco_SIMPLIFIED_UncorrUncertaintyNP1__1down"};
  TTreeReaderValue<Float_t> evsf_signal0_syst_EL_EFF_Reco_SIMPLIFIED_UncorrUncertaintyNP1__1up = {fReader_sys, "evsf_signal0_syst_EL_EFF_Reco_SIMPLIFIED_UncorrUncertaintyNP1__1up"};
  TTreeReaderValue<Float_t> evsf_signal0_syst_EL_EFF_Reco_SIMPLIFIED_UncorrUncertaintyNP2__1down = {fReader_sys, "evsf_signal0_syst_EL_EFF_Reco_SIMPLIFIED_UncorrUncertaintyNP2__1down"};
  TTreeReaderValue<Float_t> evsf_signal0_syst_EL_EFF_Reco_SIMPLIFIED_UncorrUncertaintyNP2__1up = {fReader_sys, "evsf_signal0_syst_EL_EFF_Reco_SIMPLIFIED_UncorrUncertaintyNP2__1up"};
  TTreeReaderValue<Float_t> evsf_signal0_syst_EL_EFF_Reco_SIMPLIFIED_UncorrUncertaintyNP3__1down = {fReader_sys, "evsf_signal0_syst_EL_EFF_Reco_SIMPLIFIED_UncorrUncertaintyNP3__1down"};
  TTreeReaderValue<Float_t> evsf_signal0_syst_EL_EFF_Reco_SIMPLIFIED_UncorrUncertaintyNP3__1up = {fReader_sys, "evsf_signal0_syst_EL_EFF_Reco_SIMPLIFIED_UncorrUncertaintyNP3__1up"};
  TTreeReaderValue<Float_t> evsf_signal0_syst_EL_EFF_Reco_SIMPLIFIED_UncorrUncertaintyNP4__1down = {fReader_sys, "evsf_signal0_syst_EL_EFF_Reco_SIMPLIFIED_UncorrUncertaintyNP4__1down"};
  TTreeReaderValue<Float_t> evsf_signal0_syst_EL_EFF_Reco_SIMPLIFIED_UncorrUncertaintyNP4__1up = {fReader_sys, "evsf_signal0_syst_EL_EFF_Reco_SIMPLIFIED_UncorrUncertaintyNP4__1up"};
  TTreeReaderValue<Float_t> evsf_signal0_syst_EL_EFF_Reco_SIMPLIFIED_UncorrUncertaintyNP5__1down = {fReader_sys, "evsf_signal0_syst_EL_EFF_Reco_SIMPLIFIED_UncorrUncertaintyNP5__1down"};
  TTreeReaderValue<Float_t> evsf_signal0_syst_EL_EFF_Reco_SIMPLIFIED_UncorrUncertaintyNP5__1up = {fReader_sys, "evsf_signal0_syst_EL_EFF_Reco_SIMPLIFIED_UncorrUncertaintyNP5__1up"};
  TTreeReaderValue<Float_t> evsf_signal0_syst_EL_EFF_Reco_SIMPLIFIED_UncorrUncertaintyNP6__1down = {fReader_sys, "evsf_signal0_syst_EL_EFF_Reco_SIMPLIFIED_UncorrUncertaintyNP6__1down"};
  TTreeReaderValue<Float_t> evsf_signal0_syst_EL_EFF_Reco_SIMPLIFIED_UncorrUncertaintyNP6__1up = {fReader_sys, "evsf_signal0_syst_EL_EFF_Reco_SIMPLIFIED_UncorrUncertaintyNP6__1up"};
  TTreeReaderValue<Float_t> evsf_signal0_syst_EL_EFF_Reco_SIMPLIFIED_UncorrUncertaintyNP7__1down = {fReader_sys, "evsf_signal0_syst_EL_EFF_Reco_SIMPLIFIED_UncorrUncertaintyNP7__1down"};
  TTreeReaderValue<Float_t> evsf_signal0_syst_EL_EFF_Reco_SIMPLIFIED_UncorrUncertaintyNP7__1up = {fReader_sys, "evsf_signal0_syst_EL_EFF_Reco_SIMPLIFIED_UncorrUncertaintyNP7__1up"};
  TTreeReaderValue<Float_t> evsf_signal0_syst_EL_EFF_Reco_SIMPLIFIED_UncorrUncertaintyNP8__1down = {fReader_sys, "evsf_signal0_syst_EL_EFF_Reco_SIMPLIFIED_UncorrUncertaintyNP8__1down"};
  TTreeReaderValue<Float_t> evsf_signal0_syst_EL_EFF_Reco_SIMPLIFIED_UncorrUncertaintyNP8__1up = {fReader_sys, "evsf_signal0_syst_EL_EFF_Reco_SIMPLIFIED_UncorrUncertaintyNP8__1up"};
  TTreeReaderValue<Float_t> evsf_signal0_syst_EL_EFF_Reco_SIMPLIFIED_UncorrUncertaintyNP9__1down = {fReader_sys, "evsf_signal0_syst_EL_EFF_Reco_SIMPLIFIED_UncorrUncertaintyNP9__1down"};
  TTreeReaderValue<Float_t> evsf_signal0_syst_EL_EFF_Reco_SIMPLIFIED_UncorrUncertaintyNP9__1up = {fReader_sys, "evsf_signal0_syst_EL_EFF_Reco_SIMPLIFIED_UncorrUncertaintyNP9__1up"};
  
  TTreeReaderValue<Float_t> evsf_signal0_syst_MUON_EFF_BADMUON_SYS__1down = {fReader_sys, "evsf_signal0_syst_MUON_EFF_BADMUON_SYS__1down"};
  TTreeReaderValue<Float_t> evsf_signal0_syst_MUON_EFF_BADMUON_SYS__1up = {fReader_sys, "evsf_signal0_syst_MUON_EFF_BADMUON_SYS__1up"};
  TTreeReaderValue<Float_t> evsf_signal0_syst_MUON_EFF_ISO_STAT__1down = {fReader_sys, "evsf_signal0_syst_MUON_EFF_ISO_STAT__1down"};
  TTreeReaderValue<Float_t> evsf_signal0_syst_MUON_EFF_ISO_STAT__1up = {fReader_sys, "evsf_signal0_syst_MUON_EFF_ISO_STAT__1up"};
  TTreeReaderValue<Float_t> evsf_signal0_syst_MUON_EFF_ISO_SYS__1down = {fReader_sys, "evsf_signal0_syst_MUON_EFF_ISO_SYS__1down"};
  TTreeReaderValue<Float_t> evsf_signal0_syst_MUON_EFF_ISO_SYS__1up = {fReader_sys, "evsf_signal0_syst_MUON_EFF_ISO_SYS__1up"};
  TTreeReaderValue<Float_t> evsf_signal0_syst_MUON_EFF_RECO_STAT__1down = {fReader_sys, "evsf_signal0_syst_MUON_EFF_RECO_STAT__1down"};
  TTreeReaderValue<Float_t> evsf_signal0_syst_MUON_EFF_RECO_STAT__1up = {fReader_sys, "evsf_signal0_syst_MUON_EFF_RECO_STAT__1up"};
  TTreeReaderValue<Float_t> evsf_signal0_syst_MUON_EFF_RECO_SYS__1down = {fReader_sys, "evsf_signal0_syst_MUON_EFF_RECO_SYS__1down"};
  TTreeReaderValue<Float_t> evsf_signal0_syst_MUON_EFF_RECO_SYS__1up = {fReader_sys, "evsf_signal0_syst_MUON_EFF_RECO_SYS__1up"};
  TTreeReaderValue<Float_t> evsf_signal0_syst_MUON_EFF_TTVA_STAT__1down = {fReader_sys, "evsf_signal0_syst_MUON_EFF_TTVA_STAT__1down"};
  TTreeReaderValue<Float_t> evsf_signal0_syst_MUON_EFF_TTVA_STAT__1up = {fReader_sys, "evsf_signal0_syst_MUON_EFF_TTVA_STAT__1up"};
  TTreeReaderValue<Float_t> evsf_signal0_syst_MUON_EFF_TTVA_SYS__1down = {fReader_sys, "evsf_signal0_syst_MUON_EFF_TTVA_SYS__1down"};
  TTreeReaderValue<Float_t> evsf_signal0_syst_MUON_EFF_TTVA_SYS__1up = {fReader_sys, "evsf_signal0_syst_MUON_EFF_TTVA_SYS__1up"};
  //TTreeReaderValue<Float_t> evsf_signal0_syst_MUON_EFF_TrigStatUncertainty__1down = {fReader_sys, "evsf_signal0_syst_MUON_EFF_TrigStatUncertainty__1down"};
  //TTreeReaderValue<Float_t> evsf_signal0_syst_MUON_EFF_TrigStatUncertainty__1up = {fReader_sys, "evsf_signal0_syst_MUON_EFF_TrigStatUncertainty__1up"};
  //TTreeReaderValue<Float_t> evsf_signal0_syst_MUON_EFF_TrigSystUncertainty__1down = {fReader_sys, "evsf_signal0_syst_MUON_EFF_TrigSystUncertainty__1down"};
  //TTreeReaderValue<Float_t> evsf_signal0_syst_MUON_EFF_TrigSystUncertainty__1up = {fReader_sys, "evsf_signal0_syst_MUON_EFF_TrigSystUncertainty__1up"};

  // MET variables 
  TTreeReaderValue<Float_t> met_eleterm_et = {fReader_nom, "met_eleterm_et"};
  TTreeReaderValue<Float_t> met_eleterm_phi = {fReader_nom, "met_eleterm_phi"};
  TTreeReaderValue<Float_t> met_jetterm_et = {fReader_nom, "met_jetterm_et"};
  TTreeReaderValue<Float_t> met_jetterm_phi = {fReader_nom, "met_jetterm_phi"};
  TTreeReaderValue<Float_t> met_muonterm_et = {fReader_nom, "met_muonterm_et"};
  TTreeReaderValue<Float_t> met_muonterm_phi = {fReader_nom, "met_muonterm_phi"};
  TTreeReaderValue<Float_t> met_softerm_tst_et = {fReader_nom, "met_softerm_tst_et"};
  TTreeReaderValue<Float_t> met_softerm_tst_phi = {fReader_nom, "met_softerm_tst_phi"};
  TTreeReaderValue<Float_t> met_truth_et = {fReader_nom, "met_truth_et"};
  TTreeReaderValue<Float_t> met_truth_phi = {fReader_nom, "met_truth_phi"};
  TTreeReaderValue<Float_t> met_tst_et = {fReader, "met_tst_et"};
  TTreeReaderValue<Float_t> met_tst_phi = {fReader, "met_tst_phi"};
  TTreeReaderValue<Float_t> met_tst_sumet = {fReader, "met_tst_sumet"};
  TTreeReaderValue<Float_t> met_tst_significance = {fReader, "met_tst_significance"};

  // Muon variables 
  TTreeReaderArray<float> mu_pt = {fReader, "mu_pt"};
  TTreeReaderArray<float> mu_eta = {fReader, "mu_eta"};
  TTreeReaderArray<float> mu_phi = {fReader, "mu_phi"};
  TTreeReaderArray<float> mu_SF = {fReader, "mu_SF"};
   TTreeReaderArray<int> mu_passTTVA = {fReader, "mu_passTTVA"};
  //TTreeReaderArray<float> mu_d0sig = {fReader, "mu_d0sig"};
  //TTreeReaderArray<float> mu_z0sinTheta = {fReader, "mu_z0sinTheta"};
  TTreeReaderArray<float> mu_charge = {fReader, "mu_charge"};
  //TTreeReaderArray<int> mu_author = {fReader, "mu_author"};
  //TTreeReaderArray<int> mu_isBadHighPt = {fReader, "mu_isBadHighPt"};
  TTreeReaderArray<int> mu_passIso = {fReader, "mu_passIso"};
  //TTreeReaderArray<int> mu_numberOfPrecisionLayers = {fReader, "mu_numberOfPrecisionLayers"};
  TTreeReaderArray<float> mu_SF_iso = {fReader, "mu_SF_iso"};
  TTreeReaderArray<float> mu_SF_rec = {fReader, "mu_SF_rec"};
  TTreeReaderArray<int> mu_trigmatched_1u = {fReader, "mu_trigmatched_1u"};
  TTreeReaderArray<int> mu_trigmatched_2u = {fReader, "mu_trigmatched_2u"};
  //TTreeReaderArray<int> mu_trigmatched = {fReader, "mu_trigmatched"};
  TTreeReaderArray<int> mu_isBad = {fReader, "mu_isBad"};
  TTreeReaderArray<float> mu_truthEta = {fReader_nom, "mu_truthEta"};
  TTreeReaderArray<float> mu_truthPhi = {fReader_nom, "mu_truthPhi"};
  TTreeReaderArray<float> mu_truthPt = {fReader_nom, "mu_truthPt"};
  TTreeReaderArray<float> mu_truthTheta = {fReader_nom, "mu_truthTheta"};
  TTreeReaderArray<float> mu_truthQOverP = {fReader_nom, "mu_truthQOverP"};
  TTreeReaderArray<unsigned int> mu_truth_IFFtype = {fReader_nom, "mu_truth_IFFtype"};
  /*
  TTreeReaderArray<int> mu_isotool_pass_FCTightTrackOnly = {fReader_nom, "mu_isotool_pass_FCTightTrackOnly"};
  TTreeReaderArray<int> mu_isotool_pass_PflowLoose_VarRad = {fReader_nom, "mu_isotool_pass_PflowLoose_VarRad"};
  TTreeReaderArray<int> mu_isotool_pass_PflowTight_VarRad = {fReader_nom, "mu_isotool_pass_PflowTight_VarRad"};
  TTreeReaderArray<int> mu_isotool_pass_Tight_VarRad = {fReader_nom, "mu_isotool_pass_Tight_VarRad"};
  TTreeReaderArray<int> mu_isotool_pass_Loose_VarRad = {fReader_nom, "mu_isotool_pass_Loose_VarRad"};
  */ 
  TTreeReaderArray<int> mu_truth_origin = {fReader_nom, "mu_truth_origin"};
  TTreeReaderArray<int> mu_truth_type = {fReader_nom, "mu_truth_type"};

  // Electron variables 
  TTreeReaderArray<float> el_pt = {fReader, "el_pt"};
  TTreeReaderArray<float> el_eta = {fReader, "el_eta"};
  TTreeReaderArray<float> el_cl_etaBE2 = {fReader, "el_cl_etaBE2"};
  TTreeReaderArray<float> el_phi = {fReader, "el_phi"};
  TTreeReaderArray<float> el_SF = {fReader, "el_SF"};
  TTreeReaderArray<int> el_passLHID = {fReader, "el_passLHID"};
  TTreeReaderArray<int> el_passTTVA = {fReader, "el_passTTVA"};
  //TTreeReaderArray<float> el_d0sig = {fReader, "el_d0sig"};
  //TTreeReaderArray<float> el_z0sinTheta = {fReader, "el_z0sinTheta"};
  TTreeReaderArray<int> el_passIso = {fReader, "el_passIso"};
  TTreeReaderArray<float> el_SF_iso = {fReader, "el_SF_iso"};
  TTreeReaderArray<float> el_SF_isoGradient = {fReader, "el_SF_isoGradient"};
  TTreeReaderArray<float> el_SF_rec = {fReader, "el_SF_rec"};
  TTreeReaderArray<float> el_SF_id = {fReader, "el_SF_id"};
  TTreeReaderArray<float> el_SF_cid = {fReader, "el_SF_cid"};
  TTreeReaderArray<float> el_SF_idLooseAndBLayer = {fReader, "el_SF_idLooseAndBLayer"};
  TTreeReaderArray<int> el_trigmatched_1e = {fReader, "el_trigmatched_1e"};
  TTreeReaderArray<int> el_trigmatched_2e = {fReader, "el_trigmatched_2e"};
  //TTreeReaderArray<int> el_trigmatched = {fReader, "el_trigmatched"};
  TTreeReaderArray<float> el_charge = {fReader, "el_charge"};
  TTreeReaderArray<float> el_truth_pt = {fReader_nom, "el_truth_pt"};
  TTreeReaderArray<float> el_truth_eta = {fReader_nom, "el_truth_eta"};
  TTreeReaderArray<float> el_truth_phi = {fReader_nom, "el_truth_phi"};
  TTreeReaderArray<float> el_truth_E = {fReader_nom, "el_truth_E"};
  TTreeReaderArray<float> el_truth_Q = {fReader_nom, "el_truth_Q"};
  //TTreeReaderArray<int> el_author = {fReader_nom, "el_author"};
  TTreeReaderArray<int> el_isConv = {fReader_nom, "el_isConv"};
  //TTreeReaderArray<float> el_ecisBDT = {fReader_nom, "el_ecisBDT"};
  TTreeReaderArray<unsigned int> el_truth_IFFtype = {fReader_nom, "el_truth_IFFtype"};
  //TTreeReaderArray<int> el_truth_matched = {fReader_nom, "el_truth_matched"};
  //TTreeReaderArray<int> el_truth_mothertype = {fReader_nom, "el_truth_mothertype"};
  //TTreeReaderArray<int> el_truth_status = {fReader_nom, "el_truth_status"};
  TTreeReaderArray<int> el_truth_type = {fReader_nom, "el_truth_type"};
  //TTreeReaderArray<int> el_truth_typebkg = {fReader_nom, "el_truth_typebkg"};
  TTreeReaderArray<int> el_truth_origin = {fReader_nom, "el_truth_origin"};
  //TTreeReaderArray<int> el_truth_originbkg = {fReader_nom, "el_truth_originbkg"};
  TTreeReaderArray<int> el_isotool_pass_gradient = {fReader_nom, "el_isotool_pass_gradient"};
  TTreeReaderArray<int> el_isotool_pass_FCLoose = {fReader_nom, "el_isotool_pass_FCLoose"};
  TTreeReaderArray<int> el_isotool_pass_FCTight = {fReader_nom, "el_isotool_pass_FCTight"};

  // Jet variables 
  TTreeReaderArray<float> jet_pt = {fReader, "jet_pt"};
  TTreeReaderArray<float> jet_eta = {fReader, "jet_eta"};
  TTreeReaderArray<float> jet_phi = {fReader, "jet_phi"};
  TTreeReaderArray<float> jet_m = {fReader, "jet_m"};
  //TTreeReaderArray<int> jet_NumTrkPt500 = {fReader, "jet_NumTrkPt500"};
  TTreeReaderArray<float> jet_DL1r_score = {fReader, "jet_DL1r_score"};
  TTreeReaderArray<int> jet_isbjet = {fReader, "jet_isbjet"};
  TTreeReaderArray<int> jet_PartonTruthLabelID = {fReader, "jet_PartonTruthLabelID"};
  //TTreeReaderArray<int> jet_ConeTruthLabelID = {fReader, "jet_ConeTruthLabelID"};
  //TTreeReaderArray<float> jet_timing = {fReader, "jet_timing"};
  TTreeReaderArray<int> jet_isbjet_loose = {fReader, "jet_isbjet_loose"};
  TTreeReaderArray<float> jet_jvt = {fReader, "jet_jvt"};
  TTreeReaderArray<float> jet_fjvt = {fReader, "jet_fjvt"};
  TTreeReaderArray<int> jet_cleaning = {fReader, "jet_cleaning"};
  //TTreeReaderArray<float> jet_TruthLabelDeltaR_B = {fReader_nom, "jet_TruthLabelDeltaR_B"};
  //TTreeReaderArray<float> jet_TruthLabelDeltaR_C = {fReader_nom, "jet_TruthLabelDeltaR_C"};
  //TTreeReaderArray<float> jet_TruthLabelDeltaR_T = {fReader_nom, "jet_TruthLabelDeltaR_T"};

  EventSelector(TTree * /*tree*/ =0) { }
  virtual ~EventSelector() { }
  virtual Int_t   Version() const { return 2; }
  virtual void    Begin(TTree *tree);
  virtual void    SlaveBegin(TTree *tree);
  virtual void    Init(TTree *tree);
  virtual Bool_t  Notify();
  virtual Bool_t  Process(Long64_t entry);
  virtual Int_t   GetEntry(Long64_t entry, Int_t getall = 0) { return fChain ? fChain->GetTree()->GetEntry(entry, getall) : 0; }
  virtual void    SetOption(const char *option) { fOption = option; }
  virtual void    SetObject(TObject *obj) { fObject = obj; }
  virtual void    SetInputList(TList *input) { fInput = input; }
  virtual TList  *GetOutputList() const { return fOutput; }
  virtual void    SlaveTerminate();
  virtual void    Terminate();
  void WriteToFile(TString fileid, TString option, TString name);
  void PrintCutflow(Int_t fileid); 
  vector<Float_t> GetLogBinning(Int_t nbins, Float_t xmin, Float_t xmax); 
  vector<Float_t> GetSRBinning(TString chn, Float_t xmin, Float_t xmax); 
  map<TString, Float_t> GetLepSFVariations(Long64_t entry); 
  map<TString, Float_t> GetCidSFVariations(Long64_t entry); 
  map<TString, Float_t> GetJetSFVariations(Long64_t entry); 
  vector<Double_t> GetEffBinning(); 
  ClassDef(EventSelector,0);

};

#endif

#ifdef EventSelector_cxx
void EventSelector::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the reader is initialized.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

  TString option = GetOption(); 
  TObjArray *my_option = option.Tokenize("_");
  int doTruth = atoi(((TObjString *)(my_option->At(1)))->String());
  int doSFSyst = atoi(((TObjString *)(my_option->At(3)))->String());
  int doCalibSyst = atoi(((TObjString *)(my_option->At(4)))->String());

  fReader.SetTree(tree);
  if(!doSFSyst && !doCalibSyst){ fReader_nom.SetTree(tree); } 
  if(doSFSyst){ fReader_sys.SetTree(tree); } 
  fChain = tree; 
}

Bool_t EventSelector::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}


#endif // #ifdef EventSelector_cxx
