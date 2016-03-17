#include <iostream>
#include <TCanvas.h>
#include <TF1.h>
#include <TLatex.h>
#include <TLegend.h>
#include <TString.h>
#include <TFile.h>
#include <TH1F.h>
#include <TStyle.h>

#define NPT  14
double ptbins[NPT+1] = {0,1.5,2.5,3.5,4.5,5.5,7,9,11,13,16,20,28,40,100};
double eff_fit_range_low_expobkg_ptbin14[14] = {1.70, 1.70, 1.77, 1.75, 1.70, 1.70, 1.70, 1.70, 1.70, 1.70, 1.70, 1.70, 1.70, 1.70};
double eff_fit_range_high_expobkg_ptbin14[14] = {2.05, 2.05, 2.00, 2.00, 2.05, 2.05, 2.05, 2.05, 2.05, 2.05, 2.05, 2.05, 2.05, 2.05};

void drawhist( TH1F * histo, int iptbin, TCanvas * cfg, int ipad )
{
	cfg->cd(ipad);
	char pt_range[1000];

	double fit_range_low = eff_fit_range_low_expobkg_ptbin14[iptbin];
	double fit_range_high = eff_fit_range_high_expobkg_ptbin14[iptbin];

	float max = histo->GetMaximum();
	if( iptbin != 1 ) histo->SetMaximum(1.15 * max);
	
	float pt_low = ptbins[iptbin];
	float pt_high = ptbins[iptbin+1];
	sprintf(pt_range, "%2.1f < p_{T} < %2.1f GeV/c", pt_low, pt_high);
	histo->SetTitle(pt_range);
	histo->SetTitleFont(42,"txyz");
	histo->GetYaxis()->SetTitleOffset(1.5);
	histo->GetYaxis()->SetTitle("Entries / 10 MeV/c^{2}");
	histo->GetYaxis()->SetTitleSize(0.05);
	histo->GetXaxis()->SetTitle("m_{#piK} (GeV/c^{2})");
	histo->GetXaxis()->SetTitleSize(0.05);
	histo->GetXaxis()->SetRangeUser( fit_range_low + 0.005, fit_range_high - 0.005 );
	histo->Draw();

	TF1 * fit_fun = histo->GetFunction("fit_fun");
	fit_fun->SetLineWidth(2.0);

    //expo bkg
    TF1* fit_fun_bg = (TF1*)fit_fun->Clone("fit_fun_bg");
    for( int ipar = 0; ipar < 9; ipar++ )
        fit_fun_bg->SetParameter(ipar, 0);
    fit_fun_bg->SetLineColor(4);
    fit_fun_bg->SetLineStyle(2);
    fit_fun_bg->Draw("same");

    //misid D0 plus bkg
    TF1* fit_fun_bgplusmisid = new TF1("fit_fun_bgplusmisid", "gausn(0) * ([6]/0.01) * (1.0/[3]) + expo(4)", fit_range_low, fit_range_high);
	fit_fun_bgplusmisid->SetLineWidth(2.0);
    fit_fun_bgplusmisid->SetParameter(6, fit_fun->GetParameter(0)); //number of D0
    for( int ipar = 0; ipar < 6; ipar++ )
        fit_fun_bgplusmisid->SetParameter(ipar, fit_fun->GetParameter(ipar+5));
    fit_fun_bgplusmisid->SetLineColor(8);
    fit_fun_bgplusmisid->SetLineStyle(2);
    fit_fun_bgplusmisid->Draw("same");
	histo->Draw("same");

    char sig_print[100], chi2_print[100], mean_print[100], sigma_print[100];
    float binwidth = histo->GetBinWidth(10);
    float ptbinwidth = ptbins[iptbin+1] - ptbins[iptbin];

    float Nsig = fit_fun->GetParameter(0)/( binwidth );
    float err_Nsig = fit_fun->GetParError(0)/( binwidth );
    float fitchi2 = fit_fun->GetChisquare();
    float fitmean = fit_fun->GetParameter(1);
    float fitmeanerror = fit_fun->GetParError(1);
    float fitsigma = fit_fun->GetParameter(2) * fit_fun->GetParameter(3) + fit_fun->GetParameter(4) * ( 1.0 - fit_fun->GetParameter(3) );
    float fitsigmaerror = fit_fun->GetParError(2);
    int noffreepara = fit_fun->GetNumberFreeParameters();
    int noffitpoints = fit_fun->GetNumberFitPoints();

    cout << " fitchi2: " << fitchi2 << "   noffreepara: " << noffreepara << "  noffitpoints: " << noffitpoints << endl;

    sprintf( sig_print,"N_{sig}: %.1f #pm %.1f", Nsig, err_Nsig);
    sprintf( chi2_print, "#chi^{2}#/d.o.f: %3.2f", fitchi2/( noffitpoints - noffreepara));
    sprintf( mean_print, "#mu: %.4f #pm %.4f GeV/c^{2}", fitmean, fitmeanerror);
    sprintf( sigma_print, "#sigma: %.5f #pm %.5f", fitsigma, fitsigmaerror);
    TLatex Tl;
    Tl.SetNDC();
    Tl.SetTextAlign(12);
    Tl.SetTextSize(0.05);
    Tl.DrawLatex(0.25,0.85, mean_print);
    Tl.DrawLatex(0.25,0.75, sig_print);
//    Tl.DrawLatex(0.55,0.7, chi2_print);
//      Tl.DrawLatex(0.55,0.7, sigma_print);

	if(ipad == 1)
	{
	  cfg->cd(6);
      TLatex Tl;
      Tl.SetNDC();
      Tl.SetTextAlign(12);
      Tl.SetTextSize(0.05);
      Tl.SetTextFont(42);
      Tl.DrawLatex(0.10,0.85, "CMS Preliminary PbPb #sqrt{s_{NN}} = 2.76 TeV");
      TString centrality;
      centrality.Form("Centrality %d-%d%%", 0,100);
      cout << centrality << endl;
      Tl.DrawLatex(0.10,0.78, centrality);
      Tl.DrawLatex(0.10,0.70, "#left|y#right| < 1.0");

      TLegend* t = new TLegend(0.05, 0.1, 0.9, 0.65);
      t->SetFillColor(0);
      t->SetTextSize(0.04);
      t->AddEntry( histo, "Data");
      t->AddEntry( fit_fun, "Fit", "L");
      t->AddEntry( fit_fun_bg, "Combinatorial Bkg", "L");
      t->AddEntry( fit_fun_bgplusmisid, "Combinatorial Bkg + Misid. D^{0}", "L");
      t->Draw();

	}
}

