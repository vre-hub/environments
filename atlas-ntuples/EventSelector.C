#define EventSelector_cxx
#include "EventSelector.h"
#include <TH2.h>
#include <TStyle.h>
#include "TLorentzVector.h"
#include <fstream>
#include <TString.h>
#include <math.h>
#include <cmath>
#include <iostream>
#include <string> 
#include <algorithm> 
#include <iterator> 
#include "CalcGenericMT2/src/MT2_ROOT.h"
#include "MatrixMethod/MatrixMethod.cxx"
#include "MatrixMethod/MMefficiencies.cxx"

TLorentzVector l1, l2, l3, ll, l1_truth, l2_truth; 

// Options 
Int_t isData = 0, isMC = 0; 
Int_t doTruth = 0, doCutflow = 0, doSyst = 0, doSFSyst = 0, doCalibSyst = 0, doFakes = 0, doLoose = 0, isRecast = 0, isAFII = 0, makeTree = 0, doDebug = 0; 

// Sample and channel stuff
Int_t DSID, prev_DSID = 0, yr; 
Int_t Incl_Sherpa[] = {364100, 364101, 364102, 364103, 364104, 364105, 364106, 364107, 364108, 364114, 364115, 364117, 364118, 364120};
Int_t Incl_Sh2211[] = {700320, 700321, 700322, 700323, 700324, 700325, 700326, 700327, 700328}; 
Int_t Incl_Powheg[] = {361106, 361107}; 
Int_t TTbar_samples[] = {410470, 410472}; //, 410633, 410634, 410635, 410636, 410637}; 
Int_t STincl_samples[] = {410644, 410645, 410658, 410659}; 
Int_t STdilep_samples[] = {410648, 410649}; 
Int_t Diboson_samples[] = {363356, 363358, 363359, 363360, 363489, 364250, 364253, 364254, 364255, 700488, 700489, 700490, 700491, 700492, 700493, 700494, 700495, 700496, 700600, 700601, 700602, 700603, 700604, 700605}; 
Int_t Zee_samples[] = {364114, 364115, 364116, 364117, 364118, 364119, 364120, 364121, 364122, 364123, 364124, 364125, 364126, 364127, 366309, 366310, 366312, 366313, 366315}; 
Int_t Sh2211_samples[] = {700320, 700321, 700322, 700323, 700324, 700325, 700326, 700327, 700328, 700452, 700453, 700454, 700455, 700456, 700457, 700458, 700459, 700460, 700488, 700489, 700490, 700491, 700492, 700493, 700494, 700495, 700496, 700600, 700601, 700602, 700603, 700604, 700605}; 
Int_t Sh221_samples[] = {364100, 364101, 364102, 364103, 364104, 364105, 364106, 364107, 364108, 364109, 364110, 364111, 364112, 364113, 364114, 364115, 364116, 364117, 364118, 364119, 364120, 364121, 364122, 364123, 364124, 364125, 364126, 364127, 366300, 366301, 366302, 366303, 366304, 366305, 366306, 366307, 366308, 366309, 366310, 366312, 366313, 366315}; 
Int_t Diboson_Sh2211[] = {700488, 700489, 700490, 700491, 700492, 700493, 700494, 700495, 700496};  
Int_t Diboson_Sh2212[] = {700600, 700601, 700602, 700603, 700604, 700605}; 
Int_t isInclusive_Sherpa = 0, isInclusive_Powheg = 0, isInclusive_Sh2211 = 0, isTop = 0, isTTbar = 0, isSTincl = 0, isSTdilep = 0, isDiboson = 0, isSh2211 = 0, isSh221 =0, isZee = 0, isWB = 0, isSystChannel = 0, isTreeChannel = 0; 
TString  dileptons, final_name, filepath, period, name_1; 
TString option, dataset;  
vector<TString> channel_names, of_channel_names, all_channels, passed_channels, all_METcuts, passed_METcuts, all_METrelcuts, passed_METrelcuts, all_METsigcuts, passed_METsigcuts, variations, SFvariations, weightVariations, Top_variations, Sh2211_variations, blinded_channels, syst_channel_names, syst_channels;  
map<TString, Int_t> weight_indices; 
Int_t isEE = 0, isMM = 0; 

// Kinematic variables 
Float_t mll, met, met_phi, met_sig, met_sig_rel, met_ht, dphi, dR_ll, dphi_ll, ptll, ht, met_rel, dphi_rel, met_res, met_soft, met_elec, met_muon, met_jet, pt_lep1, pt_lep2;
Float_t met_truth, met_rel_truth, dphi_rel_truth, mll_truth, dphi_truth;
Int_t njets, ncjets, nfjets, nljets, nbjets;    

// Weights and SFs
Float_t wgt, wgt_mc, wgt_pu, wgt_kf, wgt_ttbar, wgt_nlo_ew, wgt_xs, wgt_lsf, wgt_jsf, wgt_tsf, g_eff, xs, wgt_jet, wgt_fjet, wgt_bjet, wgt_fakes, LLwgt_noSF, wgt_lsf_lep1Loose, wgt_lsf_lep1Tight, wgt_lsf_lep2Loose, wgt_lsf_lep2Tight, wgt_lsf_lep3Loose, wgt_lsf_lep3Tight; 
Float_t nb2fb = 1.E6, pb2fb = 1.E3;
Float_t sow_nom = 0; 
float sow_nloew = 0;

// Cutflow variables 
Long64_t nevents = 0, sample_nevents = 0, eventID = 0; 
Int_t n_trig_e = 0, n_jetclean_e = 0, n_twolep_e = 0, n_loose_e = 0, n_pt_e = 0, n_eta_e =0, n_mll70_e = 0, n_mll120_e = 0, n_met100_e = 0, n_mll70_e_TT = 0;  
Int_t n_trig_u = 0, n_jetclean_u = 0, n_twolep_u = 0, n_loose_u = 0, n_mubad = 0, n_pt_u = 0, n_mll70_u = 0, n_mll120_u = 0, n_met100_u = 0, n_mll70_u_TT = 0;  
Int_t passed_pt30 = 0; 
Float_t min_MET = 999; 
Int_t n_2lep_truth = 0, n_not2lep_truth;  
Int_t n_SR1_500 = 0, n_SR1_1000 = 0, n_SR1_1500 =0, n_SR2_500 = 0, n_SR2_1000 = 0, n_SR2_1500 = 0, n_SR3_500 = 0, n_SR3_1000 = 0, n_SR3_1500 = 0; 
Int_t nev_syst = 0, nev_nom = 0; 

// Weight sums 
Float_t s_mc_e = 0, s_kf_e = 0, s_pu_e = 0, s_xs_e = 0, s_lsf_e = 0, s_trig_e = 0, s_tt_e = 0, s_wgt_e = 0;     
Float_t s_mc_u = 0, s_kf_u = 0, s_pu_u = 0, s_xs_u = 0, s_lsf_u = 0, s_trig_u = 0, s_tt_u = 0, s_wgt_u = 0;     
Float_t s_mc_x_pu = 0, s_mc = 0; 
Float_t sw_bin1 = 0, sw_bin2 = 0, sw_bin3 = 0; 
Float_t test_sow = 0; 

Float_t m_e = 0.511e-3; // Electron mass (GeV) 
Float_t m_u = 0.106; // Muon mass (GeV) 

//ofstream outfile ("EventNumbers.txt");
ofstream  outfile; 

//
//Matrix Method
//
// Flag for whether leptons pass Tight
Bool_t tight1, tight2, tight3;
//Loose/Tight event counts (used per event, so one of them will be 1, the others 0)
Double_t NTT,NTl,NlT,Nll;
//Fake and real efficiencies
Double_t f1,f2,r1,r2;
//Tool to read different kinds of efficiencies from files (fake effs, real effs, 1D/2D, systematics variations...)
MMefficiencies MMeffs;
//Matrix Method tool from Eirik
MatrixMethod MM;

void EventSelector::Begin(TTree * /*tree*/)
{

  time_t t; // t passed as argument in function time()
  struct tm * tt; // decalring variable for localtime()
  time (&t); //passing argument to time()
  tt = localtime(&t);
  cout << "Process started: " << asctime(tt);

  // Read options 
  option = GetOption();
  TObjArray *my_option = option.Tokenize("_");
  dataset = ((TObjString *)(my_option->At(0)))->String();
  doTruth = atoi(((TObjString *)(my_option->At(1)))->String());
  doCutflow = atoi(((TObjString *)(my_option->At(2)))->String());
  doSFSyst = atoi(((TObjString *)(my_option->At(3)))->String());
  doCalibSyst = atoi(((TObjString *)(my_option->At(4)))->String());
  doFakes = atoi(((TObjString *)(my_option->At(5)))->String());
  doLoose = atoi(((TObjString *)(my_option->At(6)))->String());
  isRecast = atoi(((TObjString *)(my_option->At(7)))->String());
  isAFII = atoi(((TObjString *)(my_option->At(8)))->String());
  delete my_option; 

  if(doSFSyst || doCalibSyst){ doSyst = 1; } 
  //if(isRecast){ doSFSyst = 1; doCalibSyst= 1; }

  
  string stringy_option(dataset); 
  if(stringy_option.find("data")!=string::npos){isData=1;}else{isMC=1;}

  if(doTruth){ outfile.open("Signal_info_"+dataset+".txt"); } 

  TH1::SetDefaultSumw2();

  // Define channels to consider 
  channel_names = {"incl", "incl_high", "presel", "incl_SS", "incl_OS", "incl_sb", "incl_high_dphi25", "incl_high_0j", "incl_high_nj",  "incl_high_0b", "incl_high_nb",
		   "Zpeak", "low_wZ", "low", "lowmet_incl", "lowmet_dphi25", "lowmet_0j", "lowmet_nj", "bv85_low", "bv85_dphi25_low", "bv77", "bv85", "bv85_dphi25", "VR_top_low",
		   "CR_Z_low", "CR_Z", "CR_Z_0j", "CR_top", "CR_Z_METsig", "CR_db_METsig", "VR_Z_METsig", "VR_db_METsig", "VR_Z_low", "VR_Z", "VR_top",    
		   "CR_Z_low_pre", "CR_Z_pre", "CR_Z_dphi", "CR_top_pre", 
		   "VR_Z_low_pre", "VR_Z_pre", "VR_Z_dphi", "VR_top_pre",
		   "VR_fakes", "VR_fakes_1j", "VR_fakes_METrel", "VR_fakes_METsig",   
		   "SR_bin1_METsig", "SR_bin2_METsig", "SR_bin3_METsig", "SR_bin1_METrel", "SR_bin2_METrel", "SR_bin3_METrel", "SR_bin1_MET", "SR_bin2_MET", "SR_bin3_MET",
		   "SR_bin1_METrel_0j", "SR_bin2_METrel_0j", "SR_bin3_METrel_0j", "SR_bin1_METrel_dphi", "SR_bin2_METrel_dphi", "SR_bin3_METrel_dphi",
		   "SR_bin1_METrel_incl", "SR_bin2_METrel_incl", "SR_bin3_METrel_incl", "SR_high", "SR_low", "SR_bin1_METsig_v2", "SR_bin2_METsig_v2", "SR_bin3_METsig_v2",};

  of_channel_names = {"incl", "incl_high", "CR_top", "CR_top_0b", "VR_top", "VR_top_0b", "CR_top_bin1", "CR_top_bin2", "CR_top_bin3", "VR_top_METsig", "CR_top_METsig", "VR_top_METsig_0b", "CR_top_METsig_0b"};

  syst_channel_names = {"incl", "incl_high", "presel", "CR_Z_METsig", "CR_db_METsig", "VR_Z_METsig", "VR_db_METsig", "SR_bin1_METsig", "SR_bin2_METsig", "SR_bin3_METsig"};
  // "SR_bin1_METsig_v2", "SR_bin2_METsig_v2", "SR_bin3_METsig_v2", "SR_bin1_MET", "SR_bin2_MET", "SR_bin3_MET", SR_bin1_METrel", "SR_bin2_METrel", "SR_bin3_METrel", "SR_high"
  // "CR_Z",  "CR_db", "VR_Z", "VR_db", , 
 
  /*
  all_METcuts = {};
  Int_t max_METcut = 300; 
  for(Int_t i = 0; i<=max_METcut; i+=10){
    string cut = to_string(i); 
    all_METcuts.push_back(cut); 
    channel_names.push_back("METcut"+cut); 
    channel_names.push_back("METcut"+cut+"_bv77"); 
    channel_names.push_back("METcut"+cut+"_bv85"); 
    channel_names.push_back("METcut"+cut+"_bv85_dphi25"); 
  }
  */ 
  all_METrelcuts = {};
  Int_t max_METrelcut = 300; 
  for(Int_t i = 0; i<=max_METrelcut; i+=10){
    string cut = to_string(i); 
    all_METrelcuts.push_back(cut); 
    channel_names.push_back("METrelcut"+cut); 
    channel_names.push_back("METrelcut"+cut+"_bv85"); 
    channel_names.push_back("METrelcut"+cut+"_bv85_dphi25"); 
    // Low-mass
    channel_names.push_back("METrelcut"+cut+"_low"); 
    channel_names.push_back("METrelcut"+cut+"_bv85_low"); 
    channel_names.push_back("METrelcut"+cut+"_bv85_dphi25_low"); 
  }
  /*
  all_METsigcuts = {}; 
  Int_t max_METsigcut = 30; 
  for(Int_t i = 0; i<=max_METsigcut; i+=1){
    string cut = to_string(i); 
    all_METsigcuts.push_back(cut); 
    channel_names.push_back("METsigcut"+cut); 
    channel_names.push_back("METsigcut"+cut+"_bv85"); 
    channel_names.push_back("METsigcut"+cut+"_bv85_dphi20"); 
    channel_names.push_back("METsigcut"+cut+"_bv85_dphi22"); 
    channel_names.push_back("METsigcut"+cut+"_bv85_dphi24"); 
    channel_names.push_back("METsigcut"+cut+"_bv85_dphi25"); 
    channel_names.push_back("METsigcut"+cut+"_bv85_dphi26"); 
    channel_names.push_back("METsigcut"+cut+"_bv85_dphi28"); 
    channel_names.push_back("METsigcut"+cut+"_bv85_dphi30"); 
  }
  */ 

  all_channels = {};
  for(const auto & chn:channel_names){
    all_channels.push_back("ee_"+chn); 
    all_channels.push_back("uu_"+chn); 
    if(isMC && doFakes){
      all_channels.push_back("ee_"+chn+"_real"); 
      all_channels.push_back("uu_"+chn+"_real"); 
    }
    isSystChannel = (std::find(std::begin(syst_channel_names), std::end(syst_channel_names), chn) != std::end(syst_channel_names));
    if(isSystChannel){
      if(doFakes){
	syst_channels.push_back("ee_"+chn+"_real"); 
	syst_channels.push_back("uu_"+chn+"_real"); 
      }
      else{
	syst_channels.push_back("ee_"+chn); 
	syst_channels.push_back("uu_"+chn); 
      }
    }
  }

  for(const auto & chn:of_channel_names){
    all_channels.push_back("eu_"+chn);  
  }
  
  all_channels.push_back("eeu_CR_fakes");  
  all_channels.push_back("uue_CR_fakes");  
  if(isMC && doFakes){
    for(const auto & chn:of_channel_names){
      all_channels.push_back("eu_"+chn+"_real");  
    }
    all_channels.push_back("eeu_CR_fakes_real");  
    all_channels.push_back("uue_CR_fakes_real");  
  }

  if(doSyst){
    if(doFakes){
      syst_channels.push_back("eu_CR_top_real"); 
      syst_channels.push_back("eu_VR_top_real"); 
    }
    else{
      //syst_channels.push_back("eu_CR_top"); 
      //syst_channels.push_back("eu_VR_top"); 
      syst_channels.push_back("eu_incl_high"); 
      syst_channels.push_back("eu_CR_top_METsig"); 
      syst_channels.push_back("eu_VR_top_METsig"); 
      syst_channels.push_back("eu_CR_top_METsig_0b"); 
      syst_channels.push_back("eu_VR_top_METsig_0b"); 
      //syst_channels.push_back("eu_CR_top_0b"); 
      //syst_channels.push_back("eu_VR_top_0b"); 
    }
  }
  variations = {}; SFvariations = {}; Top_variations = {}; Sh2211_variations = {};     

  if(doSyst == 1){ 
    TFile *f;
    if (isRecast)
      f = new TFile("recast/test/ntuples/mc16a/user.dummy.recastSignal.mc16_13TeV.500345.MGPy8EG_MET_50_lv_lds_mZp_300_ee_minitrees.root/user.dummy.dummy._000001.minitrees.root");
    else{
      if(doCalibSyst){
	f = new TFile("/scratch/MiniTrees/SystCalib_jan2023/MC/mc16a/user.ehaaland.BKGSYSTmc16a02012023.mc16_13TeV.410644.PowhegPythia8EvtGen_A14_singletop_schan_lept_top_minitrees.root/user.ehaaland.31769699._000001.minitrees.root");
      }
      if(doSFSyst){
	f = new TFile("/scratch/MiniTrees/SystSF_dec2022/MC/mc16a/user.ehaaland.BKGSYSTmc16a23122022.mc16_13TeV.410644.PowhegPythia8EvtGen_A14_singletop_schan_lept_top_minitrees.root/user.ehaaland.31736227._000001.minitrees.root");
      }
    }
    
    if(doCalibSyst){
      TH1* calib = (TH1*)f->Get("histoCalibSys"); 
      for(Int_t b = 1; b<=calib->GetNbinsX(); b++){
	variations.push_back(calib->GetXaxis()->GetBinLabel(b)); 
	//cout << calib->GetXaxis()->GetBinLabel(b) << endl; 
      }
      // Add extra AFII variations 
      if(isRecast){
	variations.push_back("JET_JER_DataVsMC_MC16__1up");
	variations.push_back("JET_PunchThrough_MC16__1up");
      }
      else{
	variations.push_back("JET_JER_DataVsMC_AFII__1up");
	variations.push_back("JET_RelativeNonClosure_AFII__1up");
	variations.push_back("JET_PunchThrough_AFII__1up");
      }
    }
    if(doSFSyst){
      // Add SF systematics 
      TH1* SF = (TH1*)f->Get("histoSfSys");
      for(Int_t b = 1; b<=SF->GetNbinsX(); b++){
	TString sf_syst = SF->GetXaxis()->GetBinLabel(b); 
	if( sf_syst.Contains("ChargeIDSel") ){continue;} // sf_syst.Contains("down") ||
	//cout << sf_syst << endl;
	variations.push_back(""); 
	variations.push_back(sf_syst);       
	SFvariations.push_back(sf_syst);       
      }
      delete f;
	
      // PU systematic 
      variations.push_back("pu_weight_PRW_DATASF__1up"); 
      variations.push_back("pu_weight_PRW_DATASF__1down"); 

      // Top mass variation 
      variations.push_back("Top_Mass");  

      // Top theory variations 
      Top_variations = {"muR = 1.00, muF = 2.00", "muR = 1.00, muF = 0.50", "muR = 2.00, muF = 1.00", "muR = 0.50, muF = 1.00", "Var3cUp", "Var3cDown", "isr:muRfac=1.0_fsr:muRfac=2.0", "isr:muRfac=1.0_fsr:muRfac=0.5"}; 
      // Add PDF variations 
      Top_variations.push_back("PDF set = 90900"); // Nominal PDF4LHC15 variation 
      for(Int_t pdf = 90901; pdf<=90930; pdf++){ 
	TString pdf_var = "PDF set = "+TString(to_string(pdf)); 
	Top_variations.push_back(pdf_var);  
      }    
      for(const auto & var:Top_variations){ variations.push_back(var); } 

      // Weak boson (DY and VV) theory variations 
      Sh2211_variations = {"MUR0.5_MUF0.5_PDF303200_PSMUR0.5_PSMUF0.5", "MUR0.5_MUF1_PDF303200_PSMUR0.5_PSMUF1", "MUR1_MUF0.5_PDF303200_PSMUR1_PSMUF0.5", "MUR1_MUF1_PDF303200", "MUR1_MUF2_PDF303200_PSMUR1_PSMUF2", "MUR2_MUF1_PDF303200_PSMUR2_PSMUF1", "MUR2_MUF2_PDF303200_PSMUR2_PSMUF2", "MUR1_MUF1_PDF303200_ASSEW", "MUR1_MUF1_PDF303200_MULTIASSEW", "MUR1_MUF1_PDF303200_EXPASSEW", "MUR1_MUF1_PDF269000", "MUR1_MUF1_PDF270000"}; 
      // Add PDF variations 
      for(Int_t pdf = 303201; pdf<=303300; pdf++){ 
	TString pdf_var = "MUR1_MUF1_PDF"+TString(to_string(pdf)); 
	Sh2211_variations.push_back(pdf_var);  
      }    
      for(const auto & var:Sh2211_variations){ variations.push_back(var); }
    }
  }
  else if (isData){ variations = {"", "RF", "FF", "Fakes", "Fakes_xsec_up", "Fakes_xsec_down"}; } // , 
  else{ variations = {""}; SFvariations = {""}; } 

  // Get log-binning 
  vector<Float_t> xbins_pt = GetLogBinning(120, 10, 10000);
  vector<Float_t> xbins_mll = GetLogBinning(74, 70, 10000); // old binning 
  //vector<Float_t> xbins_mll = GetLogBinning(148, 70, 10000);
  //vector<Float_t> xbins_mll_trunc = GetLogBinning(66, 180, 1500); 
  vector<Float_t> xbins_metsig = GetLogBinning(120, 0.1, 100);
  //vector<Float_t> xbins_mcw = GetLogBinning(150, 0.1, 1000);

  // Signal region binning 
  vector<Float_t> xbins_mee_SR = GetSRBinning("ee", 180, 1200); Int_t Nbins_SR_ee = xbins_mee_SR.size()-1; 
  vector<Float_t> xbins_muu_SR = GetSRBinning("uu", 180, 1200); Int_t Nbins_SR_uu = xbins_muu_SR.size()-1; 
  // Tailored efficiency binning
  vector<Double_t> xbins_eff = GetEffBinning(); Int_t NbinsEff = xbins_eff.size()-1;
  // Various mass binning
  vector<Float_t> xbins_mll40 = GetLogBinning(40, 180, 1200); Int_t Nbins_mll40 = xbins_mll40.size()-1; 
  vector<Float_t> xbins_mll50 = GetLogBinning(50, 180, 1200); Int_t Nbins_mll50 = xbins_mll50.size()-1; 
  vector<Float_t> xbins_mll60 = GetLogBinning(60, 180, 1200); Int_t Nbins_mll60 = xbins_mll60.size()-1; 
  vector<Float_t> xbins_presel = {70,72,74,76,78,81,83,86,88,91,94,96,99,102,105,109,112,115,119,122,126,130,134,138,142,146,151,155,160,165,170,175,180,186,194,201,209,217,226,234,243,253,263,273,283,294,306,318,330,343,356,370,384,399,414,430,447,464,482,501,520,540,561,583,606,629,653,679,705,732,761,790,821,852,885,920,955,992,1031,1070,1112,1155,1199}; Int_t Nbins_presel = xbins_presel.size()-1; 
  
  // Vector for linear binning 
  vector<Float_t> xbins_lin;
  vector<Float_t> xbins_mcw; 
  for(Int_t i=-200; i<201; i++){ 
    xbins_mcw.push_back(i); 
    if(i>=0){
      xbins_lin.push_back(i);
    } 
  }

  // Define histograms
  TH1::AddDirectory(false); //prevents that the program hangs while cleaning up after the Python script is done
  TString h_name; 
  for( const auto & chn:all_channels ){
    isSystChannel = (std::find(std::begin(syst_channels), std::end(syst_channels), chn) != std::end(syst_channels));
    for(const auto & var:variations ){ 
      if(doSyst && !isSystChannel && var!=""){ continue; } 
      if(var == ""){ h_name = chn; } 
      else{ h_name = chn+"_"+var; }
      //if(h_name.Contains("NLO")){cout << h_name << endl; }
      if(chn.Contains("cut")){ 
	if(chn.Contains("low")){ h_mll_low[h_name] = new TH1D("h_"+h_name+"_mll_low", h_name+"_mll_low", 50, 10, 60); } 
	else{ 
	  if( chn.Contains("uu") || chn.Contains("eu")){ h_mll[h_name] = new TH1D("h_"+h_name+"_mll", h_name+"_mll", Nbins_SR_uu, &xbins_muu_SR[0]); }
	  else{ h_mll[h_name] = new TH1D("h_"+h_name+"_mll", h_name+"_mll", Nbins_SR_ee, &xbins_mee_SR[0]); } 
	} 
      } 
      else{
	if( chn.Contains("SR_bin") || chn.Contains("SR_high") || chn.Contains("CR_top") || chn.Contains("VR_top") || chn.Contains("CR_Z") || chn.Contains("VR_Z") || chn.Contains("incl_high") ){
	  if( chn.Contains("uu") || chn.Contains("eu")){ h_mll[h_name] = new TH1D("h_"+h_name+"_mll", h_name+"_mll", Nbins_SR_uu, &xbins_muu_SR[0]); }
	  else{ h_mll[h_name] = new TH1D("h_"+h_name+"_mll", h_name+"_mll", Nbins_SR_ee, &xbins_mee_SR[0]); } 
	}
	else if(chn.Contains("presel")){
	  h_mll[h_name] = new TH1D("h_"+h_name+"_mll", h_name+"_mll", Nbins_presel, &xbins_presel[0]); 
	}
	else{
	  h_mll[h_name] = new TH1D("h_"+h_name+"_mll", h_name+"_mll", 74, &xbins_mll[0]);
	}
	h_pt1[h_name] = new TH1D("h_"+h_name+"_pt1", h_name+"_pt1", 120, &xbins_pt[0]);  
	h_pt2[h_name] = new TH1D("h_"+h_name+"_pt2", h_name+"_pt2", 120, &xbins_pt[0]);  
	h_met[h_name] = new TH1D("h_"+h_name+"_met", h_name+"_met", 120, &xbins_pt[0]);
	h_met_sig[h_name] = new TH1D("h_"+h_name+"_met_sig", h_name+"_met_sig", 50, 0, 50);        
	h_met_rel[h_name] = new TH1D("h_"+h_name+"_met_rel", h_name+"_met_rel", 120, &xbins_pt[0]);
	h_nbjets[h_name] = new TH1D("h_"+h_name+"_nbjets", h_name+"_nbjets", 10, 0, 10);
	if(chn.Contains("CR_Z_low") || chn.Contains("VR_Z_low") || chn.Contains("CR_top") || chn.Contains("incl_sb") || chn.Contains("VR_db")){ 
	  h_mll_lin[h_name] = new TH1D("h_"+h_name+"_mll_lin", h_name+"_mll_lin", 70, 110, 180); 
	}
	else if( chn.Contains("CR_db")){ h_mll_lin[h_name] = new TH1D("h_"+h_name+"_mll_lin", h_name+"_mll_lin", 40, 70, 110); }
	else{ h_mll_lin[h_name] = new TH1D("h_"+h_name+"_mll_lin", h_name+"_mll_lin", 264, 180, 1500); }
	if(doFakes && !doSyst){
	  // Histograms for real efficiencies
	  h_pt_loose[h_name] = new TH1D("h_"+h_name+"_pt_loose", h_name+"_pt_loose", NbinsEff, &xbins_eff[0]);
	  h_pt_tight[h_name] = new TH1D("h_"+h_name+"_pt_tight", h_name+"_pt_tight", NbinsEff, &xbins_eff[0]);
	  h_ptEta_loose[h_name] = new TH2D("h_"+h_name+"_ptEta_loose", h_name+"_ptEta_loose", NbinsEff, &xbins_eff[0], 250, 0, 2.5);
	  h_ptEta_tight[h_name] = new TH2D("h_"+h_name+"_ptEta_tight", h_name+"_ptEta_tight", NbinsEff, &xbins_eff[0], 250, 0, 2.5);
	  h_mll_loose[h_name] = new TH1D("h_"+h_name+"_mll_loose", h_name+"_mll_loose", NbinsEff, &xbins_eff[0]);
	  h_mll_tight[h_name] = new TH1D("h_"+h_name+"_mll_tight", h_name+"_mll_tight", NbinsEff, &xbins_eff[0]);
	  h_met_loose[h_name] = new TH1D("h_"+h_name+"_met_loose", h_name+"_met_loose", NbinsEff, &xbins_eff[0]);
	  h_met_tight[h_name] = new TH1D("h_"+h_name+"_met_tight", h_name+"_met_tight", NbinsEff, &xbins_eff[0]);
	  // Histograms for fake rates
	  h_pt3_loose[h_name] = new TH1D("h_"+h_name+"_ptl3_loose", h_name+"_ptl3_loose", NbinsEff, &xbins_eff[0]);
	  h_pt3_tight[h_name] = new TH1D("h_"+h_name+"_ptl3_tight", h_name+"_ptl3_tight", NbinsEff, &xbins_eff[0]);	  
	}
	if(var==""){
	  h_phi1[h_name] = new TH1D("h_"+h_name+"_phi1", h_name+"_phi1", 50, -M_PI, M_PI);  
	  h_phi2[h_name] = new TH1D("h_"+h_name+"_phi2", h_name+"_phi2", 50, -M_PI, M_PI);  
	  h_eta1[h_name] = new TH1D("h_"+h_name+"_eta1", h_name+"_eta1", 50, -3, 3);  
	  h_eta2[h_name] = new TH1D("h_"+h_name+"_eta2", h_name+"_eta2", 50, -3, 3);  
	  h_dphi[h_name] = new TH1D("h_"+h_name+"_dphi", h_name+"_dphi", 25, 0, M_PI);  
	  h_mll_low[h_name] = new TH1D("h_"+h_name+"_mll_low", h_name+"_mll_low", 110, 10, 120);
	  h_met_lin[h_name] = new TH1D("h_"+h_name+"_met_lin", h_name+"_met_lin", 200, 0, 2000);
	  h_met_phi[h_name] = new TH1D("h_"+h_name+"_met_phi", h_name+"_met_phi", 50, -M_PI, M_PI);  
	  h_met_sig_rel[h_name] = new TH1D("h_"+h_name+"_met_sig_rel", h_name+"_met_sig_rel", 50, 0, 50);        
	  h_met_ht[h_name] = new TH1D("h_"+h_name+"_met_ht", h_name+"_met_ht", 150, 0, 1.5);        
	  h_met_res[h_name] = new TH1D("h_"+h_name+"_met_res", h_name+"_met_res", 200, 0, 200);
	  h_met_sig_log[h_name] = new TH1D("h_"+h_name+"_met_sig_log", h_name+"_met_sig_log", 120, &xbins_metsig[0]);        
	  h_met_soft[h_name] = new TH1D("h_"+h_name+"_met_soft", h_name+"_met_soft", 120, &xbins_pt[0]);
	  h_met_muon[h_name] = new TH1D("h_"+h_name+"_met_muon", h_name+"_met_muon", 120, &xbins_pt[0]);
	  h_met_elec[h_name] = new TH1D("h_"+h_name+"_met_elec", h_name+"_met_elec", 120, &xbins_pt[0]);
	  h_met_jet[h_name] = new TH1D("h_"+h_name+"_met_jet", h_name+"_met_jet", 120, &xbins_pt[0]);
	  h_dphi_rel[h_name] = new TH1D("h_"+h_name+"_dphi_rel", h_name+"_dphi_rel", 25, 0, M_PI);  
	  h_ptll[h_name] = new TH1D("h_"+h_name+"_ptll", h_name+"_ptll", 600, 0, 3000);       
	  h_mt2[h_name] = new TH1D("h_"+h_name+"_mt2", h_name+"_mt2", 100, 0, 500);
	  h_bjet_pt[h_name] = new TH1D("h_"+h_name+"_bjet_pt", h_name+"_bjet_pt", 120, &xbins_pt[0]);  
	  h_bjet_eta[h_name] = new TH1D("h_"+h_name+"_bjet_eta", h_name+"_bjet_eta", 50, -3, 3);  
	  h_jet_pt[h_name] = new TH1D("h_"+h_name+"_jet_pt", h_name+"_jet_pt", 120, &xbins_pt[0]);  
	  h_jet_eta[h_name] = new TH1D("h_"+h_name+"_jet_eta", h_name+"_jet_eta", 50, -3, 3);  
	  h_nfjets[h_name] = new TH1D("h_"+h_name+"_nfjets", h_name+"_nfjets", 20, 0, 20);
	  h_ncjets[h_name] = new TH1D("h_"+h_name+"_ncjets", h_name+"_ncjets", 20, 0, 20);
	  h_njets[h_name] = new TH1D("h_"+h_name+"_njets", h_name+"_njets", 20, 0, 20);
	  h_nljets[h_name] = new TH1D("h_"+h_name+"_nljets", h_name+"_nljets", 10, 0, 10);
	  h_dR_ll[h_name] = new TH1D("h_"+h_name+"_dR_ll", h_name+"_dR_ll", 100, 0, 10);
	  h_dphi_ll[h_name] = new TH1D("h_"+h_name+"_dphi_ll", h_name+"_dphi_ll", 25, 0, M_PI);
	  h_mcw[h_name] = new TH1D("h_"+h_name+"_mcw", h_name+"_mcw", 400, &xbins_mcw[0]);
	  h_mll40[h_name] = new TH1D("h_"+h_name+"_mll40", h_name+"_mll40", Nbins_mll40, &xbins_mll40[0]);
	  h_mll50[h_name] = new TH1D("h_"+h_name+"_mll50", h_name+"_mll50", Nbins_mll50, &xbins_mll50[0]);
	  h_mll60[h_name] = new TH1D("h_"+h_name+"_mll60", h_name+"_mll60", Nbins_mll60, &xbins_mll60[0]);
	  // 2D histograms
	  /*
	  h_met_mll[h_name] = new TH2D("h_"+h_name+"_met_mll", h_name+"_met_mll", 120, &xbins_pt[0], 74, &xbins_mll[0]); 
	  h_metsig_mll[h_name] = new TH2D("h_"+h_name+"_metsig_mll", h_name+"_metsig_mll", 200, &xbins_lin[0], 74, &xbins_mll[0]); 
	  h_met_metsig[h_name] = new TH2D("h_"+h_name+"_met_metsig", h_name+"_met_metsig", 200, 0, 2000, 50, 0, 50); 
	  h_met_metrel[h_name] = new TH2D("h_"+h_name+"_met_metrel", h_name+"_met_metrel", 120, &xbins_pt[0], 120, &xbins_pt[0]); 
	  h_mll_mcw[h_name] = new TH2D("h_"+h_name+"_mll_mcw", h_name+"_mll_mcw", 74, &xbins_mll[0], 400, &xbins_mcw[0]);
	  h_dphi_dphirel[h_name] = new TH2D("h_"+h_name+"_dphi_dphirel", h_name+"_dphi_dphirel", 25, 0, M_PI, 25, 0, M_PI); 
	  */ 
	} 
      }
    }
  }

  
  if(isMC){
    h_bornMass["no_cuts"] = new TH1D("h_no_cuts_bornMass", "no_cuts_bornMass", 74, &xbins_mll[0]);    
    if(doTruth){ outfile << "DSID    "<< "Name                                            "  << "Cross section     " << "SOW (tot)   " << "SOW (bin 1)    " << "SOW (bin 2)    " << "SOW (bin 3)    " << endl; } 
  } 
    
  if(doSyst && !isRecast){ makeTree = 1; }
  if(makeTree){
    tree = new TTree("tree", "tree"); 
    tree->Branch("mll", &mll);
    tree->Branch("pt1", &pt_lep1);
    tree->Branch("pt2", &pt_lep2);
    tree->Branch("wgt", &wgt);
    tree->Branch("event", &eventID);
    
    tree_MUON_SCALE__1up=tree->CloneTree(0); 
    tree_MUON_SCALE__1up->SetName("tree_MUON_SCALE__1up");     

    tree_MUON_EFF_RECO_SYS__1up=tree->CloneTree(0); 
    tree_MUON_EFF_RECO_SYS__1up->SetName("tree_MUON_EFF_RECO_SYS__1up");     

  }

}

