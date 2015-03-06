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
double cut_fprob = 0.08;
double cut_fchi2 = 3.0;

double sideband_close = 0.1;
double sideband_far = 0.15;
double width_signal = 0.05;
double mass_d0 = 1.864;

void Cut_distribution_Data_sideband()
{
	TH1::SetDefaultSumw2();
	TFile * Data_input = new TFile("Dmesonana_Rereco_MBtrig_d0pt3p0_nodalphacuts_pt1p5_tight_3lumi_0131_temp_all_pt7.root");
	TTree * recodmesontree = (TTree *) Data_input->Get("recodmesontree");

	TH1D * mass = new TH1D("mass","mass",35,1.70,2.05);

	TH1D * ffls3d_signal_data = new TH1D("ffls3d_signal_data","ffls3d_signal_data",20,0.,20.);
	TH1D * ffls3d_signalregion = new TH1D("ffls3d_signalregion","ffls3d_signalregion",20,0.,20.);
	TH1D * ffls3d_band = new TH1D("ffls3d_band","ffls3d_band",20,0,20.);
	TH1D * ffls3d_leftband = new TH1D("ffls3d_leftband","ffls3d_leftband",20,0,20.);
	TH1D * ffls3d_rightband = new TH1D("ffls3d_rightband","ffls3d_rightband",20,0,20.);

	TH1D * cosalpha_signal_data = new TH1D("cosalpha_signal_data","cosalpha_signal_data",1000,-1.,1.);
	TH1D * cosalpha_signalregion = new TH1D("cosalpha_signalregion","cosalpha_signalregion",1000,-1.,1.);
	TH1D * cosalpha_band = new TH1D("cosalpha_band","cosalpha_band",1000,-1.,1.);
	TH1D * cosalpha_leftband = new TH1D("cosalpha_leftband","cosalpha_leftband",1000,-1.,1.);
	TH1D * cosalpha_rightband = new TH1D("cosalpha_rightband","cosalpha_rightband",1000,-1.,1.);

	TH1D * fprob_signal_data = new TH1D("fprob_signal_data","fprob_signal_data",50,0.,1.);
    TH1D * fprob_signalregion = new TH1D("fprob_signalregion","fprob_signalregion",50,0.,1.);
	TH1D * fprob_band = new TH1D("fprob_band","fprob_band",50,0,1.);
	TH1D * fprob_leftband = new TH1D("fprob_leftband","fprob_leftband",50,0,1.);
	TH1D * fprob_rightband = new TH1D("fprob_rightband","fprob_rightband",50,0,1.);

	TH1D * fchi2_signal_data = new TH1D("fchi2_signal_data","fchi2_signal_data",50,0.,20.);
	TH1D * fchi2_signalregion = new TH1D("fchi2_signalregion","fchi2_signalregion",50,0.,20.);
	TH1D * fchi2_band = new TH1D("fchi2_band","fchi2_band",50,0,20.);
	TH1D * fchi2_leftband = new TH1D("fchi2_leftband","fchi2_leftband",50,0,20.);
	TH1D * fchi2_rightband = new TH1D("fchi2_rightband","fchi2_rightband",50,0,20.);

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
		   if( TMath::Abs( dcandy->at(icand) ) > 2.0 )  continue;
		   if( TMath::Abs( dcanddau1eta->at(icand) ) > 2.4 || TMath::Abs( dcanddau2eta->at(icand) ) > 2.4 )   continue;
		   if( dcanddau1q->at(icand) * dcanddau2q->at(icand) > 0 )   continue;

		   mass->Fill(dcandmass->at(icand));
	   
		   //decaylenght
		   if( dcandmass->at(icand) - mass_d0 > -1.0 * sideband_far && dcandmass->at(icand) - mass_d0 < -1.0 * sideband_close && dcandcosalpha->at(icand) > cut_cosfalpha0 && dcandfchi2->at(icand) < cut_fchi2 && dcandfprob->at(icand) > cut_fprob )  
			   ffls3d_leftband->Fill(dcandffls3d->at(icand)); 
		   if( dcandmass->at(icand) - mass_d0 > sideband_close && dcandmass->at(icand) - mass_d0 < sideband_far && dcandcosalpha->at(icand) > cut_cosfalpha0 && dcandfchi2->at(icand) < cut_fchi2 && dcandfprob->at(icand) > cut_fprob )  
			   ffls3d_rightband->Fill(dcandffls3d->at(icand));
		   if( TMath::Abs( dcandmass->at(icand) - mass_d0 ) < width_signal && dcandcosalpha->at(icand) > cut_cosfalpha0 && dcandfchi2->at(icand) < cut_fchi2 && dcandfprob->at(icand) > cut_fprob )
			   ffls3d_signalregion->Fill(dcandffls3d->at(icand));

           //cosalpha
		   if( dcandmass->at(icand) - mass_d0 > -1.0 * sideband_far && dcandmass->at(icand) - mass_d0 < -1.0 * sideband_close && dcandffls3d->at(icand) > cut_ffls3d && dcandfchi2->at(icand) < cut_fchi2 && dcandfprob->at(icand) > cut_fprob ) 
			   cosalpha_leftband->Fill(dcandcosalpha->at(icand));
		   if( dcandmass->at(icand) - mass_d0 > sideband_close && dcandmass->at(icand) - mass_d0 < sideband_far && dcandffls3d->at(icand) > cut_ffls3d && dcandfchi2->at(icand) < cut_fchi2 && dcandfprob->at(icand) > cut_fprob )
			   cosalpha_rightband->Fill(dcandcosalpha->at(icand));
		   if( TMath::Abs( dcandmass->at(icand) - mass_d0 ) < width_signal && dcandffls3d->at(icand) > cut_ffls3d && dcandfchi2->at(icand) < cut_fchi2 && dcandfprob->at(icand) > cut_fprob)
			   cosalpha_signalregion->Fill(dcandcosalpha->at(icand));
 
           //chi2
		   if( dcandmass->at(icand) - mass_d0 > -1.0 * sideband_far && dcandmass->at(icand) - mass_d0 < -1.0 * sideband_close && dcandffls3d->at(icand) > cut_ffls3d && dcandcosalpha->at(icand) > cut_cosfalpha0 )
			   fchi2_leftband->Fill(dcandfchi2->at(icand));
		   if( dcandmass->at(icand) - mass_d0 > sideband_close && dcandmass->at(icand) - mass_d0 < sideband_far && dcandffls3d->at(icand) > cut_ffls3d && dcandcosalpha->at(icand) > cut_cosfalpha0 )
			   fchi2_rightband->Fill(dcandfchi2->at(icand));
		   if( TMath::Abs( dcandmass->at(icand) - mass_d0 ) < width_signal && dcandffls3d->at(icand) > cut_ffls3d && dcandcosalpha->at(icand) > cut_cosfalpha0 )
			   fchi2_signalregion->Fill(dcandfchi2->at(icand));

           //prob
		   if( dcandmass->at(icand) - mass_d0 > -1.0 * sideband_far && dcandmass->at(icand) - mass_d0 < -1.0 * sideband_close && dcandffls3d->at(icand) > cut_ffls3d && dcandcosalpha->at(icand) > cut_cosfalpha0 )
			   fprob_leftband->Fill(dcandfprob->at(icand));
		   if( dcandmass->at(icand) - mass_d0 > sideband_close && dcandmass->at(icand) - mass_d0 < sideband_far && dcandffls3d->at(icand) > cut_ffls3d && dcandcosalpha->at(icand) > cut_cosfalpha0 )
			   fprob_rightband->Fill(dcandfprob->at(icand));
		   if( TMath::Abs( dcandmass->at(icand) - mass_d0 ) < width_signal && dcandffls3d->at(icand) > cut_ffls3d && dcandcosalpha->at(icand) > cut_cosfalpha0 )
			   fprob_signalregion->Fill(dcandfprob->at(icand));
		   
	   }
   }

   ffls3d_band->Add(ffls3d_leftband, ffls3d_rightband, 1.0, 1.0);
   cosalpha_band->Add(cosalpha_leftband, cosalpha_rightband, 1.0, 1.0);
   fchi2_band->Add(fchi2_leftband, fchi2_rightband, 1.0, 1.0);
   fprob_band->Add(fprob_leftband, fprob_rightband, 1.0, 1.0);

   ffls3d_band->Scale( 0.5 * width_signal/(sideband_far - sideband_close) );
   cosalpha_band->Scale( 0.5 * width_signal/(sideband_far - sideband_close) );
   fchi2_band->Scale( 0.5 * width_signal/(sideband_far - sideband_close) );
   fprob_band->Scale( 0.5 * width_signal/(sideband_far - sideband_close) );

   ffls3d_signal_data->Add( ffls3d_signalregion, ffls3d_band, 1.0, -1.0);
   cosalpha_signal_data->Add( cosalpha_signalregion, cosalpha_band, 1.0, -1.0);
   fchi2_signal_data->Add( fchi2_signalregion, fchi2_band, 1.0, -1.0);
   fprob_signal_data->Add( fprob_signalregion, fprob_band, 1.0, -1.0);


   TFile * output = new TFile("Cut_distribution_sideband_Data.root","RECREATE");

   mass->Write();

   ffls3d_leftband->Write();
   ffls3d_rightband->Write();
   ffls3d_band->Write();
   ffls3d_signalregion->Write();
   ffls3d_signal_data->Write();

   cosalpha_leftband->Write();
   cosalpha_rightband->Write();
   cosalpha_band->Write();
   cosalpha_signalregion->Write();
   cosalpha_signal_data->Write();

   fchi2_leftband->Write();
   fchi2_rightband->Write();
   fchi2_band->Write();
   fchi2_signalregion->Write();
   fchi2_signal_data->Write();

   fprob_leftband->Write();
   fprob_rightband->Write();
   fprob_band->Write();
   fprob_signalregion->Write();
   fprob_signal_data->Write();

   output->Close();


}
