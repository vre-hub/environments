### Introduction 

This TSelector code is made for reading ntuples produced with the DileptonST code found here: https://gitlab.cern.ch/atlas-phys/exot/lpx/exot-2020-10-projects/dileptonstexclusivesearch

The purpose of the selector is to do read the ntuples and do everything that needs to be done on an event-by-event basis, e.g. calculate kinematic variables, do event selections and fill histograms.  

Documentation for the TSelector class can be found here: https://root.cern.ch/doc/master/classTSelector.html

### 1) EventSelector.h 

In the header file all your histograms and functions are declared, as well as readers to access the variables in the ntuples. 

If you want to add a new histogram called `h_jet_pt` you need to add a line like this to the header file: 
```
map<TString, TH1*> h_jet_pt; //!
```              
Notice that we declare the histograms in maps, which is the C++ equivalent of Python dictionaries.

The variable readers are automatically declared when generating this class from an ntuple, so you do not need to worry about them unless the structure of the nutples changes. For example, if a variable has been added/removed from the ntuples you have to add/remove the corresponding line to the header file.   

### 2) EventSelector.C

This file contains the implementation of the functions defined in the header file. The three most important ones to mention here are the following: 

#### a) Begin (or SlaveBegin) 

This function is only called once before we start looping through all the events. In this function we specify a list of the all the channels we want to consider called `all_channels`. (A _channel_ in this context just means a specific event selection.) Then we loop through the channel list, and for each channel we add a histogram to the histogram map decleared in the header file. Here you also specify the range and binning of the histograms. (Several other things can also be done in this function, but these are maybe the two most important things to notice.) 
#### b) Process 

This function is called for each event in the ntuple. Here we read out the variables in the ntuple, calculate more high-level variables, do event selections, calculate event weights, and fill the histograms. 
 
If a variable is stored as an array in the ntuple you can read out the elements e.g. like this: 
```
Float_t el_pt = el_pt[0];  
```
Variables that are not arrays can be read e.g. like this: 
```
Float_t met = *met_tst_et/1000.; # Divide by 1000 to get GeV as unit  
```
Notice that the use of TLorentzVector's can be very handy for kinematics handling. 

After we have extracted/calculated the variables we need we can do our event selection. The idea here is that we check if the event has passed a certain set of selection criteria corresponding to one of the channels we put in the `all_channels` list. For example, if we have channel called `ee_CR`, and that this channel is defined by requiring events to have MET less than 100 GeV, we should do the following:  
```
if(met<100){passed_channels.push_back("ee_CR"); }   
```
When we fill the histograms we loop through the list called `passed_channels`, so that we only fill the histograms for the channels that are satisfied by this particular event.   

#### c) Terminate 

This function is called at the end of the job, and here we write the histograms to file, and print out cutflows if desired. Notice that if we are running on multiple background files we typically want to write to file and/or print cutflows for each of these. This is then done in Process, by checking if the dataset ID has changed. Notice also that if you want to print the cutflow the variable do_cutflow must be set to 1.  

### 3) runSelector.py  

This is the script we will be running in the terminal. In this script the ntuples are put together in a so-called TChain, and the TSelector are then called to run on this TChain. You will need to give this script some input arguments. These arguments are briefly explained in the file. A terminal command for running on MC samples could for example look like this: 
```
python runSelector --data mc16a --bkgs all_bkg --doSyst 1 --isHepp01 1
```
The line above indicate that you want to run on samples from mc16a, you want to run on the list of samples specified as all_bkg (see list definitions in the script), and you want to include systematics, and you are running on hepp01. Notice that if you want to include systematics the variable do_syst in EventSelector.C must also be set to 1. A command for running on data could look like this:   
```
python runSelector --data data18
```

#### Parallel processing 

For parallel running of jobs you can use the script **prunSelector.py**. In this script we make one TChain (and hence one job) for each sample, instead of putting all samples in one big TChain. This is particularly useful if we have a machine with many of CPUs, such as hepp01. 