void EventSelector::SlaveBegin(TTree * /*tree*/){}

Bool_t EventSelector::Process(Long64_t entry){


  fReader.SetLocalEntry(entry);
  if(!doCalibSyst){
    fReader_nom.SetLocalEntry(entry); 
  }
  if(doSFSyst){
    fReader_sys.SetLocalEntry(entry); 
  }
  
  //For recast, the sample cross section and filter efficiency will typically not be in LPXKFactorTool,
  //but it's also not needed in order to set a cross section limit in the statistical analysis. We can
  //just use a dummy cross section to avoid division by zero in the acceptance*efficiency calculation.
  if (isRecast && (*xsec == 0.0 || *geneff == 0.0)) {
    *xsec = 1.0;
    *geneff = 1.0;
  }

  //if(*run!=284484){return kTRUE;} // For cutflow comparison

  if(doSyst == 0 && *systName!=""){return kTRUE;} 
  //if(*systName!=""){return kTRUE;} 
  
  nevents++; eventID = *event;  
  if(nevents%1000000 == 0){cout << nevents/1000000 << " million events processed" << endl; } 

  //if(nevents>100){return kTRUE;} 
  if(doDebug && nevents>100000){return kTRUE;} 
  if(doDebug){ cout << "Inside process" << endl; } 
  
  TString this_syst=""; 
  if(*systName == ""){this_syst = "";} 
  else{ this_syst = "_"+*systName; }

  if( isData ){

    DSID = *run; 
    if(prev_DSID == 0){ prev_DSID = *run; sample_nevents=0;}
    prev_DSID = DSID; 

    TObjArray *path = (TString(((TChain*)(EventSelector::fChain))->GetFile()->GetName())).Tokenize(".");
    period = ((TObjString *)(path->At(4)))->String();
    TString file_nr = ((TObjString *)(path->At(9)))->String();

    final_name = period+file_nr;
    delete path;

  } 
  else{
    DSID = *run; 
    if(prev_DSID == 0){ prev_DSID = *run; } 
    if( DSID != prev_DSID ){
      if(doCutflow==1){PrintCutflow(prev_DSID);}
      sample_nevents=0;
      if(doTruth){
	outfile << scientific <<  "        "  << s_mc_x_pu << "        "  << sw_bin1 << "        "  << sw_bin2 << "        "  << sw_bin3 << endl; 
      }
      WriteToFile(Form("%d", prev_DSID), dataset, final_name); 
      s_mc_x_pu = 0; s_mc = 0; 
      sw_bin1 = 0; sw_bin2 = 0; sw_bin3 = 0; 
      isMM = 0; isEE = 0; 
    } 
    prev_DSID = DSID; 
    
    TObjArray *path = (TString(((TChain*)(EventSelector::fChain))->GetFile()->GetName())).Tokenize(".");
    name_1 = ((TObjString *)(path->At(5)))->String();
    TString file_nr = ((TObjString *)(path->At(9)))->String();
    string name_2(name_1);
    name_2.erase(name_2.end()-10, name_2.end()); 
    if(isAFII){ final_name = TString(name_2)+"_AFII"+file_nr; } 
    else{ final_name = TString(name_2)+file_nr; }
    delete path;

    isInclusive_Sherpa = (std::find(std::begin(Incl_Sherpa), std::end(Incl_Sherpa), DSID) != std::end(Incl_Sherpa));
    if(isInclusive_Sherpa && *bornMass/1000.>100){ return kTRUE; } // For inclusive Zee/Zmuu Sherpa samples: only keep events with mll<100 GeV. 

    isInclusive_Sh2211 = (std::find(std::begin(Incl_Sh2211), std::end(Incl_Sh2211), DSID) != std::end(Incl_Sh2211));
    if(isInclusive_Sh2211 && *bornMass/1000.>120){ return kTRUE; } // For inclusive Sherpa 2.2.11 samples: only keep events with mll<120 GeV. 

    isInclusive_Powheg = (std::find(std::begin(Incl_Powheg), std::end(Incl_Powheg), DSID) != std::end(Incl_Powheg));
    if(isInclusive_Powheg && *bornMass>120){ return kTRUE; } // For inclusive Zee/Zmuu Powheg samples: only keep events with mll<120 GeV. 

    isTTbar = (std::find(std::begin(TTbar_samples), std::end(TTbar_samples), DSID) != std::end(TTbar_samples));
    isSTincl = (std::find(std::begin(STincl_samples), std::end(STincl_samples), DSID) != std::end(STincl_samples));
    isSTdilep = (std::find(std::begin(STdilep_samples), std::end(STdilep_samples), DSID) != std::end(STdilep_samples));
    if(isTTbar || isSTincl || isSTdilep){ isTop = 1; } 
    isDiboson = (std::find(std::begin(Diboson_samples), std::end(Diboson_samples), DSID) != std::end(Diboson_samples));
    isZee = (std::find(std::begin(Zee_samples), std::end(Zee_samples), DSID) != std::end(Zee_samples));
    if(isZee || isDiboson){ isWB = 1; } 
    isSh2211 = (std::find(std::begin(Sh2211_samples), std::end(Sh2211_samples), DSID) != std::end(Sh2211_samples));
    isSh221 = (std::find(std::begin(Sh221_samples), std::end(Sh221_samples), DSID) != std::end(Sh221_samples));

    //if(DSID==410472 && *ttbarMass/1000.>1100.0 && *systName==""){ return kTRUE; } 
    //if(DSID==410472 && *ttbarGenFiltMET/1000.>200 && *systName=="" && !isAFII){return kTRUE;} 
    //if(DSID==410472 && *ttbarTruthHT/1000.>600 && *systName=="" && !isAFII){return kTRUE;}
    
    // Change weight indices for ST samples, set PDF_alphaS indices
    if(sample_nevents==0){
      
      TString file_name = TString(((TChain*)(EventSelector::fChain))->GetFile()->GetName());
      TFile* this_file = new TFile(file_name);  
      TH1* MCweights = (TH1*)this_file->Get("histoMCEventWeightSys");
      delete this_file;
      //cout << "Nominal MC weight: " << *mconly_weight << endl; 
      for(Int_t b = 1; b<=MCweights->GetNbinsX(); b++){
	TString this_weight = MCweights->GetXaxis()->GetBinLabel(b);
	//cout << this_weight << endl; 
	//if(this_weight.Contains("PDF260000")){cout << this_weight << ", at index " << b-1 << " has value " << mconly_weights[b] << endl;}
	if(isSh2211){
	  //cout << "Nominal MC weight: " << *mconly_weight << endl; 
	  if(std::find(std::begin(Sh2211_variations), std::end(Sh2211_variations), this_weight) != std::end(Sh2211_variations)){
	    weight_indices[this_weight] = b-1; 
	    //cout << "Weight " << this_weight << " at index " << b << " has value " << mconly_weights[b] << endl; 
	  }
	}
	if(isTop){
	  if(std::find(std::begin(Top_variations), std::end(Top_variations), this_weight.Strip(TString::kBoth,' ')) != std::end(Top_variations)){
	    weight_indices[this_weight.Strip(TString::kBoth,' ')] = b-1; 
	    //cout << "Weight " << this_weight << " at index " << b << " has value " << mconly_weights[b] << endl; 
	  }
	}
      }
    }
  }
  sample_nevents++; 
  //if(nevents>100){return kTRUE;} 

  /*
  if(*systName==""){
    sow_nom+=(*mconly_weight);
    sow_nloew+=(*NLO_EW_corr_MULTIASSEW);
  }
  */ 

  //return kTRUE; 
  
  if(isMC){ yr = *year; } 
  if(isData){ 
    if(dataset=="data15"){yr=2015;} 
    if(dataset=="data16"){yr=2016;} 
    if(dataset=="data17"){yr=2017;} 
    if(dataset=="data18"){yr=2018;} 
  } 

  //===================//
  // Truth level stuff //
  //===================//
  
  if(isMC){
    // Born-mass histogram 
    Float_t wgt_truth = (*mconly_weight)*(*xsec)*(*geneff)*(*kF_weight)*nb2fb;
    h_bornMass["no_cuts"]->Fill(*bornMass/1000., wgt_truth); // Divide born mass by 1000 for Sherpa, but not for Powheg
  }

  if(doTruth==1 && isMC==1){

    if(sample_nevents == 1){ 
      outfile << prev_DSID << "  " << final_name << "    " << *xsec*1E3*(*geneff); 
    }

    
    // Total sum of weights for signals
    if(*systName == "") {
      s_mc_x_pu += *pu_weight*(*mconly_weight);
      s_mc += *mconly_weight;
    }


    //All the below is specific for the benchmark signal samples and not relevant for recast.
    //Setting fiducial limits in recast will probably not be necessary. If we wanted to do that,
    //we would need to move away from the "truthMET_darkMatter" variables and use "normal" truthMET
    //instead. In that case, we would need a reliable way to propagate the channel information from
    //the recast workflow to correctly set the "isEE" and "isMM". That should be easy enough, but
    //as long as we don't set fiducial limits in recast, it's not necessary.
    if (!isRecast) {
      
      // Sum of weights for signals in fiducial regions 
      if(name_1.Contains("_ee_")){isEE = 1;}
      if(name_1.Contains("_mumu_")){isMM = 1;}

      // Find the two hardest truth leptons 
      Int_t lt1 = 0, lt2= 0, counter = 0; 
      Float_t pt1 = 0, pt2 = 0; 
      if(isEE){
	for(const auto & pt:truth_el_pt){
	  if(pt>pt1){ pt1 = pt; lt1 = counter;}
	  counter++; 
	}
	counter=0; 
	for(const auto & pt:truth_el_pt){
	  if(pt>pt2 && pt<pt1){ pt2 = pt; lt2 = counter; } 
	  counter++; 
	}
      }
      if(isMM){
	for(const auto & pt:truth_mu_pt){
	  if(pt>pt1){ pt1 = pt; lt1 = counter;}
	  counter++; 
	}
	counter=0; 
	for(const auto & pt:truth_mu_pt){
	  if(pt>pt2 && pt<pt1){ pt2 = pt; lt2 = counter; } 
	  counter++; 
	}
      }

      // Set truth 4-vectors 
      if(isEE){ 
	l1_truth.SetPtEtaPhiM(truth_el_pt[lt1]/1000., truth_el_eta[lt1], truth_el_phi[lt1], m_e);  
	l2_truth.SetPtEtaPhiM(truth_el_pt[lt2]/1000., truth_el_eta[lt2], truth_el_phi[lt2], m_e);  
      }
      if(isMM){
	l1_truth.SetPtEtaPhiM(truth_mu_pt[lt1]/1000., truth_mu_eta[lt1], truth_mu_phi[lt1], m_u);  
	l2_truth.SetPtEtaPhiM(truth_mu_pt[lt2]/1000., truth_mu_eta[lt2], truth_mu_phi[lt2], m_u);  
      }

      // Calculate truth kinematic variables 
      Int_t passed_truth_pt = 0; 
      if(isEE){ if(l1_truth.Pt()>25 && l2_truth.Pt()>25){ passed_truth_pt = 1; } }
      if(isMM){ if(l1_truth.Pt()>27 && l2_truth.Pt()>20){ passed_truth_pt = 1; } }

      mll_truth = (l1_truth+l2_truth).M();  
      dphi_truth = fabs( *truthMET_darkMatter_phi - (l1_truth+l2_truth).Phi() ); 

      met_truth = *truthMET_darkMatter_et/1000;
      if(fabs(l1_truth.Phi()-*truthMET_darkMatter_phi)<fabs(l2_truth.Phi()-*truthMET_darkMatter_phi)){ dphi_rel_truth = fabs(l1_truth.Phi()-*truthMET_darkMatter_phi); } 
      else{ dphi_rel_truth = fabs(l2_truth.Phi()-*truthMET_darkMatter_phi); }

      if(dphi_rel_truth<M_PI/2.0){ met_rel_truth = met_truth*sin(dphi_rel_truth); }
      else{ met_rel_truth = met_truth; }

      // Fiducial cuts
      if(*systName == "") {
	if(mll_truth>120 && dphi_truth>2.5 && passed_truth_pt==1){
	  if(met_rel_truth>50 && met_rel_truth<100){sw_bin1 += *pu_weight*(*mconly_weight);}
	  if(met_rel_truth>100 && met_rel_truth<150){sw_bin2 += *pu_weight*(*mconly_weight);}
	  if(met_rel_truth>150){sw_bin3 += *pu_weight*(*mconly_weight);}
	}
      }
    }
  }

  
  
  //==================================//
  // Triggers, isolation and cleaning //
  //==================================//

  /*
  if(yr==2015){ 
    if( *trigger_HLT_2e12_lhloose_L12EM10VH ){ el_trig = 1; n_trig_e++; }
    if( *trigger_HLT_mu26_imedium || *trigger_HLT_mu50 ){ mu_trig = 1; n_trig_u++;}
  }
  if(yr==2016){ 
    if( *trigger_HLT_2e17_lhvloose_nod0 ){ el_trig = 1; n_trig_e++; }
    if( *trigger_HLT_mu26_ivarmedium || *trigger_HLT_mu50 ){ mu_trig = 1; n_trig_u++;}
  }
  if(yr==2017){
    if( *trigger_HLT_2e24_lhvloose_nod0 ){el_trig = 1; n_trig_e++;}
    if((isData && (*run<326834 || *run>328393)) || isMC ){ // (isMC && *systName=="" && doSyst && (*randomRunNumber<326834 || *randomRunNumber>328393)) ){
      if( *trigger_HLT_2e17_lhvloose_nod0_L12EM15VHI ){el_trig = 1; n_trig_e++;}
    }  
    if( *trigger_HLT_mu26_ivarmedium || *trigger_HLT_mu50 ){ mu_trig = 1; n_trig_u++;}
  }
  if(yr==2018){
    if( *trigger_HLT_2e24_lhvloose_nod0 || *trigger_HLT_2e17_lhvloose_nod0_L12EM15VHI ){el_trig = 1; n_trig_e++;}
    if( *trigger_HLT_mu26_ivarmedium || *trigger_HLT_mu50 ){ mu_trig = 1; n_trig_u++;}
  }
  */

  Int_t ee_trig = *pass_ee_trig, uu_trig = *pass_uu_trig, e_trig = *pass_e_trig, u_trig = *pass_u_trig;

  Int_t mu_trig = uu_trig, el_trig = ee_trig; 
  
  Int_t pass_l_trig = 0, pass_ll_trig = 0;
  if(ee_trig || uu_trig){ pass_ll_trig = 1; } 
  if( u_trig){ pass_l_trig = 1; } // e_trig ||
  
  if( pass_ll_trig == 0 && pass_l_trig == 0 ){ return kTRUE; } 

  if(*jetCleaning_eventClean == 0){ return kTRUE; } 
  if(doCutflow==1){
    if(mu_trig==1){ n_jetclean_u++;} 
    if(el_trig==1){ n_jetclean_e++;} 
  }

  if(doDebug){ cout << "Done trigger" << endl; } 
  
  Int_t n_loose_mu_2utrig = 0; vector<Int_t> loose_mu_2utrig = {}; 
  Int_t n_loose_mu_1utrig = 0; vector<Int_t> loose_mu_1utrig = {}; 
  Int_t n_mu_bad = 0, n_mu = 0; 
  for(const auto & pt:mu_pt){ n_mu++; } 

  for(Int_t i = 0; i<n_mu; i++){
    if(mu_passTTVA[i]){
      if(mu_trigmatched_2u[i]){ n_loose_mu_2utrig++; loose_mu_2utrig.push_back(i); }
      if(mu_trigmatched_1u[i]){ n_loose_mu_1utrig++; loose_mu_1utrig.push_back(i); }
    }
    if(mu_isBad[i]){n_mu_bad++; } 
  }

  Int_t n_loose_el_notrig = 0; vector<Int_t> loose_el_notrig = {};
  Int_t n_loose_el_2etrig = 0; vector<Int_t> loose_el_2etrig = {};
  Int_t n_el = 0; 
  for(const auto & pt:el_pt){ n_el++; } 

  for(Int_t i = 0; i<n_el; i++){
    if(el_passTTVA[i]){
      n_loose_el_notrig++; loose_el_notrig.push_back(i);
      if(el_trigmatched_2e[i]){ n_loose_el_2etrig++; loose_el_2etrig.push_back(i); }
    }
  }

  Int_t is2loose = 0;
  if( (n_loose_mu_2utrig+n_loose_el_2etrig)==2 || (n_loose_el_notrig+n_loose_mu_1utrig)==2 ){ is2loose = 1; } // Check if the event has exactly two loose leptons 
  
  Int_t lep1=-999, lep2=-999, lep3=-999;
  dileptons = ""; 
  if(is2loose){ 
    if(n_loose_mu_2utrig == 2){ 
      if(mu_trig==0){ return kTRUE; } 
      lep1 = loose_mu_2utrig[0]; lep2 = loose_mu_2utrig[1];
      dileptons = "uu"; n_loose_u++;
    } 
    else if(n_loose_el_2etrig == 2){ 
      if(el_trig==0){ return kTRUE; } 
      lep1 = loose_el_2etrig[0]; lep2 = loose_el_2etrig[1];
      dileptons = "ee";  n_loose_e++; 
    }
    else if(n_loose_el_notrig==1 && n_loose_mu_1utrig == 1){
      if(mu_trig==0){ return kTRUE; } 
      lep1 = loose_el_notrig[0]; lep2 = loose_mu_1utrig[0]; 
      dileptons = "eu"; 
    } 
  }

  if(doDebug){ cout << "Done loose selection" << endl; } 
  
  /*
  if( n_loose_el==2 && n_loose_mu_f ==1 ){
    if(el_trig==0){ return kTRUE; } 
    dileptons = "eeu"; 
    lep1 = loose_el[0]; lep2 = loose_el[1]; lep3 = loose_mu_f[0];    
  }
  if( n_loose_mu==2 && n_loose_el==1 ){
    if(mu_trig==0){ return kTRUE; } 
    dileptons = "uue"; 
    lep1 = loose_mu[0]; lep2 = loose_mu[1]; lep3 = loose_el[0];    
  }
  */
  
  if(dileptons==""){ return kTRUE; } 

  // Bad muon veto 
  //if(*n_mu_baseline_bad!=0){ return kTRUE; n_mubad++;} 
  if(n_mu_bad!=0){ return kTRUE; n_mubad++;} 

  //Check whether the leptons pass the Tight selection (as defined in the Matrix Method)
  if (dileptons == "ee") {    
    tight1 = el_passIso[lep1] && el_passLHID[lep1];
    tight2 = el_passIso[lep2] && el_passLHID[lep2];
  }
  if (dileptons == "uu") {    
    tight1 = mu_passIso[lep1];
    tight2 = mu_passIso[lep2];
  }
  if (dileptons == "eu") {    
    tight1 = el_passIso[lep1] && el_passLHID[lep1];
    tight2 = mu_passIso[lep2];
  }
  if (dileptons == "eeu"){    
    tight1 = el_passIso[lep1] && el_passLHID[lep1];
    tight2 = el_passIso[lep2] && el_passLHID[lep2];
    tight3 = mu_passIso[lep3];
  }
  if (dileptons == "uue") {    
    tight1 = mu_passIso[lep1];
    tight2 = mu_passIso[lep2];
    tight3 = el_passIso[lep3] && el_passLHID[lep3];
  }

  if(doDebug){ cout << "Done tight selection" << endl; } 

  //============//
  // Kinematics //
  //============//

  Int_t isOS = 0, isTrigMatched = 0;  
  if(dileptons == "ee"){ 
    l1.SetPtEtaPhiM(el_pt[lep1]/1000., el_eta[lep1], el_phi[lep1], m_e);  
    l2.SetPtEtaPhiM(el_pt[lep2]/1000., el_eta[lep2], el_phi[lep2], m_e);  
    if(el_charge[lep1]!=el_charge[lep2]){ isOS = 1; } 
    //if(el_trigmatched_2e[lep1] && el_trigmatched_2e[lep2]){ isTrigMatched = 1; } 
  } 
  if(dileptons == "uu"){
    l1.SetPtEtaPhiM(mu_pt[lep1]/1000., mu_eta[lep1], mu_phi[lep1], m_u);  
    l2.SetPtEtaPhiM(mu_pt[lep2]/1000., mu_eta[lep2], mu_phi[lep2], m_u);  
    if(mu_charge[lep1]!=mu_charge[lep2]){ isOS = 1; } 
    //if(mu_trigmatched_2u[lep1] && mu_trigmatched_2u[lep2]){ isTrigMatched = 1; } 
  } 
  if(dileptons == "eu"){ 
    l1.SetPtEtaPhiM(el_pt[lep1]/1000., el_eta[lep1], el_phi[lep1], m_e);  
    l2.SetPtEtaPhiM(mu_pt[lep2]/1000., mu_eta[lep2], mu_phi[lep2], m_u);  
    if(el_charge[lep1]!=mu_charge[lep2]){ isOS = 1; } 
  }
  if(dileptons == "eeu"){ 
    l1.SetPtEtaPhiM(el_pt[lep1]/1000., el_eta[lep1], el_phi[lep1], m_e);  
    l2.SetPtEtaPhiM(el_pt[lep2]/1000., el_eta[lep2], el_phi[lep2], m_e);  
    l3.SetPtEtaPhiM(mu_pt[lep3]/1000., mu_eta[lep3], mu_phi[lep3], m_u);  
    if(el_charge[lep1]!=el_charge[lep2]){ isOS = 1; } 
  } 
  if(dileptons == "uue"){
    l1.SetPtEtaPhiM(mu_pt[lep1]/1000., mu_eta[lep1], mu_phi[lep1], m_u);  
    l2.SetPtEtaPhiM(mu_pt[lep2]/1000., mu_eta[lep2], mu_phi[lep2], m_u);  
    l3.SetPtEtaPhiM(el_pt[lep3]/1000., el_eta[lep3], el_phi[lep3], m_e);  
    if(mu_charge[lep1]!=mu_charge[lep2]){ isOS = 1; } 
  } 

  ll = l1+l2; 
  mll = ll.M(); 
  met = *met_tst_et/1000.; 
  met_phi = *met_tst_phi; 
  met_sig = *met_tst_significance;
  if(!doSyst){
    met_elec = *met_eleterm_et/1000.; met_jet = *met_jetterm_et/1000.; met_muon = *met_muonterm_et/1000.; met_soft = *met_softerm_tst_et/1000.;
  }
  
  ptll = ll.Pt(); 
  dphi = fabs( met_phi - (l1+l2).Phi() ); 
  dphi_ll = fabs( l1.Phi()-l2.Phi() ); 
  dR_ll = l1.DeltaR(l2); 
  ht = *met_tst_sumet/1000.;
  met_ht = met/ht; 

  pt_lep1 = l1.Pt(); pt_lep2 = l2.Pt(); 
  
  if(fabs(l1.Phi()-met_phi)<fabs(l2.Phi()-met_phi)){ dphi_rel = fabs(l1.Phi()-met_phi); } 
  else{ dphi_rel = fabs(l2.Phi()-met_phi); } 

  if(dphi_rel<M_PI/2.0){ met_rel = met*sin(dphi_rel); } 
  else{ met_rel = met; }

  met_res = met/met_sig;  
  met_sig_rel = met_rel/met_res; 
  
  TLorentzVector MET;
  MET.SetPtEtaPhiM(met, 0.0, met_phi, 0.0);

  ComputeMT2 calcMT2 = ComputeMT2(l1, l2, MET);
  Float_t mt2 = calcMT2.Compute();
  Float_t mtl1 = (l1+MET).Mt();   
  Float_t mtl2 = (l2+MET).Mt();   
  
  Int_t n_bjet77 = 0, n_bjet85=0; 
  vector<Float_t> dRlj = {};
  vector<Int_t> cjets = {}; 
  TLorentzVector thisjet; 
  njets = 0; ncjets = 0; nfjets = 0; nljets = 0; nbjets = 0;   
  Int_t n_jets = 0; // sizeof(jet_pt)/sizeof(jet_pt[0]); 
  for(const auto & pt:jet_pt){ n_jets++; } 

  for(Int_t j=0; j<n_jets; j++){ 
    njets++; 
    thisjet.SetPtEtaPhiE(jet_pt[j]/1000., jet_eta[j], jet_phi[j], jet_pt[j]/1000.); 
    if(fabs(jet_eta[j])<2.5){ 
      ncjets++; 
      cjets.push_back(j);
      if(jet_DL1r_score[j]>2.195){n_bjet77++;}
      if(jet_isbjet[j]==1 && jet_cleaning[j]==2){ n_bjet85++; nbjets++; }  
      if(jet_isbjet[j]==0){ nljets++;}
      //if(jet_DL1r_score[j]>0.665){   } 
      //if(jet_DL1r_score[j]<0.665){nljets++;} 
    }
    if(fabs(jet_eta[j])>2.5){ nfjets++; } 
    dRlj.push_back(l1.DeltaR(thisjet)); 
    dRlj.push_back(l2.DeltaR(thisjet)); 
  }

  TLorentzVector j1, j2;  
  Float_t mjj = 0; 
  if( nljets == 2 ){
    j1.SetPtEtaPhiE(jet_pt[0]/1000., jet_eta[0], jet_phi[0], jet_pt[0]/1000.);     
    j2.SetPtEtaPhiE(jet_pt[1]/1000., jet_eta[1], jet_phi[1], jet_pt[1]/1000.);     
    mjj = (j1+j2).M(); 
  }

  Float_t minDRlj = -1; 
  if(njets>0){ minDRlj = *std::min_element(std::begin(dRlj), std::end(dRlj)); }

  if(doDebug){ cout << "Done kinematics" << endl; } 
  
  //=================//
  // Final selection //
  //=================//

  if(dileptons=="ee" || dileptons=="eeu"){
    if(l1.Pt() < 25 || l2.Pt() < 25 ){return kTRUE;}
    passed_pt30 = 0; 
    if(l1.Pt() > 30 && l1.Pt() > 30 ){passed_pt30=1;}
    n_pt_e++;
    if( fabs(el_cl_etaBE2[lep1])<1.52 && fabs(el_cl_etaBE2[lep1])>1.37 ){return kTRUE;} 
    if( fabs(el_cl_etaBE2[lep2])<1.52 && fabs(el_cl_etaBE2[lep2])>1.37 ){return kTRUE;} 
    n_eta_e++; 
  }
  if(dileptons=="uu" || dileptons=="uue"){
    if(l1.Pt() < 25 || l2.Pt() < 25 ){return kTRUE;}
    passed_pt30 = 0; 
    if(l1.Pt() > 30 && l1.Pt() > 30 ){passed_pt30=1;}
    n_pt_u++;  
  }
  if(dileptons=="eu"){
    if(l1.Pt() < 25 || l2.Pt() < 25){return kTRUE;}
    if( fabs(el_cl_etaBE2[lep1])<1.52 && fabs(el_cl_etaBE2[lep1])>1.37 ){return kTRUE;} 
  }
  if(dileptons == "eeu"){ 
    if(l1.Pt() < 30 || l2.Pt() < 30 ){return kTRUE;}
    if(l3.Pt() < 20){ return kTRUE; } 
  }
  if(dileptons == "uue"){
    if(l1.Pt() < 30 || l2.Pt() < 30 ){return kTRUE;}
    if(l3.Pt() < 25){ return kTRUE; } 
    if( fabs(el_cl_etaBE2[lep3])<1.52 && fabs(el_cl_etaBE2[lep3])>1.37 ){return kTRUE;} 
  }

  if(mll < 10){ return kTRUE; } 

  if(doDebug){ cout << "Done pre-selection" << endl; } 
  
  passed_channels = {}; isTreeChannel=0; 

  if(dileptons=="ee" && mll>70){passed_channels.push_back("ee_incl");} 
  if(dileptons=="uu" && mll>70){passed_channels.push_back("uu_incl");} 

  if((dileptons=="uu" || dileptons=="ee") && isOS && pass_ll_trig && mll>70){ // && isTrigMatched 
    if(nbjets==0 && met_sig>1.0){ passed_channels.push_back(dileptons+"_presel"); } 
    passed_channels.push_back(dileptons+"_incl_OS"); n_mll70_e++;
    if(tight1 && tight2) n_mll70_e_TT++;
    if(mll>70 && mll<110){ passed_channels.push_back(dileptons+"_Zpeak"); }
    if(mll>110 && mll<180){ passed_channels.push_back(dileptons+"_incl_sb"); }
    if(mll<110 && nbjets==0){
      if(mll<90 && met_sig>10.0){ passed_channels.push_back(dileptons+"_CR_db_METsig"); } 
      if(mll>90 && met_sig>8.0){ passed_channels.push_back(dileptons+"_VR_db_METsig"); }
    }
    if(mll>110 && mll<180 && nbjets==0){
      passed_channels.push_back(dileptons+"_CR_Z_low_pre");
      passed_channels.push_back(dileptons+"_VR_Z_low_pre");
      if(dphi>2.5){ passed_channels.push_back(dileptons+"_CR_Z_dphi"); }
      if(dphi>2.5){ passed_channels.push_back(dileptons+"_VR_Z_dphi"); }
      if(met_rel>20 && met_rel<50){ passed_channels.push_back(dileptons+"_CR_Z_low"); }
      if(met_rel>50 && met_rel<80){ passed_channels.push_back(dileptons+"_VR_Z_low"); }
    }
    if(nbjets>0){ 
      if(mll>110 && mll<180){
	passed_channels.push_back(dileptons+"_CR_top_pre");
	if(met_rel>50){ passed_channels.push_back(dileptons+"_CR_top"); }
      }
      if(mll>180){
	passed_channels.push_back(dileptons+"_VR_top_pre");
	if(met_rel>50){ passed_channels.push_back(dileptons+"_VR_top"); }
      } 
    }
    if(mll>180){
      passed_channels.push_back(dileptons+"_incl_high"); 
      if(dphi>2.5){ passed_channels.push_back(dileptons+"_incl_high_dphi25"); }
      if(nljets==0){ passed_channels.push_back(dileptons+"_incl_high_0j"); }
      if(nljets>0){ passed_channels.push_back(dileptons+"_incl_high_nj"); } 
      if(nbjets==0){ passed_channels.push_back(dileptons+"_incl_high_0b"); }
      if(nbjets>0){ passed_channels.push_back(dileptons+"_incl_high_nb"); } 
      if(met_rel<50){
	passed_channels.push_back(dileptons+"_lowmet_incl"); 
	if(dphi>2.5){ passed_channels.push_back(dileptons+"_lowmet_dphi25"); }
	if(nljets==0){ passed_channels.push_back(dileptons+"_lowmet_0j"); }
	if(nljets>0){ passed_channels.push_back(dileptons+"_lowmet_nj"); } 
      }
      // Inclusive MET rel. bins
      if(met_rel>50 && met_rel<100){ passed_channels.push_back(dileptons+"_SR_bin1_METrel_incl"); }
      if(met_rel>100 && met_rel<150){ passed_channels.push_back(dileptons+"_SR_bin2_METrel_incl"); }
      if(met_rel>150){ passed_channels.push_back(dileptons+"_SR_bin3_METrel_incl"); }
      if(n_bjet77==0){passed_channels.push_back(dileptons+"_bv77");}
      if(nbjets == 0){
	passed_channels.push_back(dileptons+"_CR_Z_pre");
	passed_channels.push_back(dileptons+"_VR_Z_pre");
	if(met_rel<25 && nljets==0){ passed_channels.push_back(dileptons+"_CR_Z_0j"); }
	if(met_rel>10 && met_rel<30){ passed_channels.push_back(dileptons+"_CR_Z"); }
	if(met_rel>30 && met_rel<50){ passed_channels.push_back(dileptons+"_VR_Z"); }
	if(met_sig>1 && met_sig<3){ passed_channels.push_back(dileptons+"_CR_Z_METsig"); }
	if(met_sig>3 && met_sig<5){ passed_channels.push_back(dileptons+"_VR_Z_METsig"); }
	passed_channels.push_back(dileptons+"_bv85");
	// MET rel. bins with dphi cut
	if(dphi>2.5){
	  if(met_rel>50 && met_rel<100){ passed_channels.push_back(dileptons+"_SR_bin1_METrel_dphi"); }
	  if(met_rel>100 && met_rel<150){ passed_channels.push_back(dileptons+"_SR_bin2_METrel_dphi"); }
	  if(met_rel>150){ passed_channels.push_back(dileptons+"_SR_bin3_METrel_dphi"); }
	}
	// MET rel. bins with jet veto
	if(nljets==0){
	  if(met_rel>50 && met_rel<100){ passed_channels.push_back(dileptons+"_SR_bin1_METrel_0j"); }
	  if(met_rel>100 && met_rel<150){ passed_channels.push_back(dileptons+"_SR_bin2_METrel_0j"); }
	  if(met_rel>150){ passed_channels.push_back(dileptons+"_SR_bin3_METrel_0j"); }
	}
	if(dphi>2.5){ passed_channels.push_back(dileptons+"_bv85_dphi25"); }
	if(met_sig>10 && mll>685){passed_channels.push_back(dileptons+"_SR_high"); }
	// MET sig. bins
	if(met_sig>5 && met_sig<8){ passed_channels.push_back(dileptons+"_SR_bin1_METsig"); }
	if(met_sig>8 && met_sig<12){ passed_channels.push_back(dileptons+"_SR_bin2_METsig"); }
	if(met_sig>12){ passed_channels.push_back(dileptons+"_SR_bin3_METsig"); }
	// MET sig. bins
	if(met_sig>5 && met_sig<10){ passed_channels.push_back(dileptons+"_SR_bin1_METsig_v2"); }
	if(met_sig>10 && met_sig<15){ passed_channels.push_back(dileptons+"_SR_bin2_METsig_v2"); }
	if(met_sig>15){ passed_channels.push_back(dileptons+"_SR_bin3_METsig_v2"); }
	// MET rel. bins
	if(met_rel>50 && met_rel<100){ passed_channels.push_back(dileptons+"_SR_bin1_METrel"); }
	if(met_rel>100 && met_rel<150){ passed_channels.push_back(dileptons+"_SR_bin2_METrel"); }
	if(met_rel>150){ passed_channels.push_back(dileptons+"_SR_bin3_METrel"); }
	// MET bins
	if(met>50 && met<100){ passed_channels.push_back(dileptons+"_SR_bin1_MET"); } // if(mll>750 && mll<1000){n_SR1_500++;} if(mll>1000 && mll<1500){n_SR1_1000++;} if(mll>1500){n_SR1_1500++;} }
	if(met>100 && met<150){ passed_channels.push_back(dileptons+"_SR_bin2_MET"); } //if(mll>750 && mll<1000){n_SR2_500++;} if(mll>1000 && mll<1500){n_SR2_1000++;} if(mll>1500){n_SR2_1500++;} }
	if(met>150){ passed_channels.push_back(dileptons+"_SR_bin3_MET"); } // if(mll>750 && mll<1000){n_SR3_500++;} if(mll>1000 && mll<1500){n_SR3_1000++;} if(mll>1500){n_SR3_1500++;}}
      }
      /*
      for(const auto cut:all_METcuts){
	if(met>atof(cut)){ passed_channels.push_back(dileptons+"_METcut"+cut); 
	  if(n_bjet77==0){passed_channels.push_back(dileptons+"_METcut"+cut+"_bv77");}
	  if(nbjets==0){passed_channels.push_back(dileptons+"_METcut"+cut+"_bv85");
	    if(dphi>2.5){passed_channels.push_back(dileptons+"_METcut"+cut+"_bv85_dphi25");} 
	  }
	}
      }
      */ 
      for(const auto cut:all_METrelcuts){
	if(met_rel>atof(cut)){ 
	  passed_channels.push_back(dileptons+"_METrelcut"+cut); 
	  if(nbjets==0){
	    passed_channels.push_back(dileptons+"_METrelcut"+cut+"_bv85"); 
	    if(dphi>2.5){passed_channels.push_back(dileptons+"_METrelcut"+cut+"_bv85_dphi25");}
	  } 
	}
      }
      /*
      for(const auto cut:all_METsigcuts){
	if(met_sig>atof(cut)){ 
	  passed_channels.push_back(dileptons+"_METsigcut"+cut); 
	  if(nbjets==0){
	    passed_channels.push_back(dileptons+"_METsigcut"+cut+"_bv85");  
	    if(dphi>2.0){passed_channels.push_back(dileptons+"_METsigcut"+cut+"_bv85_dphi20");}
	    if(dphi>2.2){passed_channels.push_back(dileptons+"_METsigcut"+cut+"_bv85_dphi22");}
	    if(dphi>2.4){passed_channels.push_back(dileptons+"_METsigcut"+cut+"_bv85_dphi24");}
	    if(dphi>2.5){passed_channels.push_back(dileptons+"_METsigcut"+cut+"_bv85_dphi25");}
	    if(dphi>2.6){passed_channels.push_back(dileptons+"_METsigcut"+cut+"_bv85_dphi26");}
	    if(dphi>2.8){passed_channels.push_back(dileptons+"_METsigcut"+cut+"_bv85_dphi28");}
	    if(dphi>3.0){passed_channels.push_back(dileptons+"_METsigcut"+cut+"_bv85_dphi30");}
	  } 
	}
      }
      */ 
    }
  }

  
  if(doDebug){ cout << "Done same-flavour selections" << endl; } 
  
  // Same charge selection (fake CR) 
  if( !isOS && (dileptons=="ee" || dileptons=="uu")){
    passed_channels.push_back(dileptons+"_incl_SS");
    if(mll>180){
      passed_channels.push_back(dileptons+"_VR_fakes"); 
      if(nljets>0){ 
	passed_channels.push_back(dileptons+"_VR_fakes_1j"); 
      }
      if(met_rel>50){ 
	passed_channels.push_back(dileptons+"_VR_fakes_METrel"); 
      }
      if(met_sig>5){ 
	passed_channels.push_back(dileptons+"_VR_fakes_METsig"); 
      }
    }
  }

  if(doDebug){ cout << "Done fakes VR selections" << endl; } 

  // Different flavour selections 
  if(dileptons == "eu" && mll>110 && isOS && pass_l_trig){
    passed_channels.push_back("eu_incl");
    if(mll<180 && nbjets==0){
      if(met_sig>5 && met_sig<8){passed_channels.push_back("eu_CR_top_bin1");}
      if(met_sig>8 && met_sig<12){passed_channels.push_back("eu_CR_top_bin2");}
      if(met_sig>12){passed_channels.push_back("eu_CR_top_bin3");}
    }
    if(mll>180){
      passed_channels.push_back("eu_incl_high");
      if(met_sig>5 && met_sig<8){passed_channels.push_back("eu_CR_top_METsig");}
      if(met_sig>8){passed_channels.push_back("eu_VR_top_METsig");}
      if(nbjets==0){
	if(met_sig>5 && met_sig<8){passed_channels.push_back("eu_CR_top_METsig_0b");}
	if(met_sig>8){passed_channels.push_back("eu_VR_top_METsig_0b");}
	//if(met_rel>50 && met_rel<100){passed_channels.push_back("eu_CR_top_0b");}
	//if(met_rel>100){passed_channels.push_back("eu_VR_top_0b");}
      }
    }
  }

  if(doDebug){ cout << "Done DF selections" << endl; } 
  
  // Three-lepton selections 
  if(dileptons == "eeu" && mll>70 && mll<180 && isOS){
    passed_channels.push_back("eeu_CR_fakes");
  }
  if(dileptons == "uue" && mll>70 && mll<120 && isOS){
    passed_channels.push_back("uue_CR_fakes");
  }

  // Low-mass selections 
  if(mll < 120 && isOS){ 
    if(dileptons=="ee"){ passed_channels.push_back("ee_low_wZ"); }
    if(dileptons=="uu"){ passed_channels.push_back("uu_low_wZ"); }
  }
  if(mll<60 && isOS && (dileptons=="ee" || dileptons=="uu")){
    passed_channels.push_back(dileptons+"_low"); 
    if(nbjets>0 && met_rel>50){ passed_channels.push_back(dileptons+"_VR_top_low"); }
    if(nbjets == 0){ passed_channels.push_back(dileptons+"_bv85_low");
      if(dphi>2.5){ passed_channels.push_back(dileptons+"_bv85_dphi25_low");
	if(met_sig>10){ passed_channels.push_back(dileptons+"_SR_low");}
      }
    }
    for(const auto cut:all_METrelcuts){
      if(met_rel>atof(cut)){ 
	passed_channels.push_back(dileptons+"_METrelcut"+cut+"_low"); 
	if(nbjets==0){
	  passed_channels.push_back(dileptons+"_METrelcut"+cut+"_bv85_low");  
	  if(dphi>2.5){passed_channels.push_back(dileptons+"_METrelcut"+cut+"_bv85_dphi25_low");}
	} 
      }
    }
  }

  if(doDebug){ cout << "Done low-mass selections" << endl; } 
  
  // Truth matching 
  if(isMC && doFakes){
    Int_t only_real_leptons = 1; 
    if(dileptons=="ee"){ 
      if (el_truth_IFFtype[lep1] != 2 || el_truth_IFFtype[lep2] != 2){ only_real_leptons = 0;  }
    }
    if(dileptons=="uu"){ 
      if (mu_truth_IFFtype[lep1] != 4 || mu_truth_IFFtype[lep2] != 4){ only_real_leptons = 0; }
    }
    if(dileptons=="eu"){ 
      if (el_truth_IFFtype[lep1] != 2 || mu_truth_IFFtype[lep2] != 4){ only_real_leptons = 0; }
    }
    if(dileptons=="eeu"){ 
      if (el_truth_IFFtype[lep1] != 2 || el_truth_IFFtype[lep2] != 2 || mu_truth_IFFtype[lep3] != 4){ only_real_leptons = 0;  }
    }
    if(dileptons=="uue"){ 
      if (mu_truth_IFFtype[lep1] != 4 || mu_truth_IFFtype[lep2] != 4 || el_truth_IFFtype[lep3] != 2){ only_real_leptons = 0; }
    }

    if(only_real_leptons == 1){ 
      vector<TString> chn_tmp = passed_channels; 
      for(const auto  & chn:chn_tmp){
	passed_channels.push_back(chn+"_real"); 
      }
    }

  }

  if(doDebug){ cout << "Done truth matching" << endl; } 
  
  //==============// 
  // Event weight //
  //==============//

  map<TString, Float_t> lep_SF, cid_SF, jet_SF; 
  weightVariations = {}; 
  if(this_syst == "" && isMC && doSFSyst){ 
    //weightVariations = SFvariations; 
    weightVariations.insert(weightVariations.begin(), SFvariations.begin(), SFvariations.end());
    weightVariations.insert(weightVariations.end(), Top_variations.begin(), Top_variations.end());
    weightVariations.insert(weightVariations.end(), Sh2211_variations.begin(), Sh2211_variations.end());
    if(doSyst){ 
      weightVariations.push_back("pu_weight_PRW_DATASF__1up"); weightVariations.push_back("pu_weight_PRW_DATASF__1down");
      weightVariations.push_back("Top_Mass");
      //weightVariations.push_back("NLO_EW_ASSEW"); weightVariations.push_back("NLO_EW_MULTIASSEW"); weightVariations.push_back("NLO_EW_EXPEW");
      //weightVariations.push_back("PDF_alphaS_0117"); weightVariations.push_back("PDF_alphaS_0119");
    }
    lep_SF= GetLepSFVariations(entry); cid_SF= GetCidSFVariations(entry); jet_SF= GetJetSFVariations(entry); 
  } 

  if (isMC){weightVariations.push_back("");} 
  if (isData){weightVariations = variations;}
 
  for(const auto weight_sys:weightVariations){ 
    if(isData){

      //Standard weight of 1 for data
      wgt = 1.0; 
      //But do not fill standard histograms unless both are tight
      if(!doLoose){
	if ( !(tight1 && tight2) ){ wgt = 0.0; }
      }
      // Special treatment for trilepton regions
      if(dileptons=="eeu" || dileptons=="uue"){
	if(doLoose){ if ( !(tight1 && tight2) ){ wgt = 0.0; }  }
	if(!doLoose){ if ( !(tight1 && tight2 && tight3) ){ wgt = 0.0; }  }
      }

      if(doFakes){ 
	//
	//Calculate also additional "fake weight" for QCD estimate
	//
	
	//First, get the real and fake efficiencies for the two leptons
	Int_t L1=0, L2=0; 
	if(dileptons=="ee"){ L1 = 1; L2 = 1; }
	if(dileptons=="uu"){ L1 = 2; L2 = 2; } 
	if(dileptons=="eu"){ L1 = 1; L2 = 2; }

	if(weight_sys.Contains("up")){
	  f1 = MMeffs.fakeEff1D_up(l1.Pt(), L1, yr);
	  f2 = MMeffs.fakeEff1D_up(l2.Pt(), L2, yr);
	}
	else if(weight_sys.Contains("down")){
	  f1 = MMeffs.fakeEff1D_dw(l1.Pt(), L1, yr);
	  f2 = MMeffs.fakeEff1D_dw(l2.Pt(), L2, yr);
	}
	else{
	  f1 = MMeffs.fakeEff1D(l1.Pt(), L1, yr);
	  f2 = MMeffs.fakeEff1D(l2.Pt(), L2, yr);
	}
	r1 = MMeffs.realEff2D(l1.Pt(), l1.Eta(), L1, yr);
	r2 = MMeffs.realEff2D(l2.Pt(), l2.Eta(), L2, yr);
	
	//Problem with negative fake efficiencies affects just a very few events due to ambiguity in the crack region
	if (f1 < 0.0) f1 = 0.0;
	if (f2 < 0.0) f2 = 0.0;

	//Set the relevant "event counts" for the different combinations of "exclusive Loose" (i.e. "not Tight") and Tight
	NTT = 0.0; NTl = 0.0; NlT = 0.0; Nll = 0.0;
	if (tight1 && tight2)
	  NTT = 1.0;
	if (tight1 && !tight2)
	  NTl = 1.0;
	if (!tight1 && tight2)
	  NlT = 1.0;
	if (!tight1 && !tight2)
	  Nll = 1.0;

	//For one specific event, there should be only one combination
	if (NTT + NTl + NlT + Nll != 1.0) cout << "ERROR: inconsistency in NXX for MM\n";

	//Get the weights for the Matrix Method - these are essentially the inverted matrix expressions
	//Contributions are obtained independently for ...
	Double_t RF_TT = MM.N4_RF_TT(r1,f1,r2,f2,NTT,NTl,NlT,Nll); //... Real+Fake (RF)
	Double_t FR_TT = MM.N4_FR_TT(r1,f1,r2,f2,NTT,NTl,NlT,Nll); //... Fake+Real (FR)
	Double_t FF_TT = MM.N4_FF_TT(r1,f1,r2,f2,NTT,NTl,NlT,Nll); //... Fake+Fake (FF)

	//Can also be useful to get the same for the "inclusive Loose" selection, but this is not used at the moment
	Double_t RF_LL = MM.N4_RF_LL(r1,f1,r2,f2,NTT,NTl,NlT,Nll);
	Double_t FR_LL = MM.N4_FR_LL(r1,f1,r2,f2,NTT,NTl,NlT,Nll);
	Double_t FF_LL = MM.N4_FF_LL(r1,f1,r2,f2,NTT,NTl,NlT,Nll);

	//This is the final "Fake background weight", i.e. every combination that includes a fake lepton
	//Weights with label "TT" means Tight+Tight, i.e. the "signal region selection"
	if(doLoose){ 
	  wgt_fakes = RF_LL + FR_LL + FF_LL; 
	  //Now set the relevant weight for histograms filling
	  if (weight_sys == "RF") wgt = RF_LL + FR_LL;
	  if (weight_sys == "FF") wgt = FF_LL;
	  if (weight_sys.Contains("Fakes")) wgt = wgt_fakes;
	} 
	else{ 
	  wgt_fakes = RF_TT + FR_TT + FF_TT; 
	  //Now set the relevant weight for histograms filling
	  if (weight_sys == "RF") wgt = RF_TT + FR_TT;
	  if (weight_sys == "FF") wgt = FF_TT;
	  if (weight_sys.Contains("Fakes")) wgt = wgt_fakes; 
	  /*
	  if (dileptons == "uu" && weight_sys == "Fakes"){
	    cout << tight1 << ", " << tight2 << endl; 
	    cout << wgt_fakes << endl;
	    cout << "f1 : " << f1 << endl; 
	    cout << "f2 : " << f2 << endl; 
	    cout << "r1 : " << r1 << endl; 
	    cout << "r2 : " << r2 << endl; 
	  } 
	  */ 
	} 
      }

      LLwgt_noSF = 1.0;
      wgt_lsf_lep1Loose = 1.0;
      wgt_lsf_lep2Loose = 1.0;
      wgt_lsf_lep1Tight = 1.0;
      wgt_lsf_lep2Tight = 1.0;
      wgt_lsf_lep3Loose = 1.0; 
      wgt_lsf_lep3Tight = 1.0; 

    } 
    else{ 
      // MC generator weight
      Int_t isTopVar = (std::find(std::begin(Top_variations), std::end(Top_variations), weight_sys) != std::end(Top_variations));
      Int_t isSh2211Var = (std::find(std::begin(Sh2211_variations), std::end(Sh2211_variations), weight_sys) != std::end(Sh2211_variations));
      if(isTopVar && isTop){ wgt_mc = mconly_weights[weight_indices[weight_sys]]; } 
      else if(isSh2211Var && isSh2211){ wgt_mc = mconly_weights[weight_indices[weight_sys]]; } 
      else{ wgt_mc = *mconly_weight; } 
      // Pileup weight
      if(weight_sys=="pu_weight_PRW_DATASF__1up"){ wgt_pu = *pu_weight_PRW_DATASF__1up; } 
      else if(weight_sys=="pu_weight_PRW_DATASF__1down"){ wgt_pu = *pu_weight_PRW_DATASF__1down; } 
      else{ wgt_pu = *pu_weight; } 
      // k-factor
      if(isSh2211){ wgt_kf = 1.0; } // 0.9751; ignore k-factor for high mass Sh2211 samples
      else{ wgt_kf = *kF_weight; } 
      // ttbar reweighting 
      wgt_ttbar = *ttbarNNLOweight;
      // NLO EW correction
      if(isSh2211 && doSyst){
	if(weight_sys=="MUR1_MUF1_PDF303200_ASSEW"){ wgt_nlo_ew = (*NLO_EW_corr_ASSEW)/(*mconly_weight); }
	else if(weight_sys=="MUR1_MUF1_PDF303200_MULTIASSEW"){ wgt_nlo_ew = (*NLO_EW_corr_MULTIASSEW)/(*mconly_weight); }
	else if(weight_sys=="MUR1_MUF1_PDF303200_EXPASSEW"){ wgt_nlo_ew = (*NLO_EW_corr_EXPASSEW)/(*mconly_weight); }
	else{  wgt_nlo_ew = 1.0; }
      }
      else{ wgt_nlo_ew = 1.0; }
      //wgt_nlo_ew = 1.0; 
      // jet weight
      if(weight_sys.Contains("_JvtEff")){ wgt_jet = jet_SF[weight_sys]; }
      else{ wgt_jet = *jvt_signal_jets_SF; }
      // forward jet weight
      if(weight_sys.Contains("_fJvtEff")){ wgt_jet = jet_SF[weight_sys]; }
      else{ wgt_fjet = *fjvt_signal_jets_SF; }
      // b-jet weight
      if(weight_sys.Contains("FT_EFF")){ wgt_bjet = jet_SF[weight_sys]; }
      else{ wgt_bjet = *btag_signal_jets_SF; }
      // Cross section  
      xs = *xsec; 
      // Filter efficiency 
      g_eff = *geneff; 
      if( xs < 0 || g_eff < 0 ){ cout << "Error in cross section or filter efficiency!!!" << endl; } 
      // Total cross section weight 
      if( DSID == 410472 && weight_sys == "Top_Mass"){ wgt_xs = ( xs*wgt_kf +  0.02318 )*nb2fb*g_eff; }
      else{ wgt_xs = xs*wgt_kf*nb2fb*g_eff; } 
      // Lepton and trigger scale factor 
      if(dileptons.Contains("ee")){ // ee

	wgt_lsf_lep1Loose = el_SF_rec[lep1] * el_SF_idLooseAndBLayer[lep1];
	wgt_lsf_lep1Tight = el_SF_rec[lep1] * el_SF_id[lep1] * el_SF_iso[lep1];
	wgt_lsf_lep2Loose = el_SF_rec[lep2] * el_SF_idLooseAndBLayer[lep2];
	wgt_lsf_lep2Tight = el_SF_rec[lep2] * el_SF_id[lep2] * el_SF_iso[lep2];

	if(weight_sys.Contains("EL_EFF") && !weight_sys.Contains("ChargeID")){
	  wgt_lsf = lep_SF[weight_sys]; 
	}
	else{
	  wgt_lsf = *evsf_signal_nominal_EL; //*(*trig_ee_SF);;
	  //wgt_lsf = el_SF[lep1]*el_SF[lep2]*(*trig_ee_SF); 
	}
	
	if(weight_sys.Contains("ChargeID") || weight_sys.Contains("CHARGEID")){
	  wgt_lsf *= cid_SF[weight_sys];
	}
	else{
	  wgt_lsf *= el_SF_cid[lep1]; 
	  wgt_lsf *= el_SF_cid[lep2]; 
	}
	wgt_lsf *= *trig_ee_SF;
      }  
      if(dileptons.Contains("uu")){ // uu

	wgt_lsf_lep1Loose = mu_SF_rec[lep1]; 
	wgt_lsf_lep1Tight = mu_SF_rec[lep1]*mu_SF_iso[lep1]; 
	wgt_lsf_lep2Loose = mu_SF_rec[lep2]; 
	wgt_lsf_lep2Tight = mu_SF_rec[lep2]*mu_SF_iso[lep2]; 

	if(weight_sys.Contains("MUON_EFF")){
	  wgt_lsf = lep_SF[weight_sys]; 
	}
	else{
	  wgt_lsf = *evsf_signal_nominal_MU; //*(*trig_uu_SF); //(*trig_1u_SF);   
	  //wgt_lsf = mu_SF[lep1]*mu_SF[lep2]*(*trig_uu_SF); 
	}
	wgt_lsf *= *trig_uu_SF;  
      } 
      if(dileptons == "eu"){
	wgt_lsf = el_SF[lep1]*mu_SF[lep2]*(*trig_1u_SF)*el_SF_cid[lep1];   
      }
      if(dileptons == "eeu"){ 
	wgt_lsf *= mu_SF[lep3]; 
	wgt_lsf_lep3Loose = mu_SF_rec[lep3]; 
	wgt_lsf_lep3Tight = mu_SF_rec[lep3]*mu_SF_iso[lep3]; 
      }  
      if(dileptons == "uue"){
	wgt_lsf*= el_SF[lep3]; 
	wgt_lsf_lep3Loose = el_SF_rec[lep3] * el_SF_idLooseAndBLayer[lep3];
	wgt_lsf_lep3Tight = el_SF_rec[lep3] * el_SF_id[lep3] * el_SF_iso[lep3];
      }

      // Total weight 
      LLwgt_noSF = wgt_mc*wgt_pu*wgt_xs*wgt_ttbar;
      if(dileptons=="eeu" || dileptons=="uue"){ // For trilepton events 
	if(doLoose){ // Two tight and one (inclusive) loose lepton 
	  if ( !(tight1 && tight2) ){ wgt = 0.0; }
	  else{ 
	    wgt = LLwgt_noSF*wgt_lsf_lep1Tight*wgt_lsf_lep2Tight*wgt_lsf_lep3Loose;
	    if(dileptons=="uue"){ wgt *= el_SF_cid[lep3]; wgt *= (*trig_1u_SF);} 
	    if(dileptons=="eeu"){ wgt *= (*trig_ee_SF);} 
	  } 
	}
	if(!doLoose){ // Three tight leptons 
	  if ( !(tight1 && tight2 && tight3) ){ wgt = 0.0; }  
	  else{ wgt = LLwgt_noSF*wgt_lsf; } 
	}
      }
      else{ // For dilepton events 
	if(doLoose){ // Inclusive loose selection 
	  wgt = LLwgt_noSF*wgt_lsf_lep1Loose*wgt_lsf_lep2Loose;
	  if(dileptons=="ee"){ wgt *= el_SF_cid[lep1]; wgt *= el_SF_cid[lep2]; wgt *= (*trig_ee_SF); }
	  if(dileptons=="uu"){ wgt *= (*trig_1u_SF); } 
	}
	else{ // Tight selection
	  if ( !(tight1 && tight2) ){ wgt = 0.0; } 
	  else{ wgt = wgt_mc*wgt_pu*wgt_xs*wgt_lsf*wgt_ttbar*wgt_nlo_ew*wgt_bjet*wgt_jet*wgt_fjet; } 
	  /*
	  if(*event==169773933){
	    //cout << *event << endl;
	    if(*systName=="" && weight_sys==""){
	      cout << "Nominal!!!" << endl; 
	    }
	    if(*systName==""){ cout << weight_sys << endl; }
	    else{ cout << *systName << endl; } 
	    cout << wgt << endl; 
	  }
	  */ 
	}
      }
    }

    if(doDebug){ cout << "Done weights" << endl; } 
    
    // Weight sums 
    if(doCutflow == 1){
      if(dileptons == "uu" && mll>70){
	s_mc_u += wgt_mc; 
	s_kf_u += wgt_kf;
	s_pu_u += wgt_pu; 
	s_tt_u += wgt_ttbar; 
	s_xs_u += wgt_xs; 
	s_lsf_u += wgt_lsf;  
	s_trig_u += wgt_tsf; 
	s_wgt_u += wgt; 
      } 
      if(dileptons == "ee" && mll>70){
	s_mc_e += wgt_mc; 
	s_kf_e += wgt_kf;
	s_pu_e += wgt_pu; 
	s_tt_e += wgt_ttbar; 
	s_xs_e += wgt_xs; 
	s_lsf_e += wgt_lsf;  
	s_trig_e += wgt_tsf; 
	s_wgt_e += wgt; 
      } 
    }

    //=================//
    // Fill histograms //
    //=================//

    TString syst = ""; 
    if(weight_sys == ""){ syst = this_syst; } 
    else{ syst = "_"+weight_sys; } 

    for(const auto & chn:passed_channels){
      TString this_name = chn+syst; 
      Int_t isBlinded = 0; 
      //cout << this_name << endl; 
      if(chn.Contains("SR") || chn.Contains("bv") || chn.Contains("cut")){ isBlinded = 1; }  
      if(isData && isBlinded && weight_sys==""){ continue; } // Don't fill data histograms for blinded selections

      isSystChannel = (std::find(std::begin(syst_channels), std::end(syst_channels), chn) != std::end(syst_channels));
      if(!isSystChannel && syst!="" && doSyst){ continue; }

      /*
      if(chn.Contains("cut") && syst!=""){ continue; } 
      if(chn.Contains("bv85") && syst!=""){ continue; } 
      if((chn.Contains("SR_bin") && !chn.Contains("METrel")) && syst!=""){ continue; } 
      */ 
      //cout << this_name << endl; 
      
      if(chn.Contains("cut")){
	if(chn.Contains("low")){ h_mll_low[this_name]->Fill(mll, wgt); } 
	else{ h_mll[this_name]->Fill(mll, wgt); } 
      }
      else{
	//if(this_name.Contains("uu_incl_SS")){	cout << nevents << " : " << this_name << " : " << wgt  << endl; }
	h_pt1[this_name]->Fill(l1.Pt(), wgt); 
	h_pt2[this_name]->Fill(l2.Pt(), wgt); 
	h_mll[this_name]->Fill(mll, wgt); 
	h_met[this_name]->Fill(met, wgt); 
	h_met_sig[this_name]->Fill(met_sig, wgt); 
	h_met_rel[this_name]->Fill(met_rel, wgt); 
	h_mll_lin[this_name]->Fill(mll, wgt); 
	h_nbjets[this_name]->Fill(nbjets, wgt); 
	if(doFakes && !doSyst){
	  h_pt_loose[this_name]->Fill(l1.Pt(), LLwgt_noSF*wgt_lsf_lep1Loose); 
	  h_pt_loose[this_name]->Fill(l2.Pt(), LLwgt_noSF*wgt_lsf_lep2Loose); 
	  h_ptEta_loose[this_name]->Fill(l1.Pt(), fabs(l1.Eta()), LLwgt_noSF*wgt_lsf_lep1Loose); 
	  h_ptEta_loose[this_name]->Fill(l2.Pt(), fabs(l2.Eta()), LLwgt_noSF*wgt_lsf_lep2Loose); 
	  h_mll_loose[this_name]->Fill(mll, LLwgt_noSF*wgt_lsf_lep1Loose); 
	  h_mll_loose[this_name]->Fill(mll, LLwgt_noSF*wgt_lsf_lep2Loose); 
	  h_met_loose[this_name]->Fill(met, LLwgt_noSF*wgt_lsf_lep1Loose); 
	  h_met_loose[this_name]->Fill(met, LLwgt_noSF*wgt_lsf_lep2Loose); 
	  if(tight1){ 
	    h_pt_tight[this_name]->Fill(l1.Pt(), LLwgt_noSF*wgt_lsf_lep1Tight); 
	    h_ptEta_tight[this_name]->Fill(l1.Pt(), fabs(l1.Eta()), LLwgt_noSF*wgt_lsf_lep1Tight);  
	    h_mll_tight[this_name]->Fill(mll, LLwgt_noSF*wgt_lsf_lep1Tight); 
	    h_met_tight[this_name]->Fill(met, LLwgt_noSF*wgt_lsf_lep1Tight); 
	  }
	  if(tight2){ 
	    h_pt_tight[this_name]->Fill(l2.Pt(), LLwgt_noSF*wgt_lsf_lep2Tight); 
	    h_ptEta_tight[this_name]->Fill(l2.Pt(), fabs(l2.Eta()), LLwgt_noSF*wgt_lsf_lep2Tight); 
	    h_mll_tight[this_name]->Fill(mll, LLwgt_noSF*wgt_lsf_lep2Tight); 
	    h_met_tight[this_name]->Fill(met, LLwgt_noSF*wgt_lsf_lep2Tight); 
	  }
	  if(chn.Contains("eeu") || chn.Contains("uue")){
	    if(tight1 && tight2){
	      h_pt3_loose[this_name]->Fill(l3.Pt(), LLwgt_noSF*wgt_lsf_lep3Loose); 
	      if(tight3){
		h_pt3_tight[this_name]->Fill(l3.Pt(), LLwgt_noSF*wgt_lsf_lep3Tight); 
	      }
	    }
	  }
	}
	if(syst == ""){
	  h_phi1[this_name]->Fill(l1.Phi(), wgt); 
	  h_phi2[this_name]->Fill(l2.Phi(), wgt); 
	  h_eta1[this_name]->Fill(l1.Eta(), wgt); 
	  h_eta2[this_name]->Fill(l2.Eta(), wgt); 
	  h_dphi[this_name]->Fill(dphi, wgt); 
	  h_mll_low[this_name]->Fill(mll, wgt); 
	  h_met_lin[this_name]->Fill(met, wgt); 
	  h_met_phi[this_name]->Fill(met_phi, wgt); 
	  h_met_sig_log[this_name]->Fill(met_sig, wgt); 
	  h_met_sig_rel[this_name]->Fill(met_sig_rel, wgt); 
	  h_met_ht[this_name]->Fill(met_ht, wgt); 
	  h_met_res[this_name]->Fill(met_res, wgt); 
	  h_met_soft[this_name]->Fill(met_soft, wgt); 
	  h_met_muon[this_name]->Fill(met_muon, wgt); 
	  h_met_elec[this_name]->Fill(met_elec, wgt); 
	  h_met_jet[this_name]->Fill(met_jet, wgt); 
	  h_dphi_rel[this_name]->Fill(dphi_rel, wgt); 
	  h_dR_ll[this_name]->Fill(dR_ll, wgt); 
	  h_dphi_ll[this_name]->Fill(dphi_ll, wgt); 
	  h_ptll[this_name]->Fill(ptll, wgt); 
	  h_mt2[this_name]->Fill(mt2, wgt);
	  h_ncjets[this_name]->Fill(ncjets, wgt); 
	  h_nfjets[this_name]->Fill(nfjets, wgt); 
	  h_njets[this_name]->Fill(njets, wgt); 
	  h_nljets[this_name]->Fill(nljets, wgt); 
	  h_mcw[this_name]->Fill(wgt_mc);
	  h_mll40[this_name]->Fill(mll,wgt);
	  h_mll50[this_name]->Fill(mll,wgt);
	  h_mll60[this_name]->Fill(mll,wgt);
	  /*
	  h_met_mll[this_name]->Fill(met, mll, wgt); 
	  h_metsig_mll[this_name]->Fill(met_sig, mll, wgt); 
	  h_met_metsig[this_name]->Fill(met, met_sig, wgt); 
	  h_met_metrel[this_name]->Fill(met, met_rel, wgt); 
	  h_mll_mcw[this_name]->Fill(mll, wgt_mc); 
	  h_dphi_dphirel[this_name]->Fill(dphi, dphi_rel, wgt); 
	  */ 
	}
	
      }
    }
    
    if(makeTree && isTreeChannel){
      if(weight_sys=="" && *systName==""){ tree->Fill(); } 
      if(*systName=="MUON_SCALE__1up"){ tree_MUON_SCALE__1up->Fill(); } 
      if(weight_sys=="MUON_EFF_RECO_SYS__1up"){ tree_MUON_EFF_RECO_SYS__1up->Fill(); } 
    } 
  }

  if(doDebug){ cout << "Done histogram filling. End of process!!" << endl; } 

  return kTRUE;
}

