void Drawvariable(TString varname, TString vartitle, TFile * input_mc_fonll, TFile * input_mc_data, float min, float max, int rebin)
{
  TH1D* h_mc_fonll = ( TH1D *) input_mc_fonll->Get(Form("%s_signal_mcmatched",varname.Data()));
  TH1D* h_mc_data = (TH1D *) input_mc_data->Get(Form("%s_signal_mcmatched",varname.Data()));

  h_mc_fonll->Rebin(rebin);
  h_mc_data->Rebin(rebin);

  h_mc_fonll->Scale(1./h_mc_fonll->Integral(0,-1));
  h_mc_data->Scale(1./h_mc_data->Integral(0,-1)); 

  TCanvas *c = new TCanvas(Form("c%s",varname),"",600,600);

  TPad *pad1 = new TPad("pad1","top pad",0.0,0.3,1.0,1.0);
  pad1->Draw();
  TPad *pad2 = new TPad("pad2","bottom pad",0.0,0.0,1.0,0.3);
  pad2->Draw();

  pad1->cd();
  if( varname == "ffls3d" )   gPad->SetLogy();

  h_mc_fonll->SetXTitle(Form("%s",vartitle.Data()));
  h_mc_fonll->GetXaxis()->SetRangeUser(min, max);
  h_mc_fonll->SetYTitle("#Probability");
  h_mc_fonll->SetTitleOffset(1.5,"Y");
  if(h_mc_fonll->GetMaximum()>h_mc_data->GetMaximum()) h_mc_fonll->SetMaximum(h_mc_fonll->GetMaximum()*1.2);
  else h_mc_fonll->SetMaximum(h_mc_data->GetMaximum()*1.2);

  h_mc_fonll->SetLineColor(kBlue+1);
  h_mc_fonll->SetFillStyle(3345);
  h_mc_fonll->SetFillColor(4.0);
  h_mc_fonll->SetLineWidth(2);
  h_mc_fonll->SetStats(0);
  h_mc_fonll->Draw("HISTe");

//  h_mc_fonll->SetLineColor(2.0);
//  h_mc_fonll->SetFillStyle(3004);
//  h_mc_fonll->SetFillColor(2.0);
//  h_mc_fonll->SetLineWidth(2);
//  h_mc_fonll->SetStats(0);
  h_mc_data->SetLineColor(1.0);
  h_mc_data->SetMarkerColor(1.0);
  h_mc_data->SetMarkerStyle(20);
  h_mc_data->SetMarkerSize(0.8);
  h_mc_data->SetStats(0);
  h_mc_data->Draw("same");
  
  TLegend *leg = new TLegend(0.45,0.65,0.85,0.85);
  leg->AddEntry(h_mc_data,"Weighted to Data Spectrum");
  leg->AddEntry(h_mc_fonll,"Weighted to FONLL Spectrum", "f");
  leg->SetBorderSize(0);
  leg->SetFillStyle(0);
  leg->Draw("same");


  pad2->cd();
  TH1D * ratio_mc_weightpt_no = ( TH1D *) h_mc_fonll->Clone("ratio_mc_weightpt_no");
  ratio_mc_weightpt_no->Divide(h_mc_data, h_mc_fonll, 1.0, 1.0, "B");
  ratio_mc_weightpt_no->GetXaxis()->SetRangeUser(min, max);
  ratio_mc_weightpt_no->GetYaxis()->SetRangeUser(0.8, 1.2);
  ratio_mc_weightpt_no->GetYaxis()->SetTitleOffset(0.3);
  ratio_mc_weightpt_no->GetYaxis()->SetTitleSize(0.08);
  ratio_mc_weightpt_no->GetYaxis()->SetTitle("Ratio");
  ratio_mc_weightpt_no->Draw();

  c->SaveAs(Form("mcreweightpt/varcomparison_MC_%s_pt3p5to40_data_fonll.pdf",varname.Data()));
  c->SaveAs(Form("mcreweightpt/varcomparison_MC_%s_pt3p5to40_data_fonll.png",varname.Data()));
}

void Drawcom_MC_cuts()
{
	gStyle->SetOptTitle(0);
    TFile * input_mc_fonll = new TFile("filespt3p5to40/Cut_distribution_MC_FONLLweight_Prompt_pt4to40_sideband_othercut.root");
    TFile * input_mc_data = new TFile("filespt3p5to40/Cut_distribution_MC_FONLLweight_Prompt_pt4to40_sideband_dataptweight_othercut.root");
//
//    TFile * input_mc_fonll = new TFile("filespt7to40/Cut_distribution_MC_FONLLweight_Prompt_pt7to40_sideband.root");
//    TFile * input_mc_data = new TFile("filespt7to40/Cut_distribution_MC_FONLLweight_Prompt_pt7to40_sideband_dataptweight.root");

    Drawvariable("y","rapidity",input_mc_fonll,input_mc_data, -2, 2, 4);
//	Drawvariable("ffls3d","decay length sig",input_mc_fonll,input_mc_data, 0, 40, 10);
//	Drawvariable("alpha", "#alpha", input_mc_fonll,input_mc_data,0.0,0.2, 2);
//	Drawvariable("fprob", "vertex probability", input_mc_fonll,input_mc_data,0.,1.0, 50);
//	Drawvariable("fchi2", "vertex chi2", input_mc_fonll,input_mc_data, 0., 10., 5);
}
