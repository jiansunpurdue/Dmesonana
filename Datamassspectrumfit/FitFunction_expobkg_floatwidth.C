extern int rapidityrange;

double eff_fit_range_low_expobkg_floatwidth_ptbin12[12] = {1.70, 1.77, 1.75, 1.72, 1.70, 1.70, 1.70, 1.70, 1.70, 1.70, 1.70, 1.70};
double eff_fit_range_high_expobkg_floatwidth_ptbin12[12] = {2.05, 1.95, 2.05, 2.05, 2.05, 2.05, 2.05, 2.05, 2.05, 2.05, 2.05, 2.05};

double eff_fit_range_low_expobkg_floatwidth_ptbin7[7] = {1.70, 1.77, 1.75, 1.70, 1.70, 1.70, 1.70};
double eff_fit_range_high_expobkg_floatwidth_ptbin7[7] = {2.05, 1.95, 2.00, 2.05, 2.05, 2.05, 2.05};


double eff_fit_range_low_expobkg_floatwidth_ptbin14[14] = {1.70, 1.70, 1.77, 1.75, 1.70, 1.70, 1.70, 1.70, 1.70, 1.70, 1.70, 1.70, 1.70, 1.70};
double eff_fit_range_high_expobkg_floatwidth_ptbin14[14] = {2.05, 2.05, 2.00, 2.00, 2.05, 2.05, 2.05, 2.05, 2.05, 2.05, 2.05, 2.05, 2.05, 2.05};

double eff_fit_range_low_expobkg_floatwidth_ptbin9[9] = {1.70, 1.70, 1.77, 1.75, 1.70, 1.70, 1.70, 1.70, 1.70};
double eff_fit_range_high_expobkg_floatwidth_ptbin9[9] = {2.05, 2.05, 2.00, 2.00, 2.05, 2.05, 2.05, 2.05, 2.05};

