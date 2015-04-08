#include <string>
#include <vector>
#include <map>
#include <fstream>
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
#include "sideband.h"

//loosecut: 2.0, 0.2, 0.05
//tight: 3.5, 0.05, 0.05

#define NPT  12
double ptbins[NPT+1] = {0,3.5,4.5,5.5,7,9,11,13,16,20,28,40,100};

double cut_ffls3d = 3.5;  //2.0   4.5 GeV: 3.5    0.06  0.05
double cut_falpha = 0.05;  //0.2
double cut_fprob = 0.05;  //0.05

double Ptcut_low = 3.5;
double Ptcut_high = 7.0;

bool Allcuts = true;
bool nocuts = false;

void Cut_distribution_Data_sideband( int startFile, int endFile, char *filelist )
{
	TH1::SetDefaultSumw2();

    TH1D * h_pt = new TH1D("h_pt","h_pt",NPT, ptbins);
	TH1D * mass = new TH1D("mass","mass",35,1.70,2.05);

    TH1D * mass_ffls3d = new TH1D("mass_ffls3d","mass_ffls3d", 35, 1.7, 2.05);
	TH1D * ffls3d_signal_data = new TH1D("ffls3d_signal_data","ffls3d_signal_data",1000,0.,100.);
	TH1D * ffls3d_signalregion = new TH1D("ffls3d_signalregion","ffls3d_signalregion",1000,0.,100.);
	TH1D * ffls3d_band = new TH1D("ffls3d_band","ffls3d_band",1000,0,100.);
	TH1D * ffls3d_leftband = new TH1D("ffls3d_leftband","ffls3d_leftband",1000,0,100.);
	TH1D * ffls3d_rightband = new TH1D("ffls3d_rightband","ffls3d_rightband",1000,0,100.);

    TH1D * mass_alpha = new TH1D("mass_alpha","mass_alpha", 35, 1.7, 2.05);
	TH1D * alpha_signal_data = new TH1D("alpha_signal_data","alpha_signal_data",1000,0.,3.2);
	TH1D * alpha_signalregion = new TH1D("alpha_signalregion","alpha_signalregion",1000,0.,3.2);
	TH1D * alpha_band = new TH1D("alpha_band","alpha_band",1000,0.,3.2);
	TH1D * alpha_leftband = new TH1D("alpha_leftband","alpha_leftband",1000,0.,3.2);
	TH1D * alpha_rightband = new TH1D("alpha_rightband","alpha_rightband",1000,0.,3.2);

    TH1D * mass_fprob = new TH1D("mass_fprob","mass_fprob", 35, 1.70, 2.05);
	TH1D * fprob_signal_data = new TH1D("fprob_signal_data","fprob_signal_data",1000,0.,1.);
    TH1D * fprob_signalregion = new TH1D("fprob_signalregion","fprob_signalregion",1000,0.,1.);
	TH1D * fprob_band = new TH1D("fprob_band","fprob_band",1000,0,1.);
	TH1D * fprob_leftband = new TH1D("fprob_leftband","fprob_leftband",1000,0,1.);
	TH1D * fprob_rightband = new TH1D("fprob_rightband","fprob_rightband",1000,0,1.);

    TH1D * mass_fchi2 = new TH1D("mass_fchi2","mass_fchi2", 35, 1.70, 2.05);
	TH1D * fchi2_signal_data = new TH1D("fchi2_signal_data","fchi2_signal_data",1000,0.,100.);
    TH1D * fchi2_signalregion = new TH1D("fchi2_signalregion","fchi2_signalregion",1000,0.,100.);
	TH1D * fchi2_band = new TH1D("fchi2_band","fchi2_band",1000,0,100.);
	TH1D * fchi2_leftband = new TH1D("fchi2_leftband","fchi2_leftband",1000,0,100.);
	TH1D * fchi2_rightband = new TH1D("fchi2_rightband","fchi2_rightband",1000,0,100.);

    TH1D * mass_y = new TH1D("mass_y","mass_y", 35, 1.70, 2.05);
	TH1D * y_signal_data = new TH1D("y_signal_data","y_signal_data",16,-2.,2.);
    TH1D * y_signalregion = new TH1D("y_signalregion","y_signalregion",16,-2.,2.);
	TH1D * y_band = new TH1D("y_band","y_band",16,-2.,2.);
	TH1D * y_leftband = new TH1D("y_leftband","y_leftband",16,-2.,2.);
	TH1D * y_rightband = new TH1D("y_rightband","y_rightband",16,-2.,2.);

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
   string filename;

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

//        TFile *f = TFile::Open(filename.c_str());
    TFile * Data_input = TFile::Open(filename.c_str());;	
	TTree * recodmesontree = (TTree *) Data_input->Get("recodmesontree");

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
	recodmesontree->SetBranchAddress("dcanddau1q", &dcanddau1q);
	recodmesontree->SetBranchAddress("dcanddau2q", &dcanddau2q);
    
   for ( int entry = 0; entry < recodmesontree->GetEntries(); entry++ )
   {
	   recodmesontree->GetEntry(entry);
	   if( entry % 1000000 == 0 )  cout << entry+1 << "st event" << endl;
	   if( !MinBias ) continue;
	   if( ndcand != dtype->size() || ndcand != passingcuts->size() || ndcand != dcandmass->size() || ndcand != dcandpt->size() )    
		   cout << "Error!!!!!!!!" << endl;
	   for( int icand = 0; icand < ndcand; icand++ )
	   {
           if( dcandpt->at(icand) < Ptcut_low || dcandpt->at(icand) > Ptcut_high)   continue;
		   
		   if( TMath::Abs( dcandy->at(icand) ) > 2.0 )  continue;
		   if( TMath::Abs( dcanddau1eta->at(icand) ) > 2.4 || TMath::Abs( dcanddau2eta->at(icand) ) > 2.4 )   continue;
		   if( dcanddau1q->at(icand) * dcanddau2q->at(icand) > 0 )   continue;
		   double dcandalpha = TMath::ACos(dcandcosalpha->at(icand));

//all loose or tight cuts applied?
		   if( Allcuts && ( dcandffls3d->at(icand) < cut_ffls3d || dcandalpha > cut_falpha || dcandfprob->at(icand) < cut_fprob ) )   continue;

		   mass->Fill(dcandmass->at(icand));

           //rapidity
		   if( nocuts || ( dcandffls3d->at(icand) > cut_ffls3d && dcandalpha < cut_falpha && dcandfprob->at(icand) > cut_fprob ) )
		   {
			  mass_y->Fill(dcandmass->at(icand));
		      if( dcandmass->at(icand) - mass_d0 > -1.0 * sideband_far && dcandmass->at(icand) - mass_d0 < -1.0 * sideband_close ) 
		   	   y_leftband->Fill(dcandy->at(icand));
		      if( dcandmass->at(icand) - mass_d0 > sideband_close && dcandmass->at(icand) - mass_d0 < sideband_far )
		   	   y_rightband->Fill(dcandy->at(icand));
		      if( TMath::Abs( dcandmass->at(icand) - mass_d0 ) < width_signal )
		   	   y_signalregion->Fill(dcandy->at(icand));
		   }

	   
		   //decaylength
		    if( nocuts || ( dcandalpha < cut_falpha && dcandfprob->at(icand) > cut_fprob ))
			{
			   mass_ffls3d->Fill(dcandmass->at(icand));
    		   if( dcandmass->at(icand) - mass_d0 > -1.0 * sideband_far && dcandmass->at(icand) - mass_d0 < -1.0 * sideband_close )  
    			   ffls3d_leftband->Fill(dcandffls3d->at(icand)); 
    		   if( dcandmass->at(icand) - mass_d0 > sideband_close && dcandmass->at(icand) - mass_d0 < sideband_far )  
    			   ffls3d_rightband->Fill(dcandffls3d->at(icand));
    		   if( TMath::Abs( dcandmass->at(icand) - mass_d0 ) < width_signal )
    			   ffls3d_signalregion->Fill(dcandffls3d->at(icand));
			}

           //alpha
		   if( nocuts || ( dcandffls3d->at(icand) > cut_ffls3d && dcandfprob->at(icand) > cut_fprob ) )
		   {
			  mass_alpha->Fill(dcandmass->at(icand));
		      if( dcandmass->at(icand) - mass_d0 > -1.0 * sideband_far && dcandmass->at(icand) - mass_d0 < -1.0 * sideband_close ) 
		   	   alpha_leftband->Fill(dcandalpha);
		      if( dcandmass->at(icand) - mass_d0 > sideband_close && dcandmass->at(icand) - mass_d0 < sideband_far )
		   	   alpha_rightband->Fill(dcandalpha);
		      if( TMath::Abs( dcandmass->at(icand) - mass_d0 ) < width_signal )
		   	   alpha_signalregion->Fill(dcandalpha);
		   }

           //prob
		   if( nocuts || ( dcandffls3d->at(icand) > cut_ffls3d && dcandalpha < cut_falpha ) )
		   {
			  mass_fprob->Fill(dcandmass->at(icand));
		      if( dcandmass->at(icand) - mass_d0 > -1.0 * sideband_far && dcandmass->at(icand) - mass_d0 < -1.0 * sideband_close )
		          fprob_leftband->Fill(dcandfprob->at(icand));
		      if( dcandmass->at(icand) - mass_d0 > sideband_close && dcandmass->at(icand) - mass_d0 < sideband_far )
		          fprob_rightband->Fill(dcandfprob->at(icand));
		      if( TMath::Abs( dcandmass->at(icand) - mass_d0 ) < width_signal )
			   fprob_signalregion->Fill(dcandfprob->at(icand));
		   }
		   
           //fchi2
		   if( nocuts || ( dcandffls3d->at(icand) > cut_ffls3d && dcandalpha < cut_falpha ) )
		   {
			  mass_fchi2->Fill(dcandmass->at(icand));
		      if( dcandmass->at(icand) - mass_d0 > -1.0 * sideband_far && dcandmass->at(icand) - mass_d0 < -1.0 * sideband_close )
		          fchi2_leftband->Fill(dcandfchi2->at(icand));
		      if( dcandmass->at(icand) - mass_d0 > sideband_close && dcandmass->at(icand) - mass_d0 < sideband_far )
		          fchi2_rightband->Fill(dcandfchi2->at(icand));
		      if( TMath::Abs( dcandmass->at(icand) - mass_d0 ) < width_signal )
			   fchi2_signalregion->Fill(dcandfchi2->at(icand));
		   }
	   }
   }
Data_input->Close();
}

   char * outfilename = new char[1000];
   sprintf(outfilename, "Cut_distribution_Data_sideband_pt%1.0fto%1.0f_%dTo%d_noloosecuts%d.root", Ptcut_low, Ptcut_high, startFile, endFile, nocuts);
   TFile * output = new TFile(outfilename,"RECREATE");

   mass->Write();

   mass_y->Write();
   y_leftband->Write();
   y_rightband->Write();
   y_band->Write();
   y_signalregion->Write();
   y_signal_data->Write();

   mass_ffls3d->Write();
   ffls3d_leftband->Write();
   ffls3d_rightband->Write();
   ffls3d_band->Write();
   ffls3d_signalregion->Write();
   ffls3d_signal_data->Write();

   mass_alpha->Write();
   alpha_leftband->Write();
   alpha_rightband->Write();
   alpha_band->Write();
   alpha_signalregion->Write();
   alpha_signal_data->Write();

   mass_fprob->Write();
   fprob_leftband->Write();
   fprob_rightband->Write();
   fprob_band->Write();
   fprob_signalregion->Write();
   fprob_signal_data->Write();

   mass_fchi2->Write();
   fchi2_leftband->Write();
   fchi2_rightband->Write();
   fchi2_band->Write();
   fchi2_signalregion->Write();
   fchi2_signal_data->Write();

   output->Close();


}
