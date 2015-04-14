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

#include "./../PtBins.h"
using namespace std;


double NsigMC[NPT] = { 0.,4.71502e+06,4.71502e+06,4.52978e+06,3.53057e+06,1.8534e+06,1.16857e+06,730841, 434796, 226032, 58895.2 , 0.0};
double NsigMCerror[NPT] = { 0.0,106053, 96199.7, 79213.6, 52891.9, 27333.3, 16174.2, 9442.98, 5095.41, 2368.65, 705.864, 0.0};

double p0[NPT] = {0.0, 4.46143e+04, 4.60846e+04, 4.47238e+04, 3.36765e+04, 1.65979e+04, 1.00342e+04, 5.93331e+03, 3.42488e+03, 1.76738e+03, 4.44104e+02, 0.0};
double p0error[NPT] =  { 0.0, 1.06550e+03, 9.82781e+02, 8.94665e+02, 6.81751e+02, 3.46451e+02, 2.08120e+02, 1.14258e+02, 6.55421e+01, 3.36693e+01, 9.40173e+00, 0.0};
double p1[NPT] = { 0.0, 1.86825e+00, 1.86631e+00, 1.87290e+00, 1.86807e+00, 1.87436e+00, 1.86868e+00, 1.86815e+00, 1.86979e+00, 1.86801e+00, 1.87162e+00, 0.0};
double p1error[NPT] = { 0.0, 1.84948e-03, 1.87471e-03, 2.14965e-03, 2.43882e-03, 2.53836e-03, 2.55428e-03, 2.39527e-03, 2.34529e-03, 2.40362e-03, 2.65083e-03, 0.0};
double p2[NPT] = {0.0, 7.32402e-02, 8.08389e-02, 9.76748e-02, 1.13106e-01, 1.13500e-01, 1.17294e-01, 1.15535e-01, 1.19552e-01, 1.27681e-01, 1.24804e-01,0.0};
double p2error[NPT] = { 0.0, 1.57751e-03, 1.73784e-03, 2.33569e-03, 3.17703e-03, 3.26998e-03, 3.38318e-03, 3.00984e-03, 3.14191e-03, 3.43527e-03, 3.70928e-03,0.0};


bool evtunprescaleMB = false;   //false to fit raw counts without unprescale MB trigger
bool isMC = false;

float cut_m_low = 1.70;
float cut_m_high = 2.05;
int massbin = 35;

double eff_fit_range_low[NPT] = {1.70, 1.72, 1.78, 1.74, 1.70, 1.70, 1.70, 1.70, 1.70, 1.70, 1.70, 1.70};
double eff_fit_range_high[NPT] = {2.05, 1.95, 2.00, 2.05, 2.05, 2.05, 2.05, 2.05, 2.05, 2.05, 2.05, 2.05};

const int cfg_N_row = 3;
const int cfg_N_column = 4;

float hiBin_low = -0.5;
float hiBin_high = 199.5;
float rapidityrange = 2.0;

TH1F* hfg_minbias[NPT];  //for D0

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
	}
}

