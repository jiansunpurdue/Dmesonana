void Data_MC_pt_comparison()
{
    gStyle->SetOptTitle(0);
	gStyle->SetOptStat(0);
	gStyle->SetOptFit(1);
	gROOT->ForceStyle();
	TH1::SetDefaultSumw2();

	TFile * input_data = new TFile("./../../rootfiles/Dspectrum_pbpb_data_ptbin_12_ptd_unpreMBtrig_0_cent-0to100.root");
	TH1D* N_mb_data = ( TH1D* ) input_data->Get("N_mb");
//
    TFile * input_mc_Prompt = new TFile("./../../rootfiles/Dspectrum_pbpb_MC_genmatch_histo_ptbin_12_ptd_cent-0to100_FONLLweight_Prompt.root");
    TFile * input_mc_Bfeeddown = new TFile("./../../rootfiles/Dspectrum_pbpb_MC_genmatch_histo_ptbin_12_ptd_cent-0to100_FONLLweight_Bfeeddown.root");
	
	TH1D* N_mb_mc_Prompt = ( TH1D* ) input_mc_Prompt->Get("N_mb_matched");
	TH1D* N_mb_mc_Bfeeddown = ( TH1D* ) input_mc_Bfeeddown->Get("N_mb_matched");

    int bin1 = N_mb_data->FindBin(4.0);
	int bin2 = N_mb_data->FindBin(35.0);

	double datacounts = N_mb_data->Integral(bin1, bin2, "width");
	double mccounts_Prompt = N_mb_mc_Prompt->Integral(bin1, bin2, "width");
	double mccounts_Bfeeddown = N_mb_mc_Bfeeddown->Integral(bin1, bin2, "width");
   
    double BtoDfraction = 0.05;

	N_mb_mc_Prompt->Scale( (1.0 - BtoDfraction) * datacounts/mccounts_Prompt);
	N_mb_mc_Bfeeddown->Scale( BtoDfraction * datacounts/mccounts_Bfeeddown);

	
	TCanvas * cfg_N_data_mc = new TCanvas("cfg_N_data_mc","cfg_N_data_mc");
    TPad *pad1 = new TPad("pad1","top pad",0.0,0.3,1.0,1.0);
    pad1->Draw();
    TPad *pad2 = new TPad("pad2","bottom pad",0.0,0.0,1.0,0.3);
    pad2->Draw();
  
    pad1->cd();
    gPad->SetLogy();

	THStack* N_mb_mc_total = new THStack("N_mb_mc_total","N_mb_mc_total");

    N_mb_mc_Bfeeddown->SetLineColor(2.0);
    N_mb_mc_Bfeeddown->SetFillStyle(3345);
    N_mb_mc_Bfeeddown->SetFillColor(2.0);
    N_mb_mc_Bfeeddown->SetLineWidth(2);
    N_mb_mc_Bfeeddown->SetStats(0);
	N_mb_mc_Bfeeddown->GetXaxis()->SetRangeUser(4.0, 35.0);
	N_mb_mc_Bfeeddown->GetYaxis()->SetRangeUser(1e-2, 1e4);
    N_mb_mc_total->Add(N_mb_mc_Bfeeddown, "HISTe");

    N_mb_mc_Prompt->SetLineColor(4.0);
    N_mb_mc_Prompt->SetFillStyle(3345);
    N_mb_mc_Prompt->SetFillColor(4.0);
    N_mb_mc_Prompt->SetLineWidth(2);
    N_mb_mc_Prompt->SetStats(0);
	N_mb_mc_Prompt->GetXaxis()->SetRangeUser(4.0, 35.0);
	N_mb_mc_Prompt->GetYaxis()->SetRangeUser(1e-2, 1e4);
    N_mb_mc_total->Add(N_mb_mc_Prompt, "HISTe");

    N_mb_data->SetLineColor(1.0);
    N_mb_data->SetMarkerColor(1.0);
    N_mb_data->SetMarkerStyle(20);
    N_mb_data->SetMarkerSize(0.8);
    N_mb_data->SetStats(0);

	N_mb_mc_Prompt->Add(N_mb_mc_Bfeeddown);
	N_mb_mc_Prompt->GetXaxis()->SetRangeUser(4.0, 35.0);
	N_mb_mc_Prompt->GetYaxis()->SetRangeUser(1e-2, 1e4);
	N_mb_mc_Prompt->GetYaxis()->SetTitle("dN/dp_{T}");
	N_mb_mc_Prompt->GetXaxis()->SetTitle("D^{0} p_{T} (GeV/c)");
	N_mb_mc_Prompt->Draw("HISTe");
	N_mb_mc_Bfeeddown->Draw("HISTesame");
	N_mb_data->Draw("same");
//    N_mb_mc_total->Draw();
//	N_mb_mc_total->GetXaxis()->SetRangeUser(4.0, 35.0);
//	N_mb_mc_total->GetYaxis()->SetRangeUser(1e-2, 1e4);
////	N_mb_mc_total->Draw();
//    N_mb_data->Draw("same");


  TLegend *leg = new TLegend(0.55,0.7,0.85,0.85);
  leg->AddEntry(N_mb_data,"Data D^{0}","PL");
  leg->AddEntry(N_mb_mc_Prompt,"MC Prompt D^{0}","f");
  leg->AddEntry(N_mb_mc_Bfeeddown,"MC B Feed-down D^{0}","f");
  leg->SetBorderSize(0);
  leg->SetFillStyle(0);
  leg->Draw();

	pad2->cd();
	TH1D * ratio_data_mc_total = ( TH1D *) N_mb_data->Clone("ratio_data_mc_total");
	ratio_data_mc_total->SetStats(1);
	ratio_data_mc_total->Divide( N_mb_data, N_mb_mc_Prompt, 1.0, 1.0);
	ratio_data_mc_total->GetXaxis()->SetRangeUser(4.0, 35.0);
	ratio_data_mc_total->GetYaxis()->SetRangeUser(0.0, 2.5);
	ratio_data_mc_total->GetYaxis()->SetTitle("Data/MC");
	TF1* fit_fun = new TF1("fit_fun", "pol2(0)", 3.5, 40.0);
	fit_fun->SetLineColor(8);
	fit_fun->SetLineStyle(2);
	ratio_data_mc_total->Fit(fit_fun, "I", "", 3.5, 40.0);
	ratio_data_mc_total->Draw();


	TFile * output = new TFile("MC_to_Data_raw.root","RECREATE");
    cfg_N_data_mc->Write();
	N_mb_data->Write();
	N_mb_mc_Bfeeddown->Write();
	N_mb_mc_Prompt->Write();
	N_mb_mc_total->Write();
	ratio_data_mc_total->Write();
	output->Close();



}
