#include "TH1F.h"
#include <cmath>
#include "TGraphAsymmErrors.h"
#include "TLegend.h"
#include "TCanvas.h"
#include <fstream>
#include <iostream>

#define BIN_NUM 392 //pPb_pt:220,pPb_y:40,pp_pt:222,pp_y:45
#define HMIN 2      //pPb_pt:5,pPb_y:-2,pp_pt:9,pp_y:0
#define HMAX 100     //pPb_pt:55,pPb_y:2,pp_pt:120,pp_y:2.25

#define MAXGENDMESON 100

int weight_cal_pythiarawtofonll_Bfeeddown()
{

  gROOT->SetStyle("Plain");
  gStyle->SetOptTitle(0);
  gStyle->SetOptStat(0);
  TH1::SetDefaultSumw2();

  
  TFile * input_BFONLL = new TFile("./RAA_RCP/BtoD_cent0to100.root");
  TH1D * BtoD_central = (TH1D *) input_BFONLL->Get("hDFromBPt");
  BtoD_central->Scale(0.5);
  double bin_edge[BIN_NUM+1];

  for( int i = 0; i < BIN_NUM+1; i++ )
  {
      bin_edge[i] = 2.0 + 0.25 * i;
  }

  TH1D * hpt = (TH1D *) BtoD_central->Rebin( BIN_NUM, "hpt", bin_edge);
  

  TFile * input_PbPb_MC = new TFile("rootfiles/Dmesonana_hiforest_official_PbPbD0tokaonpion_Pt0153050_2760GeV_0323_all_v1.root");
  TTree * gendmesontree = ( TTree * ) input_PbPb_MC->Get("gendmesontree");
  
  float pthat;
  double weight_pthat;
  int ngend;
  float dpt[MAXGENDMESON];
  float deta[MAXGENDMESON];
  float dy[MAXGENDMESON];
  float pt_Bmom[MAXGENDMESON];
  gendmesontree->SetBranchAddress("pthat", &pthat);
  gendmesontree->SetBranchAddress("weight_pthat", &weight_pthat);
  gendmesontree->SetBranchAddress("ngend", &ngend);
  gendmesontree->SetBranchAddress("dpt", dpt);
  gendmesontree->SetBranchAddress("deta", deta);
  gendmesontree->SetBranchAddress("dy", dy);
  gendmesontree->SetBranchAddress("pt_Bmom", pt_Bmom);


  TH1D * D0_pythiaspectrum = new TH1D("D0_pythiaspectrum","D0_pythiaspectrum",BIN_NUM,HMIN,HMAX);
  TH1D * D0_pythiaspectrum_cuts = new TH1D("D0_pythiaspectrum_cuts","D0_pythiaspectrum_cuts",BIN_NUM,HMIN,HMAX);

  TH1D * D0_pythiaspectrum_raw = new TH1D("D0_pythiaspectrum_raw","D0_pythiaspectrum_raw",BIN_NUM,HMIN,HMAX);
  
  for( int ievent = 0; ievent < gendmesontree->GetEntries(); ievent++ )
  {
	  gendmesontree->GetEntry(ievent);
	  for( int igend = 0; igend < ngend; igend++ )
	  {
          if( pt_Bmom[igend] < 0 )   continue;   //just take B feed down D0
		  if( TMath::Abs( dy[igend] ) > 2.0 ) continue;
		  D0_pythiaspectrum_raw->Fill(dpt[igend]);

		  if( dpt[igend] > 2.0 * pthat )   continue;

		  D0_pythiaspectrum->Fill(dpt[igend], weight_pthat);

		  if( pthat < 15 && dpt[igend] > 16.0 ) continue;
//		  if( pthat > 15.0 && pthat < 30.0 && dpt[igend] > 20.0 ) continue;
		  D0_pythiaspectrum_cuts->Fill(dpt[igend], weight_pthat);
	  }
  }

  for (int i=0;i<D0_pythiaspectrum->GetNbinsX();i++)
  {
	 D0_pythiaspectrum->SetBinContent(i+1,D0_pythiaspectrum->GetBinContent(i+1) * 1e9 / ( 2 * D0_pythiaspectrum->GetBinWidth(i+1) ));
	 D0_pythiaspectrum->SetBinError(i+1,D0_pythiaspectrum->GetBinError(i+1) * 1e9 / ( 2 * D0_pythiaspectrum->GetBinWidth(i+1) ));

	 D0_pythiaspectrum_cuts->SetBinContent(i+1,D0_pythiaspectrum_cuts->GetBinContent(i+1) * 1e9 / ( 2 * D0_pythiaspectrum_cuts->GetBinWidth(i+1) ));
	 D0_pythiaspectrum_cuts->SetBinError(i+1,D0_pythiaspectrum_cuts->GetBinError(i+1) * 1e9 / ( 2 * D0_pythiaspectrum_cuts->GetBinWidth(i+1) ));
  }
  TCanvas* c_fonll_pythia = new TCanvas("c_fonll_pythia","c_fonll_pythia");
  gPad->SetLogy();
  D0_pythiaspectrum->GetXaxis()->SetRangeUser(3.5, 45);
  D0_pythiaspectrum->GetYaxis()->SetRangeUser(1e0, 1e8);
  D0_pythiaspectrum->GetYaxis()->SetTitle("d#sigma/dp_{T}(D^{0}) (pb b GeV-1c)");
  D0_pythiaspectrum->GetXaxis()->SetTitle("D^{0} p_{T} (GeV/c)");
  D0_pythiaspectrum->Draw();
  hpt->SetLineColor(4.0);
  hpt->Draw("same");

  D0_pythiaspectrum_cuts->SetLineColor(2.0);
//  D0_pythiaspectrum_cuts->Draw("same");
  
  TLegend * t = new TLegend(0.22, 0.75, 0.85, 0.88);
  t->SetFillColor(0);
  t->AddEntry(hpt,"FONLL B Feed-down D^{0} Center Value");
  t->AddEntry(D0_pythiaspectrum, "Pythia B Feed-down D^{0}, Pthat Weighted");
//  t->AddEntry(D0_pythiaspectrum_cuts, "Pythia Pthat Weighted, Cuts");
  t->Draw();
  
  
  TCanvas * c_ratio_rawtofonll = new TCanvas("c_ratio_rawtofonll","c_ratio_rawtofonll", 800, 600);
  c_ratio_rawtofonll->Divide(2,1);
  c_ratio_rawtofonll->cd(1);
  gPad->SetLogy();
  
  hpt->SetLineColor(4.0);
  hpt->GetXaxis()->SetTitle("D^{0} p_{T} (GeV/c)");
  hpt->GetXaxis()->SetRangeUser(3.5, 45);
  hpt->GetYaxis()->SetRangeUser(1e0, 1e8);
  hpt->Draw();

  D0_pythiaspectrum_raw->SetLineColor(2.0);
  D0_pythiaspectrum_raw->Scale(0.5);
  D0_pythiaspectrum_raw->Draw("HISTesame");
  
  TLegend * t1 = new TLegend(0.15, 0.75, 0.65, 0.88);
  t1->SetFillColor(0);
  t1->SetTextSize(0.03);
  t1->AddEntry(hpt,"FONLL B Feed-down Center Value");
  t1->AddEntry(D0_pythiaspectrum_raw, "Pythia B Feed-down Raw Spectrum Shape");
  t1->Draw(); 

  c_ratio_rawtofonll->cd(2);
  gPad->SetLogy();
  TH1D * ratio_rawtofonll = (TH1D *) hpt->Clone("ratio_rawtofonll");
  ratio_rawtofonll->Divide(hpt, D0_pythiaspectrum_raw, 1.0, 1.0);
  ratio_rawtofonll->GetXaxis()->SetRangeUser(3.5, 45);
  ratio_rawtofonll->GetXaxis()->SetTitle("D^{0} p_{T} (GeV/c)");
  ratio_rawtofonll->GetYaxis()->SetTitle("FONLL / Pythia Raw");
  ratio_rawtofonll->Draw("HISTe");

  TH1D * D0_pythiaspectrum_weighted = new TH1D("D0_pythiaspectrum_weighted","D0_pythiaspectrum_weighted",BIN_NUM,HMIN,HMAX);
  for( int ievent = 0; ievent < gendmesontree->GetEntries(); ievent++ )
  {
	  gendmesontree->GetEntry(ievent);
	  for( int igend = 0; igend < ngend; igend++ )
	  {
		  if( TMath::Abs( dy[igend] ) > 2.0 ) continue;
		  D0_pythiaspectrum_weighted->Fill( dpt[igend], ratio_rawtofonll->GetBinContent( ratio_rawtofonll->FindBin(dpt[igend]) ) );
	  }
  }


  c_ratio_rawtofonll->cd(1);
  D0_pythiaspectrum_weighted->Scale(0.5);
  D0_pythiaspectrum_weighted->SetLineColor(8.0);
//  D0_pythiaspectrum_weighted->Draw("HISTesame");
  c_fonll_pythia->SaveAs("plots/D0_dsigmadpt_fonll_pythiapthatweight_Bfeeddown.png");
  c_fonll_pythia->SaveAs("plots/D0_dsigmadpt_fonll_pythiapthatweight_Bfeeddown.pdf");
  c_ratio_rawtofonll->SaveAs("plots/weight_pytiarawtofonll_D0_PbPb_Bfeeddown.png");
  c_ratio_rawtofonll->SaveAs("plots/weight_pytiarawtofonll_D0_PbPb_Bfeeddown.pdf");

  TFile * output = new TFile("D0_PbPb_rawtoFONLL_3to100_Bfeeddown.root","RECREATE");

  D0_pythiaspectrum->Write();
  hpt->Write();
  D0_pythiaspectrum_raw->Write();
  ratio_rawtofonll->Write();
  c_fonll_pythia->Write();
  c_ratio_rawtofonll->Write();

  output->Close();
}
