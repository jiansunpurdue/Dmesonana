#include <string>
#include <vector>
#include <map>
#include <iostream>
#include <TFile.h>
#include <TH1F.h>
#include <TMath.h>
#include <TF1.h>
#include <TNamed.h>
#include <TNtuple.h>
#include <TTree.h>
#include <TMath.h>
#include <TCanvas.h>
#include <TStyle.h>
#include <TLatex.h>
#include "Math/MinimizerOptions.h"
#include <TLegend.h>

#define MAXGENDMESON 100

using namespace std;

void MCDataComparison(int isData=0, int isgenmatched=0)
{

  TString inputfilename;

  if (isData==0){
    inputfilename="/afs/cern.ch/work/j/jisun/public/Dmesonana/Dmesonana_hiforest_D0filtered_2760GeV_D0pt3_pthat015305080120_1220_1222_all.root";
  }
  if (isData==1){
    inputfilename="/afs/cern.ch/work/j/jisun/public/Dmesonana/Dmesonana_PPJet_Jettrig_obj_pt0p5_d0dstar_alpha1p0_highpurity_1209_all.root";
  }

  TH1F* hPt = new TH1F("hPt","hPt",50,0.,100.);
  TH1F* hDecaySign = new TH1F("hDecaySign","hDecaySign",50,0.,100.);
  TH1F* hCosPointing = new TH1F("hCosPointing","hCosPointing",50,-1.5,1.5);
  TH1F* hVertexProb = new TH1F("hVertexProb","hVertexProb",50,0,1.);
  TH1F* hMassD = new TH1F("hMassD","hMassD",100,1.7,1.99);
  
  TFile * input= new TFile(inputfilename.Data());
  TTree * recodmesontree= (TTree *) input->Get("recodmesontree");  
  if(isData==0){
    TTree * gendmesontree = (TTree *) input->Get("gendmesontree");
    recodmesontree->AddFriend(gendmesontree);
  }

  int MinBias,MinBias_Prescl,Jet20,Jet20_Prescl,Jet40,Jet40_Prescl,Jet60,Jet60_Prescl,Jet80,Jet80_Prescl,Jet100,Jet100_Prescl;
  int ndcand,hiBin;
  double pthatweight,trigweight;
  float maxJetTrgPt;
  vector<int> *dtype = 0, *passingcuts = 0;
  vector<float> *dcandmass = 0, *dcandpt = 0, *dcandeta = 0, *dcandphi = 0;
  vector<float> *dcandffls3d = 0, *dcandalpha = 0, *dcandfprob = 0, *dcandfchi2 = 0;
  vector<float> *dcanddau1eta = 0, *dcanddau2eta = 0;
  vector<int>   *matchedtogen = 0, *dcandmatchedpdg = 0, *nongendoublecounted = 0;
  vector<float> *dcandmatchedpt = 0, *dcandmatchedeta = 0, *dcandmatchedphi = 0, *dcandmatchnofdau = 0;

  recodmesontree->SetBranchAddress("MinBias", &MinBias);
  recodmesontree->SetBranchAddress("MinBias_Prescl", &MinBias_Prescl);
  recodmesontree->SetBranchAddress("Jet20", &Jet20);
  recodmesontree->SetBranchAddress("Jet20_Prescl", &Jet20_Prescl);
  recodmesontree->SetBranchAddress("Jet40", &Jet40);
  recodmesontree->SetBranchAddress("Jet40_Prescl", &Jet40_Prescl);
  recodmesontree->SetBranchAddress("Jet60", &Jet60);
  recodmesontree->SetBranchAddress("Jet60_Prescl", &Jet60_Prescl);
  recodmesontree->SetBranchAddress("Jet80", &Jet80);
  recodmesontree->SetBranchAddress("Jet80_Prescl", &Jet80_Prescl);
  recodmesontree->SetBranchAddress("Jet100", &Jet100);
  recodmesontree->SetBranchAddress("Jet100_Prescl", &Jet100_Prescl);
  recodmesontree->SetBranchAddress("maxJetTrgPt", &maxJetTrgPt);
  recodmesontree->SetBranchAddress("pthatweight", &pthatweight);
  recodmesontree->SetBranchAddress("trigweight", &trigweight);
  recodmesontree->SetBranchAddress("ndcand", &ndcand);
  recodmesontree->SetBranchAddress("dtype", &dtype);
  recodmesontree->SetBranchAddress("passingcuts", &passingcuts);
  recodmesontree->SetBranchAddress("dcandmass", &dcandmass);
  recodmesontree->SetBranchAddress("dcandpt", &dcandpt);
  recodmesontree->SetBranchAddress("dcandeta", &dcandeta);
  recodmesontree->SetBranchAddress("dcandphi", &dcandphi);
  recodmesontree->SetBranchAddress("dcandffls3d", &dcandffls3d);
  recodmesontree->SetBranchAddress("dcandalpha", &dcandalpha);
  recodmesontree->SetBranchAddress("dcandfprob", &dcandfprob);
  recodmesontree->SetBranchAddress("dcandfchi2", &dcandfchi2);
  if(isData==0){
  recodmesontree->SetBranchAddress("matchedtogen", &matchedtogen);
  recodmesontree->SetBranchAddress("nongendoublecounted", &nongendoublecounted);
  recodmesontree->SetBranchAddress("dcandmatchedpt", &dcandmatchedpt);
  recodmesontree->SetBranchAddress("dcandmatchedeta", &dcandmatchedeta);
  recodmesontree->SetBranchAddress("dcandmatchedphi", &dcandmatchedphi);
  }

  bool isselectedgenmatched=false;

  int maxevents;
  if(isData==0) maxevents=recodmesontree->GetEntries();
  else maxevents=1000000;
  for ( int entry = 0; entry<maxevents; entry++ ){
    recodmesontree->GetEntry(entry);
    if( !MinBias && !Jet20 && !Jet40 && !Jet60 && !Jet80 && !Jet100 ) continue;
    if( ndcand != dtype->size() || ndcand != passingcuts->size() || ndcand != dcandmass->size() || ndcand != dcandpt->size() ) cout << "Error!!!!!!!!" << endl;

    for( int icand = 0; icand < ndcand; icand++ ){
      
      if(dcandmass->at(icand)< 1.80 || dcandmass->at(icand)> 1.92) continue;
      if(isData==1) isselectedgenmatched=true;
      else {isselectedgenmatched=(bool)matchedtogen->at(icand);}
      
      if(isgenmatched==1 && !isselectedgenmatched) continue;
                  
      hMassD->Fill(dcandmass->at(icand));
      hPt->Fill(dcandpt->at(icand));
      hDecaySign->Fill(dcandffls3d->at(icand));
      hCosPointing->Fill(TMath::Cos(dcandalpha->at(icand)));
      hVertexProb->Fill(dcandfprob->at(icand));
      
    }
  }  
  TString outputfilename=Form("results/output_isData%d_genmatched%d.root",isData,isgenmatched);
  TFile*foutput=new TFile(outputfilename.Data(),"RECREATE");
  foutput->cd();
  hPt->Write();
  hDecaySign->Write();
  hCosPointing->Write();
  hVertexProb->Write();
  hMassD->Write();
  
  delete foutput;

}