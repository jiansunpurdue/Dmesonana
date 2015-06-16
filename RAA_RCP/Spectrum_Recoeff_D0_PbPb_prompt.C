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
    d0raw_data_overeff->GetYaxis()->SetTitle("#frac{1}{2N_{evt}} #frac{dN}{dp_{T}}");
	d0raw_data_overeff->GetYaxis()->SetTitleOffset(2.0);


    if( Nptbin == 9 || Nptbin == 5 )    
	{
		d0raw_data_overeff->SetBinContent(d0raw_data_overeff->FindBin(35), -999);
		d0raw_data_overeff->SetBinError(d0raw_data_overeff->FindBin(35), 0);
		d0raw_data_overeff->GetXaxis()->SetRangeUser(4.0,25);
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
    Tl.DrawLatex(0.5,0.7, "#left|y#right| < 2.0");
	TString centrality;
	centrality.Form("Centrality %d%%-%d%%", cent_low,cent_high);
	Tl.DrawLatex(0.5,0.6, centrality);

// end data
//
    char outputfile[200];
	sprintf(outputfile,"Prompt_Spectrum_centRecoeff_D0_PbPb_dpt_cent%dto%d_ptbin%d.root", cent_low, cent_high, Nptbin);
	TFile * output = new TFile(outputfile,"RECREATE");
	recoeff_matched->Write();
	d0spectrum_pbpb->Write();
	d0raw_data->Write();
	d0raw_data_overeff->Write();
	output->Close();
}

void Spectrum_Recoeff_D0_PbPb_prompt()
{
	TFile * input_MC;
	TFile * input_data;
    TFile * input_promptfraction;
    double NEVT = 0.0;
	int cent_low, cent_high;
	int Nptbin;

//10 ptbins
	input_MC = new TFile("./../rootfiles/D0_PbPb_acc_eff_ptbin_12_ybin_6_prompt_FONLLweight_cent-0to100_dataptshape.root");
    input_data = new TFile("./../Datamassspectrumfit/rootfiles/Dspectrum_pbpb_data_ptbin_12_ptd_unpreMBtrig_0_cent0to100.root");
    input_promptfraction = new TFile("Bfraction_method1_ptbin_12_cent0to100.root");
    cent_low = 0;
	cent_high = 100;
	Nptbin = 10;
	NEVT = 30172291.0;
	Draw_Recoeff_D0_PbPb( input_MC, input_data, input_promptfraction, NEVT, cent_low, cent_high, Nptbin);
	input_MC->Close();
	input_promptfraction->Close();
	input_data->Close();

//9 ptbins
    input_MC = new TFile("./../rootfiles/D0_PbPb_acc_eff_ptbin_12_ybin_6_prompt_FONLLweight_cent-0to10_dataptshape.root");
    input_data = new TFile("./../Datamassspectrumfit/rootfiles/Dspectrum_pbpb_data_ptbin_12_ptd_unpreMBtrig_0_cent0to10.root");
	input_promptfraction = new TFile("Bfraction_method1_ptbin_12_cent0to10.root");
    cent_low = 0;
    cent_high = 10;
    Nptbin = 9;
	NEVT = 3.07931000000000000e+06;
    Draw_Recoeff_D0_PbPb( input_MC, input_data, input_promptfraction, NEVT, cent_low, cent_high, Nptbin);
    input_MC->Close();
	input_promptfraction->Close();
    input_data->Close();

    input_MC = new TFile("./../rootfiles/D0_PbPb_acc_eff_ptbin_12_ybin_6_prompt_FONLLweight_cent-0to20_dataptshape.root");
    input_data = new TFile("./../Datamassspectrumfit/rootfiles/Dspectrum_pbpb_data_ptbin_12_ptd_unpreMBtrig_0_cent0to20.root");
	input_promptfraction = new TFile("Bfraction_method1_ptbin_12_cent0to20.root");
    cent_low = 0;
	cent_high = 20;
	Nptbin = 9;
	NEVT = 6.09279800000000000e+06;
	Draw_Recoeff_D0_PbPb( input_MC, input_data, input_promptfraction, NEVT, cent_low, cent_high, Nptbin);
	input_MC->Close();
	input_promptfraction->Close();
	input_data->Close();

// 5 ptbins
  input_MC = new TFile("./../rootfiles/D0_PbPb_acc_eff_ptbin_7_ybin_6_prompt_FONLLweight_cent-0to10_dataptshape.root");
  input_data = new TFile("./../Datamassspectrumfit/rootfiles/Dspectrum_pbpb_data_ptbin_7_ptd_unpreMBtrig_0_cent0to10.root");
  input_promptfraction = new TFile("Bfraction_method1_ptbin_7_cent0to10.root");
  cent_low = 0;
  cent_high = 10;
  Nptbin = 5;
  NEVT = 3.07931000000000000e+06;
  Draw_Recoeff_D0_PbPb( input_MC, input_data, input_promptfraction, NEVT, cent_low, cent_high, Nptbin);
  input_MC->Close();
  input_promptfraction->Close();
  input_data->Close();

	input_MC = new TFile("./../rootfiles/D0_PbPb_acc_eff_ptbin_7_ybin_6_prompt_FONLLweight_cent10to30_dataptshape.root");
    input_data = new TFile("./../Datamassspectrumfit/rootfiles/Dspectrum_pbpb_data_ptbin_7_ptd_unpreMBtrig_0_cent10to30.root");
    input_promptfraction = new TFile("Bfraction_method1_ptbin_7_cent10to30.root");
    cent_low = 10;
	cent_high = 30;
	Nptbin = 5;
	NEVT = 6.09303800000000000e+06;
	Draw_Recoeff_D0_PbPb( input_MC, input_data, input_promptfraction, NEVT, cent_low, cent_high, Nptbin);
	input_MC->Close();
	input_promptfraction->Close();
	input_data->Close();

	input_MC = new TFile("./../rootfiles/D0_PbPb_acc_eff_ptbin_7_ybin_6_prompt_FONLLweight_cent30to50_dataptshape.root");
    input_data = new TFile("./../Datamassspectrumfit/rootfiles/Dspectrum_pbpb_data_ptbin_7_ptd_unpreMBtrig_0_cent30to50.root");
    input_promptfraction = new TFile("Bfraction_method1_ptbin_7_cent30to50.root");
    cent_low = 30;
	cent_high = 50;
	Nptbin = 5;
	NEVT = 6.13955200000000000e+06;
	Draw_Recoeff_D0_PbPb( input_MC, input_data, input_promptfraction, NEVT, cent_low, cent_high, Nptbin);
	input_MC->Close();
	input_promptfraction->Close();
	input_data->Close();

	input_MC = new TFile("./../rootfiles/D0_PbPb_acc_eff_ptbin_7_ybin_6_prompt_FONLLweight_cent50to100_dataptshape.root");
    input_data = new TFile("./../Datamassspectrumfit/rootfiles/Dspectrum_pbpb_data_ptbin_7_ptd_unpreMBtrig_0_cent50to100.root");
    input_promptfraction = new TFile("Bfraction_method1_ptbin_7_cent50to100.root");
    cent_low = 50;
	cent_high = 100;
	Nptbin = 5;
	NEVT = 1.48603910000000000e+07;
	Draw_Recoeff_D0_PbPb( input_MC, input_data, input_promptfraction, NEVT, cent_low, cent_high, Nptbin);
	input_MC->Close();
	input_promptfraction->Close();
	input_data->Close();

}
