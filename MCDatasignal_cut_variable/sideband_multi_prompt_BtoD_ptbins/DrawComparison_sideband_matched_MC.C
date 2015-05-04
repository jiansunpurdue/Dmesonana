#include "sideband.h"
//double range_fit_low = mass_d0 - sideband_far;
//double range_fit_high = mass_d0 + sideband_far;

double range_fit_low = 1.7;
double range_fit_high = 2.05;

void Drawvariable(TString varname, TString vartitle, TFile * input_mc, float min, float max, int rebin, TFile * outputfile)
{

  gStyle->SetOptTitle(0);
  gStyle->SetOptStat(0);
  TH1::SetDefaultSumw2();
  gStyle->SetHistMinimumZero(kTRUE);
  TH1D* h_mc_matched = (TH1D *) input_mc->Get(Form("%s_signal_mcmatched",varname.Data()));

  TH1D* h_leftband = ( TH1D *) input_mc->Get(Form("%s_leftband",varname.Data()));
  TH1D* h_rightband = ( TH1D *) input_mc->Get(Form("%s_rightband",varname.Data()));
  TH1D* h_band = ( TH1D *) input_mc->Get(Form("%s_band",varname.Data()));
  TH1D* h_signalregion = ( TH1D *) input_mc->Get(Form("%s_signalregion",varname.Data()));
  TH1D* h_data = ( TH1D *) input_mc->Get(Form("%s_signal_data",varname.Data()));
  TH1D* h_mass = ( TH1D *) input_mc->Get(Form("mass_%s",varname.Data()));


  TCanvas * c_mass = new TCanvas(Form("c_mass_%s",varname),"");

  TF1* fit_fun = new TF1("fit_fun", "gausn(0) + pol2(3)", range_fit_low, range_fit_high);
  float histomax = h_mass->GetMaximum();
  h_mass->SetMaximum(1.1 * histomax);

  float p0 = 1000, p1 = 1.87, p2 = 0.02;
  float p0_L = 0, p1_L = 1.84, p2_L = 0;
  float p0_H = 2*histomax, p1_H = 1.9, p2_H = 0.05;
  fit_fun->SetParameter(0, p0);
  fit_fun->SetParameter(1, p1);
  fit_fun->SetParameter(2, p2);

  //.. fit constraint ..
  fit_fun->SetParLimits(0, p0_L, p0_H);
  fit_fun->SetParLimits(1, p1_L, p1_H);
  fit_fun->SetParLimits(2, p2_L, p2_H);
  fit_fun->SetParameter(3, 2000.);
  fit_fun->SetParameter(4, -1000);
  fit_fun->SetParameter(5, 1000);
  
  for ( int fittingtimes = 0; fittingtimes < 3; fittingtimes++ )
  {
	  h_mass->Fit(fit_fun,"","", range_fit_low, range_fit_high);
	  fit_fun->SetParameter(0, fit_fun->GetParameter(0));
	  fit_fun->SetParameter(1, fit_fun->GetParameter(1));
	  fit_fun->SetParameter(2, fit_fun->GetParameter(2));
	  fit_fun->SetParameter(3, fit_fun->GetParameter(3));
	  fit_fun->SetParameter(4, fit_fun->GetParameter(4));
	  fit_fun->SetParameter(5, fit_fun->GetParameter(5));
  }

  
  h_mass->GetYaxis()->SetTitle("Counts");
  h_mass->GetXaxis()->SetTitle("m_{#piK} (GeV)");
  h_mass->GetXaxis()->SetRangeUser(1.70, 2.05);
  h_mass->SetLineColor(4.0);
  h_mass->SetMinimum();
  h_mass->Draw();
  
  TF1* fit_fun_bg = (TF1*)fit_fun->Clone("fit_fun_bg");
  fit_fun_bg->SetParameter(0, 0);
  fit_fun_bg->SetParameter(1, 0);
  fit_fun_bg->SetParameter(2, 0);
  fit_fun_bg->SetLineColor(8);
  fit_fun_bg->SetLineStyle(2);
  fit_fun_bg->Draw("same");
  
//  TF1* fit_fun_bg = new TF1("fit_fun_bg", "pol2(3)", range_fit_low, range_fit_high, 3);
//  fit_fun_bg->SetParameter(0, fit_fun->GetParameter(3));
//  fit_fun_bg->SetParameter(1, fit_fun->GetParameter(4));
//  fit_fun_bg->SetParameter(2, fit_fun->GetParameter(5));
//  fit_fun_bg->SetLineColor(8);
//  fit_fun_bg->SetLineStyle(2);
//  fit_fun_bg->Draw("same");

  double sidebandcounts = fit_fun_bg->Integral(mass_d0-sideband_far, mass_d0-sideband_close) + fit_fun_bg->Integral( mass_d0+sideband_close, mass_d0+sideband_far);
  double signalregioncounts = fit_fun_bg->Integral(mass_d0-width_signal, mass_d0+width_signal);
  h_band->Add(h_leftband, h_rightband, 1.0, 1.0);

  cout << "slideband counts fit: "  << sidebandcounts << "  h_band:" << h_band->Integral(0, -1) << "   signalregioncounts: " << signalregioncounts << endl;
  cout << "Integral test: " << fit_fun_bg->Integral(1.867, 1.868) << "   " << fit_fun_bg->Integral(1.867, 1.869) << endl;
//  h_band->Scale( width_signal/(sideband_far - sideband_close) );
  h_band->Scale( sidebandcounts / ( 0.01 * h_band->Integral(0, -1)) );
  h_band->Scale( signalregioncounts / sidebandcounts );
  h_data->Add( h_signalregion, h_band, 1.0, -1.0);


  h_data->Rebin(rebin);
  h_mc_matched->Rebin(rebin);

  double datacounts = h_data->Integral(h_data->FindBin(min), h_data->FindBin(max) );
  
  h_mc_matched->Scale( datacounts / h_mc_matched->Integral(h_mc_matched->FindBin(min), h_mc_matched->FindBin(max)) );

  TCanvas *c = new TCanvas(Form("c%s",varname),"",600,600);
  TPad *pad1 = new TPad("pad1","top pad",0.0,0.3,1.0,1.0);
  pad1->Draw();
  TPad *pad2 = new TPad("pad2","bottom pad",0.0,0.0,1.0,0.3);
  pad2->Draw();

  pad1->cd();

  if( varname == "ffls3d" )   gPad->SetLogy();

  h_mc_matched->SetLineColor(4.0);
  h_mc_matched->SetFillStyle(3345);
  h_mc_matched->SetFillColor(4.0);
  h_mc_matched->SetLineWidth(2);
  h_mc_matched->SetStats(0);

  h_data->SetLineColor(1.0);
  h_data->SetMarkerColor(1.0);
  h_data->SetMarkerStyle(20);
  h_data->SetMarkerSize(0.8);
  h_data->SetStats(0);

  h_mc_matched->GetXaxis()->SetTitle(Form("%s",vartitle.Data()));
  h_mc_matched->GetXaxis()->SetRangeUser(min, max);
  cout << "min:::  "  << min << "   max:: " << max << endl;
//  h_mc_matched->GetXaxis()->SetLimits(min, max);
  h_mc_matched->GetYaxis()->SetTitle("Counts");
  h_mc_matched->GetYaxis()->SetTitleOffset(1.2);
  h_mc_matched->SetMaximum(h_data->GetMaximum()*1.4);

  if( varname != "ffls3d" )  h_mc_matched->SetMinimum(0.);
  h_mc_matched->Draw("HISTe");
  h_data->DrawCopy("epsame");
  
  TLegend *leg = new TLegend(0.55,0.7,0.85,0.85);
  leg->AddEntry(h_data,"MC D^{0} Signal with Sideband","PL");
  leg->AddEntry(h_mc_matched,"MC Truth D^{0} Signal","f");
  leg->SetBorderSize(0);
  leg->SetFillStyle(0);
  leg->Draw();

  pad2->cd();

  TH1D * DataMCratio = ( TH1D *) h_data->Clone("hhDataMCratio");
  DataMCratio->Divide(h_mc_matched);
  DataMCratio->GetXaxis()->SetRangeUser(min, max);
  DataMCratio->GetYaxis()->SetRangeUser(0.0, 2.0);
  DataMCratio->GetYaxis()->SetTitleOffset(0.3);
  DataMCratio->GetYaxis()->SetTitleSize(0.08);
  DataMCratio->GetYaxis()->SetTitle("MC Sideband/MC Truth");
  DataMCratio->DrawCopy();

//  c->SaveAs(Form("plots_pt7to40_nodouble/var_mctruth_sideband_promptD_%s_pt7to40_tightcut_nodouble.pdf",varname.Data()));
//  c->SaveAs(Form("plots_pt7to40_nodouble/var_mctruth_sideband_promptD_%s_pt7to40_tightcut_nodouble.png",varname.Data()));

  outputfile->cd();
  DataMCratio->Write();
  h_data->Write();
  h_mc_matched->Write();

}

void DrawComparison_sideband_matched_MC()
{
	gStyle->SetOptTitle(0);
  
    TFile * input_mc = new TFile("filespt7to40/Cut_distribution_MC_FONLLweight_Prompt_pt7to40_sideband_dataptweight_nodouble.root");
//    TFile * input_mc = new TFile("filespt3p5to40/Cut_distribution_MC_FONLLweight_Prompt_pt4to40_sideband_dataptweight_othercut_nodouble.root");

	TFile * outputfile = new TFile("Sideband_FONLLweight_MC_sideband_prompt_pt4_nodouble.root","RECREATE");

//    Drawvariable("y","rapidity",input_mc, -2, 2, 4, outputfile);
	Drawvariable("ffls3d","decay length sig",input_mc, 0.0, 40, 20, outputfile);
//	Drawvariable("alpha", "#alpha", input_mc, 0.0,3.14, 10 , outputfile);
//	Drawvariable("fprob", "vertex prob", input_mc, 0.0, 1.0, 50, outputfile);
//	Drawvariable("fchi2", "vertex #chi2", input_mc,input_mc, input_mc_BtoD, 0.0, 10, 5, 0., 1.0);
    outputfile->Close();
}
