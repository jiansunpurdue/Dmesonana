#include <fstream>
#include <iostream>
#include <vector>
#include "TH1F.h"
#include "TFile.h"
#include "TSystem.h"
#include "TTree.h"
#include "TNtuple.h"
#include "TBranch.h"
#include "TMath.h"
#include <TF1.h>
#include <TLorentzVector.h>

#include "Dmesonana.hh"
#include <iomanip>
#include "UserCode/OpenHF/interface/hfcand_v2.hh"

#define MASSD0 1.8645  //value from pythia

bool savealldcand = true;
bool isMC = false;
bool isPbPb = true;
bool ispppPbMB = false;
bool ispPbJettrig = false;

bool gendecaylength = true;

////for D0 official Hydjet samples
#define NPTHATBIN 4
//official samples pthat 0,15,30 and 50, D0 pt 1.0 GeV
int MCentries[NPTHATBIN] = { 195282, 190493, 190688, 222777};
int pthatbin[NPTHATBIN+1] = { 0, 15, 30, 50, 1000};
double pthatweight_xsection[NPTHATBIN+1] = {41.30, 0.2028, 1.074E-2, 1.022E-03, 1.756E-15};
double filtereff[NPTHATBIN+1] = { 0.0317, 0.1396, 0.1686, 0.2030, 0.0945};

//////for D0 official Hydjet samples
//#define NPTHATBIN 4
////official samples pthat 0,15,30 and 50, D0 pt 3.0 GeV
//int MCentries[NPTHATBIN] = { 192029, 192708, 190549, 224082};
//int pthatbin[NPTHATBIN+1] = { 0, 15, 30, 50, 1000};
//double pthatweight_xsection[NPTHATBIN+1] = {41.30, 0.2037, 1.079E-2, 1.025E-03, 1.756E-15};
//double filtereff[NPTHATBIN+1] = { 0.012269, 0.09910, 0.13495, 0.15662, 0.0945};

TH1F * pthat_weighted = new TH1F("pthat_weighted","pthat_weighted",200,0,500.0);
TH1F * gend0pt_weighted = new TH1F("gend0pt_weighted","gend0pt_weighted",100,0.0,100.0);

//
Dmesonana::Dmesonana()
{
}