void EventSelector::SlaveTerminate(){}

void EventSelector::Terminate()
{

  if(doTruth){
    outfile <<  "        "  << s_mc_x_pu << "        "  << sw_bin1 << "        "  << sw_bin2 << "        "  << sw_bin3 << endl; 
    outfile.close();
  }

  if(doCutflow==1){PrintCutflow(DSID);} 
  if(isData){ WriteToFile(period, dataset, final_name); }
  else{ WriteToFile(Form("%d", DSID), dataset, final_name); } 
  cout << "Events processed: " << nevents << endl; 
  //cout << "Sum of nom. weights: " << sow_nom << endl; 
  //cout << "Sum of NLO EW weights: " << sow_nloew << endl; 
  //cout << "SOW sf: " << sow_nloew/sow_nom << endl; 

  //cout << "Nom. events" << nev_nom << endl; 
  //cout << "Syst. events" << nev_syst << endl; 
  /*
  cout << "Event SR 1, 750-1000 GeV: " << n_SR1_500 << endl; 
  cout << "Event SR 2, 750-1000 GeV: " << n_SR2_500 << endl; 
  cout << "Event SR 3, 750-1000 GeV: " << n_SR3_500 << endl; 
  cout << "Event SR 1, 1000-1500 GeV: " << n_SR1_1000 << endl; 
  cout << "Event SR 2, 1000-1500 GeV: " << n_SR2_1000 << endl; 
  cout << "Event SR 3, 1000-1500 GeV: " << n_SR3_1000 << endl; 
  cout << "Event SR 1, >1500 GeV: " << n_SR1_1500 << endl; 
  cout << "Event SR 2, >1500 GeV: " << n_SR2_1500 << endl; 
  cout << "Event SR 3, >1500 GeV: " << n_SR3_1500 << endl; 
  */ 
  //cout << "Minimum MET for events with METsig>5.: " << min_MET << endl; 

  // Write tree
  if(makeTree){
    TString this_infile = TString(((TChain*)(EventSelector::fChain))->GetFile()->GetName());
    TFile *f = new TFile(this_infile);
    TH1F * h1 = new TH1F();
    h1 = (TH1F*)f->Get("histoEventCount");
    f->Close(); delete f; 

    TString DSID_string = to_string(DSID); 
    TFile treefile("trees/"+dataset+"/"+DSID_string+"."+final_name+".root", "RECREATE");
    h1->Write(); 
    tree->Write();
    tree_MUON_SCALE__1up->Write();
    tree_MUON_EFF_RECO_SYS__1up->Write();
    treefile.Close(); 
    delete h1; 

    delete tree; delete tree_MUON_SCALE__1up; delete tree_MUON_EFF_RECO_SYS__1up; 
  }
}


