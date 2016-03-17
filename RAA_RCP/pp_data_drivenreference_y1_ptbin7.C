#define NPTBIN 7

void pp_data_drivenreference_y1_ptbin7()
{
    gStyle->SetOptTitle(0);
    gStyle->SetOptStat(0);
    gStyle->SetOptFit(0);
    TH1::SetDefaultSumw2();

	double ptcenter_7ptbin[NPTBIN] = {2.0, 3.0, 4.0, 5.75, 9.0, 13.5, 22.0};
	double pterror_7ptbin[NPTBIN] = {0.5, 0.5, 0.5, 1.25, 2.0, 2.5, 6.0};
//	
//	reference w/o scale errors
//	double pp_datadriven_center_7ptbin[NPTBIN]={179.582, 72.0524, 30.9477, 9.22383, 1.31836, 0.156899, 0.0};
//	double pp_datadriven_errorupper_7ptbin[NPTBIN]={48.3617, 16.8263, 6.59188, 1.86227, 0.238972, 0.0590557, 0.0};
//	double pp_datadriven_errorlower_7ptbin[NPTBIN]={84.0442, 25.0686, 9.04093, 2.29724, 0.251336, 0.0615574, 0.0};
//
	double pp_datadriven_center_7ptbin[NPTBIN]={191.417,85.7596, 34.7843, 9.70763, 1.29304, 0.159842, 0.0};
	double pp_datadriven_errorupper_7ptbin[NPTBIN]={103.348,28.5619, 9.10257, 2.30885, 0.315551, 0.0446278, 0.0};
	double pp_datadriven_errorlower_7ptbin[NPTBIN]={92.0822,26.1409, 8.84569, 2.33445, 0.316003, 0.0449567 , 0.0};

	for( int i = 0; i < NPTBIN; i++ )
	{
		pp_datadriven_center_7ptbin[i] = pp_datadriven_center_7ptbin[i] * 1E6;
		pp_datadriven_errorupper_7ptbin[i] = pp_datadriven_errorupper_7ptbin[i] * 1E6;
		pp_datadriven_errorlower_7ptbin[i] = pp_datadriven_errorlower_7ptbin[i] * 1E6;
	}

	TFile * fonllinput = new TFile("./../FONLL/fonll/outputDzero_y1_7ptbin_1p5to28.root");
	TGraphAsymmErrors * d0fonllspectrum = ( TGraphAsymmErrors *) fonllinput->Get("gaeSigmaDzero");
	d0fonllspectrum->SetName("d0fonllspectrum");

	for( int i = 6; i < NPTBIN; i++ )
	{
		pp_datadriven_center_7ptbin[i] = d0fonllspectrum->GetY()[i];
		pp_datadriven_errorupper_7ptbin[i] = d0fonllspectrum->GetErrorYhigh(i);
		pp_datadriven_errorlower_7ptbin[i] = d0fonllspectrum->GetErrorYlow(i);
	}

	for( int i = 0; i < NPTBIN; i++ )
	{
		cout << " pt center: " << ptcenter_7ptbin[i] << endl;
		cout << "central: " << pp_datadriven_center_7ptbin[i] << "  upper error: " << pp_datadriven_errorupper_7ptbin[i] << "  lower error: " << pp_datadriven_errorlower_7ptbin[i] << endl;
	}

	TGraphAsymmErrors* gaeSigmaDzero = new TGraphAsymmErrors(NPTBIN, ptcenter_7ptbin, pp_datadriven_center_7ptbin, pterror_7ptbin, pterror_7ptbin, pp_datadriven_errorlower_7ptbin, pp_datadriven_errorupper_7ptbin);
	gaeSigmaDzero->SetName("gaeSigmaDzero");

    TGraph* gaeSigmaDzero_center = new TGraph(NPTBIN, ptcenter_7ptbin, pp_datadriven_center_7ptbin);
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


	cfg_ptbin7->SaveAs("ppreference/ppdatadrivenplusFONLL_7ptbin_y1.png");
	cfg_ptbin7->SaveAs("ppreference/ppdatadrivenplusFONLL_7ptbin_y1.pdf");

	TFile * output = new TFile("ppdatadrivenplusFONLL_7ptbin_y1.root","RECREATE");

	gaeSigmaDzero->Write();
    gaeSigmaDzero_center->Write();
	cfg_ptbin7->Write();

	output->Close();

}
