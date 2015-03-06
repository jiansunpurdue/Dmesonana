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
#define MAXGENDMESON 100

double cut_ffls3d = 4.0;
double cut_cosfalpha0 = 0.975;
double cut_fchi2 = 3.0;

void Cut_distribution_MC_matched()
{
	TH1::SetDefaultSumw2();
	TH1D * ffls3d_signal_mcmatched = new TH1D("ffls3d_signal_mcmatched","ffls3d_signal_mcmatched",160,0.,80.); //40
	TH1D * cosalpha_signal_mcmatched = new TH1D("cosalpha_signal_mcmatched","cosalpha_signal_mcmatched",1000,-1.,1.);  //200
	TH1D * fprob_signal_mcmatched = new TH1D("fprob_signal_mcmatched","fprob_signal_mcmatched",100,0.,1.);  //20
	TH1D * fchi2_signal_mcmatched = new TH1D("fchi2_signal_mcmatched","fchi2_signal_mcmatched",80,0.,20.);  //40

	TFile * input_fonllweight = new TFile("./../D0_PbPb_rawtoFONLL_3to100.root");
	TH1D * fonllweight = ( TH1D * ) input_fonllweight->Get("ratio_rawtofonll");

	TFile * input = new TFile("./../rootfiles/Dmesonana_hiforest_PbPb_Pyquen_D0embedded_D0pt3_pthat015305080_1217_1223_all_vz_v2.root");
	TTree * recodmesontree = (TTree *) input->Get("recodmesontree");
    TTree * gendmesontree = (TTree *) input->Get("gendmesontree");
    recodmesontree->AddFriend(gendmesontree);

    float pthat;
    int ngend;
    float dpt[MAXGENDMESON];
    float deta[MAXGENDMESON];
    float dy[MAXGENDMESON];
    gendmesontree->SetBranchAddress("pthat", &pthat);
    gendmesontree->SetBranchAddress("ngend", &ngend);
    gendmesontree->SetBranchAddress("dpt", dpt);
    gendmesontree->SetBranchAddress("deta", deta);
    gendmesontree->SetBranchAddress("dy", dy);

    int MinBias;
    int MinBias_Prescl;

    int ndcand;
    int hiBin;
    double pthatweight;
    double trigweight;
    vector<int> *dtype = 0, *passingcuts = 0;
    vector<float> *dcandmass = 0, *dcandpt = 0, *dcandy = 0, *dcandphi = 0, *dcandffls3d = 0, *dcandcosalpha = 0, *dcandfprob = 0, *dcandfchi2 = 0;
    vector<float> *dcanddau1eta = 0, *dcanddau2eta = 0;
	vector<int> *dcanddau1q = 0, *dcanddau2q = 0;
	vector<int>   *matchedtogen = 0, *nongendoublecounted = 0;

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
//	recodmesontree->SetBranchAddress("dcanddau1q", &dcanddau1q);
//	recodmesontree->SetBranchAddress("dcanddau2q", &dcanddau2q);
    recodmesontree->SetBranchAddress("matchedtogen", &matchedtogen);
    recodmesontree->SetBranchAddress("nongendoublecounted", &nongendoublecounted);
    
   for ( int entry = 0; entry < recodmesontree->GetEntries(); entry++ )
   {
	   recodmesontree->GetEntry(entry);
	   if( entry % 1000000 == 0 )  cout << entry+1 << "st event" << endl;
	   if( !MinBias ) continue;
	   if( ndcand != dtype->size() || ndcand != passingcuts->size() || ndcand != dcandmass->size() || ndcand != dcandpt->size() )    
		   cout << "Error!!!!!!!!" << endl;
	
	   double weight = pthatweight;
	   for( int icand = 0; icand < ndcand; icand++ )
	   {
//           if( pthat < 15 && dcandpt->at(icand) > 9.0 )   continue;
//           if( pthat > 15.0 && pthat < 30.0 && dcandpt->at(icand) > 16.0 )   continue;
		   
		   if( dcandpt->at(icand) < 7.0 )  continue;
//		   if( !passingcuts->at(icand) )   continue;
           weight = fonllweight->GetBinContent( fonllweight->FindBin( dcandpt->at(icand) ) );

		   if( TMath::Abs( dcandy->at(icand) ) > 2.0 )  continue;
		   if( TMath::Abs( dcanddau1eta->at(icand) ) > 2.4 || TMath::Abs( dcanddau2eta->at(icand) ) > 2.4 )   continue;

           if( !( matchedtogen->at(icand) == 1 && nongendoublecounted->at(icand) == 1 ))   continue;

		   if(TMath::Abs( dcandmass->at(icand) - 1.864 ) > 0.04) continue;  //just the D0 mass range
		   
		   //decaylenght
//		   if( dcandcosalpha->at(icand) > cut_cosfalpha0 && dcandfchi2->at(icand) < cut_fchi2 )  
               ffls3d_signal_mcmatched->Fill(dcandffls3d->at(icand), weight); 

           //cosalpha
//		   if( dcandffls3d->at(icand) > cut_ffls3d && dcandfchi2->at(icand) < cut_fchi2 ) 
			   cosalpha_signal_mcmatched->Fill(dcandcosalpha->at(icand) , weight);
 
           //chi2
//		   if( dcandffls3d->at(icand) > cut_ffls3d && dcandcosalpha->at(icand) > cut_cosfalpha0 )
			   fchi2_signal_mcmatched->Fill(dcandfchi2->at(icand), weight);

	   }
   }

   TFile * output = new TFile("Cut_distribution_MC_FONLLweight.root","RECREATE");
   
   ffls3d_signal_mcmatched->Write();
   cosalpha_signal_mcmatched->Write();
   fchi2_signal_mcmatched->Write();
   
   output->Close();


}
