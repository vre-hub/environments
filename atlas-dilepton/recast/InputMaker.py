import ROOT
from ROOT import * 
import os, sys, operator, argparse
from collections import OrderedDict
from common import sig_ID,fill_hist,systematics

ROOT.gROOT.SetBatch(1)
ROOT.TH1.AddDirectory(kFALSE)

# Input arguments 
parser = argparse.ArgumentParser()  
parser.add_argument('--camp', type=str, default="all", help="MC campaign") 
parser.add_argument('--chn', type=str, default="uu", help="Dilepton channel")
parser.add_argument('--cut', type=str, default="0", help="Cut to make input for")
parser.add_argument('--var', type=str, default="mll", help="Variable to make input for")
parser.add_argument('--doSyst', type=int, default=0, help="Include systematics")  
parser.add_argument('--doFid', type=int, default=0, help="Calculate fiducial acceptance")  

args = parser.parse_args() 
mc_cmp = args.camp
channel = args.chn
cut = args.cut
var = args.var
doSyst = args.doSyst
doFid = args.doFid 

# Path to histograms
hist_path = "Histograms/"
files = OrderedDict() 


#---------------------------------------#
# Make histograms and add to dictionary #
#---------------------------------------#

# Signals to consider
signal_models = ['recast']
signal_masses = ['0'] 
Sig_IDs = [sig_ID]

hists_sig = OrderedDict()  
hists_sig_syst = {}
for mass in signal_masses: 
    for mod in signal_models: 
        sig = mod 
        hists_sig[sig] = TH1F() 
        hists_sig_syst[sig] = {} 
        for syst in systematics: 
            hists_sig_syst[sig][syst] = TH1F() 

hSysNames = TH1F("hSysNames", "hSysNames", len(systematics), 1, len(systematics))  
b_sys = 0
for syst in systematics: 
    b_sys+=1 
    hSysNames.GetXaxis().SetBinLabel(b_sys, syst.replace("__1up","")) 


mc_cmp_list = [] 
if mc_cmp=="all":
        mc_cmp_list = ['mc16a', 'mc16d', 'mc16e']
else: 
        mc_cmp_list.append(mc_cmp) 

#---------------------------------#
# Read MC and fill new histograms #
#---------------------------------#

for camp in mc_cmp_list: 
    for f in os.listdir(hist_path+camp):  
        if 'syst' in f: continue
        if 'real' in f: continue 
        if "loose" in f: continue 
        if f.startswith('.'): continue 
        ID = f.split('.')[1]
        name = f.split('.')[2]
        files[ID] = name
        infile = TFile(hist_path+camp+"/"+f)
        if int(ID) in Sig_IDs:                     
            sig = 'recast'
            hists_sig[sig] = fill_hist(infile, hists_sig[sig], 'h_'+channel+'_'+cut+'_'+var, ID, 'sig', camp, var, "", False, True) 

if doSyst == 1: 
    for camp in mc_cmp_list:
        for f in os.listdir(hist_path+camp):  
            if not 'syst' in f: continue
            if "real" in f: continue 
            if "loose" in f: continue 
            if f.startswith('.'): continue
            ID = f.split('.')[1]
            infile = TFile(hist_path+camp+"/"+f) 
            name = f.split('.')[2]
            #print( f )
            for syst in systematics: 
                if ("ee" in channel) and ("MUON" in syst): continue 
                if ("uu" in channel) and ("EG" in syst): continue 
                if ("uu" in channel) and ("EL" in syst): continue 
                if int(ID) in Sig_IDs: 
                    sig = 'recast'
                    #print( 'h_'+channel+'_'+cut+'_'+syst+'_'+var )  
                    hists_sig_syst[sig][syst] = fill_hist(infile, hists_sig_syst[sig][syst], 'h_'+channel+'_'+cut+'_'+syst+'_'+var, ID, 'sig', camp, var, syst, False, True) 


if doSyst == 1: 
    for mod in hists_sig.keys():  
        for syst in hists_sig_syst[mod].keys(): 
            if ("ee" in channel) and ("MUON" in syst): continue 
            if ("uu" in channel) and ("EG" in syst): continue 
            if ("uu" in channel) and ("EL" in syst): continue
            hists_sig_syst[mod][syst].Divide(hists_sig[mod])  
            for b in range(1,hists_sig_syst[mod][syst].GetNbinsX()+1): 
                y = hists_sig_syst[mod][syst].GetBinContent(b)
                if y > 0: 
                    hists_sig_syst[mod][syst].SetBinContent(b, y-1)
                else: 
                    hists_sig_syst[mod][syst].SetBinContent(b, 0)
                hists_sig_syst[mod][syst].SetBinError(b, 0.0)


