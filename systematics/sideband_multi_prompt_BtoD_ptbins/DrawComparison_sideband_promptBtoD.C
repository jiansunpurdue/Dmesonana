double sideband_close = 0.10;//0.10;//0.07; //0.06
double sideband_far = 0.15;//0.15;//0.10;  //0.11
double width_signal = 0.03;
double mass_d0 = 1.864;

//double range_fit_low = mass_d0 - sideband_far;
//double range_fit_high = mass_d0 + sideband_far;

double range_fit_low = 1.7;
double range_fit_high = 2.05;

void Drawvariable(TString varname, TString vartitle, TFile * input_data, TFile * input_mc_prompt, TFile * input_mc_BtoD, float min, float max, int rebin, float test_begin, float test_over)
{

  gStyle->SetOptTitle(0);
  gStyle->SetOptStat(0);
  TH1::SetDefaultSumw2();
  gStyle->SetHistMinimumZero(kTRUE);
  TH1D* h_mc_prompt = (TH1D *) input_mc_prompt->Get(Form("%s_signal_mcmatched",varname.Data()));
  TH1D* h_mc_BtoD = (TH1D *) input_mc_BtoD->Get(Form("%s_signal_mcmatched",varname.Data()));

  TH1D* h_leftband = ( TH1D *) input_data->Get(Form("%s_leftband",varname.Data()));
  TH1D* h_rightband = ( TH1D *) input_data->Get(Form("%s_rightband",varname.Data()));
  TH1D* h_band = ( TH1D *) input_data->Get(Form("%s_band",varname.Data()));
  TH1D* h_signalregion = ( TH1D *) input_data->Get(Form("%s_signalregion",varname.Data()));
  TH1D* h_data = ( TH1D *) input_data->Get(Form("%s_signal_data",varname.Data()));
  TH1D* h_mass = ( TH1D *) input_data->Get(Form("mass_%s",varname.Data()));


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
  

  double sidebandcounts = fit_fun_bg->Integral(mass_d0-sideband_far, mass_d0-sideband_close) + fit_fun_bg->Integral( mass_d0+sideband_close, mass_d0+sideband_far);
  double signalregioncounts = fit_fun_bg->Integral(mass_d0-width_signal, mass_d0+width_signal);
  h_band->Add(h_leftband, h_rightband, 1.0, 1.0);

  cout << "slideband counts fit: "  << sidebandcounts << "  h_band:" << h_band->Integral(0, -1) << "   signalregioncounts: " << signalregioncounts << endl;
  cout << "Integral test: " << fit_fun_bg->Integral(1.867, 1.887) << "   " << fit_fun_bg->Integral(1.867, 1.877) << endl;
//  h_band->Scale( width_signal/(sideband_far - sideband_close) );
  h_band->Scale( signalregioncounts/ ( 0.01 * h_band->Integral( 0, -1) ) );
  h_data->Add( h_signalregion, h_band, 1.0, -1.0);


  h_data->Rebin(rebin);
  h_mc_prompt->Rebin(rebin);
  h_mc_BtoD->Rebin(rebin);
//
//  double datacounts = h_data->Integral(h_data->FindBin(min), h_data->FindBin(max) );
//  double BtoDfraction = 0.05;
//  
//  h_mc_prompt->Scale( datacounts * ( 1.0 - BtoDfraction) / h_mc_prompt->Integral(h_mc_prompt->FindBin(min), h_mc_prompt->FindBin(max)) );
//  h_mc_BtoD->Scale( datacounts * BtoDfraction / h_mc_BtoD->Integral(h_mc_BtoD->FindBin(min), h_mc_BtoD->FindBin(max)) );
//
  double datacounts = h_data->Integral(0, -1 );
  double BtoDfraction = 0.05;
  
  h_mc_prompt->Scale( datacounts * ( 1.0 - BtoDfraction) / h_mc_prompt->Integral(0, -1) );
  h_mc_BtoD->Scale( datacounts * BtoDfraction / h_mc_BtoD->Integral(0,-1) );

  TCanvas *c = new TCanvas(Form("c%s",varname),"",600,600);
  TPad *pad1 = new TPad("pad1","top pad",0.0,0.3,1.0,1.0);
  pad1->Draw();
  TPad *pad2 = new TPad("pad2","bottom pad",0.0,0.0,1.0,0.3);
  pad2->Draw();

  pad1->cd();

  if( varname == "ffls3d" )   gPad->SetLogy();

  THStack* hs_allD_mc = new THStack("hs_allD_mc","hs_allD_mc");

  h_mc_BtoD->SetLineColor(2.0);
  h_mc_BtoD->SetFillStyle(3345);
  h_mc_BtoD->SetFillColor(2.0);
  h_mc_BtoD->SetLineWidth(2);
  h_mc_BtoD->SetStats(0);
  hs_allD_mc->Add(h_mc_BtoD, "HISTe");

  h_mc_prompt->SetLineColor(4.0);
  h_mc_prompt->SetFillStyle(3345);
  h_mc_prompt->SetFillColor(4.0);
  h_mc_prompt->SetLineWidth(2);
  h_mc_prompt->SetStats(0);
  hs_allD_mc->Add(h_mc_prompt, "HISTe");

  h_data->SetLineColor(1.0);
  h_data->SetMarkerColor(1.0);
  h_data->SetMarkerStyle(20);
  h_data->SetMarkerSize(0.8);
  h_data->SetStats(0);

  if( varname != "ffls3d" )  hs_allD_mc->SetMinimum(0.);
  hs_allD_mc->Draw();
  h_data->DrawCopy("epsame");
  
  hs_allD_mc->GetXaxis()->SetTitle(Form("%s",vartitle.Data()));
  hs_allD_mc->GetXaxis()->SetRangeUser(min, max);
  cout << "min:::  "  << min << "   max:: " << max << endl;
//  hs_allD_mc->GetXaxis()->SetLimits(min, max);
  hs_allD_mc->GetYaxis()->SetTitle("Counts");
  hs_allD_mc->GetYaxis()->SetTitleOffset(1.2);
  hs_allD_mc->SetMaximum(h_data->GetMaximum()*1.4);

  TLegend *leg = new TLegend(0.55,0.7,0.85,0.85);
  leg->AddEntry(h_data,"Data Signal","PL");
  leg->AddEntry(h_mc_prompt,"MC Truth Prompt D^{0} Signal","f");
  leg->AddEntry(h_mc_BtoD,"MC Truth B Feed-down D^{0} Signal","f");
  leg->SetBorderSize(0);
  leg->SetFillStyle(0);
  leg->Draw();

  pad2->cd();
  TH1D * DataMCratio = ( TH1D *) (hs_allD_mc->GetStack()->Last())->Clone("DataMCratio");
  DataMCratio->Divide(h_data, DataMCratio, 1.0, 1.0);
  DataMCratio->GetXaxis()->SetRangeUser(min, max);
  DataMCratio->GetYaxis()->SetRangeUser(0.0, 2.0);
  DataMCratio->GetYaxis()->SetTitleOffset(0.6);
  DataMCratio->GetYaxis()->SetTitleSize(0.08);
  DataMCratio->GetYaxis()->SetLabelSize(0.08);
  DataMCratio->GetYaxis()->SetTitle("Data/MC");
  DataMCratio->Draw();

//  c->SaveAs(Form("plots_pt7to40/varcomparison_datasideband_%s_pt7to40_tightcut.pdf",varname.Data()));
//  c->SaveAs(Form("plots_pt7to40/varcomparison_datasideband_%s_pt7to40_tightcut.png",varname.Data()));
//  c_mass->SaveAs(Form("plots_pt7to40/varmass_datasideband_%s_pt7to40_tightcut.pdf",varname.Data()));
//  c_mass->SaveAs(Form("plots_pt7to40/varmass_datasideband_%s_pt7to40_tightcut.png",varname.Data()));
}

