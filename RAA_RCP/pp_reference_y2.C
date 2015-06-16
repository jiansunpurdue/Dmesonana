void pp_reference_y2()
{
    gStyle->SetOptTitle(0);
    gStyle->SetOptStat(0);

	TFile * input_GM_FVNS = new TFile("D0_prediction_GM_FVNS_y2.root");

	TGraphAsymmErrors* gaeSigmaDzero_GM_FVNS_ptbin10 = ( TGraphAsymmErrors* ) input_GM_FVNS->Get("gaeSigmaDzero_GM_FVNS_ptbin10");

	TFile * input_FONLL = new TFile("./../FONLL/fonll/outputDzero.root");

	TGraphAsymmErrors* gaeSigmaDzero_FONLL_ptbin10 = ( TGraphAsymmErrors* ) input_FONLL->Get("gaeSigmaDzero");

	TCanvas * cfg_pp_ptbin10 = new TCanvas("cfg_pp_ptbin10","cfg_pp_ptbin10", 450, 600);
    TPad *pad1 = new TPad("pad1","top pad",0.0,0.3,1.0,1.0);
    pad1->Draw();
    TPad *pad2 = new TPad("pad2","bottom pad",0.0,0.0,1.0,0.3);
    pad2->Draw();

    pad1->cd();
    gPad->SetLogy();

	gaeSigmaDzero_GM_FVNS_ptbin10->Draw("ap");
    gaeSigmaDzero_FONLL_ptbin10->SetLineColor(1.0);
    gaeSigmaDzero_FONLL_ptbin10->SetMarkerSize(1.0);
    gaeSigmaDzero_FONLL_ptbin10->SetMarkerStyle(21);
    gaeSigmaDzero_FONLL_ptbin10->SetMarkerColor(1.0);
	gaeSigmaDzero_FONLL_ptbin10->SetLineWidth(0.5);
	gaeSigmaDzero_FONLL_ptbin10->GetXaxis()->SetRangeUser(3.5, 40);
	gaeSigmaDzero_FONLL_ptbin10->Draw("psame");

    TLegend * t = new TLegend(0.45, 0.75, 0.85, 0.85);
    t->SetFillColor(0);
	t->AddEntry( gaeSigmaDzero_FONLL_ptbin10, "FONLL", "p");
	t->AddEntry( gaeSigmaDzero_GM_FVNS_ptbin10, "GM-VFNS", "p");
	t->Draw();


	pad2->cd();

	TGraphAsymmErrors* ratio_central_GM_FVNS_FONLL = ( TGraphAsymmErrors* ) gaeSigmaDzero_GM_FVNS_ptbin10->Clone("ratio_central_GM_FVNS_FONLL");
	ratio_central_GM_FVNS_FONLL->SetName("ratio_central_GM_FVNS_FONLL");
	ratio_central_GM_FVNS_FONLL->SetTitle("ratio_central_GM_FVNS_FONLL");

	for( int ipt = 0; ipt < ratio_central_GM_FVNS_FONLL->GetN(); ipt++ )
	{
		ratio_central_GM_FVNS_FONLL->GetY()[ipt] = gaeSigmaDzero_GM_FVNS_ptbin10->GetY()[ipt]/gaeSigmaDzero_FONLL_ptbin10->GetY()[ipt];
		ratio_central_GM_FVNS_FONLL->SetPointEYhigh(ipt, 0);
		ratio_central_GM_FVNS_FONLL->SetPointEYlow(ipt, 0);
	}

	ratio_central_GM_FVNS_FONLL->GetYaxis()->SetTitle("Ratio");
	ratio_central_GM_FVNS_FONLL->GetYaxis()->SetRangeUser(0.5, 3);
	ratio_central_GM_FVNS_FONLL->GetYaxis()->SetTitleOffset(0.6);
	ratio_central_GM_FVNS_FONLL->GetYaxis()->SetTitleSize(0.10);
	ratio_central_GM_FVNS_FONLL->GetYaxis()->SetLabelSize(0.10);
	ratio_central_GM_FVNS_FONLL->Draw("ap");
    
	TLegend * t1 = new TLegend(0.20, 0.75, 0.5, 0.85);
    t1->SetFillColor(0);
	t1->SetTextSize(0.08);
	t1->AddEntry( ratio_central_GM_FVNS_FONLL, "GM-VFNS Central / FONLL Central", "p");
	t1->Draw();

	cfg_pp_ptbin10->SaveAs("ppreference/D0_prompt_FONLL_GM_FVNS_ratio_ptbin10.png");
	cfg_pp_ptbin10->SaveAs("ppreference/D0_prompt_FONLL_GM_FVNS_ratio_ptbin10.pdf");

	TCanvas * cfg_theory_uncertainty = new TCanvas("cfg_theory_uncertainty","cfg_theory_uncertainty", 350, 600);
	cfg_theory_uncertainty->Divide(1,2);

	cfg_theory_uncertainty->cd(1);
	
	TGraphAsymmErrors* theory_peruncertainty_FONLL = ( TGraphAsymmErrors* ) gaeSigmaDzero_FONLL_ptbin10->Clone("theory_peruncertainty_FONLL");
	theory_peruncertainty_FONLL->SetName("theory_peruncertainty_FONLL");
	theory_peruncertainty_FONLL->SetTitle("theory_peruncertainty_FONLL");

	for( int ipt = 0; ipt < theory_peruncertainty_FONLL->GetN(); ipt++ )
	{
		theory_peruncertainty_FONLL->GetY()[ipt] = gaeSigmaDzero_FONLL_ptbin10->GetY()[ipt]/gaeSigmaDzero_FONLL_ptbin10->GetY()[ipt];
		theory_peruncertainty_FONLL->SetPointEYhigh(ipt, gaeSigmaDzero_FONLL_ptbin10->GetErrorYhigh(ipt)/gaeSigmaDzero_FONLL_ptbin10->GetY()[ipt]);
		theory_peruncertainty_FONLL->SetPointEYlow(ipt, gaeSigmaDzero_FONLL_ptbin10->GetErrorYlow(ipt)/gaeSigmaDzero_FONLL_ptbin10->GetY()[ipt]);
	}

	theory_peruncertainty_FONLL->GetYaxis()->SetTitle("FONLL Relative Error");
	theory_peruncertainty_FONLL->GetYaxis()->SetRangeUser(0., 2);
	theory_peruncertainty_FONLL->Draw("ap");

	cfg_theory_uncertainty->cd(2);
	
	TGraphAsymmErrors* theory_peruncertainty_GM_FVNS = ( TGraphAsymmErrors* ) gaeSigmaDzero_GM_FVNS_ptbin10->Clone("theory_peruncertainty_GM_FVNS");
	theory_peruncertainty_GM_FVNS->SetName("theory_peruncertainty_GM_FVNS");
	theory_peruncertainty_GM_FVNS->SetTitle("theory_peruncertainty_GM_FVNS");

	for( int ipt = 0; ipt < theory_peruncertainty_GM_FVNS->GetN(); ipt++ )
	{
		theory_peruncertainty_GM_FVNS->GetY()[ipt] = gaeSigmaDzero_GM_FVNS_ptbin10->GetY()[ipt]/gaeSigmaDzero_GM_FVNS_ptbin10->GetY()[ipt];
		theory_peruncertainty_GM_FVNS->SetPointEYhigh(ipt, gaeSigmaDzero_GM_FVNS_ptbin10->GetErrorYhigh(ipt)/gaeSigmaDzero_GM_FVNS_ptbin10->GetY()[ipt]);
		theory_peruncertainty_GM_FVNS->SetPointEYlow(ipt, gaeSigmaDzero_GM_FVNS_ptbin10->GetErrorYlow(ipt)/gaeSigmaDzero_GM_FVNS_ptbin10->GetY()[ipt]);
	}

	theory_peruncertainty_GM_FVNS->GetYaxis()->SetTitle("GM-VFNS Relative Error");
	theory_peruncertainty_GM_FVNS->GetYaxis()->SetRangeUser(0., 2);
	theory_peruncertainty_GM_FVNS->Draw("ap");
	
	cfg_theory_uncertainty->SaveAs("ppreference/D0_prompt_theory_uncertainty_FONLL_GM_FVNS_ptbin10.png");
	cfg_theory_uncertainty->SaveAs("ppreference/D0_prompt_theory_uncertainty_FONLL_GM_FVNS_ptbin10.pdf");
    
}