void EventSelector::WriteToFile(TString fileid, TString data_type, TString name)
{
  
  // Make outfile   
  TString outputdir; 
  TString filename, filename_syst, filename_fakes, h_name; 
  if(fileid.Contains("period")){ 
    if(doLoose){ 
      filename = "hist."+data_type+"."+name+".loose.root"; 
      filename_fakes = "hist."+data_type+"."+name+".fakes_loose.root"; 
    } 
    else{ 
      filename = "hist."+data_type+"."+name+".root"; 
      filename_fakes = "hist."+data_type+"."+name+".fakes.root"; 
    } 
  } 
  else{ 
    if(doLoose){ 
      filename = "hist."+fileid+"."+name+".loose.root"; 
      filename_fakes = "hist."+fileid+"."+name+".real_loose.root"; 
    } 
    else{ 
      filename = "hist."+fileid+"."+name+".root"; 
      filename_fakes = "hist."+fileid+"."+name+".real.root"; 
    }
    if(doSyst){
      if(doFakes){ filename_syst = "hist."+fileid+"."+name+".syst_real.root"; }
      else{ filename_syst = "hist."+fileid+"."+name+".syst.root"; }
    }
  }

  if(isRecast){
    outputdir="Histograms";
  } 
  else{
    if(doSFSyst){ outputdir="/scratch/Histograms/SFSyst"; } 
    else if(doCalibSyst){ outputdir="/scratch/Histograms/CalibSyst"; } 
    else if(doFakes){
      if(isMC){ outputdir="/scratch/Histograms/Real"; }
      else{ outputdir="/scratch/Histograms"; } 
    }
    else{
      if(isMC){ outputdir="/scratch/Histograms/Nominal"; }
      else{ outputdir="/scratch/Histograms"; }
    }
  }

  TFile file(outputdir+"/"+data_type+"/"+fileid+"/"+filename, "RECREATE"); 
  
  // Write nominal histograms 
  for( const auto & chn:all_channels ){
    if(chn.Contains("real")){ continue; } 
    h_name = chn; 
    if(chn.Contains("cut")){
      if(chn.Contains("low")){ h_mll_low[h_name]->Write(); } 
      else{ h_mll[h_name]->Write(); } 
    } 
    else{ 
      h_pt1[h_name]->Write(); 
      h_pt2[h_name]->Write(); 
      h_eta1[h_name]->Write(); 
      h_eta2[h_name]->Write(); 
      h_mll[h_name]->Write(); 
      h_mll_low[h_name]->Write();
      h_mll_lin[h_name]->Write();
      h_met[h_name]->Write(); 
      h_met_sig[h_name]->Write(); 
      h_met_sig_log[h_name]->Write(); 
      h_phi1[h_name]->Write(); 
      h_phi2[h_name]->Write();
      h_met_lin[h_name]->Write(); 
      h_met_phi[h_name]->Write(); 
      h_met_sig_rel[h_name]->Write(); 
      h_met_ht[h_name]->Write(); 
      h_met_rel[h_name]->Write(); 
      h_met_res[h_name]->Write(); 
      h_met_soft[h_name]->Write(); 
      h_met_muon[h_name]->Write(); 
      h_met_elec[h_name]->Write(); 
      h_met_jet[h_name]->Write(); 
      h_dphi[h_name]->Write(); 
      h_dphi_rel[h_name]->Write(); 
      h_dR_ll[h_name]->Write(); 
      h_dphi_ll[h_name]->Write(); 
      h_ptll[h_name]->Write(); 
      h_mt2[h_name]->Write();
      h_njets[h_name]->Write();
      h_nbjets[h_name]->Write();
      h_nljets[h_name]->Write();
      h_ncjets[h_name]->Write();
      h_nfjets[h_name]->Write();
      h_mcw[h_name]->Write(); 
      h_mll40[h_name]->Write(); 
      h_mll50[h_name]->Write(); 
      h_mll60[h_name]->Write(); 
      /*
      h_met_mll[h_name]->Write(); 
      h_metsig_mll[h_name]->Write(); 
      h_met_metsig[h_name]->Write(); 
      h_met_metrel[h_name]->Write(); 
      h_mll_mcw[h_name]->Write(); 
      h_dphi_dphirel[h_name]->Write(); 
      */ 
      if(doFakes && !doSyst){
	h_pt_loose[h_name]->Write(); 
	h_pt_tight[h_name]->Write(); 
	h_pt3_loose[h_name]->Write(); 
	h_pt3_tight[h_name]->Write(); 
	h_ptEta_loose[h_name]->Write(); 
	h_ptEta_tight[h_name]->Write(); 
	h_mll_loose[h_name]->Write(); 
	h_mll_tight[h_name]->Write(); 
	h_met_loose[h_name]->Write(); 
	h_met_tight[h_name]->Write(); 
      }
    }
  }

  if(isMC==1){ 
    h_bornMass["no_cuts"]->Write(); 
  }

  file.Close(); 

  // Write fakes for data and "real-only" histograms for MC 
  if(doFakes && !doSyst){ 
    TFile file_fakes(outputdir+"/"+data_type+"/"+fileid+"/"+filename_fakes, "RECREATE"); 
    for( const auto & chn:all_channels ){
      for(const auto & var:variations ) {
	if (isData){
	  Int_t doDataFakes = 0;  
	  if(var!=""){doDataFakes = 1;} 
	  if(var=="" && (chn.Contains("SS") || chn.Contains("CR_fake"))){ doDataFakes = 1; } 
	  if(!doDataFakes){ continue;}
	  if(var!=""){ h_name = chn+"_"+var; } 
	  if(var==""){ h_name = chn; } 
	}  
	if(isMC){
	  if( var!="" || !chn.Contains("real")){ continue; }
	  h_name = chn; 
	} 
	if(chn.Contains("cut")){
	  if(chn.Contains("low")){ h_mll_low[h_name]->Write(); } 
	  else{ h_mll[h_name]->Write(); } 
	} 
	else{
	  h_pt1[h_name]->Write(); 
	  h_pt2[h_name]->Write(); 
	  h_mll[h_name]->Write();
	  h_met[h_name]->Write(); 
	  h_nbjets[h_name]->Write(); 
	  h_met_sig[h_name]->Write(); 
	  h_met_rel[h_name]->Write(); 
	  h_mll_lin[h_name]->Write();
	  h_pt_loose[h_name]->Write(); 
	  h_pt_tight[h_name]->Write(); 
	  h_ptEta_loose[h_name]->Write(); 
	  h_ptEta_tight[h_name]->Write(); 
	  h_pt3_loose[h_name]->Write(); 
	  h_pt3_tight[h_name]->Write(); 
	  h_mll_loose[h_name]->Write(); 
	  h_mll_tight[h_name]->Write(); 
	  h_met_loose[h_name]->Write(); 
	  h_met_tight[h_name]->Write(); 
	}
      }
    }
    file_fakes.Close(); 
  } 

  // Write systematics histograms 
  Int_t n_histograms = 0; 
  if(doSyst == 1){ 

    TFile file_syst(outputdir+"/"+data_type+"/"+fileid+"/"+filename_syst, "RECREATE"); 
    for( const auto & chn:all_channels ){
      isSystChannel = (std::find(std::begin(syst_channels), std::end(syst_channels), chn) != std::end(syst_channels));
      for(const auto & var:variations ) {
	if( var == "" ){ continue; } 
	if(!isSystChannel){ continue; }
	if(doFakes && !chn.Contains("real")){ continue; } 

	h_name = chn+"_"+var;
	//cout << h_name << endl; 
	
	if(chn.Contains("cut")){
	  if(chn.Contains("low")){ h_mll_low[h_name]->Write(); n_histograms++;} 
	  else{ h_mll[h_name]->Write(); n_histograms++;} 
	} 
	else{
	  h_pt1[h_name]->Write(); 
	  h_pt2[h_name]->Write(); 
	  h_mll[h_name]->Write();
	  h_met[h_name]->Write(); 
	  h_nbjets[h_name]->Write(); 
	  h_met_sig[h_name]->Write(); 
	  h_met_rel[h_name]->Write(); 
	  h_mll_lin[h_name]->Write();
	  n_histograms += 10; 
	} 
      }
    }
    file_syst.Close(); 

  }

  cout << "Number of syst. histograms: " << n_histograms << endl; 

  // Reset histograms
  for( const auto & chn:all_channels ){ 
    isSystChannel = (std::find(std::begin(syst_channels), std::end(syst_channels), chn) != std::end(syst_channels));
    for(const auto & var:variations ) {
      if(!isSystChannel && var!="" && doSyst){ continue; }
      if(var == ""){ h_name = chn; } 
      else{ h_name = chn+"_"+var; } 
      if(chn.Contains("cut")){
	if(chn.Contains("low")){ h_mll_low[h_name]->Reset(); } 
	else{ h_mll[h_name]->Reset(); } 
      } 
      else{
	h_pt1[h_name]->Reset(); 
	h_pt2[h_name]->Reset(); 
	h_mll[h_name]->Reset();
	h_mll_lin[h_name]->Reset();
	h_met[h_name]->Reset(); 
	h_met_sig[h_name]->Reset(); 
	h_met_rel[h_name]->Reset(); 
	h_nbjets[h_name]->Reset(); 
	if(doFakes && !doSyst){
	  h_pt_loose[h_name]->Reset(); 
	  h_pt_tight[h_name]->Reset(); 
	  h_pt3_loose[h_name]->Reset(); 
	  h_pt3_tight[h_name]->Reset(); 
	  h_ptEta_loose[h_name]->Reset(); 
	  h_ptEta_tight[h_name]->Reset(); 
	  h_mll_loose[h_name]->Reset(); 
	  h_mll_tight[h_name]->Reset(); 
	  h_met_loose[h_name]->Reset(); 
	  h_met_tight[h_name]->Reset(); 
	}
	if(var==""){
	  h_phi1[h_name]->Reset(); 
	  h_phi2[h_name]->Reset(); 
	  h_eta1[h_name]->Reset(); 
	  h_eta2[h_name]->Reset(); 
	  h_dphi[h_name]->Reset(); 
	  h_mll_low[h_name]->Reset();
	  h_met_lin[h_name]->Reset(); 
	  h_met_phi[h_name]->Reset(); 
	  h_met_sig_rel[h_name]->Reset(); 
	  h_met_ht[h_name]->Reset(); 
	  h_met_sig_log[h_name]->Reset(); 
	  h_met_res[h_name]->Reset(); 
	  h_met_soft[h_name]->Reset(); 
	  h_met_muon[h_name]->Reset(); 
	  h_met_elec[h_name]->Reset(); 
	  h_met_jet[h_name]->Reset(); 
	  h_dphi_rel[h_name]->Reset(); 
	  h_dR_ll[h_name]->Reset(); 
	  h_dphi_ll[h_name]->Reset(); 
	  h_ptll[h_name]->Reset(); 
	  h_mt2[h_name]->Reset(); 
	  h_ncjets[h_name]->Reset(); 
	  h_nfjets[h_name]->Reset(); 
	  h_njets[h_name]->Reset(); 
	  h_nljets[h_name]->Reset(); 
	  h_mcw[h_name]->Reset(); 
	  h_mll40[h_name]->Reset(); 
	  h_mll50[h_name]->Reset(); 
	  h_mll60[h_name]->Reset(); 
	  /*
	  h_met_mll[h_name]->Reset(); 
	  h_metsig_mll[h_name]->Reset(); 
	  h_met_metsig[h_name]->Reset(); 
	  h_met_metrel[h_name]->Reset(); 
	  h_mll_mcw[h_name]->Reset(); 
	  h_dphi_dphirel[h_name]->Reset(); 
	  */ 
	}
      }
    }
  }
  
  if(isMC==1){
    h_bornMass["no_cuts"]->Reset(); 
  }

  //delete h_kFactor_corr_ee;
  //delete h_kFactor_corr_uu; 
  
  cout << "Done with file: " << name << endl; 

  time_t t; // t passed as argument in function time()
  struct tm * tt; // decalring variable for localtime()
  time (&t); //passing argument to time()
  tt = localtime(&t);
  cout << "Time: "<< asctime(tt);  

}


