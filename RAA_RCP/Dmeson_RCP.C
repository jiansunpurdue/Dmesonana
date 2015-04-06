//#include "PtBins.h"

void Draw_RCP( TFile * input_pbpb_central, TFile * input_pbpb_perip, int cent_low, int cent_high, int Nptbin, double TAA_central, double TAA_perip)
{
	gStyle->SetOptTitle(0);
	gStyle->SetOptStat(0);
	TH1::SetDefaultSumw2();

	TH1D * D0Spectrum_pbpb_central = ( TH1D *) input_pbpb_central->Get("d0raw_data_overeff");
	TH1D * D0_pbpb_spectrum_central = ( TH1D * ) D0Spectrum_pbpb_central->Clone("D0_pbpb_spectrum_central");
	TH1D * hf_mb_central = ( TH1D * ) input_pbpb_central->Get("hf_mb");

	if( Nptbin == 8 )   
	{
		D0_pbpb_spectrum_central->SetBinContent(D0_pbpb_spectrum_central->FindBin(35), -9999999);
	    D0_pbpb_spectrum_central->SetBinError(D0_pbpb_spectrum_central->FindBin(35), 0);
		D0_pbpb_spectrum_central->GetYaxis()->SetRangeUser(5.0, 24);
	}

	D0_pbpb_spectrum_central->Scale(1.0/0.0388);    //branch ratio
	D0_pbpb_spectrum_central->Scale(0.5);          // D0 and anti D0
	D0_pbpb_spectrum_central->Scale(1.0/hf_mb_central->Integral(0,-1));   //number of MB events in PbPb
	D0_pbpb_spectrum_central->Scale(1.0/TAA_central);


	TH1D * D0Spectrum_pbpb_perip = ( TH1D *) input_pbpb_perip->Get("d0raw_data_overeff");
	TH1D * D0_pbpb_spectrum_perip = ( TH1D * ) D0Spectrum_pbpb_perip->Clone("D0_pbpb_spectrum_perip");
	TH1D * hf_mb_perip = ( TH1D * ) input_pbpb_perip->Get("hf_mb");

	if( Nptbin == 8 )   
	{
		D0_pbpb_spectrum_perip->SetBinContent(D0_pbpb_spectrum_perip->FindBin(35), -999);
	    D0_pbpb_spectrum_perip->SetBinError(D0_pbpb_spectrum_perip->FindBin(35), 0);
		D0_pbpb_spectrum_perip->GetYaxis()->SetRangeUser(5.0, 24);
	}

	D0_pbpb_spectrum_perip->Scale(1.0/0.0388);    //branch ratio
	D0_pbpb_spectrum_perip->Scale(0.5);          // D0 and anti D0
	D0_pbpb_spectrum_perip->Scale(1.0/hf_mb_perip->Integral(0,-1));   //number of MB events in PbPb
	D0_pbpb_spectrum_perip->Scale(1.0/TAA_perip);

	TCanvas * cfg_D0_central_perip = new TCanvas("cfg_D0_central_perip","cfg_D0_central_perip");
	cfg_D0_central_perip->SetLeftMargin(0.2);
	gPad->SetLogy();

    D0_pbpb_spectrum_central->GetYaxis()->SetTitleOffset(2.0);
    D0_pbpb_spectrum_central->GetYaxis()->SetTitle("#frac{1}{2N_{evt}T_{AA}}#frac{dN_{PbPb}}{dp_{T}} #frac{pb}{GeV/c}");
    D0_pbpb_spectrum_central->GetXaxis()->SetTitle("D0 p_{T} (GeV/c)");
    D0_pbpb_spectrum_central->GetYaxis()->SetRangeUser(1E2,1E8);
	D0_pbpb_spectrum_central->SetLineColor(1.0);
	D0_pbpb_spectrum_central->SetMarkerColor(1.0);

	D0_pbpb_spectrum_perip->SetLineColor(4.0);
	D0_pbpb_spectrum_perip->SetMarkerColor(4.0);

	D0_pbpb_spectrum_central->Draw();
	D0_pbpb_spectrum_perip->Draw("same");


	TH1D * D0_Rcp = (TH1D *)D0_pbpb_spectrum_central->Clone("D0_Rcp");

	D0_Rcp->Divide(D0_pbpb_spectrum_central, D0_pbpb_spectrum_perip, 1.0, 1.0);

	TCanvas * cfg_D0_Rcp = new TCanvas("cfg_D0_Rcp","cfg_D0_Rcp");
    
	D0_Rcp->GetYaxis()->SetTitleOffset(1.25);
	D0_Rcp->GetYaxis()->SetTitle("D^{0} R^{P, 50-100%}_{C}");
    D0_Rcp->GetYaxis()->SetRangeUser(0,2);
	D0_Rcp->Draw();


    TLatex Tl;
    Tl.SetNDC();
    Tl.SetTextAlign(12);
    Tl.SetTextSize(0.03);
    Tl.DrawLatex(0.3,0.8, "CMS Preliminary #sqrt{s_{NN}} = 2.76 TeV");
    Tl.DrawLatex(0.3,0.75, "#left|y#right| < 2.0");
    TString centrality;
    centrality.Form("Centrality %d%%-%d%%", cent_low,cent_high);
    cout << centrality << endl;
    Tl.DrawLatex(0.3,0.7, centrality);   


    char cfgname[200];
	sprintf(cfgname,"plots/RCPD0_PbPb_effunpre_cent%dto%d_ptbin%d.pdf",cent_low,cent_high, Nptbin);
	cfg_D0_Rcp->SaveAs(cfgname);
	sprintf(cfgname,"plots/RCPD0_PbPb_effunpre_cent%dto%d_ptbin%d.png",cent_low,cent_high, Nptbin);
	cfg_D0_Rcp->SaveAs(cfgname);

	char outputfile[200];
	sprintf(outputfile, "RCP_D0_PbPb_effunpre_cent%dto%d_ptbin%d.root", cent_low,cent_high, Nptbin);

	TFile * output = new TFile(outputfile,"RECREATE");

	D0_pbpb_spectrum_central->Write();
	D0_pbpb_spectrum_perip->Write();
	cfg_D0_central_perip->Write();
	cfg_D0_Rcp->Write();
	D0_Rcp->Write();

	output->Close();
	
}

