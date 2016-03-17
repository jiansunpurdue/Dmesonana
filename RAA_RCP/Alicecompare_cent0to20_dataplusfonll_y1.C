# define NPTALICE 7

double syserrorPerTAAfraction = 5.6e-2;
double syserrorPerTAAfraction_alice = 5.4e-2;

void Alicecompare_cent0to20_dataplusfonll_y1()
{
    gStyle->SetOptTitle(0);
	gStyle->SetOptStat(0);

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

	TFile * inputcms = new TFile("./rootfiles/PromptRAA_D0_PbPb_spectrum_fonll_effunpre_cent0to20_ptbin12_y1_dataplusfonll.root");

	TGraphAsymmErrors * D0_fonll_raa_errorsys = ( TGraphAsymmErrors * ) inputcms->Get("D0_fonll_raa_errorsys");
	TGraphAsymmErrors * D0_fonll_raa_errorfonll = ( TGraphAsymmErrors * ) inputcms->Get("D0_fonll_raa_errorfonll");
	TGraphAsymmErrors * D0_fonll_raa_errordata = ( TGraphAsymmErrors * ) inputcms->Get("D0_fonll_raa_errordata");
	TGraphAsymmErrors * D0_fonll_raa_errordata_dataextraref = ( TGraphAsymmErrors * ) inputcms->Get("D0_fonll_raa_errordata_dataextraref");
	TGraphAsymmErrors * D0_fonll_raa_errordata_FONLLref = ( TGraphAsymmErrors * ) inputcms->Get("D0_fonll_raa_errordata_FONLLref");

	TCanvas * cfg_alice_0to20 = new TCanvas("cfg_alice_0to20","cfg_alice_0to20");

    D0_fonll_raa_errorsys->GetYaxis()->SetTitle("R*_{#kern[-0.3]{AA}} , R_{AA}");
    D0_fonll_raa_errorsys->GetXaxis()->SetRangeUser(0, 40);
	D0_fonll_raa_errorsys->Draw("A2");
	D0_fonll_raa_errorfonll->Draw("2same");
//	D0_fonll_raa_errordata->Draw("Psame");
    D0_fonll_raa_errordata_dataextraref->Draw("Psame");
	D0_fonll_raa_errordata_FONLLref->Draw("Psame");

	TGraphAsymmErrors * RAA_Alice_syserror = new TGraphAsymmErrors( NPTALICE, ptcentalice, RAAcent, pterroralice, pterroralice, RAAsyserrorlow, RAAsyserrorhigh);
	TGraphAsymmErrors * RAA_Alice_statserror = new TGraphAsymmErrors( NPTALICE, ptcentalice, RAAcent, pterroralice, pterroralice, RAAstatserror, RAAstatserror);

    RAA_Alice_syserror->SetFillStyle(0);
    RAA_Alice_syserror->SetMarkerStyle(21);
    RAA_Alice_syserror->SetLineColor(9.0);
    RAA_Alice_syserror->Draw("2same");

    RAA_Alice_statserror->SetLineWidth(0.5);
    RAA_Alice_statserror->SetMarkerStyle(21);
    RAA_Alice_statserror->SetMarkerSize(1.0);
	RAA_Alice_statserror->SetLineColor(9.0);
	RAA_Alice_statserror->SetMarkerColor(9.0);
    RAA_Alice_statserror->Draw("psame");
    
	D0_fonll_raa_errordata_dataextraref->Draw("Psame");
	D0_fonll_raa_errordata_FONLLref->Draw("Psame");

    TBox *b = new TBox(0.05,1-syserrorPerTAAfraction,1.0,1+syserrorPerTAAfraction);
    b->SetLineColor(kGray+1);
    b->SetFillColor(kGray+1);
    b->Draw();

    TBox *b_alice = new TBox(1.0,1-syserrorPerTAAfraction_alice,2.0,1+syserrorPerTAAfraction_alice);
    b_alice->SetLineColor(38.0);
    b_alice->SetFillColor(38.0);
    b_alice->Draw();

    TF1 * fun = new TF1("fun", "1.0", 0, 500);
    fun->SetLineColor(1.0);
    fun->SetLineStyle(3);
    fun->SetLineWidth(0.1);
    fun->Draw("same");
    
    TLegend *leg = new TLegend(0.16,0.67,0.45,0.85);
    leg->SetTextFont(42);
	leg->SetTextSize(0.038);
    leg->AddEntry(D0_fonll_raa_errordata, "Prompt D^{0} R*_{#kern[-0.3]{AA}}, CMS Preliminary", "PL");
	leg->AddEntry((TObject*)0, "#scale[0.8]{|y| < 1.0, Cent. 0-20%}","");
    leg->AddEntry(D0_fonll_raa_errorsys, "Syst. PbPb data","F");
    leg->AddEntry(D0_fonll_raa_errorfonll,"Err. pp reference","f");
//	leg->AddEntry(b, "Syst._{} T_{AA}+N_{MB}+BR","f");
    leg->SetBorderSize(0);
    leg->SetFillStyle(0);
    leg->Draw();

	TLegend *legalice = new TLegend(0.20,0.38,0.49,0.50);
	legalice->SetTextFont(42);
	legalice->SetTextSize(0.038);
	legalice->AddEntry( RAA_Alice_statserror, "Prompt D^{0} R_{AA}, Alice #scale[0.8]{(JHEP 09 (2012) 112)}", "PL");
	legalice->AddEntry( (TObject*)0, "#scale[0.8]{|y| < 0.5, Cent. 0-20%}","");
	legalice->AddEntry( RAA_Alice_syserror, "Syst.", "F");
//	legalice->AddEntry( b_alice, "Syst. normalization", "f");
	legalice->SetBorderSize(0);
	legalice->SetFillStyle(0);
	legalice->Draw();

    TLatex Traareference;
    Traareference.SetNDC();
    Traareference.SetTextAlign(12);
    Traareference.SetTextSize(0.03);
    Traareference.SetTextFont(42);
    Traareference.DrawLatex(0.17,0.63, "Filled markers: data-extrapolated reference");
    Traareference.DrawLatex(0.17,0.60, "Open markers: FONLL reference");

    TLatex Tl;
    Tl.SetNDC();
    Tl.SetTextAlign(12);
    Tl.SetTextSize(0.04);
    Tl.SetTextFont(42);
    Tl.DrawLatex(0.53,0.93, "PbPb #sqrt{s_{NN}} = 2.76 TeV");

	cfg_alice_0to20->RedrawAxis();


    cfg_alice_0to20->SaveAs("./results/Comparison_alice_cent0to20_dataplusfonll_y1.png");
    cfg_alice_0to20->SaveAs("./results/Comparison_alice_cent0to20_dataplusfonll_y1.pdf");

	TCanvas * cfg_alice_0to20_pt8to16 = new TCanvas("cfg_alice_0to20_pt8to16","cfg_alice_0to20_pt8to16");
    
	D0_fonll_raa_errorsys->Draw("A2");
    D0_fonll_raa_errorfonll->Draw("2same");
//  D0_fonll_raa_errordata->Draw("Psame");
    D0_fonll_raa_errordata_dataextraref->Draw("Psame");
    D0_fonll_raa_errordata_FONLLref->Draw("Psame");
    RAA_Alice_syserror->Draw("2same");
    RAA_Alice_statserror->Draw("psame");
    fun->Draw("same");
    b->Draw();
    b_alice->Draw();
    leg->Draw();


    double RAA_alice_center[6] = {0.15, 0.20, 0.25, 0.33, 0.36, 0.59};
    double RAA_alice_statistical_high[6] = {0.167, 0.23, 0.30, 0.39, 0.43, 0.72};
    double RAA_alice_unco_high[6] = {0.18, 0.24, 0.31, 0.39, 0.44, 0.73};
    double RAA_alice_unco_low[6] = {0.122, 0.16, 0.20, 0.26, 0.28, 0.45};
    double RAA_alice_co_high[6] = {0.18, 0.23, 0.29, 0.37, 0.41, 0.67};

    double error_RAA_alice_statistical[6];
    double error_RAA_alice_unco_high[6];
    double error_RAA_alice_unco_low[6];
    double error_RAA_alice_co[6];

    for( int i = 0; i < 6; i++ )
    {
        error_RAA_alice_statistical[i] = RAA_alice_statistical_high[i] - RAA_alice_center[i];
        error_RAA_alice_unco_high[i] = RAA_alice_unco_high[i] - RAA_alice_center[i];
        error_RAA_alice_unco_low[i] = RAA_alice_center[i] - RAA_alice_unco_low[i];
        error_RAA_alice_co[i] = RAA_alice_co_high[i] - RAA_alice_center[i];
    }

    double pt_alice_center[1] = {12.0};
    double pt_error_alice[1] = {4.0};

	double RAA_alice_cent0to10[1] = {RAA_alice_center[0]};
	double error_RAA_alice_statistical_cent0to10[1] = {error_RAA_alice_statistical[0]};
	
	double RAA_alice_cent0to20[1] = {RAA_alice_center[1]};
	double error_RAA_alice_statistical_cent0to20[1] = {error_RAA_alice_statistical[1]};

    TGraphAsymmErrors * RAA_D0_alice_pt8to16_errordata_cent0to10 = new TGraphAsymmErrors( 1, pt_alice_center, RAA_alice_cent0to10, pt_error_alice, pt_error_alice, error_RAA_alice_statistical_cent0to10, error_RAA_alice_statistical_cent0to10);

    RAA_D0_alice_pt8to16_errordata_cent0to10->SetFillStyle(1001);
    RAA_D0_alice_pt8to16_errordata_cent0to10->SetFillColor(kGreen-9);
    RAA_D0_alice_pt8to16_errordata_cent0to10->SetLineColor(kGreen-9);
    RAA_D0_alice_pt8to16_errordata_cent0to10->SetMarkerStyle(21);
    RAA_D0_alice_pt8to16_errordata_cent0to10->SetMarkerSize(1.0);
    RAA_D0_alice_pt8to16_errordata_cent0to10->SetLineColor(kGreen);
    RAA_D0_alice_pt8to16_errordata_cent0to10->SetMarkerColor(kGreen);
    RAA_D0_alice_pt8to16_errordata_cent0to10->Draw("P");

    TGraphAsymmErrors * RAA_D0_alice_pt8to16_errordata_cent0to20 = new TGraphAsymmErrors( 1, pt_alice_center, RAA_alice_cent0to20, pt_error_alice, pt_error_alice, error_RAA_alice_statistical_cent0to20, error_RAA_alice_statistical_cent0to20);

    RAA_D0_alice_pt8to16_errordata_cent0to20->SetFillStyle(1001);
    RAA_D0_alice_pt8to16_errordata_cent0to20->SetFillColor(kGreen-9);
    RAA_D0_alice_pt8to16_errordata_cent0to20->SetLineColor(kGreen-9);
    RAA_D0_alice_pt8to16_errordata_cent0to20->SetMarkerStyle(21);
    RAA_D0_alice_pt8to16_errordata_cent0to20->SetMarkerSize(1.0);
    RAA_D0_alice_pt8to16_errordata_cent0to20->SetLineColor(kGreen);
    RAA_D0_alice_pt8to16_errordata_cent0to20->SetMarkerColor(kGreen);
    RAA_D0_alice_pt8to16_errordata_cent0to20->Draw("P");

    cfg_alice_0to20_pt8to16->RedrawAxis();

    cfg_alice_0to20_pt8to16->SaveAs("./results/Comparison_alice_cent0to20_dataplusfonll_y1_pt8to16.png");
    cfg_alice_0to20_pt8to16->SaveAs("./results/Comparison_alice_cent0to20_dataplusfonll_y1_pt8to16.pdf");


}