void write_histo( TFile * output)
{
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
    histo->GetYaxis()->SetTitle("Counts");
    double fit_range_low = eff_fit_range_low[iptbin];
    double fit_range_high = eff_fit_range_high[iptbin];
    histo->GetXaxis()->SetRangeUser( fit_range_low, fit_range_high);
//    TF1* fit_fun = new TF1("fit_fun", fitfunction, cut_m_low, cut_m_high, 6);
    //.. fit with a Gaussian and pol
    TF1* fit_fun = new TF1("fit_fun", "gausn(0) + gausn(3) * ([0]/0.01) * (1.0/[6]) + pol1(7)", cut_m_low, cut_m_high);
//    TF1* fit_fun = new TF1("fit_fun", "gausn(0) + expo(3)", cut_m_low, cut_m_high);
//    TF1* fit_fun = new TF1("fit_fun", "gausn(0) + expo(6)", cut_m_low, cut_m_high);
    float max = histo->GetMaximum();
	histo->SetMaximum(1.1 * max);

    double effp0 = p0[iptbin];
    double effp0error = p0error[iptbin];
    double effp1 = p1[iptbin];
    double effp1error = p1error[iptbin];
    double effp2 = p2[iptbin];
    double effp2error = p2error[iptbin];
    double effNsigMC = NsigMC[iptbin];
    double effNsigMCerror = NsigMCerror[iptbin];

    float p0 = 1000, p1 = 1.87, p2 = 0.02;
    float p0_L = 0, p1_L = 1.84, p2_L = 0;
    float p0_H = 2*max, p1_H = 1.9, p2_H = 0.05;

	float p3 = -1. * max, p4 = max, p5 = -1. * max;
    
	int pass = 0;
    int fittingtry = 0;

	char sig_print[100], chi2_print[100], mean_print[100], sigma_print[100];

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

        //pol2 as bkg function
        fit_fun->FixParameter(3, effp0);
        fit_fun->FixParameter(4, effp1);
        fit_fun->FixParameter(5, effp2);
        //    fit_fun->SetParLimits(3, effp0 - effp0error, effp0 + effp0error);
        //    fit_fun->SetParLimits(4, effp1 - effp1error, effp1 + effp1error);
        //    fit_fun->SetParLimits(5, effp2 - effp2error, effp2 + effp2error);
        //    fit_fun->SetParLimits(6, NsigMC[iptbin] - NsigMCerror[iptbin], NsigMC[iptbin] + NsigMCerror[iptbin] );
        fit_fun->FixParameter(6, effNsigMC);

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
        fit_fun_1st->SetParameter(6, 0);
        fit_fun_1st->SetParameter(7, 0);
        fit_fun_1st->SetParameter(8, 0);
        fit_fun_1st->SetLineColor(4);
        fit_fun_1st->SetLineStyle(2);
//        fit_fun_1st->Draw("same");

        TF1* fit_fun_doublecounted = new TF1("fit_fun_doublecounted", "gausn(0) * ([3]/0.01) * (1.0/[4])", fit_range_low, fit_range_high);
        fit_fun_doublecounted->SetParameter(0, fit_fun->GetParameter(3));
        fit_fun_doublecounted->SetParameter(1, fit_fun->GetParameter(4));
        fit_fun_doublecounted->SetParameter(2, fit_fun->GetParameter(5));
        fit_fun_doublecounted->SetParameter(3, fit_fun->GetParameter(0));
        fit_fun_doublecounted->SetParameter(4, fit_fun->GetParameter(6));
        fit_fun_doublecounted->SetLineColor(12);
        fit_fun_doublecounted->SetLineStyle(2);
//        fit_fun_doublecounted->Draw("same");

        TF1* fit_fun_bg = (TF1*)fit_fun->Clone("fit_fun_bg");
        fit_fun_bg->SetParameter(0, 0);
        fit_fun_bg->SetParameter(1, 0);
        fit_fun_bg->SetParameter(2, 0);
        fit_fun_bg->SetParameter(3, 0);
        fit_fun_bg->SetParameter(4, 0);
        fit_fun_bg->SetParameter(5, 0);
        fit_fun_bg->SetParameter(6, 0);
        fit_fun_bg->SetLineColor(4);
		fit_fun_bg->SetLineStyle(2);
        fit_fun_bg->Draw("same");

        TF1* fit_fun_doubleplusbkg = new TF1("fit_fun_doubleplusbkg", "gausn(0) * ([3]/0.01) * (1.0/[4]) + pol1(5)", fit_range_low, fit_range_high);
        fit_fun_doubleplusbkg->SetParameter(0, fit_fun->GetParameter(3));
        fit_fun_doubleplusbkg->SetParameter(1, fit_fun->GetParameter(4));
        fit_fun_doubleplusbkg->SetParameter(2, fit_fun->GetParameter(5));
        fit_fun_doubleplusbkg->SetParameter(3, fit_fun->GetParameter(0));
        fit_fun_doubleplusbkg->SetParameter(4, fit_fun->GetParameter(6));
        fit_fun_doubleplusbkg->SetParameter(5, fit_fun->GetParameter(7));
        fit_fun_doubleplusbkg->SetParameter(6, fit_fun->GetParameter(8));
        fit_fun_doubleplusbkg->SetLineColor(8.0);
        fit_fun_doubleplusbkg->SetLineStyle(2);
        fit_fun_doubleplusbkg->Draw("same");

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
		   float fitsigma = fit_fun->GetParameter(2);
		   int noffreepara = fit_fun->GetNumberFreeParameters();
		   int noffitpoints = fit_fun->GetNumberFitPoints();

		   cout << " fitchi2: " << fitchi2 << "   noffreepara: " << noffreepara << "  noffitpoints: " << noffitpoints << endl;

           if( !isMC )
		       sprintf( sig_print,"N_{sig}: %7.1f#pm%7.1f", Nsig, err_Nsig);
		   else
			   sprintf( sig_print,"N_{sig}: %7.5f#pm%7.5f", Nsig, err_Nsig);
		   sprintf( chi2_print, "#chi^{2}#/d.o.f: %3.2f", fitchi2/( noffitpoints - noffreepara));
		   sprintf( mean_print, "mean: %6.5f", fitmean);
		   sprintf( sigma_print, "#sigma: %6.5f", fitsigma);

		   if (fittingtry == 2)
		   {
			   TLatex Tl;
			   Tl.SetNDC();
			   Tl.SetTextAlign(12);
			   Tl.SetTextSize(0.06);
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
            p0 = fit_fun->GetParameter(0);
			p1 = fit_fun->GetParameter(1);
			p2 = fit_fun->GetParameter(2);
//            p1_L = 1.84, p2_L = 0;
//            p1_H = 1.9, p2_H = 0.05;
        }
    }


    return;


}