void DrawSigextforpas()
{
    gStyle->SetOptTitle(1);
    gStyle->SetOptStat(0);
    TH1::SetDefaultSumw2();
    gStyle->SetPadRightMargin(0.05);
    gStyle->SetPadLeftMargin(0.15);
	gStyle->SetTitleX(0.1f);
	gStyle->SetTitleW(0.8f);
	gStyle->SetTitleFont(42,"t");

	TFile * input = new TFile("./Dspectrum_pbpb_data_ptbin_14_ptd_unpreMBtrig_0_cent0to100_y1.root");
	TH1F * h[NPT];

	char hname[100];

	for( int i = 0; i < NPT; i++ )
	{
		sprintf(hname, "hfg_minbias_expobkg_%d", i);
		h[i] = ( TH1F * ) input->Get(hname);
	}

	TCanvas * cfg_sigextforpas = new TCanvas("cfg_sigextforpas","cfg_sigextforpas", 900, 600);
	cfg_sigextforpas->Divide(3, 2);

	drawhist( h[2], 2, cfg_sigextforpas, 1);
	drawhist( h[5], 5, cfg_sigextforpas, 2);
	drawhist( h[8], 8, cfg_sigextforpas, 3);
	drawhist( h[11], 11, cfg_sigextforpas, 4);
	drawhist( h[12], 12, cfg_sigextforpas, 5);

	cfg_sigextforpas->SaveAs("massfitforpas/sigextforpas.pdf");
	cfg_sigextforpas->SaveAs("massfitforpas/sigextforpas.png");
}
