#include <TFile.h>
#include <TH1D.h>
#include <TF1.h>
#include <TCanvas.h>
#include <TPad.h>
#include <TStyle.h>
#include <TLegend.h>
#include <iostream>
#include <THStack.h>
#include <TString.h>


//present parameter setup just work for D0 pt 7 GeV to 40 GeV

double sideband_close = 0.05;//0.10;//0.10;//0.07; //0.06
double sideband_far = 0.07;//0.15;//0.15;//0.10;  //0.11
double width_signal = 0.03;
double mass_d0 = 1.865;

//double range_fit_low = mass_d0 - sideband_far;
//double range_fit_high = mass_d0 + sideband_far;

double range_fit_low = 1.7;
double range_fit_high = 2.05;

TFile * output;

void Getdistributionwithsideband(TString varname, TH1D * h_signal_dis, TFile * input, TString type)
{
  gStyle->SetHistMinimumZero(kTRUE);
  TH1D* h_leftband = ( TH1D *) input->Get(Form("%s_leftband",varname.Data()));
  TH1D* h_rightband = ( TH1D *) input->Get(Form("%s_rightband",varname.Data()));
  TH1D* h_band = ( TH1D *) input->Get(Form("%s_band",varname.Data()));
  TH1D* h_signalregion = ( TH1D *) input->Get(Form("%s_signalregion",varname.Data()));
  TH1D* h_mass = ( TH1D *) input->Get(Form("mass_%s",varname.Data()));


  TCanvas * c_mass = new TCanvas(Form("c_mass_%s",varname.Data()),"");

  double fit_range_low = 1.70;
  double fit_range_high = 2.05;

	TF1* fit_fun = new TF1("fit_fun", "[0]*([3]*Gaus(x,[1],[2])/(sqrt(2*3.14159)*[2])+(1-[3])*Gaus(x,[1],[4])/(sqrt(2*3.14159)*[4])) + gausn(5) * ([0]/0.01) * (1.0/[8]) + expo(9)", 1.70, 2.05);
	fit_fun->SetLineColor(1.0);
	//	fit_fun->SetLineWidth(2.0);

	float max = h_mass->GetMaximum();
	h_mass->SetMaximum(1.15 * max);
	fit_fun->SetParameter(0, 1.5 * max);
	fit_fun->SetParameter(9, 2.0);
	//
	fit_fun->SetParameter(1, 1.865);
	fit_fun->FixParameter(2, 0.01084);
	fit_fun->FixParameter(4, 0.02453);
	fit_fun->FixParameter(3, 0.9506);

	// does not work, cannot float them, mean is OK to float
	fit_fun->SetParLimits(1, 1.855, 1.875);

	//gaussian as particle misid D0 function
	fit_fun->FixParameter(5, 6.614e4);
	fit_fun->FixParameter(6, 1.872);
	fit_fun->FixParameter(7, 0.116);
	fit_fun->FixParameter(8, 7.7598e6);

	int pass = 0;
	int fittingtry = 0;

	char sig_print[100], chi2_print[100], mean_print[100], sigma_print[100];

	while (!pass) {


		h_mass->Fit(fit_fun,"L","", fit_range_low, fit_range_high);
		fittingtry++;

		if (fittingtry == 3)  
		{
			pass = 1;

		}

	}
	//.. draw foreground and background ..
	h_mass->Draw();

	// double gaussian signal
	TF1* fit_fun_1st = (TF1*)fit_fun->Clone("fit_fun_1st");
	for( int ipar = 5; ipar < 11; ipar++ )
		fit_fun_1st->SetParameter(ipar, 0);

	//expo bkg
	TF1* fit_fun_bg = (TF1*)fit_fun->Clone("fit_fun_bg");
	for( int ipar = 0; ipar < 9; ipar++ )
		fit_fun_bg->SetParameter(ipar, 0);
	fit_fun_bg->SetLineColor(4);
	fit_fun_bg->SetLineStyle(2);
	fit_fun_bg->Draw("same");

	//misid D0 plus bkg
	TF1* fit_fun_bgplusmisid = new TF1("fit_fun_bgplusmisid", "gausn(0) * ([6]/0.01) * (1.0/[3]) + expo(4)", fit_range_low, fit_range_high);
	fit_fun_bgplusmisid->SetParameter(6, fit_fun->GetParameter(0)); //number of D0
	fit_fun_bgplusmisid->SetParError(6, fit_fun->GetParError(0));
	for( int ipar = 0; ipar < 6; ipar++ )
	{
		fit_fun_bgplusmisid->SetParameter(ipar, fit_fun->GetParameter(ipar+5));
	    fit_fun_bgplusmisid->SetParError(ipar, fit_fun->GetParError(ipar+5));
	}
	fit_fun_bgplusmisid->SetLineColor(8);
	fit_fun_bgplusmisid->SetLineStyle(2);
	fit_fun_bgplusmisid->Draw("same");

  double sidebandcounts = fit_fun_bgplusmisid->Integral(mass_d0-sideband_far, mass_d0-sideband_close) + fit_fun_bgplusmisid->Integral( mass_d0+sideband_close, mass_d0+sideband_far);
  double signalregioncounts = fit_fun_bgplusmisid->Integral(mass_d0-width_signal, mass_d0+width_signal);

//  h_leftband->Scale( h_rightband->Integral(0, -1) / h_leftband->Integral(0, -1) );

  h_band->Add(h_leftband, h_rightband, 1.0, 1.0);

  cout << "slideband counts fit: "  << sidebandcounts << "  h_band:" << h_band->Integral(0, -1) << "   signalregioncounts: " << signalregioncounts << endl;
  cout << "Integral test: " << fit_fun_bgplusmisid->Integral(1.867, 1.887) << "   " << fit_fun_bgplusmisid->Integral(1.867, 1.877) << endl;
//  h_band->Scale( width_signal/(sideband_far - sideband_close) );
  h_band->Scale( signalregioncounts/ ( 0.01 * h_band->Integral( 0, -1) ) );
  h_signal_dis->Add( h_signalregion, h_band, 1.0, -1.0);
//
  if( type == "data" )
  {
	  c_mass->SaveAs(Form("plots_nocentralityweight_doublegaussian/varmass_bothsideband_%s_pt7to40_%s_cent30to100.pdf",varname.Data(),type.Data()));
	  c_mass->SaveAs(Form("plots_nocentralityweight_doublegaussian/varmass_bothsideband_%s_pt7to40_%s_cent30to100.png",varname.Data(),type.Data()));
  }
//
//  if( type == "data" )
//  {
//	  output->cd();
//      h_signalregion->Write();
//      h_band->Write();
//      h_signal_dis->Write();
//  }
}

