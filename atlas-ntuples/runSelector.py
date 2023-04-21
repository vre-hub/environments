import ROOT
from ROOT import *
import sys, os, time, argparse, shutil 

t0 = time.time() 

parser = argparse.ArgumentParser()
parser.add_argument('--data', type=str, default="mc16a", help="Data to consider (For MC: mc16a/d/e, for data: data15/16/17/18 or all_data)")
parser.add_argument('--bkgs', type=str, default="", help="Backgrounds IDs to run over")
parser.add_argument('--isHepp01', type=int, default=0, help="Run on hepp01?")
parser.add_argument('--prod_date', type=str, default="oct2022v2", help="Which ntuple production round to use")

parser.add_argument('--doSyst', type=int, default=0, help="Run on systematics?")
parser.add_argument('--doTruth', type=int, default=0, help="Do truth stuff?")
parser.add_argument('--doCutflow', type=int, default=0, help="Do cutflow?")
parser.add_argument('--doFakes', type=int, default=0, help="Do fakes?")
parser.add_argument('--doLoose', type=int, default=0, help="Do loose selections?")

args = parser.parse_args()

data = args.data # Should be "data15/16/17/18" or "mc16a/d/e" 
bkgs = args.bkgs 
isHepp01 = args.isHepp01
prod_date = args.prod_date

doTruth = args.doTruth
doCutflow = args.doCutflow 
doSyst = args.doSyst
doFakes = args.doFakes 
doLoose = args.doLoose


# Set input and output paths 
input_dir = '' 
hist_path = "Histograms"

if 'mc' in data: 
        input_dir = '/scratch3/MiniTrees/Nominal/MC/'+data+'/' #local
if 'data' in data: 
        input_dir = '/scratch3/MiniTrees/Nominal/Data/'+data+'/' #local

if doSyst == 1 and bkgs != 'recast':
        input_dir = input_dir.replace("Nominal", "Systematics") 
        hist_path = "/scratch/"+hist_path
if isHepp01 == 1:
        input_dir = input_dir.replace("scratch3", "scratch")
if doSyst == 0 and isHepp01==1: 
        input_dir = input_dir.replace("Nominal","Nominal_"+prod_date) 

# DSIDs corresponding to the --bkgs argument         
IDs = {} 
IDs["DYmumu_incl"] = [364100, 364101, 364102, 364103, 364104, 364105, 364106, 364107, 364108, 364109, 364110, 364111, 364112, 364113]
IDs["DYee_incl"] = [364114, 364115, 364116, 364117, 364118, 364119, 364120, 364121, 364122, 364123, 364124, 364125, 364126, 364127]
IDs["DYmumu_100"] = [366300, 366301, 366302, 366303, 366304, 366305, 366306, 366307, 366308]
IDs["DYee_100"] = [366309, 366310, 366312, 366313, 366315]
IDs["DYtautau"] = [364128, 364129, 364130, 364131, 364132, 364133, 364134, 364135, 364136, 364137, 364138, 364139, 364140, 364141] 
IDs["DYee_PH"] = [301000, 301001, 301002, 301003, 301004, 301005, 301006, 301007, 301008, 301009, 301010, 301011, 301012, 301013, 301014, 301015, 301016, 301017, 301018, 361106]
IDs["DYmumu_PH"] = [301020, 301021, 301022, 301023, 301024, 301025, 301026, 301027, 301028, 301029, 301030, 301031, 301032, 301033, 301034, 301035, 301036, 301037, 301038, 361107] 
IDs["Top"] = [410470, 410472, 410644, 410645, 410648, 410649, 410658, 410659, 410633, 410634, 410635, 410636, 410637] 
IDs["TTbar_dil"] = [410472]
IDs["TTbar_nonallhad"] = [410470]
IDs["ST"] = [410644, 410645,410646, 410647, 410648, 410649, 410658, 410659]
IDs["Diboson"] = [363356, 363358, 363359, 363360, 363489, 364250, 364253, 364254, 364255]
IDs["Wmunu"] = [364156, 364157, 364158, 364159, 364160, 364161, 364162, 364163, 364164, 364165, 364166, 364167, 364168, 364169]
IDs["Wenu"] = [364170, 364171, 364172, 364173, 364174, 364175, 364176, 364177, 364178, 364179, 364180, 364181, 364182, 364183]
IDs["Wtaunu"] = [364184, 364185, 364186, 364187, 364188, 364189, 364190, 364191, 364192, 364193, 364194, 364195, 364196, 364197]
IDs["DY_low"] = [364198, 364199, 364200, 364201, 364202, 364203, 364204, 364205, 364206, 364207, 364208, 364209, 364210, 364211, 364212, 364213, 364214, 364215]
IDs["sig_high"] = [500339, 500340, 500341, 500342, 500343, 500345, 500346, 500347, 500348, 500349, 500350, 500351, 500352, 500353, 500354, 500355, 500356, 500357, 500358, 500359, 500360, 500361, 500362, 500363, 500364, 500365, 500366, 500367, 500368, 500369, 500370, 500344]
IDs["sig_low"] = [506745, 506746, 506747, 506748, 506749, 506750, 506751, 506752, 506753, 506754, 506755, 506756, 506757, 506758, 506759, 506760, 506761, 506762, 506763, 506764, 506765, 506766, 506767, 506768] 

