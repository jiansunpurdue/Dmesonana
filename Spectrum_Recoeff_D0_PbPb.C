
void Draw_Recoeff_D0_PbPb( TFile * input_MC, TFile * input_data, bool evtunprescaleMB, int cent_low, int cent_high, int Nptbin)
{
	gStyle->SetOptStat(0);
	gStyle->SetOptTitle(0);
	TH1::SetDefaultSumw2();

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
    recoeff_matched->GetXaxis()->SetTitle("D^{0} p_{T} (GeV/c)");
    recoeff_matched->GetYaxis()->SetTitle("Reco Eff");
    recoeff_matched->SetMarkerSize(0.8);
    recoeff_matched->SetMarkerStyle(20);
    recoeff_matched->Draw("ep");

    recoeff_fitting->SetLineColor(4.0);
    recoeff_fitting->SetMarkerColor(4.0);	
    recoeff_fitting->GetXaxis()->SetTitle("D^{0} p_{T} (GeV/c)");
    recoeff_fitting->GetYaxis()->SetTitle("Reco Eff");
    recoeff_fitting->SetMarkerSize(0.8);
    recoeff_fitting->SetMarkerStyle(20);
	recoeff_fitting->Draw("epsame");

	TH1D * ratio_matched_fitting = ( TH1D *) recoeff_matched->Clone("ratio_matched_fitting");
	ratio_matched_fitting->Divide(N_mb,N_mb_matched,1.0,1.0,"B");


// for data
	TH1D * d0raw_data = ( TH1D * ) input_data->Get("N_mb");
	TH1D * d0raw_data_overeff = ( TH1D * ) d0raw_data->Clone("d0raw_data_overeff");

    if( Nptbin == 8 )    
	{
		d0raw_data_overeff->SetBinContent(d0raw_data_overeff->FindBin(35), -999);
		d0raw_data_overeff->SetBinError(d0raw_data_overeff->FindBin(35), 0);
	}

    d0raw_data_overeff->Divide(recoeff_matched);   // corrected by acceptance * reco eff

	TH1D * hf_mb = (TH1D *) input_data->Get("hf_mb");
	double effectprescale = hf_mb->Integral(0,-1)/hf_mb->GetEntries();
    if( !evtunprescaleMB )	d0raw_data_overeff->Scale(effectprescale);

	TCanvas *d0spectrum_pbpb = new TCanvas("d0spectrum_pbpb","d0spectrum_pbpb");
	gPad->SetLogy();

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
	Tl.DrawLatex(0.3,0.8, "CMS Preliminary, 2011 PbPb, #sqrt{s_{NN}} = 2.76 TeV");
    Tl.DrawLatex(0.5,0.7, "#left|y#right| < 2.0");
	TString centrality;
	centrality.Form("Centrality %d%%-%d%%", cent_low,cent_high);
	Tl.DrawLatex(0.5,0.6, centrality);

// end data
//
    char outputfile[200];
	sprintf(outputfile,"Spectrum_Recoeff0to200_D0_PbPb_dpt_evtunprescaleMB%d_cent%dto%d_ptbin%d.root", evtunprescaleMB, cent_low, cent_high, Nptbin);
	TFile * output = new TFile(outputfile,"RECREATE");
	hf_mb->Write();
	recoeff->Write();
	recoeff_matched->Write();
	recoeff_fitting->Write();
	ratio_matched_fitting->Write();
	d0spectrum_pbpb->Write();
	d0raw_data->Write();
	d0raw_data_overeff->Write();
	output->Close();
}

