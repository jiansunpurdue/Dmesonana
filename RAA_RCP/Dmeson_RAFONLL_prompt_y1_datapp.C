//
//systematics for differenct centrality and pt bins
double syserrorPer_upper_ptbin12_cent0to100[12] = { 0.178, 0.175, 0.173, 0.173, 0.173, 0.172, 0.174, 0.172, 0.172, 0.170, 0.170, 0.239};
double syserrorPer_lower_ptbin12_cent0to100[12] = { 0.178, 0.175, 0.173, 0.173, 0.173, 0.172, 0.174, 0.172, 0.172, 0.170, 0.170, 0.239};

double syserrorPer_upper_ptbin11_cent0to10[11] = { 0.287, 0.241, 0.238, 0.258, 0.247, 0.237, 0.245, 0.234, 0.247, 0.245, 0.245};
double syserrorPer_lower_ptbin11_cent0to10[11] = { 0.287, 0.241, 0.238, 0.258, 0.247, 0.237, 0.245, 0.234, 0.247, 0.245, 0.245};

double syserrorPer_upper_ptbin11_cent0to20[11] = { 0.261, 0.241, 0.241, 0.248, 0.239, 0.232, 0.237, 0.229, 0.242, 0.241, 0.241};
double syserrorPer_lower_ptbin11_cent0to20[11] = { 0.261, 0.241, 0.241, 0.248, 0.239, 0.232, 0.237, 0.229, 0.242, 0.241, 0.241};

double syserrorPer_upper_ptbin7_cent0to10[7] = { 0.287, 0.238, 0.235, 0.250, 0.237, 0.230, 0.227};
double syserrorPer_lower_ptbin7_cent0to10[7] = { 0.287, 0.238, 0.235, 0.250, 0.237, 0.230, 0.227};

double syserrorPer_upper_ptbin7_cent10to30[7] = {0.255, 0.248, 0.245, 0.237, 0.229, 0.225, 0.249};
double syserrorPer_lower_ptbin7_cent10to30[7] = {0.255, 0.248, 0.245, 0.237, 0.229, 0.225, 0.249};

double syserrorPer_upper_ptbin7_cent30to50[7] = {0.209, 0.195, 0.190, 0.191, 0.189, 0.204, 0.203};
double syserrorPer_lower_ptbin7_cent30to50[7] = {0.209, 0.195, 0.190, 0.191, 0.189, 0.204, 0.203};

double syserrorPer_upper_ptbin7_cent50to100[7] = {0.246, 0.197, 0.193, 0.192, 0.191, 0.190, 0.304};
double syserrorPer_lower_ptbin7_cent50to100[7] = {0.246, 0.197, 0.193, 0.192, 0.191, 0.190, 0.304};

double *syserrorPer_upper;
double *syserrorPer_lower;
double syserror_Per_FONLL = 4.1e-2;


//#define NPT  12
//double ptbins[NPT+1] = {0,1.5,2.5,3.5,4.5,5.5,7,9,11,13,16,20,28,40,100};


