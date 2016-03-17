# define NPTALICE 10
# define NPTCHARGEPARTICLE 27

double syserrorPerTAAfraction = 5.4e-2;
double syserrorPerTAAfraction_alice = 5.1e-2;

bool removelastpoint = true;

void Alicecompare_cent0to10_dataplusfonll_y1()
{   
    gStyle->SetOptTitle(0);
    gStyle->SetOptStat(0);
    TH1::SetDefaultSumw2();

	double ptcentalice[NPTALICE] = {1.5, 2.5, 3.5, 4.5, 5.5, 7.0, 10.0, 14.0, 20, 30};
	double pterroralice[NPTALICE] = { 0.5, 0.5, 0.5, 0.5, 0.5, 1.0, 2.0, 2.0, 4.0, 6.0};
	double RAAcent[NPTALICE] = { 0.695, 0.694, 0.385, 0.245, 0.186, 0.153, 0.155, 0.174, 0.219};

	double RAAstatserror[NPTALICE] = { 0.210, 0.079, 0.037, 0.026, 0.025, 0.019, 0.021, 0.048, 0.058};
	double RAAsyserrorhigh[NPTALICE] = { 0.257, 0.199, 0.088, 0.057, 0.044, 0.035, 0.038, 0.049, 0.094};
	double RAAsyserrorlow[NPTALICE] = { 0.303, 0.289, 0.118, 0.071, 0.049, 0.038, 0.039, 0.048, 0.125};

	if ( removelastpoint ) RAAcent[NPTALICE-1] = -999;

	TFile * inputcms = new TFile("./rootfiles/PromptRAA_D0_PbPb_spectrum_fonll_effunpre_cent0to10_ptbin12_y1_dataplusfonll.root");

	TGraphAsymmErrors * D0_fonll_raa_errorsys = ( TGraphAsymmErrors * ) inputcms->Get("D0_fonll_raa_errorsys");
	TGraphAsymmErrors * D0_fonll_raa_errorfonll = ( TGraphAsymmErrors * ) inputcms->Get("D0_fonll_raa_errorfonll");
	TGraphAsymmErrors * D0_fonll_raa_errordata = ( TGraphAsymmErrors * ) inputcms->Get("D0_fonll_raa_errordata");
	TGraphAsymmErrors * D0_fonll_raa_errordata_dataextraref = ( TGraphAsymmErrors * ) inputcms->Get("D0_fonll_raa_errordata_dataextraref");
	TGraphAsymmErrors * D0_fonll_raa_errordata_FONLLref = ( TGraphAsymmErrors * ) inputcms->Get("D0_fonll_raa_errordata_FONLLref");

	TGraphAsymmErrors * D0_fonll_raa_errordata_FONLLref_scaleby1over1p3 = ( TGraphAsymmErrors * ) D0_fonll_raa_errordata_FONLLref->Clone("D0_fonll_raa_errordata_FONLLref_scaleby1over1p3");

	for( int i = 0; i < D0_fonll_raa_errordata_FONLLref_scaleby1over1p3->GetN(); i++ )
	{
		D0_fonll_raa_errordata_FONLLref_scaleby1over1p3->GetY()[i] = D0_fonll_raa_errordata_FONLLref_scaleby1over1p3->GetY()[i] / 1.3;
		D0_fonll_raa_errordata_FONLLref_scaleby1over1p3->SetPointEYhigh(i, D0_fonll_raa_errordata_FONLLref_scaleby1over1p3->GetErrorYhigh(i) / 1.3);
		D0_fonll_raa_errordata_FONLLref_scaleby1over1p3->SetPointEYlow(i, D0_fonll_raa_errordata_FONLLref_scaleby1over1p3->GetErrorYlow(i) / 1.3);
	}

	
	D0_fonll_raa_errordata_FONLLref_scaleby1over1p3->SetLineColor(2.0);
	D0_fonll_raa_errordata_FONLLref_scaleby1over1p3->SetMarkerColor(2.0);

	TCanvas * cfg_alice_0to20 = new TCanvas("cfg_alice_0to20","cfg_alice_0to20");

    D0_fonll_raa_errorsys->GetXaxis()->SetRangeUser(0, 40);
    D0_fonll_raa_errorsys->GetYaxis()->SetTitle("R*_{#kern[-0.3]{AA}} , R_{AA}");
	if( removelastpoint ) D0_fonll_raa_errorsys->GetXaxis()->SetRangeUser(0, 40);
	D0_fonll_raa_errorsys->Draw("A2");
	D0_fonll_raa_errorfonll->Draw("2same");
//	D0_fonll_raa_errordata->Draw("Psame");
    D0_fonll_raa_errordata_dataextraref->Draw("Psame");
	D0_fonll_raa_errordata_FONLLref->Draw("Psame");

//	D0_fonll_raa_errordata_FONLLref_scaleby1over1p3->Draw("Psame");

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
//    RAA_Alice_statserror->Draw("psame");

    TGraphAsymmErrors * RAA_Alice_statserror_dataextraref = ( TGraphAsymmErrors *) RAA_Alice_statserror->Clone("RAA_Alice_statserror_dataextraref");
    RAA_Alice_statserror_dataextraref->SetName("RAA_Alice_statserror_dataextraref");

    for( int i = 0; i < RAA_Alice_statserror_dataextraref->GetN(); i++ )
    {
        if( RAA_Alice_statserror_dataextraref->GetX()[i] > 16.0 )
        {
            RAA_Alice_statserror_dataextraref->GetX()[i] = -999;
            RAA_Alice_statserror_dataextraref->SetPointEYlow(i, 0);
            RAA_Alice_statserror_dataextraref->SetPointEYhigh(i, 0);

        }
    }

    RAA_Alice_statserror_dataextraref->Draw("Psame");


    TGraphAsymmErrors * RAA_Alice_statserror_FONLLref = ( TGraphAsymmErrors *) RAA_Alice_statserror->Clone("RAA_Alice_statserror_FONLLref");
    RAA_Alice_statserror_FONLLref->SetName("RAA_Alice_statserror_FONLLref");

    for( int i = 0; i < RAA_Alice_statserror_FONLLref->GetN(); i++ )
    {
        if( RAA_Alice_statserror_FONLLref->GetX()[i] < 16.0 )
        {
            RAA_Alice_statserror_FONLLref->GetX()[i] = -999;
            RAA_Alice_statserror_FONLLref->SetPointEYlow(i, 0);
            RAA_Alice_statserror_FONLLref->SetPointEYhigh(i, 0);

        }
    }

    RAA_Alice_statserror_FONLLref->SetMarkerStyle(21);
    RAA_Alice_statserror_FONLLref->Draw("Psame");


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
    leg->SetTextSize(0.03);
    leg->AddEntry(D0_fonll_raa_errordata, "Prompt D^{0} R*_{#kern[-0.3]{AA}}, CMS Preliminary", "PL");
    leg->AddEntry((TObject*)0, "#scale[0.8]{|y| < 1.0, Cent. 0-10%}","");
    leg->AddEntry(D0_fonll_raa_errorsys, "Syst. PbPb data","F");
    leg->AddEntry(D0_fonll_raa_errorfonll,"Err. pp reference","f");
//  leg->AddEntry(b, "Syst._{} T_{AA}+N_{MB}+BR","f");
    leg->SetBorderSize(0);
    leg->SetFillStyle(0);
    leg->Draw();

    TLegend *legalice = new TLegend(0.18,0.365,0.45,0.50);
    legalice->SetTextFont(42);
    legalice->SetTextSize(0.03);
    legalice->AddEntry( RAA_Alice_statserror, "Prompt D^{0} R_{AA}, Alice", "PL");
	legalice->AddEntry( (TObject*)0, "#scale[0.8]{Submitted to JHEP, arXiv:1509.06888}", "");
    legalice->AddEntry( (TObject*)0, "#scale[0.8]{|y| < 0.5, Cent. 0-10%}","");
    legalice->AddEntry( RAA_Alice_syserror, "Syst.", "F");
//  legalice->AddEntry( b_alice, "Syst. normalization", "f");
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

    cfg_alice_0to20->SaveAs("./results/Comparison_alice_cent0to10_dataplusfonll_y1.png");
    cfg_alice_0to20->SaveAs("./results/Comparison_alice_cent0to10_dataplusfonll_y1.pdf");
}