void fit_hist_expobkg_floatwidth( TH1F * histo, TCanvas *cfg, int iptbin , TH1D * rawdNdpt, TH1F * hfg_massmean, TH1F * hfg_masssigma, int cent_low, int cent_high, TH1F * hfg_fitalpha)
{
    double *eff_fit_range_low_expobkg_floatwidth = new double[NPT];
    double *eff_fit_range_high_expobkg_floatwidth = new double[NPT];

    for( int ibin = 0; ibin < NPT; ibin++ )
    {
        eff_fit_range_low_expobkg_floatwidth[ibin] = 1.70;
        eff_fit_range_high_expobkg_floatwidth[ibin] = 2.05;
    }

	if( NPT == 12 )
	{
		for( int ibin = 0; ibin < NPT; ibin++ )
		{
			eff_fit_range_low_expobkg_floatwidth[ibin] = eff_fit_range_low_expobkg_floatwidth_ptbin12[ibin];
			eff_fit_range_high_expobkg_floatwidth[ibin] = eff_fit_range_high_expobkg_floatwidth_ptbin12[ibin];
		}
	}
	else if ( NPT == 7 )
	{
		for( int ibin = 0; ibin < NPT; ibin++ )
		{
			eff_fit_range_low_expobkg_floatwidth[ibin] = eff_fit_range_low_expobkg_floatwidth_ptbin7[ibin];
			eff_fit_range_high_expobkg_floatwidth[ibin] = eff_fit_range_high_expobkg_floatwidth_ptbin7[ibin];
		}
	}
    else if ( NPT == 14 )
    {
        for( int ibin = 0; ibin < NPT; ibin++ )
        {
            eff_fit_range_low_expobkg_floatwidth[ibin] = eff_fit_range_low_expobkg_floatwidth_ptbin14[ibin];
            eff_fit_range_high_expobkg_floatwidth[ibin] = eff_fit_range_high_expobkg_floatwidth_ptbin14[ibin];
        }
    }
    else if ( NPT == 9 )
    {
        for( int ibin = 0; ibin < NPT; ibin++ )
        {
            eff_fit_range_low_expobkg_floatwidth[ibin] = eff_fit_range_low_expobkg_floatwidth_ptbin9[ibin];
            eff_fit_range_high_expobkg_floatwidth[ibin] = eff_fit_range_high_expobkg_floatwidth_ptbin9[ibin];
        }
    }

	ROOT::Math::MinimizerOptions::SetDefaultMaxFunctionCalls(100000); 
	cfg->cd(iptbin);

    TPad *pad1 = new TPad("pad1","top pad",0.0,0.3,1.0,1.0);
    pad1->SetTopMargin(0.10);
    pad1->SetBottomMargin(0.01);
    if( NPT == 7 )
    {
        pad1->SetLeftMargin(0.20);
        pad1->SetRightMargin(0.05);
    }
    pad1->Draw();
    TPad *pad2 = new TPad("pad2","bottom pad",0.0,0.0,1.0,0.3);
    pad2->SetTopMargin(0.0);
    pad2->SetBottomMargin(0.40);
    if( NPT == 7 )
    {
        pad2->SetLeftMargin(0.20);
        pad2->SetRightMargin(0.05);
    }
    pad2->Draw();

	pad1->cd();

	cout << "/////////////////////////////////////********        i             **************         " << iptbin << endl;
	histo->SetMarkerSize(0.8);
	histo->SetLineColor(2);
	histo->SetMarkerColor(2);
	histo->SetMarkerStyle(20);
	histo->SetTitleSize(0.06,"t");
	histo->GetYaxis()->CenterTitle();
	histo->GetXaxis()->SetNdivisions(505);
	histo->GetXaxis()->SetTitle("m_{#piK} (GeV/c^{2})");
	histo->GetXaxis()->SetTitleOffset(1.0);
	histo->GetXaxis()->SetTitleSize(0.06);
	histo->GetYaxis()->SetTitleOffset(1.0);
    if( NPT == 7 ) histo->GetYaxis()->SetTitleOffset(1.5);
	histo->GetYaxis()->SetTitleSize(0.06);
	histo->GetYaxis()->SetTitle("Entries / 10 MeV/c^{2}");

	double fit_range_low = eff_fit_range_low_expobkg_floatwidth[iptbin];
	double fit_range_high = eff_fit_range_high_expobkg_floatwidth[iptbin];

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

	//.. fit with a Gaussian and pol
	TF1* fit_fun = new TF1("fit_fun", "[0]*([3]*Gaus(x,[1],[2]*(1.0+[11]))/(sqrt(2*3.14159)*[2]*(1.0+[11]))+(1-[3])*Gaus(x,[1],[4]*(1.0+[11]))/(sqrt(2*3.14159)*[4]*(1.0+[11]))) + gausn(5) * ([0]/0.01) * (1.0/[8]) + expo(9)", fit_range_low, fit_range_high);
	fit_fun->SetLineColor(1.0);
	//	fit_fun->SetLineWidth(2.0);

	float max = histo->GetMaximum();
	histo->SetMaximum(1.15 * max);
	fit_fun->SetParameter(0, 1.5 * max);
	fit_fun->SetParameter(9, 3.0);
	fit_fun->SetParameter(10, -1.5);
	//
	fit_fun->SetParameter(1, effmean);
	fit_fun->FixParameter(2, effsigma1);
	fit_fun->FixParameter(4, effsigma2);
	fit_fun->FixParameter(3, efffraction1);

	//mean is OK to float
	fit_fun->SetParLimits(1, 1.855, 1.875);
	
    fit_fun->SetParameter(11, 0.10);
    fit_fun->SetParLimits(11, -1.0, 0.8);
	if( rapidityrange == 2 )  fit_fun->SetParLimits(11, -1.0, 0.8);

	//gaussian as particle misid D0 function
	fit_fun->FixParameter(5, effp0);
	fit_fun->FixParameter(6, effp1);
	fit_fun->FixParameter(7, effp2);
	fit_fun->FixParameter(8, effNsigMC);

	int pass = 0;
	int fittingtry = 0;

	char sig_print[100], chi2_print[100], mean_print[100], sigma_print[100], alpha_print[100];

	while (!pass) {

		histo->Fit(fit_fun,"L","", fit_range_low, fit_range_high);
		fittingtry++;

		if (fittingtry == 3)  
		{
			pass = 1;

		}

	}
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


	float binwidth = histo->GetBinWidth(10);
	float ptbinwidth = ptbins[iptbin+1] - ptbins[iptbin];
	rawdNdpt->SetBinContent( iptbin+1, fit_fun->GetParameter(0)/( binwidth * ptbinwidth ));
	rawdNdpt->SetBinError( iptbin+1, fit_fun->GetParError(0)/( binwidth * ptbinwidth ));

	float Nsig = fit_fun->GetParameter(0)/( binwidth );
	float err_Nsig = fit_fun->GetParError(0)/( binwidth );
	float fitchi2 = fit_fun->GetChisquare();
	float fitmean = fit_fun->GetParameter(1);
	float fitmeanerror = fit_fun->GetParError(1);
    float fitsigma = fit_fun->GetParameter(2) * fit_fun->GetParameter(3) * (1.0 + fit_fun->GetParameter(11) ) + fit_fun->GetParameter(4) * ( 1.0 - fit_fun->GetParameter(3) ) * (1.0 + fit_fun->GetParameter(11) );
    float fitsigmaerror = fit_fun->GetParError(2)  * fit_fun->GetParameter(3) * (1.0 + fit_fun->GetParameter(11) ) + fit_fun->GetParError(4) * ( 1.0 - fit_fun->GetParameter(3) ) * (1.0 + fit_fun->GetParameter(11) );
    float fitalpha = fit_fun->GetParameter(11);
    float fitalphaerror = fit_fun->GetParError(11);
	int noffreepara = fit_fun->GetNumberFreeParameters();
	int noffitpoints = fit_fun->GetNumberFitPoints();

	hfg_massmean->SetBinContent(iptbin+1, fitmean);
	hfg_massmean->SetBinError(iptbin+1, fitmeanerror);
	hfg_masssigma->SetBinContent(iptbin+1, fitsigma);
	hfg_masssigma->SetBinError(iptbin+1, fitsigmaerror);
    hfg_fitalpha->SetBinContent(iptbin+1, fitalpha);
    hfg_fitalpha->SetBinError(iptbin+1, fitalphaerror);

	cout << " fitchi2: " << fitchi2 << "   noffreepara: " << noffreepara << "  noffitpoints: " << noffitpoints << endl;

	sprintf( sig_print,"N_{sig}: %.1f#pm%.1f", Nsig, err_Nsig);
	sprintf( chi2_print, "#chi^{2}#/d.o.f: %3.2f", fitchi2/( noffitpoints - noffreepara));
	sprintf( mean_print, "mean: %.4f#pm%.4f GeV/c^{2}", fitmean, fitmeanerror);
	sprintf( sigma_print, "#sigma: %6.5f", fitsigma);
    sprintf( alpha_print, "#alpha: %.3f#pm%.3f", fitalpha,fitalphaerror);

	TLatex Tl;
	Tl.SetNDC();
	Tl.SetTextAlign(12);
	Tl.SetTextSize(0.06);


    if( NPT == 3 )
    {
        Tl.SetTextSize(0.04);
        Tl.DrawLatex(0.17,0.8, mean_print);
        Tl.DrawLatex(0.17,0.7, sig_print);
    }

    if( NPT == 7 || NPT == 6 )
    {
        Tl.SetTextSize(0.04);
        Tl.DrawLatex(0.25,0.8, mean_print);
        Tl.DrawLatex(0.25,0.7, sig_print);
        Tl.DrawLatex(0.65,0.7, alpha_print);
    }

    if( NPT >= 9 )
    {
        Tl.DrawLatex(0.15,0.8, mean_print);
        Tl.DrawLatex(0.15,0.65, sig_print);
        Tl.DrawLatex(0.55,0.65, alpha_print);
    }

	if(  ( NPT == 12 && iptbin == 10 ) || ( NPT == 7 && iptbin == 5 ) || ( NPT == 9 && iptbin == 7 ) )
	{
		if( NPT == 12 ) cfg->cd(11);
		if( NPT == 7 )  cfg->cd(6);
		if( NPT == 9 )  cfg->cd(8);

		TLatex T2;
		T2.SetNDC();
		T2.SetTextAlign(12);
		T2.SetTextSize(0.06);
		T2.SetTextFont(62);
		T2.DrawLatex(0.10,0.90, "CMS Preliminary #sqrt{s_{NN}} = 2.76 TeV");
        TString rapiditydrawn;
        rapiditydrawn.Form("#left|y#right| < %d.0", rapidityrange);
        T2.DrawLatex(0.10,0.80, rapiditydrawn);
		TString centrality;
		centrality.Form("Centrality %d-%d%%", cent_low, cent_high);
		cout << centrality << endl;
		T2.DrawLatex(0.10,0.70, centrality);

		TLegend* t = new TLegend(0.05, 0.2, 0.9, 0.65);
		t->SetFillColor(0);
		t->SetTextSize(0.04);
		if( NPT == 7 ) t->SetTextSize(0.04);
		t->AddEntry( histo, "Data");
		t->AddEntry( fit_fun, "Fit", "L");
		t->AddEntry( fit_fun_bg, "Combinatorial Background", "L");
		t->AddEntry( fit_fun_bgplusmisid, "Combinatorial Background + Misid D^{0}", "L");
		t->Draw();
	}


	pad2->cd();

    TH1F * pull_histo = ( TH1F * ) histo->Clone("pull_histo");
    pull_histo->GetFunction("fit_fun")->Delete();

    for( int ibin = 1; ibin < pull_histo->GetNbinsX()+1; ibin++ )
    {
        pull_histo->SetBinError(ibin, 0);
        pull_histo->SetBinContent( ibin, -10);
        if( histo->GetBinError(ibin) != 0 )
             pull_histo->SetBinContent( ibin, ( histo->GetBinContent( ibin ) -  fit_fun->Eval( histo->GetBinCenter(ibin) )) / histo->GetBinError(ibin) );
    }

	pull_histo->SetTitle(0);
	pull_histo->GetYaxis()->SetRangeUser( -4.0, 4.0 );
	pull_histo->GetYaxis()->SetTitleOffset(0.4);
	pull_histo->GetYaxis()->SetLabelSize(0.10);
	pull_histo->GetYaxis()->SetTitleSize(0.15);
    if( NPT == 7 )
    {
        pull_histo->GetYaxis()->SetTitleOffset(0.5);
        pull_histo->GetYaxis()->SetTitleSize(0.15);
    }
	pull_histo->GetYaxis()->SetTitle("Pull");
	pull_histo->GetYaxis()->SetNdivisions(108);
	pull_histo->GetXaxis()->SetLabelSize(0.15);
	pull_histo->GetXaxis()->SetTitleSize(0.15);
	if( NPT == 7 ) pull_histo->GetXaxis()->SetLabelSize(0.10);
    pull_histo->GetXaxis()->SetTitleOffset(1.2);
	pull_histo->Draw("ep");

	TLatex T2;
	T2.SetNDC();
	T2.SetTextAlign(12);
	T2.SetTextSize(0.12);
	T2.DrawLatex(0.65,0.85, chi2_print);

	TF1 * fun = new TF1("fun", "0.0", 0, 500);
	fun->SetLineColor(1.0);
	fun->SetLineStyle(2);
	fun->SetLineWidth(0.2);
	fun->Draw("same");

	return;
}

