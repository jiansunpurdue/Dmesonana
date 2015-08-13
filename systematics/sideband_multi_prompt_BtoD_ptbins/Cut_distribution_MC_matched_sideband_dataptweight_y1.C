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
#include <TGraphAsymmErrors.h>

#include "sideband.h"


#define MAXGENDMESON 100

//loosecut: 2.0, 0.2, 0.05
//tight: 3.5, 0.05, 0.05
//
#define NPT  12
double ptbins[NPT+1] = {0,3.5,4.5,5.5,7,9,11,13,16,20,28,40,100};

double cut_ffls3d = 3.5;  //2.0
double cut_falpha = 0.12;  //0.2
double cut_fprob = 0.05;  //0.05

double Ptcut_low = 7.0;
double Ptcut_high = 40.0;

float hiBin_low = 59.5;
float hiBin_high = 199.5;

double rapidity_low = 0.0;
double rapidity_high = 1.0;
float dautracketacut = 1.1;
float dautrackptcut = 1.0;

bool isPrompt = false;
bool docentralityweight = true;
bool loosealphacut = false;

bool removedoublecountedD = false;
bool Allcuts = false;
bool nocuts = false;

//not useful, keep it true
bool nosinglecut = true;

//void decideeffectivecuts(double dpt, double &effectiveffls3dcut, double &effectivecosalphacut, double &effectiveprobcut)
//{
//    for( int i = 0; i < NCUTPT; i++ )
//    {
//        if( dpt >= cut_pt_edge[i] && dpt < cut_pt_edge[i+1] )
//        {
//            effectiveffls3dcut = ffls3dcut[i];
//            effectivecosalphacut = TMath::Cos(alphacut[i]);
//            effectiveprobcut = fprobcut[i];
//            break;
//        }
//    }
//    return;
//}
//

