#define BIN_NUM 396
#define HMIN 1      //pPb_pt:5,pPb_y:-2,pp_pt:9,pp_y:0
#define HMAX 100     //pPb_pt:55,pPb_y:2,pp_pt:120,pp_y:2.25

#define REBIN 12     //pPb_pt:6,pPb_y:4,pp_pt:8,pp_y:4
#define REBINp 13    //pPb_pt:7,pPb_y:5,pp_pt:9,pp_y:5

#define BR 0.0388
#define ERROR_BR_PERCEN 0.013

#define NPT  14
double ptbins[NPT+1] = {0,1.5,2.5,3.5,4.5,5.5,7,9,11,13,16,20,28,40,100};

#define ERROR_SYS_ACCEFF_PERCEN 0.20

//double ERROR_SYS_TKEFF_PERCEN = 7.8e-2;
double ERROR_SYS_TKEFF_PERCEN = 9.3e-2;
//double ERROR_SYS_FIT_PERCEN_cent0to100_10ptbin[10] = { 16.0e-2, 11.0e-2, 5.9e-2, 4.6e-2, 4.3e-2, 7.1e-2, 4.2e-2, 4.4e-2, 8.5e-2, 13.8e-2};
//double ERROR_SYS_FIT_PERCEN_cent0to10_9ptbin[9] = { 31.1e-2, 16.9e-2, 12.0e-2, 14.4e-2, 17.8e-2, 13.0e-2, 10.1e-2, 7.1e-2, 23.9e-2};
//double ERROR_SYS_FIT_PERCEN_cent0to20_9ptbin[9] = { 26.9e-2, 11.9e-2, 8.9e-2, 8.5e-2, 9.5e-2, 7.2e-2, 7.3e-2, 6.9e-2, 22.0e-2};

double *syserrorPer_fit;

