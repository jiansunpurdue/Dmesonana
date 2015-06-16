void Dmeson_RCP_Centrality_7ptbin_y1()
{
	gStyle->SetOptTitle(0);
	gStyle->SetOptStat(0);

	TH1D * D0_Rcp_errorstats[3];
	TGraphAsymmErrors * RCP_errorsys[3];

	TFile * input_cent0to10 = new TFile("RCP_D0_PbPb_effunpre_cent0to10_ptbin7_y1.root");
	D0_Rcp_errorstats[0] = ( TH1D * ) input_cent0to10->Get("D0_Rcp_errorstats");
	RCP_errorsys[0] = ( TGraphAsymmErrors * ) input_cent0to10->Get("RCP_errorsys");

	TFile * input_cent10to30 = new TFile("RCP_D0_PbPb_effunpre_cent10to30_ptbin7_y1.root");
	D0_Rcp_errorstats[1] = ( TH1D * ) input_cent10to30->Get("D0_Rcp_errorstats");
	RCP_errorsys[1] = ( TGraphAsymmErrors * ) input_cent10to30->Get("RCP_errorsys");

	TFile * input_cent30to50 = new TFile("RCP_D0_PbPb_effunpre_cent30to50_ptbin7_y1.root");
	D0_Rcp_errorstats[2] = ( TH1D * ) input_cent30to50->Get("D0_Rcp_errorstats");
	RCP_errorsys[2] = ( TGraphAsymmErrors * ) input_cent30to50->Get("RCP_errorsys");

	TCanvas * D0_RCP_7ptbin = new TCanvas("D0_RCP_7ptbin","D0_RCP_7ptbin");

//    RCP_errorsys[0]->SetFillColorAlpha(15, 0.5);
//    TColor *col1 = gROOT->GetColor(15);
//	col1->SetAlpha(0.2);
    RCP_errorsys[0]->SetFillColor(15);
    RCP_errorsys[0]->Draw("A2");
    D0_Rcp_errorstats[0]->SetMarkerStyle(20);
	D0_Rcp_errorstats[0]->SetFillColor(15);
	D0_Rcp_errorstats[0]->Draw("same");


    RCP_errorsys[1]->SetFillColor(kBlue-9);
    RCP_errorsys[1]->Draw("2same");
	D0_Rcp_errorstats[1]->SetFillColor(kBlue-9);
	D0_Rcp_errorstats[1]->SetLineColor(4.0);
	D0_Rcp_errorstats[1]->SetMarkerColor(4.0);
	D0_Rcp_errorstats[1]->SetMarkerStyle(21);
	D0_Rcp_errorstats[1]->Draw("same");

    RCP_errorsys[2]->SetFillColor(kRed-7);
	RCP_errorsys[2]->Draw("2same");
	D0_Rcp_errorstats[2]->SetFillColor(kRed-7);
	D0_Rcp_errorstats[2]->SetLineColor(2.0);
	D0_Rcp_errorstats[2]->SetMarkerColor(2.0);
	D0_Rcp_errorstats[2]->SetMarkerStyle(22);
	D0_Rcp_errorstats[2]->Draw("same");

    TF1 * fun = new TF1("fun", "1.0", 0, 500);
    fun->SetLineColor(1.0);
    fun->SetLineStyle(3);
    fun->SetLineWidth(0.1);
    fun->Draw("same");

    TLegend * t = new TLegend(0.5, 0.65, 0.85, 0.8);
	t->SetFillColor(0);
	t->AddEntry(D0_Rcp_errorstats[0], "Centrality 0-10%", "PLf");
	t->AddEntry(D0_Rcp_errorstats[1], "Centrality 10%-30%", "PLf");
    t->AddEntry(D0_Rcp_errorstats[2], "Centrality 30%-50%", "PLf");
	t->Draw();

    TLatex Tl;
    Tl.SetNDC();
    Tl.SetTextAlign(12);
    Tl.SetTextSize(0.03);
    Tl.SetTextFont(62);
    Tl.DrawLatex(0.15,0.85, "CMS Preliminary #sqrt{s_{NN}} = 2.76 TeV");
    Tl.DrawLatex(0.15,0.80, "#left|y#right| < 1.0");

	D0_RCP_7ptbin->SaveAs("results/D0_RCP_7ptbin_cent0103050100_y1.png");
	D0_RCP_7ptbin->SaveAs("results/D0_RCP_7ptbin_cent0103050100_y1.pdf");

//
//    double step = 5.;
//	double Npart_central[4] = {22.06, 108.15, 224.42, 355.45};
//	double Npart_error[4];
//    double Npart_pt4p5to7[4];
//	double Npart_pt7to11[4];
//	double Npart_pt11to20[4];
//	double Npart_pt20to40[4];
//
//	double RAA_D0_pt4p5to7[4];
//	double RAA_D0_pt4p5to7_errordata_yl[4];
//	double RAA_D0_pt4p5to7_errordata_yh[4];
//	double RAA_D0_pt4p5to7_errorfonll_yl[4];
//	double RAA_D0_pt4p5to7_errorfonll_yh[4];
//	
//	double RAA_D0_pt7to11[4];
//	double RAA_D0_pt7to11_errordata_yl[4];
//	double RAA_D0_pt7to11_errordata_yh[4];
//	double RAA_D0_pt7to11_errorfonll_yl[4];
//	double RAA_D0_pt7to11_errorfonll_yh[4];
//	
//	double RAA_D0_pt11to20[4];
//	double RAA_D0_pt11to20_errordata_yl[4];
//	double RAA_D0_pt11to20_errordata_yh[4];
//	double RAA_D0_pt11to20_errorfonll_yl[4];
//	double RAA_D0_pt11to20_errorfonll_yh[4];
//	
//	double RAA_D0_pt20to40[4];
//	double RAA_D0_pt20to40_errordata_yl[4];
//	double RAA_D0_pt20to40_errordata_yh[4];
//	double RAA_D0_pt20to40_errorfonll_yl[4];
//	double RAA_D0_pt20to40_errorfonll_yh[4];
//
//	for( int i = 0; i < 4; i++ )
//	{
//		Npart_error[i] = step/2.;
//		Npart_pt4p5to7[i] = Npart_central[i] - 1.5 * step;
//		Npart_pt7to11[i]  = Npart_central[i] - step * 0.5;
//		Npart_pt11to20[i]  = Npart_central[i] + step * 0.5;
//		Npart_pt20to40[i]  = Npart_central[i] + 1.5 * step;
//	}
//
//	for( int i = 0; i < 4; i++ )
//	{
//		RAA_D0_pt4p5to7[i] = D0_Rcp_errorstats[3-i]->GetY()[0];
//		cout << " RAA_D0_pt4p5to7[i]: " << RAA_D0_pt4p5to7[i] << endl;
//		RAA_D0_pt4p5to7_errordata_yl[i] = D0_Rcp_errorstats[3-i]->GetErrorYlow(0);
//		RAA_D0_pt4p5to7_errordata_yh[i] = D0_Rcp_errorstats[3-i]->GetErrorYhigh(0);
//		RAA_D0_pt4p5to7_errorfonll_yl[i] = D0_fonll_raa_errorfonll[3-i]->GetErrorYlow(0);
//		RAA_D0_pt4p5to7_errorfonll_yh[i] = D0_fonll_raa_errorfonll[3-i]->GetErrorYhigh(0);
//
//		RAA_D0_pt7to11[i] = D0_Rcp_errorstats[3-i]->GetY()[1];
//		RAA_D0_pt7to11_errordata_yl[i] = D0_Rcp_errorstats[3-i]->GetErrorYlow(1);
//		RAA_D0_pt7to11_errordata_yh[i] = D0_Rcp_errorstats[3-i]->GetErrorYhigh(1);
//		RAA_D0_pt7to11_errorfonll_yl[i] = D0_fonll_raa_errorfonll[3-i]->GetErrorYlow(1);
//		RAA_D0_pt7to11_errorfonll_yh[i] = D0_fonll_raa_errorfonll[3-i]->GetErrorYhigh(1);
//
//		RAA_D0_pt11to20[i] = D0_Rcp_errorstats[3-i]->GetY()[2];
//		RAA_D0_pt11to20_errordata_yl[i] = D0_Rcp_errorstats[3-i]->GetErrorYlow(2);
//		RAA_D0_pt11to20_errordata_yh[i] = D0_Rcp_errorstats[3-i]->GetErrorYhigh(2);
//		RAA_D0_pt11to20_errorfonll_yl[i] = D0_fonll_raa_errorfonll[3-i]->GetErrorYlow(2);
//		RAA_D0_pt11to20_errorfonll_yh[i] = D0_fonll_raa_errorfonll[3-i]->GetErrorYhigh(2);
//
//		RAA_D0_pt20to40[i] = D0_Rcp_errorstats[3-i]->GetY()[3];
//		RAA_D0_pt20to40_errordata_yl[i] = D0_Rcp_errorstats[3-i]->GetErrorYlow(3);
//		RAA_D0_pt20to40_errordata_yh[i] = D0_Rcp_errorstats[3-i]->GetErrorYhigh(3);
//		RAA_D0_pt20to40_errorfonll_yl[i] = D0_fonll_raa_errorfonll[3-i]->GetErrorYlow(3);
//		RAA_D0_pt20to40_errorfonll_yh[i] = D0_fonll_raa_errorfonll[3-i]->GetErrorYhigh(3);
//	}
//
//	TH1D * RAA_D0_pt4p5to7_errordata_Npart = new TH1D( 4, Npart_pt4p5to7, RAA_D0_pt4p5to7, Npart_error, Npart_error, RAA_D0_pt4p5to7_errordata_yl, RAA_D0_pt4p5to7_errordata_yh);
//    TH1D * RAA_D0_pt4p5to7_errorfonll_Npart = new TH1D( 4, Npart_pt4p5to7, RAA_D0_pt4p5to7, Npart_error, Npart_error, RAA_D0_pt4p5to7_errorfonll_yl, RAA_D0_pt4p5to7_errorfonll_yh);
//
//	TH1D * RAA_D0_pt7to11_errordata_Npart = new TH1D( 4, Npart_pt7to11, RAA_D0_pt7to11, Npart_error, Npart_error, RAA_D0_pt7to11_errordata_yl, RAA_D0_pt7to11_errordata_yh);
//    TH1D * RAA_D0_pt7to11_errorfonll_Npart = new TH1D( 4, Npart_pt7to11, RAA_D0_pt7to11, Npart_error, Npart_error, RAA_D0_pt7to11_errorfonll_yl, RAA_D0_pt7to11_errorfonll_yh);
//
//	TH1D * RAA_D0_pt11to20_errordata_Npart = new TH1D( 4, Npart_pt11to20, RAA_D0_pt11to20, Npart_error, Npart_error, RAA_D0_pt11to20_errordata_yl, RAA_D0_pt11to20_errordata_yh);
//    TH1D * RAA_D0_pt11to20_errorfonll_Npart = new TH1D( 4, Npart_pt11to20, RAA_D0_pt11to20, Npart_error, Npart_error, RAA_D0_pt11to20_errorfonll_yl, RAA_D0_pt11to20_errorfonll_yh);
//
//	TH1D * RAA_D0_pt20to40_errordata_Npart = new TH1D( 4, Npart_pt20to40, RAA_D0_pt20to40, Npart_error, Npart_error, RAA_D0_pt20to40_errordata_yl, RAA_D0_pt20to40_errordata_yh);
//    TH1D * RAA_D0_pt20to40_errorfonll_Npart = new TH1D( 4, Npart_pt20to40, RAA_D0_pt20to40, Npart_error, Npart_error, RAA_D0_pt20to40_errorfonll_yl, RAA_D0_pt20to40_errorfonll_yh);
//
//	TCanvas * D0_RCP_Npart = new TCanvas("D0_RCP_Npart","D0_RCP_Npart");
//
//	RAA_D0_pt4p5to7_errorfonll_Npart->GetYaxis()->SetRangeUser(0, 2);
//	RAA_D0_pt4p5to7_errorfonll_Npart->GetYaxis()->SetTitle("D^{0} R^{FONLL}_{AA}");
//	RAA_D0_pt4p5to7_errorfonll_Npart->GetXaxis()->SetRangeUser(0, 400);
//	RAA_D0_pt4p5to7_errorfonll_Npart->GetXaxis()->SetTitle("N_{part}");
//	RAA_D0_pt4p5to7_errorfonll_Npart->SetFillColor(0);
//	RAA_D0_pt4p5to7_errorfonll_Npart->SetFillStyle(0);
//	RAA_D0_pt4p5to7_errorfonll_Npart->SetLineColor(1.0);
//	RAA_D0_pt4p5to7_errorfonll_Npart->Draw("A2");
//
//	RAA_D0_pt4p5to7_errordata_Npart->SetMarkerStyle(20);
//	RAA_D0_pt4p5to7_errordata_Npart->SetMarkerSize(0.8);
//	RAA_D0_pt4p5to7_errordata_Npart->SetLineColor(1.0);
//	RAA_D0_pt4p5to7_errordata_Npart->SetMarkerColor(1.0);
//	RAA_D0_pt4p5to7_errordata_Npart->Draw("P");
//
//	RAA_D0_pt7to11_errorfonll_Npart->GetYaxis()->SetRangeUser(0, 2);
//	RAA_D0_pt7to11_errorfonll_Npart->GetYaxis()->SetTitle("D^{0} R^{FONLL}_{AA}");
//	RAA_D0_pt7to11_errorfonll_Npart->GetXaxis()->SetRangeUser(0, 400);
//	RAA_D0_pt7to11_errorfonll_Npart->GetXaxis()->SetTitle("N_{part}");
//	RAA_D0_pt7to11_errorfonll_Npart->SetFillColor(0);
//	RAA_D0_pt7to11_errorfonll_Npart->SetFillStyle(0);
//	RAA_D0_pt7to11_errorfonll_Npart->SetLineColor(4.0);
//	RAA_D0_pt7to11_errorfonll_Npart->Draw("2");
//
//	RAA_D0_pt7to11_errordata_Npart->SetMarkerStyle(20);
//	RAA_D0_pt7to11_errordata_Npart->SetMarkerSize(0.8);
//	RAA_D0_pt7to11_errordata_Npart->SetLineColor(4.0);
//	RAA_D0_pt7to11_errordata_Npart->SetMarkerColor(4.0);
//	RAA_D0_pt7to11_errordata_Npart->Draw("P");
//
//	RAA_D0_pt11to20_errorfonll_Npart->GetYaxis()->SetRangeUser(0, 2);
//	RAA_D0_pt11to20_errorfonll_Npart->GetYaxis()->SetTitle("D^{0} R^{FONLL}_{AA}");
//	RAA_D0_pt11to20_errorfonll_Npart->GetXaxis()->SetRangeUser(0, 400);
//	RAA_D0_pt11to20_errorfonll_Npart->GetXaxis()->SetTitle("N_{part}");
//	RAA_D0_pt11to20_errorfonll_Npart->SetFillColor(0);
//	RAA_D0_pt11to20_errorfonll_Npart->SetFillStyle(0);
//	RAA_D0_pt11to20_errorfonll_Npart->SetLineColor(2.0);
//	RAA_D0_pt11to20_errorfonll_Npart->Draw("2");
//
//	RAA_D0_pt11to20_errordata_Npart->SetMarkerStyle(20);
//	RAA_D0_pt11to20_errordata_Npart->SetMarkerSize(0.8);
//	RAA_D0_pt11to20_errordata_Npart->SetLineColor(2.0);
//	RAA_D0_pt11to20_errordata_Npart->SetMarkerColor(2.0);
//	RAA_D0_pt11to20_errordata_Npart->Draw("P");
//	
//	RAA_D0_pt20to40_errorfonll_Npart->GetYaxis()->SetRangeUser(0, 2);
//	RAA_D0_pt20to40_errorfonll_Npart->GetYaxis()->SetTitle("D^{0} R^{FONLL}_{AA}");
//	RAA_D0_pt20to40_errorfonll_Npart->GetXaxis()->SetRangeUser(0, 400);
//	RAA_D0_pt20to40_errorfonll_Npart->GetXaxis()->SetTitle("N_{part}");
//	RAA_D0_pt20to40_errorfonll_Npart->SetFillColor(0);
//	RAA_D0_pt20to40_errorfonll_Npart->SetFillStyle(0);
//	RAA_D0_pt20to40_errorfonll_Npart->SetLineColor(kGreen+2);
//	RAA_D0_pt20to40_errorfonll_Npart->Draw("2");
//
//	RAA_D0_pt20to40_errordata_Npart->SetMarkerStyle(20);
//	RAA_D0_pt20to40_errordata_Npart->SetMarkerSize(0.8);
//	RAA_D0_pt20to40_errordata_Npart->SetLineColor(kGreen+2);
//	RAA_D0_pt20to40_errordata_Npart->SetMarkerColor(kGreen+2);
//	RAA_D0_pt20to40_errordata_Npart->Draw("P");
//    
//	TLegend * t = new TLegend(0.5, 0.7, 0.85, 0.85);
//	t->SetFillColor(0);
//	t->AddEntry(RAA_D0_pt4p5to7_errordata_Npart, "4.5 < p_{T} < 7 GeV/c", "PL");
//	t->AddEntry(RAA_D0_pt7to11_errordata_Npart, "7 < p_{T} < 11 GeV/c", "PL");
//    t->AddEntry(RAA_D0_pt11to20_errordata_Npart, "11 < p_{T} < 20 GeV/c", "PL");
//    t->AddEntry(RAA_D0_pt20to40_errordata_Npart, "20 < p_{T} < 40 GeV/c", "PL");
//	t->Draw();
//
//	D0_RCP_Npart->SaveAs("plots/D0_RCP_Npart_cent0103050100_pt4p57112040.png");
//	D0_RCP_Npart->SaveAs("plots/D0_RCP_Npart_cent0103050100_pt4p57112040.pdf");
}
