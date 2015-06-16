void Dmeson_RAFONLL_Centrality()
{
    gStyle->SetOptTitle(0);
	gStyle->SetOptStat(0);
	TH1::SetDefaultSumw2();

	TFile * input_cent0to20 = new TFile("RAA_D0_PbPb_spectrum_fonll_effunpre_cent0to20_ptbin8.root");
	TGraphAsymmErrors * D0_fonll_raa_errordata_cent0to20 = ( TGraphAsymmErrors * ) input_cent0to20->Get("D0_fonll_raa_errordata");
	TGraphAsymmErrors * D0_fonll_raa_errorfonll_cent0to20 = ( TGraphAsymmErrors * ) input_cent0to20->Get("D0_fonll_raa_errorfonll");
	TH1D * D0_pbpb_spectrum_cent0to20 = ( TH1D * ) input_cent0to20->Get("D0_pbpb_spectrum");

	TFile * input_cent40to80 = new TFile("RAA_D0_PbPb_spectrum_fonll_effunpre_cent40to80_ptbin8.root");
	TGraphAsymmErrors * D0_fonll_raa_errordata_cent40to80 = ( TGraphAsymmErrors * ) input_cent40to80->Get("D0_fonll_raa_errordata");
	TGraphAsymmErrors * D0_fonll_raa_errorfonll_cent40to80 = ( TGraphAsymmErrors * ) input_cent40to80->Get("D0_fonll_raa_errorfonll");
	TH1D * D0_pbpb_spectrum_cent40to80 = ( TH1D * ) input_cent40to80->Get("D0_pbpb_spectrum");


	TCanvas * D0_RAFONLL_cent0to2040to80 = new TCanvas("D0_RAFONLL_cent0to2040to80","D0_RAFONLL_cent0to2040to80");

	D0_fonll_raa_errorfonll_cent0to20->Draw("A2");
	D0_fonll_raa_errordata_cent0to20->Draw("P");

    D0_fonll_raa_errorfonll_cent40to80->SetLineColor(4.0);
	D0_fonll_raa_errordata_cent40to80->SetLineColor(4.0);
	D0_fonll_raa_errordata_cent40to80->SetMarkerColor(4.0);
	D0_fonll_raa_errorfonll_cent40to80->Draw("2");
	D0_fonll_raa_errordata_cent40to80->Draw("P");
    
	TLegend * t = new TLegend(0.5, 0.7, 0.85, 0.85);
	t->SetFillColor(0);
	t->AddEntry(D0_fonll_raa_errordata_cent0to20, "Centrality 0-20%", "PL");
	t->AddEntry(D0_fonll_raa_errordata_cent40to80, "Centrality 40%-80%", "PL");
	t->Draw();

	D0_RAFONLL_cent0to2040to80->SaveAs("plots/D0_RAFONLL_cent0to2040to80.png");
	D0_RAFONLL_cent0to2040to80->SaveAs("plots/D0_RAFONLL_cent0to2040to80.pdf");
	
	TFile * input_cent0to10 = new TFile("RAA_D0_PbPb_spectrum_fonll_effunpre_cent0to10_ptbin4.root");
	TGraphAsymmErrors * D0_fonll_raa_errordata_cent0to10 = ( TGraphAsymmErrors * ) input_cent0to10->Get("D0_fonll_raa_errordata");
	TGraphAsymmErrors * D0_fonll_raa_errorfonll_cent0to10 = ( TGraphAsymmErrors * ) input_cent0to10->Get("D0_fonll_raa_errorfonll");
	TH1D * D0_pbpb_spectrum_cent0to10 = ( TH1D * ) input_cent0to10->Get("D0_pbpb_spectrum");
	
	TFile * input_cent10to30 = new TFile("RAA_D0_PbPb_spectrum_fonll_effunpre_cent10to30_ptbin8.root");
	TGraphAsymmErrors * D0_fonll_raa_errordata_cent10to30 = ( TGraphAsymmErrors * ) input_cent10to30->Get("D0_fonll_raa_errordata");
	TGraphAsymmErrors * D0_fonll_raa_errorfonll_cent10to30 = ( TGraphAsymmErrors * ) input_cent10to30->Get("D0_fonll_raa_errorfonll");
	TH1D * D0_pbpb_spectrum_cent10to30 = ( TH1D * ) input_cent10to30->Get("D0_pbpb_spectrum");
	
	TFile * input_cent30to50 = new TFile("RAA_D0_PbPb_spectrum_fonll_effunpre_cent30to50_ptbin8.root");
	TGraphAsymmErrors * D0_fonll_raa_errordata_cent30to50 = ( TGraphAsymmErrors * ) input_cent30to50->Get("D0_fonll_raa_errordata");
	TGraphAsymmErrors * D0_fonll_raa_errorfonll_cent30to50 = ( TGraphAsymmErrors * ) input_cent30to50->Get("D0_fonll_raa_errorfonll");
	TH1D * D0_pbpb_spectrum_cent30to50 = ( TH1D * ) input_cent30to50->Get("D0_pbpb_spectrum");

	TFile * input_cent50to100 = new TFile("RAA_D0_PbPb_spectrum_fonll_effunpre_cent50to100_ptbin8.root");
	TGraphAsymmErrors * D0_fonll_raa_errordata_cent50to100 = ( TGraphAsymmErrors * ) input_cent50to100->Get("D0_fonll_raa_errordata");
	TGraphAsymmErrors * D0_fonll_raa_errorfonll_cent50to100 = ( TGraphAsymmErrors * ) input_cent50to100->Get("D0_fonll_raa_errorfonll");
	TH1D * D0_pbpb_spectrum_cent50to100 = ( TH1D * ) input_cent50to100->Get("D0_pbpb_spectrum");

    TCanvas * D0_RAFONLL_cent0103050100 = new TCanvas("D0_RAFONLL_cent0103050100","D0_RAFONLL_cent0103050100");	

	D0_fonll_raa_errorfonll_cent0to10->Draw("A2");
	D0_fonll_raa_errordata_cent0to10->Draw("P");

    D0_fonll_raa_errorfonll_cent10to30->SetLineColor(4.0);
	D0_fonll_raa_errordata_cent10to30->SetLineColor(4.0);
	D0_fonll_raa_errordata_cent10to30->SetMarkerColor(4.0);
	D0_fonll_raa_errorfonll_cent10to30->Draw("2");
	D0_fonll_raa_errordata_cent10to30->Draw("P");

    D0_fonll_raa_errorfonll_cent30to50->SetLineColor(2.0);
	D0_fonll_raa_errordata_cent30to50->SetLineColor(2.0);
	D0_fonll_raa_errordata_cent30to50->SetMarkerColor(2.0);
	D0_fonll_raa_errorfonll_cent30to50->Draw("2");
	D0_fonll_raa_errordata_cent30to50->Draw("P");

    D0_fonll_raa_errorfonll_cent50to100->SetLineColor(kGreen+2);
	D0_fonll_raa_errordata_cent50to100->SetLineColor(kGreen+2);
	D0_fonll_raa_errordata_cent50to100->SetMarkerColor(kGreen+2);
	D0_fonll_raa_errorfonll_cent50to100->Draw("2");
	D0_fonll_raa_errordata_cent50to100->Draw("P");


    TLegend * t1 = new TLegend(0.5, 0.7, 0.85, 0.85);
    t1->SetFillColor(0);
    t1->AddEntry(D0_fonll_raa_errordata_cent0to10, "Centrality 0-10%", "PL");
    t1->AddEntry(D0_fonll_raa_errordata_cent10to30, "Centrality 10%-30%", "PL");
    t1->AddEntry(D0_fonll_raa_errordata_cent30to50, "Centrality 30%-50%", "PL");
    t1->AddEntry(D0_fonll_raa_errordata_cent50to100, "Centrality 50-100%", "PL");
    t1->Draw();

    D0_RAFONLL_cent0103050100->SaveAs("plots/D0_RAFONLL_cent0103050100.png");
    D0_RAFONLL_cent0103050100->SaveAs("plots/D0_RAFONLL_cent0103050100.pdf");

	TFile * input_cent0to100 = new TFile("RAA_D0_PbPb_spectrum_fonll_effunpre_cent0to100_ptbin9.root");
	TH1D * D0_pbpb_spectrum_cent0to100 = ( TH1D * ) input_cent0to100->Get("D0_pbpb_spectrum");
	TGraphAsymmErrors * d0fonllspectrum = ( TGraphAsymmErrors * ) input_cent0to100->Get("gaeSigmaDecayDzero");

	TCanvas * cfg_spectrum_centrality = new TCanvas("cfg_spectrum_centrality","cfg_spectrum_centrality");
    cfg_spectrum_centrality->SetLeftMargin(0.2);
	gPad->SetLogy();

//    D0_pbpb_spectrum_cent0to100->GetYaxis()->SetRangeUser(1E2,1E16);
    D0_pbpb_spectrum_cent0to100->GetYaxis()->SetRangeUser(1E2,1E8);
    D0_pbpb_spectrum_cent0to100->SetLineColor(4.0);
	D0_pbpb_spectrum_cent0to100->SetMarkerColor(4.0);
	D0_pbpb_spectrum_cent0to100->Draw();

    d0fonllspectrum->SetMarkerStyle(25);
	d0fonllspectrum->Draw("psame");

//    D0_pbpb_spectrum_cent0to20->Scale(1e2);
	D0_pbpb_spectrum_cent0to20->SetLineColor(2.0);
	D0_pbpb_spectrum_cent0to20->SetMarkerColor(2.0);
//	D0_pbpb_spectrum_cent0to20->Draw("same");

//    D0_pbpb_spectrum_cent40to80->Scale(1e3);
	D0_pbpb_spectrum_cent40to80->SetLineColor(6.0);
	D0_pbpb_spectrum_cent40to80->SetMarkerColor(6.0);
//	D0_pbpb_spectrum_cent40to80->Draw("same");

//    D0_pbpb_spectrum_cent10to30->Scale(1e4);
	D0_pbpb_spectrum_cent10to30->SetLineColor(8.0);
	D0_pbpb_spectrum_cent10to30->SetMarkerColor(8.0);
	D0_pbpb_spectrum_cent10to30->Draw("same");

//    D0_pbpb_spectrum_cent30to50->Scale(1e5);
	D0_pbpb_spectrum_cent30to50->SetLineColor(12.0);
	D0_pbpb_spectrum_cent30to50->SetMarkerColor(12.0);
	D0_pbpb_spectrum_cent30to50->Draw("same");

//    D0_pbpb_spectrum_cent50to100->Scale(1e6);
	D0_pbpb_spectrum_cent50to100->SetLineColor(50.0);
	D0_pbpb_spectrum_cent50to100->SetMarkerColor(50.0);
	D0_pbpb_spectrum_cent50to100->Draw("same");

    TLegend * t2 = new TLegend(0.5, 0.6, 0.85, 0.85);
    t2->SetFillColor(0);
	t2->AddEntry(d0fonllspectrum, "FONLL", "PL");
    t2->AddEntry(D0_pbpb_spectrum_cent0to100, "PbPb Data 0-100%", "PL");

//    t2->AddEntry(D0_pbpb_spectrum_cent0to20, "0-20%", "PL");
//    t2->AddEntry(D0_pbpb_spectrum_cent40to80, "40-80%", "PL");
    t2->AddEntry(D0_pbpb_spectrum_cent10to30, "10-30%", "PL");
	t2->AddEntry(D0_pbpb_spectrum_cent30to50, "30-50%", "PL");
	t2->AddEntry(D0_pbpb_spectrum_cent50to100, "50-100%", "PL");

//    t2->AddEntry(D0_pbpb_spectrum_cent0to20, "0-20% #times 10^{2}", "PL");
//    t2->AddEntry(D0_pbpb_spectrum_cent40to80, "40-80% #times 10^{3}", "PL");
//    t2->AddEntry(D0_pbpb_spectrum_cent10to30, "10-30% #times 10^{4}", "PL");
//	t2->AddEntry(D0_pbpb_spectrum_cent30to50, "30-50% #times 10^{5}", "PL");
//	t2->AddEntry(D0_pbpb_spectrum_cent50to100, "50-100% #times 10^{6}", "PL");
    t2->Draw();

}
