void Dmeson_RAA()
{
	TFile * input_pbpb = new TFile("Spectrum_Recoeff_D0_PbPb_d4p0.root");
	TFile * input_pp = new TFile("Spectrum_Recoeff_D0_pp_d2p0.root");

	TH1D * D0Spectrum_pbpb = ( TH1D *) input_pbpb->Get("d0raw_data_overeff");
	TH1D * D0Spectrum_pp = ( TH1D *) input_pp->Get("d0raw_data_overeff");

	TH1D * Raa_Dmeson = ( TH1D * ) D0Spectrum_pbpb->Clone("Raa_Dmeson");

	TCanvas * raadmeson = new TCanvas("raadmeson","raadmeson");

	Raa_Dmeson->Divide(D0Spectrum_pbpb,D0Spectrum_pp,1.0,1.0);
	Raa_Dmeson->Scale(1.0/1.127E9);   //number of MB events in PbPb
	Raa_Dmeson->Scale(5.3 * 1.0E9 /5.67); //Lpp over TAA
	Raa_Dmeson->GetYaxis()->SetTitle("R_{AA}");
	Raa_Dmeson->GetYaxis()->SetRangeUser(0.0,1.0);

	Raa_Dmeson->Draw();
}
