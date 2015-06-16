#define BR 0.0388

void Draw_Recoeff_D0_PbPb( TFile * input_MC, TFile * input_data, TFile * input_promptfraction, double NEVT, int cent_low, int cent_high, int Nptbin)
{
	gStyle->SetOptStat(0);
	gStyle->SetOptTitle(0);
	TH1::SetDefaultSumw2();
	
	TH1D * recoeff_matched = ( TH1D * ) input_MC->Get("d0accxeff_pt");

// for data
	TH1D * d0raw_data = ( TH1D * ) input_data->Get("N_mb_expobkg");
	TH1D * d0raw_data_overeff = ( TH1D * ) d0raw_data->Clone("d0raw_data_overeff");

    TGraphAsymmErrors * promptD0faction = ( TGraphAsymmErrors *) input_promptfraction->Get("gaePromptfraction");

    for( int i = 0; i < promptD0faction->GetN(); i++ )
	{
		cout << " histo bin center: " << d0raw_data_overeff->GetBinCenter(i+2) << "   Tgraph bincenter: " << promptD0faction->GetX()[i] << endl; 
		d0raw_data_overeff->SetBinContent( i+2, d0raw_data_overeff->GetBinContent(i+2) * promptD0faction->GetY()[i] );
		d0raw_data_overeff->SetBinError( i+2, d0raw_data_overeff->GetBinError(i+2) * promptD0faction->GetY()[i] );
		cout << " histo bin center: " << d0raw_data_overeff->GetBinCenter(i+2) << "   Tgraph bincenter: " << promptD0faction->GetX()[i] << endl; 
//		d0raw_data_overeff->SetBinContent( i+2, d0raw_data_overeff->GetBinContent(i+2) * 1.0 );
//		d0raw_data_overeff->SetBinError( i+2, d0raw_data_overeff->GetBinError(i+2) * 1.0 );
	}


    d0raw_data_overeff->Divide(recoeff_matched);   // corrected by acceptance * reco eff

    d0raw_data_overeff->Scale(1.0/NEVT);
	d0raw_data_overeff->Scale(1.0/BR);
	d0raw_data_overeff->Scale(0.5);

	TCanvas *d0spectrum_pbpb = new TCanvas("d0spectrum_pbpb","d0spectrum_pbpb");
	d0spectrum_pbpb->SetLeftMargin(0.2);
	gPad->SetLogy();

    d0raw_data_overeff->GetXaxis()->SetTitle("D^{0} Pt (GeV/c)");
    d0raw_data_overeff->GetXaxis()->SetRangeUser(2.0,35);
    d0raw_data_overeff->GetYaxis()->SetTitle("#frac{1}{2N_{evt}} #frac{dN}{dp_{T}}");
	d0raw_data_overeff->GetYaxis()->SetTitleOffset(2.0);

	d0raw_data_overeff->SetBinContent(d0raw_data_overeff->FindBin(2.0), -999);
	d0raw_data_overeff->SetBinError(d0raw_data_overeff->FindBin(2.0), 0);
	d0raw_data_overeff->SetBinContent(d0raw_data_overeff->FindBin(3.0), -999);
	d0raw_data_overeff->SetBinError(d0raw_data_overeff->FindBin(3.0), 0);

    if( Nptbin == 11 || Nptbin == 7 )    
	{
		d0raw_data_overeff->SetBinContent(d0raw_data_overeff->FindBin(35), -999);
		d0raw_data_overeff->SetBinError(d0raw_data_overeff->FindBin(35), 0);
		d0raw_data_overeff->GetXaxis()->SetRangeUser(2.0,25);
		cout << " set axis range" << endl;

	}

    d0raw_data_overeff->SetLineColor(4.0);
    d0raw_data_overeff->SetMarkerSize(1.0);
    d0raw_data_overeff->SetMarkerStyle(20);
    d0raw_data_overeff->SetMarkerColor(4.0);
    d0raw_data_overeff->DrawCopy("ep");

    TLatex Tl;
    Tl.SetNDC();
    Tl.SetTextAlign(12);
    Tl.SetTextSize(0.03);
	Tl.DrawLatex(0.3,0.8, "CMS Preliminary, 2011 PbPb, #sqrt{s_{NN}} = 2.76 TeV");
    Tl.DrawLatex(0.5,0.7, "#left|y#right| < 1.0");
	TString centrality;
	centrality.Form("Centrality %d-%d%%", cent_low,cent_high);
	Tl.DrawLatex(0.5,0.6, centrality);

// end data
//
    char outputfile[200];
	sprintf(outputfile,"rootfiles/Prompt_Spectrum_centRecoeff_D0_PbPb_dpt_cent%dto%d_ptbin%d_y1.root", cent_low, cent_high, Nptbin);
	TFile * output = new TFile(outputfile,"RECREATE");
	recoeff_matched->Write();
	d0spectrum_pbpb->Write();
	d0raw_data->Write();
	d0raw_data_overeff->Write();
	output->Close();
}

