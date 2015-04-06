void fittest_ratio_wdoublecounted()
{
	gStyle->SetOptStat(0);
	gStyle->SetOptTitle(0);
    TH1::SetDefaultSumw2();
	
	TFile * input1 = new TFile("./../rootfiles/Dspectrum_pbpb_data_ptbin_12_ptd_unpreMBtrig_0_cent-0to100.root");
//	TFile * input2 = new TFile("rootfiles/Dspectrum_pbpb_data_ptbin_12_ptd_unpreMBtrig_0_cent-0to100_doublecountedpoly2.root");
    TFile * input2 = new TFile("rootfiles/Dspectrum_pbpb_data_ptbin_12_ptd_unpreMBtrig_0_cent-0to100_floatdoublecountedpoly2.root");
//    TFile * input1 = new TFile("rootfiles/Dspectrum_pbpb_data_ptbin_11_ptd_unpreMBtrig_0_cent-0to100_fitexpo_tunefirst.root");
//	TFile * input2 = new TFile("rootfiles/Dspectrum_pbpb_data_ptbin_11_ptd_unpreMBtrig_0_cent-0to100_fittest_expbkg_tunefirst.root");

	TH1D * N_mb_fit_nodoublecountedpdf = (TH1D *) input1->Get("N_mb");
	TH1D * N_mb_fit_doublecountedpdf = (TH1D *) input2->Get("N_mb");

    TCanvas *c = new TCanvas("c","c",600,600);
    TPad *pad1 = new TPad("pad1","top pad",0.0,0.3,1.0,1.0);
    pad1->Draw();
    TPad *pad2 = new TPad("pad2","bottom pad",0.0,0.0,1.0,0.3);
    pad2->Draw();

	pad1->cd();
	gPad->SetLogy();
	N_mb_fit_nodoublecountedpdf->GetXaxis()->SetRangeUser(4.0, 35);
	N_mb_fit_nodoublecountedpdf->SetLineColor(1.0);
	N_mb_fit_doublecountedpdf->SetLineColor(4.0);
	N_mb_fit_nodoublecountedpdf->SetLineWidth(1.8);
	N_mb_fit_doublecountedpdf->SetLineWidth(1.8);

	N_mb_fit_nodoublecountedpdf->GetXaxis()->SetTitle("D0 p_{T} (GeV/c)");
	N_mb_fit_nodoublecountedpdf->GetYaxis()->SetTitle("Raw dN/dp_{T}");
	N_mb_fit_nodoublecountedpdf->Draw();
	N_mb_fit_doublecountedpdf->Draw("same");

    TLegend * t = new TLegend(0.35, 0.7, 0.85, 0.85);
    t->SetFillColor(0);
    t->AddEntry(N_mb_fit_nodoublecountedpdf, "Poly2 + Gaussian (Default)");
    t->AddEntry(N_mb_fit_doublecountedpdf, "Poly2 + Gaussian + Misid Gaussian");
    t->Draw();
  
    TH1D * ratio_doublecounted_nodoublecounted = ( TH1D *) N_mb_fit_doublecountedpdf->Clone("ratio_doublecounted_nodoublecounted");
	ratio_doublecounted_nodoublecounted->Divide(N_mb_fit_doublecountedpdf, N_mb_fit_nodoublecountedpdf, 1.0, 1.0, "B");

    pad2->cd();
//	ratio_doublecounted_nodoublecounted->SetLineWidth(1.5);
//	ratio_doublecounted_nodoublecounted->SetLineColor(4.0);
	ratio_doublecounted_nodoublecounted->GetYaxis()->SetTitle("Ratio to Default");
	ratio_doublecounted_nodoublecounted->GetYaxis()->SetRangeUser(0.9, 1.02);
	ratio_doublecounted_nodoublecounted->GetXaxis()->SetRangeUser(4.0, 35);
	ratio_doublecounted_nodoublecounted->GetYaxis()->SetLabelSize(0.07);
	ratio_doublecounted_nodoublecounted->GetXaxis()->SetLabelSize(0.07);
	ratio_doublecounted_nodoublecounted->GetYaxis()->SetTitleSize(0.08);
	ratio_doublecounted_nodoublecounted->GetYaxis()->SetTitleOffset(0.6);
	ratio_doublecounted_nodoublecounted->Draw("HIST");

}
