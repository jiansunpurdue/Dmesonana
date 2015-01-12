bool isPbPb = false;

void Spectrum_Recoeff_D0_ppPbPb()
{
	gStyle->SetOptStat(0);
	gStyle->SetOptTitle(0);
	TH1::SetDefaultSumw2();
    if ( isPbPb )
	{
	   TFile * input_MC = new TFile("Dspectrum_pbpb_MC_genmatch_histo_ptbin_11_d4p0_nospike.root");
	   TFile * input_data = new TFile("Dspectrum_pbpb_histo_ptbin_11_d4p0.root");
	}
	else
	{
		TFile * input_MC = new TFile("Dspectrum_pp_MC_genmatch_histo_ptbin_11_recoeff_cuts2p0_nospike.root");
		TFile * input_data = new TFile("Dspectrum_pp_histo_ptbin_11_d2p0.root");
	}

	TH1D * N_gendpt = ( TH1D * ) input_MC->Get("N_gendpt");
	TH1D * N_mb_matched = ( TH1D * ) input_MC->Get("N_mb_matched");
	TH1D * N_mb = ( TH1D * ) input_MC->Get("N_mb");

	TH1D * recoeff_matched = ( TH1D * ) N_mb_matched->Clone("recoeff_matched");
	recoeff_matched->Divide(N_mb_matched, N_gendpt, 1.0, 1.0, "B");

	TH1D * recoeff_fitting = ( TH1D * ) N_mb->Clone("recoeff_fitting");
	recoeff_fitting->Divide(N_mb, N_gendpt, 1.0, 1.0, "B");

	TCanvas * recoeff = new TCanvas("recoeff","recoeff");

	recoeff_matched->GetXaxis()->SetRangeUser(5.0,35);

    recoeff_matched->SetLineColor(1.0);
    recoeff_matched->SetMarkerColor(1.0);	
    recoeff_matched->GetXaxis()->SetTitle("D Meson Pt");
    recoeff_matched->GetYaxis()->SetTitle("Reco Eff");
    recoeff_matched->SetMarkerSize(0.8);
    recoeff_matched->SetMarkerStyle(20);
    recoeff_matched->Draw("ep");

    recoeff_fitting->SetLineColor(4.0);
    recoeff_fitting->SetMarkerColor(4.0);	
    recoeff_fitting->GetXaxis()->SetTitle("D Meson Pt");
    recoeff_fitting->GetYaxis()->SetTitle("Reco Eff");
    recoeff_fitting->SetMarkerSize(0.8);
    recoeff_fitting->SetMarkerStyle(20);
	recoeff_fitting->Draw("epsame");

	TH1D * ratio_matched_fitting = ( TH1D *) recoeff_matched->Clone("ratio_matched_fitting");
	ratio_matched_fitting->Divide(N_mb,N_mb_matched,1.0,1.0,"B");


// for data
    if( isPbPb )
		TH1D * d0raw_data = ( TH1D * ) input_data->Get("N_mb");
	else
		TH1D * d0raw_data = ( TH1D * ) input_data->Get("N_Jettrig");
	TH1D * d0raw_data_overeff = ( TH1D * ) d0raw_data->Clone("d0raw_data_overeff");
	d0raw_data_overeff->Divide(recoeff_matched);   // corrected by acceptance * reco eff

	if( !isPbPb )
	{   // corrected by trigger eff
		TFile * input_trigeff = new TFile("Jettrig_eff_pp_ptbin_11_nocuts.root");
		TH1D * Jettrig_eff_pp = ( TH1D * ) input_trigeff->Get("Jettrig_eff_pp");
		TH1D * d0raw_data_overrecoeff = ( TH1D *) d0raw_data_overeff->Clone("d0raw_data_overrecoeff");
		d0raw_data_overeff->Divide(Jettrig_eff_pp);
	}

	TCanvas *d0spectrum_pbpb = new TCanvas("d0spectrum_pbpb","d0spectrum_pbpb");

    d0raw_data_overeff->GetXaxis()->SetTitle("D Meson Pt");
    d0raw_data_overeff->GetXaxis()->SetRangeUser(5.,35);
    d0raw_data_overeff->GetYaxis()->SetTitle("dN/dp_{T}");

    d0raw_data_overeff->SetLineColor(4.0);
    d0raw_data_overeff->SetMarkerSize(0.8);
    d0raw_data_overeff->SetMarkerStyle(20);
    d0raw_data_overeff->SetMarkerColor(4.0);
    d0raw_data_overeff->Draw("ep");

    TLatex Tl;
    Tl.SetNDC();
    Tl.SetTextAlign(12);
    Tl.SetTextSize(0.03);
	if( isPbPb )
		Tl.DrawLatex(0.3,0.8, "CMS Preliminary, 2011 PbPb, #sqrt{S_{NN}} = 2.76 TeV");
	else
		Tl.DrawLatex(0.3,0.8, "CMS Preliminary, 2013 pp, #sqrt{S_{NN}} = 2.76 TeV");
    Tl.DrawLatex(0.5,0.7, "#left|#eta#right| < 2.0");

// end data
//
    if( isPbPb )
		TFile * output = new TFile("Spectrum_Recoeff_D0_PbPb_d4p0.root","RECREATE");
	else
		TFile * output = new TFile("Spectrum_Recoeff_D0_pp_d2p0.root","RECREATE");
	recoeff->Write();
	recoeff_matched->Write();
	recoeff_fitting->Write();
	ratio_matched_fitting->Write();
	d0spectrum_pbpb->Write();
	d0raw_data->Write();
	d0raw_data_overeff->Write();
	if( !isPbPb ) 
	{
		Jettrig_eff_pp->Write();
		d0raw_data_overrecoeff->Write();
	}
}
