#define NPTBIN 5

void pp_data_drivenreference_y2_ptbin5()
{
    gStyle->SetOptTitle(0);
    gStyle->SetOptStat(0);
    gStyle->SetOptFit(0);
    TH1::SetDefaultSumw2();

	double ptcenter_5ptbin[NPTBIN] = {4.0, 5.75, 9.0, 13.5, 22.0};
	double pterror_5ptbin[NPTBIN] = {0.5, 1.25, 2.0, 2.5, 6.0};
	double pp_datadriven_center_5ptbin[NPTBIN]={ 58.4216, 17.197, 2.38221, 0.268003, 0.0};
	double pp_datadriven_errorupper_5ptbin[NPTBIN]={ 12.3951, 3.45295, 0.432109, 0.104685, 0.0};
	double pp_datadriven_errorlower_5ptbin[NPTBIN]={17.0025, 4.26132, 0.454407, 0.109164, 0.0};

	for( int i = 0; i < NPTBIN; i++ )
	{
		pp_datadriven_center_5ptbin[i] = pp_datadriven_center_5ptbin[i] * 1E6;
		pp_datadriven_errorupper_5ptbin[i] = pp_datadriven_errorupper_5ptbin[i] * 1E6;
		pp_datadriven_errorlower_5ptbin[i] = pp_datadriven_errorlower_5ptbin[i] * 1E6;
	}

	TFile * fonllinput = new TFile("./../FONLL/fonll/outputDzero_5ptbin_3p5to28.root");
	TGraphAsymmErrors * d0fonllspectrum = ( TGraphAsymmErrors *) fonllinput->Get("gaeSigmaDzero");
	d0fonllspectrum->SetName("d0fonllspectrum");

	for( int i = 4; i < NPTBIN; i++ )
	{
		pp_datadriven_center_5ptbin[i] = d0fonllspectrum->GetY()[i];
		pp_datadriven_errorupper_5ptbin[i] = d0fonllspectrum->GetErrorYhigh(i);
		pp_datadriven_errorlower_5ptbin[i] = d0fonllspectrum->GetErrorYlow(i);
	}

	for( int i = 0; i < NPTBIN; i++ )
	{
		cout << "central: " << pp_datadriven_center_5ptbin[i] << "  upper error: " << pp_datadriven_errorupper_5ptbin[i] << "  lower error: " << pp_datadriven_errorlower_5ptbin[i] << endl;
	}

	TGraphAsymmErrors* gaeSigmaDzero = new TGraphAsymmErrors(NPTBIN, ptcenter_5ptbin, pp_datadriven_center_5ptbin, pterror_5ptbin, pterror_5ptbin, pp_datadriven_errorlower_5ptbin, pp_datadriven_errorupper_5ptbin);

	gaeSigmaDzero->SetName("gaeSigmaDzero");

    TCanvas * cfg_ptbin5 = new TCanvas("cfg_ptbin5", "cfg_ptbin5");
    gPad->SetLogy();
    gaeSigmaDzero->GetXaxis()->SetRangeUser(3.5,40);
    gaeSigmaDzero->GetYaxis()->SetRangeUser(1e3, 2e8);
    gaeSigmaDzero->GetYaxis()->SetTitle("d#sigma/dp_{T}(D^{0}) (pb/(GeV/c))");
    gaeSigmaDzero->GetXaxis()->SetTitle("p_{T} (GeV/c)");
    gaeSigmaDzero->SetLineColor(1.0);
    gaeSigmaDzero->SetMarkerSize(1.0);
    gaeSigmaDzero->SetMarkerStyle(20);
    gaeSigmaDzero->SetMarkerColor(1.0);
    gaeSigmaDzero->Draw("ap");

	cfg_ptbin5->SaveAs("ppreference/ppdatadrivenplusFONLL_5ptbin_y2.png");
	cfg_ptbin5->SaveAs("ppreference/ppdatadrivenplusFONLL_5ptbin_y2.pdf");

	TFile * output = new TFile("ppdatadrivenplusFONLL_5ptbin_y2.root","RECREATE");

	gaeSigmaDzero->Write();
	cfg_ptbin5->Write();

	output->Close();

}
