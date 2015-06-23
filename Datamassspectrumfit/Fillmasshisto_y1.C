#include <string>
#include <vector>
#include <map>
#include <iostream>
#include <TFile.h>
#include <TH1F.h>
#include <TF1.h>
#include <TNamed.h>
#include <TNtuple.h>
#include <TTree.h>
#include <TMath.h>
#include <TCanvas.h>
#include <TStyle.h>
#include <TLatex.h>
#include <TLegend.h>
#include "Math/MinimizerOptions.h"

#include "./../PtBins_rapidity1.h"
using namespace std;

bool evtunprescaleMB = false;   //false to fit raw counts without unprescale MB trigger
bool isMC = false;

float cut_m_low = 1.70;
float cut_m_high = 2.05;
int massbin = 35;

float hiBin_low = 99.5;
float hiBin_high = 199.5;
int rapidityrange = 1;
float dautrackptcut = 1999.; // depending on rapidity
float dautracketacut = 1.1;

TH1F* hfg_minbias[NPT];  //for D0

void book_hist()
{
    TH1::SetDefaultSumw2();

	char hname[100], pt_range[1000];
	for(int i = 0; i<NPT; i++)
	{
		float pt_low = ptbins[i];
		float pt_high = ptbins[i+1];
		sprintf(pt_range, "p_{T}: %2.1f to %2.1f GeV", pt_low, pt_high);
		sprintf(hname, "hfg_minbias_%d", i);
		hfg_minbias[i] = new TH1F(hname, pt_range, massbin, cut_m_low, cut_m_high);
		hfg_minbias[i]->Sumw2();
	}
}

void write_histo( TFile * output)
{
   for(int i = 0; i<NPT; i++)
   {
	   hfg_minbias[i]->Write();
   }
}

int decideptbin( float dpt )
{
    int ipt = -1;
    for ( int i = 0 ; i < NPT; i++)
    {
        if (dpt >= ptbins[i] && dpt < ptbins[i+1])  { ipt = i; break; }
    }
	if ( dpt > ptbins[NPT] ) ipt = NPT-1;
    return ipt;
}

void decideeffectivecuts(double dpt, double &effectiveffls3dcut, double &effectivecosalphacut, double &effectiveprobcut)
{
	for( int i = 0; i < NCUTPT; i++ )
	{
		if( dpt >= cut_pt_edge[i] && dpt < cut_pt_edge[i+1] )
		{
			effectiveffls3dcut = ffls3dcut[i];
			effectivecosalphacut = TMath::Cos(alphacut[i]);
			effectiveprobcut = fprobcut[i];
			break;
		}
	}
	return;
}

