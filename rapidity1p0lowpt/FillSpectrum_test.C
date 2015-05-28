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

bool evtunprescaleMB = false;   //false to fit raw counts without unprescale MB trigger
bool isMC = false;

float cut_m_low = 1.70;
float cut_m_high = 2.05;
int massbin = 35;

double dautrackptcut = 1.0;
double dautracketacut = 2.4;

float rapidityrange_low = 0.0;
float rapidityrange_high = 1.0;


const int cfg_N_row = 4;
const int cfg_N_column = 4;
double eff_fit_range_low[NPT] = {1.70, 1.70, 1.70, 1.70, 1.75, 1.72, 1.70, 1.70, 1.70, 1.70, 1.70, 1.70, 1.70, 1.70};
double eff_fit_range_high[NPT] = {2.05, 2.05, 2.05, 2.05, 2.05, 2.05, 2.05, 2.05, 2.05, 2.05, 2.05, 2.05, 2.05, 2.05};
//
//const int cfg_N_row = 3;
//const int cfg_N_column = 2;
//double eff_fit_range_low[NPT] = {1.70, 1.70, 1.70, 1.70, 1.70, 1.70, 1.70};
//double eff_fit_range_high[NPT] = {2.05, 2.05, 2.05, 2.05, 2.05, 2.05, 2.05};
//
float hiBin_low = -0.5;
float hiBin_high = 199.5;

TH1F* hfg_minbias[NPT];  //for D0

TH1F* hfg_massmean;
TH1F* hfg_masssigma;

void book_hist()
{
	TH1::SetDefaultSumw2();

    hfg_massmean = new TH1F( "hfg_massmean", "hfg_massmean", NPT, ptbins);
	hfg_massmean->Sumw2();
	hfg_masssigma = new TH1F("hfg_masssigma","hfg_masssigma",NPT, ptbins);
    hfg_masssigma->Sumw2();

	char hname[100], pt_range[1000];
	for(int i = 0; i<NPT; i++)
	{
		float pt_low = ptbins[i];
		float pt_high = ptbins[i+1];
		sprintf(pt_range, "pt: %2.1f to %2.1f GeV", pt_low, pt_high);
		sprintf(hname, "hfg_minbias_%d", i);
		hfg_minbias[i] = new TH1F(hname, pt_range, massbin, cut_m_low, cut_m_high);
		hfg_minbias[i]->Sumw2();
	}
}

void write_histo( TFile * output)
{
   hfg_massmean->Write();
   hfg_masssigma->Write();

   for(int i = 0; i<NPT; i++)
   {
	   hfg_minbias[i]->Write();
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
    histo->GetYaxis()->SetTitle("Entries");

    double fit_range_low = 1.70;//eff_fit_range_low[iptbin];
    double fit_range_high = 2.05;//eff_fit_range_high[iptbin];

    histo->GetXaxis()->SetRangeUser(fit_range_low, fit_range_high);

    //.. fit with a Gaussian and pol
    TF1* fit_fun = new TF1("fit_fun", "gausn(0) + pol2(3)", fit_range_low, fit_range_high);
    float max = histo->GetMaximum();
	histo->SetMaximum(1.1 * max);

    float p0_signalgaussian = 1000, p1_signalgaussian = 1.87, p2_signalgaussian = 0.02;
    float p0_signalgaussian_L = 0, p1_signalgaussian_L = 1.84, p2_signalgaussian_L = 0;
    float p0_signalgaussian_H = 2*max, p1_signalgaussian_H = 1.9, p2_signalgaussian_H = 0.05;

//	float p3 = -1. * max, p4 = max, p5 = -1. * max;
    
	int pass = 0;
    int fittingtry = 0;

	char sig_print[100], chi2_print[100], mean_print[100], sigma_print[100];

    while (!pass) {

        fit_fun->SetParameter(0, p0_signalgaussian);
        fit_fun->SetParameter(1, p1_signalgaussian);
        fit_fun->SetParameter(2, p2_signalgaussian);

        //.. fit constraint ..
        fit_fun->SetParLimits(0, p0_signalgaussian_L, p0_signalgaussian_H);
        fit_fun->SetParLimits(1, p1_signalgaussian_L, p1_signalgaussian_H);
        fit_fun->SetParLimits(2, p2_signalgaussian_L, p2_signalgaussian_H);

//        fit_fun->SetParameter(3, p3);
//		fit_fun->SetParameter(4, p4);
//		fit_fun->SetParameter(5, p5);

        if( fittingtry == 0 )
            histo->Fit(fit_fun,"","", fit_range_low, fit_range_high);
        else 
			histo->Fit(fit_fun,"","", fit_range_low, fit_range_high);

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
		fit_fun_bg->SetLineStyle(2);
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
		   float fitmean = fit_fun->GetParameter(1);
		   float fitmeanerror = fit_fun->GetParError(1);
		   float fitsigma = fit_fun->GetParameter(2);
		   float fitsigmaerror = fit_fun->GetParError(2);
		   int noffreepara = fit_fun->GetNumberFreeParameters();
		   int noffitpoints = fit_fun->GetNumberFitPoints();

           hfg_massmean->SetBinContent(iptbin+1, fitmean);
		   hfg_massmean->SetBinError(iptbin+1, fitmeanerror);
		   hfg_masssigma->SetBinContent(iptbin+1, fitsigma);
		   hfg_masssigma->SetBinError(iptbin+1, fitsigmaerror);

		   cout << " fitchi2: " << fitchi2 << "   noffreepara: " << noffreepara << "  noffitpoints: " << noffitpoints << endl;

           if( !isMC )
		       sprintf( sig_print,"N_{sig}: %7.1f#pm%7.1f", Nsig, err_Nsig);
		   else
			   sprintf( sig_print,"N_{sig}: %7.5f#pm%7.5f", Nsig, err_Nsig);
		   sprintf( chi2_print, "#chi^{2}#/d.o.f: %3.2f", fitchi2/( noffitpoints - noffreepara));
		   sprintf( mean_print, "mean: %6.4f", fitmean);
		   sprintf( sigma_print, "#sigma: %6.4f", fitsigma);

		   if (fittingtry == 2)
		   {
			   TLatex Tl;
			   Tl.SetNDC();
			   Tl.SetTextAlign(12);
			   Tl.SetTextSize(0.06);
			   if( NPT == 6 )
				   Tl.SetTextSize(0.04);
			   Tl.DrawLatex(0.15,0.8, sig_print);
			   Tl.DrawLatex(0.15,0.7, chi2_print);
			   Tl.DrawLatex(0.55,0.8, mean_print);
			   Tl.DrawLatex(0.55,0.7, sigma_print);
		   }

		}

        if (fittingtry == 2)  
		{
			pass = 1;

		}
        if(!pass) {
            p0_signalgaussian = fit_fun->GetParameter(0);
			p1_signalgaussian = fit_fun->GetParameter(1);
			p2_signalgaussian = fit_fun->GetParameter(2);
//            p1_signalgaussian_L = 1.84, p2_signalgaussian_L = 0;
//            p1_signalgaussian_H = 1.9, p2_signalgaussian_H = 0.05;
        }
    }


    return;


}

