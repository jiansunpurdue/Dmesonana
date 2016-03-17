double syserrorPer_upper_ptbin7_cent0to10_RCP[7] = { 0.277863 ,0.223157 ,0.208286 ,0.223361 ,0.186682 ,0.1648 ,0.273383};
double syserrorPer_lower_ptbin7_cent0to10_RCP[7] = { 0.277863 ,0.223157 ,0.208286 ,0.223361 ,0.186682 ,0.1648 ,0.273383};

double syserrorPer_upper_ptbin7_cent10to30_RCP[7] = { 0.281785 ,0.177403 ,0.211679 ,0.171167 ,0.156774 ,0.141021 ,0.280355};
double syserrorPer_lower_ptbin7_cent10to30_RCP[7] = { 0.281785 ,0.177403 ,0.211679 ,0.171167 ,0.156774 ,0.141021 ,0.280355};

double syserrorPer_upper_ptbin7_cent30to50_RCP[7] = { 0.247546 ,0.160509 ,0.144803 ,0.120975 ,0.114865 ,0.101931 ,0.24052};
double syserrorPer_lower_ptbin7_cent30to50_RCP[7] = { 0.247546 ,0.160509 ,0.144803 ,0.120975 ,0.114865 ,0.101931 ,0.24052};

double *syserrorPer_upper;
double *syserrorPer_lower;
double syserror_Per_FONLL = 4.1e-2;