//
Dmesonana::~Dmesonana()
{
	//    delete filename;
	delete result;

}
//
void Dmesonana::Init(int startFile, int endFile, char *filelist)
{//.. called right after constructor 
	char * outfilename = new char[1000];
//	sprintf(outfilename, "/scratch/lustreA/s/sun229/v2_files/Dmesonana_%s_%dTo%d.root",  filelist, startFile, endFile);
    sprintf(outfilename, "Dmesonana_%s_%dTo%d.root",  filelist, startFile, endFile);
	result = new TFile(outfilename, "recreate");

	//

	hftree = 0;
	genparticletree = 0;
	jetObjTree = 0;
	HltTree = 0;
	jettree = 0;
	skimtree = 0;
	HiTree = 0;

	hfcandidate = new hfcand_v2;

	//	for ( int i = 0; i < NJETTRIG; i++)
	//		Jettrig_trigObject[i] = new trigO;

	define_cuts();

	if( isMC )
	{
    	gendmesontree = new TTree("gendmesontree","gendmesontree");
		gendmesontree->Branch("genpvx",&genpvx, "genpvx/F");
		gendmesontree->Branch("genpvy",&genpvy, "genpvy/F");
		gendmesontree->Branch("genpvz",&genpvz, "genpvz/F");
    	gendmesontree->Branch("pthat",&pthat, "pthat/F");
    	gendmesontree->Branch("weight_pthat",&weight_pthat, "weight_pthat/D");
    	gendmesontree->Branch("ngend",&ngend,"ngend/I");
		gendmesontree->Branch("gensvx", gensvx, "gensvx[ngend]/F");
		gendmesontree->Branch("gensvy", gensvy, "gensvy[ngend]/F");
		gendmesontree->Branch("gensvz", gensvz, "gensvz[ngend]/F");
    	gendmesontree->Branch("dpt", dpt, "dpt[ngend]/F");
    	gendmesontree->Branch("deta", deta, "deta[ngend]/F");
		gendmesontree->Branch("dy", dy, "dy[ngend]/F");
    	gendmesontree->Branch("dphi", dphi, "dphi[ngend]/F");
		gendmesontree->Branch("dgenff3d", dgenff3d, "dgenff3d[ngend]/F");
    	gendmesontree->Branch("dpdg", dpdg, "dpdg[ngend]/I");
		gendmesontree->Branch("dsube", dsube, "dsube[ngend]/I");
		gendmesontree->Branch("dnofdau", dnofdau, "dnofdau[ngend]/I");
    	gendmesontree->Branch("pt_ddau", pt_ddau, "pt_ddau[ngend][3]/F");
    	gendmesontree->Branch("eta_ddau", eta_ddau, "eta_ddau[ngend][3]/F");
    	gendmesontree->Branch("phi_ddau", phi_ddau, "phi_ddau[ngend][3]/F");
    	gendmesontree->Branch("pdg_ddau", pdg_ddau, "pdg_ddau[ngend][3]/I");
		gendmesontree->Branch("dnofmom", dnofmom, "dnofmom[ngend]/I");
		gendmesontree->Branch("pdg_dmom", pdg_dmom, "pdg_dmom[ngend]/I");
		gendmesontree->Branch("pt_dmom", pt_dmom, "pt_dmom[ngend]/F");
		gendmesontree->Branch("pdg_Bmom", pdg_Bmom, "pdg_Bmom[ngend]/I");
		gendmesontree->Branch("pt_Bmom", pt_Bmom, "pt_Bmom[ngend]/F");

		allgend0tree = new TTree("allgend0tree","allgend0tree");
    	allgend0tree->Branch("pthat",&pthat, "pthat/F");
    	allgend0tree->Branch("weight_pthat",&weight_pthat, "weight_pthat/D");
    	allgend0tree->Branch("nallgend0",&nallgend0,"nallgend0/I");
    	allgend0tree->Branch("alld0pt", alld0pt, "alld0pt[nallgend0]/F");
    	allgend0tree->Branch("alld0eta", alld0eta, "alld0eta[nallgend0]/F");
    	allgend0tree->Branch("alld0phi", alld0phi, "alld0phi[nallgend0]/F");
    	allgend0tree->Branch("alld0pdg", alld0pdg, "alld0pdg[nallgend0]/I");
		allgend0tree->Branch("alld0sube", alld0sube, "alld0sube[nallgend0]/I");
		allgend0tree->Branch("alld0dnofdau", alld0dnofdau, "alld0dnofdau[nallgend0]/I");
    	allgend0tree->Branch("pt_alld0dau", pt_alld0dau, "pt_alld0dau[nallgend0][10]/F");
    	allgend0tree->Branch("eta_alld0dau", eta_alld0dau, "eta_alld0dau[nallgend0][10]/F");
    	allgend0tree->Branch("phi_alld0dau", phi_alld0dau, "phi_alld0dau[nallgend0][10]/F");
    	allgend0tree->Branch("pdg_alld0dau", pdg_alld0dau, "pdg_alld0dau[nallgend0][10]/I");
		allgend0tree->Branch("pdg_alld0Bmom", pdg_alld0Bmom, "pdg_alld0Bmom[nallgend0]/I");
		allgend0tree->Branch("pt_alld0Bmom", pt_alld0Bmom, "pt_alld0Bmom[nallgend0]/F");
	}

	recodmesontree = new TTree("recodmesontree","recodmesontree");
	if( isPbPb )
	{
		if( isMC )  	recodmesontree->Branch("Ncoll", &Ncoll, "Ncoll/F");
		recodmesontree->Branch("hiBin", &hiBin, "hiBin/I");
		recodmesontree->Branch("run", &run, "run/I");
		recodmesontree->Branch("evt", &evt, "evt/I");
		recodmesontree->Branch("vx", &vx, "vx/F");
		recodmesontree->Branch("vy", &vy, "vy/F");
		recodmesontree->Branch("vz", &vz, "vz/F");
		recodmesontree->Branch("bsx", &bsx, "bsx/F");
		recodmesontree->Branch("bsy", &bsy, "bsy/F");
		recodmesontree->Branch("bsz", &bsz, "bsz/F");
    	recodmesontree->Branch("MinBias", &MinBias, "MinBias/I");
    	recodmesontree->Branch("MinBias_Prescl", &MinBias_Prescl, "MinBias_Prescl/I");
//    	recodmesontree->Branch("Jet55", &Jet55, "Jet55/I");  //
//    	recodmesontree->Branch("Jet55_Prescl", &Jet55_Prescl, "Jet55_Prescl/I");
//    	recodmesontree->Branch("Jet65", &Jet65, "Jet65/I");
//    	recodmesontree->Branch("Jet65_Prescl", &Jet65_Prescl, "Jet65_Prescl/I");
//    	recodmesontree->Branch("Jet80", &Jet80, "Jet80/I");
//    	recodmesontree->Branch("Jet80_Prescl", &Jet80_Prescl, "Jet80_Prescl/I");
	}
	else
	{
		recodmesontree->Branch("MinBias", &MinBias, "MinBias/I");
		recodmesontree->Branch("MinBias_Prescl", &MinBias_Prescl, "MinBias_Prescl/I");
		recodmesontree->Branch("Jet20", &Jet20, "Jet20/I");
		recodmesontree->Branch("Jet20_Prescl", &Jet20_Prescl, "Jet20_Prescl/I");
		recodmesontree->Branch("Jet40", &Jet40, "Jet40/I");
		recodmesontree->Branch("Jet40_Prescl", &Jet40_Prescl, "Jet40_Prescl/I");
		recodmesontree->Branch("Jet60", &Jet60, "Jet60/I");
		recodmesontree->Branch("Jet60_Prescl", &Jet60_Prescl, "Jet60_Prescl/I");
		recodmesontree->Branch("Jet80", &Jet80, "Jet80/I");
		recodmesontree->Branch("Jet80_Prescl", &Jet80_Prescl, "Jet80_Prescl/I");
		recodmesontree->Branch("Jet100", &Jet100, "Jet100/I");
		recodmesontree->Branch("Jet100_Prescl", &Jet100_Prescl, "Jet100_Prescl/I");
	}

	recodmesontree->Branch("maxJetTrgPt", &maxJetTrgPt, "maxJetTrgPt/F");
	recodmesontree->Branch("pthatweight", &pthatweight, "pthatweight/D");   //same with weight_pthat in gen tree, 0 for data
	recodmesontree->Branch("trigweight", &trigweight, "trigweight/D");
	recodmesontree->Branch("ndcand", &ndcand, "ndcand/I");
	recodmesontree->Branch("dtype", &dtype);
//	recodmesontree->Branch("passingcuts", &passingcuts); //
	recodmesontree->Branch("dcandmass", &dcandmass);
	recodmesontree->Branch("dcandpt", &dcandpt);
	recodmesontree->Branch("dcandeta", &dcandeta);
	recodmesontree->Branch("dcandy", &dcandy);
	recodmesontree->Branch("dcandphi", &dcandphi);
	recodmesontree->Branch("dcandsvx", &dcandsvx);
	recodmesontree->Branch("dcandsvy", &dcandsvy);
	recodmesontree->Branch("dcandsvz", &dcandsvz);
	recodmesontree->Branch("dcandffls3d", &dcandffls3d);
	recodmesontree->Branch("dcandff3d", &dcandff3d);
	recodmesontree->Branch("dcandcosalpha", &dcandcosalpha);
	recodmesontree->Branch("dcandfflsxy", &dcandfflsxy);
	recodmesontree->Branch("dcandffxy", &dcandffxy);
	recodmesontree->Branch("dcandcosalphaxy", &dcandcosalphaxy);
	recodmesontree->Branch("dcandfprob", &dcandfprob);
	recodmesontree->Branch("dcandfchi2", &dcandfchi2);
	recodmesontree->Branch("dcanddau1eta", &dcanddau1eta);
	recodmesontree->Branch("dcanddau2eta", &dcanddau2eta);
	recodmesontree->Branch("dcanddau1pt", &dcanddau1pt);
	recodmesontree->Branch("dcanddau2pt", &dcanddau2pt);
//	recodmesontree->Branch("dcanddau1q", &dcanddau1q); //
//	recodmesontree->Branch("dcanddau2q", &dcanddau2q); //
	if( isMC )
	{
		recodmesontree->Branch("dcanddau1matchedpdg", &dcanddau1matchedpdg);
		recodmesontree->Branch("dcanddau2matchedpdg", &dcanddau2matchedpdg);
		recodmesontree->Branch("dcanddau1matchedmotherpdg", &dcanddau1matchedmotherpdg);
		recodmesontree->Branch("dcanddau2matchedmotherpdg", &dcanddau2matchedmotherpdg);
		recodmesontree->Branch("dcanddau1matchedmothersube", &dcanddau1matchedmothersube);
		recodmesontree->Branch("dcanddau2matchedmothersube", &dcanddau2matchedmothersube);
		recodmesontree->Branch("dcanddau1matchedmothernofdau", &dcanddau1matchedmothernofdau);
		recodmesontree->Branch("dcanddau2matchedmothernofdau", &dcanddau2matchedmothernofdau);
		recodmesontree->Branch("dcanddau1matchedmotherpt", &dcanddau1matchedmotherpt);
		recodmesontree->Branch("dcanddau2matchedmotherpt", &dcanddau2matchedmotherpt);
		recodmesontree->Branch("dcanddau1matchedmothereta",&dcanddau1matchedmothereta);
		recodmesontree->Branch("dcanddau2matchedmothereta",&dcanddau2matchedmothereta);
		recodmesontree->Branch("dcanddau1matchedmotherphi",&dcanddau1matchedmotherphi);
		recodmesontree->Branch("dcanddau2matchedmotherphi",&dcanddau2matchedmotherphi);
    	recodmesontree->Branch("matchedtogen", &matchedtogen);
		recodmesontree->Branch("nongendoublecounted", &nongendoublecounted);
    	recodmesontree->Branch("dcandmatchedpdg", &dcandmatchedpdg);
    	recodmesontree->Branch("dcandmatchedpt", &dcandmatchedpt);
		recodmesontree->Branch("dcandmatchedff3d", &dcandmatchedff3d);
		recodmesontree->Branch("dcandmatchedy", &dcandmatchedy);
    	recodmesontree->Branch("dcandmatchedeta", &dcandmatchedeta); //
    	recodmesontree->Branch("dcandmatchedphi", &dcandmatchedphi);
		recodmesontree->Branch("dcandmatchedsvx", &dcandmatchedsvx);
		recodmesontree->Branch("dcandmatchedsvy", &dcandmatchedsvy);
		recodmesontree->Branch("dcandmatchedsvz", &dcandmatchedsvz);
//    	recodmesontree->Branch("dcandmatchnofdau", &dcandmatchnofdau); //
    	recodmesontree->Branch("dcandmatcheddau1pt", &dcandmatcheddau1pt);
    	recodmesontree->Branch("dcandmatcheddau2pt", &dcandmatcheddau2pt);
		recodmesontree->Branch("matched_pdg_Bmom", &matched_pdg_Bmom);
		recodmesontree->Branch("matched_pt_Bmom", &matched_pt_Bmom);
	}

}


