from collections import OrderedDict
import os
from ROOT import TFile

lumi = {}
lumi['mc16a'] = 3219.56 + 32988.1
lumi['mc16d'] = 44307.4
lumi['mc16e'] = 58450.1

SOW_sig = OrderedDict()
sig_ID = -1;
for camp in lumi.keys():

    SOW_sig[camp] = OrderedDict()
    
    d = os.listdir('ntuples/'+camp)[0]
    files = os.listdir('ntuples/'+camp+'/'+d)
    if len(files) != 1:
        print( 'ERROR: Not exactly one ntuple file in', 'ntuples/'+camp+'/'+d )

    f = 'ntuples/'+camp+'/'+d+'/'+files[0]
    tf = TFile(f);
    h = tf.Get("histoEventCount")
    ID = f.split('.')[4]
    SOW_sig[camp][ID] = h.GetBinContent(1)
    
    print( 'Sum of weights for DSID = ', ID, ',', camp, ': ', SOW_sig[camp][ID] )
    sig_ID = int(ID)


systematics = ["EG_RESOLUTION_ALL__1down", "EG_RESOLUTION_ALL__1up", "EG_SCALE_AF2__1down", "EG_SCALE_AF2__1up", "EG_SCALE_ALL__1down", "EG_SCALE_ALL__1up", "JET_BJES_Response__1up", "JET_EffectiveNP_1__1up", "JET_EffectiveNP_2__1up", "JET_EffectiveNP_3__1up", "JET_EffectiveNP_4__1up", "JET_EffectiveNP_5__1up", "JET_EffectiveNP_6__1up", "JET_EffectiveNP_7__1up", "JET_EffectiveNP_8restTerm__1up", "JET_EtaIntercalibration_Modelling__1up", "JET_EtaIntercalibration_NonClosure_2018data__1up", "JET_EtaIntercalibration_NonClosure_highE__1up", "JET_EtaIntercalibration_NonClosure_negEta__1up", "JET_EtaIntercalibration_NonClosure_posEta__1up", "JET_EtaIntercalibration_TotalStat__1up", "JET_Flavor_Composition__1up", "JET_Flavor_Response__1up", "JET_JER_DataVsMC_MC16__1up", "JET_JER_EffectiveNP_1__1up", "JET_JER_EffectiveNP_2__1up", "JET_JER_EffectiveNP_3__1up", "JET_JER_EffectiveNP_4__1up", "JET_JER_EffectiveNP_5__1up", "JET_JER_EffectiveNP_6__1up", "JET_JER_EffectiveNP_7restTerm__1up", "JET_Pileup_OffsetMu__1up", "JET_Pileup_OffsetNPV__1up", "JET_Pileup_PtTerm__1up", "JET_Pileup_RhoTopology__1up", "JET_PunchThrough_MC16__1up", "JET_SingleParticle_HighPt__1up", "JET_JER_DataVsMC_AFII__1up", "JET_RelativeNonClosure_AFII__1up", "MUON_ID__1down", "MUON_ID__1up", "MUON_MS__1down", "MUON_MS__1up", "MUON_SAGITTA_DATASTAT__1down", "MUON_SAGITTA_DATASTAT__1up", "MUON_SAGITTA_RESBIAS__1down", "MUON_SAGITTA_RESBIAS__1up", "MUON_SCALE__1down", "MUON_SCALE__1up", "MET_SoftTrk_ResoPara", "MET_SoftTrk_ResoPerp", "MET_SoftTrk_Scale__1down", "MET_SoftTrk_Scale__1up"]

# Fill histograms and scale to luminosity and cross section 
def fill_hist(infile, h, h_name, DSID, h_type, mc_cmp, var, syst="", is2D=False, doInputBinning=False):
        
    h_temp = infile.Get(h_name).Clone('h_temp')

    if syst!="" and h_temp.GetEntries()==0:
        new_infile = TFile( (infile.GetName()).replace(".syst", "") ) 
        new_h_name = h_name.replace("_"+syst, "")
        h_temp = new_infile.Get(new_h_name).Clone('h_temp')

    N = 0 
    if h_type == 'sig': 
        N = SOW_sig[mc_cmp][str(DSID)] 
    L = lumi[mc_cmp]*1.0e-3

    sf = L/N
    
    if N == 1 or L == 0:
        print( "Something wrong: %d" %DSID )
    
    if not "mcw" in var: 
        h_temp.Scale(sf) 

    if is2D: 
        for x in range(0, h_temp.GetNbinsX()+1): 
            for y in range(0, h_temp.GetNbinsY()+1): 
                if h_temp.GetBinContent(x,y)<0: 
                    h_temp.SetBinContent(x,y,0)
    else: 
        for x in range(h_temp.GetNbinsX()+1): 
            if h_temp.GetBinContent(x)<0: 
                h_temp.SetBinContent(x,0)

    if not h.GetName(): 
        h=h_temp   
    else: 
        h.Add(h_temp) 

    return h  