void Draw_RCP( TFile * input_pbpb_central, TFile * input_pbpb_perip, int cent_low, int cent_high, int Nptbin, double TAA_central, double TAA_perip)
{
	gStyle->SetOptTitle(0);
	gStyle->SetOptStat(0);
	TH1::SetDefaultSumw2();

    syserrorPer_upper =  new double[Nptbin];
    syserrorPer_lower =  new double[Nptbin];

    for( int i = 0; i < Nptbin; i++ )
    {
        syserrorPer_upper[i] = 0.0;
        syserrorPer_lower[i] = 0.0;
    }

    if( Nptbin == 7 && cent_low == 0 && cent_high == 10 )
    {
        for( int i = 0; i < Nptbin; i++ )
        {
            syserrorPer_upper[i] = syserrorPer_upper_ptbin7_cent0to10_RCP[i];
            syserrorPer_lower[i] = syserrorPer_lower_ptbin7_cent0to10_RCP[i];
        }
    }

    if( Nptbin == 7 && cent_low == 10 && cent_high == 30 )
    {
        for( int i = 0; i < Nptbin; i++ )
        {
            syserrorPer_upper[i] = syserrorPer_upper_ptbin7_cent10to30_RCP[i];
            syserrorPer_lower[i] = syserrorPer_lower_ptbin7_cent10to30_RCP[i];
        }
    }

    if( Nptbin == 7 && cent_low == 30 && cent_high == 50 )
    {
        for( int i = 0; i < Nptbin; i++ )
        {
            syserrorPer_upper[i] = syserrorPer_upper_ptbin7_cent30to50_RCP[i];
            syserrorPer_lower[i] = syserrorPer_lower_ptbin7_cent30to50_RCP[i];
        }
    }

	TFile * fonllinput = new TFile("ppdatadrivenplusFONLL_7ptbin_y1.root");
    TGraphAsymmErrors * RCP_errorsys = ( TGraphAsymmErrors *) fonllinput->Get("gaeSigmaDzero");
    RCP_errorsys->SetName("RCP_errorsys");

	TH1D * D0Spectrum_pbpb_central = ( TH1D *) input_pbpb_central->Get("d0raw_data_overeff");
	TH1D * D0_pbpb_spectrum_central = ( TH1D * ) D0Spectrum_pbpb_central->Clone("D0_pbpb_spectrum_central");

	if( Nptbin == 7 || Nptbin == 11 )   
	{
		D0_pbpb_spectrum_central->SetBinContent(D0_pbpb_spectrum_central->FindBin(35), -9999999);
	    D0_pbpb_spectrum_central->SetBinError(D0_pbpb_spectrum_central->FindBin(35), 0);
		D0_pbpb_spectrum_central->GetYaxis()->SetRangeUser(2.0, 25);
	}

	D0_pbpb_spectrum_central->Scale(1.0/TAA_central);


	TH1D * D0Spectrum_pbpb_perip = ( TH1D *) input_pbpb_perip->Get("d0raw_data_overeff");
	TH1D * D0_pbpb_spectrum_perip = ( TH1D * ) D0Spectrum_pbpb_perip->Clone("D0_pbpb_spectrum_perip");

	if( Nptbin == 7 || Nptbin == 11 )   
	{
		D0_pbpb_spectrum_perip->SetBinContent(D0_pbpb_spectrum_perip->FindBin(35), -999);
	    D0_pbpb_spectrum_perip->SetBinError(D0_pbpb_spectrum_perip->FindBin(35), 0);

		D0_pbpb_spectrum_perip->SetBinContent(D0_pbpb_spectrum_perip->FindBin(2.0), -9);
		D0_pbpb_spectrum_perip->GetYaxis()->SetRangeUser(2.0, 24);
	}

	D0_pbpb_spectrum_perip->Scale(1.0/TAA_perip);

	TCanvas * cfg_D0_central_perip = new TCanvas("cfg_D0_central_perip","cfg_D0_central_perip");
	cfg_D0_central_perip->SetLeftMargin(0.2);
	gPad->SetLogy();

    D0_pbpb_spectrum_central->GetYaxis()->SetTitleOffset(2.0);
    D0_pbpb_spectrum_central->GetYaxis()->SetTitle("#frac{1}{2N_{evt}T_{AA}}#frac{dN_{PbPb}}{dp_{T}} #frac{pb}{GeV/c}");
    D0_pbpb_spectrum_central->GetXaxis()->SetTitle("D0 p_{T} (GeV/c)");
    D0_pbpb_spectrum_central->GetYaxis()->SetRangeUser(1E2,1E8);
	D0_pbpb_spectrum_central->SetLineColor(1.0);
	D0_pbpb_spectrum_central->SetMarkerColor(1.0);

	D0_pbpb_spectrum_perip->SetLineColor(4.0);
	D0_pbpb_spectrum_perip->SetMarkerColor(4.0);

	D0_pbpb_spectrum_central->DrawCopy();
	D0_pbpb_spectrum_perip->DrawCopy("same");


	TH1D * D0_Rcp_errorstats = (TH1D *)D0_pbpb_spectrum_central->Clone("D0_Rcp_errorstats");

	D0_Rcp_errorstats->Divide(D0_pbpb_spectrum_central, D0_pbpb_spectrum_perip, 1.0, 1.0);

	cout << " Centrality: " << cent_low << "   to   " << cent_high << endl;
	for( int i = 0; i < Nptbin + 1; i++ )
	{
		cout << " PbPb central spectrum: " << D0_pbpb_spectrum_central->GetBinContent(i+1) << endl;
	}

    for( int i = 0; i < RCP_errorsys->GetN(); i++ )
    {
        double error_Per_lower = syserrorPer_lower[i];
        double error_Per_upper = syserrorPer_upper[i];
        double syserror_lower =  error_Per_lower * D0_Rcp_errorstats->GetBinContent(i+2);
        double syserror_upper =  error_Per_upper * D0_Rcp_errorstats->GetBinContent(i+2);
        cout << "RCP :" << D0_Rcp_errorstats->GetBinContent(i+2) << "  sys error, lower : " << error_Per_lower << "   upper: " << error_Per_upper << endl;
        RCP_errorsys->GetY()[i] = D0_Rcp_errorstats->GetBinContent(i+2);
		RCP_errorsys->SetPointEYlow(i, syserror_lower);
        RCP_errorsys->SetPointEYhigh(i, syserror_upper);
    }

	TCanvas * cfg_D0_Rcp = new TCanvas("cfg_D0_Rcp","cfg_D0_Rcp");

    RCP_errorsys->GetYaxis()->SetRangeUser(0.,2.);
    RCP_errorsys->GetXaxis()->SetRangeUser(1.5,28.);
	RCP_errorsys->GetYaxis()->SetTitleOffset(1.25);
    RCP_errorsys->GetYaxis()->SetTitle("Prompt D^{0} R^{50-100%}_{CP}");
    RCP_errorsys->GetXaxis()->SetTitle("Prompt D^{0} p_{T} (GeV/c)");
    RCP_errorsys->SetFillColor(5.0);
    RCP_errorsys->SetFillStyle(1001);
	RCP_errorsys->Draw("A2");
   
    D0_Rcp_errorstats->SetFillColor(5.0);
	D0_Rcp_errorstats->SetFillStyle(1001);
	D0_Rcp_errorstats->GetYaxis()->SetTitle("Prompt D^{0} R^{50-100%}_{CP}");
    D0_Rcp_errorstats->GetYaxis()->SetRangeUser(0,2);
	D0_Rcp_errorstats->DrawCopy("Psame");

    TLatex Tl;
    Tl.SetNDC();
    Tl.SetTextAlign(12);
    Tl.SetTextSize(0.03);
    Tl.DrawLatex(0.3,0.8, "CMS Preliminary #sqrt{s_{NN}} = 2.76 TeV");
    Tl.DrawLatex(0.3,0.75, "|y| < 1.0");
    TString centrality;
    centrality.Form("Centrality %d-%d%%", cent_low,cent_high);
    cout << centrality << endl;
    Tl.DrawLatex(0.3,0.7, centrality);   


    char cfgname[200];
	sprintf(cfgname,"results/RCPD0_PbPb_effunpre_cent%dto%d_ptbin%d_y1.pdf",cent_low,cent_high, Nptbin);
	cfg_D0_Rcp->SaveAs(cfgname);
	sprintf(cfgname,"results/RCPD0_PbPb_effunpre_cent%dto%d_ptbin%d_y1.png",cent_low,cent_high, Nptbin);
	cfg_D0_Rcp->SaveAs(cfgname);

	char outputfile[200];
	sprintf(outputfile, "RCP_D0_PbPb_effunpre_cent%dto%d_ptbin%d_y1.root", cent_low,cent_high, Nptbin);

	TFile * output = new TFile(outputfile,"RECREATE");

	D0_pbpb_spectrum_central->Write();
	D0_pbpb_spectrum_perip->Write();
	cfg_D0_central_perip->Write();
	cfg_D0_Rcp->Write();
	D0_Rcp_errorstats->Write();
	RCP_errorsys->Write();

	output->Close();

	cout << endl;
	
}