void Dmesonana::get_tree_info()
{
	//information from hltobject
	jetObjTree->SetBranchAddress("pt", &maxJetTrgPt);
	jetObjTree->SetBranchAddress("eta", &maxJetTrgEta);
	jetObjTree->SetBranchAddress("phi", &maxJetTrgPhi);
	jetObjTree->SetBranchAddress("mass", &maxJetTrgMass);

	if( isMC )
	{
	    //gen particle tree
		genparticletree->SetBranchAddress("vx", &genpvx);
		genparticletree->SetBranchAddress("vy", &genpvy);
		genparticletree->SetBranchAddress("vz", &genpvz);
        genparticletree->SetBranchAddress("mult", &mult);
    	genparticletree->SetBranchAddress("pt", genpt);
    	genparticletree->SetBranchAddress("eta", geneta);
    	genparticletree->SetBranchAddress("phi", genphi);
		genparticletree->SetBranchAddress("pdg", genpdg);
    	genparticletree->SetBranchAddress("chg", genchg);
		genparticletree->SetBranchAddress("sube", gensube);
    	genparticletree->SetBranchAddress("matchingID", genmatchingID);
    	genparticletree->SetBranchAddress("nMothers", gennMothers);
    	genparticletree->SetBranchAddress("motherIdx", genmotherIdx);
    	genparticletree->SetBranchAddress("nDaughters", gennDaughters);
    	genparticletree->SetBranchAddress("daughterIdx", gendaughterIdx);
    	genparticletree->SetBranchAddress("sta", gensta);
		if( gendecaylength )
		{
			genparticletree->SetBranchAddress("vx_production", genvx_production);
			genparticletree->SetBranchAddress("vy_production", genvy_production);
			genparticletree->SetBranchAddress("vz_production", genvz_production);
    	}
	}

    if( isPbPb )
	{
	    HltTree->SetBranchAddress("L1_HcalHfCoincPmORBscMinBiasThresh1_BptxAND",&L1_HcalHfCoincPmORBscMinBiasThresh1_BptxAND);
	    HltTree->SetBranchAddress("L1_HcalHfCoincPmORBscMinBiasThresh1_BptxAND_Prescl",&L1_HcalHfCoincPmORBscMinBiasThresh1_BptxAND_Prescl);
	    HltTree->SetBranchAddress("L1_SingleJet36_BptxAND",&L1_SingleJet36_BptxAND);
	    HltTree->SetBranchAddress("L1_SingleJet36_BptxAND_Prescl",&L1_SingleJet36_BptxAND_Prescl);
	    HltTree->SetBranchAddress("L1_SingleJet52_BptxAND",&L1_SingleJet52_BptxAND);
	    HltTree->SetBranchAddress("L1_SingleJet52_BptxAND_Prescl",&L1_SingleJet52_BptxAND_Prescl);
	    HltTree->SetBranchAddress("L1_ETT2000",&L1_ETT2000);
	    HltTree->SetBranchAddress("L1_ETT2000_Prescl",&L1_ETT2000_Prescl);
	    //	HltTree->SetBranchAddress("HLT_HIJet55_v7_trigObject",&Jettrig_trigObject[0]);
	    //	HltTree->SetBranchAddress("HLT_HIJet65_v7_trigObject",&Jettrig_trigObject[1]);
	    //	HltTree->SetBranchAddress("HLT_HIJet80_v7_trigObject",&Jettrig_trigObject[2]);
	    //	HltTree->SetBranchAddress("HLT_HIJet95_v7_trigObject",&Jettrig_trigObject[3]);

	    if( isMC )
	    {
	        HltTree->SetBranchAddress("HLT_HIJet55_v7",&Jet55);
	        HltTree->SetBranchAddress("HLT_HIJet55_v7_Prescl",&Jet55_Prescl);
	        HltTree->SetBranchAddress("HLT_HIJet65_v7",&Jet65);
	        HltTree->SetBranchAddress("HLT_HIJet65_v7_Prescl",&Jet65_Prescl);
	        HltTree->SetBranchAddress("HLT_HIJet80_v7",&Jet80);
	        HltTree->SetBranchAddress("HLT_HIJet80_v7_Prescl",&Jet80_Prescl);
	        HltTree->SetBranchAddress("HLT_HIJet95_v7",&Jet95);
	        HltTree->SetBranchAddress("HLT_HIJet95_v7_Prescl",&Jet95_Prescl);
	        HltTree->SetBranchAddress("HLT_HIMinBiasHfOrBSC_v4",&MinBias);
	        HltTree->SetBranchAddress("HLT_HIMinBiasHfOrBSC_v4_Prescl",&MinBias_Prescl);

	    }
	    else
	    {
	        HltTree->SetBranchAddress("HLT_HIJet55_v1",&Jet55);
	        HltTree->SetBranchAddress("HLT_HIJet55_v1_Prescl",&Jet55_Prescl);
	        HltTree->SetBranchAddress("HLT_HIJet65_v1",&Jet65);
	        HltTree->SetBranchAddress("HLT_HIJet65_v1_Prescl",&Jet65_Prescl);
	        HltTree->SetBranchAddress("HLT_HIJet80_v1",&Jet80);
	        HltTree->SetBranchAddress("HLT_HIJet80_v1_Prescl",&Jet80_Prescl);
	        HltTree->SetBranchAddress("HLT_HIJet95_v1",&Jet95);
	        HltTree->SetBranchAddress("HLT_HIJet95_v1_Prescl",&Jet95_Prescl);
	        HltTree->SetBranchAddress("HLT_HIMinBiasHfOrBSC_v1",&MinBias);
	        HltTree->SetBranchAddress("HLT_HIMinBiasHfOrBSC_v1_Prescl",&MinBias_Prescl);
	    }
	}
	else  // for pp and pPb
	{
        HltTree->SetBranchAddress("HLT_PAZeroBiasPixel_SingleTrack_v1",&MinBias);
        HltTree->SetBranchAddress("HLT_PAZeroBiasPixel_SingleTrack_v1_Prescl",&MinBias_Prescl);
        HltTree->SetBranchAddress("HLT_PAJet20_NoJetID_v1",&Jet20);
        HltTree->SetBranchAddress("HLT_PAJet20_NoJetID_v1_Prescl",&Jet20_Prescl);
        HltTree->SetBranchAddress("HLT_PAJet40_NoJetID_v1",&Jet40);
        HltTree->SetBranchAddress("HLT_PAJet40_NoJetID_v1_Prescl",&Jet40_Prescl);
        HltTree->SetBranchAddress("HLT_PAJet60_NoJetID_v1",&Jet60);
        HltTree->SetBranchAddress("HLT_PAJet60_NoJetID_v1_Prescl",&Jet60_Prescl);
        HltTree->SetBranchAddress("HLT_PAJet80_NoJetID_v1",&Jet80);
        HltTree->SetBranchAddress("HLT_PAJet80_NoJetID_v1_Prescl",&Jet80_Prescl);
        HltTree->SetBranchAddress("HLT_PAJet100_NoJetID_v1",&Jet100);
        HltTree->SetBranchAddress("HLT_PAJet100_NoJetID_v1_Prescl",&Jet100_Prescl);

        HltTree->SetBranchAddress("L1_ZeroBias",&L1_ZeroBias);
        HltTree->SetBranchAddress("L1_ZeroBias_Prescl",&L1_ZeroBias_Prescl);
        HltTree->SetBranchAddress("L1_SingleJet16_BptxAND",&L1_SingleJet16_BptxAND);
        HltTree->SetBranchAddress("L1_SingleJet16_BptxAND_Prescl",&L1_SingleJet16_BptxAND_Prescl);
        HltTree->SetBranchAddress("L1_SingleJet36",&L1_SingleJet36);
        HltTree->SetBranchAddress("L1_SingleJet36_Prescl",&L1_SingleJet36_Prescl);	
	}


}

