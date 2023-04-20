from common import lumi,SOW_sig

infile_a = open("Signal_info_mc16a.txt", "r")
infile_d = open("Signal_info_mc16d.txt", "r")
infile_e = open("Signal_info_mc16e.txt", "r")
infile_a.readline() 
infile_d.readline() 
infile_e.readline() 

xsec = {} 
sow_a = {}
sow_d = {}
sow_e = {}
sow_all = {}
names = {}

regions = ["tot", "bin1", "bin2", "bin3"]
regions_i = {"tot":3, "bin1":4, "bin2":5, "bin3":6} 

for r in regions: 
    sow_a[r] = {}
    sow_d[r] = {}
    sow_e[r] = {}
    sow_all[r] = {}

for line in infile_a.readlines(): 
    line = line.rstrip('\n') 
    this_line = line.split(" ") 
    while("" in this_line): 
        this_line.remove("")
    name = this_line[1]
    ID = this_line[0] 
    names[ID] = name
    xsec[ID] = float(this_line[2])
    for r in regions:  
        sow_a[r][ID] = float(this_line[regions_i[r]])*lumi["mc16a"]*xsec[ID]/(SOW_sig["mc16a"][ID])
        sow_all[r][ID] = float(this_line[regions_i[r]])*lumi["mc16a"]*xsec[ID]/(SOW_sig["mc16a"][ID])

for line in infile_d.readlines(): 
    line = line.rstrip('\n') 
    this_line = line.split(" ") 
    while("" in this_line): 
        this_line.remove("")
    name = this_line[1]
    ID = this_line[0] 
    for r in regions:  
        sow_d[r][ID] = float(this_line[regions_i[r]])*lumi["mc16d"]*xsec[ID]/(SOW_sig["mc16d"][ID])
        sow_all[r][ID] += float(this_line[regions_i[r]])*lumi["mc16d"]*xsec[ID]/(SOW_sig["mc16d"][ID])

for line in infile_e.readlines(): 
    line = line.rstrip('\n') 
    this_line = line.split(" ") 
    while("" in this_line): 
        this_line.remove("")
    name = this_line[1]
    ID = this_line[0] 
    for r in regions:  
        sow_e[r][ID] = float(this_line[regions_i[r]])*lumi["mc16e"]*xsec[ID]/(SOW_sig["mc16e"][ID])
        sow_all[r][ID] += float(this_line[regions_i[r]])*lumi["mc16e"]*xsec[ID]/(SOW_sig["mc16e"][ID])


outfile = open("Signal_info.txt", "w")
outfile.write("ID       Name                                      Cross section   SOW (mc16a)   SOW (mc16d)   SOW (mc16e)  SOW (all)  SOW (bin 1)  SOW (bin 2)   SOW (bin 3) \n")
for ID in sorted(names.keys()): 
    outfile.write("%s   %s" %(ID, names[ID]) )
    outfile.write("      %s" %xsec[ID])
    outfile.write("      %.5f" %float(sow_a["tot"][ID]))
    outfile.write("      %.5f" %float(sow_d["tot"][ID]))
    outfile.write("      %.5f" %float(sow_e["tot"][ID]))
    for r in regions:
        outfile.write("      %.5f" %float(sow_all[r][ID]))
    outfile.write("\n")

outfile.close() 