fn_chn = ""
if "uu" in channel: 
    fn_chn = "mu"
if "ee" in channel: 
    fn_chn = "el"

#-------------------#
# Make signal input #
#-------------------#

infofile = open("Signal_info.txt", "r")
infofile.readline() 

xsec = {} 
sow_i = {}
sow_cmp = {"mc16a":3, "mc16d":4, "mc16e":5, "all":6 }
for line in infofile.readlines(): 
    line = line.rstrip('\n') 
    this_line = line.split(" ") 
    while("" in this_line): 
        this_line.remove("")
    name = 'recast'
    ID = this_line[0] 
    xsec[name] = float(this_line[2])
    if doFid: 
        if "bin1" in cut: 
            sow_i[name] = float(this_line[7])
        if "bin2" in cut: 
            sow_i[name] = float(this_line[8])
        if "bin3" in cut: 
            sow_i[name] = float(this_line[9])
    else: 
        sow_i[name] = float(this_line[sow_cmp[mc_cmp]])

infofile.close()

start_bin = 0
end_bin = 0

start_bin = 1
end_bin = hists_sig['recast'].GetNbinsX()

acc = OrderedDict() 
for sig in hists_sig.keys():
    
    sow_f = hists_sig[sig].Integral(start_bin, end_bin)    
    acc[sig] = sow_f/sow_i[sig] 

hist_arrays = {}
hist_arrays_syst = {}
h_xsec = {} 
h_acc = {}  

for mod in signal_models: 
   hist_arrays[mod] = TObjArray(5)  
   hist_arrays[mod].SetName("template") 
   h_xsec[mod] = TH1F("crossSection", "crossSection", 4, 0, 4)
   h_acc[mod] = TH1F("acceptance", "acceptance", 4, 0, 4)
   hist_arrays_syst[mod] = {} 
   for syst in systematics: 
       hist_arrays_syst[mod][syst] = TObjArray(5)  
       name = "template_sys_"+syst.replace("__1up", "") 
       hist_arrays_syst[mod][syst].SetName(name)        

mass_index = {} 
mass_index = {"0":0}

for sig in hists_sig.keys():
    mass = '0'
    mod = sig
    hists_sig[sig].SetName(str(mass_index[mass])+'_'+mass) 
    hist_arrays[mod].Add(hists_sig[sig])
    h_xsec[mod].SetBinContent(mass_index[mass]+1,xsec[sig]) 
    h_acc[mod].SetBinContent(mass_index[mass]+1,acc[sig]) 
    if doSyst == 1: 
        for syst in systematics: 
            hists_sig_syst[sig][syst].SetName(str(mass_index[mass])+'_'+mass)
            if hists_sig_syst[sig][syst].GetNbinsX()>1: 
                hists_sig_syst[sig][syst].Smooth()
            hist_arrays_syst[mod][syst].Add(hists_sig_syst[sig][syst]) 

for mod in signal_models: 
    outfile_sig = TFile() 
    sig_filename = "signal_templates_"+fn_chn+"_"+mod+"_"+cut
    if not 'mll' in var: 
        sig_filename+=("_"+var) 
    if doFid: 
        sig_filename+="_fiducial"
    if doSyst: 
        sig_filename+=".syst"
    sig_filename+=".root"
    outfile_sig = TFile(sig_filename, "RECREATE")
    print( "Creating file: %s" %sig_filename )
    hist_arrays[mod].Write("template",1)
    if doSyst == 1: 
        for syst in systematics: 
            if ("ee" in channel) and ("MUON" in syst): continue 
            if ("uu" in channel) and ("EG" in syst): continue 
            if ("uu" in channel) and ("EL" in syst): continue 
            name = "template_sys_"+syst.replace("__1up", "") 
            hist_arrays_syst[mod][syst].Write(name,1)
    h_xsec[mod].Write() 
    h_acc[mod].Write() 
    outfile_sig.Close() 


