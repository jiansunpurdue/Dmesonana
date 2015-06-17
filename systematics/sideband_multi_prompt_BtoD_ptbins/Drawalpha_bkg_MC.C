int rebinnumber =  5;

void Drawalpha_bkg_MC()
{
    gStyle->SetOptTitle(0);
    gStyle->SetOptStat(0);
    TH1::SetDefaultSumw2();

	TFile * input = new TFile("./filescent30to100/Cut_distribution_MC_FONLLweight_Prompt_pt7to40_rapidity0to1_cent30to100_sideband_dataptweight.root");

	TH1D * alpha_signalregionbkg = ( TH1D * ) input->Get("alpha_signalregionbkg");
	TH1D * alpha_leftband = ( TH1D * ) input->Get("alpha_leftband");
	TH1D * alpha_rightband = ( TH1D * ) input->Get("alpha_rightband");

	alpha_signalregionbkg->Rebin(rebinnumber);
	alpha_leftband->Rebin(rebinnumber);
	alpha_rightband->Rebin(rebinnumber);

	alpha_signalregionbkg->Scale( 1.0/alpha_signalregionbkg->Integral(0, -1) );
	alpha_leftband->Scale( 1.0/alpha_leftband->Integral(0, -1) );
	alpha_rightband->Scale( 1.0/alpha_rightband->Integral(0, -1) );

	alpha_signalregionbkg->SetLineColor(1.0);
	alpha_leftband->SetLineColor(2.0);
	alpha_rightband->SetLineColor(4.0);

	alpha_signalregionbkg->SetLineWidth(2.0);
	alpha_leftband->SetLineWidth(2.0);
	alpha_rightband->SetLineWidth(2.0);

	TCanvas * cfg_alpha = new TCanvas("cfg_alpha","cfg_alpha");

    alpha_signalregionbkg->GetXaxis()->SetRangeUser(0,0.2);
	alpha_signalregionbkg->Draw();
	alpha_leftband->Draw("same");
	alpha_rightband->Draw("same");

    TLegend *leg = new TLegend(0.4,0.65,0.65,0.8);
    leg->SetTextFont(62);
	leg->AddEntry(alpha_signalregionbkg,"Signal Region Bkg");
    leg->AddEntry(alpha_leftband,"Left Sideband");
    leg->AddEntry(alpha_rightband,"Right Sideband");
    leg->SetBorderSize(0);
    leg->SetFillStyle(0);
    leg->Draw();

    cfg_alpha->SaveAs("Alpha_bkg_sideband_MC_cent30to100.png");
    cfg_alpha->SaveAs("Alpha_bkg_sideband_MC_cent30to100.pdf");
}