double Dmesonana::jettrigcomb()
{
	double weight_trig = 0.0;

	if( isPbPb )
	{
    	if( Jet55 && maxJetTrgPt > 55 && maxJetTrgPt < 65 ) weight_trig = Jet55_Prescl;
    	if( Jet65 && maxJetTrgPt > 65 && maxJetTrgPt < 80 ) weight_trig = Jet65_Prescl;
    	if( Jet80 && maxJetTrgPt > 80 ) weight_trig = Jet80_Prescl;
	}
	else
	{
		if( Jet20 && maxJetTrgPt >= 20 && maxJetTrgPt < 40 ) weight_trig = Jet20_Prescl;
		if( Jet40 && maxJetTrgPt >= 40 && maxJetTrgPt < 60 ) weight_trig = Jet40_Prescl;
		if( Jet60 && maxJetTrgPt >= 60 && maxJetTrgPt < 80 ) weight_trig = Jet60_Prescl;
		if( Jet80 && maxJetTrgPt >= 80 && maxJetTrgPt < 100 ) weight_trig = Jet80_Prescl;
		if( Jet100 && maxJetTrgPt >= 100 ) weight_trig = Jet100_Prescl;
	}

	return weight_trig;

}

//
//
void Dmesonana::LoopOverFile(int startFile, int endFile, char *filelist, int decaychannel) 
{//.. loop over files in the "*filelist" from startFile to endFile in sequence
	//
	Init(startFile, endFile, filelist);

	//
	ifstream file_stream(filelist);
	int ifile = 0;
	while (file_stream >> filename) {
		
		ifile++;
		if(ifile-1 >= endFile) {
			break;
		} else if(ifile-1 < startFile) {
			continue;
		}



		cout << "file  = " << ifile<<" name = "<<filename <<endl;

		if (!TFile::Open(filename.c_str()))   { cout << " fail to open file" << endl; continue;}

		TFile *f = TFile::Open(filename.c_str());


		hftree  = (TTree*)f->Get("HFtree/hftree");
		HltTree = (TTree*)f->Get("hltanalysis/HltTree");
		jetObjTree = (TTree*)f->Get("hltobject/jetObjTree");
		if( !isMC )  skimtree = (TTree*)f->Get("skimanalysis/HltTree");

		if( isMC )
		{
			if(!hftree || !HltTree || !jetObjTree ) {
				cout<<"===> empty tree <==="<<endl;
				continue;
			}
		}
		else
		{
		    if(!hftree || !HltTree || !jetObjTree || !skimtree) {
		    	cout<<"==> empty tree <=="<<endl;
			    continue;
		    }
		}

        if( isMC )
		{
		    jettree = ( TTree * ) f->Get("akPu3PFJetAnalyzer/t");
		    genparticletree = (TTree*)f->Get("HiGenParticleAna/hi");
		    if( !genparticletree || !jettree )  { cout<<"==> empty gentree or jet tree <=="<<endl; continue;}
		    hftree->AddFriend(genparticletree);
		    hftree->AddFriend(jettree);
		}

		if( isPbPb )
		{
			HiTree = ( TTree * ) f->Get("hiEvtAnalyzer/HiTree");
			if( !HiTree )  { cout << "==> empty HiTree <==" << endl; continue; }
			HiTree->SetBranchAddress("hiBin", &hiBin);
			HiTree->SetBranchAddress("run", &run);
			HiTree->SetBranchAddress("evt", &evt);
			HiTree->SetBranchAddress("vx", &vx);
			HiTree->SetBranchAddress("vy", &vy);
			HiTree->SetBranchAddress("vz", &vz);
			if( isMC ) HiTree->SetBranchAddress("Ncoll", &Ncoll);
			hftree->AddFriend(HiTree);
		}

		hftree->AddFriend(HltTree);
		hftree->AddFriend(jetObjTree);
		hftree->AddFriend(skimtree);

		hftree->SetBranchAddress("hfcandidate", &hfcandidate);
		if( !isMC )
		{
		   skimtree->SetBranchAddress("pHBHENoiseFilter",&pHBHENoiseFilter);
		   if( isPbPb )
		       skimtree->SetBranchAddress("pcollisionEventSelection",&pcollisionEventSelection);
		   else
			   skimtree->SetBranchAddress("pPAcollisionEventSelectionPA",&pcollisionEventSelection);
		}
        if( isMC )  jettree->SetBranchAddress("pthat", &pthat);

		get_tree_info();

		LoopOverEvt();

		f->Close();
	}

	write();
}

