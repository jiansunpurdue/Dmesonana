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

#include "PtBins.h"
using namespace std;

bool evtunprescaleMB = false;   //false to fit raw counts without unprescale MB trigger
bool isMC = false;

float cut_m_low = 1.70;
float cut_m_high = 2.05;
int massbin = 35;

double eff_fit_range_low[NPT] = {1.70, 1.75, 1.75, 1.72, 1.70, 1.70, 1.70, 1.70, 1.70, 1.70, 1.70, 1.70};
double eff_fit_range_high[NPT] = {2.05, 2.05, 2.05, 2.05, 2.05, 2.05, 2.05, 2.05, 2.05, 2.05, 2.05, 2.05};
const int cfg_N_row = 3;
const int cfg_N_column = 4;

//const int cfg_N_row = 3;
//const int cfg_N_column = 2;
//double eff_fit_range_low[NPT] = {1.70, 1.75, 1.75, 1.70, 1.70, 1.70, 1.70};
//double eff_fit_range_high[NPT] = {2.05, 2.05, 2.00, 2.05, 2.05, 2.05, 2.05};
//
float hiBin_low = -0.5;
float hiBin_high = 39.5;
float rapidityrange = 2.0;

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

    double fit_range_low = eff_fit_range_low[iptbin];
    double fit_range_high = eff_fit_range_high[iptbin];

	double effmean = signalmean[iptbin];
	double effmeanerror = error_signalmean[iptbin];
	double effsigma1 = signalsigma1[iptbin];
	double effsigma1error = error_signalsigma1[iptbin];
	double effsigma2 = signalsigma2[iptbin];
	double effsigma2error = error_signalsigma2[iptbin];
	double efffraction1 = gaussian1fraction[iptbin];
	double efffraction1error = error_gaussian1fraction[iptbin];

    double effp0 = p0[iptbin];
    double effp0error = p0error[iptbin];
    double effp1 = p1[iptbin];
    double effp1error = p1error[iptbin];
    double effp2 = p2[iptbin];
    double effp2error = p2error[iptbin];
    double effNsigMC = NsigMC[iptbin];
    double effNsigMCerror = NsigMCerror[iptbin];

    histo->GetXaxis()->SetRangeUser(fit_range_low + 0.005, fit_range_high - 0.005);
//    histo->GetXaxis()->SetLimits(fit_range_low, fit_range_high);

    //.. fit with a Gaussian and pol
    TF1* fit_fun = new TF1("fit_fun", "[0]*([3]*Gaus(x,[1],[2])/(sqrt(2*3.14159)*[2])+(1-[3])*Gaus(x,[1],[4])/(sqrt(2*3.14159)*[4])) + gausn(5) * ([0]/0.01) * (1.0/[8]) + expo(9)", fit_range_low, fit_range_high);
    float max = histo->GetMaximum();
	if( hiBin_low == 99.5 || hiBin_low == 59.5 ) histo->SetMaximum(1.2 * max);
	else histo->SetMaximum(1.1 * max);
    fit_fun->SetParameter(0, 1.5 * max);
//
    fit_fun->SetParameter(1, effmean);
//    fit_fun->SetParameter(2, effsigma1);
//    fit_fun->SetParameter(4, effsigma2);
//    fit_fun->SetParameter(3, efffraction1);
//    fit_fun->SetParLimits(1, effmean - effmeanerror, effmean + effmeanerror);
//    fit_fun->SetParLimits(2, effsigma1 - effsigma1error, effsigma1 + effsigma1error);
//    fit_fun->SetParLimits(4, effsigma2 - effsigma2error, effsigma2 + effsigma2error);
//    fit_fun->SetParLimits(3, efffraction1-efffraction1error, efffraction1+efffraction1error);
//    
//    fit_fun->FixParameter(1, effmean);
    fit_fun->FixParameter(2, effsigma1);
    fit_fun->FixParameter(4, effsigma2);
    fit_fun->FixParameter(3, efffraction1);

// does not work, cannot float them, mean is OK to float
	fit_fun->SetParLimits(1, 1.855, 1.875);