void Spectrum_Recoeff_D0_PbPb()
{
    bool evtunprescaleMB = false;
	TFile * input_MC;
	TFile * input_data;
	int cent_low, cent_high;
	int Nptbin;

//9 ptbins
	input_MC = new TFile("Dspectrum_pbpb_MC_genmatch_histo_ptbin_11_ptd_cent-0to200.root");
    input_data = new TFile("Dspectrum_pbpb_data_ptbin_11_ptd_unpreMBtrig_1_cent-0to200.root");
	evtunprescaleMB = true;
    cent_low = 0;
	cent_high = 100;
	Nptbin = 9;
	Draw_Recoeff_D0_PbPb( input_MC, input_data, evtunprescaleMB, cent_low, cent_high, Nptbin);
	input_MC->Close();
	input_data->Close();

//unprescale MB trigger with effective prescaler
	evtunprescaleMB = false;

	input_MC = new TFile("Dspectrum_pbpb_MC_genmatch_histo_ptbin_11_ptd_cent-0to200.root");
    input_data = new TFile("Dspectrum_pbpb_data_ptbin_11_ptd_unpreMBtrig_0_cent-0to200.root");
    cent_low = 0;
	cent_high = 100;
	Nptbin = 9;
	Draw_Recoeff_D0_PbPb( input_MC, input_data, evtunprescaleMB, cent_low, cent_high, Nptbin);
	input_MC->Close();
	input_data->Close();

	input_MC = new TFile("Dspectrum_pbpb_MC_genmatch_histo_ptbin_11_ptd_cent-0to200.root");
    input_data = new TFile("Dspectrum_pbpb_data_ptbin_11_ptd_unpreMBtrig_0_cent-0to40.root");
    cent_low = 0;
	cent_high = 20;
	Nptbin = 8;
	Draw_Recoeff_D0_PbPb( input_MC, input_data, evtunprescaleMB, cent_low, cent_high, Nptbin);
	input_MC->Close();
	input_data->Close();

	input_MC = new TFile("Dspectrum_pbpb_MC_genmatch_histo_ptbin_11_ptd_cent-0to200.root");
    input_data = new TFile("Dspectrum_pbpb_data_ptbin_11_ptd_unpreMBtrig_0_cent80to160.root");
    cent_low = 40;
	cent_high = 80;
	Nptbin = 8;
	Draw_Recoeff_D0_PbPb( input_MC, input_data, evtunprescaleMB, cent_low, cent_high, Nptbin);
	input_MC->Close();
	input_data->Close();

	input_MC = new TFile("Dspectrum_pbpb_MC_genmatch_histo_ptbin_11_ptd_cent-0to200.root");
    input_data = new TFile("Dspectrum_pbpb_data_ptbin_11_ptd_unpreMBtrig_0_cent20to60.root");
    cent_low = 10;
	cent_high = 30;
	Nptbin = 8;
	Draw_Recoeff_D0_PbPb( input_MC, input_data, evtunprescaleMB, cent_low, cent_high, Nptbin);
	input_MC->Close();
	input_data->Close();


	input_MC = new TFile("Dspectrum_pbpb_MC_genmatch_histo_ptbin_11_ptd_cent-0to200.root");
    input_data = new TFile("Dspectrum_pbpb_data_ptbin_11_ptd_unpreMBtrig_0_cent60to100.root");
    cent_low = 30;
	cent_high = 50;
	Nptbin = 8;
	Draw_Recoeff_D0_PbPb( input_MC, input_data, evtunprescaleMB, cent_low, cent_high, Nptbin);
	input_MC->Close();
	input_data->Close();


	input_MC = new TFile("Dspectrum_pbpb_MC_genmatch_histo_ptbin_11_ptd_cent-0to200.root");
    input_data = new TFile("Dspectrum_pbpb_data_ptbin_11_ptd_unpreMBtrig_0_cent100to200.root");
    cent_low = 50;
	cent_high = 100;
	Nptbin = 8;
	Draw_Recoeff_D0_PbPb( input_MC, input_data, evtunprescaleMB, cent_low, cent_high, Nptbin);
	input_MC->Close();
	input_data->Close();


//Nptbin6
	input_MC = new TFile("Dspectrum_pbpb_MC_genmatch_histo_ptbin_6_ptd_cent-0to200.root");
    input_data = new TFile("Dspectrum_pbpb_data_ptbin_6_ptd_unpreMBtrig_0_cent-0to20.root");
    cent_low = 0;
	cent_high = 10;
	Nptbin = 4;
	Draw_Recoeff_D0_PbPb( input_MC, input_data, evtunprescaleMB, cent_low, cent_high, Nptbin);
	input_MC->Close();
	input_data->Close();

	input_MC = new TFile("Dspectrum_pbpb_MC_genmatch_histo_ptbin_6_ptd_cent-0to200.root");
    input_data = new TFile("Dspectrum_pbpb_data_ptbin_6_ptd_unpreMBtrig_0_cent20to60.root");
    cent_low = 10;
	cent_high = 30;
	Nptbin = 4;
	Draw_Recoeff_D0_PbPb( input_MC, input_data, evtunprescaleMB, cent_low, cent_high, Nptbin);
	input_MC->Close();
	input_data->Close();

	input_MC = new TFile("Dspectrum_pbpb_MC_genmatch_histo_ptbin_6_ptd_cent-0to200.root");
    input_data = new TFile("Dspectrum_pbpb_data_ptbin_6_ptd_unpreMBtrig_0_cent60to100.root");
    cent_low = 30;
	cent_high = 50;
	Nptbin = 4;
	Draw_Recoeff_D0_PbPb( input_MC, input_data, evtunprescaleMB, cent_low, cent_high, Nptbin);
	input_MC->Close();
	input_data->Close();

	input_MC = new TFile("Dspectrum_pbpb_MC_genmatch_histo_ptbin_6_ptd_cent-0to200.root");
    input_data = new TFile("Dspectrum_pbpb_data_ptbin_6_ptd_unpreMBtrig_0_cent100to200.root");
    cent_low = 50;
	cent_high = 100;
	Nptbin = 4;
	Draw_Recoeff_D0_PbPb( input_MC, input_data, evtunprescaleMB, cent_low, cent_high, Nptbin);
	input_MC->Close();
	input_data->Close();

}
