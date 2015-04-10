#define BR 0.0388
#define NEVT 30172291.0


void Draw_Recoeff_D0_PbPb( TFile * input_MC, TFile * input_data, TFile * input_promptfraction, bool evtunprescaleMB, int cent_low, int cent_high, int Nptbin)
{
	gStyle->SetOptStat(0);
	gStyle->SetOptTitle(0);
	TH1::SetDefaultSumw2();
	
	TH1D * recoeff_matched = ( TH1D * ) input_MC->Get("d0accxeff_pt");

// for data
	TH1D * d0raw_data = ( TH1D * ) input_data->Get("N_mb");
	TH1D * d0raw_data_overeff = ( TH1D * ) d0raw_data->Clone("d0raw_data_overeff");

    TGraphAsymmErrors * promptD0faction = ( TGraphAsymmErrors *) input_promptfraction->Get("gaePromptfraction");

    for( int i = 0; i < promptD0faction->GetN(); i++ )
	{
		cout << " histo bin center: " << d0raw_data_overeff->GetBinCenter(i+2) << "   Tgraph bincenter: " << promptD0faction->GetX()[i] << endl; 
		d0raw_data_overeff->SetBinContent( i+2, d0raw_data_overeff->GetBinContent(i+2) * promptD0faction->GetY()[i] );
		d0raw_data_overeff->SetBinError( i+2, d0raw_data_overeff->GetBinError(i+2) * promptD0faction->GetY()[i] );
	}



    if( Nptbin == 8 )    
	{
		d0raw_data_overeff->SetBinContent(d0raw_data_overeff->FindBin(35), -999);
		d0raw_data_overeff->SetBinError(d0raw_data_overeff->FindBin(35), 0);
	}

    d0raw_data_overeff->Divide(recoeff_matched);   // corrected by acceptance * reco eff

    d0raw_data_overeff->Scale(1.0/NEVT);
	d0raw_data_overeff->Scale(1.0/BR);
	d0raw_data_overeff->Scale(0.5);

	TCanvas *d0spectrum_pbpb = new TCanvas("d0spectrum_pbpb","d0spectrum_pbpb");
	d0spectrum_pbpb->SetLeftMargin(0.2);
	gPad->SetLogy();

    d0raw_data_overeff->GetXaxis()->SetTitle("D^{0} Pt (GeV/c)");
    d0raw_data_overeff->GetXaxis()->SetRangeUser(4.0,35);
    d0raw_data_overeff->GetYaxis()->SetTitle("#frac{1}{N_{evt}} #frac{dN}{dp_{T}}");
	d0raw_data_overeff->GetYaxis()->SetTitleOffset(2.0);

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
	sprintf(outputfile,"Prompt_Spectrum_centRecoeff_D0_PbPb_dpt_evtunprescaleMB%d_cent%dto%d_ptbin%d.root", evtunprescaleMB, cent_low, cent_high, Nptbin);
	TFile * output = new TFile(outputfile,"RECREATE");
	recoeff_matched->Write();
	d0spectrum_pbpb->Write();
	d0raw_data->Write();
	d0raw_data_overeff->Write();
	output->Close();
}

