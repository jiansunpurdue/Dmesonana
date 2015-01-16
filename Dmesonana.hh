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
#include "UserCode/OpenHF/interface/hfcand_v1.hh"

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
        int type;
        float mass;
        float fpt;
        float feta;
		float fphi;
        float ffls3d;
        float alpha;
        float fprob;
        float fdr;
        float fchi2;
        float mass_dau;
		float fpt1;
		float fpt2;
		float feta1;
		float feta2;
		int   fq1;
		int   fq2;
        
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

		int pHBHENoiseFilter;
		int pcollisionEventSelection;

        // trigger Prescl weight for each events
        float maxJetTrgPt;
        float maxJetTrgEta;
        float maxJetTrgPhi;
        float maxJetTrgMass;

        float pthat;

        //trig decison and trig Prescl, for pbpb
        int Jet55;
        int Jet55_Prescl;
        int Jet65;
        int Jet65_Prescl;
        int Jet80;
        int Jet80_Prescl;
        int Jet95;
        int Jet95_Prescl;
        int MinBias;
        int MinBias_Prescl;
        int L1_HcalHfCoincPmORBscMinBiasThresh1_BptxAND;
        int L1_HcalHfCoincPmORBscMinBiasThresh1_BptxAND_Prescl;
        int L1_SingleJet36_BptxAND;
        int L1_SingleJet36_BptxAND_Prescl;
        int L1_ETT2000;
        int L1_ETT2000_Prescl;
        int L1_SingleJet52_BptxAND;
        int L1_SingleJet52_BptxAND_Prescl;

		//trig decison and trig Prescl, for pp
		int Jet20;
		int Jet20_Prescl;
		int Jet40;
		int Jet40_Prescl;
		int Jet60;
		int Jet60_Prescl;
//		int Jet80;            //Jet80 and MB trigger use variables for pbpb
//		int Jet80_Prescl;
		int Jet100;
		int Jet100_Prescl;
//		int ZeroBias;
//		int ZeroBias_Prescl;
		int L1_ZeroBias;
		int L1_ZeroBias_Prescl;
		int L1_SingleJet16_BptxAND; //jet 20, 40
		int L1_SingleJet16_BptxAND_Prescl;
		int L1_SingleJet36;  //jet 60, 80, 100, 120
		int L1_SingleJet36_Prescl;

        //just for jet triggers, used to get trig object
//        trigO  *Jettrig_trigObject[NJETTRIG];
//        double trigPt[NJETTRIG][100];
//        double trigEta[NJETTRIG][100];
//        double trigPhi[NJETTRIG][100];


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

		int ngend;
		double weight_pthat;
		float dpt[MAXGENDMESON];
		float deta[MAXGENDMESON];
		float dphi[MAXGENDMESON];
		int    dpdg[MAXGENDMESON];
		int    dnofdau[MAXGENDMESON];
		float pt_ddau[MAXGENDMESON][3];
		float eta_ddau[MAXGENDMESON][3];
		float phi_ddau[MAXGENDMESON][3];
		int    pdg_ddau[MAXGENDMESON][3];
		int    dnofmom[MAXGENDMESON];
		int    pdg_dmom[MAXGENDMESON];
		float pt_dmom[MAXGENDMESON];
		int    pdg_Bmom[MAXGENDMESON];
		float pt_Bmom[MAXGENDMESON];

		int ndcand;
		int hiBin;
		double trigweight;
		double pthatweight;
		vector<int> dtype, passingcuts;
		vector<float> dcandmass, dcandpt, dcandeta, dcandphi, dcandffls3d, dcandalpha, dcandfprob, dcandfchi2;
		vector<float> dcanddau1eta, dcanddau2eta;
		vector<float> dcanddau1pt, dcanddau2pt;
		vector<int>   matchedtogen, dcandmatchedpdg, nongendoublecounted;
		vector<float> dcandmatchedpt, dcandmatchedeta, dcandmatchedphi, dcandmatchnofdau;
		vector<float> dcandmatcheddau1pt, dcandmatcheddau2pt;


    private: //.. different cuts used to produce results.

        float cut_m_low[nch]; //.. low end of the mass hiso.
        float cut_m_high[nch]; //.. high end of the mass hiso
        float cut_m_dau_low[nch]; //.. low end of the daughter mass cut
        float cut_m_dau_high[nch]; //.. high end of the daughter mass cut
        float cut_ffls3d[nch];
        float cut_falpha0[nch];
        float cut_fprob[nch];
        float cut_fdr[nch];
        float cut_fchi2[nch];


    private:
        void Init(int startFile, int endFile, char *filelist);
		bool Matchd0();
		bool Matchdstar();
        void write();
		void define_cuts();
		void get_tree_info();
		void LoopOverEvt();
		void LoopOvercandidate();
		void FindGenDmeson();
		double jettrigcomb();

    public:
        Dmesonana();
        virtual ~Dmesonana();

        void LoopOverFile(int startFile, int endFile, char *filelist, int decaychannel);
  //      void draw(char* filename, int ich, TCanvas* cfg);

};

#endif //  Dmesonana_H
