//
//systematics for differenct centrality and pt bins
double syserrorPer_upper_ptbin12_cent0to100[12] = { 0.180, 0.182, 0.183, 0.179, 0.178, 0.177, 0.177, 0.174, 0.173, 0.172, 0.194, 0.238};
double syserrorPer_lower_ptbin12_cent0to100[12] = { 0.180, 0.182, 0.183, 0.179, 0.178, 0.177, 0.177, 0.174, 0.173, 0.172, 0.194, 0.238};

double syserrorPer_upper_ptbin12_cent0to10[12] = { 0.217, 0.244, 0.236, 0.253, 0.254, 0.227, 0.224, 0.212, 0.211, 0.210, 0.209, 0.343}; //last bin to be updated
double syserrorPer_lower_ptbin12_cent0to10[12] = { 0.217, 0.244, 0.236, 0.253, 0.254, 0.227, 0.224, 0.212, 0.211, 0.210, 0.209, 0.343};

double syserrorPer_upper_ptbin12_cent0to20[12] = { 0.232, 0.217, 0.237, 0.233, 0.234, 0.216, 0.210, 0.202, 0.201, 0.221, 0.221, 0.306};
double syserrorPer_lower_ptbin12_cent0to20[12] = { 0.232, 0.217, 0.237, 0.233, 0.234, 0.216, 0.210, 0.202, 0.201, 0.221, 0.221, 0.306};

double syserrorPer_upper_ptbin7_cent0to10[7] = { 0.217, 0.244, 0.236, 0.256, 0.226, 0.211, 0.210};
double syserrorPer_lower_ptbin7_cent0to10[7] = { 0.217, 0.244, 0.236, 0.256, 0.226, 0.211, 0.210};

double syserrorPer_upper_ptbin7_cent10to30[7] = { 0.222, 0.203, 0.239, 0.212, 0.202, 0.193, 0.219};
double syserrorPer_lower_ptbin7_cent10to30[7] = { 0.222, 0.203, 0.239, 0.212, 0.202, 0.193, 0.219};

double syserrorPer_upper_ptbin7_cent30to50[7] = { 0.148, 0.162, 0.155, 0.145, 0.142, 0.136, 0.134};
double syserrorPer_lower_ptbin7_cent30to50[7] = { 0.148, 0.162, 0.155, 0.145, 0.142, 0.136, 0.134};

double syserrorPer_upper_ptbin7_cent50to100[7] = { 0.259, 0.165, 0.157, 0.146, 0.144, 0.140, 0.260};
double syserrorPer_lower_ptbin7_cent50to100[7] = { 0.259, 0.165, 0.157, 0.146, 0.144, 0.140, 0.260};

double syserrorPer_upper_ptbin3_cent0to10[3] = { 0., 0.190, 0.};
double syserrorPer_lower_ptbin3_cent0to10[3] = { 0., 0.190, 0.};

double syserrorPer_upper_ptbin3_cent10to20[3] = { 0., 0.185, 0.};
double syserrorPer_lower_ptbin3_cent10to20[3] = { 0., 0.185, 0.};

double syserrorPer_upper_ptbin3_cent20to30[3] = { 0., 0.183, 0.};
double syserrorPer_lower_ptbin3_cent20to30[3] = { 0., 0.183, 0.};

double syserrorPer_upper_ptbin3_cent30to40[3] = { 0., 0.126, 0.};
double syserrorPer_lower_ptbin3_cent30to40[3] = { 0., 0.126, 0.};

double syserrorPer_upper_ptbin3_cent40to50[3] = { 0., 0.124, 0.};
double syserrorPer_lower_ptbin3_cent40to50[3] = { 0., 0.124, 0.};

double syserrorPer_upper_ptbin3_cent50to100[3] = { 0., 0.124, 0.};
double syserrorPer_lower_ptbin3_cent50to100[3] = { 0., 0.124, 0.};

double RAA_cent50to100[7] = { 999.0, 0.702351, 0.750395, 0.722585, 0.634087, 0.877874, 0.833067};

double *syserrorPer_upper;
double *syserrorPer_lower;
double syserror_Per_FONLL = 4.1e-2;

#define ERROR_BR_PERCEN 0.013


//#define NPT  12
//double ptbins[NPT+1] = {0,1.5,2.5,3.5,4.5,5.5,7,9,11,13,16,20,28,40,100};