IDs["DY_all"] = IDs["DYmumu_incl"] + IDs["DYee_incl"] + IDs["DYmumu_100"] + IDs["DYee_100"] + IDs["DYtautau"] + IDs["DY_low"] #+ IDs["DYee_PH"] + IDs["DYmumu_PH"] 
IDs["W"] = IDs["Wmunu"] + IDs["Wenu"] + IDs["Wtaunu"] 
IDs["fakeMC"] = IDs["TTbar_nonallhad"]+IDs["W"] 
IDs["sig"] = IDs["sig_high"] + IDs["sig_low"] 

IDs["all_bkg"] = IDs["DY_all"]+IDs["Top"]+IDs["Diboson"]+IDs["W"]
IDs["all_MC"] = IDs["all_bkg"] + IDs["sig"]

IDs["data15"] = ["D", "E", "F", "G", "H", "J"]
IDs["data16"] = ["A", "B", "C", "D", "E", "F", "G", "I", "K", "L"]
IDs["data17"] = ["B", "C", "D", "E", "F", "H", "I", "K"]
IDs["data18"] = ["B", "C", "D", "F", "I", "K", "L", "M", "O", "Q"]

IDs["sig_test"] = [500370]
IDs["sig_test_el"] = [500370]
IDs["sig_test_mu"] = [500340]
IDs["sig_low_test"] = [506745]
IDs["bkg_test"] = [410644]
IDs["top_test"] = [410472]
IDs["data_test"] = ["D"]

# for recast, take a look in the input dir to find the DSID
if bkgs == 'recast':
        DSID = int(os.listdir('ntuples/mc16a')[0].split('.')[4])
        IDs["recast"] = [DSID]
        input_dir = 'ntuples/'+data+'/'

# Make output directories         
if not os.path.exists(hist_path):
        os.makedirs(hist_path)

if not os.path.exists(hist_path+'/'+data+'/'):
        os.makedirs(hist_path+'/'+data)

for ID in IDs[bkgs]: 
        this_path = ""
        if 'data' in data: 
                this_path = hist_path+'/'+data+'/period'+ID
        else: 
                this_path = hist_path+'/'+data+'/'+str(ID)
        if os.path.exists(this_path):
                shutil.rmtree(this_path) 
        os.makedirs(this_path)


myChain = TChain('nominal') 

for folder in sorted(os.listdir(input_dir)): 
        if not '.root' in folder: continue 
        if 'mc' in data: 
                DSID = int(folder.split('.')[4])
                if not DSID in IDs[bkgs]: continue 
        if "AFII" in folder: continue 
        print( folder )
        n_files = 0
        for filename in os.listdir(input_dir+folder): 
                n_files += 1
                #if '000001' not in filename: continue
                myChain.Add(input_dir+folder+'/'+filename)  

entries = myChain.GetEntries() 
print( "Number of events to process: %d" %entries )

isRecast = 0;
if bkgs == 'recast':
        isRecast = 1;
isAFII = 0; 

doSFSyst = 0; doCalibSyst = 0
if doSyst:
        doSFSyst = 1; doCalibSyst = 1 

option = data+"_"+str(doTruth)+"_"+str(doCutflow)+"_"+str(doSFSyst)+"_"+str(doCalibSyst)+"_"+str(doFakes)+"_"+str(doLoose)+"_"+str(isRecast)+"_"+str(isAFII) 
cachesize = 1000000000000000; 
myChain.SetCacheSize(cachesize);
myChain.AddBranchToCache("*", True);
myChain.Process("EventSelector.C+", option)

t = int( time.time()-t0 )/60.  
print( "Time spent: %.1f min" %t )