void GetRatio( TH1D * h_signal_dis_data_copy, TH1D * h_mc_total, float range1, float range2, float cut1, float cut2)
{
  gStyle->SetHistMinimumZero(kTRUE);
  int bin1 = h_signal_dis_data_copy->FindBin(range1);
  int bin2 = h_signal_dis_data_copy->FindBin(range2);

  int cutbin1 = h_signal_dis_data_copy->FindBin(cut1);
  int cutbin2 = h_signal_dis_data_copy->FindBin(cut2);

  cout << " *************************** cut1: " << cut1 << "    cut2: " << cut2 << " *******************" << endl;

  double error = -9999.;

  TH1D* counts_data_nocut = new TH1D("counts_data_nocut", "counts_data_nocut", 1, 0, 1);
  counts_data_nocut->SetBinContent(1, h_signal_dis_data_copy->IntegralAndError(bin1, bin2, error));
  counts_data_nocut->SetBinError(1, error);

  cout << "data  nocut counts: " << h_signal_dis_data_copy->IntegralAndError(bin1, bin2, error) << "  error: " << error << endl;

  TH1D* counts_data_cut = new TH1D("counts_data_cut", "counts_data_cut", 1, 0, 1);
  counts_data_cut->SetBinContent(1, h_signal_dis_data_copy->IntegralAndError(cutbin1, cutbin2, error));
  counts_data_cut->SetBinError(1, error);

  cout << "data cut counts: " << h_signal_dis_data_copy->IntegralAndError(cutbin1, cutbin2, error) << "   error: " << error << endl;

  counts_data_cut->Divide(counts_data_cut, counts_data_nocut, 1.0, 1.0, "B");
  cout <<"  data eff: " << counts_data_cut->GetBinContent(1) << "   error: " << counts_data_cut->GetBinError(1) << endl;

  TH1D* counts_mc_nocut = new TH1D("counts_mc_nocut", "counts_mc_nocut", 1, 0, 1);
  counts_mc_nocut->SetBinContent(1, h_mc_total->IntegralAndError(bin1, bin2, error));
  counts_mc_nocut->SetBinError(1, error);

  cout << "mc nocut counts: "<< h_mc_total->IntegralAndError(bin1, bin2, error) << "  error: " << error << endl;

  TH1D* counts_mc_cut = new TH1D("counts_mc_cut", "counts_mc_cut", 1, 0, 1);
  counts_mc_cut->SetBinContent(1, h_mc_total->IntegralAndError(cutbin1, cutbin2, error));
  counts_mc_cut->SetBinError(1, error);

  cout << "mc cut counts: " << h_mc_total->IntegralAndError(cutbin1, cutbin2, error) << "  error: " << error << endl;

  counts_mc_cut->Divide(counts_mc_cut, counts_mc_nocut, 1.0, 1.0, "B");
  cout <<"  mc eff: " << counts_mc_cut->GetBinContent(1) << "   error: " << counts_mc_cut->GetBinError(1) << endl;

  TH1D * ratio_data_mc = (TH1D*) counts_mc_cut->Clone("ratio_data_mc");
  ratio_data_mc->Divide(counts_data_cut, counts_mc_cut, 1.0, 1.0);

  cout <<" ratio(data/mc) :" << ratio_data_mc->GetBinContent(1) << "   error: " << ratio_data_mc->GetBinError(1) << endl;

}

