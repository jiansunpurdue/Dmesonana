#ifndef Dmesonana_H
#define Dmesonana_H

#include <string>
#include <vector>
#include <map>
#include <iostream>
#include <TFile.h>
#include <TH1F.h>
#include <TNamed.h>
#include <TNtuple.h>
#include <TTree.h>
#include <TCanvas.h>
#include "DataFormats/HLTReco/interface/TriggerObject.h"
#include "./../interface/hfcand_v1.hh"

#define MAXPARTICLES 50000
#define nch 3

#define MAXGENDMESON 100

typedef std::vector<trigger::TriggerObject> trigO;
using namespace std;

class Dmesonana 
{
private:
  string filename;
  
  TFile* result;  //.. result output file name
  
  // read from input
  Int_t type;
  Float_t mass;
  Float_t fpt;
  Float_t feta;
  Float_t fphi;
  Float_t ffls3d;
  Float_t alpha;
  Float_t fprob;
  Float_t fdr;
  Float_t fchi2;
  Float_t mass_dau;
  Float_t fpt1;
  Float_t fpt2;
  Float_t feta1;
  Float_t feta2;
  Int_t   fq1;
  Int_t   fq2;
  
  vector<int>  gIndex1;
  vector<int>  gIndex2;
  vector<int>  gIndex_dau2;
  
  Int_t mult;
  Float_t genpt[MAXPARTICLES];
  Float_t geneta[MAXPARTICLES];
  Float_t genphi[MAXPARTICLES];
  Int_t genpdg[MAXPARTICLES];
  Int_t genchg[MAXPARTICLES];
  Int_t gensube[MAXPARTICLES];
  Int_t gensta[MAXPARTICLES];
  Int_t genmatchingID[MAXPARTICLES];
  Int_t gennMothers[MAXPARTICLES];
  Int_t genmotherIdx[MAXPARTICLES][200];
  Int_t gennDaughters[MAXPARTICLES];
  Int_t gendaughterIdx[MAXPARTICLES][200];
  
  Int_t pHBHENoiseFilter;
  Int_t pcollisionEventSelection;
  
  // trigger Prescl weight for each events
  Float_t maxJetTrgPt;
  Float_t maxJetTrgEta;
  Float_t maxJetTrgPhi;
  Float_t maxJetTrgMass;
  
  Float_t pthat;
  
  //trig decison and trig Prescl, for pbpb
  Int_t Jet55;
  Int_t Jet55_Prescl;
  Int_t Jet65;
  Int_t Jet65_Prescl;
  Int_t Jet80;
  Int_t Jet80_Prescl;
  Int_t Jet95;
  Int_t Jet95_Prescl;
  Int_t MinBias;
  Int_t MinBias_Prescl;
  Int_t L1_HcalHfCoincPmORBscMinBiasThresh1_BptxAND;
  Int_t L1_HcalHfCoincPmORBscMinBiasThresh1_BptxAND_Prescl;
  Int_t L1_SingleJet36_BptxAND;
  Int_t L1_SingleJet36_BptxAND_Prescl;
  Int_t L1_ETT2000;
  Int_t L1_ETT2000_Prescl;
  Int_t L1_SingleJet52_BptxAND;
  Int_t L1_SingleJet52_BptxAND_Prescl;
  
  //trig decison and trig Prescl, for pp
  Int_t Jet20;
  Int_t Jet20_Prescl;
  Int_t Jet40;
  Int_t Jet40_Prescl;
  Int_t Jet60;
  Int_t Jet60_Prescl;
  //		Int_t Jet80;            //Jet80 and MB trigger use variables for pbpb
  //		Int_t Jet80_Prescl;
  Int_t Jet100;
  Int_t Jet100_Prescl;
  //		Int_t ZeroBias;
  //		Int_t ZeroBias_Prescl;
  Int_t L1_ZeroBias;
  Int_t L1_ZeroBias_Prescl;
  Int_t L1_SingleJet16_BptxAND; //jet 20, 40
  Int_t L1_SingleJet16_BptxAND_Prescl;
  Int_t L1_SingleJet36;  //jet 60, 80, 100, 120
  Int_t L1_SingleJet36_Prescl;
  
  //just for jet triggers, used to get trig object
  //        trigO  *Jettrig_trigObject[NJETTRIG];
  //        Double_t trigPt[NJETTRIG][100];
  //        Double_t trigEta[NJETTRIG][100];
  //        Double_t trigPhi[NJETTRIG][100];
  
  
private: 
  //.. forest tree used in the analyses
  TTree *genparticletree;
  TTree *hftree;  
  TTree *HltTree;
  TTree *jetObjTree;
  TTree * jettree;
  TTree * skimtree;
  hfcand_v1* hfcandidate;
  
private:
  //output trees
  TTree * gendmesontree;
  TTree * recodmesontree;
  
  Int_t    ngend;
  Double_t weight_pthat;
  Float_t  dpt;
  Float_t  deta;
  Float_t  dphi;
  Int_t    dpdg;
  Int_t    dnofdau;
  Float_t  pt_ddau[3];
  Float_t  eta_ddau[3];
  Float_t  phi_ddau[3];
  Int_t    pdg_ddau[3];
  Int_t    dnofmom;
  Int_t    pdg_dmom;
  Float_t  pt_dmom;
  Int_t    pdg_Bmom;
  Float_t  pt_Bmom;
  
  Int_t ndcand;
  Int_t hiBin;
  Double_t trigweight;
  Double_t pthatweight;
  vector<int> dtype, passingcuts;
  vector<float> dcandmass, dcandpt, dcandeta, dcandphi, dcandffls3d, dcandalpha, dcandfprob, dcandfchi2;
  vector<float> dcanddau1eta, dcanddau2eta;
  vector<float> dcanddau1pt, dcanddau2pt;
  vector<int>   matchedtogen, dcandmatchedpdg, nongendoublecounted;
  vector<float> dcandmatchedpt, dcandmatchedeta, dcandmatchedphi, dcandmatchnofdau;
  vector<float> dcandmatcheddau1pt, dcandmatcheddau2pt;
  
  
private: //.. different cuts used to produce results.
  
  Float_t cut_m_low[nch]; //.. low end of the mass hiso.
  Float_t cut_m_high[nch]; //.. high end of the mass hiso
  Float_t cut_m_dau_low[nch]; //.. low end of the daughter mass cut
  Float_t cut_m_dau_high[nch]; //.. high end of the daughter mass cut
  Float_t cut_ffls3d[nch];
  Float_t cut_falpha0[nch];
  Float_t cut_fprob[nch];
  Float_t cut_fdr[nch];
  Float_t cut_fchi2[nch];
  
  
private:
  void Init(Int_t startFile, Int_t endFile, char *filelist);
  bool Matchd0();
  bool Matchdstar();
  void write();
  void define_cuts();
  void get_tree_info();
  void LoopOverEvt();
  void LoopOvercandidate();
  void FindGenDmeson();
  Double_t jettrigcomb();

public:
  Dmesonana();
  virtual ~Dmesonana();
  
  void LoopOverFile(Int_t startFile, Int_t endFile, char *filelist, Int_t decaychannel);
  //      void draw(char* filename, Int_t ich, TCanvas* cfg);
  
};

#endif //  Dmesonana_H
