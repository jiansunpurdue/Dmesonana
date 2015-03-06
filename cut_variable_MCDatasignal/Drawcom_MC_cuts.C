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

  h_mc_nocut->SetLineColor(kBlue+1);
  h_mc_nocut->SetFillStyle(1001);
  h_mc_nocut->SetFillColor(kBlue-9);
  h_mc_nocut->SetLineWidth(2);
  h_mc_nocut->SetStats(0);

  h_mc_cut->SetLineColor(2.0);
  h_mc_cut->SetFillStyle(3004);
  h_mc_cut->SetFillColor(2.0);
  h_mc_cut->SetLineWidth(2);
  h_mc_cut->SetStats(0);
//  h_mc_cut->SetLineColor(1.0);
//  h_mc_cut->SetMarkerColor(1.0);
//  h_mc_cut->SetMarkerStyle(20);
//  h_mc_cut->SetMarkerSize(0.8);
//  h_mc_cut->SetStats(0);

  h_mc_nocut->Draw("HISTe");
  h_mc_cut->Draw("HISTesame");
  
  TLegend *leg = new TLegend(0.35,0.65,0.6,0.85);
  leg->AddEntry(h_mc_nocut,"MC Truth Signal w/o cuts","f");
  leg->AddEntry(h_mc_cut,"MC Truth Signal w/ cuts","f");
  leg->SetBorderSize(0);
  leg->SetFillStyle(0);
  leg->Draw("same");

  c->SaveAs(Form("Cutvariablecompare/varcomparison_MC_%s_pt4p5_loose.pdf",varname.Data()));
  c->SaveAs(Form("Cutvariablecompare/varcomparison_MC_%s_pt4p5_loose.png",varname.Data()));
}

void Drawcom_MC_cuts()
{
	gStyle->SetOptTitle(0);
    TFile * input_mc_cut = new TFile("Cut_distribution_MC_Loose.root");
    TFile * input_mc = new TFile("Cut_distribution_MC_nocuts.root");

	Drawvariable("ffls3d","decay length sig",input_mc_cut,input_mc, 0, 40, 2);
//	Drawvariable("cosalpha", "cos#alpha", input_mc_cut,input_mc,-1.0,1.0, 2);
//	Drawvariable("fprob", "vertex probability", input_mc_cut,input_mc,0.,1.0, 4);
//	Drawvariable("fchi2", "vertex chi2", input_mc_cut,input_mc, 0., 20., 2);
}