void Draw_RAFONLL( TFile * input_pbpb, TFile * fonllinput, int cent_low, int cent_high, int Nptbin, double TAA, double syserrorPerTAA)
{
	gStyle->SetOptTitle(0);
	gStyle->SetOptStat(0);
	TH1::SetDefaultSumw2();
	syserrorPer_upper =  new double[Nptbin];
	syserrorPer_lower =  new double[Nptbin];

	cout << " Nptbin: " << Nptbin << "   cent_low: " << cent_low << "  cent_high: " << cent_high << endl;

	for( int i = 0; i < Nptbin; i++ )
	{
		syserrorPer_upper[i] = 0.00;
		syserrorPer_lower[i] = 0.00;
	}

	if( Nptbin == 12 && cent_low == 0 && cent_high == 100 )
	{
		for( int i = 0; i < Nptbin; i++ )
		{
			syserrorPer_upper[i] = syserrorPer_upper_ptbin12_cent0to100[i];
			syserrorPer_lower[i] = syserrorPer_lower_ptbin12_cent0to100[i];
		}
	}

	if( Nptbin == 12 && cent_low == 0 && cent_high == 10 )
	{
		for( int i = 0; i < Nptbin; i++ )
		{
			syserrorPer_upper[i] = syserrorPer_upper_ptbin12_cent0to10[i];
			syserrorPer_lower[i] = syserrorPer_lower_ptbin12_cent0to10[i];
		}
	}

	if( Nptbin == 12 && cent_low == 0 && cent_high == 20 )
	{
		for( int i = 0; i < Nptbin; i++ )
		{
			syserrorPer_upper[i] = syserrorPer_upper_ptbin12_cent0to20[i];
			syserrorPer_lower[i] = syserrorPer_lower_ptbin12_cent0to20[i];
		}
	}

	if( Nptbin == 7 && cent_low == 0 && cent_high == 10 )
	{
		for( int i = 0; i < Nptbin; i++ )
		{
			syserrorPer_upper[i] = syserrorPer_upper_ptbin7_cent0to10[i];
			syserrorPer_lower[i] = syserrorPer_lower_ptbin7_cent0to10[i];
		 }
	}

	if( Nptbin == 7 && cent_low == 10 && cent_high == 30 )
	{
		for( int i = 0; i < Nptbin; i++ )
		{
			syserrorPer_upper[i] = syserrorPer_upper_ptbin7_cent10to30[i];
			syserrorPer_lower[i] = syserrorPer_lower_ptbin7_cent10to30[i];
		}
	}

	if( Nptbin == 7 && cent_low == 30 && cent_high == 50 )
	{
		for( int i = 0; i < Nptbin; i++ )
		{
			syserrorPer_upper[i] = syserrorPer_upper_ptbin7_cent30to50[i];
			syserrorPer_lower[i] = syserrorPer_lower_ptbin7_cent30to50[i];
		}
	}

	if( Nptbin == 7 && cent_low == 50 && cent_high == 100 )
	{
		for( int i = 0; i < Nptbin; i++ )
		{
			syserrorPer_upper[i] = syserrorPer_upper_ptbin7_cent50to100[i];
			syserrorPer_lower[i] = syserrorPer_lower_ptbin7_cent50to100[i];
		}
	}

	if( Nptbin == 3 && cent_low == 0 && cent_high == 10 )
	{
        for( int i = 0; i < Nptbin; i++ )
        {
			syserrorPer_upper[i] = syserrorPer_upper_ptbin3_cent0to10[i];
			syserrorPer_lower[i] = syserrorPer_lower_ptbin3_cent0to10[i];
		}
	}


	if( Nptbin == 3 && cent_low == 10 && cent_high == 20 )
	{
		for( int i = 0; i < Nptbin; i++ )
		{
			syserrorPer_upper[i] = syserrorPer_upper_ptbin3_cent10to20[i];
			syserrorPer_lower[i] = syserrorPer_lower_ptbin3_cent10to20[i];
		}
	}


	if( Nptbin == 3 && cent_low == 20 && cent_high == 30 )
	{
		for( int i = 0; i < Nptbin; i++ )
		{
			syserrorPer_upper[i] = syserrorPer_upper_ptbin3_cent20to30[i];
			syserrorPer_lower[i] = syserrorPer_lower_ptbin3_cent20to30[i];
		}
	}


	if( Nptbin == 3 && cent_low == 30 && cent_high == 40 )
	{
		for( int i = 0; i < Nptbin; i++ )
		{
			syserrorPer_upper[i] = syserrorPer_upper_ptbin3_cent30to40[i];
			syserrorPer_lower[i] = syserrorPer_lower_ptbin3_cent30to40[i];
		}
	}


	if( Nptbin == 3 && cent_low == 40 && cent_high == 50 )
	{
		for( int i = 0; i < Nptbin; i++ )
		{
			syserrorPer_upper[i] = syserrorPer_upper_ptbin3_cent40to50[i];
			syserrorPer_lower[i] = syserrorPer_lower_ptbin3_cent40to50[i];
		}
	}


	if( Nptbin == 3 && cent_low == 50 && cent_high == 100 )
	{
		for( int i = 0; i < Nptbin; i++ )
		{
			syserrorPer_upper[i] = syserrorPer_upper_ptbin3_cent50to100[i];
			syserrorPer_lower[i] = syserrorPer_lower_ptbin3_cent50to100[i];
		}
	}

	TH1D * D0Spectrum_pbpb = ( TH1D *) input_pbpb->Get("d0raw_data_overeff");
	TH1D * D0_pbpb_spectrum = ( TH1D * ) D0Spectrum_pbpb->Clone("D0_pbpb_spectrum");

	D0_pbpb_spectrum->Scale(1.0/TAA);
	
	if( Nptbin == 7)   
	{
		D0_pbpb_spectrum->SetBinContent(D0_pbpb_spectrum->FindBin(35), -999);
	    D0_pbpb_spectrum->SetBinError(D0_pbpb_spectrum->FindBin(35), 0);
		D0_pbpb_spectrum->GetYaxis()->SetRangeUser(2.0, 25);
	}

	TGraphAsymmErrors * d0referencespectrum = ( TGraphAsymmErrors *) fonllinput->Get("gaeSigmaDzero");
	TGraph* d0referencespectrum_center = ( TGraphAsymmErrors *) fonllinput->Get("gaeSigmaDzero_center");
	d0referencespectrum->SetName("d0referencespectrum");
	d0referencespectrum_center->SetName("d0referencespectrum_center");

    cout << "!!!!!!!!!!!!!removing first bin!!!!!!!!!!!!!!!!" << endl;
	D0_pbpb_spectrum->SetBinContent(D0_pbpb_spectrum->FindBin(2.0), 10e25);
	D0_pbpb_spectrum->SetBinError(D0_pbpb_spectrum->FindBin(2.0), 0);
	d0referencespectrum->GetY()[0] = 10e15;
	d0referencespectrum_center->GetY()[0] = 10e15;
	cout << "!!!!!!!!!!!!!removing first bin!!!!!!!!!!!!!!!!" << endl;

	TCanvas * spectrum = new TCanvas("spectrum","spectrum",610,600);
	spectrum->SetLeftMargin(0.2);
	gPad->SetLogy();


	TGraphAsymmErrors * D0_pbpb_spectrum_syserror = ( TGraphAsymmErrors *) d0referencespectrum->Clone("D0_pbpb_spectrum_syserror");

	for( int i = 0; i < D0_pbpb_spectrum_syserror->GetN(); i++ )
	{
		double error_Per_lower = syserrorPer_lower[i]; 
		double error_Per_upper = syserrorPer_upper[i];
		double binvalue = D0_pbpb_spectrum->GetBinContent(i+2);
//		cout << " binvalue : " << binvalue << "  error_Per_lower: " << error_Per_lower << "   error_Per_upper: " << error_Per_upper << endl;
		D0_pbpb_spectrum_syserror->GetY()[i] = binvalue;
		D0_pbpb_spectrum_syserror->SetPointEYhigh(i, error_Per_upper*binvalue);
		D0_pbpb_spectrum_syserror->SetPointEYlow(i, error_Per_lower*binvalue);
//		cout << " error_Per_upper*binvalue: " << error_Per_upper*binvalue << "   error_Per_lower*binvalue: " << error_Per_lower*binvalue << endl;
	}


	D0_pbpb_spectrum_syserror->GetYaxis()->SetRangeUser(1E2,1E9);
	D0_pbpb_spectrum_syserror->GetXaxis()->SetRangeUser(0.0,40);
	if( Nptbin == 7 ) D0_pbpb_spectrum_syserror->GetXaxis()->SetRangeUser(0.0,28);
    D0_pbpb_spectrum_syserror->GetYaxis()->SetTitleOffset(2.0);
    D0_pbpb_spectrum_syserror->GetYaxis()->SetTitle("#frac{d#sigma_{pp}}{dp_{T}}, #frac{1}{T_{AA}} #frac{dN_{PbPb}}{dp_{T}} #frac{pb}{GeV/c}");
	D0_pbpb_spectrum_syserror->GetXaxis()->SetTitle("p_{T} (GeV/c)");
    D0_pbpb_spectrum_syserror->SetFillColor(5.0);
	D0_pbpb_spectrum_syserror->SetLineColor(5.0);
	D0_pbpb_spectrum_syserror->SetFillStyle(1001);
	D0_pbpb_spectrum_syserror->Draw("A2");

    D0_pbpb_spectrum->SetFillColor(5.0);
	D0_pbpb_spectrum->SetFillStyle(1001);
	D0_pbpb_spectrum->SetMarkerStyle(20);
	D0_pbpb_spectrum->SetMarkerColor(2.0);
	D0_pbpb_spectrum->SetLineColor(2.0);
	D0_pbpb_spectrum->DrawCopy("epsame");
	
	d0referencespectrum->SetLineWidth(0.5);
	d0referencespectrum->SetMarkerStyle(22);
	d0referencespectrum->SetMarkerSize(1.0);
    d0referencespectrum->SetFillColor(0);
    d0referencespectrum->SetFillStyle(0);
    d0referencespectrum->Draw("2same");

	TGraph * d0referencespectrum_center_dataextraref = ( TGraph * ) d0referencespectrum_center->Clone("d0referencespectrum_center_dataextraref");
	d0referencespectrum_center_dataextraref->SetName("d0referencespectrum_center_dataextraref");

	for( int i = 0; i < d0referencespectrum_center_dataextraref->GetN(); i++ )
    {
		if( d0referencespectrum_center_dataextraref->GetX()[i] > 16.0 )
		{
			d0referencespectrum_center_dataextraref->GetX()[i] = -999;

		}
	}
	
	d0referencespectrum_center_dataextraref->Draw("Psame");

	TGraph * d0referencespectrum_center_FONLLref = ( TGraph * ) d0referencespectrum_center->Clone("d0referencespectrum_center_FONLLref");
	d0referencespectrum_center_FONLLref->SetName("d0referencespectrum_center_FONLLref");

	for( int i = 0; i < d0referencespectrum_center_FONLLref->GetN(); i++ )
    {
		if( d0referencespectrum_center_FONLLref->GetX()[i] < 16.0 )
		{
			d0referencespectrum_center_FONLLref->GetX()[i] = -999;

		}
	}
 
    d0referencespectrum_center_FONLLref->SetMarkerStyle(26);
	d0referencespectrum_center_FONLLref->Draw("Psame");
	
	D0_pbpb_spectrum->DrawCopy("epsame"); // draw again to uncover the error bars

    TLatex Ts;
    Ts.SetNDC();
    Ts.SetTextAlign(12);
    Ts.SetTextSize(0.04);
	Ts.SetTextFont(42);
    Ts.DrawLatex(0.20,0.93, "#scale[1.25]{CMS} Preliminary");
	Ts.DrawLatex(0.53,0.93, "PbPb #sqrt{s_{NN}} = 2.76 TeV");
    Ts.DrawLatex(0.40,0.85, "|y| < 1.0");

	TLegend * t = new TLegend(0.35, 0.65, 0.85, 0.80);
	t->SetFillColor(0);
	t->SetTextSize(0.04);
	t->AddEntry( D0_pbpb_spectrum, Form("PbPb, Cent. %d-%d%%", cent_low, cent_high));
	t->AddEntry(d0referencespectrum, "pp Reference", "PF");
	t->Draw();

    TLatex Treference;
    Treference.SetNDC();
    Treference.SetTextAlign(12);
    Treference.SetTextSize(0.028);
	Treference.SetTextFont(42);
    Treference.DrawLatex(0.37,0.63, "Filled markers: data-extrapolated reference");
    Treference.DrawLatex(0.37,0.60, "Open markers: FONLL reference");

	TCanvas * raadmeson = new TCanvas("raadmeson","raadmeson");
	TH1D * D0_pbpb_spectrum_raa = ( TH1D *) D0_pbpb_spectrum->Clone("D0_pbpb_spectrum_raa");
	TGraphAsymmErrors * D0_fonll_raa_errordata = ( TGraphAsymmErrors *) d0referencespectrum->Clone("D0_fonll_raa_errordata");
	TGraphAsymmErrors * D0_fonll_raa_errorfonll = ( TGraphAsymmErrors *) d0referencespectrum->Clone("D0_fonll_raa_errorfonll");
	D0_fonll_raa_errordata->SetMarkerStyle(20);
	D0_fonll_raa_errorfonll->SetMarkerStyle(20);

//	D0_fonll_raa_errordata->SetLineColor(1.0);
//	D0_fonll_raa_errordata->SetMarkerColor(2.0);
//	D0_fonll_raa_errorfonll->SetLineColor(1.0);
//	D0_fonll_raa_errorfonll->SetMarkerColor(2.0);

	for( int i = 0; i < D0_fonll_raa_errordata->GetN();i++){
		cout << endl;
		D0_fonll_raa_errordata->GetY()[i] = D0_pbpb_spectrum_raa->GetBinContent(i+2) / d0referencespectrum->GetY()[i];
		cout << "PbPb: " << D0_pbpb_spectrum_raa->GetBinContent(i+2) << " pp: " << d0referencespectrum->GetY()[i] << " RAA: " << D0_fonll_raa_errordata->GetY()[i] << endl;
//        cout << "Pbbin spectrum: " << D0_pbpb_spectrum_raa->GetBinContent(i+2) << endl;
        double higherror = D0_pbpb_spectrum_raa->GetBinError(i+2)/d0referencespectrum->GetY()[i];
		double lowerror = D0_pbpb_spectrum_raa->GetBinError(i+2)/d0referencespectrum->GetY()[i];
		D0_fonll_raa_errordata->SetPointEYhigh(i, higherror);
		D0_fonll_raa_errordata->SetPointEYlow(i, lowerror);

        D0_fonll_raa_errorfonll->GetY()[i] = D0_pbpb_spectrum_raa->GetBinContent(i+2) / d0referencespectrum->GetY()[i];
		
//		cout <<"Relative statistical error" << higherror/D0_fonll_raa_errordata->GetY()[i] << endl;
        
		double errorPer_low_fonll = d0referencespectrum->GetErrorYlow(i)/d0referencespectrum->GetY()[i];
		double errorPer_high_fonll = d0referencespectrum->GetErrorYhigh(i)/d0referencespectrum->GetY()[i];

		//add systematic from braching ratio
		double toterrorPer_low_fonll = TMath::Sqrt(syserror_Per_FONLL*syserror_Per_FONLL + errorPer_low_fonll*errorPer_low_fonll);
		double  toterrorPer_high_fonll = TMath::Sqrt(syserror_Per_FONLL*syserror_Per_FONLL + errorPer_high_fonll*errorPer_high_fonll);

//        cout << "FONLL calculation, center value: " <<  d0referencespectrum->GetY()[i] << " Percentage error, lower: " << errorPer_high_fonll << " Percentage error, upper: " << errorPer_low_fonll << endl;
//		cout << "FONLL total Per error, lower: " << toterrorPer_high_fonll << "   upper: " << toterrorPer_low_fonll << endl;


       if( d0referencespectrum ->GetX()[i] > 16.0 )
	   {
//		   cout << "!!!!!!!!!!!!!!!!!!! error with lower and upper limit from pp reference!!!!!!!!!!" << endl;
		   higherror = toterrorPer_low_fonll / (1. - toterrorPer_low_fonll ) * D0_fonll_raa_errordata->GetY()[i];
		   lowerror = toterrorPer_high_fonll / ( 1. + toterrorPer_high_fonll ) * D0_fonll_raa_errordata->GetY()[i];
	   }
	   else
	   {
//		   cout << "!!!!!!!!!!!!!!!!!!!! Standard Error Calculation from pp reference!!!!!!!!!!!!!!" << endl;
		   higherror = errorPer_low_fonll * D0_fonll_raa_errordata->GetY()[i];
		   lowerror = toterrorPer_high_fonll * D0_fonll_raa_errordata->GetY()[i];
	   }

		cout << " RAA: " << D0_fonll_raa_errordata->GetY()[i] << "   upper error from reference: " << higherror << "   lower error from reference: " << lowerror << endl;
		if( Nptbin == 7 ) 
		{
			cout << " RCP: " << D0_fonll_raa_errordata->GetY()[i]/RAA_cent50to100[i] << endl;
		}
//        higherror = toterrorPer_low_fonll * D0_fonll_raa_errordata->GetY()[i];
//		lowerror = errorPer_high_fonll  * D0_fonll_raa_errordata->GetY()[i];
        D0_fonll_raa_errorfonll->SetPointEYhigh(i, higherror);
        D0_fonll_raa_errorfonll->SetPointEYlow(i, lowerror);

		cout << endl;
	}

    TGraphAsymmErrors * D0_fonll_raa_errorsys = ( TGraphAsymmErrors *) D0_fonll_raa_errordata->Clone("D0_fonll_raa_errorsys");

    for( int i = 0; i < D0_fonll_raa_errorsys->GetN(); i++ )
	{
//		cout << " RAA: " << D0_fonll_raa_errorsys->GetY()[i] << endl;
        double error_Per_lower = syserrorPer_lower[i];
        double error_Per_upper = syserrorPer_upper[i];
		double syserror_lower =  error_Per_lower * D0_fonll_raa_errorsys->GetY()[i];
		double syserror_upper =  error_Per_upper * D0_fonll_raa_errorsys->GetY()[i];
//		cout << "sys error, lower : " << error_Per_lower << "   upper: " << error_Per_upper << endl; 
		D0_fonll_raa_errorsys->SetPointEYlow(i, syserror_lower);
		D0_fonll_raa_errorsys->SetPointEYhigh(i, syserror_upper);
	}

	D0_fonll_raa_errordata->GetYaxis()->SetRangeUser(0.,3.0);
	D0_fonll_raa_errordata->GetXaxis()->SetRangeUser(0.0,40.);
	D0_fonll_raa_errordata->GetYaxis()->SetTitle("R*_{#kern[-0.3]{AA}}");
	D0_fonll_raa_errordata->GetXaxis()->SetTitle("p_{T} (GeV/c)");
	D0_fonll_raa_errordata->SetFillColor(5.0);
	D0_fonll_raa_errordata->SetFillStyle(1001);

	D0_fonll_raa_errorsys->GetYaxis()->SetRangeUser(0.,2.);
	if( cent_low == 50 && cent_high == 100 ) D0_fonll_raa_errorsys->GetYaxis()->SetRangeUser(0.,2.0);
	D0_fonll_raa_errorsys->GetXaxis()->SetRangeUser(0.0,40.);
	if( Nptbin == 7 ) D0_fonll_raa_errorsys->GetXaxis()->SetRangeUser(0.0,28);
	D0_fonll_raa_errorsys->GetYaxis()->SetTitle("R*_{#kern[-0.3]{AA}}");
	D0_fonll_raa_errorsys->GetXaxis()->SetTitle("p_{T} (GeV/c)");
    D0_fonll_raa_errorsys->SetFillColor(5.0);
	D0_fonll_raa_errorsys->SetLineColor(5.0);
	D0_fonll_raa_errorsys->SetFillStyle(1001);

	D0_fonll_raa_errorsys->Draw("A2");

	D0_fonll_raa_errorfonll->SetFillColor(0);
	D0_fonll_raa_errorfonll->SetFillStyle(0);
	D0_fonll_raa_errorfonll->Draw("2same");

//	D0_fonll_raa_errordata->Draw("Psame");
	
	TGraphAsymmErrors * D0_fonll_raa_errordata_dataextraref = ( TGraphAsymmErrors *) D0_fonll_raa_errordata->Clone("D0_fonll_raa_errordata_dataextraref");
	D0_fonll_raa_errordata_dataextraref->SetName("D0_fonll_raa_errordata_dataextraref");
    
	for( int i = 0; i < D0_fonll_raa_errordata_dataextraref->GetN(); i++ )
    {
		if( D0_fonll_raa_errordata_dataextraref->GetX()[i] > 16.0 )
		{
			D0_fonll_raa_errordata_dataextraref->GetX()[i] = -999;
            D0_fonll_raa_errordata_dataextraref->SetPointEYlow(i, 0);
            D0_fonll_raa_errordata_dataextraref->SetPointEYhigh(i, 0);

		}
	}

	D0_fonll_raa_errordata_dataextraref->Draw("Psame");


	TGraphAsymmErrors * D0_fonll_raa_errordata_FONLLref = ( TGraphAsymmErrors *) D0_fonll_raa_errordata->Clone("D0_fonll_raa_errordata_FONLLref");
	D0_fonll_raa_errordata_FONLLref->SetName("D0_fonll_raa_errordata_FONLLref");
    
	for( int i = 0; i < D0_fonll_raa_errordata_FONLLref->GetN(); i++ )
    {
		if( D0_fonll_raa_errordata_FONLLref->GetX()[i] < 16.0 )
		{
			D0_fonll_raa_errordata_FONLLref->GetX()[i] = -999;
            D0_fonll_raa_errordata_FONLLref->SetPointEYlow(i, 0);
            D0_fonll_raa_errordata_FONLLref->SetPointEYhigh(i, 0);

		}
	}

	D0_fonll_raa_errordata_FONLLref->SetMarkerStyle(24);
	D0_fonll_raa_errordata_FONLLref->Draw("Psame");

	double syserrorPerTAAfraction = TMath::Sqrt( syserrorPerTAA * syserrorPerTAA + ERROR_BR_PERCEN * ERROR_BR_PERCEN + 0.03 * 0.03);

    TBox *b = new TBox(0.04,1-syserrorPerTAAfraction,1.0,1+syserrorPerTAAfraction);
    b->SetLineColor(kGray+1);
    b->SetFillColor(kGray+1);
    b->Draw();

    TF1 * fun = new TF1("fun", "1.0", 0, 500);
    fun->SetLineColor(1.0);
    fun->SetLineStyle(3);
    fun->SetLineWidth(0.1);
    fun->Draw("same");

    TLegend *leg = new TLegend(0.16,0.67,0.45,0.87);
	leg->SetTextFont(42);
	leg->SetTextSize(0.04);
    leg->AddEntry(D0_fonll_raa_errordata,"Prompt D^{0} R*_{#kern[-0.3]{AA}}","PL");
	leg->AddEntry(D0_fonll_raa_errorsys, "Syst. PbPb data","F");
    leg->AddEntry(D0_fonll_raa_errorfonll,"Err. pp reference","f");
    leg->AddEntry(b, "Syst._{} T_{AA}+N_{MB}+BR","f");
    leg->SetBorderSize(0);
    leg->SetFillStyle(0);
    leg->Draw();

    TLatex Traareference;
    Traareference.SetNDC();
    Traareference.SetTextAlign(12);
    Traareference.SetTextSize(0.03);
	Traareference.SetTextFont(42);
    Traareference.DrawLatex(0.17,0.63, "Filled markers: data-extrapolated reference");
    Traareference.DrawLatex(0.17,0.60, "Open markers: FONLL reference");

    TLatex Tl;
    Tl.SetNDC();
    Tl.SetTextAlign(12);
    Tl.SetTextSize(0.04);
	Tl.SetTextFont(42);
    Tl.DrawLatex(0.125,0.93, "#scale[1.25]{CMS} Preliminary");
    Tl.DrawLatex(0.53,0.93, "PbPb #sqrt{s_{NN}} = 2.76 TeV");
    TString centrality; 
	centrality.Form("Cent. %d-%d%%", cent_low,cent_high);
	cout << centrality << endl;
    Tl.DrawLatex(0.62,0.85, centrality);
    Tl.DrawLatex(0.65,0.80, "|y| < 1.0");

	raadmeson->RedrawAxis();

    char cfgname[200];
	sprintf(cfgname,"results/PromptD0_PbPb_spectrum_fonll_effunpre_cent%dto%d_ptbin%d_y1_dataplusfonll.pdf",cent_low,cent_high, Nptbin);
	spectrum->SaveAs(cfgname);
	sprintf(cfgname,"results/PromptD0_PbPb_spectrum_fonll_effunpre_cent%dto%d_ptbin%d_y1_dataplusfonll.png",cent_low,cent_high, Nptbin);
	spectrum->SaveAs(cfgname);
	sprintf(cfgname,"results/PromptRAAD0_PbPb_fonll_effunpre_cent%dto%d_ptbin%d_y1_dataplusfonll.pdf",cent_low,cent_high, Nptbin);
	raadmeson->SaveAs(cfgname);
	sprintf(cfgname,"results/PromptRAAD0_PbPb_fonll_effunpre_cent%dto%d_ptbin%d_y1_dataplusfonll.png",cent_low,cent_high, Nptbin);
	raadmeson->SaveAs(cfgname);

	char outputfile[200];
	sprintf(outputfile, "rootfiles/PromptRAA_D0_PbPb_spectrum_fonll_effunpre_cent%dto%d_ptbin%d_y1_dataplusfonll.root", cent_low,cent_high, Nptbin);
	TFile * output = new TFile(outputfile,"RECREATE");
	spectrum->Write();
	raadmeson->Write();
	D0_fonll_raa_errorsys->Write();
	D0_fonll_raa_errorfonll->Write();
	D0_fonll_raa_errordata->Write();
	D0_fonll_raa_errordata_dataextraref->Write();
	D0_fonll_raa_errordata_FONLLref->Write();
//	d0referencespectrum_dataextraref->Write();
//	d0referencespectrum_FONLLref->Write();
    D0_pbpb_spectrum->Write();
    d0referencespectrum->Write();
	D0_pbpb_spectrum_syserror->Write();
	output->Close();
}

