#include <iostream>
#include <fstream>
#include <vector>
#include <math.h>
#include <algorithm>
#include <sstream>
#include <string>
#include <set>
#include "TH1.h"
#include "TF1.h"
#include "TTree.h"
#include "TFile.h"
#include "TNtupleD.h"
#include "TNtuple.h"
#include "TROOT.h"
#include "TChain.h"
#include "TMath.h"

//#define NPTHATBINS 3
//double pthatbins[NPTHATBINS+1] = {0., 15., 30.,  1000.};

#define NPTHATBINS 6
double pthatbins[NPTHATBINS+1] = {0., 5., 15., 30., 50., 80., 1000.};

using namespace std;

void CountMCEvts_pthatbin()
{
	TH1F * pthat_all = new TH1F("pthat_all","pthat_all",NPTHATBINS, pthatbins);
	TTree * jettree = NULL;

	std::string filelist = "hiforest_PbPb_Pyquen_D0embedded_D0pt3_pthat015305080_1217_1223.lis";
	ifstream file_stream(filelist.c_str());
	string filename;
	int ifile = 0;
	while (file_stream >> filename) 
	{
		ifile++;
		cout << "file  = " << ifile<<" name = "<<filename <<endl;
		if (!TFile::Open(filename.c_str()))   { cout << " fail to open file" << endl; continue;}
		TFile *f = TFile::Open(filename.c_str());

        jettree = ( TTree * ) f->Get("akPu3PFJetAnalyzer/t");
		if( !jettree )   cout << "Empty Tree!!!!!!!!!!" << endl;
		Float_t pthat;
		jettree->SetBranchAddress("pthat", &pthat);

		for(int entry = 0; entry < jettree->GetEntries(); entry++)
		{
			jettree->GetEntry(entry);
			pthat_all->Fill(pthat);

		}

		f->Close();

	}

	for( int ibin = 0 ; ibin < NPTHATBINS ; ibin++ )
	{
		cout << " Number of events with pthat " << pthatbins[ibin] << " to " << pthatbins[ibin+1] << " is " << pthat_all->GetBinContent(ibin + 1) << endl;
	}

	TFile * outputfile = new TFile("pthatall.root","RECREATE");
	pthat_all->Write();
	outputfile->Close();

}
