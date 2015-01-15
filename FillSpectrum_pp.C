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
#include "Math/MinimizerOptions.h"

#include "PtBins.h"
using namespace std;

const int ffls3dcut = 2.0;
const int cfg_N_row = 3;
const int cfg_N_column = 3;

TH1F* hfg_minbias[NPT];  //for D0
TH1F* hfg_Jet20[NPT];
TH1F* hfg_Jet40[NPT];
TH1F* hfg_Jet60[NPT];
TH1F* hfg_Jet80[NPT];
TH1F* hfg_Jet100[NPT];
TH1F* hfg_Jettrigcombo[NPT];

float cut_m_low = 1.70;
float cut_m_high = 2.05;
int massbin = 35;

bool isMC = false;
bool ispPb = true;

void book_hist()
{
	char hname[100], pt_range[1000];
	for(int i = 0; i<NPT; i++)
	{
		float pt_low = ptbins[i];
		float pt_high = ptbins[i+1];
		sprintf(pt_range, "pt: %f %f", pt_low, pt_high);
		sprintf(hname, "hfg_minbias_%d", i);
		hfg_minbias[i] = new TH1F(hname, pt_range, massbin, cut_m_low, cut_m_high);
		hfg_minbias[i]->Sumw2();

		sprintf(hname, "hfg_Jet20_%d", i);
		hfg_Jet20[i] = new TH1F(hname, pt_range, massbin, cut_m_low, cut_m_high);
		hfg_Jet20[i]->Sumw2();

		sprintf(hname, "hfg_Jet40_%d", i);
		hfg_Jet40[i] = new TH1F(hname, pt_range, massbin, cut_m_low, cut_m_high);
		hfg_Jet40[i]->Sumw2();

		sprintf(hname, "hfg_Jet60_%d", i);
		hfg_Jet60[i] = new TH1F(hname, pt_range, massbin, cut_m_low, cut_m_high);
		hfg_Jet60[i]->Sumw2();

		sprintf(hname, "hfg_Jet80_%d", i);
		hfg_Jet80[i] = new TH1F(hname, pt_range, massbin, cut_m_low, cut_m_high);
		hfg_Jet80[i]->Sumw2();

		sprintf(hname, "hfg_Jet100_%d", i);
		hfg_Jet100[i] = new TH1F(hname, pt_range, massbin, cut_m_low, cut_m_high);
		hfg_Jet100[i]->Sumw2();

		sprintf(hname, "hfg_Jettrigcombo_%d", i);
		hfg_Jettrigcombo[i] = new TH1F(hname, pt_range, massbin, cut_m_low, cut_m_high);
		hfg_Jettrigcombo[i]->Sumw2();
	}
}