void Dmeson_RCP_y1()
{
    //double TAA_central = 5.67E-9;  //centrality 0 to 100  5.67 0.32
    // double TAA_central = 18.93e-9 ;     //Alice.  CMS????centrality 0 to 20
   // double TAA_central = 1.20e-9;      //Alice.   CMS????centrality 40 to 80

    double TAA_central;
	double TAA_perip = 0.47e-9; // 50 to 100%
	int cent_low, cent_high;
	int Nptbin;
	TFile * input_pbpb_central;
	TFile * input_pbpb_perip;
   
   //centrality 0% to 10% 
	  input_pbpb_central = new TFile("rootfiles/Prompt_Spectrum_centRecoeff_D0_PbPb_dpt_cent0to10_ptbin7_y1.root");
	  input_pbpb_perip = new TFile("rootfiles/Prompt_Spectrum_centRecoeff_D0_PbPb_dpt_cent50to100_ptbin7_y1.root");

      TAA_central = 23.20e-9; //error 0.99
	  cent_low = 0;
	  cent_high = 10;
	  Nptbin = 7;

      Draw_RCP(input_pbpb_central, input_pbpb_perip, cent_low, cent_high, Nptbin, TAA_central, TAA_perip);

	  input_pbpb_central->Close();
	  input_pbpb_perip->Close();
   
   //centrality 10% to 30% 
	  input_pbpb_central = new TFile("rootfiles/Prompt_Spectrum_centRecoeff_D0_PbPb_dpt_cent10to30_ptbin7_y1.root");
	  input_pbpb_perip = new TFile("rootfiles/Prompt_Spectrum_centRecoeff_D0_PbPb_dpt_cent50to100_ptbin7_y1.root");

      TAA_central = 11.64e-9; //error 0.67
	  cent_low = 10;
	  cent_high = 30;
	  Nptbin = 7;

      Draw_RCP(input_pbpb_central, input_pbpb_perip, cent_low, cent_high, Nptbin, TAA_central, TAA_perip);

	  input_pbpb_central->Close();
	  input_pbpb_perip->Close();
   
   //centrality 30% to 50% 
	  input_pbpb_central = new TFile("rootfiles/Prompt_Spectrum_centRecoeff_D0_PbPb_dpt_cent30to50_ptbin7_y1.root");
	  input_pbpb_perip = new TFile("rootfiles/Prompt_Spectrum_centRecoeff_D0_PbPb_dpt_cent50to100_ptbin7_y1.root");

      TAA_central = 3.92e-9;  //error 0.37
	  cent_low = 30;
	  cent_high = 50;
	  Nptbin = 7;

      Draw_RCP(input_pbpb_central, input_pbpb_perip, cent_low, cent_high, Nptbin, TAA_central, TAA_perip);

	  input_pbpb_central->Close();
	  input_pbpb_perip->Close();
	
}