//	fit_fun->SetParLimits(2, 0.01, 0.03);
//	fit_fun->SetParLimits(4, 0.015, 0.1);
//	fit_fun->SetParLimits(3, 0.0, 1.0);
//

    //gaussian as particle misid D0 function
    fit_fun->FixParameter(5, effp0);
    fit_fun->FixParameter(6, effp1);
    fit_fun->FixParameter(7, effp2);
    fit_fun->FixParameter(8, effNsigMC);
    //    fit_fun->SetParLimits(5, effp0 - effp0error, effp0 + effp0error);
    //    fit_fun->SetParLimits(6, effp1 - effp1error, effp1 + effp1error);
    //    fit_fun->SetParLimits(7, effp2 - effp2error, effp2 + effp2error);
    //    fit_fun->SetParLimits(8, NsigMC[iptbin] - NsigMCerror[iptbin], NsigMC[iptbin] + NsigMCerror[iptbin] );


	int pass = 0;
    int fittingtry = 0;

	char sig_print[100], chi2_print[100], mean_print[100], sigma_print[100];

    while (!pass) {


		histo->Fit(fit_fun,"L","", fit_range_low, fit_range_high);

        //.. draw foreground and background ..
        histo->Draw();

        // double gaussian signal
        TF1* fit_fun_1st = (TF1*)fit_fun->Clone("fit_fun_1st");
		for( int ipar = 5; ipar < 11; ipar++ )
			fit_fun_1st->SetParameter(ipar, 0);

        //expo bkg
        TF1* fit_fun_bg = (TF1*)fit_fun->Clone("fit_fun_bg");
		for( int ipar = 0; ipar < 9; ipar++ )
			fit_fun_bg->SetParameter(ipar, 0);
        fit_fun_bg->SetLineColor(4);
		fit_fun_bg->SetLineStyle(2);
        fit_fun_bg->Draw("same");

		//misid D0 plus bkg
		TF1* fit_fun_bgplusmisid = new TF1("fit_fun_bgplusmisid", "gausn(0) * ([6]/0.01) * (1.0/[3]) + expo(4)", fit_range_low, fit_range_high);
		fit_fun_bgplusmisid->SetParameter(6, fit_fun->GetParameter(0)); //number of D0
		for( int ipar = 0; ipar < 6; ipar++ )
			fit_fun_bgplusmisid->SetParameter(ipar, fit_fun->GetParameter(ipar+5));
		fit_fun_bgplusmisid->SetLineColor(8);
		fit_fun_bgplusmisid->SetLineStyle(2);
		fit_fun_bgplusmisid->Draw("same");

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
		   float fitsigma = fit_fun->GetParameter(2) * fit_fun->GetParameter(3) + fit_fun->GetParameter(4) * ( 1.0 - fit_fun->GetParameter(3) );
           float fitsigmaerror = fit_fun->GetParError(2);
		   int noffreepara = fit_fun->GetNumberFreeParameters();
		   int noffitpoints = fit_fun->GetNumberFitPoints();
           
           hfg_massmean->SetBinContent(iptbin+1, fitmean);
           hfg_massmean->SetBinError(iptbin+1, fitmeanerror);
           hfg_masssigma->SetBinContent(iptbin+1, fitsigma);
           hfg_masssigma->SetBinError(iptbin+1, fitsigmaerror);

		   cout << " fitchi2: " << fitchi2 << "   noffreepara: " << noffreepara << "  noffitpoints: " << noffitpoints << endl;
    
		   sprintf( sig_print,"N_{sig}: %.1f#pm%.1f", Nsig, err_Nsig);
		   sprintf( chi2_print, "#chi^{2}#/d.o.f: %3.2f", fitchi2/( noffitpoints - noffreepara));
		   sprintf( mean_print, "mean: %6.5f", fitmean);
		   sprintf( sigma_print, "#sigma: %6.5f", fitsigma);

		   if (fittingtry == 2)
		   {
			   TLatex Tl;
			   Tl.SetNDC();
			   Tl.SetTextAlign(12);
			   Tl.SetTextSize(0.06);
               if( NPT == 7 || NPT == 6 )    Tl.SetTextSize(0.04);
			   Tl.DrawLatex(0.15,0.8, sig_print);
			   Tl.DrawLatex(0.55,0.7, chi2_print);
			   Tl.DrawLatex(0.55,0.8, mean_print);
//			   Tl.DrawLatex(0.55,0.7, sigma_print);
		   }

		}

        if (fittingtry == 2)  
		{
			pass = 1;

		}
		
		if( pass && ( ( NPT == 12 && iptbin == 10 ) || ( NPT == 7 && iptbin == 5 ) ))
		{
		    if( NPT == 12 ) cfg->cd(11);
			if( NPT == 7 )  cfg->cd(6);
		    TLegend* t = new TLegend(0.05, 0.1, 0.9, 0.9);
		    t->SetFillColor(0);
			t->SetTextSize(0.06);
			if( NPT == 7 ) t->SetTextSize(0.04);
		    t->AddEntry( histo, "Data");
		    t->AddEntry( fit_fun, "Fit", "L");
		    t->AddEntry( fit_fun_bg, "Combinatorial Background", "L");
		    t->AddEntry( fit_fun_bgplusmisid, "Combinatorial Background + Mis Id D^{0}", "L");
		    t->Draw();
		}

    }


    return;


}

void FillSpectrum_expobkg_doublegauss_forpas()
{
	book_hist();

	TH1D * hf_mb = new TH1D("hf_mb","hf_mb",10,-5,5);
	hf_mb->Sumw2();

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
   TCanvas* cfg_mb; 
   if( NPT == 12 ) 
          cfg_mb = new TCanvas("cfg_mb", "cfg_mb", 800, 800);
   else
          cfg_mb = new TCanvas("cfg_mb", "cfg_mb", 600, 600);
   cfg_mb->Divide(cfg_N_row, cfg_N_column);

   for ( int i = 1; i < NPT -1 ; i++)
	   fit_hist( hfg_minbias[i], cfg_mb, i, N_mb, 3.0, 55.0);
//   
//   char cfgname[200];
//   sprintf(cfgname,"plots/D0_PbPb_data_ptbin_%d_ptd_unpreMBtrig_%d_cent%2.0fto%2.0f_expobkg_doublegauss.pdf",NPT, evtunprescaleMB, hiBin_low * 0.5, hiBin_high * 0.5);
//   cfg_mb->SaveAs(cfgname);
//   sprintf(cfgname,"plots/D0_PbPb_data_ptbin_%d_ptd_unpreMBtrig_%d_cent%2.0fto%2.0f_expobkg_doublegauss.gif",NPT, evtunprescaleMB, hiBin_low * 0.5, hiBin_high * 0.5);
//   cfg_mb->SaveAs(cfgname);
//  
   char outputfile[200];
   sprintf(outputfile,"rootfiles/Dspectrum_pbpb_data_ptbin_%d_ptd_unpreMBtrig_%d_cent%2.0fto%2.0f_expobkg_doublegauss_forpas.root", NPT, evtunprescaleMB, hiBin_low * 0.5, hiBin_high * 0.5);
   TFile * output = new TFile(outputfile,"RECREATE");
   hf_mb->Write();
   N_mb->Write();
   cfg_mb->Write();
   write_histo( output );
}

