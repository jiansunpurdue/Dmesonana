//#include "PtBins.h"
//

double syserrorPer_upper[10] = { 27.5e-2, 26.7e-2, 26.7e-2, 26.0e-2, 26.0e-2, 25.9e-2, 25.9e-2, 25.9e-2, 27.2e-2, 30.1e-2 };
double syserrorPer_lower[10] = { 29.0e-2, 27.2e-2, 27.2e-2, 26.0e-2, 26.0e-2, 25.9e-2, 25.9e-2, 25.9e-2, 27.2e-2, 30.1e-2 };
double syserror_Per_FONLL = 4.1e-2;

double syserrorPerTAAfraction = 5.8e-2;

void Draw_RAFONLL( TFile * input_pbpb, TFile * fonllinput, int cent_low, int cent_high, int Nptbin, double TAA)
{
	gStyle->SetOptTitle(0);
	gStyle->SetOptStat(0);
	TH1::SetDefaultSumw2();
	TH1D * D0Spectrum_pbpb = ( TH1D *) input_pbpb->Get("d0raw_data_overeff");
	TH1D * D0_pbpb_spectrum = ( TH1D * ) D0Spectrum_pbpb->Clone("D0_pbpb_spectrum");

	D0_pbpb_spectrum->Scale(1.0/TAA);
	
	if( Nptbin == 8 )   
	{
		D0_pbpb_spectrum->SetBinContent(D0_pbpb_spectrum->FindBin(35), -999);
	    D0_pbpb_spectrum->SetBinError(D0_pbpb_spectrum->FindBin(35), 0);
		D0_pbpb_spectrum->GetYaxis()->SetRangeUser(5.0, 24);
	}

	TGraphAsymmErrors * d0fonllspectrum = ( TGraphAsymmErrors *) fonllinput->Get("gaeSigmaDzero");

	TCanvas * spectrum = new TCanvas("spectrum","spectrum");
	spectrum->SetLeftMargin(0.2);
	gPad->SetLogy();


	TGraphAsymmErrors * D0_pbpb_spectrum_syserror = ( TGraphAsymmErrors *) d0fonllspectrum->Clone("D0_pbpb_spectrum_syserror");

	for( int i = 0; i < D0_pbpb_spectrum_syserror->GetN(); i++ )
	{
		double error_Per_lower = syserrorPer_lower[i]; 
		double error_Per_upper = syserrorPer_upper[i];
		double binvalue = D0_pbpb_spectrum->GetBinContent(i+2);
		cout << " binvalue : " << binvalue << "  error_Per_lower: " << error_Per_lower << "   error_Per_upper: " << error_Per_upper << endl;
		D0_pbpb_spectrum_syserror->GetY()[i] = binvalue;
		D0_pbpb_spectrum_syserror->SetPointEYhigh(i, error_Per_upper*binvalue);
		D0_pbpb_spectrum_syserror->SetPointEYlow(i, error_Per_lower*binvalue);
		cout << " error_Per_upper*binvalue: " << error_Per_upper*binvalue << "   error_Per_lower*binvalue: " << error_Per_lower*binvalue << endl;
	}


	D0_pbpb_spectrum_syserror->GetYaxis()->SetRangeUser(10E1,10E7);
	D0_pbpb_spectrum_syserror->GetXaxis()->SetRangeUser(3.5,40);
    D0_pbpb_spectrum_syserror->GetYaxis()->SetTitleOffset(2.0);
    D0_pbpb_spectrum_syserror->GetYaxis()->SetTitle("#frac{d#sigma_{pp}}{dp_{T}}, #frac{1}{2N_{evt}T_{AA}} #frac{dN_{PbPb}}{dp_{T}} #frac{pb}{GeV/c}");
	D0_pbpb_spectrum_syserror->GetXaxis()->SetTitle("Prompt D^{0} p_{T} (GeV/c)");
//	D0_pbpb_spectrum_syserror->GetYaxis()->SetRangeUser(10E-8,10E0);   //Alice way to plot, scale pp cross section by TAA rather than PbPb
//	D0_pbpb_spectrum_syserror->GetYaxis()->SetTitle("dN/dp_{T}");
//    D0_pbpb_spectrum_syserror->SetFillColor(kRed-10);
//	D0_pbpb_spectrum_syserror->SetLineColor(kRed-10);
    D0_pbpb_spectrum_syserror->SetFillColor(5.0);
	D0_pbpb_spectrum_syserror->SetLineColor(5.0);
	D0_pbpb_spectrum_syserror->SetFillStyle(1001);
	D0_pbpb_spectrum_syserror->Draw("A2");

    D0_pbpb_spectrum->SetFillColor(5.0);
	D0_pbpb_spectrum->SetFillStyle(1001);
	D0_pbpb_spectrum->Draw("epsame");
	
//	double scale = 5.67/1.0E9;    //TAA
//	for( int i = 0; i < d0fonllspectrum->GetN();i++){
//		d0fonllspectrum->GetY()[i] = d0fonllspectrum->GetY()[i] * scale;
//		d0fonllspectrum->SetPointEYhigh(i,d0fonllspectrum->GetErrorYhigh(i)*scale);
//		d0fonllspectrum->SetPointEYlow(i,d0fonllspectrum->GetErrorYlow(i)*scale);
//	}
	d0fonllspectrum->SetLineWidth(0.5);
	d0fonllspectrum->SetMarkerStyle(20);
	d0fonllspectrum->SetMarkerSize(0.8);
	d0fonllspectrum->Draw("psame");

	TLegend * t = new TLegend(0.35, 0.7, 0.85, 0.85);
	t->SetFillColor(0);
	t->AddEntry(D0_pbpb_spectrum, Form("PbPb Data, centrality %d-%d%%", cent_low, cent_high));
	t->AddEntry(d0fonllspectrum, "FONLL", "PL");
	t->Draw();


	TCanvas * raadmeson = new TCanvas("raadmeson","raadmeson");
	TH1D * D0_pbpb_spectrum_raa = ( TH1D *) D0_pbpb_spectrum->Clone("D0_pbpb_spectrum_raa");
	TGraphAsymmErrors * D0_fonll_raa_errordata = ( TGraphAsymmErrors *) d0fonllspectrum->Clone("D0_fonll_raa_errordata");
	TGraphAsymmErrors * D0_fonll_raa_errorfonll = ( TGraphAsymmErrors *) d0fonllspectrum->Clone("D0_fonll_raa_errorfonll");

	for( int i = 0; i < D0_fonll_raa_errordata->GetN();i++){
		D0_fonll_raa_errordata->GetY()[i] = D0_pbpb_spectrum_raa->GetBinContent(i+2) / d0fonllspectrum->GetY()[i];
//		cout << "PbPb: " << D0_pbpb_spectrum_raa->GetBinContent(i+2) << " pp: " << d0fonllspectrum->GetY()[i] << " RAA: " << D0_fonll_raa_errordata->GetY()[i] << endl;
//        cout << "Pbbin: " << ptbins[i+1] << " to " << ptbins[i+2] <<   " RAA: " << D0_fonll_raa_errordata->GetY()[i] << endl;
//		double higherror =  TMath::Sqrt( TMath::Power(D0_pbpb_spectrum_raa->GetBinError(i+2), 2) / TMath::Power(d0fonllspectrum->GetY()[i] ,2) );
//        double lowerror =  TMath::Sqrt( TMath::Power(D0_pbpb_spectrum_raa->GetBinError(i+2), 2) / TMath::Power(d0fonllspectrum->GetY()[i] ,2) );
        double higherror = D0_pbpb_spectrum_raa->GetBinError(i+2)/d0fonllspectrum->GetY()[i];
		double lowerror = D0_pbpb_spectrum_raa->GetBinError(i+2)/d0fonllspectrum->GetY()[i];
		D0_fonll_raa_errordata->SetPointEYhigh(i, higherror);
		D0_fonll_raa_errordata->SetPointEYlow(i, lowerror);

        D0_fonll_raa_errorfonll->GetY()[i] = D0_pbpb_spectrum_raa->GetBinContent(i+2) / d0fonllspectrum->GetY()[i];
        
		double errorPer_low_fonll = d0fonllspectrum->GetErrorYlow(i)/d0fonllspectrum->GetY()[i];
		double errorPer_high_fonll = d0fonllspectrum->GetErrorYhigh(i)/d0fonllspectrum->GetY()[i];
		double toterrorPer_low_fonll = TMath::Sqrt(syserror_Per_FONLL*syserror_Per_FONLL + errorPer_low_fonll*errorPer_low_fonll);
		double  toterrorPer_high_fonll = TMath::Sqrt(syserror_Per_FONLL*syserror_Per_FONLL + errorPer_high_fonll*errorPer_high_fonll);

		cout << "FONLL error, lower: " << toterrorPer_low_fonll << "   upper: " << toterrorPer_high_fonll << endl;

		higherror = toterrorPer_low_fonll / (1. - toterrorPer_low_fonll ) * D0_fonll_raa_errordata->GetY()[i];
		lowerror = errorPer_high_fonll / ( 1. + errorPer_high_fonll ) * D0_fonll_raa_errordata->GetY()[i];
        D0_fonll_raa_errorfonll->SetPointEYhigh(i, higherror);
        D0_fonll_raa_errorfonll->SetPointEYlow(i, lowerror);

	}

    TGraphAsymmErrors * D0_fonll_raa_syserror = ( TGraphAsymmErrors *) D0_fonll_raa_errordata->Clone("D0_fonll_raa_syserror");

    for( int i = 0; i < D0_fonll_raa_syserror->GetN(); i++ )
	{
//		cout << " RAA: " << D0_fonll_raa_syserror->GetY()[i] << endl;
        double error_Per_lower = syserrorPer_lower[i];
        double error_Per_upper = syserrorPer_upper[i];
		double syserror_lower =  error_Per_lower * D0_fonll_raa_syserror->GetY()[i];
		double syserror_upper =  error_Per_upper * D0_fonll_raa_syserror->GetY()[i];
		cout << "sys error, lower : " << error_Per_lower << "   upper: " << error_Per_upper << endl; 
		D0_fonll_raa_syserror->SetPointEYlow(i, syserror_lower);
		D0_fonll_raa_syserror->SetPointEYhigh(i, syserror_upper);
	}
	

	D0_fonll_raa_errordata->GetYaxis()->SetRangeUser(0.,2.);
	D0_fonll_raa_errordata->GetXaxis()->SetRangeUser(3.5,40.);
	D0_fonll_raa_errordata->GetYaxis()->SetTitle("Prompt D^{0} R^{FONLL}_{AA}");
	D0_fonll_raa_errordata->GetXaxis()->SetTitle("Prompt D^{0} p_{T} (GeV/c)");
	D0_fonll_raa_errordata->SetFillColor(5.0);
	D0_fonll_raa_errordata->SetFillStyle(1001);

	D0_fonll_raa_syserror->GetYaxis()->SetRangeUser(0.,2.);
	D0_fonll_raa_syserror->GetXaxis()->SetRangeUser(1.5,40.);
	D0_fonll_raa_syserror->GetYaxis()->SetTitle("Prompt D^{0} R^{FONLL}_{AA}");
	D0_fonll_raa_syserror->GetXaxis()->SetTitle("Prompt D^{0} p_{T} (GeV/c)");
//	D0_fonll_raa_syserror->SetFillColor(38.0);
//	D0_fonll_raa_syserror->SetLineColor(38.0);
    D0_fonll_raa_syserror->SetFillColor(5.0);
	D0_fonll_raa_syserror->SetLineColor(5.0);
	D0_fonll_raa_syserror->SetFillStyle(1001);

	D0_fonll_raa_syserror->Draw("A2");

	D0_fonll_raa_errorfonll->SetFillColor(0);
	D0_fonll_raa_errorfonll->SetFillStyle(0);
	D0_fonll_raa_errorfonll->Draw("2same");

	D0_fonll_raa_errordata->Draw("Psame");

    TBox *b = new TBox(1.5,1-syserrorPerTAAfraction,3.5,1+syserrorPerTAAfraction);
    b->SetLineColor(kGray);
    b->SetFillColor(kGray);
    b->Draw();

    TLegend *leg = new TLegend(0.5,0.65,0.85,0.8);
	leg->SetTextFont(62);
    leg->AddEntry(D0_fonll_raa_errordata,"Prompt D^{0} R^{FONLL}_{AA}","PLf");
    leg->AddEntry(D0_fonll_raa_errorfonll,"Syst. err. from FONLL","f");
	leg->AddEntry(b, "Syst. TAA+BR","f");
    leg->SetBorderSize(0);
    leg->SetFillStyle(0);
    leg->Draw();

    TLatex Tl;
    Tl.SetNDC();
    Tl.SetTextAlign(12);
    Tl.SetTextSize(0.03);
	Tl.SetTextFont(62);
    Tl.DrawLatex(0.15,0.85, "CMS Preliminary #sqrt{s_{NN}} = 2.76 TeV");
    Tl.DrawLatex(0.15,0.80, "#left|y#right| < 2.0");
    TString centrality; 
	centrality.Form("Centrality %d-%d%%", cent_low,cent_high);
	cout << centrality << endl;
    Tl.DrawLatex(0.15,0.75, centrality);

    char cfgname[200];
	sprintf(cfgname,"results/PromptD0_PbPb_spectrum_fonll_effunpre_cent%dto%d_ptbin%d.pdf",cent_low,cent_high, Nptbin);
	spectrum->SaveAs(cfgname);
	sprintf(cfgname,"results/PromptD0_PbPb_spectrum_fonll_effunpre_cent%dto%d_ptbin%d.png",cent_low,cent_high, Nptbin);
	spectrum->SaveAs(cfgname);
	sprintf(cfgname,"results/PromptRAAD0_PbPb_fonll_effunpre_cent%dto%d_ptbin%d.pdf",cent_low,cent_high, Nptbin);
	raadmeson->SaveAs(cfgname);
	sprintf(cfgname,"results/PromptRAAD0_PbPb_fonll_effunpre_cent%dto%d_ptbin%d.png",cent_low,cent_high, Nptbin);
	raadmeson->SaveAs(cfgname);

	char outputfile[200];
	sprintf(outputfile, "PromptRAA_D0_PbPb_spectrum_fonll_effunpre_cent%dto%d_ptbin%d.root", cent_low,cent_high, Nptbin);
	TFile * output = new TFile(outputfile,"RECREATE");
    D0_pbpb_spectrum->Write();
    d0fonllspectrum->Write();
	D0_fonll_raa_errorfonll->Write();
	D0_fonll_raa_errordata->Write();
	spectrum->Write();
	raadmeson->Write();
	output->Close();
}

