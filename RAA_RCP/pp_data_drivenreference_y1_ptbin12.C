#define NPTBIN 12

void pp_data_drivenreference_y1_ptbin12()
{
    gStyle->SetOptTitle(0);
    gStyle->SetOptStat(0);
    gStyle->SetOptFit(0);
    TH1::SetDefaultSumw2();

	double ptcenter_12ptbin[NPTBIN] = {2,3,4,5,6.25,8,10,12,14.5,18,24,34};
	double pterror_12ptbin[NPTBIN] = {0.5,0.5,0.5,0.5,0.75,1,1,1,1.5,2,4,6};

	double pp_datadriven_center_12ptbin[NPTBIN]={ 191.417,85.7596, 34.7843, 15.1563, 6.07516, 1.95426, 0.631821, 0.248857, 0.100499, 0.0, 0.0, 0.0};
	double pp_datadriven_errorupper_12ptbin[NPTBIN]={ 103.348,28.5619, 9.10257, 3.63179, 1.42693, 0.488216, 0.143002, 0.0646319, 0.0313346, 0.0, 0.0, 0.0};
	double pp_datadriven_errorlower_12ptbin[NPTBIN]={ 92.0822,26.1409, 8.84569, 3.68539, 1.43391, 0.486217, 0.145856, 0.0653744, 0.0313829, 0.0, 0.0, 0.0};


	for( int i = 0; i < NPTBIN; i++ )
	{
		pp_datadriven_center_12ptbin[i] = pp_datadriven_center_12ptbin[i] * 1E6;
		pp_datadriven_errorupper_12ptbin[i] = pp_datadriven_errorupper_12ptbin[i] * 1E6;
		pp_datadriven_errorlower_12ptbin[i] = pp_datadriven_errorlower_12ptbin[i] * 1E6;
	}

	TFile * fonllinput = new TFile("./../FONLL/fonll/outputDzero_y1.root");
	TGraphAsymmErrors * d0fonllspectrum = ( TGraphAsymmErrors *) fonllinput->Get("gaeSigmaDzero");
	d0fonllspectrum->SetName("d0fonllspectrum");

	for( int i = 9; i < NPTBIN; i++ )
	{
		pp_datadriven_center_12ptbin[i] = d0fonllspectrum->GetY()[i];
		pp_datadriven_errorupper_12ptbin[i] = d0fonllspectrum->GetErrorYhigh(i);
		pp_datadriven_errorlower_12ptbin[i] = d0fonllspectrum->GetErrorYlow(i);
	}

	for( int i = 0; i < NPTBIN; i++ )
	{
		cout << "central: " << pp_datadriven_center_12ptbin[i] << "  upper error: " << pp_datadriven_errorupper_12ptbin[i] << "  lower error: " << pp_datadriven_errorlower_12ptbin[i] << endl;
	}

	TGraphAsymmErrors* gaeSigmaDzero = new TGraphAsymmErrors(NPTBIN, ptcenter_12ptbin, pp_datadriven_center_12ptbin, pterror_12ptbin, pterror_12ptbin, pp_datadriven_errorlower_12ptbin, pp_datadriven_errorupper_12ptbin);
	gaeSigmaDzero->SetName("gaeSigmaDzero");

	TGraph* gaeSigmaDzero_center = new TGraph(NPTBIN, ptcenter_12ptbin, pp_datadriven_center_12ptbin);
    gaeSigmaDzero_center->SetName("gaeSigmaDzero_center");

    TCanvas * cfg_ptbin12 = new TCanvas("cfg_ptbin12", "cfg_ptbin12");
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

	cfg_ptbin12->SaveAs("ppreference/ppdatadrivenplusFONLL_12ptbin_y1.png");
	cfg_ptbin12->SaveAs("ppreference/ppdatadrivenplusFONLL_12ptbin_y1.pdf");

	TFile * output = new TFile("ppdatadrivenplusFONLL_12ptbin_y1.root","RECREATE");

	gaeSigmaDzero->Write();
    gaeSigmaDzero_center->Write();
	cfg_ptbin12->Write();

	output->Close();

}
