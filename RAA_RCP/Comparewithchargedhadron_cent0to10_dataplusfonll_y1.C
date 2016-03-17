# define NPTALICE 10
# define NPTCHARGEPARTICLE 27

double syserrorPerTAAfraction = 5.4e-2;
double syserrorPerTAAfraction_chargep = 6.9e-2;

bool removelastpoint = true;

void Comparewithchargedhadron_cent0to10_dataplusfonll_y1()
{   
    gStyle->SetOptTitle(0);
    gStyle->SetOptStat(0);
    TH1::SetDefaultSumw2();


	TFile * inputcms = new TFile("./rootfiles/PromptRAA_D0_PbPb_spectrum_fonll_effunpre_cent0to10_ptbin12_y1_dataplusfonll.root");

	TGraphAsymmErrors * D0_fonll_raa_errorsys = ( TGraphAsymmErrors * ) inputcms->Get("D0_fonll_raa_errorsys");
	TGraphAsymmErrors * D0_fonll_raa_errorfonll = ( TGraphAsymmErrors * ) inputcms->Get("D0_fonll_raa_errorfonll");
	TGraphAsymmErrors * D0_fonll_raa_errordata = ( TGraphAsymmErrors * ) inputcms->Get("D0_fonll_raa_errordata");
	TGraphAsymmErrors * D0_fonll_raa_errordata_dataextraref = ( TGraphAsymmErrors * ) inputcms->Get("D0_fonll_raa_errordata_dataextraref");
	TGraphAsymmErrors * D0_fonll_raa_errordata_FONLLref = ( TGraphAsymmErrors * ) inputcms->Get("D0_fonll_raa_errordata_FONLLref");

	D0_fonll_raa_errorsys->GetY()[0] = -999;

    double pt_low_chargeparticle[NPTCHARGEPARTICLE] = { 1.000e+00, 1.100e+00, 1.200e+00, 1.400e+00, 1.600e+00, 1.800e+00, 2.000e+00, 2.200e+00, 2.400e+00, 3.200e+00, 4.000e+00, 4.800e+00, 5.600e+00, 6.400e+00, 7.200e+00, 9.600e+00, 1.200e+01, 1.440e+01, 1.920e+01, 2.400e+01, 2.880e+01, 3.520e+01, 4.160e+01, 4.800e+01, 6.080e+01, 7.360e+01, 8.640e+01};

    double pt_high_chargeparticle[NPTCHARGEPARTICLE] = {1.100e+00,1.200e+00,1.400e+00,1.600e+00,1.800e+00,2.000e+00,2.200e+00,2.400e+00,3.200e+00,4.000e+00,4.800e+00,5.600e+00,6.400e+00,7.200e+00,9.600e+00,1.200e+01,1.440e+01,1.920e+01,2.400e+01,2.880e+01,3.520e+01,4.160e+01,4.800e+01,6.080e+01,7.360e+01,8.640e+01,1.036e+02};

    double RAA_center_chargeparticle[NPTCHARGEPARTICLE] = {3.591e-01,3.701e-01,3.887e-01,4.059e-01,4.181e-01,4.204e-01,4.202e-01,4.104e-01,3.622e-01,2.640e-01,1.882e-01,1.487e-01,1.3604e-01,1.380e-01,1.519e-01,1.820e-01,2.226e-01,2.768e-01,3.678e-01,4.003e-01,4.395e-01,5.270e-01,5.161e-01,5.303e-01,6.400e-01,5.331e-01,5.202e-01};

    double error_stat_RAA_chargeparticle[NPTCHARGEPARTICLE] = {3e-04,3e-04,3e-04,4e-04,4e-04,5e-04,6e-04,7e-04,5e-04,7e-04,8e-04,1.0e-03,1.36e-03,1.9e-03,2.0e-03,4.3e-03,8.5e-03,1.23e-02,2.70e-02,4.23e-02,5.59e-02,7.33e-02,8.78e-02,2.90e-02,5.41e-02,5.98e-02,9.06e-02};

    double error_sys_RAA_chargeparticle[NPTCHARGEPARTICLE] = {2.62e-02,2.70e-02,2.84e-02,2.96e-02,3.05e-02,3.07e-02,3.07e-02,3.00e-02,2.65e-02,1.93e-02,1.38e-02,1.09e-02,1.000e-02,1.02e-02,1.12e-02,1.37e-02,1.70e-02,2.22e-02,3.12e-02,3.53e-02,4.06e-02,5.35e-02,5.72e-02,6.10e-02,7.73e-02,6.47e-02,6.36e-02};

    double pt_center_chargeparticle[NPTCHARGEPARTICLE] = {0};
	double error_pt_chargeparticle[NPTCHARGEPARTICLE] = {0};

	for( int i = 0; i < NPTCHARGEPARTICLE; i++ )
	{
		pt_center_chargeparticle[i] = ( pt_high_chargeparticle[i] + pt_low_chargeparticle[i] ) / 2.0;
		error_pt_chargeparticle[i] = (pt_high_chargeparticle[i] - pt_low_chargeparticle[i]) / 2.0;
	}
	
	TGraphErrors * RAA_chargeparticle_error_stat = new TGraphErrors( NPTCHARGEPARTICLE, pt_center_chargeparticle, RAA_center_chargeparticle, error_pt_chargeparticle, error_stat_RAA_chargeparticle);
	TGraphErrors * RAA_chargeparticle_error_sys = new TGraphErrors( NPTCHARGEPARTICLE, pt_center_chargeparticle, RAA_center_chargeparticle, error_pt_chargeparticle, error_sys_RAA_chargeparticle);


    TCanvas * cfg_chargedparticle_0to10 = new TCanvas("cfg_chargedparticle_0to10","cfg_chargedparticle_0to10");

	gPad->SetLogx();



    RAA_chargeparticle_error_sys->GetYaxis()->SetTitle("R*_{#kern[-0.3]{AA}} , R_{AA}");
	RAA_chargeparticle_error_sys->GetXaxis()->SetTitle("p_{T} (GeV/c)");
    RAA_chargeparticle_error_sys->GetXaxis()->SetRangeUser(1.0, 110);
	RAA_chargeparticle_error_sys->GetYaxis()->SetRangeUser(0.0, 2.0);
    RAA_chargeparticle_error_sys->SetFillStyle(1001);
    RAA_chargeparticle_error_sys->SetMarkerStyle(21);
	RAA_chargeparticle_error_sys->SetFillColor(kAzure-4);
    RAA_chargeparticle_error_sys->SetLineColor(kAzure-4);
    RAA_chargeparticle_error_sys->Draw("A2");

    RAA_chargeparticle_error_stat->SetLineWidth(0.5);
    RAA_chargeparticle_error_stat->SetMarkerStyle(21);
    RAA_chargeparticle_error_stat->SetMarkerSize(0.8);
	RAA_chargeparticle_error_stat->SetLineColor(4.0);
	RAA_chargeparticle_error_stat->SetMarkerColor(4.0);
    RAA_chargeparticle_error_stat->Draw("psame");

    D0_fonll_raa_errorsys->GetYaxis()->SetTitle("R*_{#kern[-0.3]{AA}} , R_{AA}");
    D0_fonll_raa_errorsys->GetXaxis()->SetRangeUser(1.0, 90);
	D0_fonll_raa_errorsys->GetYaxis()->SetRangeUser(0.0, 2.0);
    D0_fonll_raa_errorsys->Draw("2same");
    D0_fonll_raa_errorfonll->Draw("2same");
    D0_fonll_raa_errordata_dataextraref->Draw("Psame");
    D0_fonll_raa_errordata_FONLLref->Draw("Psame");

	RAA_chargeparticle_error_sys->Draw("2same");
	RAA_chargeparticle_error_stat->Draw("psame");

	D0_fonll_raa_errordata_dataextraref->Draw("Psame");
	D0_fonll_raa_errordata_FONLLref->Draw("Psame");


    TBox *b = new TBox(1.0,1-syserrorPerTAAfraction,1.1,1+syserrorPerTAAfraction);
    b->SetLineColor(kGray+1);
    b->SetFillColor(kGray+1);
    b->Draw();

    TBox *b_chargep = new TBox(1.1,1-syserrorPerTAAfraction_chargep,1.22,1+syserrorPerTAAfraction_chargep);
    b_chargep->SetLineColor(38.0);
    b_chargep->SetFillColor(38.0);
    b_chargep->Draw();


    TF1 * fun = new TF1("fun", "1.0", 0, 500);
    fun->SetLineColor(1.0);
    fun->SetLineStyle(3);
    fun->SetLineWidth(0.1);
    fun->Draw("same");

    TLegend *leg = new TLegend(0.16,0.67,0.45,0.85);
    leg->SetTextFont(42);
    leg->SetTextSize(0.038);
//	leg->SetTextColor(kRed+2);
    leg->AddEntry(D0_fonll_raa_errordata, "Prompt D^{0} R*_{#kern[-0.3]{AA}}", "PL");
    leg->AddEntry((TObject*)0, "#scale[0.8]{|y| < 1.0, Cent. 0-10%}","");
    leg->AddEntry(D0_fonll_raa_errorsys, "Syst. PbPb data","F");
    leg->AddEntry(D0_fonll_raa_errorfonll,"Err. pp reference","f");
//  leg->AddEntry(b, "Syst._{} T_{AA}+N_{MB}+BR","f");
    leg->SetBorderSize(0);
    leg->SetFillStyle(0);
    leg->Draw();

    TLegend *legchp = new TLegend(0.15,0.36,0.49,0.50);
    legchp->SetTextFont(42);
    legchp->SetTextSize(0.038);
    legchp->AddEntry( RAA_chargeparticle_error_stat, "Charged particle_{} R_{AA}", "PL");
    legchp->AddEntry( (TObject*)0, "#scale[0.8]{|#eta| < 1.0, Cent. 0-5%}","");
	legchp->AddEntry( (TObject*)0, "#scale[0.8]{CMS, EPJC 72 (2012) 1945}","");
    legchp->AddEntry( RAA_chargeparticle_error_sys, "Syst.", "F");
    legchp->SetBorderSize(0);
    legchp->SetFillStyle(0);
    legchp->Draw();


    TLatex Traareference;
    Traareference.SetNDC();
    Traareference.SetTextAlign(12);
    Traareference.SetTextSize(0.03);
    Traareference.SetTextFont(42);
//	Traareference.SetTextColor(kRed+2);
    Traareference.DrawLatex(0.17,0.63, "Filled markers: data-extrapolated reference");
    Traareference.DrawLatex(0.17,0.60, "Open markers: FONLL reference");

    TLatex Tl;
    Tl.SetNDC();
    Tl.SetTextAlign(12);
    Tl.SetTextSize(0.04);
    Tl.SetTextFont(42);
    Tl.DrawLatex(0.125,0.93, "#scale[1.25]{CMS}");
	Tl.DrawLatex(0.24,0.925, "Preliminary");//->SetTextColor(kRed+2);
    Tl.DrawLatex(0.53,0.93, "PbPb #sqrt{s_{NN}} = 2.76 TeV");

    cfg_chargedparticle_0to10->RedrawAxis();

	cfg_chargedparticle_0to10->SaveAs("results/Comparison_D0cent0to10_chargedpcent0to5.png");
	cfg_chargedparticle_0to10->SaveAs("results/Comparison_D0cent0to10_chargedpcent0to5.pdf");

}