void Dmeson_RCP()
{
    //double TAA_central = 5.67E-9;  //centrality 0 to 100  5.67 0.32
    // double TAA_central = 18.93e-9 ;     //Alice.  CMS????centrality 0 to 20
   // double TAA_central = 1.20e-9;      //Alice.   CMS????centrality 40 to 80

    double TAA_central;
	double TAA_perip = 0.47e-9; // 50 to 100%
	int cent_low, cent_high;
	int Nptbin;
	TFile * input_pbpb_central;
	TFile * input_pbpb_perip;

   //centrality 0 to 20%
      input_pbpb_central = new TFile("Spectrum_centRecoeff_D0_PbPb_dpt_evtunprescaleMB0_cent0to20_ptbin8.root");
	  input_pbpb_perip = new TFile("Spectrum_centRecoeff_D0_PbPb_dpt_evtunprescaleMB0_cent50to100_ptbin8.root");

	  TAA_central = 18.84e-9;   //CMS
	  cent_low = 0;
	  cent_high = 20;
	  Nptbin = 8;

	  Draw_RCP(input_pbpb_central, input_pbpb_perip, cent_low, cent_high, Nptbin, TAA_central, TAA_perip);

	  input_pbpb_central->Close();
	  input_pbpb_perip->Close();
      
   //centrality 10% to 30% 
	  input_pbpb_central = new TFile("Spectrum_centRecoeff_D0_PbPb_dpt_evtunprescaleMB0_cent10to30_ptbin8.root");
	  input_pbpb_perip = new TFile("Spectrum_centRecoeff_D0_PbPb_dpt_evtunprescaleMB0_cent50to100_ptbin8.root");

      TAA_central = 11.64e-9;
	  cent_low = 10;
	  cent_high = 30;
	  Nptbin = 8;

      Draw_RCP(input_pbpb_central, input_pbpb_perip, cent_low, cent_high, Nptbin, TAA_central, TAA_perip);

	  input_pbpb_central->Close();
	  input_pbpb_perip->Close();
      
   //centrality 30% to 50% 
	  input_pbpb_central = new TFile("Spectrum_centRecoeff_D0_PbPb_dpt_evtunprescaleMB0_cent30to50_ptbin8.root");
	  input_pbpb_perip = new TFile("Spectrum_centRecoeff_D0_PbPb_dpt_evtunprescaleMB0_cent50to100_ptbin8.root");

      TAA_central = 3.92e-9;
	  cent_low = 30;
	  cent_high = 50;
	  Nptbin = 8;

      Draw_RCP(input_pbpb_central, input_pbpb_perip, cent_low, cent_high, Nptbin, TAA_central, TAA_perip);

	  input_pbpb_central->Close();
	  input_pbpb_perip->Close();
      
// 4 ptbins, used for RAA vs Npart
   
   //centrality 0% to 10% 
	  input_pbpb_central = new TFile("Spectrum_centRecoeff_D0_PbPb_dpt_evtunprescaleMB0_cent0to10_ptbin4.root");
	  input_pbpb_perip = new TFile("Spectrum_centRecoeff_D0_PbPb_dpt_evtunprescaleMB0_cent50to100_ptbin4.root");

      TAA_central = 23.20e-9; //error 0.99
	  cent_low = 0;
	  cent_high = 10;
	  Nptbin = 4;

      Draw_RCP(input_pbpb_central, input_pbpb_perip, cent_low, cent_high, Nptbin, TAA_central, TAA_perip);

	  input_pbpb_central->Close();
	  input_pbpb_perip->Close();
   
   //centrality 10% to 30% 
	  input_pbpb_central = new TFile("Spectrum_centRecoeff_D0_PbPb_dpt_evtunprescaleMB0_cent10to30_ptbin4.root");
	  input_pbpb_perip = new TFile("Spectrum_centRecoeff_D0_PbPb_dpt_evtunprescaleMB0_cent50to100_ptbin4.root");

      TAA_central = 11.64e-9; //error 0.67
	  cent_low = 10;
	  cent_high = 30;
	  Nptbin = 4;

      Draw_RCP(input_pbpb_central, input_pbpb_perip, cent_low, cent_high, Nptbin, TAA_central, TAA_perip);

	  input_pbpb_central->Close();
	  input_pbpb_perip->Close();
   
   //centrality 30% to 50% 
	  input_pbpb_central = new TFile("Spectrum_centRecoeff_D0_PbPb_dpt_evtunprescaleMB0_cent30to50_ptbin4.root");
	  input_pbpb_perip = new TFile("Spectrum_centRecoeff_D0_PbPb_dpt_evtunprescaleMB0_cent50to100_ptbin4.root");

      TAA_central = 3.92e-9;  //error 0.37
	  cent_low = 30;
	  cent_high = 50;
	  Nptbin = 4;

      Draw_RCP(input_pbpb_central, input_pbpb_perip, cent_low, cent_high, Nptbin, TAA_central, TAA_perip);

	  input_pbpb_central->Close();
	  input_pbpb_perip->Close();
	
}
