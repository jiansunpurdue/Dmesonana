#include <string>
#include <vector>
#include <map>
#include <iostream>
#include <TFile.h>
#include <TH1F.h>
#include <TMath.h>
#include <TF1.h>
#include <TNamed.h>
#include <TNtuple.h>
#include <TTree.h>
#include <TMath.h>
#include <TCanvas.h>
#include <TStyle.h>
#include <TLatex.h>
#include "Math/MinimizerOptions.h"

#include "PtBins.h"

#define MAXGENDMESON 100

using namespace std;

const int ffls3dcut = 2.0;
bool isMC = true;


TH1D* d0genpt;
TH1F* hfg_minbias[NPT];  //for D0
TH1F* hfg_minbias_MCmatched[NPT];
TH1F* hfg_minbias_MCdoublecounted[NPT];
TH1F* hfg_minbias_bkg[NPT]; 

TH1F* hfg_Jet20[NPT];
TH1F* hfg_Jet20_MCmatched[NPT];
TH1F* hfg_Jet40[NPT];
TH1F* hfg_Jet40_MCmatched[NPT];
TH1F* hfg_Jet60[NPT];
TH1F* hfg_Jet60_MCmatched[NPT];
TH1F* hfg_Jet80[NPT];
TH1F* hfg_Jet80_MCmatched[NPT];
TH1F* hfg_Jet100[NPT];
TH1F* hfg_Jet100_MCmatched[NPT];
TH1F* hfg_Jettrigcombo[NPT];
TH1F* hfg_Jettrigcombo_MCmatched[NPT];
TH1F* hfg_Jettrigcombo_MCdoublecounted[NPT];
TH1F* hfg_Jettrigcombo_bkg[NPT];

float cut_m_low = 1.70;
float cut_m_high = 2.05;
int massbin = 35;


