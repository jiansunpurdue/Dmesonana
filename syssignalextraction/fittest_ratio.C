void fittest_ratio()
{
	gStyle->SetOptStat(0);
	gStyle->SetOptTitle(0);
    TH1::SetDefaultSumw2();

//	TFile * input1 = new TFile("rootfiles/Dspectrum_pbpb_data_ptbin_11_ptd_unpreMBtrig_0_cent-0to100_fit.root");
//	TFile * input2 = new TFile("rootfiles/Dspectrum_pbpb_data_ptbin_11_ptd_unpreMBtrig_0_cent-0to100_fitexpo_tunefirst.root");
//	TFile * input3 = new TFile("rootfiles/Dspectrum_pbpb_data_ptbin_11_ptd_unpreMBtrig_0_cent-0to100_fitlinear_tunefirst.root");
	
	TFile * input1 = new TFile("./rootfiles/Dspectrum_pbpb_data_ptbin_12_ptd_unpreMBtrig_0_cent-0to100_doublecountedpoly2.root");
	TFile * input2 = new TFile("./rootfiles/Dspectrum_pbpb_data_ptbin_12_ptd_unpreMBtrig_0_cent-0to100_doublecountedexpo.root");
	TFile * input3 = new TFile("./rootfiles/Dspectrum_pbpb_data_ptbin_12_ptd_unpreMBtrig_0_cent-0to100_doublecountedpoly1.root");

	TH1D * N_mb_fittest_poly2 = (TH1D *) input1->Get("N_mb");
	TH1D * N_mb_fittest_expo = (TH1D *) input2->Get("N_mb");
	TH1D * N_mb_fittest_linear = (TH1D *) input3->Get("N_mb");

    TCanvas *c = new TCanvas("c","c",600,600);
    TPad *pad1 = new TPad("pad1","top pad",0.0,0.3,1.0,1.0);
    pad1->Draw();
    TPad *pad2 = new TPad("pad2","bottom pad",0.0,0.0,1.0,0.3);
    pad2->Draw();

	pad1->cd();
	gPad->SetLogy();
	N_mb_fittest_poly2->GetXaxis()->SetRangeUser(4.0, 35);
	N_mb_fittest_poly2->SetLineColor(1.0);
	N_mb_fittest_expo->SetLineColor(4.0);
	N_mb_fittest_linear->SetLineColor(2.0);
	N_mb_fittest_poly2->SetLineWidth(1.8);
	N_mb_fittest_expo->SetLineWidth(1.8);
	N_mb_fittest_linear->SetLineWidth(1.8);

	N_mb_fittest_poly2->GetXaxis()->SetTitle("D0 p_{T} (GeV/c)");
	N_mb_fittest_poly2->GetYaxis()->SetTitle("Raw dN/dp_{T}");
	N_mb_fittest_poly2->Draw();
	N_mb_fittest_expo->Draw("same");
//	N_mb_fittest_linear->Draw("same");

    TLegend * t = new TLegend(0.35, 0.7, 0.85, 0.85);
    t->SetFillColor(0);
    t->AddEntry(N_mb_fittest_poly2, "Poly2 Bkg");
    t->AddEntry(N_mb_fittest_expo, "Expo Bkg");
	t->AddEntry(N_mb_fittest_linear, "Linear Bkg");
    t->Draw();
  
    TH1D * ratio_expo_poly2 = ( TH1D *) N_mb_fittest_expo->Clone("ratio_expo_poly2");
	ratio_expo_poly2->Divide(N_mb_fittest_expo, N_mb_fittest_poly2, 1.0, 1.0, "B");

	TH1D * ratio_linear_poly2 = ( TH1D *) N_mb_fittest_linear->Clone("ratio_linear_poly2");
    ratio_linear_poly2->Divide(N_mb_fittest_linear, N_mb_fittest_poly2, 1.0, 1.0, "B");

    pad2->cd();
//	ratio_expo_poly2->SetLineWidth(1.5);
//	ratio_expo_poly2->SetLineColor(4.0);
	ratio_expo_poly2->GetYaxis()->SetTitle("* / Poly2 Bkg");
	ratio_expo_poly2->GetYaxis()->SetRangeUser(0.8, 1.3);
	ratio_expo_poly2->GetXaxis()->SetRangeUser(4.0, 35);
	ratio_expo_poly2->GetYaxis()->SetLabelSize(0.07);
	ratio_expo_poly2->GetXaxis()->SetLabelSize(0.07);
	ratio_expo_poly2->GetYaxis()->SetTitleSize(0.08);
	ratio_expo_poly2->GetYaxis()->SetTitleOffset(0.6);
	ratio_expo_poly2->Draw("HIST");

    ratio_linear_poly2->Draw("HISTsame");

}
