//using std::vector;
#include <TTree.h>
#include <vector>

#define MAX_XB 50000
#define MAXPARTICLES 50000
#define MAXGENDMESON 100

//reco read
Int_t    Event_Jet55;
Int_t    Event_Jet55_Prescl;
Int_t    Event_Jet65;
Int_t    Event_Jet65_Prescl;
Int_t    Event_Jet80;
Int_t    Event_Jet80_Prescl;
Int_t    Event_Jet95;
Int_t    Event_Jet95_Prescl;
Int_t    Event_MinBias;
Int_t    Event_MinBias_Prescl;
Int_t    Event_Jet20;
Int_t    Event_Jet20_Prescl;
Int_t    Event_Jet40;
Int_t    Event_Jet40_Prescl;
Int_t    Event_Jet60;
Int_t    Event_Jet60_Prescl;
Int_t    Event_Jet100;
Int_t    Event_Jet100_Prescl;

Float_t  Event_maxJetTrgPt;
Double_t Event_trigweight;
Double_t Event_pthatweight;
Int_t    Event_ndcand;

vector<int> *Event_dtype=0;
vector<int> *Event_passingcuts=0;
vector<float> *Event_dcandmass=0;
vector<float> *Event_dcandpt=0;
vector<float> *Event_dcandeta=0;
vector<float> *Event_dcandy=0;
vector<float> *Event_dcandphi=0;
vector<float> *Event_dcandffls3d=0;
vector<float> *Event_dcandcosalpha=0;
vector<float> *Event_dcandfprob=0;
vector<float> *Event_dcandfchi2=0;
vector<float> *Event_dcanddau1eta=0;
vector<float> *Event_dcanddau2eta=0;
vector<float> *Event_dcanddau1pt=0;
vector<float> *Event_dcanddau2pt=0;
vector<int> *Event_matchedtogen=0;
vector<int> *Event_matched_pt_Bmom=0;
vector<int> *Event_dcandmatchedpdg=0;
vector<int> *Event_nongendoublecounted=0;
vector<float> *Event_dcandmatchedpt=0;
vector<float> *Event_dcandmatchedeta=0;
vector<float> *Event_dcandmatchedphi=0;
vector<float> *Event_dcandmatchnofdau=0;
vector<float> *Event_dcandmatcheddau1pt=0;
vector<float> *Event_dcandmatcheddau2pt=0;