void Dmeson_RAFONLL_prompt()
{
    //double TAA = 5.67E-9;  //centrality 0 to 100  5.67 0.32
    // double TAA = 18.93e-9 ;     //Alice.  CMS????centrality 0 to 20
   // double TAA = 1.20e-9;      //Alice.   CMS????centrality 40 to 80

    double TAA;
	int cent_low, cent_high;
	int Nptbin;
	TFile * input_pbpb;
	TFile * fonllinput;

   //centrality 0 to 100%
      input_pbpb = new TFile("Prompt_Spectrum_centRecoeff_D0_PbPb_dpt_evtunprescaleMB0_cent0to100_ptbin10.root");
	  fonllinput = new TFile("./../FONLL/fonll/outputDzero.root");

	  TAA = 5.67E-9;
	  cent_low = 0;
	  cent_high = 100;
	  Nptbin = 10;

	  Draw_RAFONLL(input_pbpb, fonllinput, cent_low, cent_high, Nptbin, TAA);

//	  input_pbpb->Close();
//	  fonllinput->Close();

//   //centrality 0 to 20%
//      input_pbpb = new TFile("Spectrum_centRecoeff_D0_PbPb_dpt_evtunprescaleMB0_cent0to20_ptbin8.root");
//	  fonllinput = new TFile("./FONLL/fonll/outputDzero.root");
//
//	  TAA = 18.84e-9;   //CMS
//	  cent_low = 0;
//	  cent_high = 20;
//	  Nptbin = 8;
//
//	  Draw_RAFONLL(input_pbpb, fonllinput, cent_low, cent_high, Nptbin, TAA);
//
//	  input_pbpb->Close();
//	  fonllinput->Close();
//      
//   //centrality 40% to 80% 
//	  input_pbpb = new TFile("Spectrum_centRecoeff_D0_PbPb_dpt_evtunprescaleMB0_cent40to80_ptbin8.root");
//	  fonllinput = new TFile("./FONLL/fonll/outputDzero.root");
//
//      TAA = 1.20e-9;
//	  cent_low = 40;
//	  cent_high = 80;
//	  Nptbin = 8;
//
//      Draw_RAFONLL(input_pbpb, fonllinput, cent_low, cent_high, Nptbin, TAA);
//
//	  input_pbpb->Close();
//	  fonllinput->Close();
//      
//   //centrality 10% to 30% 
//	  input_pbpb = new TFile("Spectrum_centRecoeff_D0_PbPb_dpt_evtunprescaleMB0_cent10to30_ptbin8.root");
//	  fonllinput = new TFile("./FONLL/fonll/outputDzero.root");
//
//      TAA = 11.64e-9;
//	  cent_low = 10;
//	  cent_high = 30;
//	  Nptbin = 8;
//
//      Draw_RAFONLL(input_pbpb, fonllinput, cent_low, cent_high, Nptbin, TAA);
//
//	  input_pbpb->Close();
//	  fonllinput->Close();
//      
//   //centrality 30% to 50% 
//	  input_pbpb = new TFile("Spectrum_centRecoeff_D0_PbPb_dpt_evtunprescaleMB0_cent30to50_ptbin8.root");
//	  fonllinput = new TFile("./FONLL/fonll/outputDzero.root");
//
//      TAA = 3.92e-9;
//	  cent_low = 30;
//	  cent_high = 50;
//	  Nptbin = 8;
//
//      Draw_RAFONLL(input_pbpb, fonllinput, cent_low, cent_high, Nptbin, TAA);
//
//	  input_pbpb->Close();
//	  fonllinput->Close();
//      
//   //centrality 50% to 100% 
//	  input_pbpb = new TFile("Spectrum_centRecoeff_D0_PbPb_dpt_evtunprescaleMB0_cent50to100_ptbin8.root");
//	  fonllinput = new TFile("./FONLL/fonll/outputDzero.root");
//
//      TAA = 0.47e-9;
//	  cent_low = 50;
//	  cent_high = 100;
//	  Nptbin = 8;
//
//      Draw_RAFONLL(input_pbpb, fonllinput, cent_low, cent_high, Nptbin, TAA);
//
//	  input_pbpb->Close();
//	  fonllinput->Close();
//     
//// 4 ptbins, used for RAA vs Npart
//   
//   //centrality 0% to 10% 
//	  input_pbpb = new TFile("Spectrum_centRecoeff_D0_PbPb_dpt_evtunprescaleMB0_cent0to10_ptbin4.root");
//	  fonllinput = new TFile("./FONLL/fonll/outputDzero_4ptbin.root");
//
//      TAA = 23.20e-9; //error 0.99
//	  cent_low = 0;
//	  cent_high = 10;
//	  Nptbin = 4;
//
//      Draw_RAFONLL(input_pbpb, fonllinput, cent_low, cent_high, Nptbin, TAA);
//
//	  input_pbpb->Close();
//	  fonllinput->Close();
//   
//   //centrality 10% to 30% 
//	  input_pbpb = new TFile("Spectrum_centRecoeff_D0_PbPb_dpt_evtunprescaleMB0_cent10to30_ptbin4.root");
//	  fonllinput = new TFile("./FONLL/fonll/outputDzero_4ptbin.root");
//
//      TAA = 11.64e-9; //error 0.67
//	  cent_low = 10;
//	  cent_high = 30;
//	  Nptbin = 4;
//
//      Draw_RAFONLL(input_pbpb, fonllinput, cent_low, cent_high, Nptbin, TAA);
//
//	  input_pbpb->Close();
//	  fonllinput->Close();
//   
//   //centrality 30% to 50% 
//	  input_pbpb = new TFile("Spectrum_centRecoeff_D0_PbPb_dpt_evtunprescaleMB0_cent30to50_ptbin4.root");
//	  fonllinput = new TFile("./FONLL/fonll/outputDzero_4ptbin.root");
//
//      TAA = 3.92e-9;  //error 0.37
//	  cent_low = 30;
//	  cent_high = 50;
//	  Nptbin = 4;
//
//      Draw_RAFONLL(input_pbpb, fonllinput, cent_low, cent_high, Nptbin, TAA);
//
//	  input_pbpb->Close();
//	  fonllinput->Close();
//   
//   //centrality 50% to 100% 
//	  input_pbpb = new TFile("Spectrum_centRecoeff_D0_PbPb_dpt_evtunprescaleMB0_cent50to100_ptbin4.root");
//	  fonllinput = new TFile("./FONLL/fonll/outputDzero_4ptbin.root");
//
//      TAA = 0.47e-9;  //error 0.07
//	  cent_low = 50;
//	  cent_high = 100;
//	  Nptbin = 4;
//
//      Draw_RAFONLL(input_pbpb, fonllinput, cent_low, cent_high, Nptbin, TAA);
//
//	  input_pbpb->Close();
//	  fonllinput->Close();
//	
}
