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
#include "Dmesonana.hh"
#include <iomanip>
//#include "./../interface/hfcand_v1.hh"
#include "UserCode/OpenHF/interface/hfcand_v1.hh"

bool savealldcand = false;
bool isMC = false;
bool isPbPb = true;
bool ispppPbMB = false;
bool ispPbJettrig = false;

//////for D0 Hydjet samples
//#define NPTHATBIN 5
//int MCentries[NPTHATBIN] = { 19240, 19321, 18992, 20010, 22437};
//int pthatbin[NPTHATBIN+1] = { 0, 15, 30, 50, 80, 1000};
//double pthatweight_xsection[NPTHATBIN+1] = {41.30, 0.2035, 1.087E-2, 1.014E-03, 1.004E-04, 1.756E-15};
//double filtereff[NPTHATBIN+1] = { 0.01194, 0.09132, 0.12752, 0.15206, 0.1694, 0.0945};

//////for D0 Hydjet samples, pthat from 5
//#define NPTHATBIN 5
//int MCentries[NPTHATBIN] = { 12906, 19321, 18992, 20010, 22437};
//int pthatbin[NPTHATBIN+1] = { 5, 15, 30, 50, 80, 1000};
//double pthatweight_xsection[NPTHATBIN+1] = {12.31, 0.2035, 1.087E-2, 1.014E-03, 1.004E-04, 1.756E-15};
//double filtereff[NPTHATBIN+1] = { 0.03716, 0.09132, 0.12752, 0.15206, 0.1694, 0.0945};