void DrawComparison_sideband_promptBtoD()
{
	gStyle->SetOptTitle(0);
  
    TFile * input_data = new TFile("filescent-0to100/Cut_distribution_Data_sideband_pt7to40_rapidity0to1_cent-0to100.root");
    TFile * input_mc_prompt = new TFile("filescent-0to100/Cut_distribution_MC_FONLLweight_Prompt_pt7to40_rapidity0to1_cent-0to100_sideband_dataptweight.root");
    TFile * input_mc_BtoD = new TFile("filescent-0to100/Cut_distribution_MC_FONLLweight_BtoD_pt7to40_rapidity0to1_cent-0to100_sideband_dataptweight.root");

    Drawvariable("y","rapidity",input_data,input_mc_prompt, input_mc_BtoD, -1, 1, 1, -1, 1);
//	Drawvariable("ffls3d","decay length sig",input_data,input_mc_prompt, input_mc_BtoD, 0.0, 40, 20, 0, 20);
//	Drawvariable("alpha", "#alpha", input_data,input_mc_prompt, input_mc_BtoD, 0.0, 0.5, 10, 0.0, 0.4);
//	Drawvariable("fprob", "vertex prob", input_data,input_mc_prompt, input_mc_BtoD, 0.0, 1.0, 50, 0., 1.0);
//	Drawvariable("fchi2", "vertex #chi2", input_data,input_mc_prompt, input_mc_BtoD, 0.0, 10, 5, 0., 1.0);
}
