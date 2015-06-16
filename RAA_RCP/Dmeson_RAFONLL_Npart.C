void Dmeson_RAFONLL_Npart()
{
	gStyle->SetOptTitle(0);
	gStyle->SetOptStat(0);

    TGraphAsymmErrors * D0_fonll_raa_errorsys[4];
	TGraphAsymmErrors * D0_fonll_raa_errordata[4];
	TGraphAsymmErrors * D0_fonll_raa_errorfonll[4];

	TFile * input_cent0to10 = new TFile("PromptRAA_D0_PbPb_spectrum_fonll_effunpre_cent0to10_ptbin5.root");
	D0_fonll_raa_errorsys[0] = ( TGraphAsymmErrors * ) input_cent0to10->Get("D0_fonll_raa_errorsys");
	D0_fonll_raa_errordata[0] = ( TGraphAsymmErrors * ) input_cent0to10->Get("D0_fonll_raa_errordata");
	D0_fonll_raa_errorfonll[0] = ( TGraphAsymmErrors * ) input_cent0to10->Get("D0_fonll_raa_errorfonll");

	TFile * input_cent10to30 = new TFile("PromptRAA_D0_PbPb_spectrum_fonll_effunpre_cent10to30_ptbin5.root");
	D0_fonll_raa_errorsys[1] = ( TGraphAsymmErrors * ) input_cent10to30->Get("D0_fonll_raa_errorsys");
	D0_fonll_raa_errordata[1] = ( TGraphAsymmErrors * ) input_cent10to30->Get("D0_fonll_raa_errordata");
	D0_fonll_raa_errorfonll[1] = ( TGraphAsymmErrors * ) input_cent10to30->Get("D0_fonll_raa_errorfonll");

	TFile * input_cent30to50 = new TFile("PromptRAA_D0_PbPb_spectrum_fonll_effunpre_cent30to50_ptbin5.root");
	D0_fonll_raa_errorsys[2] = ( TGraphAsymmErrors * ) input_cent30to50->Get("D0_fonll_raa_errorsys");
	D0_fonll_raa_errordata[2] = ( TGraphAsymmErrors * ) input_cent30to50->Get("D0_fonll_raa_errordata");
	D0_fonll_raa_errorfonll[2] = ( TGraphAsymmErrors * ) input_cent30to50->Get("D0_fonll_raa_errorfonll");

	TFile * input_cent50to100 = new TFile("PromptRAA_D0_PbPb_spectrum_fonll_effunpre_cent50to100_ptbin5.root");
	D0_fonll_raa_errorsys[3] = ( TGraphAsymmErrors * ) input_cent50to100->Get("D0_fonll_raa_errorsys");
	D0_fonll_raa_errordata[3] = ( TGraphAsymmErrors * ) input_cent50to100->Get("D0_fonll_raa_errordata");
	D0_fonll_raa_errorfonll[3] = ( TGraphAsymmErrors * ) input_cent50to100->Get("D0_fonll_raa_errorfonll");

	TCanvas * D0_RAFONLL_4ptbin = new TCanvas("D0_RAFONLL_4ptbin","D0_RAFONLL_4ptbin");

    D0_fonll_raa_errorsys[0]->GetYaxis()->SetRangeUser(0,2.5);
    D0_fonll_raa_errorsys[0]->Draw("A2");

	D0_fonll_raa_errorfonll[0]->Draw("2");
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

    D0_fonll_raa_errorfonll[3]->SetLineColor(kCyan+2);
	D0_fonll_raa_errordata[3]->SetLineColor(kCyan+2);
	D0_fonll_raa_errordata[3]->SetMarkerColor(kCyan+2);
	D0_fonll_raa_errorfonll[3]->Draw("2");
	D0_fonll_raa_errordata[3]->Draw("P");

    TLegend * t = new TLegend(0.5, 0.7, 0.85, 0.85);
	t->SetFillColor(0);
	t->AddEntry(D0_fonll_raa_errordata[0], "Centrality 0-10%", "PL");
	t->AddEntry(D0_fonll_raa_errordata[1], "Centrality 10%-30%", "PL");
    t->AddEntry(D0_fonll_raa_errordata[2], "Centrality 30%-50%", "PL");
    t->AddEntry(D0_fonll_raa_errordata[3], "Centrality 50-100%", "PL");
	t->Draw();

	D0_RAFONLL_4ptbin->SaveAs("results/D0_RAFONLL_5ptbin_cent0103050100.png");
	D0_RAFONLL_4ptbin->SaveAs("results/D0_RAFONLL_5ptbin_cent0103050100.pdf");


    double step = 10.;
	double Npart_central[4] = {22.06, 108.15, 224.42, 355.45};
	double Npart_error[4];
	double Npart_pt3p5to4p5[4];
    double Npart_pt4p5to7[4];
	double Npart_pt7to11[4];
	double Npart_pt11to16[4];
	double Npart_pt16to28[4];

	double RAA_D0_pt3p5to4p5[4];
	double RAA_D0_pt3p5to4p5_errordata_yl[4];
	double RAA_D0_pt3p5to4p5_errordata_yh[4];
	double RAA_D0_pt3p5to4p5_errorfonll_yl[4];
	double RAA_D0_pt3p5to4p5_errorfonll_yh[4];
	double RAA_D0_pt3p5to4p5_errorsys_yl[4];
	double RAA_D0_pt3p5to4p5_errorsys_yh[4];
	
	double RAA_D0_pt4p5to7[4];
	double RAA_D0_pt4p5to7_errordata_yl[4];
	double RAA_D0_pt4p5to7_errordata_yh[4];
	double RAA_D0_pt4p5to7_errorfonll_yl[4];
	double RAA_D0_pt4p5to7_errorfonll_yh[4];
	double RAA_D0_pt4p5to7_errorsys_yl[4];
	double RAA_D0_pt4p5to7_errorsys_yh[4];
	
	double RAA_D0_pt7to11[4];
	double RAA_D0_pt7to11_errordata_yl[4];
	double RAA_D0_pt7to11_errordata_yh[4];
	double RAA_D0_pt7to11_errorfonll_yl[4];
	double RAA_D0_pt7to11_errorfonll_yh[4];
	double RAA_D0_pt7to11_errorsys_yl[4];
	double RAA_D0_pt7to11_errorsys_yh[4];
	
	double RAA_D0_pt11to16[4];
	double RAA_D0_pt11to16_errordata_yl[4];
	double RAA_D0_pt11to16_errordata_yh[4];
	double RAA_D0_pt11to16_errorfonll_yl[4];
	double RAA_D0_pt11to16_errorfonll_yh[4];
	double RAA_D0_pt11to16_errorsys_yl[4];
	double RAA_D0_pt11to16_errorsys_yh[4];
	
	double RAA_D0_pt16to28[4];
	double RAA_D0_pt16to28_errordata_yl[4];
	double RAA_D0_pt16to28_errordata_yh[4];
	double RAA_D0_pt16to28_errorfonll_yl[4];
	double RAA_D0_pt16to28_errorfonll_yh[4];
	double RAA_D0_pt16to28_errorsys_yl[4];
	double RAA_D0_pt16to28_errorsys_yh[4];

	for( int i = 0; i < 4; i++ )
	{
//		Npart_error[i] = step/2.;
//		Npart_pt3p5to4p5[i] = Npart_central[i] - 1.5 * step;
//		Npart_pt4p5to7[i] = Npart_central[i] - 0.5 * step;
//		Npart_pt7to11[i]  = Npart_central[i] + step * 0.5;
//		Npart_pt11to16[i]  = Npart_central[i] + step * 1.5;
//		Npart_pt16to28[i]  = Npart_central[i] + 2.5 * step;

        step = 7.7;
		Npart_error[i] = step/2.;
		Npart_pt3p5to4p5[i] = Npart_central[i] - 2.0 * step;
		Npart_pt4p5to7[i] = Npart_central[i] - 1.0 * step;
		Npart_pt7to11[i]  = Npart_central[i];
		Npart_pt11to16[i]  = Npart_central[i] + step * 1.0;
		Npart_pt16to28[i]  = Npart_central[i] + 2.0 * step;
	}

	for( int i = 0; i < 4; i++ )
	{
		RAA_D0_pt3p5to4p5[i] = D0_fonll_raa_errordata[3-i]->GetY()[0];
		cout << " RAA_D0_pt3p5to4p5[i]: " << RAA_D0_pt3p5to4p5[i] << endl;
		RAA_D0_pt3p5to4p5_errordata_yl[i] = D0_fonll_raa_errordata[3-i]->GetErrorYlow(0);
		RAA_D0_pt3p5to4p5_errordata_yh[i] = D0_fonll_raa_errordata[3-i]->GetErrorYhigh(0);
		RAA_D0_pt3p5to4p5_errorfonll_yl[i] = D0_fonll_raa_errorfonll[3-i]->GetErrorYlow(0);
		RAA_D0_pt3p5to4p5_errorfonll_yh[i] = D0_fonll_raa_errorfonll[3-i]->GetErrorYhigh(0);
		RAA_D0_pt3p5to4p5_errorsys_yl[i] = D0_fonll_raa_errorsys[3-i]->GetErrorYlow(0);
		RAA_D0_pt3p5to4p5_errorsys_yh[i] = D0_fonll_raa_errorsys[3-i]->GetErrorYhigh(0);
		
		RAA_D0_pt4p5to7[i] = D0_fonll_raa_errordata[3-i]->GetY()[1];
		RAA_D0_pt4p5to7_errordata_yl[i] = D0_fonll_raa_errordata[3-i]->GetErrorYlow(1);
		RAA_D0_pt4p5to7_errordata_yh[i] = D0_fonll_raa_errordata[3-i]->GetErrorYhigh(1);
		RAA_D0_pt4p5to7_errorfonll_yl[i] = D0_fonll_raa_errorfonll[3-i]->GetErrorYlow(1);
		RAA_D0_pt4p5to7_errorfonll_yh[i] = D0_fonll_raa_errorfonll[3-i]->GetErrorYhigh(1);
		RAA_D0_pt4p5to7_errorsys_yl[i] = D0_fonll_raa_errorsys[3-i]->GetErrorYlow(1);
		RAA_D0_pt4p5to7_errorsys_yh[i] = D0_fonll_raa_errorsys[3-i]->GetErrorYhigh(1);

		RAA_D0_pt7to11[i] = D0_fonll_raa_errordata[3-i]->GetY()[2];
		RAA_D0_pt7to11_errordata_yl[i] = D0_fonll_raa_errordata[3-i]->GetErrorYlow(2);
		RAA_D0_pt7to11_errordata_yh[i] = D0_fonll_raa_errordata[3-i]->GetErrorYhigh(2);
		RAA_D0_pt7to11_errorfonll_yl[i] = D0_fonll_raa_errorfonll[3-i]->GetErrorYlow(2);
		RAA_D0_pt7to11_errorfonll_yh[i] = D0_fonll_raa_errorfonll[3-i]->GetErrorYhigh(2);
		RAA_D0_pt7to11_errorsys_yl[i] = D0_fonll_raa_errorsys[3-i]->GetErrorYlow(2);
		RAA_D0_pt7to11_errorsys_yh[i] = D0_fonll_raa_errorsys[3-i]->GetErrorYhigh(2);

		RAA_D0_pt11to16[i] = D0_fonll_raa_errordata[3-i]->GetY()[3];
		RAA_D0_pt11to16_errordata_yl[i] = D0_fonll_raa_errordata[3-i]->GetErrorYlow(3);
		RAA_D0_pt11to16_errordata_yh[i] = D0_fonll_raa_errordata[3-i]->GetErrorYhigh(3);
		RAA_D0_pt11to16_errorfonll_yl[i] = D0_fonll_raa_errorfonll[3-i]->GetErrorYlow(3);
		RAA_D0_pt11to16_errorfonll_yh[i] = D0_fonll_raa_errorfonll[3-i]->GetErrorYhigh(3);
		RAA_D0_pt11to16_errorsys_yl[i] = D0_fonll_raa_errorsys[3-i]->GetErrorYlow(3);
		RAA_D0_pt11to16_errorsys_yh[i] = D0_fonll_raa_errorsys[3-i]->GetErrorYhigh(3);

		RAA_D0_pt16to28[i] = D0_fonll_raa_errordata[3-i]->GetY()[4];
		RAA_D0_pt16to28_errordata_yl[i] = D0_fonll_raa_errordata[3-i]->GetErrorYlow(4);
		RAA_D0_pt16to28_errordata_yh[i] = D0_fonll_raa_errordata[3-i]->GetErrorYhigh(4);
		RAA_D0_pt16to28_errorfonll_yl[i] = D0_fonll_raa_errorfonll[3-i]->GetErrorYlow(4);
		RAA_D0_pt16to28_errorfonll_yh[i] = D0_fonll_raa_errorfonll[3-i]->GetErrorYhigh(4);
		RAA_D0_pt16to28_errorsys_yl[i] = D0_fonll_raa_errorsys[3-i]->GetErrorYlow(4);
		RAA_D0_pt16to28_errorsys_yh[i] = D0_fonll_raa_errorsys[3-i]->GetErrorYhigh(4);
	}


	TGraphAsymmErrors * RAA_D0_pt3p5to4p5_errordata_Npart = new TGraphAsymmErrors( 4, Npart_pt3p5to4p5, RAA_D0_pt3p5to4p5, Npart_error, Npart_error, RAA_D0_pt3p5to4p5_errordata_yl, RAA_D0_pt3p5to4p5_errordata_yh);
    TGraphAsymmErrors * RAA_D0_pt3p5to4p5_errorfonll_Npart = new TGraphAsymmErrors( 4, Npart_pt3p5to4p5, RAA_D0_pt3p5to4p5, Npart_error, Npart_error, RAA_D0_pt3p5to4p5_errorfonll_yl, RAA_D0_pt3p5to4p5_errorfonll_yh);
    TGraphAsymmErrors * RAA_D0_pt3p5to4p5_errorsys_Npart = new TGraphAsymmErrors( 4, Npart_pt3p5to4p5, RAA_D0_pt3p5to4p5, Npart_error, Npart_error, RAA_D0_pt3p5to4p5_errorsys_yl, RAA_D0_pt3p5to4p5_errorsys_yh);

	TGraphAsymmErrors * RAA_D0_pt4p5to7_errordata_Npart = new TGraphAsymmErrors( 4, Npart_pt4p5to7, RAA_D0_pt4p5to7, Npart_error, Npart_error, RAA_D0_pt4p5to7_errordata_yl, RAA_D0_pt4p5to7_errordata_yh);
    TGraphAsymmErrors * RAA_D0_pt4p5to7_errorfonll_Npart = new TGraphAsymmErrors( 4, Npart_pt4p5to7, RAA_D0_pt4p5to7, Npart_error, Npart_error, RAA_D0_pt4p5to7_errorfonll_yl, RAA_D0_pt4p5to7_errorfonll_yh);
    TGraphAsymmErrors * RAA_D0_pt4p5to7_errorsys_Npart = new TGraphAsymmErrors( 4, Npart_pt4p5to7, RAA_D0_pt4p5to7, Npart_error, Npart_error, RAA_D0_pt4p5to7_errorsys_yl, RAA_D0_pt4p5to7_errorsys_yh);

	TGraphAsymmErrors * RAA_D0_pt7to11_errordata_Npart = new TGraphAsymmErrors( 4, Npart_pt7to11, RAA_D0_pt7to11, Npart_error, Npart_error, RAA_D0_pt7to11_errordata_yl, RAA_D0_pt7to11_errordata_yh);
    TGraphAsymmErrors * RAA_D0_pt7to11_errorfonll_Npart = new TGraphAsymmErrors( 4, Npart_pt7to11, RAA_D0_pt7to11, Npart_error, Npart_error, RAA_D0_pt7to11_errorfonll_yl, RAA_D0_pt7to11_errorfonll_yh);
    TGraphAsymmErrors * RAA_D0_pt7to11_errorsys_Npart = new TGraphAsymmErrors( 4, Npart_pt7to11, RAA_D0_pt7to11, Npart_error, Npart_error, RAA_D0_pt7to11_errorsys_yl, RAA_D0_pt7to11_errorsys_yh);

	TGraphAsymmErrors * RAA_D0_pt11to16_errordata_Npart = new TGraphAsymmErrors( 4, Npart_pt11to16, RAA_D0_pt11to16, Npart_error, Npart_error, RAA_D0_pt11to16_errordata_yl, RAA_D0_pt11to16_errordata_yh);
    TGraphAsymmErrors * RAA_D0_pt11to16_errorfonll_Npart = new TGraphAsymmErrors( 4, Npart_pt11to16, RAA_D0_pt11to16, Npart_error, Npart_error, RAA_D0_pt11to16_errorfonll_yl, RAA_D0_pt11to16_errorfonll_yh);
    TGraphAsymmErrors * RAA_D0_pt11to16_errorsys_Npart = new TGraphAsymmErrors( 4, Npart_pt11to16, RAA_D0_pt11to16, Npart_error, Npart_error, RAA_D0_pt11to16_errorsys_yl, RAA_D0_pt11to16_errorsys_yh);

	TGraphAsymmErrors * RAA_D0_pt16to28_errordata_Npart = new TGraphAsymmErrors( 4, Npart_pt16to28, RAA_D0_pt16to28, Npart_error, Npart_error, RAA_D0_pt16to28_errordata_yl, RAA_D0_pt16to28_errordata_yh);
    TGraphAsymmErrors * RAA_D0_pt16to28_errorfonll_Npart = new TGraphAsymmErrors( 4, Npart_pt16to28, RAA_D0_pt16to28, Npart_error, Npart_error, RAA_D0_pt16to28_errorfonll_yl, RAA_D0_pt16to28_errorfonll_yh);
    TGraphAsymmErrors * RAA_D0_pt16to28_errorsys_Npart = new TGraphAsymmErrors( 4, Npart_pt16to28, RAA_D0_pt16to28, Npart_error, Npart_error, RAA_D0_pt16to28_errorsys_yl, RAA_D0_pt16to28_errorsys_yh);


//	TCanvas * D0_RAFONLL_Npart = new TCanvas("D0_RAFONLL_Npart","D0_RAFONLL_Npart", 600, 700);
//    TPad *pad1 = new TPad("pad1","top pad",0.0,0.2,1.0,1.0);
//	pad1->Draw();
//	TPad *pad2 = new TPad("pad2","bottom pad",0.0,0.0,1.0,0.2);
//	pad2->Draw();
//    pad1->cd();
    TCanvas * D0_RAFONLL_Npart = new TCanvas("D0_RAFONLL_Npart","D0_RAFONLL_Npart", 600, 600);

	RAA_D0_pt4p5to7_errorsys_Npart->GetYaxis()->SetRangeUser(0, 2.5);
	RAA_D0_pt4p5to7_errorsys_Npart->GetYaxis()->SetTitle("D^{0} R^{FONLL}_{AA}");
	RAA_D0_pt4p5to7_errorsys_Npart->GetXaxis()->SetLimits(0, 451);
	RAA_D0_pt4p5to7_errorsys_Npart->GetXaxis()->SetTitle("N_{part}");
	RAA_D0_pt4p5to7_errorsys_Npart->SetFillStyle(1001);
	RAA_D0_pt4p5to7_errorsys_Npart->SetFillColor(15);
	RAA_D0_pt4p5to7_errorsys_Npart->SetLineColor(15);
    RAA_D0_pt4p5to7_errorsys_Npart->Draw("A2");

	RAA_D0_pt4p5to7_errorfonll_Npart->SetFillColor(0);
	RAA_D0_pt4p5to7_errorfonll_Npart->SetFillStyle(0);
	RAA_D0_pt4p5to7_errorfonll_Npart->SetLineColor(1.0);
	RAA_D0_pt4p5to7_errorfonll_Npart->Draw("2");

	RAA_D0_pt4p5to7_errordata_Npart->SetFillStyle(1001);
	RAA_D0_pt4p5to7_errordata_Npart->SetFillColor(15);
	RAA_D0_pt4p5to7_errordata_Npart->SetLineColor(15);
	RAA_D0_pt4p5to7_errordata_Npart->SetMarkerStyle(20);
	RAA_D0_pt4p5to7_errordata_Npart->SetMarkerSize(1.0);
	RAA_D0_pt4p5to7_errordata_Npart->SetLineColor(1.0);
	RAA_D0_pt4p5to7_errordata_Npart->SetMarkerColor(1.0);
	RAA_D0_pt4p5to7_errordata_Npart->Draw("P");

	RAA_D0_pt3p5to4p5_errorsys_Npart->SetFillStyle(1001);
	RAA_D0_pt3p5to4p5_errorsys_Npart->SetFillColor(kMagenta-9);
	RAA_D0_pt3p5to4p5_errorsys_Npart->SetLineColor(kMagenta-9);
    RAA_D0_pt3p5to4p5_errorsys_Npart->Draw("2");
	
	RAA_D0_pt3p5to4p5_errorfonll_Npart->GetYaxis()->SetRangeUser(0, 2);
	RAA_D0_pt3p5to4p5_errorfonll_Npart->GetYaxis()->SetTitle("D^{0} R^{FONLL}_{AA}");
	RAA_D0_pt3p5to4p5_errorfonll_Npart->GetXaxis()->SetRangeUser(0, 450);
	RAA_D0_pt3p5to4p5_errorfonll_Npart->GetXaxis()->SetTitle("N_{part}");
	RAA_D0_pt3p5to4p5_errorfonll_Npart->SetFillColor(0);
	RAA_D0_pt3p5to4p5_errorfonll_Npart->SetFillStyle(0);
	RAA_D0_pt3p5to4p5_errorfonll_Npart->SetLineColor(6.0);
	RAA_D0_pt3p5to4p5_errorfonll_Npart->Draw("2");

	RAA_D0_pt3p5to4p5_errordata_Npart->SetFillStyle(1001);
	RAA_D0_pt3p5to4p5_errordata_Npart->SetFillColor(kMagenta-9);
	RAA_D0_pt3p5to4p5_errordata_Npart->SetLineColor(kMagenta-9);
	RAA_D0_pt3p5to4p5_errordata_Npart->SetMarkerStyle(21);
	RAA_D0_pt3p5to4p5_errordata_Npart->SetMarkerSize(1.0);
	RAA_D0_pt3p5to4p5_errordata_Npart->SetLineColor(6.0);
	RAA_D0_pt3p5to4p5_errordata_Npart->SetMarkerColor(6.0);
	RAA_D0_pt3p5to4p5_errordata_Npart->Draw("P");


	RAA_D0_pt7to11_errorsys_Npart->SetFillStyle(1001);
	RAA_D0_pt7to11_errorsys_Npart->SetFillColor(kBlue-9);
	RAA_D0_pt7to11_errorsys_Npart->SetLineColor(kBlue-9);
    RAA_D0_pt7to11_errorsys_Npart->Draw("2");
	
	RAA_D0_pt7to11_errorfonll_Npart->GetYaxis()->SetRangeUser(0, 2);
	RAA_D0_pt7to11_errorfonll_Npart->GetYaxis()->SetTitle("D^{0} R^{FONLL}_{AA}");
	RAA_D0_pt7to11_errorfonll_Npart->GetXaxis()->SetRangeUser(0, 450);
	RAA_D0_pt7to11_errorfonll_Npart->GetXaxis()->SetTitle("N_{part}");
	RAA_D0_pt7to11_errorfonll_Npart->SetFillColor(0);
	RAA_D0_pt7to11_errorfonll_Npart->SetFillStyle(0);
	RAA_D0_pt7to11_errorfonll_Npart->SetLineColor(4.0);
	RAA_D0_pt7to11_errorfonll_Npart->Draw("2");

	RAA_D0_pt7to11_errordata_Npart->SetFillStyle(1001);
	RAA_D0_pt7to11_errordata_Npart->SetFillColor(kBlue-7);
	RAA_D0_pt7to11_errordata_Npart->SetLineColor(kBlue-7);
	RAA_D0_pt7to11_errordata_Npart->SetMarkerStyle(22);
	RAA_D0_pt7to11_errordata_Npart->SetMarkerSize(1.0);
	RAA_D0_pt7to11_errordata_Npart->SetLineColor(4.0);
	RAA_D0_pt7to11_errordata_Npart->SetMarkerColor(4.0);
	RAA_D0_pt7to11_errordata_Npart->Draw("P");

	RAA_D0_pt11to16_errorsys_Npart->SetFillStyle(1001);
	RAA_D0_pt11to16_errorsys_Npart->SetFillColor(kRed-7);
	RAA_D0_pt11to16_errorsys_Npart->SetLineColor(kRed-7);
    RAA_D0_pt11to16_errorsys_Npart->Draw("2");
	
	RAA_D0_pt11to16_errorfonll_Npart->GetYaxis()->SetRangeUser(0, 2);
	RAA_D0_pt11to16_errorfonll_Npart->GetYaxis()->SetTitle("D^{0} R^{FONLL}_{AA}");
	RAA_D0_pt11to16_errorfonll_Npart->GetXaxis()->SetRangeUser(0, 450);
	RAA_D0_pt11to16_errorfonll_Npart->GetXaxis()->SetTitle("N_{part}");
	RAA_D0_pt11to16_errorfonll_Npart->SetFillColor(0);
	RAA_D0_pt11to16_errorfonll_Npart->SetFillStyle(0);
	RAA_D0_pt11to16_errorfonll_Npart->SetLineColor(2.0);
	RAA_D0_pt11to16_errorfonll_Npart->Draw("2");

	RAA_D0_pt11to16_errordata_Npart->SetFillStyle(1001);
	RAA_D0_pt11to16_errordata_Npart->SetFillColor(kRed-7);
	RAA_D0_pt11to16_errordata_Npart->SetLineColor(kRed-7);
	RAA_D0_pt11to16_errordata_Npart->SetMarkerStyle(24);
	RAA_D0_pt11to16_errordata_Npart->SetMarkerSize(1.0);
	RAA_D0_pt11to16_errordata_Npart->SetLineColor(2.0);
	RAA_D0_pt11to16_errordata_Npart->SetMarkerColor(2.0);
	RAA_D0_pt11to16_errordata_Npart->Draw("P");
	

	RAA_D0_pt16to28_errorsys_Npart->SetFillStyle(1001);
	RAA_D0_pt16to28_errorsys_Npart->SetFillColor(kCyan-7);
	RAA_D0_pt16to28_errorsys_Npart->SetLineColor(kCyan-7);
    RAA_D0_pt16to28_errorsys_Npart->Draw("2");
	
	RAA_D0_pt16to28_errorfonll_Npart->GetYaxis()->SetRangeUser(0, 2);
	RAA_D0_pt16to28_errorfonll_Npart->GetYaxis()->SetTitle("D^{0} R^{FONLL}_{AA}");
	RAA_D0_pt16to28_errorfonll_Npart->GetXaxis()->SetRangeUser(0, 450);
	RAA_D0_pt16to28_errorfonll_Npart->GetXaxis()->SetTitle("N_{part}");
	RAA_D0_pt16to28_errorfonll_Npart->SetFillColor(0);
	RAA_D0_pt16to28_errorfonll_Npart->SetFillStyle(0);
	RAA_D0_pt16to28_errorfonll_Npart->SetLineColor(kCyan+2);
	RAA_D0_pt16to28_errorfonll_Npart->Draw("2");

	RAA_D0_pt16to28_errordata_Npart->SetFillStyle(1001);
	RAA_D0_pt16to28_errordata_Npart->SetFillColor(kCyan-7);
	RAA_D0_pt16to28_errordata_Npart->SetLineColor(kCyan-7);
	RAA_D0_pt16to28_errordata_Npart->SetMarkerStyle(25);
	RAA_D0_pt16to28_errordata_Npart->SetMarkerSize(1.0);
	RAA_D0_pt16to28_errordata_Npart->SetLineColor(kCyan+2);
	RAA_D0_pt16to28_errordata_Npart->SetMarkerColor(kCyan+2);
	RAA_D0_pt16to28_errordata_Npart->Draw("P");

	TF1 * fun = new TF1("fun", "1.0", 0, 500);
	fun->SetLineColor(1.0);
	fun->SetLineStyle(3);
	fun->SetLineWidth(0.1);
	fun->Draw("same");

    TBox *a = new TBox(410,1-0.112,420,1+0.112);
    a->SetLineColor(kGray);
    a->SetFillColor(kGray);
    a->Draw();

    TBox *b = new TBox(420,1-0.094,430,1+0.094);
    b->SetLineColor(kGray);
    b->SetFillColor(kGray);
    b->Draw();

    TBox *c = new TBox(430,1-0.058,440,1+0.058);
    c->SetLineColor(kGray);
    c->SetFillColor(kGray);
    c->Draw();

    TBox *d = new TBox(440,1-0.045,450,1+0.045);
    d->SetLineColor(kGray);
    d->SetFillColor(kGray);
    d->Draw();
    
	TLegend * t = new TLegend(0.5, 0.6, 0.85, 0.85);
	t->SetFillColor(0);
	t->AddEntry(RAA_D0_pt3p5to4p5_errordata_Npart, "3.5 < p_{T} < 4.5 GeV/c", "PLF");
	t->AddEntry(RAA_D0_pt4p5to7_errordata_Npart, "4.5 < p_{T} < 7.0 GeV/c", "PLF");
	t->AddEntry(RAA_D0_pt7to11_errordata_Npart, "7.0 < p_{T} < 11.0 GeV/c", "PLF");
    t->AddEntry(RAA_D0_pt11to16_errordata_Npart, "11.0 < p_{T} < 16.0 GeV/c", "PLF");
    t->AddEntry(RAA_D0_pt16to28_errordata_Npart, "16.0 < p_{T} < 28.0 GeV/c", "PLF");
	t->AddEntry(d, "Syst. TAA+BR", "F");
	t->Draw();

    TLatex Tl;
    Tl.SetNDC();
    Tl.SetTextAlign(12);
    Tl.SetTextSize(0.03);
    Tl.DrawLatex(0.16,0.60, "50-100%");
    Tl.DrawLatex(0.27,0.54, "30-50%");
    Tl.DrawLatex(0.46,0.42, "10-30%");
	Tl.DrawLatex(0.68,0.37, "0-10%");
//
//	pad2->cd();
//	double errorsys_TAAfraction[4] = {1.0, 1.0, 1.0, 1.0};
//	double errorsys_TAAfraction_yl[4] = { 0.112, 0.094, 0.058, 0.045};
//	double errorsys_TAAfraction_yh[4] = { 0.112, 0.094, 0.058, 0.045};
//	TGraphAsymmErrors * errorsys_TAAfraction_Npart = new TGraphAsymmErrors( 4, Npart_pt7to11, errorsys_TAAfraction, Npart_error, Npart_error, errorsys_TAAfraction_yl, errorsys_TAAfraction_yh );
//	errorsys_TAAfraction_Npart->SetLineColor(kGray);
//	errorsys_TAAfraction_Npart->SetFillColor(kGray);
//	errorsys_TAAfraction_Npart->GetYaxis()->SetRangeUser(0.85, 1.15);
//	errorsys_TAAfraction_Npart->GetXaxis()->SetTitle("N_{part}");
//	errorsys_TAAfraction_Npart->GetYaxis()->SetTitleSize(0.08);
//	errorsys_TAAfraction_Npart->GetYaxis()->SetLabelSize(0.08);
//	errorsys_TAAfraction_Npart->GetXaxis()->SetTitleSize(0.08);
//	errorsys_TAAfraction_Npart->GetXaxis()->SetLabelSize(0.08);
//    errorsys_TAAfraction_Npart->GetXaxis()->SetTitleOffset(0.6);
//	errorsys_TAAfraction_Npart->Draw("A2");
//
//

	D0_RAFONLL_Npart->SaveAs("results/D0_RAFONLL_Npart_cent0103050100_pt3p54p57112028.png");
	D0_RAFONLL_Npart->SaveAs("results/D0_RAFONLL_Npart_cent0103050100_pt3p54p57112028.pdf");
}