void Dmesonana::LoopOverEvt()
{
	for(int entry = 0; entry<hftree->GetEntries(); entry++) 
		//  for(int entry = 0; entry<100; entry++)
	{
		hftree->GetEntry(entry);

		if( !isMC )
		{
			if(!pHBHENoiseFilter || !pcollisionEventSelection) continue;
		}

		if( isPbPb )
		{
            MinBias = ( MinBias && L1_HcalHfCoincPmORBscMinBiasThresh1_BptxAND );
            Jet55   = ( Jet55 && L1_SingleJet36_BptxAND );
            Jet65   = ( Jet65 && L1_SingleJet36_BptxAND );
            Jet80   = ( Jet80 && L1_SingleJet52_BptxAND );

		    MinBias_Prescl = L1_HcalHfCoincPmORBscMinBiasThresh1_BptxAND_Prescl * MinBias_Prescl;
		    Jet55_Prescl = L1_SingleJet36_BptxAND_Prescl * Jet55_Prescl;
		    Jet65_Prescl = L1_SingleJet36_BptxAND_Prescl * Jet65_Prescl;
		    Jet80_Prescl = L1_SingleJet52_BptxAND_Prescl * Jet80_Prescl;
		}
		else
		{
            MinBias = ( MinBias && L1_ZeroBias );
			Jet20 = ( Jet20 && L1_SingleJet16_BptxAND );
			Jet40 = ( Jet40 && L1_SingleJet16_BptxAND );
			Jet60 = ( Jet60 && L1_SingleJet36 );
			Jet80 = ( Jet80 && L1_SingleJet36 );
			Jet100 = ( Jet100 && L1_SingleJet36 );

			MinBias_Prescl = MinBias_Prescl * L1_ZeroBias_Prescl;
			Jet20_Prescl = Jet20_Prescl * L1_SingleJet16_BptxAND_Prescl;
			Jet40_Prescl = Jet40_Prescl * L1_SingleJet16_BptxAND_Prescl;
			Jet60_Prescl = Jet60_Prescl * L1_SingleJet36_Prescl;
			Jet80_Prescl = Jet80_Prescl * L1_SingleJet36_Prescl;
			Jet100_Prescl = Jet100_Prescl * L1_SingleJet36_Prescl;
		}

        // for pp and PbPb data forest, trigger filter is added at forest level. But not added for pPb data forest
//		if( isPbPb && !isMC && !ispppPbMB  && !ispPbJettrig && !MinBias)   
//			cout << "Error!!!!!!!!!!!" << endl;   //PbPb MB data
		if( !isPbPb && !isMC && !ispppPbMB && !ispPbJettrig && !Jet20 && !Jet40 && !Jet60 && !Jet80 && !Jet100)    
			cout << "Error!!!!!!!!!!!!!" << endl;   // pp Jet trigger data
        if( ispPbJettrig && !Jet20 && !Jet40 && !Jet60 && !Jet80 && !Jet100 ) continue;      //pPb Jet trigger data
		if( ispppPbMB && !MinBias ) continue;   //pPb MB trigger data
//		if( isPbPb && !Jet55 && !Jet65 && !Jet80 )   continue;       //PbPb Jet trigger data

		pthatweight = 0.0;   // for data, always be 0
		ndcand = 0;

		if( isMC )       //pthat weight
		{
		    weight_pthat = 0.0;
		    int ibinpthat = -999;

		    for( int ibin = 0; ibin < NPTHATBIN; ibin++)
		    {
		    	if( pthat > pthatbin[ibin] && pthat < pthatbin[ibin+1] )
		    	{
		    		ibinpthat = ibin;
		    		break;
		    	}
		    }

		    if( ibinpthat < 0 ) continue;
		    weight_pthat = ( pthatweight_xsection[ibinpthat] * filtereff[ibinpthat] - pthatweight_xsection[ibinpthat+1] * filtereff[ibinpthat+1] ) / MCentries[ibinpthat] ;

			pthatweight = weight_pthat;

		    FindGenDmeson();
	     	gendmesontree->Fill();

            FindAllGenD0();
			allgend0tree->Fill();
		}

		trigweight = jettrigcomb();   //not needed for D0 with Minbias trigger, still do this to keep the code simpler
		    
		if( isMC ) pthat_weighted->Fill(pthat, weight_pthat); 

		bsx = hfcandidate->get_BSx();
		bsy = hfcandidate->get_BSy();
		bsz = hfcandidate->get_BSz();

//		cout <<"Beam Spot: " << hfcandidate->get_BSx() << "  " << hfcandidate->get_BSy() << "  " << hfcandidate->get_BSz() << endl;

		LoopOvercandidate();
		recodmesontree->Fill();

		hfcandidate->Reset();

		vector<int>().swap(dtype); vector<int>().swap(passingcuts);
		vector<float>().swap(dcandmass);    vector<float>().swap(dcandpt); vector<float>().swap(dcandeta); vector<float>().swap(dcandphi); vector<float>().swap(dcandy);
		vector<float>().swap(dcandsvx);  vector<float>().swap(dcandsvy); vector<float>().swap(dcandsvz);
		vector<float>().swap(dcandff3d);  vector<float>().swap(dcandffls3d); vector<float>().swap(dcandcosalpha); vector<float>().swap(dcandfprob); vector<float>().swap(dcandfchi2); 
		vector<float>().swap(dcandffxy); vector<float>().swap(dcandfflsxy); vector<float>().swap(dcandcosalphaxy); 
		vector<float>().swap(dcanddau1eta); vector<float>().swap(dcanddau2eta); 
		vector<float>().swap(dcanddau1pt); vector<float>().swap(dcanddau2pt); 
		vector<int>().swap(dcanddau1q); vector<int>().swap(dcanddau2q);
		vector<int>().swap(dcanddau1matchedpdg); vector<int>().swap(dcanddau2matchedpdg); vector<int>().swap(dcanddau1matchedmotherpdg); vector<int>().swap(dcanddau2matchedmotherpdg);
		vector<int>().swap(dcanddau1matchedmothersube); vector<int>().swap(dcanddau2matchedmothersube); vector<int>().swap(dcanddau1matchedmothernofdau); vector<int>().swap(dcanddau2matchedmothernofdau);
		vector<float>().swap(dcanddau1matchedmotherpt); vector<float>().swap(dcanddau2matchedmotherpt); vector<float>().swap(dcanddau1matchedmothereta); vector<float>().swap(dcanddau2matchedmothereta); vector<float>().swap(dcanddau1matchedmotherphi); vector<float>().swap(dcanddau2matchedmotherphi);
		vector<int>().swap(matchedtogen); vector<int>().swap(dcandmatchedpdg); vector<int>().swap(nongendoublecounted); 
		vector<float>().swap(dcandmatchedpt); vector<float>().swap(dcandmatchedff3d); vector<float>().swap(dcandmatchedy); vector<float>().swap(dcandmatchedeta); vector<float>().swap(dcandmatchedphi); vector<float>().swap(dcandmatchnofdau); 
		vector<float>().swap(dcandmatchedsvx); vector<float>().swap(dcandmatchedsvy); vector<float>().swap(dcandmatchedsvz); 
		vector<float>().swap(dcandmatcheddau1pt); vector<float>().swap(dcandmatcheddau2pt); 
		vector<int>().swap(matched_pdg_Bmom); 
		vector<float>().swap(matched_pt_Bmom); 

		dtype.clear(); matchedtogen.clear(); passingcuts.clear();
		dcanddau1matchedpdg.clear(); dcanddau2matchedpdg.clear(); dcanddau1matchedmotherpdg.clear(); dcanddau2matchedmotherpdg.clear();
		dcanddau1matchedmothersube.clear(); dcanddau2matchedmothersube.clear(); dcanddau1matchedmothernofdau.clear(); dcanddau2matchedmothernofdau.clear(); 
		dcanddau1matchedmotherpt.clear(); dcanddau2matchedmotherpt.clear(); dcanddau1matchedmothereta.clear(); dcanddau2matchedmothereta.clear(); dcanddau1matchedmotherphi.clear(); dcanddau2matchedmotherphi.clear(); 
		dcandsvx.clear(); dcandsvy.clear(); dcandsvz.clear();
		dcandmass.clear(); dcandpt.clear(); dcandeta.clear(); dcandy.clear(); dcandphi.clear(); dcandffls3d.clear(); dcandff3d.clear(); dcandcosalpha.clear(); dcandfprob.clear(); dcandfchi2.clear();
		dcandffxy.clear(); dcandfflsxy.clear(); dcandcosalphaxy.clear();
		dcanddau1eta.clear();  dcanddau2eta.clear();
		dcanddau1pt.clear();  dcanddau2pt.clear();
		dcanddau1q.clear();  dcanddau2q.clear();
		dcandmatchedpdg.clear();
		dcandmatchedff3d.clear();
		nongendoublecounted.clear();
		dcandmatchedpt.clear(); dcandmatchedy.clear(); dcandmatchedeta.clear();  dcandmatchedphi.clear(); dcandmatchnofdau.clear();
		dcandmatchedsvx.clear();
		dcandmatchedsvy.clear();
		dcandmatchedsvz.clear();
		dcandmatcheddau1pt.clear();  dcandmatcheddau2pt.clear();
		matched_pdg_Bmom.clear();   matched_pt_Bmom.clear();
	}
}


