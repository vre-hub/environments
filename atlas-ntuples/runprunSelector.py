import os 

mc_cmps = ["mc16a", "mc16d", "mc16e"]

for mc_cmp in mc_cmps: 
    os.system("python prunSelector.py --camp "+mc_cmp+" --bkgs all_MC --isHepp01 1 --doSyst 1")

