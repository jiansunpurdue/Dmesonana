#define NPTBIN 10

void pp_data_drivenreference_y2_ptbin10()
{
    gStyle->SetOptTitle(0);
    gStyle->SetOptStat(0);
    gStyle->SetOptFit(0);
    TH1::SetDefaultSumw2();

	double ptcenter_10ptbin[NPTBIN] = {4,5,6.25,8,10,12,14.5,18,24,34};
	double pterror_10ptbin[NPTBIN] = {0.5,0.5,0.75,1,1,1,1.5,2,4,6};
	double pp_datadriven_center_10ptbin[NPTBIN]={58.4216, 26.5102, 10.9882, 3.61137, 1.15305, 0.431998, 0.158673, 0.0, 0.0, 0.0};
	double pp_datadriven_errorupper_10ptbin[NPTBIN]={12.3951, 5.40727, 2.15007, 0.589692, 0.274527, 0.168376, 0.0622249, 0.0, 0.0, 0.0};
	double pp_datadriven_errorlower_10ptbin[NPTBIN]={17.0025, 6.93686, 2.47762, 0.614296, 0.294518, 0.178671, 0.0628251, 0.0, 0.0, 0.0};

	for( int i = 0; i < NPTBIN; i++ )
	{
		pp_datadriven_center_10ptbin[i] = pp_datadriven_center_10ptbin[i] * 1E6;
		pp_datadriven_errorupper_10ptbin[i] = pp_datadriven_errorupper_10ptbin[i] * 1E6;
		pp_datadriven_errorlower_10ptbin[i] = pp_datadriven_errorlower_10ptbin[i] * 1E6;
	}

	TFile * fonllinput = new TFile("./../FONLL/fonll/outputDzero.root");
	TGraphAsymmErrors * d0fonllspectrum = ( TGraphAsymmErrors *) fonllinput->Get("gaeSigmaDzero");
	d0fonllspectrum->SetName("d0fonllspectrum");

	for( int i = 7; i < NPTBIN; i++ )
	{
		pp_datadriven_center_10ptbin[i] = d0fonllspectrum->GetY()[i];
		pp_datadriven_errorupper_10ptbin[i] = d0fonllspectrum->GetErrorYhigh(i);
		pp_datadriven_errorlower_10ptbin[i] = d0fonllspectrum->GetErrorYlow(i);
	}

	for( int i = 0; i < NPTBIN; i++ )
	{
		cout << "central: " << pp_datadriven_center_10ptbin[i] << "  upper error: " << pp_datadriven_errorupper_10ptbin[i] << "  lower error: " << pp_datadriven_errorlower_10ptbin[i] << endl;
	}

	TGraphAsymmErrors* gaeSigmaDzero = new TGraphAsymmErrors(NPTBIN, ptcenter_10ptbin, pp_datadriven_center_10ptbin, pterror_10ptbin, pterror_10ptbin, pp_datadriven_errorlower_10ptbin, pp_datadriven_errorupper_10ptbin);

	gaeSigmaDzero->SetName("gaeSigmaDzero");

    TCanvas * cfg_ptbin10 = new TCanvas("cfg_ptbin10", "cfg_ptbin10");
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

	cfg_ptbin10->SaveAs("ppreference/ppdatadrivenplusFONLL_10ptbin_y2.png");
	cfg_ptbin10->SaveAs("ppreference/ppdatadrivenplusFONLL_10ptbin_y2.pdf");

	TFile * output = new TFile("ppdatadrivenplusFONLL_10ptbin_y2.root","RECREATE");

	gaeSigmaDzero->Write();
	cfg_ptbin10->Write();

	output->Close();

}