void EventSelector::PrintCutflow(Int_t fileid){

  cout.precision(17); 
  cout << "===============================================" << endl; 
  cout << "CUTFLOW AND WEIGHT SUMS" << endl; 
  cout << "Run number / DSID: " << fileid << endl; 
  cout << "Total number of events: " << sample_nevents << endl; 
  cout << "==================" << endl; 
  cout << "MUON CHANNEL" << endl; 
  cout << "Passed muon triggers: " << n_trig_u << endl; 
  cout << "Jet cleaning: " << n_jetclean_u << endl; 
  cout << "Exactly two loose muons: " << n_loose_u << endl; 
  cout << "Bad muon veto: " << n_mubad << endl; 
  cout << "pT > 30 GeV: " << n_pt_u << endl; 
  cout << "mll > 70 GeV: " << n_mll70_u << endl; 
  cout << "mll > 70 GeV (Tight+Tight): " << n_mll70_u_TT << endl; 
  cout << "mll < 120 GeV: " << n_mll120_u << endl; 
  cout << "met > 100 GeV: " << n_met100_u << endl; 
  cout << "-----------------" << endl; 
  cout << "MC weights: " << s_mc_u << endl; 
  cout << "kFactors: " << s_kf_u << endl; 
  cout << "Pile-up: " << s_pu_u << endl; 
  cout << "TTbar weight: " << s_tt_u << endl; 
  cout << "XS weight: " << s_xs_u << endl; 
  cout << "Lepton SF: " << s_lsf_u << endl; 
  cout << "Trigger SF: " << s_trig_u << endl; 
  cout << "Combined: " << s_wgt_u << endl; 
  cout << "==================" << endl; 
  cout << "ELECTRON CHANNEL" << endl; 
  cout << "Passed electron triggers: " << n_trig_e << endl; 
  cout << "Jet cleaning: " << n_jetclean_e << endl; 
  cout << "Exactly two loose electrons: " << n_loose_e << endl; 
  cout << "pT > 30 GeV: " << n_pt_e << endl; 
  cout << "Eta crack veto: " << n_eta_e << endl; 
  cout << "mll > 70 GeV: " << n_mll70_e << endl; 
  cout << "mll > 70 GeV (Tight+Tight): " << n_mll70_e_TT << endl; 
  cout << "-----------------" << endl; 
  cout << "MC weights: " << s_mc_e << endl; 
  cout << "kFactors: " << s_kf_e << endl; 
  cout << "Pile-up: " << s_pu_e << endl; 
  cout << "TTbar weight: " << s_tt_e << endl; 
  cout << "XS weight: " << s_xs_e << endl; 
  cout << "Lepton SF: " << s_lsf_e << endl; 
  cout << "Trigger SF: " << s_trig_e << endl; 
  cout << "Combined: " << s_wgt_e << endl; 

  sample_nevents = 0; 
  n_trig_e = 0; n_jetclean_e = 0; n_twolep_e = 0; n_loose_e = 0; n_pt_e = 0; n_eta_e = 0; n_mll70_e = 0; n_mll70_e_TT = 0; 
  n_trig_u = 0; n_jetclean_u = 0; n_twolep_u = 0; n_loose_u = 0; n_mubad = 0; n_pt_u = 0; n_mll70_u = 0; n_mll70_u_TT = 0;
  s_mc_e = 0; s_kf_e = 0; s_pu_e = 0; s_lsf_e = 0; s_trig_e = 0; s_tt_e = 0; s_wgt_e = 0;     
  s_mc_u = 0; s_kf_u = 0; s_pu_u = 0; s_lsf_u = 0; s_trig_u = 0; s_tt_u = 0; s_wgt_u = 0;     

} 

