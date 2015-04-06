void Dmeson_RAFONLL_Npart()
{
	gStyle->SetOptTitle(0);
	gStyle->SetOptStat(0);

	TGraphAsymmErrors * D0_fonll_raa_errordata[4];
	TGraphAsymmErrors * D0_fonll_raa_errorfonll[4];

	TFile * input_cent0to10 = new TFile("RAA_D0_PbPb_spectrum_fonll_effunpre_cent0to10_ptbin4.root");
	D0_fonll_raa_errordata[0] = ( TGraphAsymmErrors * ) input_cent0to10->Get("D0_fonll_raa_errordata");
	D0_fonll_raa_errorfonll[0] = ( TGraphAsymmErrors * ) input_cent0to10->Get("D0_fonll_raa_errorfonll");

	TFile * input_cent10to30 = new TFile("RAA_D0_PbPb_spectrum_fonll_effunpre_cent10to30_ptbin4.root");
	D0_fonll_raa_errordata[1] = ( TGraphAsymmErrors * ) input_cent10to30->Get("D0_fonll_raa_errordata");
	D0_fonll_raa_errorfonll[1] = ( TGraphAsymmErrors * ) input_cent10to30->Get("D0_fonll_raa_errorfonll");

	TFile * input_cent30to50 = new TFile("RAA_D0_PbPb_spectrum_fonll_effunpre_cent30to50_ptbin4.root");
	D0_fonll_raa_errordata[2] = ( TGraphAsymmErrors * ) input_cent30to50->Get("D0_fonll_raa_errordata");
	D0_fonll_raa_errorfonll[2] = ( TGraphAsymmErrors * ) input_cent30to50->Get("D0_fonll_raa_errorfonll");

	TFile * input_cent50to100 = new TFile("RAA_D0_PbPb_spectrum_fonll_effunpre_cent50to100_ptbin4.root");
	D0_fonll_raa_errordata[3] = ( TGraphAsymmErrors * ) input_cent50to100->Get("D0_fonll_raa_errordata");
	D0_fonll_raa_errorfonll[3] = ( TGraphAsymmErrors * ) input_cent50to100->Get("D0_fonll_raa_errorfonll");

	TCanvas * D0_RAFONLL_4ptbin = new TCanvas("D0_RAFONLL_4ptbin","D0_RAFONLL_4ptbin");

	D0_fonll_raa_errorfonll[0]->Draw("A2");
	D0_fonll_raa_errordata[0]->Draw("P");

    D0_fonll_raa_errorfonll[1]->SetLineColor(4.0);
	D0_fonll_raa_errordata[1]->SetLineColor(4.0);
	D0_fonll_raa_errordata[1]->SetMarkerColor(4.0);
	D0_fonll_raa_errorfonll[1]->Draw("2");
	D0_fonll_raa_errordata[1]->Draw("P");

    D0_fonll_raa_errorfonll[2]->SetLineColor(2.0);
	D0_fonll_raa_errordata[2]->SetLineColor(2.0);
	D0_fonll_raa_errordata[2]->SetMarkerColor(2.0);
	D0_fonll_raa_errorfonll[2]->Draw("2");
	D0_fonll_raa_errordata[2]->Draw("P");

    D0_fonll_raa_errorfonll[3]->SetLineColor(kGreen+2);
	D0_fonll_raa_errordata[3]->SetLineColor(kGreen+2);
	D0_fonll_raa_errordata[3]->SetMarkerColor(kGreen+2);
	D0_fonll_raa_errorfonll[3]->Draw("2");
	D0_fonll_raa_errordata[3]->Draw("P");

    TLegend * t = new TLegend(0.5, 0.7, 0.85, 0.85);
	t->SetFillColor(0);
	t->AddEntry(D0_fonll_raa_errordata[0], "Centrality 0-10%", "PL");
	t->AddEntry(D0_fonll_raa_errordata[1], "Centrality 10%-30%", "PL");
    t->AddEntry(D0_fonll_raa_errordata[2], "Centrality 30%-50%", "PL");
    t->AddEntry(D0_fonll_raa_errordata[3], "Centrality 50-100%", "PL");
	t->Draw();

	D0_RAFONLL_4ptbin->SaveAs("plots/D0_RAFONLL_4ptbin_cent0103050100.png");
	D0_RAFONLL_4ptbin->SaveAs("plots/D0_RAFONLL_4ptbin_cent0103050100.pdf");


    double step = 10.;
	double Npart_central[4] = {22.06, 108.15, 224.42, 355.45};
	double Npart_error[4];
    double Npart_pt4p5to7[4];
	double Npart_pt7to11[4];
	double Npart_pt11to20[4];
	double Npart_pt20to40[4];

	double RAA_D0_pt4p5to7[4];
	double RAA_D0_pt4p5to7_errordata_yl[4];
	double RAA_D0_pt4p5to7_errordata_yh[4];
	double RAA_D0_pt4p5to7_errorfonll_yl[4];
	double RAA_D0_pt4p5to7_errorfonll_yh[4];
	
	double RAA_D0_pt7to11[4];
	double RAA_D0_pt7to11_errordata_yl[4];
	double RAA_D0_pt7to11_errordata_yh[4];
	double RAA_D0_pt7to11_errorfonll_yl[4];
	double RAA_D0_pt7to11_errorfonll_yh[4];
	
	double RAA_D0_pt11to20[4];
	double RAA_D0_pt11to20_errordata_yl[4];
	double RAA_D0_pt11to20_errordata_yh[4];
	double RAA_D0_pt11to20_errorfonll_yl[4];
	double RAA_D0_pt11to20_errorfonll_yh[4];
	
	double RAA_D0_pt20to40[4];
	double RAA_D0_pt20to40_errordata_yl[4];
	double RAA_D0_pt20to40_errordata_yh[4];
	double RAA_D0_pt20to40_errorfonll_yl[4];
	double RAA_D0_pt20to40_errorfonll_yh[4];

	for( int i = 0; i < 4; i++ )
	{
		Npart_error[i] = step/2.;
		Npart_pt4p5to7[i] = Npart_central[i] - 1.5 * step;
		Npart_pt7to11[i]  = Npart_central[i] - step * 0.5;
		Npart_pt11to20[i]  = Npart_central[i] + step * 0.5;
		Npart_pt20to40[i]  = Npart_central[i] + 1.5 * step;
	}

	for( int i = 0; i < 4; i++ )
	{
		RAA_D0_pt4p5to7[i] = D0_fonll_raa_errordata[3-i]->GetY()[0];
		cout << " RAA_D0_pt4p5to7[i]: " << RAA_D0_pt4p5to7[i] << endl;
		RAA_D0_pt4p5to7_errordata_yl[i] = D0_fonll_raa_errordata[3-i]->GetErrorYlow(0);
		RAA_D0_pt4p5to7_errordata_yh[i] = D0_fonll_raa_errordata[3-i]->GetErrorYhigh(0);
		RAA_D0_pt4p5to7_errorfonll_yl[i] = D0_fonll_raa_errorfonll[3-i]->GetErrorYlow(0);
		RAA_D0_pt4p5to7_errorfonll_yh[i] = D0_fonll_raa_errorfonll[3-i]->GetErrorYhigh(0);

		RAA_D0_pt7to11[i] = D0_fonll_raa_errordata[3-i]->GetY()[1];
		RAA_D0_pt7to11_errordata_yl[i] = D0_fonll_raa_errordata[3-i]->GetErrorYlow(1);
		RAA_D0_pt7to11_errordata_yh[i] = D0_fonll_raa_errordata[3-i]->GetErrorYhigh(1);
		RAA_D0_pt7to11_errorfonll_yl[i] = D0_fonll_raa_errorfonll[3-i]->GetErrorYlow(1);
		RAA_D0_pt7to11_errorfonll_yh[i] = D0_fonll_raa_errorfonll[3-i]->GetErrorYhigh(1);

		RAA_D0_pt11to20[i] = D0_fonll_raa_errordata[3-i]->GetY()[2];
		RAA_D0_pt11to20_errordata_yl[i] = D0_fonll_raa_errordata[3-i]->GetErrorYlow(2);
		RAA_D0_pt11to20_errordata_yh[i] = D0_fonll_raa_errordata[3-i]->GetErrorYhigh(2);
		RAA_D0_pt11to20_errorfonll_yl[i] = D0_fonll_raa_errorfonll[3-i]->GetErrorYlow(2);
		RAA_D0_pt11to20_errorfonll_yh[i] = D0_fonll_raa_errorfonll[3-i]->GetErrorYhigh(2);

		RAA_D0_pt20to40[i] = D0_fonll_raa_errordata[3-i]->GetY()[3];
		RAA_D0_pt20to40_errordata_yl[i] = D0_fonll_raa_errordata[3-i]->GetErrorYlow(3);
		RAA_D0_pt20to40_errordata_yh[i] = D0_fonll_raa_errordata[3-i]->GetErrorYhigh(3);
		RAA_D0_pt20to40_errorfonll_yl[i] = D0_fonll_raa_errorfonll[3-i]->GetErrorYlow(3);
		RAA_D0_pt20to40_errorfonll_yh[i] = D0_fonll_raa_errorfonll[3-i]->GetErrorYhigh(3);
	}

	TGraphAsymmErrors * RAA_D0_pt4p5to7_errordata_Npart = new TGraphAsymmErrors( 4, Npart_pt4p5to7, RAA_D0_pt4p5to7, Npart_error, Npart_error, RAA_D0_pt4p5to7_errordata_yl, RAA_D0_pt4p5to7_errordata_yh);
    TGraphAsymmErrors * RAA_D0_pt4p5to7_errorfonll_Npart = new TGraphAsymmErrors( 4, Npart_pt4p5to7, RAA_D0_pt4p5to7, Npart_error, Npart_error, RAA_D0_pt4p5to7_errorfonll_yl, RAA_D0_pt4p5to7_errorfonll_yh);

	TGraphAsymmErrors * RAA_D0_pt7to11_errordata_Npart = new TGraphAsymmErrors( 4, Npart_pt7to11, RAA_D0_pt7to11, Npart_error, Npart_error, RAA_D0_pt7to11_errordata_yl, RAA_D0_pt7to11_errordata_yh);
    TGraphAsymmErrors * RAA_D0_pt7to11_errorfonll_Npart = new TGraphAsymmErrors( 4, Npart_pt7to11, RAA_D0_pt7to11, Npart_error, Npart_error, RAA_D0_pt7to11_errorfonll_yl, RAA_D0_pt7to11_errorfonll_yh);

	TGraphAsymmErrors * RAA_D0_pt11to20_errordata_Npart = new TGraphAsymmErrors( 4, Npart_pt11to20, RAA_D0_pt11to20, Npart_error, Npart_error, RAA_D0_pt11to20_errordata_yl, RAA_D0_pt11to20_errordata_yh);
    TGraphAsymmErrors * RAA_D0_pt11to20_errorfonll_Npart = new TGraphAsymmErrors( 4, Npart_pt11to20, RAA_D0_pt11to20, Npart_error, Npart_error, RAA_D0_pt11to20_errorfonll_yl, RAA_D0_pt11to20_errorfonll_yh);

	TGraphAsymmErrors * RAA_D0_pt20to40_errordata_Npart = new TGraphAsymmErrors( 4, Npart_pt20to40, RAA_D0_pt20to40, Npart_error, Npart_error, RAA_D0_pt20to40_errordata_yl, RAA_D0_pt20to40_errordata_yh);
    TGraphAsymmErrors * RAA_D0_pt20to40_errorfonll_Npart = new TGraphAsymmErrors( 4, Npart_pt20to40, RAA_D0_pt20to40, Npart_error, Npart_error, RAA_D0_pt20to40_errorfonll_yl, RAA_D0_pt20to40_errorfonll_yh);

	TCanvas * D0_RAFONLL_Npart = new TCanvas("D0_RAFONLL_Npart","D0_RAFONLL_Npart");

	RAA_D0_pt4p5to7_errorfonll_Npart->GetYaxis()->SetRangeUser(0, 2);
	RAA_D0_pt4p5to7_errorfonll_Npart->GetYaxis()->SetTitle("D^{0} R^{FONLL}_{AA}");
	RAA_D0_pt4p5to7_errorfonll_Npart->GetXaxis()->SetRangeUser(0, 400);
	RAA_D0_pt4p5to7_errorfonll_Npart->GetXaxis()->SetTitle("N_{part}");
	RAA_D0_pt4p5to7_errorfonll_Npart->SetFillColor(0);
	RAA_D0_pt4p5to7_errorfonll_Npart->SetFillStyle(0);
	RAA_D0_pt4p5to7_errorfonll_Npart->SetLineColor(1.0);
	RAA_D0_pt4p5to7_errorfonll_Npart->Draw("A2");

	RAA_D0_pt4p5to7_errordata_Npart->SetMarkerStyle(20);
	RAA_D0_pt4p5to7_errordata_Npart->SetMarkerSize(0.8);
	RAA_D0_pt4p5to7_errordata_Npart->SetLineColor(1.0);
	RAA_D0_pt4p5to7_errordata_Npart->SetMarkerColor(1.0);
	RAA_D0_pt4p5to7_errordata_Npart->Draw("P");

	RAA_D0_pt7to11_errorfonll_Npart->GetYaxis()->SetRangeUser(0, 2);
	RAA_D0_pt7to11_errorfonll_Npart->GetYaxis()->SetTitle("D^{0} R^{FONLL}_{AA}");
	RAA_D0_pt7to11_errorfonll_Npart->GetXaxis()->SetRangeUser(0, 400);
	RAA_D0_pt7to11_errorfonll_Npart->GetXaxis()->SetTitle("N_{part}");
	RAA_D0_pt7to11_errorfonll_Npart->SetFillColor(0);
	RAA_D0_pt7to11_errorfonll_Npart->SetFillStyle(0);
	RAA_D0_pt7to11_errorfonll_Npart->SetLineColor(4.0);
	RAA_D0_pt7to11_errorfonll_Npart->Draw("2");

	RAA_D0_pt7to11_errordata_Npart->SetMarkerStyle(20);
	RAA_D0_pt7to11_errordata_Npart->SetMarkerSize(0.8);
	RAA_D0_pt7to11_errordata_Npart->SetLineColor(4.0);
	RAA_D0_pt7to11_errordata_Npart->SetMarkerColor(4.0);
	RAA_D0_pt7to11_errordata_Npart->Draw("P");

	RAA_D0_pt11to20_errorfonll_Npart->GetYaxis()->SetRangeUser(0, 2);
	RAA_D0_pt11to20_errorfonll_Npart->GetYaxis()->SetTitle("D^{0} R^{FONLL}_{AA}");
	RAA_D0_pt11to20_errorfonll_Npart->GetXaxis()->SetRangeUser(0, 400);
	RAA_D0_pt11to20_errorfonll_Npart->GetXaxis()->SetTitle("N_{part}");
	RAA_D0_pt11to20_errorfonll_Npart->SetFillColor(0);
	RAA_D0_pt11to20_errorfonll_Npart->SetFillStyle(0);
	RAA_D0_pt11to20_errorfonll_Npart->SetLineColor(2.0);
	RAA_D0_pt11to20_errorfonll_Npart->Draw("2");

	RAA_D0_pt11to20_errordata_Npart->SetMarkerStyle(20);
	RAA_D0_pt11to20_errordata_Npart->SetMarkerSize(0.8);
	RAA_D0_pt11to20_errordata_Npart->SetLineColor(2.0);
	RAA_D0_pt11to20_errordata_Npart->SetMarkerColor(2.0);
	RAA_D0_pt11to20_errordata_Npart->Draw("P");
	
	RAA_D0_pt20to40_errorfonll_Npart->GetYaxis()->SetRangeUser(0, 2);
	RAA_D0_pt20to40_errorfonll_Npart->GetYaxis()->SetTitle("D^{0} R^{FONLL}_{AA}");
	RAA_D0_pt20to40_errorfonll_Npart->GetXaxis()->SetRangeUser(0, 400);
	RAA_D0_pt20to40_errorfonll_Npart->GetXaxis()->SetTitle("N_{part}");
	RAA_D0_pt20to40_errorfonll_Npart->SetFillColor(0);
	RAA_D0_pt20to40_errorfonll_Npart->SetFillStyle(0);
	RAA_D0_pt20to40_errorfonll_Npart->SetLineColor(kGreen+2);
	RAA_D0_pt20to40_errorfonll_Npart->Draw("2");

	RAA_D0_pt20to40_errordata_Npart->SetMarkerStyle(20);
	RAA_D0_pt20to40_errordata_Npart->SetMarkerSize(0.8);
	RAA_D0_pt20to40_errordata_Npart->SetLineColor(kGreen+2);
	RAA_D0_pt20to40_errordata_Npart->SetMarkerColor(kGreen+2);
	RAA_D0_pt20to40_errordata_Npart->Draw("P");
    
	TLegend * t = new TLegend(0.5, 0.7, 0.85, 0.85);
	t->SetFillColor(0);
	t->AddEntry(RAA_D0_pt4p5to7_errordata_Npart, "4.5 < p_{T} < 7 GeV/c", "PL");
	t->AddEntry(RAA_D0_pt7to11_errordata_Npart, "7 < p_{T} < 11 GeV/c", "PL");
    t->AddEntry(RAA_D0_pt11to20_errordata_Npart, "11 < p_{T} < 20 GeV/c", "PL");
    t->AddEntry(RAA_D0_pt20to40_errordata_Npart, "20 < p_{T} < 40 GeV/c", "PL");
	t->Draw();

	D0_RAFONLL_Npart->SaveAs("plots/D0_RAFONLL_Npart_cent0103050100_pt4p57112040.png");
	D0_RAFONLL_Npart->SaveAs("plots/D0_RAFONLL_Npart_cent0103050100_pt4p57112040.pdf");
}