void Fillmasshisto_y1()
{
	book_hist();
	if( rapidityrange == 1 ) dautrackptcut = 1.0;
	cout << "  dautrackptcut : " << dautrackptcut << endl;

	TH1D * hf_mb = new TH1D("hf_mb","hf_mb",10,-5,5);
	hf_mb->Sumw2();

    TFile * input = new TFile("/tmp/sun229/Dmesonana_Rereco_MBtrig_d0pt0_tk0p4_d2p5_alpha0p2_tight_nojet_0510_all.root");
    TTree * recodmesontree = (TTree *) input->Get("recodmesontree");
    

    int MinBias;
    int MinBias_Prescl;

    int ndcand;
    int hiBin;
    double pthatweight;
    double trigweight;
    vector<int> *dtype = 0, *passingcuts = 0;
    vector<float> *dcandmass = 0, *dcandpt = 0, *dcandy = 0, *dcandphi = 0, *dcandffls3d = 0, *dcandcosalpha = 0, *dcandfprob = 0, *dcandfchi2 = 0;
    vector<float> *dcanddau1eta = 0, *dcanddau2eta = 0, *dcanddau1pt = 0, *dcanddau2pt = 0;

    recodmesontree->SetBranchAddress("MinBias", &MinBias);
    recodmesontree->SetBranchAddress("MinBias_Prescl", &MinBias_Prescl);
	recodmesontree->SetBranchAddress("hiBin", &hiBin);
    recodmesontree->SetBranchAddress("pthatweight", &pthatweight);
    recodmesontree->SetBranchAddress("trigweight", &trigweight);
    recodmesontree->SetBranchAddress("ndcand", &ndcand);
    recodmesontree->SetBranchAddress("dtype", &dtype);
    recodmesontree->SetBranchAddress("passingcuts", &passingcuts);
    recodmesontree->SetBranchAddress("dcandmass", &dcandmass);
    recodmesontree->SetBranchAddress("dcandpt", &dcandpt);
    recodmesontree->SetBranchAddress("dcandy", &dcandy);
    recodmesontree->SetBranchAddress("dcandphi", &dcandphi);
    recodmesontree->SetBranchAddress("dcandffls3d", &dcandffls3d);
    recodmesontree->SetBranchAddress("dcandcosalpha", &dcandcosalpha);
    recodmesontree->SetBranchAddress("dcandfprob", &dcandfprob);
    recodmesontree->SetBranchAddress("dcandfchi2", &dcandfchi2);
    recodmesontree->SetBranchAddress("dcanddau1eta", &dcanddau1eta);
    recodmesontree->SetBranchAddress("dcanddau2eta", &dcanddau2eta);
	recodmesontree->SetBranchAddress("dcanddau1pt", &dcanddau1pt);
	recodmesontree->SetBranchAddress("dcanddau2pt", &dcanddau2pt);
    
//   cout << " total number of event: " << recodmesontree->GetEntries() << endl;
   for ( int entry = 0; entry < recodmesontree->GetEntries(); entry++ )
//   for ( unsigned int entry = 0; entry < 2000000; entry++ )
   {
	   recodmesontree->GetEntry(entry);
	   if( entry % 1000000 == 0 )  cout << entry+1 << "st event" << endl;
	   if( !MinBias ) continue;
	   if( ndcand != dtype->size() || ndcand != passingcuts->size() || ndcand != dcandmass->size() || ndcand != dcandpt->size() )    
		   cout << "Error!!!!!!!!" << endl;
	   if( hiBin < hiBin_low || hiBin > hiBin_high )   continue;

       hf_mb->Fill(MinBias, MinBias_Prescl);
	   for( int icand = 0; icand < ndcand; icand++ )
	   {
		   if( dtype->at(icand) != 2 )   cout << " Error!!!!!!! Just working on D0 now" << endl;

		   if( TMath::Abs( dcandy->at(icand) ) > rapidityrange )  continue;
		   if( TMath::Abs( dcanddau1eta->at(icand) ) > dautracketacut || TMath::Abs( dcanddau2eta->at(icand) ) > dautracketacut )   continue;
		   if( dcanddau1pt->at(icand) < dautrackptcut || dcanddau2pt->at(icand) < dautrackptcut )  continue;
		   
           double effectiveffls3dcut = 100000.;
		   double effectivecosalphacut = 2.0;
		   double effectiveprobcut = -1.0;
           
		   decideeffectivecuts(dcandpt->at(icand), effectiveffls3dcut, effectivecosalphacut, effectiveprobcut);
//		   if( dcandpt->at(icand) > 7.0 )
//		   cout << "dcandpt: " << dcandpt->at(icand) << "  " << effectiveffls3dcut << "  " << effectiveprobcut << endl;

		   if( dcandffls3d->at(icand) < effectiveffls3dcut || dcandcosalpha->at(icand) < effectivecosalphacut || dcandfprob->at(icand) < effectiveprobcut )   
			   continue;

		   int ipt = decideptbin( dcandpt->at(icand) );
		   if( ipt < 0 ) continue;
//		   cout << " pt: " << dcandpt->at(icand) << "  ipt: " << ipt << endl;
           double weight = 1.0;
           if( !isMC )
               weight = MinBias_Prescl;
           else
               weight = pthatweight;
		   if( !evtunprescaleMB )   weight = 1.0;
           hfg_minbias[ipt]->Fill(dcandmass->at(icand), weight);

	   }
   }

   gStyle->SetOptFit(0);
   gStyle->SetOptStat(0);
   gStyle->SetTitleX(0.1f);
   gStyle->SetTitleW(0.8f);
   gStyle->SetTitleFontSize(0.06);
   
   char outputfile[200];
   sprintf(outputfile,"rootfiles/Masshisto_data_ptbin_%d_ptd_unpreMBtrig_%d_cent%2.0fto%2.0f_y%d_tkpt%.1f.root", NPT, evtunprescaleMB, hiBin_low * 0.5, hiBin_high * 0.5, rapidityrange, dautrackptcut);
   TFile * output = new TFile(outputfile,"RECREATE");
   hf_mb->Write();
   write_histo( output );
   output->Close();
}