void Calculate_Bfraction( int Nptbin, TFile *input_data_raw, TFile *input_mc_BtoDeff, TFile *input_BtoD, int cent_low, int cent_high, double NEVT, double TAA, double ERROR_TAA_PERCEN)
{

    cout << "*******************************************************************" << endl;
    cout << " **************  cent_low: " << cent_low << "     " << "cent_high: " << cent_high << " ******************* " << endl;

	char cfgname[200];
	char outputfile[200];

    gStyle->SetOptTitle(0);
    gStyle->SetOptStat(0);
    TH1::SetDefaultSumw2();

//    if( cent_low == 0 && cent_high == 100 )  ERROR_SYS_TKEFF_PERCEN = 14.0e-2;
//    if( cent_low == 0 && cent_high == 10 )  ERROR_SYS_TKEFF_PERCEN = 16.0e-2;
//    if( cent_low == 0 && cent_high == 20 )  ERROR_SYS_TKEFF_PERCEN = 16.0e-2;
//    if( cent_low == 10 && cent_high == 30 )  ERROR_SYS_TKEFF_PERCEN = 16.0e-2;
//    if( cent_low == 30 && cent_high == 50 )  ERROR_SYS_TKEFF_PERCEN = 4.0e-2;
//    if( cent_low == 50 && cent_high == 100 )  ERROR_SYS_TKEFF_PERCEN = 4.0e-2;
//
//    syserrorPer_fit = new double[Nptbin];
//
//    for( int i = 0; i < Nptbin; i++ )  syserrorPer_fit[i] = 0;
//
//    if( cent_low == 0 && cent_high == 100 && Nptbin == 10)
//    {
//        for( int i = 0; i < Nptbin; i++ )
//            syserrorPer_fit[i] = ERROR_SYS_FIT_PERCEN_cent0to100_10ptbin[i];
//    }
//
//    if( cent_low == 0 && cent_high == 10 && Nptbin == 9)
//    {
//        for( int i = 0; i < Nptbin; i++ )
//            syserrorPer_fit[i] = ERROR_SYS_FIT_PERCEN_cent0to10_9ptbin[i];
//    }
//
//    if( cent_low == 0 && cent_high == 20 && Nptbin == 9)
//    {
//        for( int i = 0; i < Nptbin; i++ )
//            syserrorPer_fit[i] = ERROR_SYS_FIT_PERCEN_cent0to20_9ptbin[i];
//    }


	TH1D * d0raw_data = ( TH1D * ) input_data_raw->Get("N_mb_expobkg");
	TH1D * recoeff_BtoD = ( TH1D * ) input_mc_BtoDeff->Get("d0accxeff_pt");


	TH1D * BtoD_max_raa = (TH1D *)input_BtoD->Get("hDFromBPtMax");
	TH1D * BtoD_central_raa = (TH1D *)input_BtoD->Get("hDFromBPtCentral");
	TH1D * BtoD_min_raa = (TH1D *)input_BtoD->Get("hDFromBPtMin");

	BtoD_max_raa->Scale(0.5);  //Change to for D0 only
	BtoD_central_raa->Scale(0.5);
	BtoD_min_raa->Scale(0.5);

//	cout << " bin width: " << BtoD_max_raa->GetBinWidth(10) << "    " << BtoD_central_raa->GetBinWidth(10) << "   " << BtoD_min_raa->GetBinWidth(10) << endl;

    double bin_edge[BIN_NUM+1];

    for( int i = 0; i < BIN_NUM+1; i++ )
    {
		bin_edge[i] = 1.0 + 0.25 * i; //0.25 is the binwidth of BtoD_max_raa
    }

	TH1D * BtoD_max_raa_range2to100 = (TH1D *) BtoD_max_raa->Rebin(BIN_NUM, "BtoD_max_raa_range2to100", bin_edge);
	TH1D * BtoD_central_raa_range2to100 = (TH1D *) BtoD_central_raa->Rebin(BIN_NUM, "BtoD_central_raa_range2to100", bin_edge);
	TH1D * BtoD_min_raa_range2to100 = (TH1D *) BtoD_min_raa->Rebin(BIN_NUM, "BtoD_min_raa_range2to100", bin_edge);

	TCanvas * cfg_fonllBtoD = new TCanvas("cfg_fonllBtoD","cfg_fonllBtoD");
	gPad->SetLogy();
	BtoD_max_raa_range2to100->Draw();
	BtoD_central_raa_range2to100->Draw("same");
	BtoD_min_raa_range2to100->Draw("same");

    //Rebin Edge
    double rebin[REBINp] = {1.5,2.5,3.5,4.5,5.5,7,9,11,13,16,20,28,40};
  
    TH1F* hpt_rebin = (TH1F*)BtoD_central_raa_range2to100->Rebin(REBIN,"hpt_rebin",rebin);
    TH1F* hminall_rebin = (TH1F*)BtoD_min_raa_range2to100->Rebin(REBIN,"hminall_rebin",rebin);
    TH1F* hmaxall_rebin = (TH1F*)BtoD_max_raa_range2to100->Rebin(REBIN,"hmaxall_rebin",rebin);
  
    //bin middle
    double apt[REBIN] = {2,3,4,5,6.25,8,10,12,14.5,18,24,34};//pPb_pt
    //bin half width
    double aptl[REBIN] = {0.5,0.5,0.5,0.5,0.75,1,1,1,1.5,2,4,6};//pPb_pt
    double asigma[REBIN],aminall[REBIN],amaxall[REBIN],aerrorl[REBIN],aerrorh[REBIN];
    //number of every rebined bin
    double bin_num[REBIN] = {4,4,4,4,6,8,8,8,12,16,32,48};//pPb_pt
  
    for( int j=0;j<REBIN;j++)
    {
		float tem;
  
        tem = hpt_rebin->GetBinContent(j+1);
        asigma[j] = tem/bin_num[j];
  
        tem = hminall_rebin->GetBinContent(j+1);
        aminall[j] = tem/bin_num[j];
  
        tem = hmaxall_rebin->GetBinContent(j+1);
        amaxall[j] = tem/bin_num[j];

		aerrorl[j] = asigma[j]-aminall[j];//all,sc,mass,pdf
		aerrorh[j] = amaxall[j]-asigma[j];//all,sc,mass,pdf
	}

	TGraphAsymmErrors* gaeSigmaBtoD = new TGraphAsymmErrors(REBIN, apt, asigma, aptl, aptl, aerrorl, aerrorh);
	gaeSigmaBtoD->SetName("gaeSigmaBtoD");

	double bfraction[REBIN], bfractionerror_lower[REBIN], bfractionerror_upper[REBIN];
	double promptfraction[REBIN], promptfractionerror_lower[REBIN], promptfractionerror_upper[REBIN];

	int Nptbincount = 12;  // to add the pt bin 28 to 40 GeV w/o changing the framework
	if( Nptbin == 11 )  Nptbincount = 12;

	for( int i = 0; i < Nptbincount; i++ )
	{
		double ptrange = ptbins[i+2] - ptbins[i+1];
//		cout << "histo bin width: " << recoeff_BtoD->GetBinWidth(i+2) << "   pt range: " << ptrange << endl;
		
		double eff = recoeff_BtoD->GetBinContent(i+2);
		double error_eff = recoeff_BtoD->GetBinError(i+2);
		double errorPer_eff = error_eff/eff;
		double entries_Dzero_raw = d0raw_data->GetBinContent(i+2)*ptrange;
		double error_entries_Dzero_raw = d0raw_data->GetBinError(i+2)*ptrange;
		double errorPer_entries_Dzero_raw = error_entries_Dzero_raw/entries_Dzero_raw;

		
		bfraction[i] = TAA * asigma[i] * eff  * BR * NEVT * ptrange / ( 0.5 * entries_Dzero_raw );

		double symmetricerrorPer_squaresum = ERROR_SYS_TKEFF_PERCEN * ERROR_SYS_TKEFF_PERCEN + ERROR_SYS_ACCEFF_PERCEN * ERROR_SYS_ACCEFF_PERCEN + ERROR_BR_PERCEN * ERROR_BR_PERCEN + ERROR_TAA_PERCEN * ERROR_TAA_PERCEN + errorPer_eff * errorPer_eff /*+ errorPer_entries_Dzero_raw * errorPer_entries_Dzero_raw*/;

		bfractionerror_lower[i] = bfraction[i] * TMath::Sqrt( aerrorl[i]/asigma[i] * aerrorl[i]/asigma[i] + 4.0 * symmetricerrorPer_squaresum );
//		cout << "  aerrorl[i]/asigma[i]: " << aerrorl[i]/asigma[i] << "    symmetricerrorPer_squaresum: " << TMath::Sqrt( 4.0 * symmetricerrorPer_squaresum )<< endl;

		bfractionerror_upper[i] = bfraction[i] * TMath::Sqrt( aerrorh[i]/asigma[i] * aerrorh[i]/asigma[i] + 4.0 * symmetricerrorPer_squaresum);
//		cout << " b fraction relative error, lower: " << bfractionerror_lower[i]/bfraction[i] << "  upper: " << bfractionerror_upper[i]/bfraction[i] << endl;

//		cout << " bfraction: " << bfraction[i] << endl;

		promptfraction[i] = 1.0 - bfraction[i];
		promptfractionerror_lower[i] = bfractionerror_upper[i] ;
		promptfractionerror_upper[i] = bfractionerror_lower[i] ;

//		cout << " prompt fraction: " <<  promptfraction[i] << "  lower error: " << promptfractionerror_lower[i] << "  upper error: " << promptfractionerror_upper[i] << endl;
		cout << " prompt relative error,  lower: " <<  promptfractionerror_lower[i]/promptfraction[i] << "   upper: " << promptfractionerror_upper[i]/promptfraction[i] << endl;

	}
	
	TGraphAsymmErrors* gaeBfraction = new TGraphAsymmErrors(REBIN, apt, bfraction, aptl, aptl, bfractionerror_lower, bfractionerror_upper);
	gaeBfraction->SetName("gaeBfraction");
	TGraph* gaeBfraction_center = new TGraph(REBIN, apt, bfraction);
	gaeBfraction_center->SetName("gaeBfraction_center");

	TCanvas * cfg_Bfraction = new TCanvas("cfg_Bfraction","cfg_Bfraction");

//    gaeBfraction->GetXaxis()->SetRangeUser(2.5, 28);
//	if( cent_low == 0 && cent_high == 100 ) gaeBfraction->GetXaxis()->SetRangeUser(2.5, 40);
    gaeBfraction->GetXaxis()->SetRangeUser(2.5, 40);
	gaeBfraction->GetYaxis()->SetRangeUser(0, 1.0);
	gaeBfraction->GetXaxis()->SetTitle("p_{T} (GeV/c)");
	gaeBfraction->GetYaxis()->SetTitle("Non-prompt D^{0} fraction");
	gaeBfraction->SetLineWidth(0.5);
	gaeBfraction->SetMarkerStyle(21);
	gaeBfraction->SetMarkerSize(1.0);
	gaeBfraction->SetMarkerColor(4.0);
	gaeBfraction->SetLineColor(4.0);
	gaeBfraction->SetFillStyle(0);
	gaeBfraction->SetFillColor(0);
	gaeBfraction->Draw("A2");
	gaeBfraction_center->SetMarkerStyle(21);
	gaeBfraction_center->SetMarkerSize(1.0);
	gaeBfraction_center->SetMarkerColor(4.0);
	gaeBfraction_center->Draw("Psame");

//    sprintf(cfgname,"plots/cfg_Bfraction_ptbin_%d_cent%dto%d_y1.png", NPT, cent_low, cent_high);
//	cfg_Bfraction->SaveAs(cfgname);
//	sprintf(cfgname,"plots/cfg_Bfraction_ptbin_%d_cent%dto%d_y1.pdf", NPT, cent_low, cent_high);
//	cfg_Bfraction->SaveAs(cfgname);
	
	TGraphAsymmErrors* gaePromptfraction = new TGraphAsymmErrors(REBIN, apt, promptfraction, aptl, aptl, promptfractionerror_lower, promptfractionerror_upper);
	gaePromptfraction->SetName("gaePromptfraction");
	TGraph* gaePromptfraction_center = new TGraph(REBIN, apt, promptfraction);
	gaePromptfraction_center->SetName("gaePromptfraction_center");

    TCanvas * cfg_Promptfraction = new TCanvas("cfg_Promptfraction","cfg_Promptfraction");

//    gaePromptfraction->GetXaxis()->SetRangeUser(2.5, 28);
//	if( cent_low == 0 && cent_high == 100 ) gaePromptfraction->GetXaxis()->SetRangeUser(2.5, 40);
    gaePromptfraction->GetXaxis()->SetRangeUser(2.5, 40);
	gaePromptfraction->GetYaxis()->SetRangeUser(0, 1.0);
	gaePromptfraction->GetXaxis()->SetTitle("p_{T} (GeV/c)");
	gaePromptfraction->GetYaxis()->SetTitle("Prompt D^{0} fraction");
	gaePromptfraction->SetLineWidth(0.5);
	gaePromptfraction->SetMarkerStyle(20);
	gaePromptfraction->SetMarkerSize(1.0);
	gaePromptfraction->SetMarkerColor(2.0);
	gaePromptfraction->SetLineColor(2.0);
	gaePromptfraction->SetFillStyle(0);
	gaePromptfraction->SetFillColor(0);
	gaePromptfraction->Draw("A2");
	gaePromptfraction_center->SetMarkerStyle(20);
	gaePromptfraction_center->SetMarkerSize(1.0);
	gaePromptfraction_center->SetMarkerColor(2.0);
	gaePromptfraction_center->Draw("Psame");

//    sprintf(cfgname,"plots/cfg_Promptfraction_ptbin_%d_cent%dto%d_y1.png", NPT, cent_low, cent_high);
//	cfg_Promptfraction->SaveAs(cfgname);
//    sprintf(cfgname,"plots/cfg_Promptfraction_ptbin_%d_cent%dto%d_y1.pdf", NPT, cent_low, cent_high);
//	cfg_Promptfraction->SaveAs(cfgname);


    TCanvas * cfg_fraction = new TCanvas("cfg_fraction","cfg_fraction");

//    gaeBfraction->GetYaxis()->SetTitle("Fraction");
//    gaeBfraction->Draw("A2");
    gaePromptfraction->GetYaxis()->SetTitle("Prompt fraction in raw yield");
    gaePromptfraction->Draw("A2");
//	gaeBfraction_center->Draw("Psame");
	gaePromptfraction_center->Draw("Psame");


    TLegend *leg = new TLegend(0.35,0.50,0.65,0.55);
	leg->SetTextSize(0.04);
	leg->SetTextAlign(13);
    leg->AddEntry(gaePromptfraction,"Prompt_{} D^{0}_{} fraction_{}, f_{#lower[-0.3]{prompt}}","PF");
//    leg->AddEntry(gaePromptfraction,"f_{prompt}","PF");
//    leg->AddEntry(gaeBfraction,"Non-prompt D^{0} fraction","PF");
    leg->SetBorderSize(0);
    leg->SetFillStyle(0);
    leg->Draw();

    TLatex Tl;
    Tl.SetNDC();
    Tl.SetTextAlign(12);
    Tl.SetTextSize(0.04);
    Tl.SetTextFont(42);
	Tl.DrawLatex(0.125,0.93, "#scale[1.25]{CMS} Simulation");
	Tl.DrawLatex(0.53,0.93, "PbPb #sqrt{s_{NN}} = 2.76 TeV");
    TString centrality;
    centrality.Form("Cent. %d-%d%%", cent_low, cent_high);
    cout << centrality << endl;
    Tl.DrawLatex(0.36,0.45, centrality);
    Tl.DrawLatex(0.36,0.40, "|y| < 1.0");

    sprintf(cfgname,"plots/cfg_fraction_ptbin_%d_cent%dto%d_y1.png", NPT, cent_low, cent_high);
    cfg_fraction->SaveAs(cfgname);
	sprintf(cfgname,"plots/cfg_fraction_ptbin_%d_cent%dto%d_y1.pdf", NPT, cent_low, cent_high);
    cfg_fraction->SaveAs(cfgname);


	TCanvas * cfg_BtoDrebin = new TCanvas("cfg_BtoDrebin","cfg_BtoDrebin");
    gPad->SetLogy();

//    gaeSigmaBtoD->GetXaxis()->SetRangeUser(2.5, 28);
//	if( cent_low == 0 && cent_high == 100 ) gaeSigmaBtoD->GetXaxis()->SetRangeUser(2.5, 40);
    gaeSigmaBtoD->GetXaxis()->SetRangeUser(2.5, 40);
	gaeSigmaBtoD->GetYaxis()->SetRangeUser(1e1, 1e7);
	gaeSigmaBtoD->GetXaxis()->SetTitle("p_{T} (GeV/c)");
	gaeSigmaBtoD->GetYaxis()->SetTitle("d#sigma/dp_{T}(D^{0}) (pb b GeV-1c)");
	gaeSigmaBtoD->SetLineWidth(0.5);
	gaeSigmaBtoD->SetMarkerStyle(20);
	gaeSigmaBtoD->SetMarkerSize(1.0);
	gaeSigmaBtoD->SetMarkerColor(4.0);
	gaeSigmaBtoD->SetLineColor(4.0);
	gaeSigmaBtoD->Draw("AP");

    TLegend * t = new TLegend(0.35, 0.75, 0.85, 0.85);
    t->SetFillColor(0);
    t->AddEntry(gaeSigmaBtoD, "FONLL Non-prompt D^{0} with RAA Scale", "PL");
    t->Draw();

    sprintf(outputfile,"rootfiles/Bfraction_method1_ptbin_%d_cent%dto%d_y1.root", NPT, cent_low, cent_high);
	TFile * output = new TFile(outputfile, "RECREATE");

	cfg_fraction->Write();

	cfg_fonllBtoD->Write();
	BtoD_max_raa_range2to100->Write();
	BtoD_central_raa_range2to100->Write();
	BtoD_min_raa_range2to100->Write();
   
    gaeSigmaBtoD->Write();
	cfg_BtoDrebin->Write();

	gaeBfraction->Write();
	cfg_Bfraction->Write();

	gaePromptfraction->Write();
	cfg_Promptfraction->Write();

	output->Close();
}