void Dmeson_RAFONLL_prompt_y1_datapp()
{
    //double TAA = 5.67E-9;  //centrality 0 to 100  5.67 0.32
    // double TAA = 18.93e-9 ;     //Alice.  CMS????centrality 0 to 20
   // double TAA = 1.20e-9;      //Alice.   CMS????centrality 40 to 80
    gStyle->SetPadBottomMargin(0.125);

    double TAA;
	int cent_low, cent_high;
	int Nptbin;
	TFile * input_pbpb;
	TFile * fonllinput;
    double syserrorPerTAA;

   //centrality 0 to 100%
      input_pbpb = new TFile("rootfiles/Prompt_Spectrum_centRecoeff_D0_PbPb_dpt_cent0to100_ptbin12_y1.root");
	  fonllinput = new TFile("ppdatadrivenplusFONLL_12ptbin_y1.root");

	  TAA = 5.67E-9;
	  cent_low = 0;
	  cent_high = 100;
	  Nptbin = 12;
	  syserrorPerTAA = 5.7e-2;

	  Draw_RAFONLL(input_pbpb, fonllinput, cent_low, cent_high, Nptbin, TAA, syserrorPerTAA);

	  input_pbpb->Close();
	  fonllinput->Close();

   //centrality 0 to 20%
      input_pbpb = new TFile("rootfiles/Prompt_Spectrum_centRecoeff_D0_PbPb_dpt_cent0to20_ptbin12_y1.root");
	  fonllinput = new TFile("ppdatadrivenplusFONLL_12ptbin_y1.root");

	  TAA = 18.84e-9;
	  cent_low = 0;
	  cent_high = 20;
	  Nptbin = 12;
	  syserrorPerTAA = 4.6e-2;

	  Draw_RAFONLL(input_pbpb, fonllinput, cent_low, cent_high, Nptbin, TAA, syserrorPerTAA);

	  input_pbpb->Close();
	  fonllinput->Close();

   //centrality 0 to 10%
      input_pbpb = new TFile("rootfiles/Prompt_Spectrum_centRecoeff_D0_PbPb_dpt_cent0to10_ptbin12_y1.root");
	  fonllinput = new TFile("ppdatadrivenplusFONLL_12ptbin_y1.root");

	  TAA = 23.20e-9;
	  cent_low = 0;
	  cent_high = 10;
	  Nptbin = 12;
	  syserrorPerTAA = 4.3e-2;

	  Draw_RAFONLL(input_pbpb, fonllinput, cent_low, cent_high, Nptbin, TAA, syserrorPerTAA);

	  input_pbpb->Close();
	  fonllinput->Close();

   //centrality 0 to 10%
      input_pbpb = new TFile("rootfiles/Prompt_Spectrum_centRecoeff_D0_PbPb_dpt_cent0to10_ptbin7_y1.root");
	  fonllinput = new TFile("ppdatadrivenplusFONLL_7ptbin_y1.root");

	  TAA = 23.20e-9;
	  cent_low = 0;
	  cent_high = 10;
	  Nptbin = 7;
	  syserrorPerTAA = 4.3e-2;

	  Draw_RAFONLL(input_pbpb, fonllinput, cent_low, cent_high, Nptbin, TAA, syserrorPerTAA);

	  input_pbpb->Close();
	  fonllinput->Close();

   //centrality 10 to 30%
      input_pbpb = new TFile("rootfiles/Prompt_Spectrum_centRecoeff_D0_PbPb_dpt_cent10to30_ptbin7_y1.root");
	  fonllinput = new TFile("ppdatadrivenplusFONLL_7ptbin_y1.root");

	  TAA = 11.64e-9;
	  cent_low = 10;
	  cent_high = 30;
	  Nptbin = 7;
	  syserrorPerTAA = 5.7e-2;

	  Draw_RAFONLL(input_pbpb, fonllinput, cent_low, cent_high, Nptbin, TAA, syserrorPerTAA);

	  input_pbpb->Close();
	  fonllinput->Close();

   //centrality 30 to 50%
      input_pbpb = new TFile("rootfiles/Prompt_Spectrum_centRecoeff_D0_PbPb_dpt_cent30to50_ptbin7_y1.root");
	  fonllinput = new TFile("ppdatadrivenplusFONLL_7ptbin_y1.root");

	  TAA = 3.92e-9;
	  cent_low = 30;
	  cent_high = 50;
	  Nptbin = 7;
	  syserrorPerTAA = 9.3e-2;

	  Draw_RAFONLL(input_pbpb, fonllinput, cent_low, cent_high, Nptbin, TAA, syserrorPerTAA);

	  input_pbpb->Close();
	  fonllinput->Close();

   //centrality 50 to 100%
      input_pbpb = new TFile("rootfiles/Prompt_Spectrum_centRecoeff_D0_PbPb_dpt_cent50to100_ptbin7_y1.root");
	  fonllinput = new TFile("ppdatadrivenplusFONLL_7ptbin_y1.root");

	  TAA = 0.47e-9;
	  cent_low = 50;
	  cent_high = 100;
	  Nptbin = 7;
	  syserrorPerTAA = 15.0e-2;

	  Draw_RAFONLL(input_pbpb, fonllinput, cent_low, cent_high, Nptbin, TAA, syserrorPerTAA);

	  input_pbpb->Close();
	  fonllinput->Close();

 //centrality 0 to 10%
      input_pbpb = new TFile("rootfiles/Prompt_Spectrum_centRecoeff_D0_PbPb_dpt_cent0to10_ptbin3_y1.root");
	  fonllinput = new TFile("ppdatadrivenplusFONLL_3ptbin_y1.root");

	  TAA = 23.20e-9;
	  cent_low = 0;
	  cent_high = 10;
	  Nptbin = 3;
	  syserrorPerTAA = 4.3e-2;

	  Draw_RAFONLL(input_pbpb, fonllinput, cent_low, cent_high, Nptbin, TAA, syserrorPerTAA);

	  input_pbpb->Close();
	  fonllinput->Close();

   //centrality 10 to 20%
      input_pbpb = new TFile("rootfiles/Prompt_Spectrum_centRecoeff_D0_PbPb_dpt_cent10to20_ptbin3_y1.root");
	  fonllinput = new TFile("ppdatadrivenplusFONLL_3ptbin_y1.root");

	  TAA = 14.48e-9;
	  cent_low = 10;
	  cent_high = 20;
	  Nptbin = 3;
	  syserrorPerTAA = 5.2e-2;

	  Draw_RAFONLL(input_pbpb, fonllinput, cent_low, cent_high, Nptbin, TAA, syserrorPerTAA);

	  input_pbpb->Close();
	  fonllinput->Close();


   //centrality 20 to 30%
      input_pbpb = new TFile("rootfiles/Prompt_Spectrum_centRecoeff_D0_PbPb_dpt_cent20to30_ptbin3_y1.root");
	  fonllinput = new TFile("ppdatadrivenplusFONLL_3ptbin_y1.root");

	  TAA = 8.80e-9;
	  cent_low = 20;
	  cent_high = 30;
	  Nptbin = 3;
	  syserrorPerTAA = 6.6e-2;

	  Draw_RAFONLL(input_pbpb, fonllinput, cent_low, cent_high, Nptbin, TAA, syserrorPerTAA);

	  input_pbpb->Close();
	  fonllinput->Close();


   //centrality 30 to 40%
      input_pbpb = new TFile("rootfiles/Prompt_Spectrum_centRecoeff_D0_PbPb_dpt_cent30to40_ptbin3_y1.root");
	  fonllinput = new TFile("ppdatadrivenplusFONLL_3ptbin_y1.root");

	  TAA = 5.09e-9;
	  cent_low = 30;
	  cent_high = 40;
	  Nptbin = 3;
	  syserrorPerTAA = 8.5e-2;

	  Draw_RAFONLL(input_pbpb, fonllinput, cent_low, cent_high, Nptbin, TAA, syserrorPerTAA);

	  input_pbpb->Close();
	  fonllinput->Close();


   //centrality 40 to 50%
      input_pbpb = new TFile("rootfiles/Prompt_Spectrum_centRecoeff_D0_PbPb_dpt_cent40to50_ptbin3_y1.root");
	  fonllinput = new TFile("ppdatadrivenplusFONLL_3ptbin_y1.root");

	  TAA = 2.75e-9;
	  cent_low = 40;
	  cent_high = 50;
	  Nptbin = 3;
	  syserrorPerTAA = 10.9e-2;

	  Draw_RAFONLL(input_pbpb, fonllinput, cent_low, cent_high, Nptbin, TAA, syserrorPerTAA);

	  input_pbpb->Close();
	  fonllinput->Close();

   //centrality 50 to 100%
      input_pbpb = new TFile("rootfiles/Prompt_Spectrum_centRecoeff_D0_PbPb_dpt_cent50to100_ptbin3_y1.root");
	  fonllinput = new TFile("ppdatadrivenplusFONLL_3ptbin_y1.root");

	  TAA = 0.47e-9;
	  cent_low = 50;
	  cent_high = 100;
	  Nptbin = 3;
	  syserrorPerTAA = 15.0e-2;

	  Draw_RAFONLL(input_pbpb, fonllinput, cent_low, cent_high, Nptbin, TAA, syserrorPerTAA);

	  input_pbpb->Close();
	  fonllinput->Close();


}
