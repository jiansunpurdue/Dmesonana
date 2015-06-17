void Draw_cut_sideband_signalregion()
{
    gStyle->SetOptTitle(0);
    gStyle->SetOptStat(0);
    gStyle->SetOptFit(0);
    TH1::SetDefaultSumw2();

	TFile * input = new TFile("Signal_cut_distribution_pt7to40.root");
	TH1D * ffls3d_signal_data = ( TH1D * ) input->Get("ffls3d_signal_data");
	TH1D * ffls3d_band = ( TH1D * ) input->Get("ffls3d_band");
	TH1D * ffls3d_signal_data = ( TH1D * ) input->Get("ffls3d_signal_data");

	ffls3d_signalregion->Rebin(20);
	ffls3d_band->Rebin(20);
	ffls3d_signal_data->Rebin(20);

	TCanvas * cfg_band = new TCanvas("cfg_band","cfg_band");
	gPad->SetLogy();

	ffls3d_signalregion->SetMarkerStyle(20);
	ffls3d_signalregion->SetMarkerSize(1.0);
	ffls3d_signalregion->SetMarkerColor(1.0);
	ffls3d_signalregion->SetLineColor(1.0);

	ffls3d_signalregion->GetXaxis()->SetRangeUser(0, 40);
	ffls3d_signalregion->GetXaxis()->SetTitle("d_{0}/#sigma(d_{0})");
    ffls3d_signalregion->GetYaxis()->SetTitle("Entries");
	ffls3d_signalregion->Draw();

    ffls3d_band->SetMarkerStyle(21);
	ffls3d_band->SetMarkerSize(1.0);
	ffls3d_band->SetMarkerColor(2.0);
	ffls3d_band->SetLineColor(2.0);
	ffls3d_band->Draw("same");

    TLegend *leg = new TLegend(0.55,0.7,0.85,0.85);
    leg->AddEntry(ffls3d_signalregion,"Data Signal Region","PL");
    leg->AddEntry(ffls3d_band,"Data Sideband * N2/N1","PL");
    leg->SetBorderSize(0);
    leg->SetFillStyle(0);
    leg->Draw();
	
	TCanvas * cfg_signal = new TCanvas("cfg_signal","cfg_signal");
	gPad->SetLogy();

	ffls3d_signal_data->SetMarkerStyle(20);
	ffls3d_signal_data->SetMarkerSize(1.0);
	ffls3d_signal_data->SetMarkerColor(4.0);
	ffls3d_signal_data->SetLineColor(4.0);

	ffls3d_signal_data->GetXaxis()->SetRangeUser(0, 40);
	ffls3d_signal_data->GetXaxis()->SetTitle("d_{0}/#sigma(d_{0})");
    ffls3d_signal_data->GetYaxis()->SetTitle("Entries");
	ffls3d_signal_data->Draw();

    TLegend *leg2 = new TLegend(0.55,0.7,0.85,0.85);
    leg2->AddEntry(ffls3d_signal_data,"Data D^{0} Signal","PL");
    leg2->SetBorderSize(0);
    leg2->SetFillStyle(0);
    leg2->Draw();


}