void Spectrum_Recoeff_D0_PbPb_prompt_y1()
{
	TFile * input_MC;
	TFile * input_data;
    TFile * input_promptfraction;
    double NEVT = 0.0;
	int cent_low, cent_high;
	int Nptbin;

//12 ptbins
	input_MC = new TFile("./../rootfiles/D0_PbPb_acc_eff_ptbin_14_ybin_6_prompt_FONLLweight_cent-0to100_dataptshape_y1.root");
    input_data = new TFile("./../Datamassspectrumfit/rootfiles/Dspectrum_pbpb_data_ptbin_14_ptd_unpreMBtrig_0_cent0to100_y1.root");
    input_promptfraction = new TFile("rootfiles/Bfraction_method1_ptbin_14_cent0to100_y1.root");
    cent_low = 0;
	cent_high = 100;
	Nptbin = 12;
	NEVT = 3.01781340000000000e+07;
	Draw_Recoeff_D0_PbPb( input_MC, input_data, input_promptfraction, NEVT, cent_low, cent_high, Nptbin);
	input_MC->Close();
	input_promptfraction->Close();
	input_data->Close();

//11 ptbins
    input_MC = new TFile("./../rootfiles/D0_PbPb_acc_eff_ptbin_14_ybin_6_prompt_FONLLweight_cent-0to10_dataptshape_y1.root");
    input_data = new TFile("./../Datamassspectrumfit/rootfiles/Dspectrum_pbpb_data_ptbin_14_ptd_unpreMBtrig_0_cent0to10_y1.root");
	input_promptfraction = new TFile("rootfiles/Bfraction_method1_ptbin_14_cent0to10_y1.root");
    cent_low = 0;
    cent_high = 10;
    Nptbin = 11;
	NEVT = 3.07931000000000000e+06;
    Draw_Recoeff_D0_PbPb( input_MC, input_data, input_promptfraction, NEVT, cent_low, cent_high, Nptbin);
    input_MC->Close();
	input_promptfraction->Close();
    input_data->Close();

    input_MC = new TFile("./../rootfiles/D0_PbPb_acc_eff_ptbin_14_ybin_6_prompt_FONLLweight_cent-0to20_dataptshape_y1.root");
    input_data = new TFile("./../Datamassspectrumfit/rootfiles/Dspectrum_pbpb_data_ptbin_14_ptd_unpreMBtrig_0_cent0to20_y1.root");
	input_promptfraction = new TFile("rootfiles/Bfraction_method1_ptbin_14_cent0to20_y1.root");
    cent_low = 0;
	cent_high = 20;
	Nptbin = 11;
	NEVT = 6.09397600000000000e+06;
	Draw_Recoeff_D0_PbPb( input_MC, input_data, input_promptfraction, NEVT, cent_low, cent_high, Nptbin);
	input_MC->Close();
	input_promptfraction->Close();
	input_data->Close();

//// 7 ptbins
    input_MC = new TFile("./../rootfiles/D0_PbPb_acc_eff_ptbin_9_ybin_6_prompt_FONLLweight_cent-0to10_dataptshape_y1.root");
    input_data = new TFile("./../Datamassspectrumfit/rootfiles/Dspectrum_pbpb_data_ptbin_9_ptd_unpreMBtrig_0_cent0to10_y1.root");
    input_promptfraction = new TFile("rootfiles/Bfraction_method1_ptbin_9_cent0to10_y1.root");
    cent_low = 0;
    cent_high = 10;
    Nptbin = 7;
    NEVT = 3.07931000000000000e+06;
    Draw_Recoeff_D0_PbPb( input_MC, input_data, input_promptfraction, NEVT, cent_low, cent_high, Nptbin);
    input_MC->Close();
    input_promptfraction->Close();
    input_data->Close();

	input_MC = new TFile("./../rootfiles/D0_PbPb_acc_eff_ptbin_9_ybin_6_prompt_FONLLweight_cent10to30_dataptshape_y1.root");
    input_data = new TFile("./../Datamassspectrumfit/rootfiles/Dspectrum_pbpb_data_ptbin_9_ptd_unpreMBtrig_0_cent10to30_y1.root");
    input_promptfraction = new TFile("rootfiles/Bfraction_method1_ptbin_9_cent10to30_y1.root");
    cent_low = 10;
	cent_high = 30;
	Nptbin = 7;
	NEVT = 6.09303800000000000e+06;
	Draw_Recoeff_D0_PbPb( input_MC, input_data, input_promptfraction, NEVT, cent_low, cent_high, Nptbin);
	input_MC->Close();
	input_promptfraction->Close();
	input_data->Close();

	input_MC = new TFile("./../rootfiles/D0_PbPb_acc_eff_ptbin_9_ybin_6_prompt_FONLLweight_cent30to50_dataptshape_y1.root");
    input_data = new TFile("./../Datamassspectrumfit/rootfiles/Dspectrum_pbpb_data_ptbin_9_ptd_unpreMBtrig_0_cent30to50_y1.root");
    input_promptfraction = new TFile("rootfiles/Bfraction_method1_ptbin_9_cent30to50_y1.root");
    cent_low = 30;
	cent_high = 50;
	Nptbin = 7;
	NEVT = 6.13955200000000000e+06;
	Draw_Recoeff_D0_PbPb( input_MC, input_data, input_promptfraction, NEVT, cent_low, cent_high, Nptbin);
	input_MC->Close();
	input_promptfraction->Close();
	input_data->Close();

	input_MC = new TFile("./../rootfiles/D0_PbPb_acc_eff_ptbin_9_ybin_6_prompt_FONLLweight_cent50to100_dataptshape_y1.root");
    input_data = new TFile("./../Datamassspectrumfit/rootfiles/Dspectrum_pbpb_data_ptbin_9_ptd_unpreMBtrig_0_cent50to100_y1.root");
    input_promptfraction = new TFile("rootfiles/Bfraction_method1_ptbin_9_cent50to100_y1.root");
    cent_low = 50;
	cent_high = 100;
	Nptbin = 7;
	NEVT = 1.48603910000000000e+07;
	Draw_Recoeff_D0_PbPb( input_MC, input_data, input_promptfraction, NEVT, cent_low, cent_high, Nptbin);
	input_MC->Close();
	input_promptfraction->Close();
	input_data->Close();

}