void setBranch(TTree *root, bool isPbPb, bool isMC)
{
  root->SetBranchAddress("MinBias",&Event_MinBias);
  root->SetBranchAddress("MinBias_Prescl",&Event_MinBias_Prescl);
  if(isPbPb)
    {
      root->SetBranchAddress("Jet55",&Event_Jet55);
      root->SetBranchAddress("Jet55_Prescl",&Event_Jet55_Prescl);
      root->SetBranchAddress("Jet65",&Event_Jet65);
      root->SetBranchAddress("Jet65_Prescl",&Event_Jet65_Prescl);
      root->SetBranchAddress("Jet80",&Event_Jet80);
      root->SetBranchAddress("Jet80_Prescl",&Event_Jet80_Prescl);
    }
  else
    {
      root->SetBranchAddress("Jet20",&Event_Jet20);
      root->SetBranchAddress("Jet20_Prescl",&Event_Jet20_Prescl);
      root->SetBranchAddress("Jet40",&Event_Jet40);
      root->SetBranchAddress("Jet40_Prescl",&Event_Jet40_Prescl);
      root->SetBranchAddress("Jet60",&Event_Jet60);
      root->SetBranchAddress("Jet60_Prescl",&Event_Jet60_Prescl);
      root->SetBranchAddress("Jet100",&Event_Jet100);
      root->SetBranchAddress("Jet100_Prescl",&Event_Jet100_Prescl);
    }
  root->SetBranchAddress("maxJetTrgPt",&Event_maxJetTrgPt);
  root->SetBranchAddress("trigweight",&Event_trigweight);
  root->SetBranchAddress("pthatweight",&Event_pthatweight);
  root->SetBranchAddress("ndcand",&Event_ndcand);

  root->SetBranchAddress("dtype",&Event_dtype);
  root->SetBranchAddress("passingcuts",&Event_passingcuts);
  root->SetBranchAddress("dcandmass",&Event_dcandmass);
  root->SetBranchAddress("dcandpt",&Event_dcandpt);
  root->SetBranchAddress("dcandeta",&Event_dcandeta);
  root->SetBranchAddress("dcandy",&Event_dcandy);
  root->SetBranchAddress("dcandphi",&Event_dcandphi);
  root->SetBranchAddress("dcandffls3d",&Event_dcandffls3d);
  root->SetBranchAddress("dcandcosalpha",&Event_dcandcosalpha);
  root->SetBranchAddress("dcandfprob",&Event_dcandfprob);
  root->SetBranchAddress("dcandfchi2",&Event_dcandfchi2);
  root->SetBranchAddress("dcanddau1eta",&Event_dcanddau1eta);
  root->SetBranchAddress("dcanddau2eta",&Event_dcanddau2eta);
  root->SetBranchAddress("dcanddau1pt",&Event_dcanddau1pt);
  root->SetBranchAddress("dcanddau2pt",&Event_dcanddau2pt);
  if(isMC)
    {
      root->SetBranchAddress("matchedtogen",&Event_matchedtogen);
      root->SetBranchAddress("matched_pt_Bmom",&Event_matched_pt_Bmom);
      root->SetBranchAddress("dcandmatchedpdg",&Event_dcandmatchedpdg);
      root->SetBranchAddress("nongendoublecounted",&Event_nongendoublecounted);
      root->SetBranchAddress("dcandmatchedpt",&Event_dcandmatchedpt);
      root->SetBranchAddress("dcandmatchedeta",&Event_dcandmatchedeta);
      root->SetBranchAddress("dcandmatchedphi",&Event_dcandmatchedphi);
      root->SetBranchAddress("dcandmatchnofdau",&Event_dcandmatchnofdau);
      root->SetBranchAddress("dcandmatcheddau1pt",&Event_dcandmatcheddau1pt);
      root->SetBranchAddress("dcandmatcheddau2pt",&Event_dcandmatcheddau2pt);
    }
}

//reco build
Int_t    Jet55;
Int_t    Jet55_Prescl;
Int_t    Jet65;
Int_t    Jet65_Prescl;
Int_t    Jet80;
Int_t    Jet80_Prescl;
Int_t    Jet95;
Int_t    Jet95_Prescl;
Int_t    MinBias;
Int_t    MinBias_Prescl;
Int_t    Jet20;
Int_t    Jet20_Prescl;
Int_t    Jet40;
Int_t    Jet40_Prescl;
Int_t    Jet60;
Int_t    Jet60_Prescl;
Int_t    Jet100;
Int_t    Jet100_Prescl;
Float_t  maxJetTrgPt;
Double_t trigweight;
Double_t pthatweight;
Int_t    ndcand;

Int_t    dtype;
Int_t    passingcuts;
Float_t  dcandmass;
Float_t  dcandpt;
Float_t  dcandeta;
Float_t  dcandy;
Float_t  dcandphi;
Float_t  dcandffls3d;
Float_t  dcandcosalpha;
Float_t  dcandfprob;
Float_t  dcandfchi2;
Float_t  dcanddau1eta;
Float_t  dcanddau2eta;
Float_t  dcanddau1pt;
Float_t  dcanddau2pt;
Int_t    matchedtogen;
Int_t    matched_pt_Bmom;
Int_t    dcandmatchedpdg;
Int_t    nongendoublecounted;
Float_t  dcandmatchedpt;
Float_t  dcandmatchedeta;
Float_t  dcandmatchedphi;
Float_t  dcandmatchnofdau;
Float_t  dcandmatcheddau1pt;
Float_t  dcandmatcheddau2pt;