vector<Float_t> EventSelector::GetLogBinning(Int_t nbins, Float_t xmin, Float_t xmax){

  Float_t logmin = log10(xmin);
  Float_t logmax = log10(xmax);
  Float_t logbinwidth = (logmax-logmin)/nbins;

  vector<Float_t> xbins;
  xbins.push_back(xmin);
  for(int i=1; i<nbins+1; i++){
    xbins.push_back( TMath::Power(10, (logmin + i*logbinwidth)) );
  }

  return xbins;
}

vector<Float_t> EventSelector::GetSRBinning(TString chn, Float_t xmin, Float_t xmax){
  
  vector<Float_t> xbins, xbins1, xbins2, xbins3; 

  if(chn=="ee"){
    xbins1 = GetLogBinning(40, xmin, 450);
    xbins2 = GetLogBinning(25, 450, xmax);
    xbins = GetLogBinning(50, 180, 1200);
  }  
  if(chn=="uu"){
    xbins1 = GetLogBinning(6, xmin, 235);
    xbins2 = GetLogBinning(24, 180, 600);
    xbins3 = GetLogBinning(4, 750, xmax);
    xbins = xbins2; //xbins.push_back(247);  
    //for(const auto & b:xbins2){
      //if(b==250){ continue; }
      //xbins.push_back(b); 
    //}
    xbins.push_back(638); xbins.push_back(685);  
    for(const auto & b:xbins3){
      //if(b==670){ continue; }
      xbins.push_back(b); 
    }
  }  

  // Overlow bins 
  xbins.push_back(1350); 
  xbins.push_back(1500); 
  xbins.push_back(1750); 
  xbins.push_back(2000);
  xbins.push_back(2500); 
  xbins.push_back(3000); 
  xbins.push_back(5000); 
  
  return xbins;
}


