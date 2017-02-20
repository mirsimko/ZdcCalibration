# How to use the ZDC code

All of the code is located in my folder: `/direct/star+u/msimko/ZDC`. You can copy the whole folder into
your directory (I will be calling it the base folder in this text).

## Getting the .dat files

First, you must download the .dat files which are quite big, therefore I recommend saving them on
the `gpfs01` disc on RCF (`/gpfs/mnt/gpfs01/star/pwg`). For the data transfer, I use the script
`transfer.cpp` in `/direct/star+u/msimko/ZDC/data`. It uses Data Carousel so you won't put much
pressure on the HPSS (this is good practice). You run it by typing:
```
$ root -q transfer.cpp
```
In this macro you have to change the variable
`runNumber` and where you want to put the files (variables: `Energy`, `trgSetup`, and `Workdir`).
Importantly, you must also change the number of .dat files in the run. You can find it here: 
<http://online.star.bnl.gov/RunLog/>

Now, you have to wait until your data get transfered. This can take from a couple of minutes up to a few hours.
You can monitor it here:
<https://www.star.bnl.gov/devcgi/display_accnt.cgi>. When they get transfered, running
```
$ ./ls.sh
```
in the `data` folder will create a list of the transfered files.

## Making the TTree

The analysis code is located in `StRoot` inside the base folder. First thing you need to do after you
copy the code is compiling it using
```
$ starver dev
$ cons
```
To run the code, first you have to change a few things in the `config.C` macro in the base folder. Basically all of the
directories of the code and the data i.e. `dirOut`, `seenRuns`, and `fileName`. The `seenRuns` file has to
exist so you want to create one (`$ touch seenRuns/seenRuns_run16.msimko.txt`). If you want to use the code
on the same run multiple times (e.g. you screw up the first time), you have to delete the run number in
this file. You don't have to worry
about the rest. 

You can run the code by typing:
```
$ starver dev
$ root4star -b -q ./read.C'("config.C")'
```
or you can simply use the macro prepared for this:
```
$ ./read
```
This will run the BFC chain (it can take a few minutes so this is a good time to have a coffee). When it is finished
in your `dirOut`, you will get lots of pdfs and pngs with histograms and ,most importantly, a root file in
`dirOut/histo/someFileWithRunNumber.root`. Note that all of the histograms are also saved here.

## ZDC calibration code

When a neutron hits the three towers of ZDC, the ratio of energy loss in the three towers should be 
around 6:3:1, and the ADC readout value is proportional to the energy loss. So we need to check the ADC value 
distribution of each tower and calculate the ratio between them.

The TTree, you created in the previous step, stores the ADC readout value of ZDC modules, tof-multi, and
TDC values (timing) as well. 
So the next step of ZDC cali. 
should be to read the information and plot figures.
We use some cuts in the code to extract the signal of the single neutron. In 2016, we used these cuts:

* TOF mult < 10
* ZDC ADC sum in the oposite tower < 100
* 200 < ZDC TDC (timing on both sides) < 2000

You can check the code in this repo in the files
`zdcTree.C` and `zdcTree.h`. Change the `runNumber`, `trgSetup`, and `typeEnergy` variables in `zdcTree.C`, and
the address of the input TFile in the file `zdcTree.h` (on lines 102 and 105). After this, you can run it by typing
```
$ ./run.sh $tofMultCut
```
The results should appear in the `dirOut/analysis/runNumber` folder. Now, you can fit the ZDC ADC distributions
and get the single and double neutron peaks (SNP and DNP, respectively). After you get the SNP, you can calibrate
the ZDC HV as described e.g. here <https://www.star.bnl.gov/protected/heavy/msimko/voltagesResult.pdf>.

## Creating html page for monitoring

You can also create a web page out of the results. All you have to do is running
```
$ root -l -q html_maker.cpp
```
after you change variables `RunNumber`, `trgSetup`, `typeEnergy`, and `root_file_path` in the `html_maker.cpp` file.