void Dmesonana::LoopOvercandidate()
{

	for(int icand = 0; icand<hfcandidate->get_nhfcand(); icand++) 
	{

		snglhfcand* cand = hfcandidate->get_hfcand(icand);

		if( cand->get_type() != 2 )  continue;

		type = cand->get_type();
		mass = cand->get_fm();
		fpt = cand->get_fpt();
		feta = cand->get_feta();
		fphi = cand->get_fphi();
		ffls3d = cand->get_ffls3d();
		ff3d = cand->get_ff3d();
		cosalpha = TMath::Cos(cand->get_falpha0());
		fprob = cand->get_fprob();
		fdr = cand->get_fdr();
		fchi2 = cand->get_fchi2();
		mass_dau = cand->get_fmdau1();
		fpt1 = cand->get_fpt1();
		fpt2 = cand->get_fpt2();
		feta1 = cand->get_feta1();
		feta2 = cand->get_feta2();
		fq1 = cand->get_fq1();   //it is float type in forest, which should be changed to int
		fq2 = cand->get_fq2();

		svx = cand->get_svx();
		svy = cand->get_svy();
		svz = cand->get_svz();

		ffxy = cand->get_ffxy();
		fflsxy = cand->get_fflsxy();
		cosalphaxy = TMath::Cos(cand->get_falpha0xy());

//
//		cout << " PV: " << vx << "  " << vy << "   " << vz << endl;
//		cout << " sv: " << cand->get_svx() << "  " << cand->get_svy() << "  " << cand->get_svz() << endl;
//		cout << " p:  " << fpt * TMath::Cos(fphi) << "  " << fpt * TMath::Sin(fphi) << "  " << fpt * TMath::SinH(feta) << endl;
//		cout << " ff3d: " << cand->get_ff3d() << "    falpha0: " << cand->get_falpha0() << endl;
//		cout << " ffxy: " << cand->get_ffxy() << "    falpha0xy: " << cand->get_falpha0xy() << endl;
//
//		cout << "from calculation: " << endl;
//
//		TVector3 pvtosv(cand->get_svx() - vx, cand->get_svy() - vy, cand->get_svz() - vz);
//		TVector3 plab( fpt * TMath::Cos(fphi), fpt * TMath::Sin(fphi), fpt * TMath::SinH(feta));
//		TVector3 pvtosvxy = pvtosv;
//		pvtosvxy.SetZ(0.0);
//		TVector3 plabxy = plab;
//		plabxy.SetZ(0.0);
//
//		cout << " ff3d: " << pvtosv.Mag() << "    falpha0: " << pvtosv.Angle(plab) << endl;
//		cout << " ffxy: " << pvtosvxy.Mag() << "    falpha0xy: " << pvtosvxy.Angle(plabxy) << endl;
//
//		cout << endl;

		TLorentzVector d0cand;
		d0cand.SetPtEtaPhiM(fpt, feta, fphi, mass);


        if( isMC )
		{
	    	gIndex1 = cand->get_gIndex1();
	    	gIndex2 = cand->get_gIndex2();
	    	gIndex_dau2 = cand->get_gIndex_dau2();
		}

		if( TMath::ACos(cosalpha) > 0.12 ) continue;
		if( ffls3d < 2.5 )  continue;
		if( fprob < 0.05 ) continue;

//		if( cosalpha < 0.9 )   continue;
//        if( fq1 * fq2 > 0 )  continue;  //applied in forest level except for the test production (not a full producton) used to do tmva and Data/Mc comparison study
		if( TMath::Abs( d0cand.Rapidity() ) > 1.0 )   continue;

		bool passingtopocuts = false;
		if(mass > cut_m_low[1] && mass < cut_m_high[1] && ffls3d > cut_ffls3d[1] && cosalpha > cut_cosfalpha0[1] && fdr < cut_fdr[1]) 
			passingtopocuts =  true;
		

		if( !isMC && !savealldcand && !passingtopocuts )  continue;
		if( isMC )
		{
			bool matchedtogend = false;
	    	bool matchedtogend0 = false;
	    	if( type == 2 )      matchedtogend0 = Matchd0();
			matchedtogend = matchedtogend0;
     		if( !savealldcand && !matchedtogend )   continue;
			matchedtogen.push_back(matchedtogend);

			int dau1 = gIndex1[0];
			int dau2 = gIndex2[0];

			if( dau1 == -999 )
			{
				dcanddau1matchedpdg.push_back(-999);
				dcanddau1matchedmotherpdg.push_back(-999);
				dcanddau1matchedmothersube.push_back(-999);
				dcanddau1matchedmothernofdau.push_back(-999);
				dcanddau1matchedmotherpt.push_back(-999.);
				dcanddau1matchedmothereta.push_back(-999.);
				dcanddau1matchedmotherphi.push_back(-999.);
			}
			else
			{
				dcanddau1matchedpdg.push_back(genpdg[dau1]);
				dcanddau1matchedmotherpdg.push_back(genpdg[genmotherIdx[dau1][0]]);
				dcanddau1matchedmothersube.push_back(gensube[genmotherIdx[dau1][0]]);
				dcanddau1matchedmothernofdau.push_back(gennDaughters[genmotherIdx[dau1][0]]);
				dcanddau1matchedmotherpt.push_back(genpt[genmotherIdx[dau1][0]]);
				dcanddau1matchedmothereta.push_back(geneta[genmotherIdx[dau1][0]]);
				dcanddau1matchedmotherphi.push_back(genphi[genmotherIdx[dau1][0]]);
			}

			if( dau2 == -999 )
			{
				dcanddau2matchedpdg.push_back(-999);
				dcanddau2matchedmotherpdg.push_back(-999);
				dcanddau2matchedmothersube.push_back(-999);
				dcanddau2matchedmothernofdau.push_back(-999);
				dcanddau2matchedmotherpt.push_back(-999.);
				dcanddau2matchedmothereta.push_back(-999.);
				dcanddau2matchedmotherphi.push_back(-999.);
			}
			else
			{
				dcanddau2matchedpdg.push_back(genpdg[dau2]);
				dcanddau2matchedmotherpdg.push_back(genpdg[genmotherIdx[dau2][0]]);
				dcanddau2matchedmothersube.push_back(gensube[genmotherIdx[dau2][0]]);
				dcanddau2matchedmothernofdau.push_back(gennDaughters[genmotherIdx[dau2][0]]);
				dcanddau2matchedmotherpt.push_back(genpt[genmotherIdx[dau2][0]]);
				dcanddau2matchedmothereta.push_back(geneta[genmotherIdx[dau2][0]]);
				dcanddau2matchedmotherphi.push_back(genphi[genmotherIdx[dau2][0]]);
			}
		}

		dtype.push_back(type);
		passingcuts.push_back(passingtopocuts);
		dcandmass.push_back(mass);
		dcandpt.push_back(fpt);
		dcandeta.push_back(feta);
		dcandy.push_back(d0cand.Rapidity());
		dcandphi.push_back(fphi);
		dcandffls3d.push_back(ffls3d);
		dcandff3d.push_back(ff3d);
		dcandcosalpha.push_back(cosalpha);
		dcandfprob.push_back(fprob);
		dcandfchi2.push_back(fchi2);
		dcanddau1eta.push_back(feta1);
		dcanddau2eta.push_back(feta2);
		dcanddau1pt.push_back(fpt1);
		dcanddau2pt.push_back(fpt2);
		dcanddau1q.push_back(fq1);
		dcanddau2q.push_back(fq2);

		dcandsvx.push_back(svx);
		dcandsvy.push_back(svy);
		dcandsvz.push_back(svz);
		dcandfflsxy.push_back(fflsxy);
		dcandffxy.push_back(ffxy);
		dcandcosalphaxy.push_back(cosalphaxy);

		ndcand++;

	}
}

