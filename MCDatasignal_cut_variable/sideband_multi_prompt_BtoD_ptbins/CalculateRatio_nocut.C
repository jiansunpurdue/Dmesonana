double sideband_close = 0.06;//0.10;//0.07; //0.06
double sideband_far = 0.11;//0.15;//0.10;  //0.11
double width_signal = 0.03;
double mass_d0 = 1.864;

//double range_fit_low = mass_d0 - sideband_far;
//double range_fit_high = mass_d0 + sideband_far;

double range_fit_low = 1.7;
double range_fit_high = 2.05;

void Drawvariable(TString varname, TString vartitle, TFile * input_data, TFile * input_mc_prompt, TFile * input_mc_BtoD, float range1, float range2, float cut1, float cut2)
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

  int bin1 = h_data->FindBin(range1);
  int bin2 = h_data->FindBin(range2);

  int cutbin1 = h_data->FindBin(cut1);
  int cutbin2 = h_data->FindBin(cut2);
  
  double BtoDfraction = 0.05;

  double datacounts = h_data->Integral(0, -1);
  h_mc_prompt->Scale( datacounts * ( 1.0 - BtoDfraction) / h_mc_prompt->Integral(0, -1) );
  h_mc_BtoD->Scale( datacounts * BtoDfraction / h_mc_BtoD->Integral(0, -1) );

//  double datacounts = h_data->Integral(bin1, bin2);
//  h_mc_prompt->Scale( datacounts * ( 1.0 - BtoDfraction) / h_mc_prompt->Integral(bin1, bin2) );
//  h_mc_BtoD->Scale( datacounts * BtoDfraction / h_mc_BtoD->Integral(bin1, bin2) );
  
  TH1D * h_mc_total = ( TH1D *) h_mc_prompt->Clone("h_mc_total");
  h_mc_total->Add( h_mc_prompt, h_mc_BtoD, 1.0, 1.0 );

  double error = -9999.;

  TH1D* counts_data_nocut = new TH1D("counts_data_nocut", "counts_data_nocut", 1, 0, 1); 
  counts_data_nocut->SetBinContent(1, h_data->IntegralAndError(bin1, bin2, error));
  counts_data_nocut->SetBinError(1, error);

  cout << "data  nocut counts: " << h_data->IntegralAndError(bin1, bin2, error) << "  error: " << error << endl;

  TH1D* counts_data_cut = new TH1D("counts_data_cut", "counts_data_cut", 1, 0, 1); 
  counts_data_cut->SetBinContent(1, h_data->IntegralAndError(cutbin1, cutbin2, error));
  counts_data_cut->SetBinError(1, error);

  cout << "data cut counts: " << h_data->IntegralAndError(cutbin1, cutbin2, error) << "   error: " << error << endl;

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

void CalculateRatio_nocut()
{
	gStyle->SetOptTitle(0);
    TFile * input_data = new TFile("sideband0p060p11/Cut_distribution_Data_sideband_pt7.0_tightcut.root");
    TFile * input_mc_prompt = new TFile("sideband0p060p11/Cut_distribution_MC_FONLLweight_Prompt_pt7.0_sideband.root");
	TFile * input_mc_BtoD = new TFile("sideband0p060p11/Cut_distribution_MC_FONLLweight_BtoD_pt7.0_sideband.root");

	Drawvariable("ffls3d","decay length sig",input_data,input_mc_prompt, input_mc_BtoD, 0.0, 1000, 3.5, 1000);
//	Drawvariable("alpha", "#alpha", input_data,input_mc_prompt, input_mc_BtoD, 0, 3.14, 0.0, 0.05);
//	Drawvariable("fprob", "vertex prob", input_data,input_mc_prompt, input_mc_BtoD, 0.0, 1.0, 0.05, 1.0);
}
