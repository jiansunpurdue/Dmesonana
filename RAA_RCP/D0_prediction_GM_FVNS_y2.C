#define NPT 10

double x_pt[NPT] = {4,5,6.25,8,10,12,14.5,18,24,34};
double error_pt[NPT] = {0.5,0.5,0.75,1,1,1,1.5,2,4,6};
double y_xsection[NPT] = { 0.8044E+05, 0.3229E+05, 0.1275E+05, 0.4310E+04, 0.1519E+04, 0.6179E+03, 0.2468E+03, 0.8283E+02, 0.2006E+02, 0.3003E+01};
double y_maxxsection[NPT] = { 0.1194E+06, 0.4462E+05, 0.1650E+05, 0.5270E+04, 0.1801E+04, 0.7158E+03, 0.2821E+03, 0.9344E+02, 0.2257E+02, 0.3343E+01};
double y_minxsection[NPT] = { 0.4321E+05, 0.2177E+05, 0.9708E+04, 0.3460E+04, 0.1232E+04, 0.5077E+03, 0.2048E+03, 0.6935E+02, 0.1690E+02, 0.2553E+01};
double error_y_high[NPT];
double error_y_low[NPT];

void D0_prediction_GM_FVNS_y2()
{
    gStyle->SetOptTitle(0);
    gStyle->SetOptStat(0);

	for( int ipt = 0; ipt < NPT; ipt++ )
	{
		y_xsection[ipt] = y_xsection[ipt] * 1000;
		y_maxxsection[ipt] = y_maxxsection[ipt] * 1000;
		y_minxsection[ipt] = y_minxsection[ipt] * 1000;
	}

	for( int ipt = 0; ipt < NPT; ipt++ )
	{
		error_y_high[ipt] = y_maxxsection[ipt] - y_xsection[ipt];
		error_y_low[ipt] = y_xsection[ipt] - y_minxsection[ipt];
	}

	TGraphAsymmErrors* gaeSigmaDzero_GM_FVNS_ptbin10 = new TGraphAsymmErrors(NPT, x_pt, y_xsection, error_pt, error_pt, error_y_low, error_y_high);
	gaeSigmaDzero_GM_FVNS_ptbin10->SetTitle("gaeSigmaDzero_GM_FVNS_ptbin10");
	gaeSigmaDzero_GM_FVNS_ptbin10->SetName("gaeSigmaDzero_GM_FVNS_ptbin10");

    TCanvas * cfg_ptbin10 = new TCanvas("cfg_ptbin10", "cfg_ptbin10");
	gPad->SetLogy();
	gaeSigmaDzero_GM_FVNS_ptbin10->GetXaxis()->SetRangeUser(3.5,40);
	gaeSigmaDzero_GM_FVNS_ptbin10->GetYaxis()->SetRangeUser(1e3, 2e8);
	gaeSigmaDzero_GM_FVNS_ptbin10->GetYaxis()->SetTitle("d#sigma/dp_{T}(D^{0}) (pb/(GeV/c))");
	gaeSigmaDzero_GM_FVNS_ptbin10->GetXaxis()->SetTitle("p_{T} (GeV/c)");
	gaeSigmaDzero_GM_FVNS_ptbin10->SetLineColor(2.0);
    gaeSigmaDzero_GM_FVNS_ptbin10->SetMarkerSize(1.0);
    gaeSigmaDzero_GM_FVNS_ptbin10->SetMarkerStyle(20);
    gaeSigmaDzero_GM_FVNS_ptbin10->SetMarkerColor(2.0);
    gaeSigmaDzero_GM_FVNS_ptbin10->Draw("ap");

	cfg_ptbin10->SaveAs("ppreference/D0_prompt_GM_FVNS_ptbin10.png");
	cfg_ptbin10->SaveAs("ppreference/D0_prompt_GM_FVNS_ptbin10.pdf");

	double x_pt_ptbin5[5] = {4.0, 5.75, 9.0, 13.5, 22.0};
	double error_pt_ptbin5[5] = {0.5, 1.25, 2.0, 2.5, 6.0};
	double y_xsection_ptbin5[5];
	double y_maxxsection_ptbin5[5];
	double y_minxsection_ptbin5[5];
	double error_y_high_ptbin5[5];
	double error_y_low_ptbin5[5];

	y_xsection_ptbin5[0] = y_xsection[0];
	y_maxxsection_ptbin5[0] = y_maxxsection[0];
	y_minxsection_ptbin5[0] = y_minxsection[0];

	y_xsection_ptbin5[1] = ( y_xsection[1] * error_pt[1] + y_xsection[2] * error_pt[2] ) / error_pt_ptbin5[1];
	y_maxxsection_ptbin5[1] = ( y_maxxsection[1] * error_pt[1] + y_maxxsection[2] * error_pt[2] ) / error_pt_ptbin5[1];
	y_minxsection_ptbin5[1] = ( y_minxsection[1] * error_pt[1] + y_minxsection[2] * error_pt[2] ) / error_pt_ptbin5[1];

	y_xsection_ptbin5[2] = ( y_xsection[3] * error_pt[3] + y_xsection[4] * error_pt[4] ) / error_pt_ptbin5[2];
	y_maxxsection_ptbin5[2] = ( y_maxxsection[3] * error_pt[3] + y_maxxsection[4] * error_pt[4] ) / error_pt_ptbin5[2];
	y_minxsection_ptbin5[2] = ( y_minxsection[3] * error_pt[3] + y_minxsection[4] * error_pt[4] ) / error_pt_ptbin5[2];

	y_xsection_ptbin5[3] = ( y_xsection[5] * error_pt[5] + y_xsection[6] * error_pt[6] ) / error_pt_ptbin5[3];
	y_maxxsection_ptbin5[3] = ( y_maxxsection[5] * error_pt[5] + y_maxxsection[6] * error_pt[6] ) / error_pt_ptbin5[3];
	y_minxsection_ptbin5[3] = ( y_minxsection[5] * error_pt[5] + y_minxsection[6] * error_pt[6] ) / error_pt_ptbin5[3];

	y_xsection_ptbin5[4] = ( y_xsection[7] * error_pt[7] + y_xsection[8] * error_pt[8] ) / error_pt_ptbin5[4];
	y_maxxsection_ptbin5[4] = ( y_maxxsection[7] * error_pt[7] + y_maxxsection[8] * error_pt[8] ) / error_pt_ptbin5[4];
	y_minxsection_ptbin5[4] = ( y_minxsection[7] * error_pt[7] + y_minxsection[8] * error_pt[8] ) / error_pt_ptbin5[4];

	for( int ipt = 0; ipt < 5; ipt++ )
	{
		error_y_high_ptbin5[ipt] = y_maxxsection_ptbin5[ipt] - y_xsection_ptbin5[ipt];
		error_y_low_ptbin5[ipt] = y_xsection_ptbin5[ipt] - y_minxsection_ptbin5[ipt];
	}

	TGraphAsymmErrors* gaeSigmaDzero_GM_FVNS_ptbin5 = new TGraphAsymmErrors(5, x_pt_ptbin5, y_xsection_ptbin5, error_pt_ptbin5, error_pt_ptbin5, error_y_low_ptbin5, error_y_high_ptbin5);
	gaeSigmaDzero_GM_FVNS_ptbin5->SetTitle("gaeSigmaDzero_GM_FVNS_ptbin5");
	gaeSigmaDzero_GM_FVNS_ptbin5->SetName("gaeSigmaDzero_GM_FVNS_ptbin5");

    TCanvas * cfg_ptbin5 = new TCanvas("cfg_ptbin5", "cfg_ptbin5");
	gPad->SetLogy();
	gaeSigmaDzero_GM_FVNS_ptbin5->GetXaxis()->SetRangeUser(3.5,40);
	gaeSigmaDzero_GM_FVNS_ptbin5->GetYaxis()->SetRangeUser(1e3, 2e9);
	gaeSigmaDzero_GM_FVNS_ptbin5->GetYaxis()->SetTitle("d#sigma/dp_{T}(D^{0}) (pb/(GeV/c))");
	gaeSigmaDzero_GM_FVNS_ptbin5->GetXaxis()->SetTitle("p_{T} (GeV/c)");
	gaeSigmaDzero_GM_FVNS_ptbin5->SetLineColor(2.0);
    gaeSigmaDzero_GM_FVNS_ptbin5->SetMarkerSize(1.0);
    gaeSigmaDzero_GM_FVNS_ptbin5->SetMarkerStyle(20);
    gaeSigmaDzero_GM_FVNS_ptbin5->SetMarkerColor(2.0);
    gaeSigmaDzero_GM_FVNS_ptbin5->Draw("ap");

	cfg_ptbin5->SaveAs("ppreference/D0_prompt_GM_FVNS_ptbin5.png");
	cfg_ptbin5->SaveAs("ppreference/D0_prompt_GM_FVNS_ptbin5.pdf");

	TFile * output = new TFile("D0_prediction_GM_FVNS_y2.root","RECREATE");

	gaeSigmaDzero_GM_FVNS_ptbin10->Write();
	gaeSigmaDzero_GM_FVNS_ptbin5->Write();
	cfg_ptbin10->Write();
	cfg_ptbin5->Write();

	output->Close();

}