void Dmesonana::FindGenDmeson()
{
	ngend = 0;
	for( int particle = 0; particle < mult; particle++ )
	{
		if( abs(genpdg[particle]) == 421 ) //D0
		{

//			if( geneta[particle] < -2.0 || geneta[particle] > 2.0 )  continue;
			if( gennDaughters[particle] != 2 )   continue;
			if( gensta[particle] != 2 )  continue;
			int dau1 = gendaughterIdx[particle][0];
			int dau2 = gendaughterIdx[particle][1];

			if( !( ( abs(genpdg[dau1]) == 321 && abs(genpdg[dau2]) == 211 ) || ( abs(genpdg[dau1]) == 211 && abs(genpdg[dau2]) == 321 ) ) )   continue;
			if( genchg[dau1] * genchg[dau2]  > 0 ) continue;

			TLorentzVector gend0;
			gend0.SetPtEtaPhiM(genpt[particle], geneta[particle], genphi[particle], MASSD0);

			dpt[ngend] = genpt[particle];
			deta[ngend] = geneta[particle];
			dy[ngend] = gend0.Rapidity();
			dphi[ngend] = genphi[particle];
			dpdg[ngend] = genpdg[particle];
			dsube[ngend] = gensube[particle];
			dnofdau[ngend] = gennDaughters[particle];

			pt_ddau[ngend][0] = genpt[dau1];
			pt_ddau[ngend][1] = genpt[dau2];
			pt_ddau[ngend][2] = -999;

			eta_ddau[ngend][0] = geneta[dau1];
			eta_ddau[ngend][1] = geneta[dau2];
			eta_ddau[ngend][2] = -999;

			phi_ddau[ngend][0] = genphi[dau1];
			phi_ddau[ngend][1] = genphi[dau2];
			phi_ddau[ngend][2] = -999;

			pdg_ddau[ngend][0] = genpdg[dau1];
			pdg_ddau[ngend][1] = genpdg[dau2];
			pdg_ddau[ngend][2] = -999;

			//calculate gen level decay lengtt
			dgenff3d[ngend] = -999;
			gensvx[ngend] = -999;
			gensvy[ngend] = -999;
			gensvz[ngend] = -999;

			if ( gendecaylength )
			{
				if( genvx_production[dau1] - genvx_production[dau2] > 0.001 )  cout << "Error !!!, not the same production vertex!!!!!" << endl;
				TVector3 v_svtopv( genvx_production[dau1] - genpvx, genvy_production[dau1] - genpvy, genvz_production[dau1] - genpvz);
//				cout << " production vx: " << genvx_production[dau1] << "  vy: " << genvy_production[dau1] << " vz: " << genvz_production[dau1] << endl;
//				cout << " genpv  vx: " << genpvx << "  vy: " << genpvy << "  vz: " << genpvz << endl;
//				cout << " dgenff3d: " << v_svtopv.Mag() << endl;
				dgenff3d[ngend] = v_svtopv.Mag();
				gensvx[ngend] = genvx_production[dau1];
				gensvy[ngend] = genvy_production[dau1];
				gensvz[ngend] = genvz_production[dau1];
			}

			dnofmom[ngend] = gennMothers[particle];
			
			if ( gennMothers[particle] == 1 )
			{
				 pdg_dmom[ngend] = genpdg[genmotherIdx[particle][0]];
				 pt_dmom[ngend] = genpt[genmotherIdx[particle][0]];
			}
			else
			{
				pdg_dmom[ngend] = -999;
				pt_dmom[ngend] = -999;
			}

            // decide if the D0 is from B feed down
			int pdg_Bmom_temp = -999;
			float pt_Bmom_temp = -999;
			int motherindex = -999;
			int daughterindex = particle;
			int igeneration = 0;
			//loop up the decay chain to see if there is B meson
			while( gennMothers[daughterindex] == 1 && pt_Bmom_temp < 0 && igeneration < 50)
			{
				motherindex = genmotherIdx[daughterindex][0];
				if( ( TMath::Abs( genpdg[motherindex] ) > 500 && TMath::Abs( genpdg[motherindex] ) < 600 ) || ( TMath::Abs( genpdg[motherindex] ) > 5000 && TMath::Abs( genpdg[motherindex] ) < 6000 ) )   //decide if there is B mesons or B baryons in the decay chain
				{
					pt_Bmom_temp = genpt[motherindex];
					pdg_Bmom_temp = genpdg[motherindex];
				}
				igeneration++;
//				cout << " daughterindex: " << daughterindex << "  motherindex: " << motherindex << endl;
				daughterindex = motherindex;
			}

			pdg_Bmom[ngend] = pdg_Bmom_temp;
			pt_Bmom[ngend] = pt_Bmom_temp;

			gend0pt_weighted->Fill(genpt[particle], weight_pthat);

			ngend++;
		}
		else if ( abs(genpdg[particle]) == 413 )
		{

		}
	}

}

void Dmesonana::FindAllGenD0()
{
	nallgend0 = 0;
	for( int particle = 0; particle < mult; particle++ )
	{
		if( ! ( abs(genpdg[particle]) == 421 ) ) continue;
		if( gennDaughters[particle] > 10 )  continue;

        //D0 information
		alld0pt[nallgend0] = genpt[particle];
		alld0eta[nallgend0] = geneta[particle];
		alld0phi[nallgend0] = genphi[particle];
		alld0pdg[nallgend0] = genpdg[particle];
		alld0sube[nallgend0] = gensube[particle];
		alld0dnofdau[nallgend0] = gennDaughters[particle];

		//D0 daughter information
		for( int idau = 0; idau < 10; idau++ )
		{
			pt_alld0dau[nallgend0][idau] = -999.;
			eta_alld0dau[nallgend0][idau] = -999.;
			phi_alld0dau[nallgend0][idau] = -999.;
			pdg_alld0dau[nallgend0][idau] = -999.;
		}
		for( int idau = 0; idau < gennDaughters[particle]; idau++ )
		{
			int idauindex = gendaughterIdx[particle][idau];
			pt_alld0dau[nallgend0][idau] = genpt[idauindex];
			eta_alld0dau[nallgend0][idau] = geneta[idauindex];
			phi_alld0dau[nallgend0][idau] = genphi[idauindex];
			pdg_alld0dau[nallgend0][idau] = genpdg[idauindex];
		}

		//decide if from B decay or not
		int pdg_Bmom_temp = -999;
		float pt_Bmom_temp = -999;
		int motherindex = -999;
		int daughterindex = particle;
		int igeneration = 0;
		//loop up the decay chain to see if there is B meson
		while( gennMothers[daughterindex] == 1 && pt_Bmom_temp < 0 && igeneration < 50)
		{
			motherindex = genmotherIdx[daughterindex][0];
			if( ( TMath::Abs( genpdg[motherindex] ) > 500 && TMath::Abs( genpdg[motherindex] ) < 600 ) || ( TMath::Abs( genpdg[motherindex] ) > 5000 && TMath::Abs( genpdg[motherindex] ) < 6000 ) )   //decide if there is B mesons or B baryons in the decay chain
			{
				pt_Bmom_temp = genpt[motherindex];
				pdg_Bmom_temp = genpdg[motherindex];
			}
			igeneration++;
			daughterindex = motherindex;
		}

		pdg_alld0Bmom[nallgend0] = pdg_Bmom_temp;
		pt_alld0Bmom[nallgend0] = pt_Bmom_temp;

		nallgend0++;
	}


}

//
void Dmesonana::write()
{//.. results 
	result->cd();
	if( isMC ) gendmesontree->Write();
	recodmesontree->Write();
	if( isMC ) allgend0tree->Write();
	pthat_weighted->Write();
	gend0pt_weighted->Write();
	result->Close();
}

//