map<TString, Float_t> EventSelector::GetLepSFVariations(Long64_t entry){

  map<TString, Float_t> lep_SF; 

  lep_SF["MUON_EFF_BADMUON_SYS__1up"] =  *evsf_signal0_syst_MUON_EFF_BADMUON_SYS__1up;
  lep_SF["MUON_EFF_ISO_STAT__1up"] =  *evsf_signal0_syst_MUON_EFF_ISO_STAT__1up;
  lep_SF["MUON_EFF_ISO_SYS__1up"] =  *evsf_signal0_syst_MUON_EFF_ISO_SYS__1up;
  lep_SF["MUON_EFF_RECO_STAT__1up"] =  *evsf_signal0_syst_MUON_EFF_RECO_STAT__1up;
  lep_SF["MUON_EFF_RECO_SYS__1up"] = *evsf_signal0_syst_MUON_EFF_RECO_SYS__1up;
  lep_SF["MUON_EFF_TTVA_STAT__1up"] = *evsf_signal0_syst_MUON_EFF_TTVA_STAT__1up;
  lep_SF["MUON_EFF_TTVA_SYS__1up"] = *evsf_signal0_syst_MUON_EFF_TTVA_SYS__1up;
  //lep_SF["MUON_EFF_TrigStatUncertainty__1up"] = *evsf_signal0_syst_MUON_EFF_TrigStatUncertainty__1up;
  //lep_SF["MUON_EFF_TrigSystUncertainty__1up"] = *evsf_signal0_syst_MUON_EFF_TrigSystUncertainty__1up;

  lep_SF["MUON_EFF_BADMUON_SYS__1down"] =  *evsf_signal0_syst_MUON_EFF_BADMUON_SYS__1down;
  lep_SF["MUON_EFF_ISO_STAT__1down"] =  *evsf_signal0_syst_MUON_EFF_ISO_STAT__1down;
  lep_SF["MUON_EFF_ISO_SYS__1down"] =  *evsf_signal0_syst_MUON_EFF_ISO_SYS__1down;
  lep_SF["MUON_EFF_RECO_STAT__1down"] =  *evsf_signal0_syst_MUON_EFF_RECO_STAT__1down;
  lep_SF["MUON_EFF_RECO_SYS__1down"] = *evsf_signal0_syst_MUON_EFF_RECO_SYS__1down;
  lep_SF["MUON_EFF_TTVA_STAT__1down"] = *evsf_signal0_syst_MUON_EFF_TTVA_STAT__1down;
  lep_SF["MUON_EFF_TTVA_SYS__1down"] = *evsf_signal0_syst_MUON_EFF_TTVA_SYS__1down;

  lep_SF["EL_EFF_ID_CorrUncertaintyNP0__1down"] = *evsf_signal0_syst_EL_EFF_ID_CorrUncertaintyNP0__1down;
  lep_SF["EL_EFF_ID_CorrUncertaintyNP0__1up"] = *evsf_signal0_syst_EL_EFF_ID_CorrUncertaintyNP0__1up;
  lep_SF["EL_EFF_ID_CorrUncertaintyNP10__1down"] = *evsf_signal0_syst_EL_EFF_ID_CorrUncertaintyNP10__1down;
  lep_SF["EL_EFF_ID_CorrUncertaintyNP10__1up"] = *evsf_signal0_syst_EL_EFF_ID_CorrUncertaintyNP10__1up;
  lep_SF["EL_EFF_ID_CorrUncertaintyNP11__1down"] = *evsf_signal0_syst_EL_EFF_ID_CorrUncertaintyNP11__1down;
  lep_SF["EL_EFF_ID_CorrUncertaintyNP11__1up"] = *evsf_signal0_syst_EL_EFF_ID_CorrUncertaintyNP11__1up;
  lep_SF["EL_EFF_ID_CorrUncertaintyNP12__1down"] = *evsf_signal0_syst_EL_EFF_ID_CorrUncertaintyNP12__1down;
  lep_SF["EL_EFF_ID_CorrUncertaintyNP12__1up"] = *evsf_signal0_syst_EL_EFF_ID_CorrUncertaintyNP12__1up;
  lep_SF["EL_EFF_ID_CorrUncertaintyNP13__1down"] = *evsf_signal0_syst_EL_EFF_ID_CorrUncertaintyNP13__1down;
  lep_SF["EL_EFF_ID_CorrUncertaintyNP13__1up"] = *evsf_signal0_syst_EL_EFF_ID_CorrUncertaintyNP13__1up;
  lep_SF["EL_EFF_ID_CorrUncertaintyNP14__1down"] = *evsf_signal0_syst_EL_EFF_ID_CorrUncertaintyNP14__1down;
  lep_SF["EL_EFF_ID_CorrUncertaintyNP14__1up"] = *evsf_signal0_syst_EL_EFF_ID_CorrUncertaintyNP14__1up;
  lep_SF["EL_EFF_ID_CorrUncertaintyNP15__1down"] = *evsf_signal0_syst_EL_EFF_ID_CorrUncertaintyNP15__1down;
  lep_SF["EL_EFF_ID_CorrUncertaintyNP15__1up"] = *evsf_signal0_syst_EL_EFF_ID_CorrUncertaintyNP15__1up;
  lep_SF["EL_EFF_ID_CorrUncertaintyNP1__1down"] = *evsf_signal0_syst_EL_EFF_ID_CorrUncertaintyNP1__1down;
  lep_SF["EL_EFF_ID_CorrUncertaintyNP1__1up"] = *evsf_signal0_syst_EL_EFF_ID_CorrUncertaintyNP1__1up;
  lep_SF["EL_EFF_ID_CorrUncertaintyNP2__1down"] = *evsf_signal0_syst_EL_EFF_ID_CorrUncertaintyNP2__1down;
  lep_SF["EL_EFF_ID_CorrUncertaintyNP2__1up"] = *evsf_signal0_syst_EL_EFF_ID_CorrUncertaintyNP2__1up;
  lep_SF["EL_EFF_ID_CorrUncertaintyNP3__1down"] = *evsf_signal0_syst_EL_EFF_ID_CorrUncertaintyNP3__1down;
  lep_SF["EL_EFF_ID_CorrUncertaintyNP3__1up"] = *evsf_signal0_syst_EL_EFF_ID_CorrUncertaintyNP3__1up;
  lep_SF["EL_EFF_ID_CorrUncertaintyNP4__1down"] = *evsf_signal0_syst_EL_EFF_ID_CorrUncertaintyNP4__1down;
  lep_SF["EL_EFF_ID_CorrUncertaintyNP4__1up"] = *evsf_signal0_syst_EL_EFF_ID_CorrUncertaintyNP4__1up;
  lep_SF["EL_EFF_ID_CorrUncertaintyNP5__1down"] = *evsf_signal0_syst_EL_EFF_ID_CorrUncertaintyNP5__1down;
  lep_SF["EL_EFF_ID_CorrUncertaintyNP5__1up"] = *evsf_signal0_syst_EL_EFF_ID_CorrUncertaintyNP5__1up;
  lep_SF["EL_EFF_ID_CorrUncertaintyNP6__1down"] = *evsf_signal0_syst_EL_EFF_ID_CorrUncertaintyNP6__1down;
  lep_SF["EL_EFF_ID_CorrUncertaintyNP6__1up"] = *evsf_signal0_syst_EL_EFF_ID_CorrUncertaintyNP6__1up;
  lep_SF["EL_EFF_ID_CorrUncertaintyNP7__1down"] = *evsf_signal0_syst_EL_EFF_ID_CorrUncertaintyNP7__1down;
  lep_SF["EL_EFF_ID_CorrUncertaintyNP7__1up"] = *evsf_signal0_syst_EL_EFF_ID_CorrUncertaintyNP7__1up;
  lep_SF["EL_EFF_ID_CorrUncertaintyNP8__1down"] = *evsf_signal0_syst_EL_EFF_ID_CorrUncertaintyNP8__1down;
  lep_SF["EL_EFF_ID_CorrUncertaintyNP8__1up"] = *evsf_signal0_syst_EL_EFF_ID_CorrUncertaintyNP8__1up;
  lep_SF["EL_EFF_ID_CorrUncertaintyNP9__1down"] = *evsf_signal0_syst_EL_EFF_ID_CorrUncertaintyNP9__1down;
  lep_SF["EL_EFF_ID_CorrUncertaintyNP9__1up"] = *evsf_signal0_syst_EL_EFF_ID_CorrUncertaintyNP9__1up;
  lep_SF["EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP0__1down"] = *evsf_signal0_syst_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP0__1down;
  lep_SF["EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP0__1up"] = *evsf_signal0_syst_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP0__1up;
  lep_SF["EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP10__1down"] = *evsf_signal0_syst_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP10__1down;
  lep_SF["EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP10__1up"] = *evsf_signal0_syst_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP10__1up;
  lep_SF["EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP11__1down"] = *evsf_signal0_syst_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP11__1down;
  lep_SF["EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP11__1up"] = *evsf_signal0_syst_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP11__1up;
  lep_SF["EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP12__1down"] = *evsf_signal0_syst_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP12__1down;
  lep_SF["EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP12__1up"] = *evsf_signal0_syst_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP12__1up;
  lep_SF["EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP13__1down"] = *evsf_signal0_syst_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP13__1down;
  lep_SF["EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP13__1up"] = *evsf_signal0_syst_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP13__1up;
  lep_SF["EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP14__1down"] = *evsf_signal0_syst_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP14__1down;
  lep_SF["EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP14__1up"] = *evsf_signal0_syst_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP14__1up;
  lep_SF["EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP15__1down"] = *evsf_signal0_syst_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP15__1down;
  lep_SF["EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP15__1up"] = *evsf_signal0_syst_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP15__1up;
  lep_SF["EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP16__1down"] = *evsf_signal0_syst_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP16__1down;
  lep_SF["EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP16__1up"] = *evsf_signal0_syst_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP16__1up;
  lep_SF["EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP17__1down"] = *evsf_signal0_syst_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP17__1down;
  lep_SF["EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP17__1up"] = *evsf_signal0_syst_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP17__1up;
  lep_SF["EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP1__1down"] = *evsf_signal0_syst_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP1__1down;
  lep_SF["EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP1__1up"] = *evsf_signal0_syst_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP1__1up;
  lep_SF["EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP2__1down"] = *evsf_signal0_syst_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP2__1down;
  lep_SF["EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP2__1up"] = *evsf_signal0_syst_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP2__1up;
  lep_SF["EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP3__1down"] = *evsf_signal0_syst_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP3__1down;
  lep_SF["EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP3__1up"] = *evsf_signal0_syst_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP3__1up;
  lep_SF["EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP4__1down"] = *evsf_signal0_syst_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP4__1down;
  lep_SF["EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP4__1up"] = *evsf_signal0_syst_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP4__1up;
  lep_SF["EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP5__1down"] = *evsf_signal0_syst_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP5__1down;
  lep_SF["EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP5__1up"] = *evsf_signal0_syst_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP5__1up;
  lep_SF["EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP6__1down"] = *evsf_signal0_syst_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP6__1down;
  lep_SF["EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP6__1up"] = *evsf_signal0_syst_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP6__1up;
  lep_SF["EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP7__1down"] = *evsf_signal0_syst_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP7__1down;
  lep_SF["EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP7__1up"] = *evsf_signal0_syst_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP7__1up;
  lep_SF["EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP8__1down"] = *evsf_signal0_syst_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP8__1down;
  lep_SF["EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP8__1up"] = *evsf_signal0_syst_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP8__1up;
  lep_SF["EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP9__1down"] = *evsf_signal0_syst_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP9__1down;
  lep_SF["EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP9__1up"] = *evsf_signal0_syst_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP9__1up;
  lep_SF["EL_EFF_ID_TOTAL_1NPCOR_PLUS_UNCOR__1down"] = *evsf_signal0_syst_EL_EFF_ID_TOTAL_1NPCOR_PLUS_UNCOR__1down;
  lep_SF["EL_EFF_ID_TOTAL_1NPCOR_PLUS_UNCOR__1up"] = *evsf_signal0_syst_EL_EFF_ID_TOTAL_1NPCOR_PLUS_UNCOR__1up;
  lep_SF["EL_EFF_Iso_CorrUncertaintyNP0__1down"] = *evsf_signal0_syst_EL_EFF_Iso_CorrUncertaintyNP0__1down;
  lep_SF["EL_EFF_Iso_CorrUncertaintyNP0__1up"] = *evsf_signal0_syst_EL_EFF_Iso_CorrUncertaintyNP0__1up;
  lep_SF["EL_EFF_Iso_CorrUncertaintyNP10__1down"] = *evsf_signal0_syst_EL_EFF_Iso_CorrUncertaintyNP10__1down;
  lep_SF["EL_EFF_Iso_CorrUncertaintyNP10__1up"] = *evsf_signal0_syst_EL_EFF_Iso_CorrUncertaintyNP10__1up;
  lep_SF["EL_EFF_Iso_CorrUncertaintyNP1__1down"] = *evsf_signal0_syst_EL_EFF_Iso_CorrUncertaintyNP1__1down;
  lep_SF["EL_EFF_Iso_CorrUncertaintyNP1__1up"] = *evsf_signal0_syst_EL_EFF_Iso_CorrUncertaintyNP1__1up;
  lep_SF["EL_EFF_Iso_CorrUncertaintyNP2__1down"] = *evsf_signal0_syst_EL_EFF_Iso_CorrUncertaintyNP2__1down;
  lep_SF["EL_EFF_Iso_CorrUncertaintyNP2__1up"] = *evsf_signal0_syst_EL_EFF_Iso_CorrUncertaintyNP2__1up;
  lep_SF["EL_EFF_Iso_CorrUncertaintyNP3__1down"] = *evsf_signal0_syst_EL_EFF_Iso_CorrUncertaintyNP3__1down;
  lep_SF["EL_EFF_Iso_CorrUncertaintyNP3__1up"] = *evsf_signal0_syst_EL_EFF_Iso_CorrUncertaintyNP3__1up;
  lep_SF["EL_EFF_Iso_CorrUncertaintyNP4__1down"] = *evsf_signal0_syst_EL_EFF_Iso_CorrUncertaintyNP4__1down;
  lep_SF["EL_EFF_Iso_CorrUncertaintyNP4__1up"] = *evsf_signal0_syst_EL_EFF_Iso_CorrUncertaintyNP4__1up;
  lep_SF["EL_EFF_Iso_CorrUncertaintyNP5__1down"] = *evsf_signal0_syst_EL_EFF_Iso_CorrUncertaintyNP5__1down;
  lep_SF["EL_EFF_Iso_CorrUncertaintyNP5__1up"] = *evsf_signal0_syst_EL_EFF_Iso_CorrUncertaintyNP5__1up;
  lep_SF["EL_EFF_Iso_CorrUncertaintyNP6__1down"] = *evsf_signal0_syst_EL_EFF_Iso_CorrUncertaintyNP6__1down;
  lep_SF["EL_EFF_Iso_CorrUncertaintyNP6__1up"] = *evsf_signal0_syst_EL_EFF_Iso_CorrUncertaintyNP6__1up;
  lep_SF["EL_EFF_Iso_CorrUncertaintyNP7__1down"] = *evsf_signal0_syst_EL_EFF_Iso_CorrUncertaintyNP7__1down;
  lep_SF["EL_EFF_Iso_CorrUncertaintyNP7__1up"] = *evsf_signal0_syst_EL_EFF_Iso_CorrUncertaintyNP7__1up;
  lep_SF["EL_EFF_Iso_CorrUncertaintyNP8__1down"] = *evsf_signal0_syst_EL_EFF_Iso_CorrUncertaintyNP8__1down;
  lep_SF["EL_EFF_Iso_CorrUncertaintyNP8__1up"] = *evsf_signal0_syst_EL_EFF_Iso_CorrUncertaintyNP8__1up;
  lep_SF["EL_EFF_Iso_CorrUncertaintyNP9__1down"] = *evsf_signal0_syst_EL_EFF_Iso_CorrUncertaintyNP9__1down;
  lep_SF["EL_EFF_Iso_CorrUncertaintyNP9__1up"] = *evsf_signal0_syst_EL_EFF_Iso_CorrUncertaintyNP9__1up;
  lep_SF["EL_EFF_Iso_SIMPLIFIED_UncorrUncertaintyNP0__1down"] = *evsf_signal0_syst_EL_EFF_Iso_SIMPLIFIED_UncorrUncertaintyNP0__1down;
  lep_SF["EL_EFF_Iso_SIMPLIFIED_UncorrUncertaintyNP0__1up"] = *evsf_signal0_syst_EL_EFF_Iso_SIMPLIFIED_UncorrUncertaintyNP0__1up;
  lep_SF["EL_EFF_Iso_SIMPLIFIED_UncorrUncertaintyNP10__1down"] = *evsf_signal0_syst_EL_EFF_Iso_SIMPLIFIED_UncorrUncertaintyNP10__1down;
  lep_SF["EL_EFF_Iso_SIMPLIFIED_UncorrUncertaintyNP10__1up"] = *evsf_signal0_syst_EL_EFF_Iso_SIMPLIFIED_UncorrUncertaintyNP10__1up;
  lep_SF["EL_EFF_Iso_SIMPLIFIED_UncorrUncertaintyNP11__1down"] = *evsf_signal0_syst_EL_EFF_Iso_SIMPLIFIED_UncorrUncertaintyNP11__1down;
  lep_SF["EL_EFF_Iso_SIMPLIFIED_UncorrUncertaintyNP11__1up"] = *evsf_signal0_syst_EL_EFF_Iso_SIMPLIFIED_UncorrUncertaintyNP11__1up;
  lep_SF["EL_EFF_Iso_SIMPLIFIED_UncorrUncertaintyNP12__1down"] = *evsf_signal0_syst_EL_EFF_Iso_SIMPLIFIED_UncorrUncertaintyNP12__1down;
  lep_SF["EL_EFF_Iso_SIMPLIFIED_UncorrUncertaintyNP12__1up"] = *evsf_signal0_syst_EL_EFF_Iso_SIMPLIFIED_UncorrUncertaintyNP12__1up;
  lep_SF["EL_EFF_Iso_SIMPLIFIED_UncorrUncertaintyNP13__1down"] = *evsf_signal0_syst_EL_EFF_Iso_SIMPLIFIED_UncorrUncertaintyNP13__1down;
  lep_SF["EL_EFF_Iso_SIMPLIFIED_UncorrUncertaintyNP13__1up"] = *evsf_signal0_syst_EL_EFF_Iso_SIMPLIFIED_UncorrUncertaintyNP13__1up;
  lep_SF["EL_EFF_Iso_SIMPLIFIED_UncorrUncertaintyNP14__1down"] = *evsf_signal0_syst_EL_EFF_Iso_SIMPLIFIED_UncorrUncertaintyNP14__1down;
  lep_SF["EL_EFF_Iso_SIMPLIFIED_UncorrUncertaintyNP14__1up"] = *evsf_signal0_syst_EL_EFF_Iso_SIMPLIFIED_UncorrUncertaintyNP14__1up;
  lep_SF["EL_EFF_Iso_SIMPLIFIED_UncorrUncertaintyNP15__1down"] = *evsf_signal0_syst_EL_EFF_Iso_SIMPLIFIED_UncorrUncertaintyNP15__1down;
  lep_SF["EL_EFF_Iso_SIMPLIFIED_UncorrUncertaintyNP15__1up"] = *evsf_signal0_syst_EL_EFF_Iso_SIMPLIFIED_UncorrUncertaintyNP15__1up;
  lep_SF["EL_EFF_Iso_SIMPLIFIED_UncorrUncertaintyNP16__1down"] = *evsf_signal0_syst_EL_EFF_Iso_SIMPLIFIED_UncorrUncertaintyNP16__1down;
  lep_SF["EL_EFF_Iso_SIMPLIFIED_UncorrUncertaintyNP16__1up"] = *evsf_signal0_syst_EL_EFF_Iso_SIMPLIFIED_UncorrUncertaintyNP16__1up;
  lep_SF["EL_EFF_Iso_SIMPLIFIED_UncorrUncertaintyNP17__1down"] = *evsf_signal0_syst_EL_EFF_Iso_SIMPLIFIED_UncorrUncertaintyNP17__1down;
  lep_SF["EL_EFF_Iso_SIMPLIFIED_UncorrUncertaintyNP17__1up"] = *evsf_signal0_syst_EL_EFF_Iso_SIMPLIFIED_UncorrUncertaintyNP17__1up;
  lep_SF["EL_EFF_Iso_SIMPLIFIED_UncorrUncertaintyNP1__1down"] = *evsf_signal0_syst_EL_EFF_Iso_SIMPLIFIED_UncorrUncertaintyNP1__1down;
  lep_SF["EL_EFF_Iso_SIMPLIFIED_UncorrUncertaintyNP1__1up"] = *evsf_signal0_syst_EL_EFF_Iso_SIMPLIFIED_UncorrUncertaintyNP1__1up;
  lep_SF["EL_EFF_Iso_SIMPLIFIED_UncorrUncertaintyNP2__1down"] = *evsf_signal0_syst_EL_EFF_Iso_SIMPLIFIED_UncorrUncertaintyNP2__1down;
  lep_SF["EL_EFF_Iso_SIMPLIFIED_UncorrUncertaintyNP2__1up"] = *evsf_signal0_syst_EL_EFF_Iso_SIMPLIFIED_UncorrUncertaintyNP2__1up;
  lep_SF["EL_EFF_Iso_SIMPLIFIED_UncorrUncertaintyNP3__1down"] = *evsf_signal0_syst_EL_EFF_Iso_SIMPLIFIED_UncorrUncertaintyNP3__1down;
  lep_SF["EL_EFF_Iso_SIMPLIFIED_UncorrUncertaintyNP3__1up"] = *evsf_signal0_syst_EL_EFF_Iso_SIMPLIFIED_UncorrUncertaintyNP3__1up;
  lep_SF["EL_EFF_Iso_SIMPLIFIED_UncorrUncertaintyNP4__1down"] = *evsf_signal0_syst_EL_EFF_Iso_SIMPLIFIED_UncorrUncertaintyNP4__1down;
  lep_SF["EL_EFF_Iso_SIMPLIFIED_UncorrUncertaintyNP4__1up"] = *evsf_signal0_syst_EL_EFF_Iso_SIMPLIFIED_UncorrUncertaintyNP4__1up;
  lep_SF["EL_EFF_Iso_SIMPLIFIED_UncorrUncertaintyNP5__1down"] = *evsf_signal0_syst_EL_EFF_Iso_SIMPLIFIED_UncorrUncertaintyNP5__1down;
  lep_SF["EL_EFF_Iso_SIMPLIFIED_UncorrUncertaintyNP5__1up"] = *evsf_signal0_syst_EL_EFF_Iso_SIMPLIFIED_UncorrUncertaintyNP5__1up;
  lep_SF["EL_EFF_Iso_SIMPLIFIED_UncorrUncertaintyNP6__1down"] = *evsf_signal0_syst_EL_EFF_Iso_SIMPLIFIED_UncorrUncertaintyNP6__1down;
  lep_SF["EL_EFF_Iso_SIMPLIFIED_UncorrUncertaintyNP6__1up"] = *evsf_signal0_syst_EL_EFF_Iso_SIMPLIFIED_UncorrUncertaintyNP6__1up;
  lep_SF["EL_EFF_Iso_SIMPLIFIED_UncorrUncertaintyNP7__1down"] = *evsf_signal0_syst_EL_EFF_Iso_SIMPLIFIED_UncorrUncertaintyNP7__1down;
  lep_SF["EL_EFF_Iso_SIMPLIFIED_UncorrUncertaintyNP7__1up"] = *evsf_signal0_syst_EL_EFF_Iso_SIMPLIFIED_UncorrUncertaintyNP7__1up;
  lep_SF["EL_EFF_Iso_SIMPLIFIED_UncorrUncertaintyNP8__1down"] = *evsf_signal0_syst_EL_EFF_Iso_SIMPLIFIED_UncorrUncertaintyNP8__1down;
  lep_SF["EL_EFF_Iso_SIMPLIFIED_UncorrUncertaintyNP8__1up"] = *evsf_signal0_syst_EL_EFF_Iso_SIMPLIFIED_UncorrUncertaintyNP8__1up;
  lep_SF["EL_EFF_Iso_SIMPLIFIED_UncorrUncertaintyNP9__1down"] = *evsf_signal0_syst_EL_EFF_Iso_SIMPLIFIED_UncorrUncertaintyNP9__1down;
  lep_SF["EL_EFF_Iso_SIMPLIFIED_UncorrUncertaintyNP9__1up"] = *evsf_signal0_syst_EL_EFF_Iso_SIMPLIFIED_UncorrUncertaintyNP9__1up;
  lep_SF["EL_EFF_Iso_TOTAL_1NPCOR_PLUS_UNCOR__1down"] = *evsf_signal0_syst_EL_EFF_Iso_TOTAL_1NPCOR_PLUS_UNCOR__1down;
  lep_SF["EL_EFF_Iso_TOTAL_1NPCOR_PLUS_UNCOR__1up"] = *evsf_signal0_syst_EL_EFF_Iso_TOTAL_1NPCOR_PLUS_UNCOR__1up;
  lep_SF["EL_EFF_Reco_CorrUncertaintyNP0__1down"] = *evsf_signal0_syst_EL_EFF_Reco_CorrUncertaintyNP0__1down;
  lep_SF["EL_EFF_Reco_CorrUncertaintyNP0__1up"] = *evsf_signal0_syst_EL_EFF_Reco_CorrUncertaintyNP0__1up;
  lep_SF["EL_EFF_Reco_CorrUncertaintyNP1__1down"] = *evsf_signal0_syst_EL_EFF_Reco_CorrUncertaintyNP1__1down;
  lep_SF["EL_EFF_Reco_CorrUncertaintyNP1__1up"] = *evsf_signal0_syst_EL_EFF_Reco_CorrUncertaintyNP1__1up;
  lep_SF["EL_EFF_Reco_CorrUncertaintyNP2__1down"] = *evsf_signal0_syst_EL_EFF_Reco_CorrUncertaintyNP2__1down;
  lep_SF["EL_EFF_Reco_CorrUncertaintyNP2__1up"] = *evsf_signal0_syst_EL_EFF_Reco_CorrUncertaintyNP2__1up;
  lep_SF["EL_EFF_Reco_CorrUncertaintyNP3__1down"] = *evsf_signal0_syst_EL_EFF_Reco_CorrUncertaintyNP3__1down;
  lep_SF["EL_EFF_Reco_CorrUncertaintyNP3__1up"] = *evsf_signal0_syst_EL_EFF_Reco_CorrUncertaintyNP3__1up;
  lep_SF["EL_EFF_Reco_CorrUncertaintyNP4__1down"] = *evsf_signal0_syst_EL_EFF_Reco_CorrUncertaintyNP4__1down;
  lep_SF["EL_EFF_Reco_CorrUncertaintyNP4__1up"] = *evsf_signal0_syst_EL_EFF_Reco_CorrUncertaintyNP4__1up;
  lep_SF["EL_EFF_Reco_CorrUncertaintyNP5__1down"] = *evsf_signal0_syst_EL_EFF_Reco_CorrUncertaintyNP5__1down;
  lep_SF["EL_EFF_Reco_CorrUncertaintyNP5__1up"] = *evsf_signal0_syst_EL_EFF_Reco_CorrUncertaintyNP5__1up;
  lep_SF["EL_EFF_Reco_CorrUncertaintyNP6__1down"] = *evsf_signal0_syst_EL_EFF_Reco_CorrUncertaintyNP6__1down;
  lep_SF["EL_EFF_Reco_CorrUncertaintyNP6__1up"] = *evsf_signal0_syst_EL_EFF_Reco_CorrUncertaintyNP6__1up;
  lep_SF["EL_EFF_Reco_CorrUncertaintyNP7__1down"] = *evsf_signal0_syst_EL_EFF_Reco_CorrUncertaintyNP7__1down;
  lep_SF["EL_EFF_Reco_CorrUncertaintyNP7__1up"] = *evsf_signal0_syst_EL_EFF_Reco_CorrUncertaintyNP7__1up;
  lep_SF["EL_EFF_Reco_SIMPLIFIED_UncorrUncertaintyNP0__1down"] = *evsf_signal0_syst_EL_EFF_Reco_SIMPLIFIED_UncorrUncertaintyNP0__1down;
  lep_SF["EL_EFF_Reco_SIMPLIFIED_UncorrUncertaintyNP0__1up"] = *evsf_signal0_syst_EL_EFF_Reco_SIMPLIFIED_UncorrUncertaintyNP0__1up;
  lep_SF["EL_EFF_Reco_SIMPLIFIED_UncorrUncertaintyNP10__1down"] = *evsf_signal0_syst_EL_EFF_Reco_SIMPLIFIED_UncorrUncertaintyNP10__1down;
  lep_SF["EL_EFF_Reco_SIMPLIFIED_UncorrUncertaintyNP10__1up"] = *evsf_signal0_syst_EL_EFF_Reco_SIMPLIFIED_UncorrUncertaintyNP10__1up;
  lep_SF["EL_EFF_Reco_SIMPLIFIED_UncorrUncertaintyNP11__1down"] = *evsf_signal0_syst_EL_EFF_Reco_SIMPLIFIED_UncorrUncertaintyNP11__1down;
  lep_SF["EL_EFF_Reco_SIMPLIFIED_UncorrUncertaintyNP11__1up"] = *evsf_signal0_syst_EL_EFF_Reco_SIMPLIFIED_UncorrUncertaintyNP11__1up;
  lep_SF["EL_EFF_Reco_SIMPLIFIED_UncorrUncertaintyNP12__1down"] = *evsf_signal0_syst_EL_EFF_Reco_SIMPLIFIED_UncorrUncertaintyNP12__1down;
  lep_SF["EL_EFF_Reco_SIMPLIFIED_UncorrUncertaintyNP12__1up"] = *evsf_signal0_syst_EL_EFF_Reco_SIMPLIFIED_UncorrUncertaintyNP12__1up;
  lep_SF["EL_EFF_Reco_SIMPLIFIED_UncorrUncertaintyNP13__1down"] = *evsf_signal0_syst_EL_EFF_Reco_SIMPLIFIED_UncorrUncertaintyNP13__1down;
  lep_SF["EL_EFF_Reco_SIMPLIFIED_UncorrUncertaintyNP13__1up"] = *evsf_signal0_syst_EL_EFF_Reco_SIMPLIFIED_UncorrUncertaintyNP13__1up;
  lep_SF["EL_EFF_Reco_SIMPLIFIED_UncorrUncertaintyNP14__1down"] = *evsf_signal0_syst_EL_EFF_Reco_SIMPLIFIED_UncorrUncertaintyNP14__1down;
  lep_SF["EL_EFF_Reco_SIMPLIFIED_UncorrUncertaintyNP14__1up"] = *evsf_signal0_syst_EL_EFF_Reco_SIMPLIFIED_UncorrUncertaintyNP14__1up;
  lep_SF["EL_EFF_Reco_SIMPLIFIED_UncorrUncertaintyNP15__1down"] = *evsf_signal0_syst_EL_EFF_Reco_SIMPLIFIED_UncorrUncertaintyNP15__1down;
  lep_SF["EL_EFF_Reco_SIMPLIFIED_UncorrUncertaintyNP15__1up"] = *evsf_signal0_syst_EL_EFF_Reco_SIMPLIFIED_UncorrUncertaintyNP15__1up;
  lep_SF["EL_EFF_Reco_SIMPLIFIED_UncorrUncertaintyNP16__1down"] = *evsf_signal0_syst_EL_EFF_Reco_SIMPLIFIED_UncorrUncertaintyNP16__1down;
  lep_SF["EL_EFF_Reco_SIMPLIFIED_UncorrUncertaintyNP16__1up"] = *evsf_signal0_syst_EL_EFF_Reco_SIMPLIFIED_UncorrUncertaintyNP16__1up;
  lep_SF["EL_EFF_Reco_SIMPLIFIED_UncorrUncertaintyNP17__1down"] = *evsf_signal0_syst_EL_EFF_Reco_SIMPLIFIED_UncorrUncertaintyNP17__1down;
  lep_SF["EL_EFF_Reco_SIMPLIFIED_UncorrUncertaintyNP17__1up"] = *evsf_signal0_syst_EL_EFF_Reco_SIMPLIFIED_UncorrUncertaintyNP17__1up;
  lep_SF["EL_EFF_Reco_SIMPLIFIED_UncorrUncertaintyNP1__1down"] = *evsf_signal0_syst_EL_EFF_Reco_SIMPLIFIED_UncorrUncertaintyNP1__1down;
  lep_SF["EL_EFF_Reco_SIMPLIFIED_UncorrUncertaintyNP1__1up"] = *evsf_signal0_syst_EL_EFF_Reco_SIMPLIFIED_UncorrUncertaintyNP1__1up;
  lep_SF["EL_EFF_Reco_SIMPLIFIED_UncorrUncertaintyNP2__1down"] = *evsf_signal0_syst_EL_EFF_Reco_SIMPLIFIED_UncorrUncertaintyNP2__1down;
  lep_SF["EL_EFF_Reco_SIMPLIFIED_UncorrUncertaintyNP2__1up"] = *evsf_signal0_syst_EL_EFF_Reco_SIMPLIFIED_UncorrUncertaintyNP2__1up;
  lep_SF["EL_EFF_Reco_SIMPLIFIED_UncorrUncertaintyNP3__1down"] = *evsf_signal0_syst_EL_EFF_Reco_SIMPLIFIED_UncorrUncertaintyNP3__1down;
  lep_SF["EL_EFF_Reco_SIMPLIFIED_UncorrUncertaintyNP3__1up"] = *evsf_signal0_syst_EL_EFF_Reco_SIMPLIFIED_UncorrUncertaintyNP3__1up;
  lep_SF["EL_EFF_Reco_SIMPLIFIED_UncorrUncertaintyNP4__1down"] = *evsf_signal0_syst_EL_EFF_Reco_SIMPLIFIED_UncorrUncertaintyNP4__1down;
  lep_SF["EL_EFF_Reco_SIMPLIFIED_UncorrUncertaintyNP4__1up"] = *evsf_signal0_syst_EL_EFF_Reco_SIMPLIFIED_UncorrUncertaintyNP4__1up;
  lep_SF["EL_EFF_Reco_SIMPLIFIED_UncorrUncertaintyNP5__1down"] = *evsf_signal0_syst_EL_EFF_Reco_SIMPLIFIED_UncorrUncertaintyNP5__1down;
  lep_SF["EL_EFF_Reco_SIMPLIFIED_UncorrUncertaintyNP5__1up"] = *evsf_signal0_syst_EL_EFF_Reco_SIMPLIFIED_UncorrUncertaintyNP5__1up;
  lep_SF["EL_EFF_Reco_SIMPLIFIED_UncorrUncertaintyNP6__1down"] = *evsf_signal0_syst_EL_EFF_Reco_SIMPLIFIED_UncorrUncertaintyNP6__1down;
  lep_SF["EL_EFF_Reco_SIMPLIFIED_UncorrUncertaintyNP6__1up"] = *evsf_signal0_syst_EL_EFF_Reco_SIMPLIFIED_UncorrUncertaintyNP6__1up;
  lep_SF["EL_EFF_Reco_SIMPLIFIED_UncorrUncertaintyNP7__1down"] = *evsf_signal0_syst_EL_EFF_Reco_SIMPLIFIED_UncorrUncertaintyNP7__1down;
  lep_SF["EL_EFF_Reco_SIMPLIFIED_UncorrUncertaintyNP7__1up"] = *evsf_signal0_syst_EL_EFF_Reco_SIMPLIFIED_UncorrUncertaintyNP7__1up;
  lep_SF["EL_EFF_Reco_SIMPLIFIED_UncorrUncertaintyNP8__1down"] = *evsf_signal0_syst_EL_EFF_Reco_SIMPLIFIED_UncorrUncertaintyNP8__1down;
  lep_SF["EL_EFF_Reco_SIMPLIFIED_UncorrUncertaintyNP8__1up"] = *evsf_signal0_syst_EL_EFF_Reco_SIMPLIFIED_UncorrUncertaintyNP8__1up;
  lep_SF["EL_EFF_Reco_SIMPLIFIED_UncorrUncertaintyNP9__1down"] = *evsf_signal0_syst_EL_EFF_Reco_SIMPLIFIED_UncorrUncertaintyNP9__1down;
  lep_SF["EL_EFF_Reco_SIMPLIFIED_UncorrUncertaintyNP9__1up"] = *evsf_signal0_syst_EL_EFF_Reco_SIMPLIFIED_UncorrUncertaintyNP9__1up; 

  return lep_SF; 

}