# Merge histograms 
out_path = hist_path+"/"+data+"/"
working_dir = os.getcwd() 
os.chdir(out_path) 
for folder in os.listdir("."):
        if '.root' in folder: continue 
        if 'mc' in data and not int(folder) in IDs[bkgs]: continue 
        if 'data' in data and not folder[-1] in IDs[bkgs]: continue  
        file_string = ""; file_string_r = ""; file_string_l = ""; file_string_rl = ""; file_string_s = "";  
        outfile = ""; outfile_r = ""; outfile_l = ""; outfile_rl = ""; outfile_s = "";  
        n_files = 0
        for f in os.listdir(folder):
                file_nr = (f.split('.')[2]).split('_')[-1]
                if (".real." in f) or ("fakes" in f):
                        outfile_r = f.replace("_"+file_nr, "") 
                        file_string_r+=(" "+folder+"/"+f)
                elif ".loose." in f:
                        n_files+=1 
                        outfile_l = f.replace("_"+file_nr, "") 
                        file_string_l+=(" "+folder+"/"+f)
                elif (".real_loose." in f) or (".fakes_loose." in f):
                        outfile_rl = f.replace("_"+file_nr, "") 
                        file_string_rl+=(" "+folder+"/"+f)
                elif "syst" in f: 
                        outfile_s = f.replace("_"+file_nr, "") 
                        file_string_s+=(" "+folder+"/"+f)
                else: 
                        n_files+=1 
                        outfile = f.replace("_"+file_nr, "") 
                        file_string+=(" "+folder+"/"+f)


        if outfile_r!="": 
                if os.path.exists(outfile_r): 
                        os.remove(outfile_r)
                if n_files == 1:
                        shutil.move(file_string_r.replace(" ", ""), outfile_r)
                else: 
                        os.system("hadd "+outfile_r+file_string_r)
        if outfile_l!="": 
                if os.path.exists(outfile_l): 
                        os.remove(outfile_l)
                if n_files == 1:
                        shutil.move(file_string_l.replace(" ", ""), outfile_l)
                else: 
                        os.system("hadd "+outfile_l+file_string_l)
        if outfile_rl!="": 
                if os.path.exists(outfile_rl): 
                        os.remove(outfile_rl)
                if n_files == 1:
                        shutil.move(file_string_rl.replace(" ", ""), outfile_rl)
                else: 
                                os.system("hadd "+outfile_rl+file_string_rl)
        if outfile_s!="": 
                if os.path.exists(outfile_s): 
                        os.remove(outfile_s)
                if n_files == 1:
                        shutil.move(file_string_s.replace(" ", ""), outfile_s)
                else: 
                        os.system("hadd "+outfile_s+file_string_s)
        if outfile!="": 
                if os.path.exists(outfile): 
                        os.remove(outfile)
                if n_files == 1:
                        shutil.move(file_string.replace(" ", ""), outfile)
                else: 
                        os.system("hadd "+outfile+file_string)

        shutil.rmtree(folder)

os.chdir("../")

if 'data' in data: 
        if not os.path.exists('data/'):
                os.makedirs('data')
        file_string = ""; file_string_r = ""; file_string_l = ""; file_string_rl = "";   
        outfile = ""; outfile_r = ""; outfile_l = ""; outfile_rl = ""; 
        for f in os.listdir(data): 
                period = f.split('.')[2]
                if "fakes" in f:
                        outfile_r = "data/"+f.replace("."+period, "") 
                        file_string_r+=(" "+data+"/"+f)
                elif ".loose." in f:
                        outfile_l = "data/"+f.replace("."+period, "") 
                        file_string_l+=(" "+data+"/"+f)
                elif ".fakes_loose." in f:
                        outfile_rl = "data/"+f.replace("."+period, "") 
                        file_string_rl+=(" "+data+"/"+f)
                else: 
                        outfile = "data/"+f.replace("."+period, "") 
                        file_string+=(" "+data+"/"+f)
                        
        if outfile_r!="": 
                if os.path.exists(outfile_r): 
                        os.remove(outfile_r)
                os.system("hadd "+outfile_r+file_string_r)
        if outfile_l!="": 
                if os.path.exists(outfile_l): 
                        os.remove(outfile_l)
                os.system("hadd "+outfile_l+file_string_l)
        if outfile_rl!="": 
                if os.path.exists(outfile_rl): 
                        os.remove(outfile_rl)
                os.system("hadd "+outfile_rl+file_string_rl)
        if outfile!="": 
                if os.path.exists(outfile): 
                        os.remove(outfile)
                os.system("hadd "+outfile+file_string)

        shutil.rmtree(data)

os.chdir(working_dir) 