void FillSpectrum_doublecountedpoly1()
{
	book_hist();

	TH1D * hf_mb = new TH1D("hf_mb","hf_mb",10,-5,5);
	hf_mb->Sumw2();

//	TFile * input = new TFile("Dmesonana_hiforest_D0embedded_Hydjet1p8_2760GeV_D0pt4_pthat15305080_1119_all.root");
    TFile * input = new TFile("/home/sun229/store/Analysisfiles/Dmesonana_Rereco_MBtrig_d0pt3p0_d1p8_pt1p5_v1_tight_1213_6lumi_cuts_noprobchi2cut_vz_v4.root");
    TTree * recodmesontree = (TTree *) input->Get("recodmesontree");
    

    int MinBias;
    int MinBias_Prescl;

    int ndcand;
    int hiBin;
    double pthatweight;
    double trigweight;
    vector<int> *dtype = 0, *passingcuts = 0;
    vector<float> *dcandmass = 0, *dcandpt = 0, *dcandy = 0, *dcandphi = 0, *dcandffls3d = 0, *dcandcosalpha = 0, *dcandfprob = 0, *dcandfchi2 = 0;
    vector<float> *dcanddau1eta = 0, *dcanddau2eta = 0;

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
		   if( TMath::Abs( dcanddau1eta->at(icand) ) > 2.4 || TMath::Abs( dcanddau2eta->at(icand) ) > 2.4 )   continue;
		   
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
//   gStyle->SetHistMinimumZero(kTRUE);

   TH1D * N_mb = new TH1D("N_mb","N_mb",NPT,ptbins);
   N_mb->Sumw2();
   TCanvas* cfg_mb = new TCanvas("cfg_mb", "cfg_mb", 800, 800);
   cfg_mb->Divide(cfg_N_row, cfg_N_column);

   for ( int i = 1; i < NPT -1 ; i++)
	   fit_hist( hfg_minbias[i], cfg_mb, i, N_mb, 3.0, 55.0);
   
   char cfgname[200];
   sprintf(cfgname,"plots/D0_PbPb_data_ptbin_%d_ptd_unpreMBtrig_%d_cent%2.0fto%2.0f_doublecountedpoly1.pdf",NPT, evtunprescaleMB, hiBin_low * 0.5, hiBin_high * 0.5);
   cfg_mb->SaveAs(cfgname);
   sprintf(cfgname,"plots/D0_PbPb_data_ptbin_%d_ptd_unpreMBtrig_%d_cent%2.0fto%2.0f_doublecountedpoly1.gif",NPT, evtunprescaleMB, hiBin_low * 0.5, hiBin_high * 0.5);
   cfg_mb->SaveAs(cfgname);
  
   char outputfile[200];
   sprintf(outputfile,"rootfiles/Dspectrum_pbpb_data_ptbin_%d_ptd_unpreMBtrig_%d_cent%2.0fto%2.0f_doublecountedpoly1.root", NPT, evtunprescaleMB, hiBin_low * 0.5, hiBin_high * 0.5);
   TFile * output = new TFile(outputfile,"RECREATE");
   hf_mb->Write();
   N_mb->Write();
   cfg_mb->Write();
   write_histo( output );
}