void Bfractioncal_method1_y1()
{
	int cent_low = 0;
	int cent_high = 0;
    double NEVT = 0.0;
	double TAA = 0.0;
	double ERROR_TAA_PERCEN = 0.0;
	TFile * input_data_raw;
	TFile * input_mc_BtoDeff;
	TFile * input_BtoD;
	int Nptbin;
	
	cent_low = 0;
	cent_high = 100;
	NEVT = 30172291.0;
	TAA = 5.67E-9;
	ERROR_TAA_PERCEN = 0.057;
	Nptbin = 12;
	TFile * input_data_raw = new TFile("./../Datamassspectrumfit/rootfiles/Dspectrum_pbpb_data_ptbin_14_ptd_unpreMBtrig_0_cent0to100_y1.root");
	TFile * input_mc_BtoDeff = new TFile("./../rootfiles/D0_PbPb_acc_eff_ptbin_14_ybin_6_Bfeeddown_FONLLweight_cent-0to100_RAAscale_y1_Ncollweight1.root");
	TFile * input_BtoD = new TFile("./BtoD_fromyenjie/rapidity1p0/BtoD-0-100.root");
    Calculate_Bfraction( Nptbin, input_data_raw, input_mc_BtoDeff, input_BtoD, cent_low, cent_high, NEVT, TAA, ERROR_TAA_PERCEN);
	
//	cent_low = 0;
//	cent_high = 10;
//	NEVT = 3.07931000000000000e+06;
//	TAA = 23.20e-9;
//	ERROR_TAA_PERCEN = 0.043;
//	Nptbin = 11;
//	TFile * input_data_raw = new TFile("./../Datamassspectrumfit/rootfiles/Dspectrum_pbpb_data_ptbin_14_ptd_unpreMBtrig_0_cent0to10_y1.root");
//	TFile * input_mc_BtoDeff = new TFile("./../rootfiles/D0_PbPb_acc_eff_ptbin_14_ybin_6_Bfeeddown_FONLLweight_cent-0to10_RAAscale_y1_Ncollweight1.root");
//	TFile * input_BtoD = new TFile("./BtoD_fromyenjie/rapidity1p0/BtoD-0-10.root");
//    Calculate_Bfraction( Nptbin, input_data_raw, input_mc_BtoDeff, input_BtoD, cent_low, cent_high, NEVT, TAA, ERROR_TAA_PERCEN);
//
//	cent_low = 0;
//	cent_high = 20;
//	NEVT = 6.09279800000000000e+06;
//	TAA = 18.84e-9;
//	ERROR_TAA_PERCEN = 0.045;
//	Nptbin = 11;
//	TFile * input_data_raw = new TFile("./../Datamassspectrumfit/rootfiles/Dspectrum_pbpb_data_ptbin_14_ptd_unpreMBtrig_0_cent0to20_y1.root");
//	TFile * input_mc_BtoDeff = new TFile("./../rootfiles/D0_PbPb_acc_eff_ptbin_14_ybin_6_Bfeeddown_FONLLweight_cent-0to20_RAAscale_y1_Ncollweight1.root");
//	TFile * input_BtoD = new TFile("./BtoD_fromyenjie/rapidity1p0/BtoD-0-20.root");
//    Calculate_Bfraction( Nptbin, input_data_raw, input_mc_BtoDeff, input_BtoD, cent_low, cent_high, NEVT, TAA, ERROR_TAA_PERCEN);
}
