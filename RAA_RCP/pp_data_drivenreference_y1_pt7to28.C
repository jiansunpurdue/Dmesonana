#define NPTBIN 1

double pp_datadriven_center_1ptbin7to16[NPTBIN]={ 0.673106e6};
double pp_datadriven_errorupper_1ptbin7to16[NPTBIN]={ 0.139017e6};
double pp_datadriven_errorlower_1ptbin7to16[NPTBIN]={ 0.145902e6};

double pp_FONLL_center_1ptbin16to28[NPTBIN]={ 14607.3 };
double pp_FONLL_errorupper_1ptbin16to28[NPTBIN]={ 3229.35 };
double pp_FONLL_errorlower_1ptbin16to28[NPTBIN]={ 2521.43 };


void pp_data_drivenreference_y1_pt7to28()
{
    gStyle->SetOptTitle(0);
    gStyle->SetOptStat(0);
    gStyle->SetOptFit(0);
    TH1::SetDefaultSumw2();

	double ptcenter_1ptbin7to28[NPTBIN] = { 17.5 };
	double pterror_1ptbin7to28[NPTBIN] = { 10.5 };
	double pp_datadriven_center_1ptbin7to28[NPTBIN]={0.0};
	double pp_datadriven_errorupper_1ptbin7to28[NPTBIN]={0.0};
	double pp_datadriven_errorlower_1ptbin7to28[NPTBIN]={0.0};

	pp_datadriven_center_1ptbin7to28[0] = ( pp_datadriven_center_1ptbin7to16[0] * 9 + pp_FONLL_center_1ptbin16to28[0] * 12 ) / 21;
	pp_datadriven_errorupper_1ptbin7to28[0] = ( pp_datadriven_errorupper_1ptbin7to16[0] * 9 + pp_FONLL_errorupper_1ptbin16to28[0] * 12 ) / 21;
	pp_datadriven_errorlower_1ptbin7to28[0] = ( pp_datadriven_errorlower_1ptbin7to16[0] * 9 + pp_FONLL_errorlower_1ptbin16to28[0] * 12 ) / 21;

	
	for( int i = 0; i < NPTBIN; i++ )
	{
		cout << "central: " << pp_datadriven_center_1ptbin7to28[i] << "  upper error: " << pp_datadriven_errorupper_1ptbin7to28[i] << "  lower error: " << pp_datadriven_errorlower_1ptbin7to28[i] << endl;
	}

	TGraphAsymmErrors* gaeSigmaDzero = new TGraphAsymmErrors(NPTBIN, ptcenter_1ptbin7to28, pp_datadriven_center_1ptbin7to28, pterror_1ptbin7to28, pterror_1ptbin7to28, pp_datadriven_errorlower_1ptbin7to28, pp_datadriven_errorupper_1ptbin7to28);

	gaeSigmaDzero->SetName("gaeSigmaDzero");

    TCanvas * cfg_ptbin7 = new TCanvas("cfg_ptbin7", "cfg_ptbin7");
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

	cfg_ptbin7->SaveAs("ppreference/ppdatadrivenplusFONLL_1ptbin7to28_y1.png");
	cfg_ptbin7->SaveAs("ppreference/ppdatadrivenplusFONLL_1ptbin7to28_y1.pdf");

	TFile * output = new TFile("ppdatadrivenplusFONLL_1ptbin7to28_y1.root","RECREATE");

	gaeSigmaDzero->Write();
	cfg_ptbin7->Write();

	output->Close();

}
