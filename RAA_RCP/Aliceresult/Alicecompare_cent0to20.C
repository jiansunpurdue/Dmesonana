# define NPTALICE 7

double syserrorPerTAAfraction = 4.7e-2;
double syserrorPerTAAfraction_alice = 5.4e-2;

void Alicecompare_cent0to20()
{
	double ptcentalice[NPTALICE] = { 2.5, 3.5, 4.5, 5.5, 7.0, 10.0, 14.0};
	double pterroralice[NPTALICE] = { 0.5, 0.5, 0.5, 0.5, 1.0, 2.0, 2.0 };
	double RAAcent[NPTALICE] = { 0.515, 0.372, 0.332, 0.276, 0.255, 0.266, 0.304};
	double RAAplusstats[NPTALICE] = { 0.614, 0.436, 0.384, 0.348, 0.303, 0.310, 0.415};
	double RAAsyshigh[NPTALICE] = { 0.764, 0.511, 0.439, 0.359, 0.342, 0.351, 0.430};
	double RAAsyslow[NPTALICE] = { 0.353, 0.262, 0.222,  0.177, 0.145, 0.160, 0.126};

	double RAAstatserror[NPTALICE], RAAsyserrorhigh[NPTALICE], RAAsyserrorlow[NPTALICE];

	for( int i = 0; i < NPTALICE; i++ )
	{
		RAAstatserror[i] = RAAplusstats[i] - RAAcent[i];
		RAAsyserrorhigh[i] = RAAsyshigh[i] - RAAcent[i];
		RAAsyserrorlow[i] = RAAcent[i] - RAAsyslow[i];
	}

	TFile * inputcms = new TFile("./../PromptRAA_D0_PbPb_spectrum_fonll_effunpre_cent0to20_ptbin9.root");

	TGraphAsymmErrors * D0_fonll_raa_errorsys = ( TGraphAsymmErrors * ) inputcms->Get("D0_fonll_raa_errorsys");
	TGraphAsymmErrors * D0_fonll_raa_errorfonll = ( TGraphAsymmErrors * ) inputcms->Get("D0_fonll_raa_errorfonll");
	TGraphAsymmErrors * D0_fonll_raa_errordata = ( TGraphAsymmErrors * ) inputcms->Get("D0_fonll_raa_errordata");

	TCanvas * cfg_alice_0to20 = new TCanvas("cfg_alice_0to20","cfg_alice_0to20");

    D0_fonll_raa_errorsys->GetYaxis()->SetTitle("Prompt D^{0} R_{AA}");
    D0_fonll_raa_errorsys->GetXaxis()->SetRangeUser(0, 28);
	D0_fonll_raa_errorsys->Draw("A2");
	D0_fonll_raa_errorfonll->Draw("2same");
	D0_fonll_raa_errordata->Draw("Psame");

	TGraphAsymmErrors * RAA_Alice_syserror = new TGraphAsymmErrors( NPTALICE, ptcentalice, RAAcent, pterroralice, pterroralice, RAAsyserrorlow, RAAsyserrorhigh);
	TGraphAsymmErrors * RAA_Alice_statserror = new TGraphAsymmErrors( NPTALICE, ptcentalice, RAAcent, pterroralice, pterroralice, RAAstatserror, RAAstatserror);

    RAA_Alice_syserror->SetFillStyle(0);
    RAA_Alice_syserror->SetMarkerStyle(21);
    RAA_Alice_syserror->SetLineColor(2.0);
    RAA_Alice_syserror->Draw("2same");

    RAA_Alice_statserror->SetLineWidth(0.5);
    RAA_Alice_statserror->SetMarkerStyle(21);
    RAA_Alice_statserror->SetMarkerSize(1.0);
	RAA_Alice_statserror->SetLineColor(2.0);
	RAA_Alice_statserror->SetMarkerColor(2.0);
    RAA_Alice_statserror->Draw("psame");

    TF1 * fun = new TF1("fun", "1.0", 0, 500);
    fun->SetLineColor(1.0);
    fun->SetLineStyle(3);
    fun->SetLineWidth(0.1);
    fun->Draw("same");

    TBox *b = new TBox(0.0,1-syserrorPerTAAfraction,1.0,1+syserrorPerTAAfraction);
    b->SetLineColor(kGray);
    b->SetFillColor(kGray);
    b->Draw();

    TBox *b_alice = new TBox(1.0,1-syserrorPerTAAfraction_alice,2.0,1+syserrorPerTAAfraction_alice);
    b_alice->SetLineColor(30);
    b_alice->SetFillColor(30);
    b_alice->Draw();

    
    TLegend *leg = new TLegend(0.15,0.55,0.85,0.8);
    leg->SetTextFont(62);
    leg->AddEntry(D0_fonll_raa_errordata,"CMS Preliminary R^{FONLL}_{AA}, #left|y#right| < 2.0, Centrality 0-20%","PLf");
    leg->AddEntry(b, "Syst. TAA+BR, CMS","f");
	leg->AddEntry( RAA_Alice_statserror, "Alice Published R_{AA}, #left|y#right| < 0.5, Centrality 0-20%","PL");
	leg->AddEntry(b_alice, "Syst. TAA+BR, Alice","f");
    leg->SetBorderSize(0);
    leg->SetFillStyle(0);
    leg->Draw();

    cfg_alice_0to20->SaveAs("./alicecomparison/Comparison_alice_cent0to20.png");
    cfg_alice_0to20->SaveAs("./alicecomparison/Comparison_alice_cent0to20.pdf");

}