void Cut_distribution_MC_matched_sideband_dataptweight_y1()//bool isPrompt=true)
{
	TH1::SetDefaultSumw2();


    TH1D * mass = new TH1D("mass","mass",35,1.70,2.05);
	TH1D * h_pt = new TH1D("h_pt","h_pt",NPT, ptbins);
	TH1D * h_hiBin_reweightwithpt = new TH1D("h_hiBin_reweightwithpt","h_hiBin_reweightwithpt", 20, 0, 200);
	TH1D * h_hiBin_reweight = new TH1D("h_hiBin_reweight","h_hiBin_reweight", 20, 0, 200);

    TH1D * mass_ffls3d = new TH1D("mass_ffls3d","mass_ffls3d", 35, 1.7, 2.05);
    TH1D * ffls3d_signal_data = new TH1D("ffls3d_signal_data","ffls3d_signal_data",1000,0.,100.);
    TH1D * ffls3d_signalregion = new TH1D("ffls3d_signalregion","ffls3d_signalregion",1000,0.,100.);
    TH1D * ffls3d_band = new TH1D("ffls3d_band","ffls3d_band",1000,0,100.);
    TH1D * ffls3d_leftband = new TH1D("ffls3d_leftband","ffls3d_leftband",1000,0,100.);
    TH1D * ffls3d_rightband = new TH1D("ffls3d_rightband","ffls3d_rightband",1000,0,100.);
    TH1D * ffls3d_signalregionbkg = new TH1D("ffls3d_signalregionbkg","ffls3d_signalregionbkg",1000,0,100.);

    TH1D * mass_alpha = new TH1D("mass_alpha","mass_alpha", 35, 1.7, 2.05);
    TH1D * alpha_signal_data = new TH1D("alpha_signal_data","alpha_signal_data",1000,0.,3.2);
    TH1D * alpha_signalregion = new TH1D("alpha_signalregion","alpha_signalregion",1000,0.,3.2);
    TH1D * alpha_band = new TH1D("alpha_band","alpha_band",1000,0.,3.2);
    TH1D * alpha_leftband = new TH1D("alpha_leftband","alpha_leftband",1000,0.,3.2);
    TH1D * alpha_rightband = new TH1D("alpha_rightband","alpha_rightband",1000,0.,3.2);
    TH1D * alpha_signalregionbkg = new TH1D("alpha_signalregionbkg","alpha_signalregionbkg",1000,0,3.2);

    TH1D * mass_fprob = new TH1D("mass_fprob","mass_fprob", 35, 1.70, 2.05);
    TH1D * fprob_signal_data = new TH1D("fprob_signal_data","fprob_signal_data",1000,0.,1.);
    TH1D * fprob_signalregion = new TH1D("fprob_signalregion","fprob_signalregion",1000,0.,1.);
    TH1D * fprob_band = new TH1D("fprob_band","fprob_band",1000,0,1.);
    TH1D * fprob_leftband = new TH1D("fprob_leftband","fprob_leftband",1000,0,1.);
    TH1D * fprob_rightband = new TH1D("fprob_rightband","fprob_rightband",1000,0,1.);
    TH1D * fprob_signalregionbkg = new TH1D("fprob_signalregionbkg","fprob_signalregionbkg",1000,0,1.0);

    TH1D * mass_fchi2 = new TH1D("mass_fchi2","mass_fchi2", 35, 1.70, 2.05);
    TH1D * fchi2_signal_data = new TH1D("fchi2_signal_data","fchi2_signal_data",1000,0.,100.);
    TH1D * fchi2_signalregion = new TH1D("fchi2_signalregion","fchi2_signalregion",1000,0.,100.);
    TH1D * fchi2_band = new TH1D("fchi2_band","fchi2_band",1000,0,100.);
    TH1D * fchi2_leftband = new TH1D("fchi2_leftband","fchi2_leftband",1000,0,100.);
    TH1D * fchi2_rightband = new TH1D("fchi2_rightband","fchi2_rightband",1000,0,100.);
    TH1D * fchi2_signalregionbkg = new TH1D("fchi2_signalregionbkg","fchi2_signalregionbkg",1000,0,100.0);

    TH1D * mass_y = new TH1D("mass_y","mass_y", 35, 1.70, 2.05);
    TH1D * y_signal_data = new TH1D("y_signal_data","y_signal_data",16,-2.,2.);
    TH1D * y_signalregion = new TH1D("y_signalregion","y_signalregion",16,-2.,2.);
    TH1D * y_band = new TH1D("y_band","y_band",16,-2.,2.);
    TH1D * y_leftband = new TH1D("y_leftband","y_leftband",16,-2.,2.);
    TH1D * y_rightband = new TH1D("y_rightband","y_rightband",16,-2.,2.);
	TH1D * y_signalregionbkg = new TH1D("y_signalregionbkg","y_signalregionbkg",1000,0,100.0);


	TH1D * ffls3d_signal_mcmatched = new TH1D("ffls3d_signal_mcmatched","ffls3d_signal_mcmatched",1000,0.,100.); //40
	TH1D * alpha_signal_mcmatched = new TH1D("alpha_signal_mcmatched","alpha_signal_mcmatched",1000,0.,3.2);  //200
	TH1D * fprob_signal_mcmatched = new TH1D("fprob_signal_mcmatched","fprob_signal_mcmatched",1000,0.,1.);  //20
	TH1D * fchi2_signal_mcmatched = new TH1D("fchi2_signal_mcmatched","fchi2_signal_mcmatched",1000,0.,100.); //40
	TH1D * y_signal_mcmatched = new TH1D("y_signal_mcmatched","y_signal_mcmatched",16,-2.0,2.0);
	TH1D * mass_signal_mcmatched = new TH1D("mass_signal_mcmatched","mass_signal_mcmatched",35,1.70,2.05);
    
    TFile * input_fonllweight;
    if( isPrompt )
        input_fonllweight = new TFile("./../../D0_PbPb_rawtoFONLL_1to100_prompt_y1.root");
    else
        input_fonllweight = new TFile("./../../D0_PbPb_rawtoFONLL_1to100_Bfeeddown_RAAscale_y1.root");
    TH1D * fonllweight = ( TH1D * ) input_fonllweight->Get("ratio_rawtofonll");
    TH1D * fonllspectrum = ( TH1D * ) input_fonllweight->Get("hpt");


    TFile * input_fitteddata = new TFile("./../../recoeff_pthatweight_fonllweight/spectrumfitted_data_y1.root");
    int cent_low = int(hiBin_low*0.5+0.5);
    int cent_high = int(hiBin_high*0.5+0.5);
    int Nptbin;

    if( ( cent_low == 0 && cent_high == 30 ) || ( cent_low == 10 && cent_high == 30 ) )  { cent_low = 0; cent_high = 20; Nptbin = 11; }
    if( ( cent_low == 30 && cent_high == 100 ) || ( cent_low == 30 && cent_high == 80 ) )  { cent_low = 30; cent_high = 50; Nptbin = 7; }
    if( cent_low == 0 && cent_high == 100  )  { cent_low = 0; cent_high = 100; Nptbin = 12; }

    cout << " Nptbin: " << Nptbin << "  cent_low: " << cent_low << "  cent_high: " << cent_high << endl;
    TH1D * D0_pbpb_spectrum_fitted = ( TH1D * ) input_fitteddata->Get(Form("D0_pbpb_spectrum_fitted_cent%dto%d_ptbin%d", cent_low, cent_high, Nptbin));
    TF1 * fit_fun_datafitted = D0_pbpb_spectrum_fitted->GetFunction("fit_fun");
    cout << "p0:  " << fit_fun_datafitted->GetParameter(0) << "   p1: " << fit_fun_datafitted->GetParameter(1) << endl;


	TFile * input = new TFile("/home/sun229/DmesonAna/sl6ana/v2_pbpb_08062015/CMSSW_5_3_24/src/UserCode/OpenHF/Dmesonana/Dmesonanarooffiles/Dmesonana_hiforest_PbPbD0tokaonpion_Pthat0153050_D0pt1p0_tkpt1p0eta1p1_2760GeV_0803_all_pt6p0.root");
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
    vector<int> *dtype = 0;
    vector<float> *dcandmass = 0, *dcandpt = 0, *dcandy = 0, *dcandphi = 0, *dcandffls3d = 0, *dcandcosalpha = 0, *dcandfprob = 0, *dcandfchi2 = 0;
    vector<float> *dcanddau1eta = 0, *dcanddau2eta = 0, *dcanddau1pt = 0, *dcanddau2pt = 0;
	vector<int> *dcanddau1q = 0, *dcanddau2q = 0;
	vector<int>   *matchedtogen = 0, *nongendoublecounted = 0;
    vector<float> *matched_pt_Bmom = 0;

    recodmesontree->SetBranchAddress("MinBias", &MinBias);
    recodmesontree->SetBranchAddress("MinBias_Prescl", &MinBias_Prescl);
	recodmesontree->SetBranchAddress("hiBin", &hiBin);
    recodmesontree->SetBranchAddress("pthatweight", &pthatweight);
    recodmesontree->SetBranchAddress("trigweight", &trigweight);
    recodmesontree->SetBranchAddress("ndcand", &ndcand);
    recodmesontree->SetBranchAddress("dtype", &dtype);
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
    recodmesontree->SetBranchAddress("matched_pt_Bmom", &matched_pt_Bmom);
	recodmesontree->SetBranchAddress("dcanddau1pt", &dcanddau1pt);
	recodmesontree->SetBranchAddress("dcanddau2pt", &dcanddau2pt);

	TFile * input_centralityweight = new TFile("/home/sun229/DmesonAna/sl6ana/v2_pbpb_08062015/CMSSW_5_3_24/src/UserCode/OpenHF/Dmesonana/MCcentralityweight/output_hibin_mc_data.root");
	TH1D * h_hibin_dataovermc = (TH1D *) input_centralityweight->Get("h_hibin_dataovermc");
    
   for ( int entry = 0; entry < recodmesontree->GetEntries(); entry++ )
   {
	   recodmesontree->GetEntry(entry);
	   if( entry % 1000000 == 0 )  cout << entry+1 << "st event" << endl;
	   if( !MinBias ) continue;
	   if( ndcand != dtype->size() || ndcand != dcandmass->size() || ndcand != dcandpt->size() )    
		   cout << "Error!!!!!!!!" << endl;
	   if( hiBin < hiBin_low || hiBin > hiBin_high )   continue;
	
//	   double weight = pthatweight;
       double weight = 1.0;
	   double weightcentrality = 1.0;

	   if( docentralityweight ) weightcentrality = h_hibin_dataovermc->GetBinContent( h_hibin_dataovermc->FindBin( hiBin ) );
	   h_hiBin_reweight->Fill( hiBin, weightcentrality);

	   for( int icand = 0; icand < ndcand; icand++ )
	   {
		   
		   if( dcandpt->at(icand) < Ptcut_low || dcandpt->at(icand) > Ptcut_high )  continue;
           if( TMath::Abs( dcandy->at(icand) ) > rapidity_high || TMath::Abs( dcandy->at(icand) ) < rapidity_low )  continue;
		   if( TMath::Abs( dcanddau1eta->at(icand) ) > dautracketacut || TMath::Abs( dcanddau2eta->at(icand) ) > dautracketacut )   continue;
		   if( dcanddau1pt->at(icand) < dautrackptcut || dcanddau2pt->at(icand) < dautrackptcut )   continue;

           if( isPrompt )
               { if( matchedtogen->at(icand) == 1 && matched_pt_Bmom->at(icand) > 0 )   continue; }
           else
               { if( matchedtogen->at(icand) == 1 && matched_pt_Bmom->at(icand) < 0 )   continue; }

		   if( removedoublecountedD && ( matchedtogen->at(icand) == 1 && nongendoublecounted->at(icand) == 0 ) )  continue;
           
		   weight = fonllweight->GetBinContent( fonllweight->FindBin( dcandpt->at(icand) ) );
           double weight_data_fonll = fit_fun_datafitted->Eval( dcandpt->at(icand) )/fonllspectrum->GetBinContent( fonllspectrum->FindBin( dcandpt->at(icand) ));
           weight = weightcentrality * weight * weight_data_fonll;

		   if( matchedtogen->at(icand) == 1 && nongendoublecounted->at(icand) == 1 )  h_hiBin_reweightwithpt->Fill( hiBin, weight);
		   
           double dcandalpha = TMath::ACos(dcandcosalpha->at(icand));

		   if( loosealphacut && dcandalpha > 0.5 )  continue;

           if( Allcuts && ( dcandffls3d->at(icand) < cut_ffls3d || dcandalpha > cut_falpha || dcandfprob->at(icand) < cut_fprob ) )   continue;
           mass->Fill(dcandmass->at(icand), weight);

           //rapidity
           if( nocuts || ( dcandffls3d->at(icand) > cut_ffls3d && dcandalpha < cut_falpha && dcandfprob->at(icand) > cut_fprob ) )
           {
              mass_y->Fill(dcandmass->at(icand), weight);
              if( dcandmass->at(icand) - mass_d0 > -1.0 * sideband_far && dcandmass->at(icand) - mass_d0 < -1.0 * sideband_close )
               y_leftband->Fill(dcandy->at(icand), weight);
              if( dcandmass->at(icand) - mass_d0 > sideband_close && dcandmass->at(icand) - mass_d0 < sideband_far )
               y_rightband->Fill(dcandy->at(icand), weight);
              if( TMath::Abs( dcandmass->at(icand) - mass_d0 ) < width_signal )
			  {
				  y_signalregion->Fill(dcandy->at(icand), weight);
				  if( ! ( matchedtogen->at(icand) == 1 && nongendoublecounted->at(icand) == 1 ) )
					  y_signalregionbkg->Fill(dcandy->at(icand), weight);
			  }
           }


           //decaylength
            if( nocuts || ( dcandalpha < cut_falpha && dcandfprob->at(icand) > cut_fprob ))
            {
               mass_ffls3d->Fill(dcandmass->at(icand), weight);
               if( dcandmass->at(icand) - mass_d0 > -1.0 * sideband_far && dcandmass->at(icand) - mass_d0 < -1.0 * sideband_close )
                   ffls3d_leftband->Fill(dcandffls3d->at(icand), weight);
               if( dcandmass->at(icand) - mass_d0 > sideband_close && dcandmass->at(icand) - mass_d0 < sideband_far )
                   ffls3d_rightband->Fill(dcandffls3d->at(icand), weight);
               if( TMath::Abs( dcandmass->at(icand) - mass_d0 ) < width_signal )
			   {
                   ffls3d_signalregion->Fill(dcandffls3d->at(icand), weight);
				   if( ! ( matchedtogen->at(icand) == 1 && nongendoublecounted->at(icand) == 1 ) )
					   ffls3d_signalregionbkg->Fill(dcandffls3d->at(icand), weight);
			   }
            }

           //alpha
           if( nocuts || ( dcandffls3d->at(icand) > cut_ffls3d && dcandfprob->at(icand) > cut_fprob ) )
           {
              mass_alpha->Fill(dcandmass->at(icand), weight);
              if( dcandmass->at(icand) - mass_d0 > -1.0 * sideband_far && dcandmass->at(icand) - mass_d0 < -1.0 * sideband_close )
               alpha_leftband->Fill(dcandalpha, weight);
              if( dcandmass->at(icand) - mass_d0 > sideband_close && dcandmass->at(icand) - mass_d0 < sideband_far )
               alpha_rightband->Fill(dcandalpha, weight);
              if( TMath::Abs( dcandmass->at(icand) - mass_d0 ) < width_signal )
			  {
				  alpha_signalregion->Fill(dcandalpha, weight);
				  if( ! ( matchedtogen->at(icand) == 1 && nongendoublecounted->at(icand) == 1 ) )
					  alpha_signalregionbkg->Fill(dcandalpha, weight);
			  }
           }

           //prob
           if( nocuts || ( dcandffls3d->at(icand) > cut_ffls3d && dcandalpha < cut_falpha ) )
           {
              mass_fprob->Fill(dcandmass->at(icand), weight);
              if( dcandmass->at(icand) - mass_d0 > -1.0 * sideband_far && dcandmass->at(icand) - mass_d0 < -1.0 * sideband_close )
                  fprob_leftband->Fill(dcandfprob->at(icand), weight);
              if( dcandmass->at(icand) - mass_d0 > sideband_close && dcandmass->at(icand) - mass_d0 < sideband_far )
                  fprob_rightband->Fill(dcandfprob->at(icand), weight);
              if( TMath::Abs( dcandmass->at(icand) - mass_d0 ) < width_signal )
			  {
				  fprob_signalregion->Fill(dcandfprob->at(icand), weight);
				  if( ! ( matchedtogen->at(icand) == 1 && nongendoublecounted->at(icand) == 1 ) )
					  fprob_signalregionbkg->Fill(dcandfprob->at(icand), weight);
			  }
           }

           //fchi2
           if( nocuts || ( dcandffls3d->at(icand) > cut_ffls3d && dcandalpha < cut_falpha ) )
           {
              mass_fchi2->Fill(dcandmass->at(icand), weight);
              if( dcandmass->at(icand) - mass_d0 > -1.0 * sideband_far && dcandmass->at(icand) - mass_d0 < -1.0 * sideband_close )
                  fchi2_leftband->Fill(dcandfchi2->at(icand), weight);
              if( dcandmass->at(icand) - mass_d0 > sideband_close && dcandmass->at(icand) - mass_d0 < sideband_far )
                  fchi2_rightband->Fill(dcandfchi2->at(icand), weight);
              if( TMath::Abs( dcandmass->at(icand) - mass_d0 ) < width_signal )
			  {
				  fchi2_signalregion->Fill(dcandfchi2->at(icand), weight);
				  if( ! ( matchedtogen->at(icand) == 1 && nongendoublecounted->at(icand) == 1 ) )
					  fchi2_signalregionbkg->Fill(dcandfprob->at(icand), weight);
			  }
           }


           if( !( matchedtogen->at(icand) == 1 && nongendoublecounted->at(icand) == 1 ))   continue;
//           if( !( matchedtogen->at(icand) == 1  ))   continue;
		   
		   h_pt->Fill(dcandpt->at(icand), weight);
//alll loose or tight cuts applied?

           double effectiveffls3dcut = 100000.;
           double effectivecosalphacut = 2.0;
           double effectiveprobcut = -1.0;

//           decideeffectivecuts(dcandpt->at(icand), effectiveffls3dcut, effectivecosalphacut, effectiveprobcut);
//         if( dcandpt->at(icand) > 7.0 )
//         cout << "dcandpt: " << dcandpt->at(icand) << "  " << effectiveffls3dcut << "  " << effectiveprobcut << endl;
//           if( dcandffls3d->at(icand) < effectiveffls3dcut || dcandcosalpha->at(icand) < effectivecosalphacut || dcandfprob->at(icand) < effectiveprobcut )
//               continue;


		   if(TMath::Abs( dcandmass->at(icand) - 1.864 ) > width_signal) continue;  //just the D0 mass range

		   //decaylenght
		   if( nocuts || ( dcandalpha < cut_falpha && dcandfprob->at(icand) > cut_fprob ) )  
		   {
			   if( nosinglecut || dcandffls3d->at(icand) > effectiveffls3dcut )
				   ffls3d_signal_mcmatched->Fill(dcandffls3d->at(icand), weight);
		   }

           //cosalpha
		   if( nocuts || ( dcandffls3d->at(icand) > cut_ffls3d && dcandfprob->at(icand) > cut_fprob )) 
           {
			   if( nosinglecut || dcandcosalpha->at(icand) > effectivecosalphacut )
				   alpha_signal_mcmatched->Fill( dcandalpha , weight);
		   }
 
           //fprob
		   if( nocuts || ( dcandffls3d->at(icand) > cut_ffls3d && dcandalpha < cut_falpha ) )
		   {
			   if( nosinglecut || dcandfprob->at(icand) > effectiveprobcut )
				   fprob_signal_mcmatched->Fill(dcandfprob->at(icand), weight);
		   }
           
           //fchi2
		   if( nocuts || ( dcandffls3d->at(icand) > cut_ffls3d && dcandalpha < cut_falpha ) )
		   {
			   if( nosinglecut || dcandfchi2->at(icand) > effectiveprobcut )
				   fchi2_signal_mcmatched->Fill(dcandfchi2->at(icand), weight);
		   }
           
		   if( nocuts || ( dcandffls3d->at(icand) > cut_ffls3d && dcandalpha < cut_falpha && dcandfprob->at(icand) > cut_fprob ) )
	  	   {
			   if( nosinglecut || ( dcandffls3d->at(icand) > effectiveffls3dcut || dcandcosalpha->at(icand) > effectivecosalphacut || dcandfprob->at(icand) > effectiveprobcut )) 
			   {
				   mass_signal_mcmatched->Fill( dcandmass->at(icand), weight);
				   y_signal_mcmatched->Fill(dcandy->at(icand), weight);
			   }
		   }



	   }
   }

   char outputfile[200];
   if( isPrompt )
       sprintf(outputfile,"Cut_distribution_MC_FONLLweight_Prompt_pt%1.0fto%1.0f_rapidity%1.0fto%1.0f_cent%2.0fto%2.0f_sideband_dataptweight.root", Ptcut_low, Ptcut_high, rapidity_low, rapidity_high, hiBin_low * 0.5, hiBin_high * 0.5);
   else
       sprintf(outputfile,"Cut_distribution_MC_FONLLweight_BtoD_pt%1.0fto%1.0f_rapidity%1.0fto%1.0f_cent%2.0fto%2.0f_sideband_dataptweight.root", Ptcut_low, Ptcut_high, rapidity_low, rapidity_high, hiBin_low * 0.5, hiBin_high * 0.5);

   TFile * output = new TFile(outputfile,"RECREATE");

   h_hiBin_reweightwithpt->Write();
   h_hiBin_reweight->Write();

   y_signalregionbkg->Write();
   ffls3d_signalregionbkg->Write();
   alpha_signalregionbkg->Write();
   fprob_signalregionbkg->Write();
   fchi2_signalregionbkg->Write();

   h_pt->Write();
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
   
   y_signal_mcmatched->Write();
   ffls3d_signal_mcmatched->Write();
   alpha_signal_mcmatched->Write();
   fprob_signal_mcmatched->Write();
   fchi2_signal_mcmatched->Write();

   
   output->Close();


}
