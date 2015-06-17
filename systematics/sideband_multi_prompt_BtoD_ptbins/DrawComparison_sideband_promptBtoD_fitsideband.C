double sideband_close = 0.10;//0.07; //0.06
double sideband_far = 0.15;//0.10;  //0.11
double width_signal = 0.03;
double mass_d0 = 1.864;

//double range_fit_low = mass_d0 - sideband_far;
//double range_fit_high = mass_d0 + sideband_far;

double range_fit_low = 1.7;
double range_fit_high = 2.05;

bool reject;

Double_t sidebandfit( Double_t * x, Double_t *par )
{
    Double_t xx = x[0];
    if( reject && xx > mass_d0 - sideband_close && xx < mass_d0 + sideband_close )
    {
        TF1::RejectPoint();
        return 0;
    }
//    return TMath::Exp(par[0]+par[1]*x);
//    return par[0]+par[1]*x;
    return  par[0]+par[1]*xx+par[2]*xx*xx;
}

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
  
  TF1 * fit = new TF1("fit",sidebandfit,range_fit_low,range_fit_high,3);
  reject = kTRUE;
  fit->SetParameter(0, 20000);
  fit->SetParameter(1, -1000);
  fit->SetParameter(2, 1000);
  h_mass->Fit(fit,"0","",range_fit_low,range_fit_high);

    reject = kFALSE;
    TF1 * fitleft = new TF1("fitleft",sidebandfit,range_fit_low, range_fit_high,3);
    fitleft->SetParameters(fit->GetParameters());
    fitleft->SetLineColor(8);
	fitleft->SetLineStyle(2);
    h_mass->GetListOfFunctions()->Add(fitleft);
    gROOT->GetListOfFunctions()->Remove(fitleft);
//    TF1 * fitright = new TF1("fitright",sidebandfit,mass_d0+sideband_close, range_fit_high,3);
//    fitright->SetParameters(fit->GetParameters());
//    fitright->SetLineColor(8);
//	fitright->SetLineColor(2);
//    h_mass->GetListOfFunctions()->Add(fitright);
//    gROOT->GetListOfFunctions()->Remove(fitright);
//

  double sidebandcounts = fitleft->Integral(mass_d0-sideband_far, mass_d0-sideband_close) + fitleft->Integral( mass_d0+sideband_close, mass_d0+sideband_far);
  double signalregioncounts = fitleft->Integral(mass_d0-width_signal, mass_d0+width_signal);
  
  h_mass->GetYaxis()->SetTitle("Counts");
  h_mass->GetXaxis()->SetTitle("m_{#piK} (GeV)");
  h_mass->GetXaxis()->SetRangeUser(1.70, 2.05);
  h_mass->SetLineColor(4.0);
  h_mass->SetMinimum();
  h_mass->Draw();

  h_band->Add(h_leftband, h_rightband, 1.0, 1.0);

  cout << "slideband counts fit: "  << sidebandcounts << "  h_band:" << h_band->Integral(0, -1) << "   signalregioncounts: " << signalregioncounts << endl;
  cout << "Integral test: " << fitleft->Integral(1.867, 1.872) << "   " << fitleft->Integral(1.867, 1.877) << endl;
//  h_band->Scale( width_signal/(sideband_far - sideband_close) );
  h_band->Scale( signalregioncounts/ ( 0.01 * h_band->Integral( 0, -1) ) );
  h_data->Add( h_signalregion, h_band, 1.0, -1.0);


  h_data->Rebin(rebin);
  h_mc_prompt->Rebin(rebin);
  h_mc_BtoD->Rebin(rebin);

  double datacounts = h_data->Integral(h_data->FindBin(min), h_data->FindBin(max) );
  double BtoDfraction = 0.05;
  
  h_mc_prompt->Scale( datacounts * ( 1.0 - BtoDfraction) / h_mc_prompt->Integral(h_mc_prompt->FindBin(min), h_mc_prompt->FindBin(max)) );
  h_mc_BtoD->Scale( datacounts * BtoDfraction / h_mc_BtoD->Integral(h_mc_BtoD->FindBin(min), h_mc_BtoD->FindBin(max)) );

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
  DataMCratio->GetYaxis()->SetTitleOffset(0.3);
  DataMCratio->GetYaxis()->SetTitleSize(0.08);
  DataMCratio->GetYaxis()->SetTitle("Data/MC");
  DataMCratio->Draw();

//  c->SaveAs(Form("plots/varcomparison_sideband_%s_pt7_tightcut.pdf",varname.Data()));
//  c->SaveAs(Form("plots/varcomparison_sideband_%s_pt7_tightcut.png",varname.Data()));
//  c_mass->SaveAs(Form("plots/varmass_sideband_%s_pt7_tightcut.pdf",varname.Data()));
//  c_mass->SaveAs(Form("plots/varmass_sideband_%s_pt7_tightcut.png",varname.Data()));
}

void DrawComparison_sideband_promptBtoD_fitsideband()
{
	gStyle->SetOptTitle(0);
  
      TFile * input_data = new TFile("rapiditycheck/Cut_distribution_Data_sideband_pt7to40_rapidity0to1.root");
	  TFile * input_mc_prompt = new TFile("rapiditycheck/Cut_distribution_MC_FONLLweight_Prompt_pt7to40_rapidity0to1_sideband_dataptweight.root");
	  TFile * input_mc_BtoD = new TFile("rapiditycheck/Cut_distribution_MC_FONLLweight_BtoD_pt7to40_rapidity0to1_sideband_dataptweight.root");

//    Drawvariable("y","rapidity",input_data,input_mc_prompt, input_mc_BtoD, -2, 2, 4, -2, 2);
//	Drawvariable("ffls3d","decay length sig",input_data,input_mc_prompt, input_mc_BtoD, 0.0, 40, 20, 0, 20);
	Drawvariable("alpha", "#alpha", input_data,input_mc_prompt, input_mc_BtoD, 0.0,0.2, 10, 0.0, 0.4);
//	Drawvariable("fprob", "vertex prob", input_data,input_mc_prompt, input_mc_BtoD, 0.0, 1.0, 50, 0., 1.0);
//	Drawvariable("fchi2", "vertex #chi2", input_data,input_mc_prompt, input_mc_BtoD, 0.0, 10, 5, 0., 1.0);
}
