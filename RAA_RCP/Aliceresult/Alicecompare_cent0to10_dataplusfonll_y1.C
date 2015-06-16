# define NPTALICE 10

double syserrorPerTAAfraction = 4.5e-2;
double syserrorPerTAAfraction_alice = 5.1e-2;

bool removelastpoint = false;

void Alicecompare_cent0to10_dataplusfonll_y1()
{   
    gStyle->SetOptTitle(0);
    gStyle->SetOptStat(0);

	double ptcentalice[NPTALICE] = {1.5, 2.5, 3.5, 4.5, 5.5, 7.0, 10.0, 14.0, 20, 30};
	double pterroralice[NPTALICE] = { 0.5, 0.5, 0.5, 0.5, 0.5, 1.0, 2.0, 2.0, 4.0, 6.0};
	double RAAcent[NPTALICE] = { 0.522, 0.542, 0.375, 0.241, 0.220, 0.188, 0.159, 0.224, 0.253, 0.383};
	double RAAplusstats[NPTALICE] = { 0.689, 0.603, 0.412, 0.269, 0.245, 0.204, 0.184, 0.281, 0.302, 0.473};
	double RAAsyshigh[NPTALICE] = { 0.701, 0.705, 0.485, 0.306, 0.277, 0.241, 0.212, 0.290, 0.391, 0.542};
	double RAAsyslow[NPTALICE] = { 0.277, 0.314, 0.257, 0.172, 0.159, 0.135, 0.119, 0.139, 0.094, 0.151};

	double RAAstatserror[NPTALICE], RAAsyserrorhigh[NPTALICE], RAAsyserrorlow[NPTALICE];

	for( int i = 0; i < NPTALICE; i++ )
	{
		RAAstatserror[i] = RAAplusstats[i] - RAAcent[i];
		RAAsyserrorhigh[i] = RAAsyshigh[i] - RAAcent[i];
		RAAsyserrorlow[i] = RAAcent[i] - RAAsyslow[i];
	}

	if ( removelastpoint ) RAAcent[NPTALICE-1] = -999;

	TFile * inputcms = new TFile("./../rootfiles/PromptRAA_D0_PbPb_spectrum_fonll_effunpre_cent0to10_ptbin11_y1_dataplusfonll.root");

	TGraphAsymmErrors * D0_fonll_raa_errorsys = ( TGraphAsymmErrors * ) inputcms->Get("D0_fonll_raa_errorsys");
	TGraphAsymmErrors * D0_fonll_raa_errorfonll = ( TGraphAsymmErrors * ) inputcms->Get("D0_fonll_raa_errorfonll");
	TGraphAsymmErrors * D0_fonll_raa_errordata = ( TGraphAsymmErrors * ) inputcms->Get("D0_fonll_raa_errordata");

	TCanvas * cfg_alice_0to20 = new TCanvas("cfg_alice_0to20","cfg_alice_0to20");

    D0_fonll_raa_errorsys->GetYaxis()->SetTitle("Prompt D^{0} R_{AA}");
    D0_fonll_raa_errorsys->GetXaxis()->SetRangeUser(0, 36);
	if( removelastpoint ) D0_fonll_raa_errorsys->GetXaxis()->SetRangeUser(0, 28);
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
    leg->AddEntry(D0_fonll_raa_errordata,"CMS Preliminary R_{AA}, #left|y#right| < 2.0, Centrality 0-10%","PLf");
    leg->AddEntry(b, "Syst. TAA+BR, CMS","f");
	leg->AddEntry( RAA_Alice_statserror, "Alice Preliminary R_{AA}, #left|y#right| < 0.5, Centrality 0-7.5%","PL");
	leg->AddEntry(b_alice, "Syst. TAA+BR, Alice","f");
    leg->SetBorderSize(0);
    leg->SetFillStyle(0);
    leg->Draw();

    cfg_alice_0to20->SaveAs("./alicecomparison/Comparison_alice_cent0to10_dataplusfonll_y1.png");
    cfg_alice_0to20->SaveAs("./alicecomparison/Comparison_alice_cent0to10_dataplusfonll_y1.pdf");

}