void Draw_RAFONLL( TFile * input_pbpb, TFile * fonllinput, int cent_low, int cent_high, int Nptbin, double TAA, double syserrorPerTAAfraction)
{
	gStyle->SetOptTitle(0);
	gStyle->SetOptStat(0);
	TH1::SetDefaultSumw2();
	syserrorPer_upper =  new double[Nptbin];
	syserrorPer_lower =  new double[Nptbin];

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

	if( Nptbin == 11 && cent_low == 0 && cent_high == 10 )
	{
		for( int i = 0; i < Nptbin; i++ )
		{
			syserrorPer_upper[i] = syserrorPer_upper_ptbin11_cent0to10[i];
			syserrorPer_lower[i] = syserrorPer_lower_ptbin11_cent0to10[i];
		}
	}

	if( Nptbin == 11 && cent_low == 0 && cent_high == 20 )
	{
		for( int i = 0; i < Nptbin; i++ )
		{
			syserrorPer_upper[i] = syserrorPer_upper_ptbin11_cent0to20[i];
			syserrorPer_lower[i] = syserrorPer_lower_ptbin11_cent0to20[i];
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

	TH1D * D0Spectrum_pbpb = ( TH1D *) input_pbpb->Get("d0raw_data_overeff");
	TH1D * D0_pbpb_spectrum = ( TH1D * ) D0Spectrum_pbpb->Clone("D0_pbpb_spectrum");

	D0_pbpb_spectrum->Scale(1.0/TAA);
	
	if( Nptbin == 11 || Nptbin == 7)   
	{
		D0_pbpb_spectrum->SetBinContent(D0_pbpb_spectrum->FindBin(35), -999);
	    D0_pbpb_spectrum->SetBinError(D0_pbpb_spectrum->FindBin(35), 0);
		D0_pbpb_spectrum->GetYaxis()->SetRangeUser(2.0, 25);
	}

	TGraphAsymmErrors * d0fonllspectrum = ( TGraphAsymmErrors *) fonllinput->Get("gaeSigmaDzero");
	d0fonllspectrum->SetName("d0fonllspectrum");

	TCanvas * spectrum = new TCanvas("spectrum","spectrum");
	spectrum->SetLeftMargin(0.2);
	gPad->SetLogy();


	TGraphAsymmErrors * D0_pbpb_spectrum_syserror = ( TGraphAsymmErrors *) d0fonllspectrum->Clone("D0_pbpb_spectrum_syserror");

	for( int i = 0; i < D0_pbpb_spectrum_syserror->GetN(); i++ )
	{
		double error_Per_lower = syserrorPer_lower[i]; 
		double error_Per_upper = syserrorPer_upper[i];
		double binvalue = D0_pbpb_spectrum->GetBinContent(i+2);
		cout << " binvalue : " << binvalue << "  error_Per_lower: " << error_Per_lower << "   error_Per_upper: " << error_Per_upper << endl;
		D0_pbpb_spectrum_syserror->GetY()[i] = binvalue;
		D0_pbpb_spectrum_syserror->SetPointEYhigh(i, error_Per_upper*binvalue);
		D0_pbpb_spectrum_syserror->SetPointEYlow(i, error_Per_lower*binvalue);
//		cout << " error_Per_upper*binvalue: " << error_Per_upper*binvalue << "   error_Per_lower*binvalue: " << error_Per_lower*binvalue << endl;
	}


	D0_pbpb_spectrum_syserror->GetYaxis()->SetRangeUser(1E2,1E9);
	D0_pbpb_spectrum_syserror->GetXaxis()->SetRangeUser(1.5,40);
	if( Nptbin == 11 || Nptbin == 7 ) D0_pbpb_spectrum_syserror->GetXaxis()->SetRangeUser(1.5,28);
    D0_pbpb_spectrum_syserror->GetYaxis()->SetTitleOffset(2.0);
    D0_pbpb_spectrum_syserror->GetYaxis()->SetTitle("#frac{d#sigma_{pp}}{dp_{T}}, #frac{1}{2N_{evt}T_{AA}} #frac{dN_{PbPb}}{dp_{T}} #frac{pb}{GeV/c}");
	D0_pbpb_spectrum_syserror->GetXaxis()->SetTitle("Prompt D^{0} p_{T} (GeV/c)");
    D0_pbpb_spectrum_syserror->SetFillColor(5.0);
	D0_pbpb_spectrum_syserror->SetLineColor(5.0);
	D0_pbpb_spectrum_syserror->SetFillStyle(1001);
	D0_pbpb_spectrum_syserror->Draw("A2");

    D0_pbpb_spectrum->SetFillColor(5.0);
	D0_pbpb_spectrum->SetFillStyle(1001);
	D0_pbpb_spectrum->SetMarkerStyle(20);
	D0_pbpb_spectrum->SetMarkerColor(4.0);
	D0_pbpb_spectrum->SetLineColor(4.0);
	D0_pbpb_spectrum->DrawCopy("epsame");
	
	d0fonllspectrum->SetLineWidth(0.5);
	d0fonllspectrum->SetMarkerStyle(21);
	d0fonllspectrum->SetMarkerSize(1.0);
	d0fonllspectrum->Draw("psame");

	TLegend * t = new TLegend(0.35, 0.7, 0.85, 0.85);
	t->SetFillColor(0);
	t->AddEntry( D0_pbpb_spectrum, Form("PbPb Data, centrality %d-%d%%", cent_low, cent_high));
	t->AddEntry(d0fonllspectrum, "FONLL", "PL");
	t->Draw();

	TCanvas * raadmeson = new TCanvas("raadmeson","raadmeson");
	TH1D * D0_pbpb_spectrum_raa = ( TH1D *) D0_pbpb_spectrum->Clone("D0_pbpb_spectrum_raa");
	TGraphAsymmErrors * D0_fonll_raa_errordata = ( TGraphAsymmErrors *) d0fonllspectrum->Clone("D0_fonll_raa_errordata");
	TGraphAsymmErrors * D0_fonll_raa_errorfonll = ( TGraphAsymmErrors *) d0fonllspectrum->Clone("D0_fonll_raa_errorfonll");
	D0_fonll_raa_errordata->SetMarkerStyle(20);
	D0_fonll_raa_errorfonll->SetMarkerStyle(20);

	for( int i = 0; i < D0_fonll_raa_errordata->GetN();i++){
		D0_fonll_raa_errordata->GetY()[i] = D0_pbpb_spectrum_raa->GetBinContent(i+2) / d0fonllspectrum->GetY()[i];
//		cout << "PbPb: " << D0_pbpb_spectrum_raa->GetBinContent(i+2) << " pp: " << d0fonllspectrum->GetY()[i] << " RAA: " << D0_fonll_raa_errordata->GetY()[i] << endl;
//        cout << "Pbbin: " << ptbins[i+1] << " to " << ptbins[i+2] <<   " RAA: " << D0_fonll_raa_errordata->GetY()[i] << endl;
        double higherror = D0_pbpb_spectrum_raa->GetBinError(i+2)/d0fonllspectrum->GetY()[i];
		double lowerror = D0_pbpb_spectrum_raa->GetBinError(i+2)/d0fonllspectrum->GetY()[i];
		D0_fonll_raa_errordata->SetPointEYhigh(i, higherror);
		D0_fonll_raa_errordata->SetPointEYlow(i, lowerror);

        D0_fonll_raa_errorfonll->GetY()[i] = D0_pbpb_spectrum_raa->GetBinContent(i+2) / d0fonllspectrum->GetY()[i];
		
//		cout <<"Relative statistical error" << higherror/D0_fonll_raa_errordata->GetY()[i] << endl;
        
		double errorPer_low_fonll = d0fonllspectrum->GetErrorYlow(i)/d0fonllspectrum->GetY()[i];
		double errorPer_high_fonll = d0fonllspectrum->GetErrorYhigh(i)/d0fonllspectrum->GetY()[i];
		double toterrorPer_low_fonll = TMath::Sqrt(syserror_Per_FONLL*syserror_Per_FONLL + errorPer_low_fonll*errorPer_low_fonll);
		double  toterrorPer_high_fonll = TMath::Sqrt(syserror_Per_FONLL*syserror_Per_FONLL + errorPer_high_fonll*errorPer_high_fonll);

//        cout << "FONLL calculation Per error, lower: " << errorPer_high_fonll << "   upper: " << errorPer_low_fonll << endl;
//		cout << "FONLL total Per error, lower: " << toterrorPer_high_fonll << "   upper: " << toterrorPer_low_fonll << endl;

		higherror = toterrorPer_low_fonll / (1. - toterrorPer_low_fonll ) * D0_fonll_raa_errordata->GetY()[i];
		lowerror = errorPer_high_fonll / ( 1. + errorPer_high_fonll ) * D0_fonll_raa_errordata->GetY()[i];
//        higherror = toterrorPer_low_fonll * D0_fonll_raa_errordata->GetY()[i];
//		lowerror = errorPer_high_fonll  * D0_fonll_raa_errordata->GetY()[i];
        D0_fonll_raa_errorfonll->SetPointEYhigh(i, higherror);
        D0_fonll_raa_errorfonll->SetPointEYlow(i, lowerror);

	}

    TGraphAsymmErrors * D0_fonll_raa_errorsys = ( TGraphAsymmErrors *) D0_fonll_raa_errordata->Clone("D0_fonll_raa_errorsys");

    for( int i = 0; i < D0_fonll_raa_errorsys->GetN(); i++ )
	{
//		cout << " RAA: " << D0_fonll_raa_errorsys->GetY()[i] << endl;
        double error_Per_lower = syserrorPer_lower[i];
        double error_Per_upper = syserrorPer_upper[i];
		double syserror_lower =  error_Per_lower * D0_fonll_raa_errorsys->GetY()[i];
		double syserror_upper =  error_Per_upper * D0_fonll_raa_errorsys->GetY()[i];
		cout << "sys error, lower : " << error_Per_lower << "   upper: " << error_Per_upper << endl; 
		D0_fonll_raa_errorsys->SetPointEYlow(i, syserror_lower);
		D0_fonll_raa_errorsys->SetPointEYhigh(i, syserror_upper);
	}
	

	D0_fonll_raa_errordata->GetYaxis()->SetRangeUser(0.,2.);
	D0_fonll_raa_errordata->GetXaxis()->SetRangeUser(0.0,40.);
	D0_fonll_raa_errordata->GetYaxis()->SetTitle("Prompt D^{0} R^{FONLL}_{AA}");
	D0_fonll_raa_errordata->GetXaxis()->SetTitle("Prompt D^{0} p_{T} (GeV/c)");
	D0_fonll_raa_errordata->SetFillColor(5.0);
	D0_fonll_raa_errordata->SetFillStyle(1001);

	D0_fonll_raa_errorsys->GetYaxis()->SetRangeUser(0.,2.);
	if( cent_low == 50 && cent_high == 100 ) D0_fonll_raa_errorsys->GetYaxis()->SetRangeUser(0.,2.0);
	D0_fonll_raa_errorsys->GetXaxis()->SetRangeUser(0.0,40.);
	if( Nptbin == 11 || Nptbin == 7 ) D0_fonll_raa_errorsys->GetXaxis()->SetRangeUser(0.0,28);
	D0_fonll_raa_errorsys->GetYaxis()->SetTitle("Prompt D^{0} R_{AA}");
	D0_fonll_raa_errorsys->GetXaxis()->SetTitle("Prompt D^{0} p_{T} (GeV/c)");
    D0_fonll_raa_errorsys->SetFillColor(5.0);
	D0_fonll_raa_errorsys->SetLineColor(5.0);
	D0_fonll_raa_errorsys->SetFillStyle(1001);

	D0_fonll_raa_errorsys->Draw("A2");

	D0_fonll_raa_errorfonll->SetFillColor(0);
	D0_fonll_raa_errorfonll->SetFillStyle(0);
	D0_fonll_raa_errorfonll->Draw("2same");

	D0_fonll_raa_errordata->Draw("Psame");

    TF1 * fun = new TF1("fun", "1.0", 0, 500);
    fun->SetLineColor(1.0);
    fun->SetLineStyle(3);
    fun->SetLineWidth(0.1);
    fun->Draw("same");

    TBox *b = new TBox(0.05,1-syserrorPerTAAfraction,1.5,1+syserrorPerTAAfraction);
    b->SetLineColor(kGray);
    b->SetFillColor(kGray);
    b->Draw();

	if( cent_low == 50 && cent_high == 100)
	{
        TLegend *leg = new TLegend(0.57,0.65,0.85,0.8);
	    leg->SetTextFont(62);
        leg->AddEntry(D0_fonll_raa_errordata,"Prompt D^{0} R_{AA}","PLf");
        leg->AddEntry(D0_fonll_raa_errorfonll,"Err. from pp reference","f");
	    leg->AddEntry(b, "Syst. TAA+BR","f");
        leg->SetBorderSize(0);
        leg->SetFillStyle(0);
        leg->Draw();
	}
	else
	{
        TLegend *leg = new TLegend(0.5,0.65,0.85,0.8);
	    leg->SetTextFont(62);
        leg->AddEntry(D0_fonll_raa_errordata,"Prompt D^{0} R_{AA}","PLf");
        leg->AddEntry(D0_fonll_raa_errorfonll,"Err. from pp reference","f");
	    leg->AddEntry(b, "Syst. TAA+BR","f");
        leg->SetBorderSize(0);
        leg->SetFillStyle(0);
        leg->Draw();
	}

    TLatex Tl;
    Tl.SetNDC();
    Tl.SetTextAlign(12);
    Tl.SetTextSize(0.03);
	Tl.SetTextFont(62);
    Tl.DrawLatex(0.20,0.85, "CMS Preliminary #sqrt{s_{NN}} = 2.76 TeV");
    Tl.DrawLatex(0.20,0.80, "#left|y#right| < 1.0");
    TString centrality; 
	centrality.Form("Centrality %d-%d%%", cent_low,cent_high);
	cout << centrality << endl;
    Tl.DrawLatex(0.20,0.75, centrality);

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
    D0_pbpb_spectrum->Write();
    d0fonllspectrum->Write();
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
    double syserrorPerTAAfraction;

   //centrality 0 to 100%
      input_pbpb = new TFile("rootfiles/Prompt_Spectrum_centRecoeff_D0_PbPb_dpt_cent0to100_ptbin12_y1.root");
	  fonllinput = new TFile("ppdatadrivenplusFONLL_12ptbin_y1.root");

	  TAA = 5.67E-9;
	  cent_low = 0;
	  cent_high = 100;
	  Nptbin = 12;
	  syserrorPerTAAfraction = 5.8e-2;

	  Draw_RAFONLL(input_pbpb, fonllinput, cent_low, cent_high, Nptbin, TAA, syserrorPerTAAfraction);

	  input_pbpb->Close();
	  fonllinput->Close();

   //centrality 0 to 10%
      input_pbpb = new TFile("rootfiles/Prompt_Spectrum_centRecoeff_D0_PbPb_dpt_cent0to10_ptbin11_y1.root");
	  fonllinput = new TFile("ppdatadrivenplusFONLL_12ptbin_y1.root");

	  TAA = 23.20e-9;
	  cent_low = 0;
	  cent_high = 10;
	  Nptbin = 11;
	  syserrorPerTAAfraction = 4.5e-2;

	  Draw_RAFONLL(input_pbpb, fonllinput, cent_low, cent_high, Nptbin, TAA, syserrorPerTAAfraction);

	  input_pbpb->Close();
	  fonllinput->Close();

   //centrality 0 to 20%
      input_pbpb = new TFile("rootfiles/Prompt_Spectrum_centRecoeff_D0_PbPb_dpt_cent0to20_ptbin11_y1.root");
	  fonllinput = new TFile("ppdatadrivenplusFONLL_12ptbin_y1.root");

	  TAA = 18.84e-9;
	  cent_low = 0;
	  cent_high = 20;
	  Nptbin = 11;
	  syserrorPerTAAfraction = 4.7e-2;

	  Draw_RAFONLL(input_pbpb, fonllinput, cent_low, cent_high, Nptbin, TAA, syserrorPerTAAfraction);

	  input_pbpb->Close();
	  fonllinput->Close();

   //centrality 0 to 10%
      input_pbpb = new TFile("rootfiles/Prompt_Spectrum_centRecoeff_D0_PbPb_dpt_cent0to10_ptbin7_y1.root");
	  fonllinput = new TFile("ppdatadrivenplusFONLL_7ptbin_y1.root");

	  TAA = 23.20e-9;
	  cent_low = 0;
	  cent_high = 10;
	  Nptbin = 7;
	  syserrorPerTAAfraction = 4.5e-2;

	  Draw_RAFONLL(input_pbpb, fonllinput, cent_low, cent_high, Nptbin, TAA, syserrorPerTAAfraction);

	  input_pbpb->Close();
	  fonllinput->Close();

   //centrality 10 to 30%
      input_pbpb = new TFile("rootfiles/Prompt_Spectrum_centRecoeff_D0_PbPb_dpt_cent10to30_ptbin7_y1.root");
	  fonllinput = new TFile("ppdatadrivenplusFONLL_7ptbin_y1.root");

	  TAA = 11.64e-9;
	  cent_low = 10;
	  cent_high = 30;
	  Nptbin = 7;
	  syserrorPerTAAfraction = 5.8e-2;

	  Draw_RAFONLL(input_pbpb, fonllinput, cent_low, cent_high, Nptbin, TAA, syserrorPerTAAfraction);

	  input_pbpb->Close();
	  fonllinput->Close();

   //centrality 30 to 50%
      input_pbpb = new TFile("rootfiles/Prompt_Spectrum_centRecoeff_D0_PbPb_dpt_cent30to50_ptbin7_y1.root");
	  fonllinput = new TFile("ppdatadrivenplusFONLL_7ptbin_y1.root");

	  TAA = 3.92e-9;
	  cent_low = 30;
	  cent_high = 50;
	  Nptbin = 7;
	  syserrorPerTAAfraction = 9.4e-2;

	  Draw_RAFONLL(input_pbpb, fonllinput, cent_low, cent_high, Nptbin, TAA, syserrorPerTAAfraction);

	  input_pbpb->Close();
	  fonllinput->Close();

   //centrality 50 to 100%
      input_pbpb = new TFile("rootfiles/Prompt_Spectrum_centRecoeff_D0_PbPb_dpt_cent50to100_ptbin7_y1.root");
	  fonllinput = new TFile("ppdatadrivenplusFONLL_7ptbin_y1.root");

	  TAA = 0.47e-9;
	  cent_low = 50;
	  cent_high = 100;
	  Nptbin = 7;
	  syserrorPerTAAfraction = 11.2e-2;

	  Draw_RAFONLL(input_pbpb, fonllinput, cent_low, cent_high, Nptbin, TAA, syserrorPerTAAfraction);

	  input_pbpb->Close();
	  fonllinput->Close();

}
