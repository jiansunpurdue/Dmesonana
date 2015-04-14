void Drawvariable(TString varname, TString vartitle, TFile * input_mc_cut, TFile * input_mc, float min, float max, int rebin)
{
  TH1D* h_mc_cut = ( TH1D *) input_mc_cut->Get(Form("%s_signal_mcmatched",varname.Data()));
  TH1D* h_mc_nocut = (TH1D *) input_mc->Get(Form("%s_signal_mcmatched",varname.Data()));

  h_mc_cut->Rebin(rebin);
  h_mc_nocut->Rebin(rebin);

  h_mc_cut->Scale(1./h_mc_cut->Integral(0,-1));
  h_mc_nocut->Scale(1./h_mc_nocut->Integral(0,-1)); 


  h_mc_nocut->SetXTitle(Form("%s",vartitle.Data()));
  h_mc_nocut->GetXaxis()->SetRangeUser(min, max);
  h_mc_nocut->SetYTitle("#Probability");
  h_mc_nocut->SetTitleOffset(1.5,"Y");
  if(h_mc_nocut->GetMaximum()>h_mc_cut->GetMaximum()) h_mc_nocut->SetMaximum(h_mc_nocut->GetMaximum()*1.2);
  else h_mc_nocut->SetMaximum(h_mc_cut->GetMaximum()*1.2);

  TCanvas *c = new TCanvas(Form("c%s",varname),"",600,600);

  TPad *pad1 = new TPad("pad1","top pad",0.0,0.3,1.0,1.0);
  pad1->Draw();
  TPad *pad2 = new TPad("pad2","bottom pad",0.0,0.0,1.0,0.3);
  pad2->Draw();

  pad1->cd();
  if( varname == "ffls3d" )   gPad->SetLogy();

  h_mc_nocut->SetLineColor(kBlue+1);
  h_mc_nocut->SetFillStyle(3345);
  h_mc_nocut->SetFillColor(4.0);
  h_mc_nocut->SetLineWidth(2);
  h_mc_nocut->SetStats(0);

//  h_mc_cut->SetLineColor(2.0);
//  h_mc_cut->SetFillStyle(3004);
//  h_mc_cut->SetFillColor(2.0);
//  h_mc_cut->SetLineWidth(2);
//  h_mc_cut->SetStats(0);
  h_mc_cut->SetLineColor(1.0);
  h_mc_cut->SetMarkerColor(1.0);
  h_mc_cut->SetMarkerStyle(20);
  h_mc_cut->SetMarkerSize(0.8);
  h_mc_cut->SetStats(0);

  h_mc_nocut->Draw("HISTe");
  h_mc_cut->Draw("same");
  
  TLegend *leg = new TLegend(0.55,0.65,0.85,0.85);
  leg->AddEntry(h_mc_nocut,"MC Truth Signal w/o RAA Rewight","f");
  leg->AddEntry(h_mc_cut,"MC Truth Signal w/ RAA Rewight");
  leg->SetBorderSize(0);
  leg->SetFillStyle(0);
  leg->Draw("same");


  pad2->cd();
  TH1D * ratio_mc_weightpt_no = ( TH1D *) h_mc_cut->Clone("ratio_mc_weightpt_no");
  ratio_mc_weightpt_no->Divide(h_mc_cut, h_mc_nocut, 1.0, 1.0, "B");
  ratio_mc_weightpt_no->GetXaxis()->SetRangeUser(min, max);
  ratio_mc_weightpt_no->GetYaxis()->SetRangeUser(0.8, 1.2);
  ratio_mc_weightpt_no->GetYaxis()->SetTitleOffset(0.3);
  ratio_mc_weightpt_no->GetYaxis()->SetTitleSize(0.08);
  ratio_mc_weightpt_no->GetYaxis()->SetTitle("w/ / w/o");
  ratio_mc_weightpt_no->Draw();

  c->SaveAs(Form("mcreweightpt/varcomparison_MC_%s_pt3p5to40_tightcut.pdf",varname.Data()));
  c->SaveAs(Form("mcreweightpt/varcomparison_MC_%s_pt3p5to40_tightcut.png",varname.Data()));
}

void Drawcom_MC_cuts()
{
	gStyle->SetOptTitle(0);
    TFile * input_mc_cut = new TFile("filespt3p5to40/Cut_distribution_MC_FONLLweight_Prompt_pt4to40_sideband.root");
    TFile * input_mc = new TFile("filespt3p5to40/Cut_distribution_MC_FONLLweight_Prompt_pt4to40_sideband_weightpt.root");

//    Drawvariable("y","rapidity",input_mc_cut,input_mc, -2, 2, 4);
//	Drawvariable("ffls3d","decay length sig",input_mc_cut,input_mc, 0, 40, 10);
//	Drawvariable("alpha", "#alpha", input_mc_cut,input_mc,0.0,0.2, 2);
//	Drawvariable("fprob", "vertex probability", input_mc_cut,input_mc,0.,1.0, 50);
	Drawvariable("fchi2", "vertex chi2", input_mc_cut,input_mc, 0., 10., 5);
}
