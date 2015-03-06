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

double cut_ffls3d = 4.0;
double cut_cosfalpha0 = 0.975;
double cut_fchi2 = 3.0;

double width_signal = 0.04;
double sideband_close = 0.06;
double sideband_far = 0.15;

void Cut_distribution_Data_likesign()
{
	TH1::SetDefaultSumw2();
	TFile * Data_input = new TFile("/home/sun229/store/Analysisfiles/Dmesonana_Rereco_MBtrig_d0pt3p0_nodalphacuts_pt1p5_tight_3lumi_0131_temp_alpha0p8_pt4p5.root");
	TTree * recodmesontree = (TTree *) Data_input->Get("recodmesontree");
    
	TH1D * mass_unlikesign_nocuts = new TH1D("mass_unlikesign_nocuts","mass_unlikesign_nocuts", 35, 1.7, 2.05);
	TH1D * mass_likesign_nocuts = new TH1D("mass_likesign_nocuts","mass_likesign_nocuts", 35, 1.7, 2.05);
	TH1D * mass_diff_nocuts = new TH1D("mass_diff_nocuts","mass_diff_nocuts", 35, 1.7, 2.05);

    TH1D * mass_unlikesign_ffls3d = new TH1D("mass_unlikesign_ffls3d","mass_unlikesign_ffls3d", 35, 1.7, 2.05);
	TH1D * mass_likesign_ffls3d = new TH1D("mass_likesign_ffls3d","mass_likesign_ffls3d", 35, 1.7, 2.05);
	TH1D * mass_diff_ffls3d = new TH1D("mass_diff_ffls3d","mass_diff_ffls3d", 35, 1.7, 2.05);

	TH1D * ffls3d_signal_data = new TH1D("ffls3d_signal_data","ffls3d_signal_data",160,0.,80.);
	TH1D * ffls3d_unlikesign = new TH1D("ffls3d_unlikesign","ffls3d_unlikesign",160,0,80.);
	TH1D * ffls3d_likesign = new TH1D("ffls3d_likesign","ffls3d_likesign",160,0,80.);

    TH1D * mass_unlikesign_cosalpha = new TH1D("mass_unlikesign_cosalpha","mass_unlikesign_cosalpha", 35, 1.7, 2.05);
	TH1D * mass_likesign_cosalpha = new TH1D("mass_likesign_cosalpha","mass_likesign_cosalpha", 35, 1.7, 2.05);
	TH1D * mass_diff_cosalpha = new TH1D("mass_diff_cosalpha","mass_diff_cosalpha", 35, 1.7, 2.05);

	TH1D * cosalpha_signal_data = new TH1D("cosalpha_signal_data","cosalpha_signal_data",1000,-1.,1.);
	TH1D * cosalpha_unlikesign = new TH1D("cosalpha_unlikesign","cosalpha_unlikesign",1000,-1.,1.);
	TH1D * cosalpha_likesign = new TH1D("cosalpha_likesign","cosalpha_likesign",1000,-1.,1.);

    TH1D * mass_unlikesign_fchi2 = new TH1D("mass_unlikesign_fchi2","mass_unlikesign_fchi2", 35, 1.7, 2.05);
	TH1D * mass_likesign_fchi2 = new TH1D("mass_likesign_fchi2","mass_likesign_fchi2", 35, 1.7, 2.05);
	TH1D * mass_diff_fchi2 = new TH1D("mass_diff_fchi2","mass_diff_fchi2", 35, 1.7, 2.05);

	TH1D * fchi2_signal_data = new TH1D("fchi2_signal_data","fchi2_signal_data",80,0.,20.);
	TH1D * fchi2_unlikesign = new TH1D("fchi2_unlikesign","fchi2_unlikesign",80,0,20.);
	TH1D * fchi2_likesign = new TH1D("fchi2_likesign","fchi2_likesign",80,0,20.);

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
		   if( dcandpt->at(icand) < 7.0 )   continue;
//		   if( !passingcuts->at(icand) )   continue;

		   if( TMath::Abs( dcandy->at(icand) ) > 2.0 )  continue;
		   if( TMath::Abs( dcanddau1eta->at(icand) ) > 2.4 || TMath::Abs( dcanddau2eta->at(icand) ) > 2.4 )   continue;

		   if( dcanddau1q->at(icand) * dcanddau2q->at(icand) < 0  ) mass_unlikesign_nocuts->Fill(dcandmass->at(icand));
		   if( dcanddau1q->at(icand) * dcanddau2q->at(icand) > 0  ) mass_likesign_nocuts->Fill(dcandmass->at(icand));

		   //decaylenght
		   if( dcanddau1q->at(icand) * dcanddau2q->at(icand) < 0 /*&& dcandcosalpha->at(icand) > cut_cosfalpha0 && dcandfchi2->at(icand) < cut_fchi2 */)  
		   {
			   mass_unlikesign_ffls3d->Fill(dcandmass->at(icand));
			   if( TMath::Abs(dcandmass->at(icand) - 1.864) < width_signal )
				   ffls3d_unlikesign->Fill(dcandffls3d->at(icand)); 
		   }

		   if( dcanddau1q->at(icand) * dcanddau2q->at(icand) > 0 /*&& dcandcosalpha->at(icand) > cut_cosfalpha0 && dcandfchi2->at(icand) < cut_fchi2 */)  
		   {
			   mass_likesign_ffls3d->Fill(dcandmass->at(icand));
			   if( TMath::Abs(dcandmass->at(icand) - 1.864) < width_signal )
				   ffls3d_likesign->Fill(dcandffls3d->at(icand));
		   }

           //cosalpha
		   if( dcanddau1q->at(icand) * dcanddau2q->at(icand) < 0 /*&& dcandffls3d->at(icand) > cut_ffls3d && dcandfchi2->at(icand) < cut_fchi2 */) 
		   {
			   mass_unlikesign_cosalpha->Fill(dcandmass->at(icand));
			   if( TMath::Abs(dcandmass->at(icand) - 1.864) < width_signal )
				   cosalpha_unlikesign->Fill(dcandcosalpha->at(icand));
		   }
		   if( dcanddau1q->at(icand) * dcanddau2q->at(icand) > 0 /*&& dcandffls3d->at(icand) > cut_ffls3d && dcandfchi2->at(icand) < cut_fchi2 */)
		   {
			   mass_likesign_cosalpha->Fill(dcandmass->at(icand));
			   if( TMath::Abs(dcandmass->at(icand) - 1.864) < width_signal )
				   cosalpha_likesign->Fill(dcandcosalpha->at(icand));
		   }
 
           //chi2
		   if( dcanddau1q->at(icand) * dcanddau2q->at(icand) < 0 /*&& dcandffls3d->at(icand) > cut_ffls3d && dcandcosalpha->at(icand) > cut_cosfalpha0 */)
		   {
			   mass_unlikesign_fchi2->Fill(dcandmass->at(icand));
			   if( TMath::Abs(dcandmass->at(icand) - 1.864) < width_signal )
				   fchi2_unlikesign->Fill(dcandfchi2->at(icand));
		   }
		   if( dcanddau1q->at(icand) * dcanddau2q->at(icand) > 0 /*&& dcandffls3d->at(icand) > cut_ffls3d && dcandcosalpha->at(icand) > cut_cosfalpha0 */)
		   {
			   mass_likesign_fchi2->Fill(dcandmass->at(icand));
			   if( TMath::Abs(dcandmass->at(icand) - 1.864) < width_signal )
				   fchi2_likesign->Fill(dcandfchi2->at(icand));
		   }

	   }
   }

   double n_sideband_unlikesign, n_sideband_likesign, scale;
   
   n_sideband_unlikesign =  mass_unlikesign_nocuts->Integral( mass_unlikesign_nocuts->FindBin(1.864-sideband_far), mass_unlikesign_nocuts->FindBin(1.864-sideband_close) ) + mass_unlikesign_nocuts->Integral( mass_unlikesign_nocuts->FindBin(1.864+sideband_close), mass_unlikesign_nocuts->FindBin(1.864+sideband_far) );
   n_sideband_likesign   =  mass_likesign_nocuts->Integral( mass_likesign_nocuts->FindBin(1.864-sideband_far), mass_likesign_nocuts->FindBin(1.864-sideband_close) )+ mass_likesign_nocuts->Integral( mass_likesign_nocuts->FindBin(1.864+sideband_close), mass_likesign_nocuts->FindBin(1.864+sideband_far) );
   scale = n_sideband_unlikesign / n_sideband_likesign;
   mass_likesign_nocuts->Scale(scale);

   mass_diff_nocuts->Add( mass_unlikesign_nocuts, mass_likesign_nocuts, 1.0, -1.0 );

   //decay length
   n_sideband_unlikesign =  mass_unlikesign_ffls3d->Integral( mass_unlikesign_ffls3d->FindBin(1.864-sideband_far), mass_unlikesign_ffls3d->FindBin(1.864-sideband_close) ) + mass_unlikesign_ffls3d->Integral( mass_unlikesign_ffls3d->FindBin(1.864+sideband_close), mass_unlikesign_ffls3d->FindBin(1.864+sideband_far) );
   n_sideband_likesign   =  mass_likesign_ffls3d->Integral( mass_likesign_ffls3d->FindBin(1.864-sideband_far), mass_likesign_ffls3d->FindBin(1.864-sideband_close) ) + mass_likesign_ffls3d->Integral( mass_likesign_ffls3d->FindBin(1.864+sideband_close), mass_likesign_ffls3d->FindBin(1.864+sideband_far) );
   scale = n_sideband_unlikesign / n_sideband_likesign;
   mass_likesign_ffls3d->Scale(scale);
   ffls3d_likesign->Scale(scale);

   mass_diff_ffls3d->Add( mass_unlikesign_ffls3d, mass_likesign_ffls3d, 1.0, -1.0 );
   ffls3d_signal_data->Add( ffls3d_unlikesign, ffls3d_likesign, 1.0, -1.0);
 
   //cos alpha
   n_sideband_unlikesign =  mass_unlikesign_cosalpha->Integral( mass_unlikesign_cosalpha->FindBin(1.864-sideband_far), mass_unlikesign_cosalpha->FindBin(1.864-sideband_close) ) + mass_unlikesign_cosalpha->Integral( mass_unlikesign_cosalpha->FindBin(1.864+sideband_close), mass_unlikesign_cosalpha->FindBin(1.864+sideband_far) );
   n_sideband_likesign   =  mass_likesign_cosalpha->Integral( mass_likesign_cosalpha->FindBin(1.864-sideband_far), mass_likesign_cosalpha->FindBin(1.864-sideband_close) ) + mass_likesign_cosalpha->Integral( mass_likesign_cosalpha->FindBin(1.864+sideband_close), mass_likesign_cosalpha->FindBin(1.864+sideband_far) );
   scale = n_sideband_unlikesign / n_sideband_likesign;
   mass_likesign_cosalpha->Scale(scale);
   cosalpha_likesign->Scale(scale);
   
   mass_diff_cosalpha->Add( mass_unlikesign_cosalpha, mass_likesign_cosalpha, 1.0, -1.0 );
   cosalpha_signal_data->Add( cosalpha_unlikesign, cosalpha_likesign, 1.0, -1.0);

   //vertex chi2
   n_sideband_unlikesign =  mass_unlikesign_fchi2->Integral( mass_unlikesign_fchi2->FindBin(1.864-sideband_far), mass_unlikesign_fchi2->FindBin(1.864-sideband_close) ) + mass_unlikesign_fchi2->Integral( mass_unlikesign_fchi2->FindBin(1.864+sideband_close), mass_unlikesign_fchi2->FindBin(1.864+sideband_far) );
   n_sideband_likesign   =  mass_likesign_fchi2->Integral( mass_likesign_fchi2->FindBin(1.864-sideband_far), mass_likesign_fchi2->FindBin(1.864-sideband_close) ) + mass_likesign_fchi2->Integral( mass_likesign_fchi2->FindBin(1.864+sideband_close), mass_likesign_fchi2->FindBin(1.864+sideband_far) );
   scale = n_sideband_unlikesign / n_sideband_likesign;
   mass_likesign_fchi2->Scale(scale);
   fchi2_likesign->Scale(scale);
  
   mass_diff_fchi2->Add( mass_unlikesign_fchi2, mass_likesign_fchi2, 1.0, -1.0 );
   fchi2_signal_data->Add( fchi2_unlikesign, fchi2_likesign, 1.0, -1.0);

   TFile * output = new TFile("Cut_distribution_Data.root","RECREATE");
   mass_unlikesign_nocuts->Write();
   mass_likesign_nocuts->Write();
   mass_diff_nocuts->Write();

   mass_unlikesign_ffls3d->Write();
   mass_likesign_ffls3d->Write();
   mass_diff_ffls3d->Write();

   ffls3d_unlikesign->Write();
   ffls3d_likesign->Write();
   ffls3d_signal_data->Write();

   mass_unlikesign_cosalpha->Write();
   mass_likesign_cosalpha->Write();
   mass_diff_cosalpha->Write();

   cosalpha_unlikesign->Write();
   cosalpha_likesign->Write();
   cosalpha_signal_data->Write();

   mass_unlikesign_fchi2->Write();
   mass_likesign_fchi2->Write();
   mass_diff_fchi2->Write();

   fchi2_unlikesign->Write();
   fchi2_likesign->Write();
   fchi2_signal_data->Write();

   output->Close();


}
