#define NPTBIN 12

void pp_data_drivenreference_y1_ptbin12()
{
    gStyle->SetOptTitle(0);
    gStyle->SetOptStat(0);
    gStyle->SetOptFit(0);
    TH1::SetDefaultSumw2();

	double ptcenter_12ptbin[NPTBIN] = {2,3,4,5,6.25,8,10,12,14.5,18,24,34};
	double pterror_12ptbin[NPTBIN] = {0.5,0.5,0.5,0.5,0.75,1,1,1,1.5,2,4,6};
	double pp_datadriven_center_12ptbin[NPTBIN]={179.582, 72.0524, 30.9477, 14.1575, 5.93471, 1.9866, 0.650123, 0.250053, 0.0947958, 0.0, 0.0, 0.0};
	double pp_datadriven_errorupper_12ptbin[NPTBIN]={48.3617, 16.8263, 6.59188, 2.90461, 1.16738, 0.325029, 0.152915, 0.0942528, 0.035591, 0.0, 0.0, 0.0};
	double pp_datadriven_errorlower_12ptbin[NPTBIN]={84.0442, 25.0686, 9.04093, 3.72568, 1.34496, 0.338623, 0.16405, 0.0999921, 0.0359343, 0.0, 0.0, 0.0};

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

    TCanvas * cfg_ptbin12 = new TCanvas("cfg_ptbin12", "cfg_ptbin12");
    gPad->SetLogy();
    gaeSigmaDzero->GetXaxis()->SetRangeUser(1.5,40);
    gaeSigmaDzero->GetYaxis()->SetRangeUser(1e2, 1e9);
    gaeSigmaDzero->GetYaxis()->SetTitle("d#sigma/dp_{T}(D^{0}) (pb/(GeV/c))");
    gaeSigmaDzero->GetXaxis()->SetTitle("p_{T} (GeV/c)");
    gaeSigmaDzero->SetLineColor(1.0);
    gaeSigmaDzero->SetMarkerSize(1.0);
    gaeSigmaDzero->SetMarkerStyle(20);
    gaeSigmaDzero->SetMarkerColor(1.0);
    gaeSigmaDzero->Draw("ap");

	cfg_ptbin12->SaveAs("ppreference/ppdatadrivenplusFONLL_12ptbin_y1.png");
	cfg_ptbin12->SaveAs("ppreference/ppdatadrivenplusFONLL_12ptbin_y1.pdf");

	TFile * output = new TFile("ppdatadrivenplusFONLL_12ptbin_y1.root","RECREATE");

	gaeSigmaDzero->Write();
	cfg_ptbin12->Write();

	output->Close();

}