void Spectrum_Recoeff_D0_PbPb_prompt()
{
    bool evtunprescaleMB = false;
	TFile * input_MC;
	TFile * input_data;
    TFile * input_promptfraction;

	int cent_low, cent_high;
	int Nptbin;

//9 ptbins
	input_MC = new TFile("./../D0_PbPb_acc_eff_ptbin_12_ybin_6_prompt_FONLLweight_cent-0to100.root");
    input_data = new TFile("./../rootfiles/Dspectrum_pbpb_data_ptbin_12_ptd_unpreMBtrig_0_cent-0to100.root");
    input_promptfraction = new TFile("Bfraction_method1.root");
    evtunprescaleMB = false;
    cent_low = 0;
	cent_high = 100;
	Nptbin = 10;
	Draw_Recoeff_D0_PbPb( input_MC, input_data, input_promptfraction, evtunprescaleMB, cent_low, cent_high, Nptbin);
//	input_MC->Close();
//	input_data->Close();

////unprescale MB trigger with effective prescaler
//    evtunprescaleMB = false;
//
//    input_MC = new TFile("rootfiles/Dspectrum_pbpb_MC_genmatch_histo_ptbin_11_ptd_cent-0to100_FONLLweight.root");
//    input_data = new TFile("rootfiles/Dspectrum_pbpb_data_ptbin_11_ptd_unpreMBtrig_0_cent-0to100.root");
//    cent_low = 0;
//    cent_high = 100;
//    Nptbin = 9;
//    Draw_Recoeff_D0_PbPb( input_MC, input_data, evtunprescaleMB, cent_low, cent_high, Nptbin);
//    input_MC->Close();
//    input_data->Close();
//
//	input_MC = new TFile("rootfiles/Dspectrum_pbpb_MC_genmatch_histo_ptbin_11_ptd_cent-0to20_FONLLweight.root");
//    input_data = new TFile("rootfiles/Dspectrum_pbpb_data_ptbin_11_ptd_unpreMBtrig_0_cent-0to20.root");
//    cent_low = 0;
//	cent_high = 20;
//	Nptbin = 8;
//	Draw_Recoeff_D0_PbPb( input_MC, input_data, evtunprescaleMB, cent_low, cent_high, Nptbin);
//	input_MC->Close();
//	input_data->Close();
//
//	input_MC = new TFile("rootfiles/Dspectrum_pbpb_MC_genmatch_histo_ptbin_11_ptd_cent40to80_FONLLweight.root");
//    input_data = new TFile("rootfiles/Dspectrum_pbpb_data_ptbin_11_ptd_unpreMBtrig_0_cent40to80.root");
//    cent_low = 40;
//	cent_high = 80;
//	Nptbin = 8;
//	Draw_Recoeff_D0_PbPb( input_MC, input_data, evtunprescaleMB, cent_low, cent_high, Nptbin);
//	input_MC->Close();
//	input_data->Close();
//
//	input_MC = new TFile("rootfiles/Dspectrum_pbpb_MC_genmatch_histo_ptbin_11_ptd_cent10to30_FONLLweight.root");
//    input_data = new TFile("rootfiles/Dspectrum_pbpb_data_ptbin_11_ptd_unpreMBtrig_0_cent10to30.root");
//    cent_low = 10;
//	cent_high = 30;
//	Nptbin = 8;
//	Draw_Recoeff_D0_PbPb( input_MC, input_data, evtunprescaleMB, cent_low, cent_high, Nptbin);
//	input_MC->Close();
//	input_data->Close();
//
//
//	input_MC = new TFile("rootfiles/Dspectrum_pbpb_MC_genmatch_histo_ptbin_11_ptd_cent30to50_FONLLweight.root");
//    input_data = new TFile("rootfiles/Dspectrum_pbpb_data_ptbin_11_ptd_unpreMBtrig_0_cent30to50.root");
//    cent_low = 30;
//	cent_high = 50;
//	Nptbin = 8;
//	Draw_Recoeff_D0_PbPb( input_MC, input_data, evtunprescaleMB, cent_low, cent_high, Nptbin);
//	input_MC->Close();
//	input_data->Close();
//
//
//	input_MC = new TFile("rootfiles/Dspectrum_pbpb_MC_genmatch_histo_ptbin_11_ptd_cent50to100_FONLLweight.root");
//    input_data = new TFile("rootfiles/Dspectrum_pbpb_data_ptbin_11_ptd_unpreMBtrig_0_cent50to100.root");
//    cent_low = 50;
//	cent_high = 100;
//	Nptbin = 8;
//	Draw_Recoeff_D0_PbPb( input_MC, input_data, evtunprescaleMB, cent_low, cent_high, Nptbin);
//	input_MC->Close();
//	input_data->Close();
//
//
////Nptbin6
//	input_MC = new TFile("rootfiles/Dspectrum_pbpb_MC_genmatch_histo_ptbin_6_ptd_cent-0to10_FONLLweight.root");
//    input_data = new TFile("rootfiles/Dspectrum_pbpb_data_ptbin_6_ptd_unpreMBtrig_0_cent-0to10.root");
//    cent_low = 0;
//	cent_high = 10;
//	Nptbin = 4;
//	Draw_Recoeff_D0_PbPb( input_MC, input_data, evtunprescaleMB, cent_low, cent_high, Nptbin);
//	input_MC->Close();
//	input_data->Close();
//
//	input_MC = new TFile("rootfiles/Dspectrum_pbpb_MC_genmatch_histo_ptbin_6_ptd_cent10to30_FONLLweight.root");
//    input_data = new TFile("rootfiles/Dspectrum_pbpb_data_ptbin_6_ptd_unpreMBtrig_0_cent10to30.root");
//    cent_low = 10;
//	cent_high = 30;
//	Nptbin = 4;
//	Draw_Recoeff_D0_PbPb( input_MC, input_data, evtunprescaleMB, cent_low, cent_high, Nptbin);
//	input_MC->Close();
//	input_data->Close();
//
//	input_MC = new TFile("rootfiles/Dspectrum_pbpb_MC_genmatch_histo_ptbin_6_ptd_cent30to50_FONLLweight.root");
//    input_data = new TFile("rootfiles/Dspectrum_pbpb_data_ptbin_6_ptd_unpreMBtrig_0_cent30to50.root");
//    cent_low = 30;
//	cent_high = 50;
//	Nptbin = 4;
//	Draw_Recoeff_D0_PbPb( input_MC, input_data, evtunprescaleMB, cent_low, cent_high, Nptbin);
//	input_MC->Close();
//	input_data->Close();
//
//	input_MC = new TFile("rootfiles/Dspectrum_pbpb_MC_genmatch_histo_ptbin_6_ptd_cent50to100_FONLLweight.root");
//    input_data = new TFile("rootfiles/Dspectrum_pbpb_data_ptbin_6_ptd_unpreMBtrig_0_cent50to100.root");
//    cent_low = 50;
//	cent_high = 100;
//	Nptbin = 4;
//	Draw_Recoeff_D0_PbPb( input_MC, input_data, evtunprescaleMB, cent_low, cent_high, Nptbin);
//	input_MC->Close();
//	input_data->Close();
//
}