void write_histo( TFile * output)
{
   for(int i = 0; i<NPT; i++)
   {
	   hfg_minbias[i]->Write();
	   hfg_Jet20[i]->Write();
	   hfg_Jet40[i]->Write();
	   hfg_Jet60[i]->Write();
	   hfg_Jet80[i]->Write();
	   hfg_Jet100[i]->Write();
	   hfg_Jettrigcombo[i]->Write();
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

void fit_hist( TH1F * histo, TCanvas *cfg, int iptbin , TH1D * counts, float lowrange, float highrange)
{

	ROOT::Math::MinimizerOptions::SetDefaultMaxFunctionCalls(100000); 
    cfg->cd(iptbin);

    cout << "/////////////////////////////////////********        i             **************         " << iptbin << endl;
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
//        fit_fun_1st->Draw("same");


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
		   
		   float Nsig = fit_fun->GetParameter(0)/( binwidth );
		   float err_Nsig = fit_fun->GetParError(0)/( binwidth );
		   float fitchi2 = fit_fun->GetChisquare();
		   int noffreepara = fit_fun->GetNumberFreeParameters();
		   int noffitpoints = fit_fun->GetNumberFitPoints();

		   cout << " fitchi2: " << fitchi2 << "   noffreepara: " << noffreepara << "  noffitpoints: " << noffitpoints << endl;

           if( !isMC )
		       sprintf( sig_print,"N_{sig} = %7.1f #pm %7.1f", Nsig, err_Nsig);
		   else
			   sprintf( sig_print,"N_{sig} = %7.5f #pm %7.5f", Nsig, err_Nsig);
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

void FillSpectrum_pp()
{
	book_hist();

//	TFile * input = new TFile("Dmesonana_hiforest_D0embedded_Hydjet1p8_2760GeV_D0pt4_pthat15305080_1119_all.root");
    TFile * input = new TFile("Dmesonana_pPb_Forest_minbiasUPC_cuts.root");
//    TFile * input = new TFile("Dmesonana_pPb_Forest_highPt_cuts.root");
    TTree * recodmesontree = (TTree *) input->Get("recodmesontree");
    
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
    double trigweight;
	float maxJetTrgPt;
    vector<int> *dtype = 0, *passingcuts = 0;
    vector<float> *dcandmass = 0, *dcandpt = 0, *dcandeta = 0, *dcandphi = 0, *dcandffls3d = 0, *dcandalpha = 0, *dcandfprob = 0, *dcandfchi2 = 0;
    vector<float> *dcanddau1eta = 0, *dcanddau2eta = 0;

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
//    recodmesontree->SetBranchAddress("dcanddau1eta", &dcanddau1eta);
//    recodmesontree->SetBranchAddress("dcanddau2eta", &dcanddau2eta);
    
//   cout << " total number of event: " << recodmesontree->GetEntries() << endl;
   for ( int entry = 0; entry < recodmesontree->GetEntries(); entry++ )
//   for ( unsigned int entry = 0; entry < 200000; entry++ )
   {
	   recodmesontree->GetEntry(entry);
	   if( entry % 1000000 == 0 )  cout << entry+1 << "st event" << endl;
	   if( !MinBias && !Jet20 && !Jet40 && !Jet60 && !Jet80 && !Jet100 )  {  cout << "error!!!!!!!!!" << endl;  continue;}
	   if( ndcand != dtype->size() || ndcand != passingcuts->size() || ndcand != dcandmass->size() || ndcand != dcandpt->size() )    
		   cout << "Error!!!!!!!!" << endl;
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
//		   cout << " pt: " << dcandpt->at(icand) << "  ipt: " << ipt << endl;
           if( MinBias )  hfg_minbias[ipt]->Fill( dcandmass->at(icand), MinBias_Prescl );
           
		   if( trigweight > 0.5 )   // Jet trigger histogram
		   {
               double weight = 0.0;
               if( !isMC )
                   weight = trigweight;           
		       hfg_Jettrigcombo[ipt]->Fill(dcandmass->at(icand), weight);

		       if( Jet20 )  hfg_Jet20[ipt]->Fill(dcandmass->at(icand), Jet20_Prescl );
		       if( Jet40 )  hfg_Jet40[ipt]->Fill(dcandmass->at(icand), Jet40_Prescl );
		       if( Jet60 )  hfg_Jet60[ipt]->Fill(dcandmass->at(icand), Jet60_Prescl );
		       if( Jet80 )  hfg_Jet80[ipt]->Fill(dcandmass->at(icand), Jet80_Prescl );
		       if( Jet100 )  hfg_Jet100[ipt]->Fill(dcandmass->at(icand), Jet100_Prescl );
		   }

	   }
   }

   gStyle->SetOptFit(0);
   gStyle->SetOptStat(0);
//   gStyle->SetHistMinimumZero(kTRUE);

   TH1D * N_mb = new TH1D("N_mb","N_mb",NPT,ptbins);
   N_mb->Sumw2();
   TCanvas* cfg_mb = new TCanvas("cfg_mb", "cfg_mb", 1000, 1000);
   cfg_mb->Divide(cfg_N_column, cfg_N_row);

   for ( int i = 1; i < NPT-1; i++)
	   fit_hist( hfg_minbias[i], cfg_mb, i, N_mb, 4.0, 55.0);
   
   TH1D * N_Jettrig = new TH1D("N_Jettrig","N_Jettrig",NPT,ptbins);
   N_Jettrig->Sumw2();
   TCanvas* cfg_Jettrig = new TCanvas("cfg_Jettrig", "cfg_Jettrig", 1000, 1000);
   cfg_Jettrig->Divide(cfg_N_column, cfg_N_row);

   for ( int i = 1; i < NPT-1; i++)
	   fit_hist( hfg_Jettrigcombo[i], cfg_Jettrig, i, N_Jettrig, 4.0, 55.0);

   TH1D * N_Jet20 = new TH1D("N_Jet20","N_Jet20",NPT,ptbins);
   N_Jet20->Sumw2();
   TCanvas* cfg_Jet20 = new TCanvas("cfg_Jet20", "cfg_Jet20", 1000, 1000);
   cfg_Jet20->Divide(cfg_N_column, cfg_N_row);

   for ( int i = 1; i < NPT-1; i++)
	   fit_hist( hfg_Jet20[i], cfg_Jet20, i, N_Jet20, 4.0, 55.0);

   TH1D * N_Jet40 = new TH1D("N_Jet40","N_Jet40",NPT,ptbins);
   N_Jet40->Sumw2();
   TCanvas* cfg_Jet40 = new TCanvas("cfg_Jet40", "cfg_Jet40", 1000, 1000);
   cfg_Jet40->Divide(cfg_N_column, cfg_N_row);

   for ( int i = 1; i < NPT-1; i++)
	   fit_hist( hfg_Jet40[i], cfg_Jet40, i, N_Jet40, 4.0, 55.0);

   TH1D * N_Jet60 = new TH1D("N_Jet60","N_Jet60",NPT,ptbins);
   N_Jet60->Sumw2();
   TCanvas* cfg_Jet60 = new TCanvas("cfg_Jet60", "cfg_Jet60", 1000, 1000);
   cfg_Jet60->Divide(cfg_N_column, cfg_N_row);

   for ( int i = 1; i < NPT-1; i++)
	   fit_hist( hfg_Jet60[i], cfg_Jet60, i, N_Jet60, 4.0, 55.0);

   TH1D * N_Jet80 = new TH1D("N_Jet80","N_Jet80",NPT,ptbins);
   N_Jet80->Sumw2();
   TCanvas* cfg_Jet80 = new TCanvas("cfg_Jet80", "cfg_Jet80", 1000, 1000);
   cfg_Jet80->Divide(cfg_N_column, cfg_N_row);

   for ( int i = 1; i < NPT-1; i++)
	   fit_hist( hfg_Jet80[i], cfg_Jet80, i, N_Jet80, 4.0, 55.0);

   TH1D * N_Jet100 = new TH1D("N_Jet100","N_Jet100",NPT,ptbins);
   N_Jet100->Sumw2();
   TCanvas* cfg_Jet100 = new TCanvas("cfg_Jet100", "cfg_Jet100", 1000, 1000);
   cfg_Jet100->Divide(cfg_N_column, cfg_N_row);

   for ( int i = 1; i < NPT-1; i++)
	   fit_hist( hfg_Jet100[i], cfg_Jet100, i, N_Jet100, 4.0, 55.0);
   
   char outputfile[200];
   if(!ispPb)
       sprintf(outputfile,"Dspectrum_pp_histo_ptbin_%d.root", NPT);
   else
	   sprintf(outputfile,"Dspectrum_pPb_histo_ptbin_%d.root", NPT);
   TFile * output = new TFile(outputfile,"RECREATE");
   N_mb->Write();
   cfg_mb->Write();
   N_Jettrig->Write();
   cfg_Jettrig->Write();
   N_Jet20->Write();
   cfg_Jet20->Write();
   N_Jet40->Write();
   cfg_Jet40->Write();
   N_Jet60->Write();
   cfg_Jet60->Write();
   N_Jet80->Write();
   cfg_Jet80->Write();
   N_Jet100->Write();
   cfg_Jet100->Write();
   write_histo( output );
}

