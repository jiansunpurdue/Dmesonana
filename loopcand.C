using std::vector;
using std::string;
#include <TTree.h>
#include <TFile.h>
#include <TChain.h>
#include <TMath.h>
#include <iostream>
#include <TNtuple.h>
#include <TVector3.h>
#include <TLorentzVector.h>
#include <cmath>
#include <vector>
#include <TString.h>
#include "loopcand.h"

void fillTree(int j, bool isPbPb, bool isMC)
{
  if(isPbPb)
    {
      Jet55 = Event_Jet55;
      Jet55_Prescl = Event_Jet55_Prescl;
      Jet65 = Event_Jet65;
      Jet65_Prescl = Event_Jet65_Prescl;
      Jet80 = Event_Jet80;
      Jet80_Prescl = Event_Jet80_Prescl;
    }
  else
    {
      //Jet95 = Event_Jet95;
      //Jet95_Prescl = Event_Jet95_Prescl;
      Jet20 = Event_Jet20;
      Jet20_Prescl = Event_Jet20_Prescl;
      Jet40 = Event_Jet40;
      Jet40_Prescl = Event_Jet40_Prescl;
      Jet60 = Event_Jet60;
      Jet60_Prescl = Event_Jet60_Prescl;
      Jet100 = Event_Jet100;
      Jet100_Prescl = Event_Jet100_Prescl;
    }
  MinBias = Event_MinBias;
  MinBias_Prescl = Event_MinBias_Prescl;    
  maxJetTrgPt = Event_maxJetTrgPt;
  trigweight = Event_trigweight;
  pthatweight = Event_pthatweight;
  ndcand = Event_ndcand;
  dtype = Event_dtype->at(j);
  passingcuts = Event_passingcuts->at(j);
  dcandmass = Event_dcandmass->at(j);
  dcandpt = Event_dcandpt->at(j);
  dcandeta = Event_dcandeta->at(j);
  dcandphi = Event_dcandphi->at(j);
  dcandffls3d = Event_dcandffls3d->at(j);
  dcandalpha = Event_dcandalpha->at(j);
  dcandfprob = Event_dcandfprob->at(j);
  dcandfchi2 = Event_dcandfchi2->at(j);
  dcanddau1eta = Event_dcanddau1eta->at(j);
  dcanddau2eta = Event_dcanddau2eta->at(j);
  dcanddau1pt = Event_dcanddau1pt->at(j);
  dcanddau2pt = Event_dcanddau2pt->at(j);
  if(isMC)
    {
      matchedtogen = Event_matchedtogen->at(j);
      dcandmatchedpdg = Event_dcandmatchedpdg->at(j);
      nongendoublecounted = Event_nongendoublecounted->at(j);
      dcandmatchedpt = Event_dcandmatchedpt->at(j);
      dcandmatchedeta = Event_dcandmatchedeta->at(j);
      dcandmatchedphi = Event_dcandmatchedphi->at(j);
      dcandmatchnofdau = Event_dcandmatchnofdau->at(j);
      dcandmatcheddau1pt = Event_dcandmatcheddau1pt->at(j);
      dcandmatcheddau2pt = Event_dcandmatcheddau2pt->at(j);
    }
  // = Event_->at(j);
}

int loopcand(string infile="/afs/cern.ch/work/j/jisun/public/Dmesonana/Dmesonana_hiforest_D0filtered_2760GeV_D0pt3_pthat015305080120_1220_1222_all.root",
	     string outfile="/afs/cern.ch/work/w/wangj/public/dmeson/candbase/Dmesonana_hiforest_D0filtered_2760GeV_D0pt3_pthat015305080120_1220_1222_all_Candbase.root",
	     bool isPbPb=false,
	     bool isMC=true)
{
  const char* infname;
  const char* outfname;

  infname = infile.c_str();
  outfname = outfile.c_str();

  TFile* inf = new TFile(infname);
  TTree* root = (TTree*)inf->Get("recodmesontree");
  TFile* outf = new TFile(outfname,"recreate");
  setBranch(root,isPbPb,isMC);
  TTree* nt0 = new TTree("ntDzero","");
  buildBranch(nt0);

  cout<<"--- Tree building finished ---"<<endl;

  Long64_t nentries = root->GetEntries();
  //nentries = 10000;

  int i=0,j=0;
  for(i=0;i<nentries;i++)
    {
      root->GetEntry(i);
      if (i%10000==0) cout <<i<<" / "<<nentries<<endl;
      for(j=0;j<Event_ndcand;j++) 
	{
	  fillTree(j,isPbPb,isMC);
	  nt0->Fill();
	}      
    }
  outf->Write();
  outf->Close();
  return 1;
}

