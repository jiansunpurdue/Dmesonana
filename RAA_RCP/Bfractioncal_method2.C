#define BIN_NUM 392
#define HMIN 2      //pPb_pt:5,pPb_y:-2,pp_pt:9,pp_y:0
#define HMAX 100     //pPb_pt:55,pPb_y:2,pp_pt:120,pp_y:2.25

#define REBIN 10     //pPb_pt:6,pPb_y:4,pp_pt:8,pp_y:4
#define REBINp 11    //pPb_pt:7,pPb_y:5,pp_pt:9,pp_y:5

#define NPT  12
double ptbins[NPT+1] = {0,3.5,4.5,5.5,7,9,11,13,16,20,28,40,100};

void Bfractioncal_method2()
{
    gStyle->SetOptTitle(0);
    gStyle->SetOptStat(0);
    TH1::SetDefaultSumw2();

	TFile* promptfonllinput = new TFile("./../FONLL/fonll/outputDzero.root");
	TGraphAsymmErrors * d0fonllspectrum = ( TGraphAsymmErrors *) promptfonllinput->Get("gaeSigmaDzero");

	TFile * input_mc_BtoDeff = new TFile("./../D0_PbPb_acc_eff_ptbin_12_ybin_6_Bfeeddown_FONLLweight_cent-0to100.root");
	TFile * input_mc_PromptDeff = new TFile("./../D0_PbPb_acc_eff_ptbin_12_ybin_6_prompt_FONLLweight_cent-0to100.root");

	TH1D * recoeff_PromptD = ( TH1D * ) input_mc_PromptDeff->Get("d0accxeff_pt");
	TH1D * recoeff_BtoD = ( TH1D * ) input_mc_BtoDeff->Get("d0accxeff_pt");

	TFile * input_BtoD = new TFile("./BtoD_fromyenjie/BtoD-0-100.root");

	TH1D * BtoD_max_raa = (TH1D *)input_BtoD->Get("hDFromBPtMax");
	TH1D * BtoD_central_raa = (TH1D *)input_BtoD->Get("hDFromBPtCentral");
	TH1D * BtoD_min_raa = (TH1D *)input_BtoD->Get("hDFromBPtMin");
	TH1D * BtoD_central_noraa = (TH1D *)input_BtoD->Get("hDFromBPt");

	BtoD_max_raa->Scale(0.5);
	BtoD_central_raa->Scale(0.5);
	BtoD_min_raa->Scale(0.5);
	BtoD_central_noraa->Scale(0.5);

	cout << " bin width: " << BtoD_max_raa->GetBinWidth(10) << "    " << BtoD_central_raa->GetBinWidth(10) << "   " << BtoD_min_raa->GetBinWidth(10) << endl;

    double bin_edge[BIN_NUM+1];  //change to range 2.0 to 100 GeV with 392 bins to make the same with present framework

    for( int i = 0; i < BIN_NUM+1; i++ )
    {
		bin_edge[i] = 2.0 + 0.25 * i; //0.25 is the binwidth of BtoD_max_raa
    }

	TH1D * BtoD_max_raa_range2to100 = (TH1D *) BtoD_max_raa->Rebin(BIN_NUM, "BtoD_max_raa_range2to100", bin_edge);
	TH1D * BtoD_central_raa_range2to100 = (TH1D *) BtoD_central_raa->Rebin(BIN_NUM, "BtoD_central_raa_range2to100", bin_edge);
	TH1D * BtoD_min_raa_range2to100 = (TH1D *) BtoD_min_raa->Rebin(BIN_NUM, "BtoD_min_raa_range2to100", bin_edge);
	TH1D * BtoD_central_noraa_range2to100 = (TH1D *) BtoD_central_noraa->Rebin(BIN_NUM, "BtoD_central_noraa_range2to100", bin_edge);

	TCanvas * cfg_fonllBtoD = new TCanvas("cfg_fonllBtoD","cfg_fonllBtoD");
	gPad->SetLogy();
	BtoD_max_raa_range2to100->Draw();
	BtoD_central_raa_range2to100->Draw("same");
	BtoD_min_raa_range2to100->Draw("same");

	BtoD_central_noraa_range2to100->SetLineColor(2.0);
	BtoD_central_noraa_range2to100->SetMarkerStyle(1.0);
	BtoD_central_noraa_range2to100->SetMarkerColor(2.0);
	BtoD_central_noraa_range2to100->Draw("same");

	cfg_fonllBtoD->SaveAs("plots/BtoD_spectrum_noraa_withraa.png");
	cfg_fonllBtoD->SaveAs("plots/BtoD_spectrum_noraa_withraa.pdf");

    //Rebin Edge
    double rebin[REBINp] = {3.5,4.5,5.5,7,9,11,13,16,20,28,40};
  
    TH1F* hpt_rebin = (TH1F*) BtoD_central_raa_range2to100->Rebin(REBIN,"hpt_rebin",rebin);
    TH1F* hminall_rebin = (TH1F*) BtoD_min_raa_range2to100->Rebin(REBIN,"hminall_rebin",rebin);
    TH1F* hmaxall_rebin = (TH1F*) BtoD_max_raa_range2to100->Rebin(REBIN,"hmaxall_rebin",rebin);
	TH1F* hpt_noraa_rebin = (TH1F*) BtoD_central_noraa_range2to100->Rebin(REBIN,"hpt_noraa_rebin",rebin);
  
    //bin middle
    double apt[REBIN] = {4,5,6.25,8,10,12,14.5,18,24,34};//pPb_pt
    //bin half width
    double aptl[REBIN] = {0.5,0.5,0.75,1,1,1,1.5,2,4,6};//pPb_pt
    //number of every rebined bin
    double bin_num[REBIN] = {4,4,6,8,8,8,12,16,32,48};//pPb_pt
    double asigma[REBIN],aminall[REBIN],amaxall[REBIN],aerrorl[REBIN],aerrorh[REBIN];

	double asigma_noraa[REBIN],aminall_noraa[REBIN],amaxall_noraa[REBIN], aerrorl_noraa[REBIN], aerrorh_noraa[REBIN];
  
    for( int j=0;j<REBIN;j++)
    {
		float tem;
        //for no raa scale spectrum
		tem = hpt_noraa_rebin->GetBinContent(j+1);
		asigma_noraa[j] = tem/bin_num[j];

		aerrorl_noraa[j] = 0;
		aerrorh_noraa[j] = 0;

		//for raa scaled spectrum
  
        tem = hpt_rebin->GetBinContent(j+1);
        asigma[j] = tem/bin_num[j];
  
        tem = hminall_rebin->GetBinContent(j+1);
        aminall[j] = tem/bin_num[j];
  
        tem = hmaxall_rebin->GetBinContent(j+1);
        amaxall[j] = tem/bin_num[j];

		aerrorl[j] = asigma[j]-aminall[j];//all,sc,mass,pdf
		aerrorh[j] = amaxall[j]-asigma[j];//all,sc,mass,pdf
	}

	TGraphAsymmErrors* gaeSigmaBtoD_noraascale = new TGraphAsymmErrors(REBIN, apt, asigma_noraa, aptl, aptl, aerrorl_noraa, aerrorh_noraa);

	TGraphAsymmErrors* gaeSigmaBtoD_raascale = new TGraphAsymmErrors(REBIN, apt, asigma, aptl, aptl, aerrorl, aerrorh);

	TCanvas * cfg_BtoDrebin = new TCanvas("cfg_BtoDrebin","cfg_BtoDrebin");
    gPad->SetLogy();

    gaeSigmaBtoD_raascale->GetXaxis()->SetRangeUser(3.5, 40);
	gaeSigmaBtoD_raascale->GetYaxis()->SetRangeUser(1e1, 1e9);
	gaeSigmaBtoD_raascale->GetXaxis()->SetTitle("D^{0} p_{T} (GeV/c)");
	gaeSigmaBtoD_raascale->GetYaxis()->SetTitle("d#sigma/dp_{T}(D^{0}) (pb b GeV-1c)");
	gaeSigmaBtoD_raascale->SetLineWidth(0.5);
	gaeSigmaBtoD_raascale->SetMarkerStyle(20);
	gaeSigmaBtoD_raascale->SetMarkerSize(0.8);
	gaeSigmaBtoD_raascale->SetMarkerColor(4.0);
	gaeSigmaBtoD_raascale->SetLineColor(4.0);
	gaeSigmaBtoD_raascale->Draw("AP");

	gaeSigmaBtoD_noraascale->SetLineWidth(0.5);
	gaeSigmaBtoD_noraascale->SetMarkerStyle(20);
	gaeSigmaBtoD_noraascale->SetMarkerSize(0.8);
	gaeSigmaBtoD_noraascale->SetMarkerColor(2.0);
	gaeSigmaBtoD_noraascale->SetLineColor(2.0);
	gaeSigmaBtoD_noraascale->Draw("Psame");

    d0fonllspectrum->SetLineWidth(0.5);
	d0fonllspectrum->SetMarkerStyle(20);
	d0fonllspectrum->SetMarkerSize(0.8);
	d0fonllspectrum->SetMarkerColor(1.0);
	d0fonllspectrum->SetLineColor(1.0);
	d0fonllspectrum->Draw("Psame");

    TLegend * t = new TLegend(0.35, 0.75, 0.85, 0.85);
    t->SetFillColor(0);
    t->AddEntry(d0fonllspectrum, "FONLL Prompt D^{0}", "PL");
	t->AddEntry(gaeSigmaBtoD_noraascale,  "FONLL B Feed-down D^{0} (Central Value)", "PL");
    t->AddEntry(gaeSigmaBtoD_raascale, "FONLL B Feed-down D^{0} with RAA Scale", "PL");
    t->Draw();

    cfg_BtoDrebin->SaveAs("plots/BtoDrebin_spectrum_prompt.png");
    cfg_BtoDrebin->SaveAs("plots/BtoDrebin_spectrum_prompt.pdf");

	TCanvas * cfg_BtoDraa_central = new TCanvas("cfg_BtoDraa_central","cfg_BtoDraa_central");

	TH1F * Raa_BtoD_central_rebin = (TH1F *) hpt_rebin->Clone("Raa_BtoD_central_rebin");
	Raa_BtoD_central_rebin->Divide( hpt_rebin, hpt_noraa_rebin, 1.0, 1.0);

    Raa_BtoD_central_rebin->SetLineWidth(0.5);
	Raa_BtoD_central_rebin->SetMarkerStyle(20);
	Raa_BtoD_central_rebin->SetMarkerSize(0.8);
	Raa_BtoD_central_rebin->SetMarkerColor(4.0);
	Raa_BtoD_central_rebin->SetLineColor(4.0);
	Raa_BtoD_central_rebin->GetYaxis()->SetRangeUser(0.0, 1.0);
	Raa_BtoD_central_rebin->Draw();

    cfg_BtoDraa_central->SaveAs("plots/RAA_rebin_BtoD_centralvalue.png");
    cfg_BtoDraa_central->SaveAs("plots/RAA_rebin_BtoD_centralvalue.pdf");

    double bfraction[REBIN], bfractionerror_lower[REBIN], bfractionerror_upper[REBIN];
    double promptfraction[REBIN], promptfractionerror_lower[REBIN], promptfractionerror_upper[REBIN];

    for( int i = 0; i < REBIN; i++ )
    {
        double eff_BtoD = recoeff_BtoD->GetBinContent(i+2);
        double error_eff_BtoD = recoeff_BtoD->GetBinError(i+2);
		double errorPer_eff_BtoD = error_eff_BtoD/eff_BtoD;
        double eff_PromptD = recoeff_PromptD->GetBinContent(i+2);
        double error_eff_PromptD = recoeff_PromptD->GetBinError(i+2); 
		double errorPer_eff_PromptD = error_eff_PromptD/eff_PromptD;

        double ptrange = ptbins[i+2] - ptbins[i+1];
        cout << "histo bin width: " << recoeff_BtoD->GetBinWidth(i+2) << "   pt range: " << ptrange << endl;

//		cout << " eff_BtoD: " << eff_BtoD << "    asigma_noraa: " << asigma_noraa[i] << endl;
//		cout << " eff_PromptD: " << eff_PromptD << "   prompt: " << d0fonllspectrum->GetY()[i] << endl; 

        double ratio_BtoD_prompt = eff_BtoD * asigma_noraa[i] / (eff_PromptD * d0fonllspectrum->GetY()[i]);
        promptfraction[i] = 1.0/( 1.0 + ratio_BtoD_prompt );

		double errorPer_low_fonll = d0fonllspectrum->GetErrorYlow(i)/d0fonllspectrum->GetY()[i];
		double errorPer_high_fonll = d0fonllspectrum->GetErrorYhigh(i)/d0fonllspectrum->GetY()[i];

		double error_ratio_BtoD_prompt_low = ratio_BtoD_prompt * ( errorPer_eff_BtoD * errorPer_eff_BtoD + errorPer_eff_PromptD * errorPer_eff_PromptD + errorPer_high_fonll * errorPer_high_fonll );
		double error_ratio_BtoD_prompt_high = ratio_BtoD_prompt * ( errorPer_eff_BtoD * errorPer_eff_BtoD + errorPer_eff_PromptD * errorPer_eff_PromptD + errorPer_low_fonll * errorPer_low_fonll );


        promptfractionerror_lower[i] = promptfraction[i] * promptfraction[i] *  error_ratio_BtoD_prompt_high;
        promptfractionerror_upper[i] = promptfraction[i] * promptfraction[i] *  error_ratio_BtoD_prompt_low;
        
		bfraction[i] = 1.0 - promptfraction[i];
        bfractionerror_lower[i] = promptfractionerror_upper[i];
        bfractionerror_upper[i] = promptfractionerror_lower[i];

        cout << " bfraction: " << bfraction[i] << endl;
    }


    TGraphAsymmErrors* gaeBfraction = new TGraphAsymmErrors(REBIN, apt, bfraction, aptl, aptl, bfractionerror_lower, bfractionerror_upper);
    gaeBfraction->SetName("gaeBfraction");
    TCanvas * cfg_Bfraction = new TCanvas("cfg_Bfraction","cfg_Bfraction");

    gaeBfraction->GetXaxis()->SetRangeUser(3.5, 40);
    gaeBfraction->GetYaxis()->SetRangeUser(0, 1.0);
    gaeBfraction->GetXaxis()->SetTitle("D^{0} p_{T} (GeV/c)");
    gaeBfraction->GetYaxis()->SetTitle("B Feed-down D^{0} fraction");
    gaeBfraction->SetLineWidth(0.5);
    gaeBfraction->SetMarkerStyle(20);
    gaeBfraction->SetMarkerSize(0.8);
    gaeBfraction->SetMarkerColor(4.0);
    gaeBfraction->SetLineColor(4.0);
    gaeBfraction->Draw("AP");

    cfg_Bfraction->SaveAs("plots/cfg_Bfraction_0to100_method2.png");
    cfg_Bfraction->SaveAs("plots/cfg_Bfraction_0to100_method2.pdf");

    TGraphAsymmErrors* gaePromptfraction = new TGraphAsymmErrors(REBIN, apt, promptfraction, aptl, aptl, promptfractionerror_lower, promptfractionerror_upper);
    gaePromptfraction->SetName("gaePromptfraction");
    TCanvas * cfg_Promptfraction = new TCanvas("cfg_Promptfraction","cfg_Promptfraction");

    gaePromptfraction->GetXaxis()->SetRangeUser(3.5, 40);
    gaePromptfraction->GetYaxis()->SetRangeUser(0, 1.0);
    gaePromptfraction->GetXaxis()->SetTitle("D^{0} p_{T} (GeV/c)");
    gaePromptfraction->GetYaxis()->SetTitle("Prompt D^{0} fraction");
    gaePromptfraction->SetLineWidth(0.5);
    gaePromptfraction->SetMarkerStyle(20);
    gaePromptfraction->SetMarkerSize(0.8);
    gaePromptfraction->SetMarkerColor(4.0);
    gaePromptfraction->SetLineColor(4.0);
    gaePromptfraction->Draw("AP");

    cfg_Promptfraction->SaveAs("plots/cfg_Promptfraction_0to100_method2.png");
    cfg_Promptfraction->SaveAs("plots/cfg_Promptfraction_0to100_method2.pdf");


    TCanvas * cfg_fraction = new TCanvas("cfg_fraction","cfg_fraction");

    gaeBfraction->GetYaxis()->SetTitle("Fraction");
    gaeBfraction->Draw("AP");
    gaePromptfraction->SetLineColor(2.0);
    gaePromptfraction->SetMarkerColor(2.0);
    gaePromptfraction->Draw("Psame");

    TLegend *leg = new TLegend(0.3,0.55,0.75,0.7);
    leg->AddEntry(gaeBfraction,"B feed-down D^{0} fraction","PL");
    leg->AddEntry(gaePromptfraction,"Prompt D^{0} fraction","PL");
    leg->SetBorderSize(0);
    leg->SetFillStyle(0);
    leg->Draw();

    cfg_fraction->SaveAs("plots/cfg_fraction_0to100_method2.png");
    cfg_fraction->SaveAs("plots/cfg_fraction_0to100_method2.pdf");



    TFile * output = new TFile("Bfraction_method2.root", "RECREATE");

    cfg_fonllBtoD->Write();
    BtoD_max_raa_range2to100->Write();
    BtoD_central_raa_range2to100->Write();
    BtoD_min_raa_range2to100->Write();

    cfg_BtoDrebin->Write();
	gaeSigmaBtoD_noraascale->Write();
	gaeSigmaBtoD_raascale->Write();
	d0fonllspectrum->Write();

	cfg_BtoDraa_central->Write();
	Raa_BtoD_central_rebin->Write();

    gaeBfraction->Write();
    cfg_Bfraction->Write();

    gaePromptfraction->Write();
    cfg_Promptfraction->Write();

    output->Close();
  
}