void buildBranch(TTree* nt)
{
  nt->Branch("Jet55",&Jet55);
  nt->Branch("Jet55_Prescl",&Jet55_Prescl);
  nt->Branch("Jet65",&Jet65);
  nt->Branch("Jet65_Prescl",&Jet65_Prescl);
  nt->Branch("Jet80",&Jet80);
  nt->Branch("Jet80_Prescl",&Jet80_Prescl);
  nt->Branch("Jet95",&Jet95);
  nt->Branch("Jet95_Prescl",&Jet95_Prescl);
  nt->Branch("MinBias",&MinBias);
  nt->Branch("MinBias_Prescl",MinBias_Prescl);
  nt->Branch("Jet20",&Jet20);
  nt->Branch("Jet20_Prescl",&Jet20_Prescl);
  nt->Branch("Jet40",&Jet40);
  nt->Branch("Jet40_Prescl",&Jet40_Prescl);
  nt->Branch("Jet60",&Jet60);
  nt->Branch("Jet60_Prescl",&Jet60_Prescl);
  nt->Branch("Jet100",&Jet100);
  nt->Branch("Jet100_Prescl",&Jet100_Prescl);

  nt->Branch("maxJetTrgPt",&maxJetTrgPt);
  nt->Branch("trigweight",&trigweight);
  nt->Branch("pthatweight",&pthatweight);
  nt->Branch("ndcand",&ndcand);

  nt->Branch("dtype",&dtype);
  nt->Branch("passingcuts",&passingcuts);
  nt->Branch("dcandmass",&dcandmass);
  nt->Branch("dcandpt",&dcandpt);
  nt->Branch("dcandeta",&dcandeta);
  nt->Branch("dcandy",&dcandy);
  nt->Branch("dcandphi",&dcandphi);
  nt->Branch("dcandffls3d",&dcandffls3d);
  nt->Branch("dcandcosalpha",&dcandcosalpha);
  nt->Branch("dcandfprob",&dcandfprob);
  nt->Branch("dcandfchi2",&dcandfchi2);
  nt->Branch("dcanddau1eta",&dcanddau1eta);
  nt->Branch("dcanddau2eta",&dcanddau2eta);
  nt->Branch("dcanddau1pt",&dcanddau1pt);
  nt->Branch("dcanddau2pt",&dcanddau2pt);

  nt->Branch("matchedtogen",&matchedtogen);
  nt->Branch("matched_pt_Bmom",&matched_pt_Bmom);
  nt->Branch("dcandmatchedpdg",&dcandmatchedpdg);
  nt->Branch("nongendoublecounted",&nongendoublecounted);
  nt->Branch("dcandmatchedpt",&dcandmatchedpt);
  nt->Branch("dcandmatchedeta",&dcandmatchedeta);
  nt->Branch("dcandmatchedphi",&dcandmatchedphi);
  nt->Branch("dcandmatchnofdau",&dcandmatchnofdau);
  nt->Branch("dcandmatcheddau1pt",&dcandmatcheddau1pt);
  nt->Branch("dcandmatcheddau2pt",&dcandmatcheddau2pt);
}

//gen read
Int_t    Event_ngend;
Double_t Event_weight_pthat;
Float_t  Event_dpt[MAXGENDMESON];
Float_t  Event_deta[MAXGENDMESON];
Float_t  Event_dphi[MAXGENDMESON];
Int_t    Event_dpdg[MAXGENDMESON];
//Int_t    Event_dnofdau[MAXGENDMESON];
Float_t  Event_pt_ddau[MAXGENDMESON][3];
Float_t  Event_eta_ddau[MAXGENDMESON][3];
Float_t  Event_phi_ddau[MAXGENDMESON][3];
Int_t    Event_pdg_ddau[MAXGENDMESON][3];
Int_t    Event_dnofmom[MAXGENDMESON];
Int_t    Event_pdg_dmom[MAXGENDMESON];
Float_t  Event_pt_dmom[MAXGENDMESON];
Int_t    Event_pdg_Bmom[MAXGENDMESON];
Float_t  Event_pt_Bmom[MAXGENDMESON];