void FillSpectrum_test()
{
	book_hist();

	TH1D * hf_mb = new TH1D("hf_mb","hf_mb",10,-5,5);
	hf_mb->Sumw2();

//	TFile * input = new TFile("Dmesonana_hiforest_D0embedded_Hydjet1p8_2760GeV_D0pt4_pthat15305080_1119_all.root");
    TFile * input = new TFile("/scratch/lustreA/s/sun229/Dmesonana_Rereco_MBtrig_d0pt0_tk0p4_d2p5_alpha0p2_tight_nojet_0510_all.root");
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

		   if( TMath::Abs( dcandy->at(icand) ) > rapidityrange_high || TMath::Abs( dcandy->at(icand) ) < rapidityrange_low )  continue;
		   if( TMath::Abs( dcanddau1eta->at(icand) ) > dautracketacut || TMath::Abs( dcanddau2eta->at(icand) ) > dautracketacut )   continue;
		   if( dcanddau1pt->at(icand) < dautrackptcut || dcanddau2pt->at(icand) < dautrackptcut )  continue;
		   
           double effectiveffls3dcut = 100000.;
		   double effectivecosalphacut = 2.0;
		   double effectiveprobcut = -1.0;
           
		   decideeffectivecuts(dcandpt->at(icand), effectiveffls3dcut, effectivecosalphacut, effectiveprobcut);

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
//   gStyle->SetHistMinimumZero(kTRUE);

   TH1D * N_mb = new TH1D("N_mb","N_mb",NPT,ptbins);
   N_mb->Sumw2();
   TCanvas* cfg_mb;
   if( NPT == 12 )
        cfg_mb = new TCanvas("cfg_mb", "cfg_mb", 800, 800);
   else
	    cfg_mb = new TCanvas("cfg_mb", "cfg_mb", 600, 600);

   cfg_mb->Divide(cfg_N_row, cfg_N_column);

   for ( int i = 1; i < NPT -1 ; i++)
	   fit_hist( hfg_minbias[i], cfg_mb, i, N_mb, 0.0, 55.0);
   
   char cfgname[200];
   sprintf(cfgname,"plots/D0_PbPb_data_tk%1.1f_tketa%1.1f_ptbin_%d_ptd_unpreMBtrig_%d_cent%2.0fto%2.0f_rapidity%.1fto%.1f.pdf", dautrackptcut, dautracketacut, NPT, evtunprescaleMB, hiBin_low * 0.5, hiBin_high * 0.5,rapidityrange_low, rapidityrange_high);
   cfg_mb->SaveAs(cfgname);
   sprintf(cfgname,"plots/D0_PbPb_data_tk%1.1f_tketa%1.1f_ptbin_%d_ptd_unpreMBtrig_%d_cent%2.0fto%2.0f_rapidity%.1fto%.1f.gif", dautrackptcut, dautracketacut, NPT, evtunprescaleMB, hiBin_low * 0.5, hiBin_high * 0.5, rapidityrange_low, rapidityrange_high);
   cfg_mb->SaveAs(cfgname);
  
   char outputfile[200];
   sprintf(outputfile,"rootfiles/Dspectrum_pbpb_data_tk%1.1f_tketa%1.1f_ptbin_%d_ptd_unpreMBtrig_%d_cent%2.0fto%2.0f_rapidity%.1fto%.1f.root", dautrackptcut, dautracketacut, NPT, evtunprescaleMB, hiBin_low * 0.5, hiBin_high * 0.5, rapidityrange_low, rapidityrange_high);
   TFile * output = new TFile(outputfile,"RECREATE");
   hf_mb->Write();
   N_mb->Write();
   cfg_mb->Write();
   write_histo( output );
}