bool Dmesonana::Matchd0()
{
	for( unsigned int n1 = 0; n1 < gIndex1.size(); n1++ )
	{
		for( unsigned int n2 = 0; n2 < gIndex2.size(); n2++ )
		{

			int dau1 = gIndex1[n1];
			int dau2 = gIndex2[n2];

			bool flag_nongendoublecounted = true; 

			if ( dau1 == -999 || dau2 == -999 )     continue;

			//mathed to two different gen particles
			if ( dau1 == dau2 )     continue;


			// one kaon, one pion 
			if( ! ( ( abs(genpdg[dau1]) == 211 && abs(genpdg[dau2]) == 321 )  || ( abs(genpdg[dau1]) == 321 && abs(genpdg[dau2]) == 211 ) ) )   
				continue;

			if ( abs(genpdg[dau1]) == 321 && abs(genpdg[dau2]) == 211 )  flag_nongendoublecounted = false;
			if ( abs(genpdg[dau1]) == 211 && abs(genpdg[dau2]) == 321 )  flag_nongendoublecounted = true;

			//only one mother
			if (!( gennMothers[dau1] == 1 && gennMothers[dau2] == 1 ))   continue;

			//mother index the same and not -999
			if ( !( genmotherIdx[dau1][0] == genmotherIdx[dau2][0] && genmotherIdx[dau1][0] != -999 ) )
				continue;

			int allmotherindex = genmotherIdx[dau1][0];
			//is D0 and just three daughters
			if( ! (abs (genpdg[allmotherindex]) == 421 && gennDaughters[allmotherindex] == 2) )  continue;

            TLorentzVector gend0;
            gend0.SetPtEtaPhiM(genpt[allmotherindex], geneta[allmotherindex], genphi[allmotherindex], MASSD0);

			nongendoublecounted.push_back(flag_nongendoublecounted);
			dcandmatchedpdg.push_back(genpdg[allmotherindex]);
			dcandmatchedpt.push_back(genpt[allmotherindex]);
			dcandmatchedy.push_back(gend0.Rapidity());
			dcandmatchedeta.push_back(geneta[allmotherindex]);
			dcandmatchedphi.push_back(genphi[allmotherindex]);
			dcandmatchnofdau.push_back(gennDaughters[allmotherindex]);
			dcandmatcheddau1pt.push_back(genpt[dau1]);
			dcandmatcheddau2pt.push_back(genpt[dau2]);
			
			//calculate gen decay length
			float genmatchedff3d = -999.;
			float genmatchedsvx = -999.;
			float genmatchedsvy = -999.;
			float genmatchedsvz = -999.;

			if ( gendecaylength )
			{
				if( genvx_production[dau1] - genvx_production[dau2] > 0.001 )  cout << "Error !!!, not the same production vertex!!!!!" << endl;
				TVector3 v_svtopv( genvx_production[dau1] - genpvx, genvy_production[dau1] - genpvy, genvz_production[dau1] - genpvz);
				genmatchedff3d = v_svtopv.Mag();
				genmatchedsvx = genvx_production[dau1];
				genmatchedsvy = genvy_production[dau1];
				genmatchedsvz = genvz_production[dau1];
			}

			dcandmatchedff3d.push_back(genmatchedff3d);
			dcandmatchedsvx.push_back(genmatchedsvx);
			dcandmatchedsvy.push_back(genmatchedsvy);
			dcandmatchedsvz.push_back(genmatchedsvz);

            // decide if the D0 is from B feed down
            int pdg_Bmom_temp = -999;
            float pt_Bmom_temp = -999;
            int motherindex = -999;
            int daughterindex = allmotherindex;
			int igeneration = 0;
            //loop up the decay chain to see if there is B meson
            while( gennMothers[daughterindex] == 1 && pt_Bmom_temp < 0 && igeneration < 50 )
            {
                motherindex = genmotherIdx[daughterindex][0];
                if( ( TMath::Abs( genpdg[motherindex] ) > 500 && TMath::Abs( genpdg[motherindex] ) < 600 ) || ( TMath::Abs( genpdg[motherindex] ) > 5000 && TMath::Abs( genpdg[motherindex] ) < 6000 ))   //decide if there is B mesons or B baryons in the decay chain
                {
                    pt_Bmom_temp = genpt[motherindex];
                    pdg_Bmom_temp = genpdg[motherindex];
                }
//				cout << "1111111" << endl;
				igeneration++;
				if( igeneration > 50 )  break;
                daughterindex = motherindex;
            }

            matched_pdg_Bmom.push_back( pdg_Bmom_temp );
            matched_pt_Bmom.push_back( pt_Bmom_temp );;

			return true;

		}
	}

	if( savealldcand )
	{
	   dcandmatchedff3d.push_back(-999);
	   dcandmatchedsvx.push_back(-999);
	   dcandmatchedsvy.push_back(-999);
	   dcandmatchedsvz.push_back(-999);
	   nongendoublecounted.push_back(-999);
	   dcandmatchedpdg.push_back(-999);
	   dcandmatchedpt.push_back(-999);
	   dcandmatchedy.push_back(-999);
	   dcandmatchedeta.push_back(-999);
	   dcandmatchedphi.push_back(-999);
	   dcandmatchnofdau.push_back(-999);
	   dcandmatcheddau1pt.push_back(-999);
	   dcandmatcheddau2pt.push_back(-999);
	   matched_pdg_Bmom.push_back(-999);
	   matched_pt_Bmom.push_back(-999);
	}

	return false;

}

bool Dmesonana::Matchdstar()
{
	for( unsigned int n1 = 0; n1 < gIndex1.size(); n1++ )
	{
		for( unsigned int n2 = 0; n2 < gIndex2.size(); n2++ )
		{
			for ( unsigned int n3 = 0; n3 < gIndex_dau2.size(); n3++ )
			{

				int dau1 = gIndex1[n1];
				int dau2 = gIndex2[n2];
				int dau3 = gIndex_dau2[n3];

				//				if ( fpt1 < 1.0 || fpt2 < 1.0 )    continue;

				if ( dau3 == -999 || dau1 == -999 || dau2 == -999 )     continue;

				//mathed to three different gen particles
				if ( dau1 == dau2 || dau1 == dau3 || dau2 == dau3 )     continue;


				// one kaon, two pion 
				if( !( ( abs(genpdg[dau1]) == 211 && abs(genpdg[dau2]) == 321 ) ) )
					continue;

				if ( abs(genpdg[dau3]) != 211 )   continue;

				//only one mother
				if (!( gennMothers[dau1] == 1 && gennMothers[dau2] == 1 && gennMothers[dau3] == 1 ))   continue;

				//mother index the same and not -999
				if ( !( genmotherIdx[dau1][0] == genmotherIdx[dau2][0] && genmotherIdx[dau1][0] != -999 ) )
					continue;

				int d0index = genmotherIdx[dau1][0];
				//is D charged and just three daughters
				if( ! (abs (genpdg[d0index]) == 421 && gennDaughters[d0index] == 2) )  continue;

				if( gennMothers[d0index] != 1 || genmotherIdx[d0index][0] != genmotherIdx[dau3][0] || genmotherIdx[dau3][0] == -999 )    continue;

				int allmotherindex = genmotherIdx[d0index][0];

				if( ! (abs(genpdg[allmotherindex]) == 413 && gennDaughters[allmotherindex] == 2) )  continue;

				return true;

			}
		}
	}

	return false;


}
void Dmesonana::define_cuts()
{

	//D*->D0+pi
	cut_m_low[0] = 1.92;
	cut_m_high[0] = 2.10;
	cut_m_dau_low[0] = 1.8;
	cut_m_dau_high[0] = 1.92;
	cut_ffls3d[0] = 2.0;
	cut_cosfalpha0[0] = 0.975;
	cut_fprob[0] = 0.05;
	cut_fdr[0] = 0.25;
	cut_fchi2[0] = 3;

	//D0->K+pi
	cut_m_low[1] = 1.70;
	cut_m_high[1] = 2.05;
	cut_m_dau_low[1] = -1;
	cut_m_dau_high[1] = 1;
	cut_ffls3d[1] = 2.0;
	cut_cosfalpha0[1] = 0.975;
	cut_fprob[1] = 0.05;
	cut_fdr[1] = 0.25;
	cut_fchi2[1] = 3;

	//D+/- = K+pi+pi
	cut_m_low[2] = 1.70;
	cut_m_high[2] = 2.05;
	cut_m_dau_low[2] = 0.5;
	cut_m_dau_high[2] = 2.05;
	cut_ffls3d[2] = 2.0;
	cut_cosfalpha0[2] = 0.975;
	cut_fprob[2] = 0.05;
	cut_fdr[2] = 0.25;
	cut_fchi2[2] = 3;


}
