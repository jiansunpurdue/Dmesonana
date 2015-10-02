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
//#include "DataFormats/HLTReco/interface/TriggerObject.h"
#include "UserCode/OpenHF/interface/hfcand_v2.hh"

#define MAXPARTICLES 150000
#define nch 3

#define MAXGENDMESON 100
#define MAXALLGEND0 100

//typedef std::vector<trigger::TriggerObject> trigO;
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
		float svx;
		float svy;
		float svz;
        float ffls3d;
		float ff3d;
        float cosalpha;
		float ffxy;
		float fflsxy;
		float cosalphaxy;
        float fprob;
        float fdr;
        float fchi2;
        float mass_dau;
		float fpt1;
		float fpt2;
		float feta1;
		float feta2;
		float   fq1;    //it is float type in forest, which should be changed to int
		float   fq2;
        
		vector<int>  gIndex1;
		vector<int>  gIndex2;
        vector<int>  gIndex_dau2;

        Float_t genpvx;
        Float_t genpvy;
        Float_t genpvz;
        Int_t mult;
        Float_t genpt[MAXPARTICLES];
        Float_t geneta[MAXPARTICLES];
		Float_t genphi[MAXPARTICLES];
        Float_t genvx_production[MAXPARTICLES];
        Float_t genvy_production[MAXPARTICLES];
        Float_t genvz_production[MAXPARTICLES];
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
		float vx;
		float vy;
		float vz;

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
		TTree * HiTree;
		hfcand_v2* hfcandidate;

    private:
		//output trees
		TTree * gendmesontree;
		TTree * recodmesontree;
		TTree * allgend0tree;

		int nallgend0;
		float alld0pt[MAXALLGEND0];
		float alld0eta[MAXALLGEND0];
		float alld0phi[MAXALLGEND0];
		int   alld0pdg[MAXALLGEND0];
		int   alld0sube[MAXALLGEND0];
		int   alld0dnofdau[MAXALLGEND0];
		float pt_alld0dau[MAXALLGEND0][10];
		float eta_alld0dau[MAXALLGEND0][10];
		float phi_alld0dau[MAXALLGEND0][10];
		int   pdg_alld0dau[MAXALLGEND0][10];
		int   pdg_alld0Bmom[MAXALLGEND0];
		float pt_alld0Bmom[MAXALLGEND0];

		int ngend;
		double weight_pthat;
		float gensvx[MAXGENDMESON];
		float gensvy[MAXGENDMESON];
		float gensvz[MAXGENDMESON];
		float dpt[MAXGENDMESON];
		float dgenff3d[MAXGENDMESON];
		float deta[MAXGENDMESON];
		float dy[MAXGENDMESON];
		float dphi[MAXGENDMESON];
		int    dpdg[MAXGENDMESON];
		int    dsube[MAXGENDMESON];
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
		int run;
		int evt;
		float Ncoll;
//		float pvx, pvy, pvz;  vx, vy, vz previously
		float bsx, bsy, bsz;
		double trigweight;
		double pthatweight;
		vector<int> dtype, passingcuts;
		vector<float> dcandmass, dcandpt, dcandeta, dcandphi, dcandy;
		vector<float> dcandsvx, dcandsvy, dcandsvz;
		vector<float> dcandff3d, dcandffls3d, dcandcosalpha, dcandfprob, dcandfchi2; //3D cut
		vector<float> dcandffxy, dcandfflsxy, dcandcosalphaxy; //2D cut
		vector<float> dcanddau1eta, dcanddau2eta;
		vector<float> dcanddau1pt, dcanddau2pt;
		vector<int> dcanddau1matchedpdg, dcanddau2matchedpdg;
		vector<int> dcanddau1matchedmotherpdg, dcanddau2matchedmotherpdg;
		vector<int> dcanddau1matchedmothersube, dcanddau2matchedmothersube;
		vector<int> dcanddau1matchedmothernofdau, dcanddau2matchedmothernofdau;
		vector<float> dcanddau1matchedmotherpt, dcanddau2matchedmotherpt;
		vector<float> dcanddau1matchedmothereta, dcanddau2matchedmothereta;
		vector<float> dcanddau1matchedmotherphi, dcanddau2matchedmotherphi;
		vector<int> dcanddau1q, dcanddau2q;
		vector<int>   matchedtogen, dcandmatchedpdg, nongendoublecounted;
		vector<float> dcandmatchedpt, dcandmatchedff3d, dcandmatchedy, dcandmatchedeta, dcandmatchedphi, dcandmatchnofdau;
		vector<float> dcandmatchedsvx, dcandmatchedsvy, dcandmatchedsvz;
		vector<float> dcandmatcheddau1pt, dcandmatcheddau2pt;
		vector<int>   matched_pdg_Bmom;
		vector<float> matched_pt_Bmom;


    private: //.. different cuts used to produce results.

        float cut_m_low[nch]; //.. low end of the mass hiso.
        float cut_m_high[nch]; //.. high end of the mass hiso
        float cut_m_dau_low[nch]; //.. low end of the daughter mass cut
        float cut_m_dau_high[nch]; //.. high end of the daughter mass cut
        float cut_ffls3d[nch];
        float cut_cosfalpha0[nch];
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
		void FindAllGenD0();
		double jettrigcomb();

    public:
        Dmesonana();
        virtual ~Dmesonana();

        void LoopOverFile(int startFile, int endFile, char *filelist, int decaychannel);
  //      void draw(char* filename, int ich, TCanvas* cfg);

};

#endif //  Dmesonana_H