map<TString, Float_t> EventSelector::GetCidSFVariations(Long64_t entry){

  map<TString, Float_t> cid_SF; 

  cid_SF["EL_CHARGEID_STAT__1down"] = *SF_cid_syst_EL_CHARGEID_STAT__1down;
  cid_SF["EL_CHARGEID_STAT__1up"] = *SF_cid_syst_EL_CHARGEID_STAT__1up;
  cid_SF["EL_CHARGEID_SYStotal__1down"] = *SF_cid_syst_EL_CHARGEID_SYStotal__1down;
  cid_SF["EL_CHARGEID_SYStotal__1up"] = *SF_cid_syst_EL_CHARGEID_SYStotal__1up;
  cid_SF["EL_EFF_ChargeIDSel_CorrUncertaintyNP0__1down"] = *SF_cid_syst_EL_EFF_ChargeIDSel_CorrUncertaintyNP0__1down;
  cid_SF["EL_EFF_ChargeIDSel_CorrUncertaintyNP0__1up"] = *SF_cid_syst_EL_EFF_ChargeIDSel_CorrUncertaintyNP0__1up;
  cid_SF["EL_EFF_ChargeIDSel_CorrUncertaintyNP10__1down"] = *SF_cid_syst_EL_EFF_ChargeIDSel_CorrUncertaintyNP10__1down;
  cid_SF["EL_EFF_ChargeIDSel_CorrUncertaintyNP10__1up"] = *SF_cid_syst_EL_EFF_ChargeIDSel_CorrUncertaintyNP10__1up;
  cid_SF["EL_EFF_ChargeIDSel_CorrUncertaintyNP1__1down"] = *SF_cid_syst_EL_EFF_ChargeIDSel_CorrUncertaintyNP1__1down;
  cid_SF["EL_EFF_ChargeIDSel_CorrUncertaintyNP1__1up"] = *SF_cid_syst_EL_EFF_ChargeIDSel_CorrUncertaintyNP1__1up;
  cid_SF["EL_EFF_ChargeIDSel_CorrUncertaintyNP2__1down"] = *SF_cid_syst_EL_EFF_ChargeIDSel_CorrUncertaintyNP2__1down;
  cid_SF["EL_EFF_ChargeIDSel_CorrUncertaintyNP2__1up"] = *SF_cid_syst_EL_EFF_ChargeIDSel_CorrUncertaintyNP2__1up;
  cid_SF["EL_EFF_ChargeIDSel_CorrUncertaintyNP3__1down"] = *SF_cid_syst_EL_EFF_ChargeIDSel_CorrUncertaintyNP3__1down;
  cid_SF["EL_EFF_ChargeIDSel_CorrUncertaintyNP3__1up"] = *SF_cid_syst_EL_EFF_ChargeIDSel_CorrUncertaintyNP3__1up;
  cid_SF["EL_EFF_ChargeIDSel_CorrUncertaintyNP4__1down"] = *SF_cid_syst_EL_EFF_ChargeIDSel_CorrUncertaintyNP4__1down;
  cid_SF["EL_EFF_ChargeIDSel_CorrUncertaintyNP4__1up"] = *SF_cid_syst_EL_EFF_ChargeIDSel_CorrUncertaintyNP4__1up;
  cid_SF["EL_EFF_ChargeIDSel_CorrUncertaintyNP5__1down"] = *SF_cid_syst_EL_EFF_ChargeIDSel_CorrUncertaintyNP5__1down;
  cid_SF["EL_EFF_ChargeIDSel_CorrUncertaintyNP5__1up"] = *SF_cid_syst_EL_EFF_ChargeIDSel_CorrUncertaintyNP5__1up;
  cid_SF["EL_EFF_ChargeIDSel_CorrUncertaintyNP6__1down"] = *SF_cid_syst_EL_EFF_ChargeIDSel_CorrUncertaintyNP6__1down;
  cid_SF["EL_EFF_ChargeIDSel_CorrUncertaintyNP6__1up"] = *SF_cid_syst_EL_EFF_ChargeIDSel_CorrUncertaintyNP6__1up;
  cid_SF["EL_EFF_ChargeIDSel_CorrUncertaintyNP7__1down"] = *SF_cid_syst_EL_EFF_ChargeIDSel_CorrUncertaintyNP7__1down;
  cid_SF["EL_EFF_ChargeIDSel_CorrUncertaintyNP7__1up"] = *SF_cid_syst_EL_EFF_ChargeIDSel_CorrUncertaintyNP7__1up;
  cid_SF["EL_EFF_ChargeIDSel_CorrUncertaintyNP8__1down"] = *SF_cid_syst_EL_EFF_ChargeIDSel_CorrUncertaintyNP8__1down;
  cid_SF["EL_EFF_ChargeIDSel_CorrUncertaintyNP8__1up"] = *SF_cid_syst_EL_EFF_ChargeIDSel_CorrUncertaintyNP8__1up;
  cid_SF["EL_EFF_ChargeIDSel_CorrUncertaintyNP9__1down"] = *SF_cid_syst_EL_EFF_ChargeIDSel_CorrUncertaintyNP9__1down;
  cid_SF["EL_EFF_ChargeIDSel_CorrUncertaintyNP9__1up"] = *SF_cid_syst_EL_EFF_ChargeIDSel_CorrUncertaintyNP9__1up;
  cid_SF["EL_EFF_ChargeIDSel_SIMPLIFIED_UncorrUncertaintyNP0__1down"] = *SF_cid_syst_EL_EFF_ChargeIDSel_SIMPLIFIED_UncorrUncertaintyNP0__1down;
  cid_SF["EL_EFF_ChargeIDSel_SIMPLIFIED_UncorrUncertaintyNP0__1up"] = *SF_cid_syst_EL_EFF_ChargeIDSel_SIMPLIFIED_UncorrUncertaintyNP0__1up;
  cid_SF["EL_EFF_ChargeIDSel_SIMPLIFIED_UncorrUncertaintyNP10__1down"] = *SF_cid_syst_EL_EFF_ChargeIDSel_SIMPLIFIED_UncorrUncertaintyNP10__1down;
  cid_SF["EL_EFF_ChargeIDSel_SIMPLIFIED_UncorrUncertaintyNP10__1up"] = *SF_cid_syst_EL_EFF_ChargeIDSel_SIMPLIFIED_UncorrUncertaintyNP10__1up;
  cid_SF["EL_EFF_ChargeIDSel_SIMPLIFIED_UncorrUncertaintyNP11__1down"] = *SF_cid_syst_EL_EFF_ChargeIDSel_SIMPLIFIED_UncorrUncertaintyNP11__1down;
  cid_SF["EL_EFF_ChargeIDSel_SIMPLIFIED_UncorrUncertaintyNP11__1up"] = *SF_cid_syst_EL_EFF_ChargeIDSel_SIMPLIFIED_UncorrUncertaintyNP11__1up;
  cid_SF["EL_EFF_ChargeIDSel_SIMPLIFIED_UncorrUncertaintyNP12__1down"] = *SF_cid_syst_EL_EFF_ChargeIDSel_SIMPLIFIED_UncorrUncertaintyNP12__1down;
  cid_SF["EL_EFF_ChargeIDSel_SIMPLIFIED_UncorrUncertaintyNP12__1up"] = *SF_cid_syst_EL_EFF_ChargeIDSel_SIMPLIFIED_UncorrUncertaintyNP12__1up;
  cid_SF["EL_EFF_ChargeIDSel_SIMPLIFIED_UncorrUncertaintyNP13__1down"] = *SF_cid_syst_EL_EFF_ChargeIDSel_SIMPLIFIED_UncorrUncertaintyNP13__1down;
  cid_SF["EL_EFF_ChargeIDSel_SIMPLIFIED_UncorrUncertaintyNP13__1up"] = *SF_cid_syst_EL_EFF_ChargeIDSel_SIMPLIFIED_UncorrUncertaintyNP13__1up;
  cid_SF["EL_EFF_ChargeIDSel_SIMPLIFIED_UncorrUncertaintyNP14__1down"] = *SF_cid_syst_EL_EFF_ChargeIDSel_SIMPLIFIED_UncorrUncertaintyNP14__1down;
  cid_SF["EL_EFF_ChargeIDSel_SIMPLIFIED_UncorrUncertaintyNP14__1up"] = *SF_cid_syst_EL_EFF_ChargeIDSel_SIMPLIFIED_UncorrUncertaintyNP14__1up;
  cid_SF["EL_EFF_ChargeIDSel_SIMPLIFIED_UncorrUncertaintyNP15__1down"] = *SF_cid_syst_EL_EFF_ChargeIDSel_SIMPLIFIED_UncorrUncertaintyNP15__1down;
  cid_SF["EL_EFF_ChargeIDSel_SIMPLIFIED_UncorrUncertaintyNP15__1up"] = *SF_cid_syst_EL_EFF_ChargeIDSel_SIMPLIFIED_UncorrUncertaintyNP15__1up;
  cid_SF["EL_EFF_ChargeIDSel_SIMPLIFIED_UncorrUncertaintyNP16__1down"] = *SF_cid_syst_EL_EFF_ChargeIDSel_SIMPLIFIED_UncorrUncertaintyNP16__1down;
  cid_SF["EL_EFF_ChargeIDSel_SIMPLIFIED_UncorrUncertaintyNP16__1up"] = *SF_cid_syst_EL_EFF_ChargeIDSel_SIMPLIFIED_UncorrUncertaintyNP16__1up;
  cid_SF["EL_EFF_ChargeIDSel_SIMPLIFIED_UncorrUncertaintyNP17__1down"] = *SF_cid_syst_EL_EFF_ChargeIDSel_SIMPLIFIED_UncorrUncertaintyNP17__1down;
  cid_SF["EL_EFF_ChargeIDSel_SIMPLIFIED_UncorrUncertaintyNP17__1up"] = *SF_cid_syst_EL_EFF_ChargeIDSel_SIMPLIFIED_UncorrUncertaintyNP17__1up;
  cid_SF["EL_EFF_ChargeIDSel_SIMPLIFIED_UncorrUncertaintyNP1__1down"] = *SF_cid_syst_EL_EFF_ChargeIDSel_SIMPLIFIED_UncorrUncertaintyNP1__1down;
  cid_SF["EL_EFF_ChargeIDSel_SIMPLIFIED_UncorrUncertaintyNP1__1up"] = *SF_cid_syst_EL_EFF_ChargeIDSel_SIMPLIFIED_UncorrUncertaintyNP1__1up;
  cid_SF["EL_EFF_ChargeIDSel_SIMPLIFIED_UncorrUncertaintyNP2__1down"] = *SF_cid_syst_EL_EFF_ChargeIDSel_SIMPLIFIED_UncorrUncertaintyNP2__1down;
  cid_SF["EL_EFF_ChargeIDSel_SIMPLIFIED_UncorrUncertaintyNP2__1up"] = *SF_cid_syst_EL_EFF_ChargeIDSel_SIMPLIFIED_UncorrUncertaintyNP2__1up;
  cid_SF["EL_EFF_ChargeIDSel_SIMPLIFIED_UncorrUncertaintyNP3__1down"] = *SF_cid_syst_EL_EFF_ChargeIDSel_SIMPLIFIED_UncorrUncertaintyNP3__1down;
  cid_SF["EL_EFF_ChargeIDSel_SIMPLIFIED_UncorrUncertaintyNP3__1up"] = *SF_cid_syst_EL_EFF_ChargeIDSel_SIMPLIFIED_UncorrUncertaintyNP3__1up;
  cid_SF["EL_EFF_ChargeIDSel_SIMPLIFIED_UncorrUncertaintyNP4__1down"] = *SF_cid_syst_EL_EFF_ChargeIDSel_SIMPLIFIED_UncorrUncertaintyNP4__1down;
  cid_SF["EL_EFF_ChargeIDSel_SIMPLIFIED_UncorrUncertaintyNP4__1up"] = *SF_cid_syst_EL_EFF_ChargeIDSel_SIMPLIFIED_UncorrUncertaintyNP4__1up;
  cid_SF["EL_EFF_ChargeIDSel_SIMPLIFIED_UncorrUncertaintyNP5__1down"] = *SF_cid_syst_EL_EFF_ChargeIDSel_SIMPLIFIED_UncorrUncertaintyNP5__1down;
  cid_SF["EL_EFF_ChargeIDSel_SIMPLIFIED_UncorrUncertaintyNP5__1up"] = *SF_cid_syst_EL_EFF_ChargeIDSel_SIMPLIFIED_UncorrUncertaintyNP5__1up;
  cid_SF["EL_EFF_ChargeIDSel_SIMPLIFIED_UncorrUncertaintyNP6__1down"] = *SF_cid_syst_EL_EFF_ChargeIDSel_SIMPLIFIED_UncorrUncertaintyNP6__1down;
  cid_SF["EL_EFF_ChargeIDSel_SIMPLIFIED_UncorrUncertaintyNP6__1up"] = *SF_cid_syst_EL_EFF_ChargeIDSel_SIMPLIFIED_UncorrUncertaintyNP6__1up;
  cid_SF["EL_EFF_ChargeIDSel_SIMPLIFIED_UncorrUncertaintyNP7__1down"] = *SF_cid_syst_EL_EFF_ChargeIDSel_SIMPLIFIED_UncorrUncertaintyNP7__1down;
  cid_SF["EL_EFF_ChargeIDSel_SIMPLIFIED_UncorrUncertaintyNP7__1up"] = *SF_cid_syst_EL_EFF_ChargeIDSel_SIMPLIFIED_UncorrUncertaintyNP7__1up;
  cid_SF["EL_EFF_ChargeIDSel_SIMPLIFIED_UncorrUncertaintyNP8__1down"] = *SF_cid_syst_EL_EFF_ChargeIDSel_SIMPLIFIED_UncorrUncertaintyNP8__1down;
  cid_SF["EL_EFF_ChargeIDSel_SIMPLIFIED_UncorrUncertaintyNP8__1up"] = *SF_cid_syst_EL_EFF_ChargeIDSel_SIMPLIFIED_UncorrUncertaintyNP8__1up;
  cid_SF["EL_EFF_ChargeIDSel_SIMPLIFIED_UncorrUncertaintyNP9__1down"] = *SF_cid_syst_EL_EFF_ChargeIDSel_SIMPLIFIED_UncorrUncertaintyNP9__1down;
  cid_SF["EL_EFF_ChargeIDSel_SIMPLIFIED_UncorrUncertaintyNP9__1up"] = *SF_cid_syst_EL_EFF_ChargeIDSel_SIMPLIFIED_UncorrUncertaintyNP9__1up;

  return cid_SF; 

}

map<TString, Float_t> EventSelector::GetJetSFVariations(Long64_t entry){

  map<TString, Float_t> jet_SF; 

  jet_SF["FT_EFF_Eigen_B_0__1down"] = *btag_signal_jets_SF_syst_FT_EFF_Eigen_B_0__1down;
  jet_SF["FT_EFF_Eigen_B_0__1up"] = *btag_signal_jets_SF_syst_FT_EFF_Eigen_B_0__1up;
  jet_SF["FT_EFF_Eigen_B_1__1down"] = *btag_signal_jets_SF_syst_FT_EFF_Eigen_B_1__1down;
  jet_SF["FT_EFF_Eigen_B_1__1up"] = *btag_signal_jets_SF_syst_FT_EFF_Eigen_B_1__1up;
  jet_SF["FT_EFF_Eigen_B_2__1down"] = *btag_signal_jets_SF_syst_FT_EFF_Eigen_B_2__1down;
  jet_SF["FT_EFF_Eigen_B_2__1up"] = *btag_signal_jets_SF_syst_FT_EFF_Eigen_B_2__1up;
  jet_SF["FT_EFF_Eigen_B_3__1down"] = *btag_signal_jets_SF_syst_FT_EFF_Eigen_B_3__1down;
  jet_SF["FT_EFF_Eigen_B_3__1up"] = *btag_signal_jets_SF_syst_FT_EFF_Eigen_B_3__1up;
  jet_SF["FT_EFF_Eigen_B_4__1down"] = *btag_signal_jets_SF_syst_FT_EFF_Eigen_B_4__1down;
  jet_SF["FT_EFF_Eigen_B_4__1up"] = *btag_signal_jets_SF_syst_FT_EFF_Eigen_B_4__1up;
  jet_SF["FT_EFF_Eigen_B_5__1down"] = *btag_signal_jets_SF_syst_FT_EFF_Eigen_B_5__1down;
  jet_SF["FT_EFF_Eigen_B_5__1up"] = *btag_signal_jets_SF_syst_FT_EFF_Eigen_B_5__1up;
  jet_SF["FT_EFF_Eigen_B_6__1down"] = *btag_signal_jets_SF_syst_FT_EFF_Eigen_B_6__1down;
  jet_SF["FT_EFF_Eigen_B_6__1up"] = *btag_signal_jets_SF_syst_FT_EFF_Eigen_B_6__1up;
  jet_SF["FT_EFF_Eigen_B_7__1down"] = *btag_signal_jets_SF_syst_FT_EFF_Eigen_B_7__1down;
  jet_SF["FT_EFF_Eigen_B_7__1up"] = *btag_signal_jets_SF_syst_FT_EFF_Eigen_B_7__1up;
  jet_SF["FT_EFF_Eigen_B_8__1down"] = *btag_signal_jets_SF_syst_FT_EFF_Eigen_B_8__1down;
  jet_SF["FT_EFF_Eigen_B_8__1up"] = *btag_signal_jets_SF_syst_FT_EFF_Eigen_B_8__1up;
  jet_SF["FT_EFF_Eigen_C_0__1down"] = *btag_signal_jets_SF_syst_FT_EFF_Eigen_C_0__1down;
  jet_SF["FT_EFF_Eigen_C_0__1up"] = *btag_signal_jets_SF_syst_FT_EFF_Eigen_C_0__1up;
  jet_SF["FT_EFF_Eigen_C_1__1down"] = *btag_signal_jets_SF_syst_FT_EFF_Eigen_C_1__1down;
  jet_SF["FT_EFF_Eigen_C_1__1up"] = *btag_signal_jets_SF_syst_FT_EFF_Eigen_C_1__1up;
  jet_SF["FT_EFF_Eigen_C_2__1down"] = *btag_signal_jets_SF_syst_FT_EFF_Eigen_C_2__1down;
  jet_SF["FT_EFF_Eigen_C_2__1up"] = *btag_signal_jets_SF_syst_FT_EFF_Eigen_C_2__1up;
  jet_SF["FT_EFF_Eigen_C_3__1down"] = *btag_signal_jets_SF_syst_FT_EFF_Eigen_C_3__1down;
  jet_SF["FT_EFF_Eigen_C_3__1up"] = *btag_signal_jets_SF_syst_FT_EFF_Eigen_C_3__1up;
  jet_SF["FT_EFF_Eigen_Light_0__1down"] = *btag_signal_jets_SF_syst_FT_EFF_Eigen_Light_0__1down;
  jet_SF["FT_EFF_Eigen_Light_0__1up"] = *btag_signal_jets_SF_syst_FT_EFF_Eigen_Light_0__1up;
  jet_SF["FT_EFF_Eigen_Light_1__1down"] = *btag_signal_jets_SF_syst_FT_EFF_Eigen_Light_1__1down;
  jet_SF["FT_EFF_Eigen_Light_1__1up"] = *btag_signal_jets_SF_syst_FT_EFF_Eigen_Light_1__1up;
  jet_SF["FT_EFF_Eigen_Light_2__1down"] = *btag_signal_jets_SF_syst_FT_EFF_Eigen_Light_2__1down;
  jet_SF["FT_EFF_Eigen_Light_2__1up"] = *btag_signal_jets_SF_syst_FT_EFF_Eigen_Light_2__1up;
  jet_SF["FT_EFF_Eigen_Light_3__1down"] = *btag_signal_jets_SF_syst_FT_EFF_Eigen_Light_3__1down;
  jet_SF["FT_EFF_Eigen_Light_3__1up"] = *btag_signal_jets_SF_syst_FT_EFF_Eigen_Light_3__1up;
  jet_SF["FT_EFF_extrapolation__1down"] = *btag_signal_jets_SF_syst_FT_EFF_extrapolation__1down;
  jet_SF["FT_EFF_extrapolation__1up"] = *btag_signal_jets_SF_syst_FT_EFF_extrapolation__1up;
  jet_SF["FT_EFF_extrapolation_from_charm__1down"] = *btag_signal_jets_SF_syst_FT_EFF_extrapolation_from_charm__1down;
  jet_SF["FT_EFF_extrapolation_from_charm__1up"] = *btag_signal_jets_SF_syst_FT_EFF_extrapolation_from_charm__1up;

  /*
  jet_SF["FT_EFF_B_systematics__1down"]= *btag_signal_jets_SF_syst_FT_EFF_B_systematics__1down;     
  jet_SF["FT_EFF_B_systematics__1up"]= *btag_signal_jets_SF_syst_FT_EFF_B_systematics__1up;       
  jet_SF["FT_EFF_C_systematics__1down"]= *btag_signal_jets_SF_syst_FT_EFF_C_systematics__1down;     
  jet_SF["FT_EFF_C_systematics__1up"]= *btag_signal_jets_SF_syst_FT_EFF_C_systematics__1up;       
  jet_SF["FT_EFF_Light_systematics__1down"]= *btag_signal_jets_SF_syst_FT_EFF_Light_systematics__1down;
  jet_SF["FT_EFF_Light_systematics__1up"]= *btag_signal_jets_SF_syst_FT_EFF_Light_systematics__1up; 
  jet_SF["JET_JvtEfficiency__1down"]= *jvt_signal_jets_SF_syst_JET_JvtEfficiency__1down; 
  jet_SF["JET_JvtEfficiency__1up"]= *jvt_signal_jets_SF_syst_JET_JvtEfficiency__1up;     
  jet_SF["JET_fJvtEfficiency__1down"]= *fjvt_signal_jets_SF_syst_JET_fJvtEfficiency__1down; 
  jet_SF["JET_fJvtEfficiency__1up"]= *fjvt_signal_jets_SF_syst_JET_fJvtEfficiency__1up;
  */ 

  return jet_SF; 

}



vector<Double_t> EventSelector::GetEffBinning(){

  vector<Double_t> xbins;
  xbins.push_back(0.0);

  Double_t binedge = 10.0;
  xbins.push_back(binedge);

  while(binedge < 10000.0){

    Double_t delta;
    if (binedge < 50.0)
      delta = 1.0;
    else if (binedge < 100.0)
      delta = 1.0;
    else if (binedge < 120.0)
      delta = 2.5;
    else if (binedge < 200.0)
      delta = 10.0;
    else if (binedge < 1000.0)
      delta = 50.0;
    else
      delta = 1000.0;

    binedge += delta;
    xbins.push_back(binedge);
  }

  return xbins;
}

