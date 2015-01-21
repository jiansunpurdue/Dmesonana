# Instructions for running D meson analysis

In this repository you can find the instructions to run the D-meson analysis code 
on top of the HiForest files. The analysis framework works in two steps.
The first step runs on the HiForest file and produce a reduced ntuple. 
The second step runs on the reduced ntuple and produce fitted spectra, efficiency
correction and cross sections.

**Set your environment**:

 * cmsrel CMSSW_5_3_24
 * cd CMSSW_5_3_24/src
 * cmsenv
 * git cms-merge-topic -u CmsHI:forest_CMSSW_5_3_20
 * git clone https://github.com/jiansunpurdue/UserCode.git
 * scram b -j20
 * cd UserCode
 * git clone https://github.com/jiansunpurdue/Dmesonana.git
 * cd ..
 
**Produce reduced ntuples**:

This step makes use of Dmesonana.cc and Dmesonana.hh. This code DOES NOT need to be compiled.
In Dmesonana.cc you can set various options:

 * savealldcand: true: if you want to save all D candidates whether passing cuts or not,
              false: just save D candidates passing cuts
 * PbPb data: isPbPb = true, others false
 * PbPb MC:   isPbPb = true, isMC = true, other false
 * pp jet triggers data: all false
 * pp jet triggers MC: isMC = true
 * pp and pPb MB data: ispppPbMB = true (does not work for pp MB now), others false
 * pPb jet triggers: ispPbJettrig = true, others false

To run it:

 * In UserCode/Dmesonana create a list.lis file in which you write the list of Forest files you 
   need to run on.
 * Ready to run: ./run_Dmesonana.sh <firstfile> <lastfile> list.lis <DmesonID>
   E.g. ./run_Dmesonana.sh 0 4 list.lis 2. In this case you run on the first 5 files (0-4) of 
   the list file list.lis with the option D0 (index=2)

**Extract spectra, efficiency, cross section ..**:

This step performs yield extraction, efficiency and trigger correction, cross sections and RAA.

 * The macros FillSpectrum.C, FillSpectrum_MC.C, FillSpectrum_pp.C, FillSpectrum_MC_pp.C 
   extract the yields in the PbPb case (data and MC) and pp case (data and MC) respectively.

 * The macro Jettrig_pp_D0eff.C calculates trigger efficiency corrections for the pp analysis
   (the PbPb analysis is ONLY done with MB events)
   It uses the output of FillSpectrum_MC_pp.C as an input.

 * The macro Spectrum_Recoeff_D0_ppPbPb.C calculates efficiency corrections and apply them to the 
   uncorrected data spectrum.