void setGenBranch(TTree *root)
{
  root->SetBranchAddress("ngend",&Event_ngend);
  root->SetBranchAddress("weight_pthat",&Event_weight_pthat);
  root->SetBranchAddress("dpt",Event_dpt);
  root->SetBranchAddress("deta",Event_deta);
  root->SetBranchAddress("dphi",Event_dphi);
  root->SetBranchAddress("dpdg",Event_dpdg);
  //root->SetBranchAddress("dnofdau",Event_dnofdau);
  root->SetBranchAddress("pt_ddau",Event_pt_ddau);
  root->SetBranchAddress("eta_ddau",Event_eta_ddau);
  root->SetBranchAddress("phi_ddau",Event_phi_ddau);
  root->SetBranchAddress("pdg_ddau",Event_pdg_ddau);
  root->SetBranchAddress("dnofmom",Event_dnofmom);
  root->SetBranchAddress("pdg_dmom",Event_pdg_dmom);
  root->SetBranchAddress("pt_dmom",Event_pt_dmom);
  root->SetBranchAddress("pdg_Bmom",Event_pdg_Bmom);
  root->SetBranchAddress("pt_Bmom",Event_pt_Bmom);

  //root->SetBranchAddress("",Event_);
}

//gen build
Int_t    ngend;
Float_t pthat;
Double_t weight_pthat;
Float_t  dpt[MAXGENDMESON];
Float_t  deta[MAXGENDMESON];
Float_t  dphi[MAXGENDMESON];
Int_t    dpdg[MAXGENDMESON];
Int_t    dnofdau[MAXGENDMESON];
Float_t  pt_ddau[MAXGENDMESON][3];
Float_t  eta_ddau[MAXGENDMESON][3];
Float_t  phi_ddau[MAXGENDMESON][3];
Int_t    pdg_ddau[MAXGENDMESON][3];
Int_t    dnofmom[MAXGENDMESON];
Int_t    pdg_dmom[MAXGENDMESON];
Float_t  pt_dmom[MAXGENDMESON];
Int_t    pdg_Bmom[MAXGENDMESON];
Float_t  pt_Bmom[MAXGENDMESON];

void buildGenBranch(TTree* nt)
{
  nt->Branch("ngend",&ngend,"ngend/I");
  nt->Branch("pthat",&pthat,"pthat/F");
  nt->Branch("weight_pthat",&weight_pthat,"weight_pthat/D");
  nt->Branch("dpt",dpt,"dpt[ngend]/F");
  nt->Branch("deta",deta,"deta[ngend]/F");
  nt->Branch("dphi",dphi,"dphi[ngend]/F");
  nt->Branch("dpdg",dpdg,"dpdg[ngend]/I");
  //nt->Branch("dnofdau",dnofdau,"dnofdau[ngend]/I");
  nt->Branch("pt_ddau",pt_ddau,"pt_ddau[ngend][3]/F");
  nt->Branch("eta_ddau",eta_ddau,"eta_ddau[ngend][3]/F");
  nt->Branch("phi_ddau",phi_ddau,"phi_ddau[ngend][3]/F");
  nt->Branch("pdg_ddau",pdg_ddau,"pdg_ddau[ngend][3]/I");
  nt->Branch("dnofmom",dnofmom,"dnofmom[ngend]/I");
  nt->Branch("pdg_dmom",pdg_dmom,"pdg_dmom[ngend]/I");
  nt->Branch("pt_dmom",pt_dmom,"pt_dmom[ngend]/F");
  nt->Branch("pdg_Bmom",pdg_Bmom,"pdg_Bmom[ngend]/I");
  nt->Branch("pt_Bmom",pt_Bmom,"pt_Bmom[ngend]/F");  
}