void Drawvariable(TString varname, TString vartitle, TFile * input_data, TFile * input_mc_prompt, TFile * input_mc_BtoD, float min, float max, int rebin, float range1, float range2, float cut1, float cut2)
{
	gStyle->SetHistMinimumZero(kTRUE);

  TH1D* h_signal_dis_data = ( TH1D *) input_data->Get(Form("%s_signal_data",varname.Data()));
  TH1D* h_signal_dis_mc_prompt = ( TH1D *) input_mc_prompt->Get(Form("%s_signal_data",varname.Data()));
  TH1D* h_signal_dis_mc_BtoD = ( TH1D *) input_mc_BtoD->Get(Form("%s_signal_data",varname.Data()));

  Getdistributionwithsideband( varname, h_signal_dis_data, input_data, "data");
  Getdistributionwithsideband( varname, h_signal_dis_mc_prompt, input_mc_prompt, "mc_prompt");
  Getdistributionwithsideband( varname, h_signal_dis_mc_BtoD, input_mc_BtoD, "mc_BtoD");

  double datacounts = h_signal_dis_data->Integral(0, -1);
  double BtoDfraction = 0.075;
  
  h_signal_dis_mc_prompt->Scale( datacounts * ( 1.0 - BtoDfraction) / h_signal_dis_mc_prompt->Integral(0, -1) );
  h_signal_dis_mc_BtoD->Scale( datacounts * BtoDfraction / h_signal_dis_mc_BtoD->Integral(0, -1) );

//  double datacounts = h_signal_dis_data->Integral(h_signal_dis_data->FindBin(min), h_signal_dis_data->FindBin(max) );
//  double BtoDfraction = 0.05;
//  
//  h_signal_dis_mc_prompt->Scale( datacounts * ( 1.0 - BtoDfraction) / h_signal_dis_mc_prompt->Integral(h_signal_dis_mc_prompt->FindBin(min), h_signal_dis_mc_prompt->FindBin(max)) );
//  h_signal_dis_mc_BtoD->Scale( datacounts * BtoDfraction / h_signal_dis_mc_BtoD->Integral(h_signal_dis_mc_BtoD->FindBin(min), h_signal_dis_mc_BtoD->FindBin(max)) );

  TH1D * h_mc_total = ( TH1D *) h_signal_dis_mc_prompt->Clone("h_mc_total");
  h_mc_total->Add( h_signal_dis_mc_prompt, h_signal_dis_mc_BtoD, 1.0, 1.0);
  TH1D * h_signal_dis_data_copy = ( TH1D *) h_signal_dis_data->Clone("h_signal_dis_data_copy");

  GetRatio( h_signal_dis_data_copy, h_mc_total, range1, range2, cut1, cut2);

  h_signal_dis_data->Rebin(rebin);
  h_signal_dis_mc_prompt->Rebin(rebin);
  h_signal_dis_mc_BtoD->Rebin(rebin);

  TCanvas *c = new TCanvas(Form("c%s",varname.Data()),"",600,600);
  TPad *pad1 = new TPad("pad1","top pad",0.0,0.3,1.0,1.0);
  pad1->Draw();
  TPad *pad2 = new TPad("pad2","bottom pad",0.0,0.0,1.0,0.3);
  pad2->Draw();

  pad1->cd();

  if( varname == "ffls3d" )   gPad->SetLogy();

  THStack* hs_allD_mc = new THStack("hs_allD_mc","hs_allD_mc");

  h_signal_dis_mc_BtoD->SetLineColor(2.0);
  h_signal_dis_mc_BtoD->SetFillStyle(3345);
  h_signal_dis_mc_BtoD->SetFillColor(2.0);
  h_signal_dis_mc_BtoD->SetLineWidth(2);
  h_signal_dis_mc_BtoD->SetStats(0);
  hs_allD_mc->Add(h_signal_dis_mc_BtoD, "HISTe");

  h_signal_dis_mc_prompt->SetLineColor(4.0);
  h_signal_dis_mc_prompt->SetFillStyle(3345);
  h_signal_dis_mc_prompt->SetFillColor(4.0);
  h_signal_dis_mc_prompt->SetLineWidth(2);
  h_signal_dis_mc_prompt->SetStats(0);
  hs_allD_mc->Add(h_signal_dis_mc_prompt, "HISTe");

  h_signal_dis_data->SetLineColor(1.0);
  h_signal_dis_data->SetMarkerColor(1.0);
  h_signal_dis_data->SetMarkerStyle(20);
  h_signal_dis_data->SetMarkerSize(0.8);
  h_signal_dis_data->SetStats(0);

  if( varname != "ffls3d" )  hs_allD_mc->SetMinimum(0.);
  hs_allD_mc->Draw();
  h_signal_dis_data->DrawCopy("epsame");
  
  hs_allD_mc->GetXaxis()->SetTitle(Form("%s",vartitle.Data()));
  hs_allD_mc->GetXaxis()->SetRangeUser(min, max - 0.001);
  cout << "min:::  "  << min << "   max:: " << max << endl;
//  hs_allD_mc->GetXaxis()->SetLimits(min, max);
  hs_allD_mc->GetYaxis()->SetTitle("Counts");
  hs_allD_mc->GetYaxis()->SetTitleOffset(1.2);
  hs_allD_mc->SetMaximum(h_signal_dis_data->GetMaximum()*1.4);

  TLegend *leg = new TLegend(0.55,0.7,0.85,0.85);
  leg->AddEntry(h_signal_dis_data,"Data Signal","PL");
  leg->AddEntry(h_signal_dis_mc_prompt,"MC Prompt D^{0} Signal","f");
  leg->AddEntry(h_signal_dis_mc_BtoD,"MC B Feed-down D^{0} Signal","f");
  leg->SetBorderSize(0);
  leg->SetFillStyle(0);
  leg->Draw();

  pad2->cd();
  TH1D * DataMCratio = ( TH1D *) (hs_allD_mc->GetStack()->Last())->Clone("DataMCratio");
  DataMCratio->Divide(h_signal_dis_data, DataMCratio, 1.0, 1.0);
  DataMCratio->GetXaxis()->SetRangeUser(min, max - 0.001);
  DataMCratio->GetYaxis()->SetRangeUser(0.0, 2.0);
  DataMCratio->GetYaxis()->SetTitleOffset(0.6);
  DataMCratio->GetYaxis()->SetTitleSize(0.08);
  DataMCratio->GetYaxis()->SetLabelSize(0.08);
  DataMCratio->GetYaxis()->SetTitle("Data/MC");
  DataMCratio->DrawCopy();

  c->SaveAs(Form("plots_nocentralityweight_doublegaussian/varcomparison_cent30to100_bothsideband_%s_BtoDfraction%1.2f_pt7to40_allcut_datapt_double.pdf",varname.Data(), BtoDfraction));
  c->SaveAs(Form("plots_nocentralityweight_doublegaussian/varcomparison_cent30to100_bothsideband_%s_BtoDfraction%1.2f_pt7to40_allcut_datapt_double.png",varname.Data(), BtoDfraction));
}

