#define NPTBIN 3

double pp_FONLL_center_1ptbin16to28 = 14607.3;
double pp_FONLL_errorupper_1ptbin16to28 = 3229.35;
double pp_FONLL_errorlower_1ptbin16to28 = 2521.43;

void pp_data_drivenreference_y1_ptbin3()
{
    gStyle->SetOptTitle(0);
    gStyle->SetOptStat(0);
    gStyle->SetOptFit(0);
    TH1::SetDefaultSumw2();

	double ptcenter_3ptbin[NPTBIN] = {4.75, 12.0, 22.0};
	double pterror_3ptbin[NPTBIN] = {3.25, 4.0, 6.0};
	double pp_datadriven_center_3ptbin[NPTBIN]={49.5843,0.429788, 0.0};
	double pp_datadriven_errorupper_3ptbin[NPTBIN]={21.5434,0.102472, 0.0};
	double pp_datadriven_errorlower_3ptbin[NPTBIN]={19.4404,0.104179, 0.0};

	for( int i = 0; i < NPTBIN; i++ )
	{
		pp_datadriven_center_3ptbin[i] = pp_datadriven_center_3ptbin[i] * 1E6;
		pp_datadriven_errorupper_3ptbin[i] = pp_datadriven_errorupper_3ptbin[i] * 1E6;
		pp_datadriven_errorlower_3ptbin[i] = pp_datadriven_errorlower_3ptbin[i] * 1E6;
	}

    pp_datadriven_center_3ptbin[2] = pp_FONLL_center_1ptbin16to28;
	pp_datadriven_errorupper_3ptbin[2] = pp_FONLL_errorupper_1ptbin16to28;
	pp_datadriven_errorlower_3ptbin[2] = pp_FONLL_errorlower_1ptbin16to28;

//	for( int i = 2; i < NPTBIN; i++ )
//	{
//		pp_datadriven_center_3ptbin[i] = d0fonllspectrum->GetY()[i];
//		pp_datadriven_errorupper_3ptbin[i] = d0fonllspectrum->GetErrorYhigh(i);
//		pp_datadriven_errorlower_3ptbin[i] = d0fonllspectrum->GetErrorYlow(i);
//	}

	for( int i = 0; i < NPTBIN; i++ )
	{
		cout << " pt center: " << ptcenter_3ptbin[i] << endl;
		cout << "central: " << pp_datadriven_center_3ptbin[i] << "  upper error: " << pp_datadriven_errorupper_3ptbin[i] << "  lower error: " << pp_datadriven_errorlower_3ptbin[i] << endl;
	}

	TGraphAsymmErrors* gaeSigmaDzero = new TGraphAsymmErrors(NPTBIN, ptcenter_3ptbin, pp_datadriven_center_3ptbin, pterror_3ptbin, pterror_3ptbin, pp_datadriven_errorlower_3ptbin, pp_datadriven_errorupper_3ptbin);
	gaeSigmaDzero->SetName("gaeSigmaDzero");

    TGraph* gaeSigmaDzero_center = new TGraph(NPTBIN, ptcenter_3ptbin, pp_datadriven_center_3ptbin);
    gaeSigmaDzero_center->SetName("gaeSigmaDzero_center");

    TCanvas * cfg_ptbin7 = new TCanvas("cfg_ptbin7", "cfg_ptbin7");
    gPad->SetLogy();
    gaeSigmaDzero->GetXaxis()->SetRangeUser(1.5,40);
    gaeSigmaDzero->GetYaxis()->SetRangeUser(1e2, 1e9);
    gaeSigmaDzero->GetYaxis()->SetTitle("d#sigma/dp_{T}(D^{0}) (pb/(GeV/c))");
    gaeSigmaDzero->GetXaxis()->SetTitle("p_{T} (GeV/c)");
    gaeSigmaDzero->SetLineColor(1.0);
    gaeSigmaDzero->SetMarkerSize(1.0);
    gaeSigmaDzero->SetMarkerStyle(22);
    gaeSigmaDzero->SetMarkerColor(1.0);
    gaeSigmaDzero->SetFillColor(0);
    gaeSigmaDzero->SetFillStyle(0);
    gaeSigmaDzero->Draw("a2");
    gaeSigmaDzero_center->SetMarkerStyle(22);
    gaeSigmaDzero_center->SetMarkerSize(1.0);
    gaeSigmaDzero_center->SetMarkerColor(1.0);
    gaeSigmaDzero_center->SetLineColor(1.0);
    gaeSigmaDzero_center->Draw("psame");

	cfg_ptbin7->SaveAs("ppreference/ppdatadrivenplusFONLL_3ptbin_y1.png");
	cfg_ptbin7->SaveAs("ppreference/ppdatadrivenplusFONLL_3ptbin_y1.pdf");

	TFile * output = new TFile("ppdatadrivenplusFONLL_3ptbin_y1.root","RECREATE");

	gaeSigmaDzero->Write();
	gaeSigmaDzero_center->Write();
	cfg_ptbin7->Write();

	output->Close();

}