void book_hist()
{
    TH1::SetDefaultSumw2();
	d0genpt = new TH1D("d0genpt","d0genpt", NPT, ptbins);
	d0genpt->Sumw2();
	char hname[100], pt_range[1000];
	for(int i = 0; i<NPT; i++)
	{
		float pt_low = ptbins[i];
		float pt_high = ptbins[i+1];
		sprintf(pt_range, "pt: %f %f", pt_low, pt_high);
		
		sprintf(hname, "hfg_minbias_%d", i);
		hfg_minbias[i] = new TH1F(hname, pt_range, massbin, cut_m_low, cut_m_high);
		hfg_minbias[i]->Sumw2();

		sprintf(hname, "hfg_minbias_MCmatched_%d", i);
		hfg_minbias_MCmatched[i] = new TH1F(hname, pt_range, massbin, cut_m_low, cut_m_high);
		hfg_minbias_MCmatched[i]->Sumw2();

		sprintf(hname, "hfg_minbias_MCdoublecounted_%d", i);
		hfg_minbias_MCdoublecounted[i] = new TH1F(hname, pt_range, massbin, cut_m_low, cut_m_high);
		hfg_minbias_MCdoublecounted[i]->Sumw2();

		sprintf(hname, "hfg_minbias_bkg_%d", i);
		hfg_minbias_bkg[i] = new TH1F(hname, pt_range, massbin, cut_m_low, cut_m_high);
		hfg_minbias_bkg[i]->Sumw2();

		sprintf(hname, "hfg_Jettrigcombo_%d", i);
		hfg_Jettrigcombo[i] = new TH1F(hname, pt_range, massbin, cut_m_low, cut_m_high);
		hfg_Jettrigcombo[i]->Sumw2();

		sprintf(hname, "hfg_Jettrigcombo_MCmatched_%d", i);
		hfg_Jettrigcombo_MCmatched[i] = new TH1F(hname, pt_range, massbin, cut_m_low, cut_m_high);
		hfg_Jettrigcombo_MCmatched[i]->Sumw2();

		sprintf(hname, "hfg_Jet20_%d", i);
		hfg_Jet20[i] = new TH1F(hname, pt_range, massbin, cut_m_low, cut_m_high);
		hfg_Jet20[i]->Sumw2();
		sprintf(hname, "hfg_Jet20_MCmatched_%d", i);
		hfg_Jet20_MCmatched[i] = new TH1F(hname, pt_range, massbin, cut_m_low, cut_m_high);
		hfg_Jet20_MCmatched[i]->Sumw2();

		sprintf(hname, "hfg_Jet40_%d", i);
		hfg_Jet40[i] = new TH1F(hname, pt_range, massbin, cut_m_low, cut_m_high);
		hfg_Jet40[i]->Sumw2();
		sprintf(hname, "hfg_Jet40_MCmatched_%d", i);
		hfg_Jet40_MCmatched[i] = new TH1F(hname, pt_range, massbin, cut_m_low, cut_m_high);
		hfg_Jet40_MCmatched[i]->Sumw2();

		sprintf(hname, "hfg_Jet60_%d", i);
		hfg_Jet60[i] = new TH1F(hname, pt_range, massbin, cut_m_low, cut_m_high);
		hfg_Jet60[i]->Sumw2();
		sprintf(hname, "hfg_Jet60_MCmatched_%d", i);
		hfg_Jet60_MCmatched[i] = new TH1F(hname, pt_range, massbin, cut_m_low, cut_m_high);
		hfg_Jet60_MCmatched[i]->Sumw2();

		sprintf(hname, "hfg_Jet80_%d", i);
		hfg_Jet80[i] = new TH1F(hname, pt_range, massbin, cut_m_low, cut_m_high);
		hfg_Jet80[i]->Sumw2();
		sprintf(hname, "hfg_Jet80_MCmatched_%d", i);
		hfg_Jet80_MCmatched[i] = new TH1F(hname, pt_range, massbin, cut_m_low, cut_m_high);
		hfg_Jet80_MCmatched[i]->Sumw2();

		sprintf(hname, "hfg_Jet100_%d", i);
		hfg_Jet100[i] = new TH1F(hname, pt_range, massbin, cut_m_low, cut_m_high);
		hfg_Jet100[i]->Sumw2();
		sprintf(hname, "hfg_Jet100_MCmatched_%d", i);
		hfg_Jet100_MCmatched[i] = new TH1F(hname, pt_range, massbin, cut_m_low, cut_m_high);
		hfg_Jet100_MCmatched[i]->Sumw2();
	}
}