void DrawComparison_bothsideband_promptBtoD_doublegaussian()
{
  gStyle->SetOptTitle(0);
  gStyle->SetOptStat(0);
  gStyle->SetOptFit(1);
  TH1::SetDefaultSumw2();
  gStyle->SetHistMinimumZero(kTRUE);
  output = new TFile("Signal_cut_distribution_pt7to40.root","RECREATE");
  
  TFile * input_data = new TFile("datafiles/Cut_distribution_Data_sideband_pt7to40_rapidity0to1_cent30to100_0To1_cuts0.root");
  TFile * input_mc_prompt = new TFile("MCfiles_nocentralityweight/Cut_distribution_MC_FONLLweight_Prompt_pt7to40_rapidity0to1_cent30to100_sideband_dataptweight.root");
  TFile * input_mc_BtoD = new TFile("MCfiles_nocentralityweight/Cut_distribution_MC_FONLLweight_BtoD_pt7to40_rapidity0to1_cent30to100_sideband_dataptweight.root");

//   Drawvariable("y","rapidity",input_data,input_mc_prompt, input_mc_BtoD, -1, 1, 2, -1, 1, -1, 1);
//    Drawvariable("ffls3d","decay length sig",input_data,input_mc_prompt, input_mc_BtoD, 0.0, 40, 20, 0, 1000, 3.5, 1000);
//	Drawvariable("alpha", "#alpha", input_data,input_mc_prompt, input_mc_BtoD, 0.0,3.14, 10, 0, 3.14, 0.0, 0.05);
    Drawvariable("alpha", "#alpha", input_data,input_mc_prompt, input_mc_BtoD, 0.0,0.2, 5, 0, 3.14, 0.0, 0.05);
//	Drawvariable("fprob", "vertex prob", input_data,input_mc_prompt, input_mc_BtoD, 0.0, 1.0, 50, 0.0, 1.0, 0.15, 1.0);
//	Drawvariable("fchi2", "vertex #chi2", input_data,input_mc_prompt, input_mc_BtoD, 0.0, 10, 5, 0.0, 100, 0.0, 3.0);
  output->Close();
}