//for D0 pythia samples
#define NPTHATBIN 6
int MCentries[NPTHATBIN] = { 16429, 24025, 23931, 25301, 24302, 27877};
int pthatbin[NPTHATBIN+1] = {0,15,30,50,80,120,1000};
double pthatweight_xsection[NPTHATBIN+1] = {41.30, 0.2035, 1.087E-2, 1.014E-03, 1.004E-04, 1.121E-05, 1.756E-15};
double filtereff[NPTHATBIN+1] = { 0.01194, 0.09132, 0.12752,  0.15206, 0.1694, 0.17794, 0.0945};

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
	sprintf(outfilename, "Dmesonana_%s_%dTo%d.root",  filelist, startFile, endFile);
	result = new TFile(outfilename, "recreate");

	//

	hftree = 0;
	genparticletree = 0;
	jetObjTree = 0;
	HltTree = 0;
	jettree = 0;
	skimtree = 0;

	hfcandidate = new hfcand_v1;

	//	for ( int i = 0; i < NJETTRIG; i++)
	//		Jettrig_trigObject[i] = new trigO;

	define_cuts();

	if( isMC )
	{
    	gendmesontree = new TTree("gendmesontree","gendmesontree");
    	gendmesontree->Branch("ngend",&ngend,"ngend/I");
    	gendmesontree->Branch("pthat",&pthat, "pthat/F");
    	gendmesontree->Branch("weight_pthat",&weight_pthat, "weight_pthat/D");
    	gendmesontree->Branch("dpt", dpt, "dpt[ngend]/F");
    	gendmesontree->Branch("deta", deta, "deta[ngend]/F");
    	gendmesontree->Branch("dphi", dphi, "dphi[ngend]/F");
    	gendmesontree->Branch("dpdg", dpdg, "dpdg[ngend]/I");
    	gendmesontree->Branch("pt_ddau", pt_ddau, "pt_ddau[ngend][3]/F");
    	gendmesontree->Branch("eta_ddau", eta_ddau, "eta_ddau[ngend][3]/F");
    	gendmesontree->Branch("phi_ddau", phi_ddau, "phi_ddau[ngend][3]/F");
    	gendmesontree->Branch("pdg_ddau", pdg_ddau, "pdg_ddau[ngend][3]/I");
		gendmesontree->Branch("dnofmom", dnofmom, "dnofmom[ngend]/I");
		gendmesontree->Branch("pdg_dmom", pdg_dmom, "pdg_dmom[ngend]/I");
		gendmesontree->Branch("pt_dmom", pt_dmom, "pt_dmom[ngend]/F");
		gendmesontree->Branch("pdg_Bmom", pdg_Bmom, "pdg_Bmom[ngend]/I");
		gendmesontree->Branch("pt_Bmom", pt_Bmom, "pt_Bmom[ngend]/F");
	}

	recodmesontree = new TTree("recodmesontree","recodmesontree");
	//	recodmesontree->Branch("hiBin", &hiBin, "hiBin/D");
	if( isPbPb )
	{
    	recodmesontree->Branch("MinBias", &MinBias, "MinBias/I");
    	recodmesontree->Branch("MinBias_Prescl", &MinBias_Prescl, "MinBias_Prescl/I");
    	recodmesontree->Branch("Jet55", &Jet55, "Jet55/I");
    	recodmesontree->Branch("Jet55_Prescl", &Jet55_Prescl, "Jet55_Prescl/I");
    	recodmesontree->Branch("Jet65", &Jet65, "Jet65/I");
    	recodmesontree->Branch("Jet65_Prescl", &Jet65_Prescl, "Jet65_Prescl/I");
    	recodmesontree->Branch("Jet80", &Jet80, "Jet80/I");
    	recodmesontree->Branch("Jet80_Prescl", &Jet80_Prescl, "Jet80_Prescl/I");
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
	recodmesontree->Branch("passingcuts", &passingcuts);
	recodmesontree->Branch("dcandmass", &dcandmass);
	recodmesontree->Branch("dcandpt", &dcandpt);
	recodmesontree->Branch("dcandeta", &dcandeta);
	recodmesontree->Branch("dcandphi", &dcandphi);
	recodmesontree->Branch("dcandffls3d", &dcandffls3d);
	recodmesontree->Branch("dcandalpha", &dcandalpha);
	recodmesontree->Branch("dcandfprob", &dcandfprob);
	recodmesontree->Branch("dcandfchi2", &dcandfchi2);
	recodmesontree->Branch("dcanddau1eta", &dcanddau1eta);
	recodmesontree->Branch("dcanddau2eta", &dcanddau2eta);
	recodmesontree->Branch("dcanddau1pt", &dcanddau1pt);
	recodmesontree->Branch("dcanddau2pt", &dcanddau2pt);
	if( isMC )
	{
    	recodmesontree->Branch("matchedtogen", &matchedtogen);
		recodmesontree->Branch("nongendoublecounted", &nongendoublecounted);
    	recodmesontree->Branch("dcandmatchedpdg", &dcandmatchedpdg);
    	recodmesontree->Branch("dcandmatchedpt", &dcandmatchedpt);
    	recodmesontree->Branch("dcandmatchedeta", &dcandmatchedeta);
    	recodmesontree->Branch("dcandmatchedphi", &dcandmatchedphi);
    	recodmesontree->Branch("dcandmatchnofdau", &dcandmatchnofdau);
    	recodmesontree->Branch("dcandmatcheddau1pt", &dcandmatcheddau1pt);
    	recodmesontree->Branch("dcandmatcheddau2pt", &dcandmatcheddau2pt);
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
        genparticletree->SetBranchAddress("mult", &mult);
    	genparticletree->SetBranchAddress("pt", genpt);
    	genparticletree->SetBranchAddress("eta", geneta);
    	genparticletree->SetBranchAddress("phi", genphi);
    	genparticletree->SetBranchAddress("pdg", genpdg);
    	genparticletree->SetBranchAddress("chg", genchg);
    	genparticletree->SetBranchAddress("matchingID", genmatchingID);
    	genparticletree->SetBranchAddress("nMothers", gennMothers);
    	genparticletree->SetBranchAddress("motherIdx", genmotherIdx);
    	genparticletree->SetBranchAddress("nDaughters", gennDaughters);
    	genparticletree->SetBranchAddress("daughterIdx", gendaughterIdx);
    	genparticletree->SetBranchAddress("sta", gensta);
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

	    //gen particle tree
	    if( isMC )
	    {
//	        HltTree->SetBranchAddress("HLT_HIJet55_v7",&Jet55);
//	        HltTree->SetBranchAddress("HLT_HIJet55_v7_Prescl",&Jet55_Prescl);
//	        HltTree->SetBranchAddress("HLT_HIJet65_v7",&Jet65);
//	        HltTree->SetBranchAddress("HLT_HIJet65_v7_Prescl",&Jet65_Prescl);
//	        HltTree->SetBranchAddress("HLT_HIJet80_v7",&Jet80);
//	        HltTree->SetBranchAddress("HLT_HIJet80_v7_Prescl",&Jet80_Prescl);
//	        HltTree->SetBranchAddress("HLT_HIJet95_v7",&Jet95);
//	        HltTree->SetBranchAddress("HLT_HIJet95_v7_Prescl",&Jet95_Prescl);
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
//    	if( MinBias && maxJetTrgPt < 55 )  weight_trig = MinBias_Prescl;
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

        // for pp and PbPb data forest, trigger filter is added at forest level. But not for pPb data
		
		if( isPbPb && !isMC && !ispppPbMB  && !ispPbJettrig && !MinBias)   
			cout << "Error!!!!!!!!!!!" << endl;   //PbPb MB data
		if( !isPbPb && !isMC && !ispppPbMB && !ispPbJettrig && !Jet20 && !Jet40 && !Jet60 && !Jet80 && !Jet100)    
			cout << "Error!!!!!!!!!!!" << endl;   // pp Jet trigger data

        if( ispPbJettrig && !Jet20 && !Jet40 && !Jet60 && !Jet80 && !Jet100 ) continue;      //pPb Jet trigger data
		if( ispppPbMB && !MinBias ) continue;   //pPb MB trigger data

//		if( isPbPb && !MinBias && !Jet55 && !Jet65 && !Jet80 )   continue;       //PbPb Jet trigger data

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
		}

		trigweight = jettrigcomb();
		    
		if( isMC ) pthat_weighted->Fill(pthat, weight_pthat); 

		LoopOvercandidate();
		recodmesontree->Fill();

		hfcandidate->Reset();

		dtype.clear(); matchedtogen.clear(); passingcuts.clear();
		dcandmass.clear(); dcandpt.clear(); dcandeta.clear(); dcandphi.clear(); dcandffls3d.clear(); dcandalpha.clear(); dcandfprob.clear(); dcandfchi2.clear();
		dcanddau1eta.clear();  dcanddau2eta.clear();
		dcanddau1pt.clear();  dcanddau2pt.clear();
		dcandmatchedpdg.clear();
		nongendoublecounted.clear();
		dcandmatchedpt.clear(); dcandmatchedeta.clear();  dcandmatchedphi.clear(); dcandmatchnofdau.clear();
		dcandmatcheddau1pt.clear();  dcandmatcheddau2pt.clear();
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
		alpha = cand->get_falpha0();
		fprob = cand->get_fprob();
		fdr = cand->get_fdr();
		fchi2 = cand->get_fchi2();
		mass_dau = cand->get_fmdau1();
		fpt1 = cand->get_fpt1();
		fpt2 = cand->get_fpt2();
		feta1 = cand->get_feta1();
		feta2 = cand->get_feta2();

        if( isMC )
		{
	    	gIndex1 = cand->get_gIndex1();
	    	gIndex2 = cand->get_gIndex2();
	    	gIndex_dau2 = cand->get_gIndex_dau2();
		}

		if( feta < -2.0 || feta > 2.0 ) continue;
		if( fpt < 3.5  )  continue;

		bool passingtopocuts = false;
		if(mass > cut_m_low[1] && mass < cut_m_high[1] && ffls3d > cut_ffls3d[1] && alpha < cut_falpha0[1] && fprob > cut_fprob[1] && fdr < cut_fdr[1] && fchi2 < cut_fchi2[1]) 
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
		}

		dtype.push_back(type);
		passingcuts.push_back(passingtopocuts);
		dcandmass.push_back(mass);
		dcandpt.push_back(fpt);
		dcandeta.push_back(feta);
		dcandphi.push_back(fphi);
		dcandffls3d.push_back(ffls3d);
		dcandalpha.push_back(alpha);
		dcandfprob.push_back(fprob);
		dcandfchi2.push_back(fchi2);
		dcanddau1eta.push_back(feta1);
		dcanddau2eta.push_back(feta2);
		dcanddau1pt.push_back(fpt1);
		dcanddau2pt.push_back(fpt2);

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

			if( geneta[particle] < -2.0 || geneta[particle] > 2.0 )  continue;
			if( gennDaughters[particle] != 2 )   continue;
			if( gensta[particle] != 2 )  continue;
			int dau1 = gendaughterIdx[particle][0];
			int dau2 = gendaughterIdx[particle][1];

			if( !( ( abs(genpdg[dau1]) == 321 && abs(genpdg[dau2]) == 211 ) || ( abs(genpdg[dau1]) == 211 && abs(genpdg[dau2]) == 321 ) ) )   continue;
			if( genchg[dau1] * genchg[dau2]  > 0 ) continue;

			dpt[ngend] = genpt[particle];
			deta[ngend] = geneta[particle];
			dphi[ngend] = genphi[particle];
			dpdg[ngend] = genpdg[particle];
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

			int pdg_Bmom_temp = -999;
			float pt_Bmom_temp = -999;

			int motherindex = -999;
			int daughterindex = particle;

			while( gennMothers[daughterindex] == 1 && pt_Bmom_temp < 0 )
			{
				motherindex = genmotherIdx[daughterindex][0];
				if( TMath::Abs( genpdg[motherindex] ) > 500 && TMath::Abs( genpdg[motherindex] ) < 600 )
				{
					pt_Bmom_temp = genpt[motherindex];
					pdg_Bmom_temp = genpdg[motherindex];
				}
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

//
void Dmesonana::write()
{//.. results 
	result->cd();
	if( isMC ) gendmesontree->Write();
	recodmesontree->Write();
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
			//is D charged and just three daughters
			if( ! (abs (genpdg[allmotherindex]) == 421 && gennDaughters[allmotherindex] == 2) )  continue;

			nongendoublecounted.push_back(flag_nongendoublecounted);
			dcandmatchedpdg.push_back(genpdg[allmotherindex]);
			dcandmatchedpt.push_back(genpt[allmotherindex]);
			dcandmatchedeta.push_back(geneta[allmotherindex]);
			dcandmatchedphi.push_back(genphi[allmotherindex]);
			dcandmatchnofdau.push_back(gennDaughters[allmotherindex]);
			dcandmatcheddau1pt.push_back(genpt[dau1]);
			dcandmatcheddau2pt.push_back(genpt[dau2]);

			return true;

		}
	}

	if( savealldcand )
	{
	   nongendoublecounted.push_back(-999);
	   dcandmatchedpdg.push_back(-999);
	   dcandmatchedpt.push_back(-999);
	   dcandmatchedeta.push_back(-999);
	   dcandmatchedphi.push_back(-999);
	   dcandmatchnofdau.push_back(-999);
	   dcandmatcheddau1pt.push_back(-999);
	   dcandmatcheddau2pt.push_back(-999);
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
	cut_falpha0[0] = 0.2;
	cut_fprob[0] = 0.05;
	cut_fdr[0] = 0.25;
	cut_fchi2[0] = 3;

	//D0->K+pi
	cut_m_low[1] = 1.70;
	cut_m_high[1] = 2.05;
	cut_m_dau_low[1] = -1;
	cut_m_dau_high[1] = 1;
	cut_ffls3d[1] = 2.0;
	cut_falpha0[1] = 0.2;
	cut_fprob[1] = 0.08;
	cut_fdr[1] = 0.25;
	cut_fchi2[1] = 3;

	//D+/- = K+pi+pi
	cut_m_low[2] = 1.70;
	cut_m_high[2] = 2.05;
	cut_m_dau_low[2] = 0.5;
	cut_m_dau_high[2] = 2.05;
	cut_ffls3d[2] = 2.0;
	cut_falpha0[2] = 0.2;
	cut_fprob[2] = 0.05;
	cut_fdr[2] = 0.25;
	cut_fchi2[2] = 3;


}
