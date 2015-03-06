void Drawvariable(TString varname, TString vartitle, TFile * input_data, TFile * input_mc, float min, float max, int rebin, float test_begin, float test_over)
{
  TH1D* h_data = ( TH1D *) input_data->Get(Form("%s_signal_data",varname.Data()));
  TH1D* h_mc = (TH1D *) input_mc->Get(Form("%s_signal_mcmatched",varname.Data()));

  h_data->Rebin(rebin);
  h_mc->Rebin(rebin);

  if( varname != "cosalpha" )
      h_mc->Scale(h_data->Integral(0,-1)/h_mc->Integral(0,-1)); 
  else
	  h_mc->Scale(h_data->Integral(h_data->FindBin(0.8), -1)/h_mc->Integral(h_mc->FindBin(0.8), -1));

  int bin_begin = h_data->FindBin(test_begin);
  int bin_over = h_data->FindBin(test_over);


  cout << "bin_begin: " << bin_begin << "   bin_over: " << bin_over << endl;
  cout << "BinLowedge: " << h_data->GetBinLowEdge(bin_begin) << "   BinLowedge: " << h_data->GetBinLowEdge(bin_over) << endl;

  TH1D* h_data_test = new TH1D("h_data_test","h_data_test", bin_over - bin_begin, h_data->GetBinLowEdge(bin_begin), h_data->GetBinLowEdge(bin_over) );
  TH1D* h_mc_test = new TH1D("h_mc_test","h_mc_test", bin_over - bin_begin, h_mc->GetBinLowEdge(bin_begin), h_mc->GetBinLowEdge(bin_over) );

  for( int i = bin_begin, ibin = 1 ; i < bin_over; i++, ibin++ )
  {
	  h_data_test->SetBinContent( ibin, h_data->GetBinContent(i) );
	  h_data_test->SetBinError( ibin, h_data->GetBinError(i) );
	  h_mc_test->SetBinContent( ibin, h_mc->GetBinContent(i) );
	  h_mc_test->SetBinError( ibin, h_mc->GetBinError(i) );
  }

  TCanvas * test = new TCanvas("test","test");
  h_data_test->Draw();
  h_mc_test->Draw("same");

  double res[100];
  double p = h_data_test->Chi2Test(h_mc_test,"UW P",res);
  cout << "p value: " << p << endl;

  h_mc->SetXTitle(Form("%s",vartitle.Data()));
  h_mc->GetXaxis()->SetRangeUser(min, max);
  h_mc->SetYTitle("#Probability");
  h_mc->SetTitleOffset(1.5,"Y");
  if(h_mc->GetMaximum()>h_data->GetMaximum()) h_mc->SetMaximum(h_mc->GetMaximum()*1.2);
  else h_mc->SetMaximum(h_data->GetMaximum()*1.2);

  TCanvas *c = new TCanvas(Form("c%s",varname),"",600,600);

  h_mc->SetLineColor(4.0);
  h_mc->SetFillStyle(3345);
  h_mc->SetFillColor(4.0);
  h_mc->SetLineWidth(2);
  h_mc->SetStats(0);

  h_data->SetLineColor(1.0);
  h_data->SetMarkerColor(1.0);
  h_data->SetMarkerStyle(20);
  h_data->SetMarkerSize(0.8);
  h_data->SetStats(0);

  h_mc->Draw("HISTe");
  h_data->Draw("epsame");
  
  TLegend *leg = new TLegend(0.35,0.65,0.6,0.85);
  leg->AddEntry(h_mc,"MC Truth Signal","f");
  leg->AddEntry(h_data,"Data Signal","PL");
  leg->SetBorderSize(0);
  leg->SetFillStyle(0);
  leg->Draw("same");

  c->SaveAs(Form("Chi2test/varcomparison_%s_scale0p1to0p15.pdf",varname.Data()));
  c->SaveAs(Form("Chi2test/varcomparison_%s_scale0p1to0p15.png",varname.Data()));
}

void DrawComparison_chi2test()
{
	gStyle->SetOptTitle(0);
    TFile * input_data = new TFile("Cut_distribution_Data_scale0p1to0p15.root");
    TFile * input_mc = new TFile("Cut_distribution_MC_oneexcept.root");

	Drawvariable("ffls3d","decay length sig",input_data,input_mc,0,40,1, 0,20);
	Drawvariable("cosalpha", "cos#alpha", input_data,input_mc,0.80,1.0, 1, 0.90, 1.0);
	Drawvariable("fprob", "vertex probability", input_data,input_mc,0.,1.0, 1, 0, 1.0);
	Drawvariable("fchi2", "vertex chi2", input_data,input_mc, 0., 20., 1, 0, 6);
}
