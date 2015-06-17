int rebinnumber =  20;

void Drawalpha_bkg_data()
{
    gStyle->SetOptTitle(0);
	gStyle->SetOptStat(0);
	TH1::SetDefaultSumw2();

	TFile * input = new TFile("./filescent-0to100/Cut_distribution_Data_sideband_pt7to40_rapidity0to1_cent-0to100.root");

	TH1D * alpha_leftband = ( TH1D * ) input->Get("alpha_leftband");
	TH1D * alpha_rightband = ( TH1D * ) input->Get("alpha_rightband");

	alpha_leftband->Rebin(rebinnumber);
	alpha_rightband->Rebin(rebinnumber);

	alpha_leftband->Scale( 1.0/alpha_leftband->Integral(0, -1) );
	alpha_rightband->Scale( 1.0/alpha_rightband->Integral(0, -1) );

	alpha_leftband->SetLineColor(2.0);
	alpha_rightband->SetLineColor(4.0);

	alpha_leftband->SetLineWidth(2.0);
	alpha_rightband->SetLineWidth(2.0);

	TCanvas * cfg_alpha = new TCanvas("cfg_alpha","cfg_alpha");

	alpha_leftband->Draw();
	alpha_rightband->Draw("same");

    TLegend *leg = new TLegend(0.4,0.65,0.65,0.8);
    leg->SetTextFont(62);
    leg->AddEntry(alpha_leftband,"Left Sideband");
    leg->AddEntry(alpha_rightband,"Right Sideband");
    leg->SetBorderSize(0);
    leg->SetFillStyle(0);
    leg->Draw();

	cfg_alpha->SaveAs("Alpha_bkg_sideband_data_cent-0to100.png");
	cfg_alpha->SaveAs("Alpha_bkg_sideband_data_cent-0to100.pdf");


}