void write_histo( TFile * output)
{
   for(int i = 0; i<NPT; i++)
   {
	   hfg_minbias[i]->Write();
	   hfg_minbias_MCmatched[i]->Write();
	   hfg_minbias_MCdoublecounted[i]->Write();
	   hfg_minbias_bkg[i]->Write();
	   hfg_Jettrigcombo[i]->Write();
	   hfg_Jettrigcombo_MCmatched[i]->Write();
	   hfg_Jet20[i]->Write();
	   hfg_Jet20_MCmatched[i]->Write();
	   hfg_Jet40[i]->Write();
	   hfg_Jet40_MCmatched[i]->Write();
	   hfg_Jet60[i]->Write();
	   hfg_Jet60_MCmatched[i]->Write();
	   hfg_Jet80[i]->Write();
	   hfg_Jet80_MCmatched[i]->Write();
	   hfg_Jet100[i]->Write();
	   hfg_Jet100_MCmatched[i]->Write();
   }
   output->Close();
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

void fit_hist( TH1F * histo, TCanvas *cfg, int iptbin , TH1D * counts, TH1D * N_sig, float lowrange, float highrange)
{

	ROOT::Math::MinimizerOptions::SetDefaultMaxFunctionCalls(100000); 
    cfg->cd(iptbin);

    cout << "/////////////////////////////////////*********************************i**************         " << iptbin << endl;
    histo->SetMarkerSize(0.8);
    histo->SetLineColor(2);
    histo->SetMarkerColor(2);
    histo->SetMarkerStyle(20);
    histo->GetXaxis()->SetNdivisions(505);
    histo->GetXaxis()->SetTitle("m_{#piK} (GeV)");
    histo->GetYaxis()->SetTitle("Counts");
    histo->GetXaxis()->SetRangeUser(cut_m_low, cut_m_high);
//    TF1* fit_fun = new TF1("fit_fun", fitfunction, cut_m_low, cut_m_high, 6);
    //.. fit with a Gaussian and pol
    TF1* fit_fun = new TF1("fit_fun", "gausn(0) + pol2(3)", cut_m_low, cut_m_high);
//    TF1* fit_fun = new TF1("fit_fun", "gausn(0) + expo(3)", cut_m_low, cut_m_high);
//    TF1* fit_fun = new TF1("fit_fun", "gausn(0) + expo(6)", cut_m_low, cut_m_high);
    float max = histo->GetMaximum();

    float p0 = 1000, p1 = 1.87, p2 = 0.02;
    float p0_L = 0, p1_L = 1.84, p2_L = 0;
    float p0_H = 2*max, p1_H = 1.9, p2_H = 0.05;

	float p3 = -1. * max, p4 = max, p5 = -1. * max;
    
	int pass = 0;
    int fittingtry = 0;

	char sig_print[100], chi2_print[100];

    while (!pass) {

        fit_fun->SetParameter(0, p0);
        fit_fun->SetParameter(1, p1);
        fit_fun->SetParameter(2, p2);

        //.. fit constraint ..
        fit_fun->SetParLimits(0, p0_L, p0_H);
        fit_fun->SetParLimits(1, p1_L, p1_H);
        fit_fun->SetParLimits(2, p2_L, p2_H);

//        fit_fun->SetParameter(3, p3);
//		fit_fun->SetParameter(4, p4);
//		fit_fun->SetParameter(5, p5);

        if( fittingtry == 0 )
            histo->Fit(fit_fun,"","", cut_m_low, cut_m_high);
        else 
//			histo->Fit(fit_fun,"WL","", cut_m_low, cut_m_high);
			histo->Fit(fit_fun,"","", cut_m_low, cut_m_high);

        //.. draw foreground and background ..
        histo->Draw();

        TF1* fit_fun_1st = (TF1*)fit_fun->Clone("fit_fun_1st");
        fit_fun_1st->SetParameter(3, 0);
        fit_fun_1st->SetParameter(4, 0);
        fit_fun_1st->SetParameter(5, 0);
		fit_fun_1st->SetLineColor(4);
		fit_fun_1st->SetLineStyle(2);
        fit_fun_1st->Draw("same");


        TF1* fit_fun_bg = (TF1*)fit_fun->Clone("fit_fun_bg");
//        TF1* fit_fun_bg = new TF1("fit_fun_bg", fitfunction, cut_m_low, cut_m_high, 6);
        fit_fun_bg->SetParameter(0, 0);
        fit_fun_bg->SetParameter(1, 0);
        fit_fun_bg->SetParameter(2, 0);
//		fit_fun_bg->SetParameter(3, fit_fun->GetParameter(3));
//		fit_fun_bg->SetParameter(4, fit_fun->GetParameter(4));
//		fit_fun_bg->SetParameter(5, fit_fun->GetParameter(5));


        fit_fun_bg->SetLineColor(8);
        fit_fun_bg->Draw("same");


        fittingtry++;

		if( ptbins[iptbin] > lowrange && ptbins[iptbin+1] < highrange )
		{
		   float binwidth = histo->GetBinWidth(10);
		   float ptbinwidth = ptbins[iptbin+1] - ptbins[iptbin];
		   counts->SetBinContent( iptbin+1, fit_fun->GetParameter(0)/( binwidth * ptbinwidth ));
	   	   counts->SetBinError( iptbin+1, fit_fun->GetParError(0)/( binwidth * ptbinwidth ));
//           counts->SetBinContent( iptbin+1, fit_fun->GetParameter(0)/binwidth );
//		   counts->SetBinError( iptbin+1, fit_fun->GetParError(0)/binwidth );
		   
		   float Nsig = fit_fun->GetParameter(0)/( binwidth );
		   float err_Nsig = fit_fun->GetParError(0)/( binwidth );
		   float fitchi2 = fit_fun->GetChisquare();
		   int noffreepara = fit_fun->GetNumberFreeParameters();
		   int noffitpoints = fit_fun->GetNumberFitPoints();

		   N_sig->SetBinContent( iptbin+1, Nsig);
		   N_sig->SetBinError( iptbin+1, err_Nsig);

		   cout << " fitchi2: " << fitchi2 << "   noffreepara: " << noffreepara << "  noffitpoints: " << noffitpoints << endl;

           if( !isMC )
		       sprintf( sig_print,"N_{sig} = %7.1f #pm %7.1f", Nsig, err_Nsig);
		   else
			   sprintf( sig_print,"10^{6} * N_{sig} = %7.2f #pm %7.2f", 1000000 * Nsig, 1000000 * err_Nsig);
//               sprintf( sig_print,"N_{sig} = %7.2f #pm %7.2f", Nsig, err_Nsig);
		   sprintf( chi2_print, "#chi^{2}#/d.o.f = %3.2f", fitchi2/( noffitpoints - noffreepara));

		   if (fittingtry == 2)
		   {
			   TLatex Tl;
			   Tl.SetNDC();
			   Tl.SetTextAlign(12);
			   Tl.SetTextSize(0.05);
			   Tl.DrawLatex(0.55,0.8, sig_print);
			   Tl.DrawLatex(0.55,0.7, chi2_print);
		   }

		}

        if (fittingtry == 2)  
		{
			pass = 1;

		}
        if(!pass) {
            p0 = fit_fun->GetParameter(0);
			p1 = fit_fun->GetParameter(1);
			p2 = fit_fun->GetParameter(2);
//            p1_L = 1.84, p2_L = 0;
//            p1_H = 1.9, p2_H = 0.05;
        }
    }


    return;


}

void FillSpectrum_MC_pp()
{
	book_hist();

    TH1F* deltapt = new TH1F("deltapt","deltapt",100,-2.0,2.0);
	TH1F* deltapt_overgen = new TH1F("deltapt_overgen","deltapt_overgen",1000,0,0.5);
    TH1F* deltaR = new TH1F("deltaR","deltaR",1000,0.0,0.3);
    deltapt->Sumw2();
    deltaR->Sumw2();
	deltapt_overgen->Sumw2();

    TFile * input = new TFile("Dmesonana_hiforest_D0filtered_2760GeV_D0pt3_pthat015305080120_1220_1222_all.root");
    TTree * recodmesontree = (TTree *) input->Get("recodmesontree");
	TTree * gendmesontree = (TTree *) input->Get("gendmesontree");
	recodmesontree->AddFriend(gendmesontree);

	float pthat;
	int ngend;
	float dpt[MAXGENDMESON];
	float deta[MAXGENDMESON];
	gendmesontree->SetBranchAddress("pthat", &pthat);
	gendmesontree->SetBranchAddress("ngend", &ngend);
	gendmesontree->SetBranchAddress("dpt", dpt);
	gendmesontree->SetBranchAddress("deta", deta);
    
    int MinBias;
    int MinBias_Prescl;
    int Jet20;
    int Jet20_Prescl;
    int Jet40;
    int Jet40_Prescl;
    int Jet60;
    int Jet60_Prescl;
    int Jet80;
    int Jet80_Prescl;
    int Jet100;
    int Jet100_Prescl;

    int ndcand;
    int hiBin;
    double pthatweight;
    double trigweight;
    float maxJetTrgPt;
    vector<int> *dtype = 0, *passingcuts = 0;
    vector<float> *dcandmass = 0, *dcandpt = 0, *dcandeta = 0, *dcandphi = 0, *dcandffls3d = 0, *dcandalpha = 0, *dcandfprob = 0, *dcandfchi2 = 0;
    vector<float> *dcanddau1eta = 0, *dcanddau2eta = 0;
	vector<int>   *matchedtogen = 0, *dcandmatchedpdg = 0, *nongendoublecounted = 0;
	vector<float> *dcandmatchedpt = 0, *dcandmatchedeta = 0, *dcandmatchedphi = 0, *dcandmatchnofdau = 0;

    recodmesontree->SetBranchAddress("MinBias", &MinBias);
    recodmesontree->SetBranchAddress("MinBias_Prescl", &MinBias_Prescl);
    recodmesontree->SetBranchAddress("Jet20", &Jet20);
    recodmesontree->SetBranchAddress("Jet20_Prescl", &Jet20_Prescl);
    recodmesontree->SetBranchAddress("Jet40", &Jet40);
    recodmesontree->SetBranchAddress("Jet40_Prescl", &Jet40_Prescl);
    recodmesontree->SetBranchAddress("Jet60", &Jet60);
    recodmesontree->SetBranchAddress("Jet60_Prescl", &Jet60_Prescl);
    recodmesontree->SetBranchAddress("Jet80", &Jet80);
    recodmesontree->SetBranchAddress("Jet80_Prescl", &Jet80_Prescl);
    recodmesontree->SetBranchAddress("Jet100", &Jet100);
    recodmesontree->SetBranchAddress("Jet100_Prescl", &Jet100_Prescl);

    recodmesontree->SetBranchAddress("maxJetTrgPt", &maxJetTrgPt);
    recodmesontree->SetBranchAddress("pthatweight", &pthatweight);
    recodmesontree->SetBranchAddress("trigweight", &trigweight);
    recodmesontree->SetBranchAddress("ndcand", &ndcand);
    recodmesontree->SetBranchAddress("dtype", &dtype);
    recodmesontree->SetBranchAddress("passingcuts", &passingcuts);
    recodmesontree->SetBranchAddress("dcandmass", &dcandmass);
    recodmesontree->SetBranchAddress("dcandpt", &dcandpt);
    recodmesontree->SetBranchAddress("dcandeta", &dcandeta);
    recodmesontree->SetBranchAddress("dcandphi", &dcandphi);
    recodmesontree->SetBranchAddress("dcandffls3d", &dcandffls3d);
    recodmesontree->SetBranchAddress("dcandalpha", &dcandalpha);
    recodmesontree->SetBranchAddress("dcandfprob", &dcandfprob);
    recodmesontree->SetBranchAddress("dcandfchi2", &dcandfchi2);
	recodmesontree->SetBranchAddress("matchedtogen", &matchedtogen);
	recodmesontree->SetBranchAddress("nongendoublecounted", &nongendoublecounted);
	recodmesontree->SetBranchAddress("dcandmatchedpt", &dcandmatchedpt);
	recodmesontree->SetBranchAddress("dcandmatchedeta", &dcandmatchedeta);
	recodmesontree->SetBranchAddress("dcandmatchedphi", &dcandmatchedphi);
//    recodmesontree->SetBranchAddress("dcanddau1eta", &dcanddau1eta);
//    recodmesontree->SetBranchAddress("dcanddau2eta", &dcanddau2eta);
    
//   cout << " total number of event: " << recodmesontree->GetEntries() << endl;
   for ( int entry = 0; entry < recodmesontree->GetEntries(); entry++ )
//   for ( unsigned int entry = 0; entry < 200000; entry++ )
   {
	   recodmesontree->GetEntry(entry);
	   if( entry % 1000000 == 0 )  cout << entry+1 << "st event" << endl;
	   if( !MinBias && !Jet20 && !Jet40 && !Jet60 && !Jet80 && !Jet100 ) continue;
	   if( ndcand != dtype->size() || ndcand != passingcuts->size() || ndcand != dcandmass->size() || ndcand != dcandpt->size() )    
		   cout << "Error!!!!!!!!" << endl;
           
	   double weight = 1.0;
	   weight = pthatweight;   // should be weight_pthat
//	   weight = 1.0;

       for( int igend = 0; igend < ngend; igend++ )
       {
           if( !MinBias )   continue;
//           if( pthat < 5 && dpt[igend] > 5.0 ) continue;
//           if( pthat > 5.0 && pthat < 15.0 && dpt[igend] > 7.0 ) continue;
           if( pthat < 15 && dpt[igend] > 9.0 ) continue;
           if( pthat > 15.0 && pthat < 30.0 && dpt[igend] > 16.0 ) continue;
           if( deta[igend] < -2.0 || deta[igend] > 2.0 )   continue;
           d0genpt->Fill( dpt[igend], weight);
       }

	   for( int icand = 0; icand < ndcand; icand++ )
	   {
		   if( !passingcuts->at(icand) )   continue;
		   if( dcandffls3d->at(icand) < ffls3dcut )   continue;

//		   if( dcandalpha->at(icand) > 0.5 )   continue;
//		   if( dcandfprob->at(icand) < 0.05 )  continue;
		   if( dcandeta->at(icand) < -2.0 || dcandeta->at(icand) > 2.0 )  continue;
		   if( dtype->at(icand) != 2 )   cout << " Error!!!!!!! Just working on D0 now" << endl;
		   int ipt = decideptbin( dcandpt->at(icand) );
		   if( ipt < 0 ) continue;

//           if( pthat < 5 && dcandpt->at(icand) > 5.0 )   continue;
//           if( pthat > 5.0 && pthat < 15.0 && dcandpt->at(icand) > 7.0 )   continue;

           if( pthat < 15 && dcandpt->at(icand) > 9.0 )   continue;
           if( pthat > 15.0 && pthat < 30.0 && dcandpt->at(icand) > 16.0 )   continue;

//		   cout << " pt: " << dcandpt->at(icand) << "  ipt: " << ipt << endl;
           if( MinBias )
		   {
		       hfg_minbias[ipt]->Fill(dcandmass->at(icand), weight);

		       if( matchedtogen->at(icand) == 1 && nongendoublecounted->at(icand) == 1)
		           {
		        	   hfg_minbias_MCmatched[ipt]->Fill(dcandmass->at(icand), weight);
		        	   deltapt->Fill(dcandmatchedpt->at(icand) - dcandpt->at(icand), weight);
		        	   deltapt_overgen->Fill( TMath::Abs( ( dcandmatchedpt->at(icand) - dcandpt->at(icand) ) / dcandmatchedpt->at(icand) ), weight);
		        	   double dr = TMath::Sqrt( (dcandmatchedeta->at(icand) - dcandeta->at(icand) ) * (dcandmatchedeta->at(icand) - dcandeta->at(icand) ) + (dcandmatchedphi->at(icand) - dcandphi->at(icand) ) * (dcandmatchedphi->at(icand) - dcandphi->at(icand) )  );
		        	   deltaR->Fill(dr, weight);
		           }
		       if( matchedtogen->at(icand) == 1 && nongendoublecounted->at(icand) == 0)
		           hfg_minbias_MCdoublecounted[ipt]->Fill(dcandmass->at(icand), weight);
		       if( matchedtogen->at(icand) == 0 )
			   hfg_minbias_bkg[ipt]->Fill(dcandmass->at(icand), weight);
		   }

		   if( trigweight > 0.5 )    // should not be necessary, trigweight is 0 for events, which don't contribute to trig combination
		   {
			   hfg_Jettrigcombo[ipt]->Fill(dcandmass->at(icand), weight);
			   if( matchedtogen->at(icand) == 1 && nongendoublecounted->at(icand) == 1)
				   hfg_Jettrigcombo_MCmatched[ipt]->Fill(dcandmass->at(icand), weight);

			   if( Jet20 )
			   {
				   hfg_Jet20[ipt]->Fill(dcandmass->at(icand), weight);
				   if( matchedtogen->at(icand) == 1 && nongendoublecounted->at(icand) == 1)
					   hfg_Jet20_MCmatched[ipt]->Fill(dcandmass->at(icand), weight);
			   }

			   if( Jet40 )
			   {
				   hfg_Jet40[ipt]->Fill(dcandmass->at(icand), weight);
				   if( matchedtogen->at(icand) == 1 && nongendoublecounted->at(icand) == 1)
					   hfg_Jet40_MCmatched[ipt]->Fill(dcandmass->at(icand), weight);
			   }

			   if( Jet60 )
			   {
				   hfg_Jet60[ipt]->Fill(dcandmass->at(icand), weight);
				   if( matchedtogen->at(icand) == 1 && nongendoublecounted->at(icand) == 1)
					   hfg_Jet60_MCmatched[ipt]->Fill(dcandmass->at(icand), weight);
			   }

			   if( Jet80 )
			   {
				   hfg_Jet80[ipt]->Fill(dcandmass->at(icand), weight);
				   if( matchedtogen->at(icand) == 1 && nongendoublecounted->at(icand) == 1)
					   hfg_Jet80_MCmatched[ipt]->Fill(dcandmass->at(icand), weight);
			   }

			   if( Jet100 )
			   {
				   hfg_Jet100[ipt]->Fill(dcandmass->at(icand), weight);
				   if( matchedtogen->at(icand) == 1 && nongendoublecounted->at(icand) == 1)
					   hfg_Jet100_MCmatched[ipt]->Fill(dcandmass->at(icand), weight);
			   }
		   }

	   }
   }

   gStyle->SetOptFit(0);
   gStyle->SetOptStat(0);
   gStyle->SetHistMinimumZero(kTRUE);

   TH1D * N_mb_matched = new TH1D("N_mb_matched","N_mb_matched",NPT,ptbins);
   N_mb_matched->Sumw2(); 
   TH1D * N_Jettrig_matched = new TH1D("N_Jettrig_matched","N_Jettrig_matched",NPT,ptbins);
   N_Jettrig_matched->Sumw2();
   TH1D * N_Jet20_matched = new TH1D("N_Jet20_matched","N_Jet20_matched",NPT,ptbins);
   N_Jet20_matched->Sumw2();
   TH1D * N_Jet40_matched = new TH1D("N_Jet40_matched","N_Jet40_matched",NPT,ptbins);
   N_Jet40_matched->Sumw2();
   TH1D * N_Jet60_matched = new TH1D("N_Jet60_matched","N_Jet60_matched",NPT,ptbins);
   N_Jet60_matched->Sumw2();
   TH1D * N_Jet80_matched = new TH1D("N_Jet80_matched","N_Jet80_matched",NPT,ptbins);
   N_Jet80_matched->Sumw2();
   TH1D * N_Jet100_matched = new TH1D("N_Jet100_matched","N_Jet100_matched",NPT,ptbins);
   N_Jet100_matched->Sumw2();

   TH1D * N_gendpt = new TH1D("N_gendpt", "N_gendpt", NPT,ptbins);
   N_gendpt->Sumw2();
   for( int i = 0; i < NPT; i++ )
   {
       float ptbinwidth = ptbins[i+1] - ptbins[i];
       N_gendpt->SetBinContent( i+1,  d0genpt->GetBinContent(i+1) / ptbinwidth);
       N_gendpt->SetBinError( i+1, d0genpt->GetBinError(i+1) / ptbinwidth);
   }
   
   TH1D * N_mb = new TH1D("N_mb","N_mb",NPT,ptbins);    //  dN/dp_T
   N_mb->Sumw2();
   TH1D * N_mb_sig = new TH1D("N_mb_sig","N_mb_sig", NPT, ptbins);   // dN
   N_mb_sig->Sumw2();
   
   TCanvas* cfg_mb = new TCanvas("cfg_mb", "cfg_mb", 1000, 1000);
   cfg_mb->Divide(3, 3);
//   cfg_mb->Divide(4, 4);

   for ( int i = 1; i < NPT-1; i++)
	   fit_hist( hfg_minbias[i], cfg_mb, i, N_mb, N_mb_sig, -1.0, 200.0);
   for ( int i = 1; i < NPT-1; i++)
   {
	   cfg_mb->cd(i);
       hfg_minbias_MCmatched[i]->SetMarkerSize(0.8);
       hfg_minbias_MCmatched[i]->SetLineColor(4);
       hfg_minbias_MCmatched[i]->SetMarkerColor(4);
       hfg_minbias_MCmatched[i]->SetMarkerStyle(20);
	   hfg_minbias_MCmatched[i]->Draw("same");
       hfg_minbias_MCdoublecounted[i]->SetMarkerSize(0.8);
       hfg_minbias_MCdoublecounted[i]->SetLineColor(12);
       hfg_minbias_MCdoublecounted[i]->SetMarkerColor(12);
       hfg_minbias_MCdoublecounted[i]->SetMarkerStyle(20);
	   hfg_minbias_MCdoublecounted[i]->Draw("same");
       
       float binwidth = hfg_minbias_MCmatched[i]->GetBinWidth(10);
       float ptbinwidth = ptbins[i+1] - ptbins[i];
	   double error = 0.0;

	   N_mb_matched->SetBinContent( i+1, hfg_minbias_MCmatched[i]->IntegralAndError(0,-1, error) / ( ptbinwidth ) );
	   N_mb_matched->SetBinError( i+1, error/ptbinwidth );
	   N_Jettrig_matched->SetBinContent( i+1, hfg_Jettrigcombo_MCmatched[i]->IntegralAndError(0,-1, error) / ( ptbinwidth ) );
	   N_Jettrig_matched->SetBinError( i+1, error/ptbinwidth );
	   N_Jet20_matched->SetBinContent( i+1, hfg_Jet20_MCmatched[i]->IntegralAndError(0,-1, error) / ( ptbinwidth ) );
	   N_Jet20_matched->SetBinError( i+1, error/ptbinwidth );
	   N_Jet40_matched->SetBinContent( i+1, hfg_Jet40_MCmatched[i]->IntegralAndError(0,-1, error) / ( ptbinwidth ) );
	   N_Jet40_matched->SetBinError( i+1, error/ptbinwidth );
	   N_Jet60_matched->SetBinContent( i+1, hfg_Jet60_MCmatched[i]->IntegralAndError(0,-1, error) / ( ptbinwidth ) );
	   N_Jet60_matched->SetBinError( i+1, error/ptbinwidth );
	   N_Jet80_matched->SetBinContent( i+1, hfg_Jet80_MCmatched[i]->IntegralAndError(0,-1, error) / ( ptbinwidth ) );
	   N_Jet80_matched->SetBinError( i+1, error/ptbinwidth );
	   N_Jet100_matched->SetBinContent( i+1, hfg_Jet100_MCmatched[i]->IntegralAndError(0,-1, error) / ( ptbinwidth ) );
	   N_Jet100_matched->SetBinError( i+1, error/ptbinwidth );
   }
   
   char outputfile[200];
   sprintf(outputfile,"Dspectrum_pp_MC_genmatch_histo_ptbin_%d.root", NPT);
   TFile * output = new TFile(outputfile,"RECREATE");
   d0genpt->Write();
   N_gendpt->Write(); 
   N_mb->Write();
   N_mb_sig->Write();
   N_mb_matched->Write();
   N_Jettrig_matched->Write();
   N_Jet20_matched->Write();
   N_Jet40_matched->Write();
   N_Jet60_matched->Write();
   N_Jet80_matched->Write();
   N_Jet100_matched->Write();
   cfg_mb->Write();
   deltapt->Write();
   deltaR->Write();
   deltapt_overgen->Write();
   write_histo( output );
}

