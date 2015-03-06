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

int weight_cal_pythiarawtofonll_prompt()
{

  gROOT->SetStyle("Plain");
  gStyle->SetOptTitle(0);
  gStyle->SetOptStat(0);
  TH1::SetDefaultSumw2();

  ifstream getdata("./FONLL/fonll/FONLLInputs/fo_Dzero_pp_2.76_y2.dat");

  if(!getdata.is_open())
    {
      cout<<"Opening the file fails"<<endl;
    }

  float central[BIN_NUM];
  float min_all[BIN_NUM],max_all[BIN_NUM],min_sc[BIN_NUM],max_sc[BIN_NUM],min_mass[BIN_NUM],max_mass[BIN_NUM],min_pdf[BIN_NUM],max_pdf[BIN_NUM];
  int i;
  float tem;
  for(i=0;i<BIN_NUM;i++)
    {
      getdata>>tem;
      getdata>>central[i];
      getdata>>min_all[i];
      getdata>>max_all[i];
      getdata>>min_sc[i];
      getdata>>max_sc[i];
      getdata>>min_mass[i];
      getdata>>max_mass[i];
      getdata>>min_pdf[i];
      getdata>>max_pdf[i];
    }
  
  TH1F* hpt = new TH1F("hpt","",BIN_NUM,HMIN,HMAX);
  TH1F* hminall = new TH1F("hminall","",BIN_NUM,HMIN,HMAX);
  TH1F* hmaxall = new TH1F("hmaxall","",BIN_NUM,HMIN,HMAX);
  TH1F* hminsc = new TH1F("hminsc","",BIN_NUM,HMIN,HMAX);
  TH1F* hmaxsc = new TH1F("hmaxsc","",BIN_NUM,HMIN,HMAX);
  TH1F* hminmass = new TH1F("hminmass","",BIN_NUM,HMIN,HMAX);
  TH1F* hmaxmass = new TH1F("hmaxmass","",BIN_NUM,HMIN,HMAX);
  TH1F* hminpdf = new TH1F("hminpdf","",BIN_NUM,HMIN,HMAX);
  TH1F* hmaxpdf = new TH1F("hmaxpdf","",BIN_NUM,HMIN,HMAX);

  for(i=0;i<BIN_NUM;i++)
    {
      hpt->SetBinContent(i+1,central[i]);
      hminall->SetBinContent(i+1,min_all[i]);
      hmaxall->SetBinContent(i+1,max_all[i]);
      hminsc->SetBinContent(i+1,min_sc[i]);
      hmaxsc->SetBinContent(i+1,max_sc[i]);
      hminmass->SetBinContent(i+1,min_mass[i]);
      hmaxmass->SetBinContent(i+1,max_mass[i]);
      hminpdf->SetBinContent(i+1,min_pdf[i]);
      hmaxpdf->SetBinContent(i+1,max_pdf[i]);
    }

  TFile * input_PbPb_MC = new TFile("rootfiles/Dmesonana_hiforest_PbPb_Pyquen_D0embedded_D0pt3_pthat015305080_1217_1223_all_Bmom_v3.root");
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
          if( pt_Bmom[igend] > 0 )   continue;
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
  D0_pythiaspectrum->GetYaxis()->SetRangeUser(1e2, 1e9);
  D0_pythiaspectrum->GetYaxis()->SetTitle("d#sigma/dp_{T}(D^{0}) (pb b GeV-1c)");
  D0_pythiaspectrum->GetXaxis()->SetTitle("D^{0} p_{T} (GeV/c)");
  D0_pythiaspectrum->Draw();
  hpt->SetLineColor(4.0);
  hpt->Draw("same");

  D0_pythiaspectrum_cuts->SetLineColor(2.0);
//  D0_pythiaspectrum_cuts->Draw("same");
  
  TLegend * t = new TLegend(0.22, 0.7, 0.85, 0.85);
  t->SetFillColor(0);
  t->AddEntry(hpt,"FONLL Prompt D^{0} Center Value");
  t->AddEntry(D0_pythiaspectrum, "Pythia Prompt D^{0}, Pthat Weighted");
//  t->AddEntry(D0_pythiaspectrum_cuts, "Pythia Pthat Weighted, Cuts");
  t->Draw();
  
  
  TCanvas * c_ratio_rawtofonll = new TCanvas("c_ratio_rawtofonll","c_ratio_rawtofonll", 800, 600);
  c_ratio_rawtofonll->Divide(2,1);
  c_ratio_rawtofonll->cd(1);
  gPad->SetLogy();
  
  hpt->SetLineColor(4.0);
  hpt->GetXaxis()->SetTitle("D^{0} p_{T} (GeV/c)");
  hpt->GetXaxis()->SetRangeUser(3.5, 45);
  hpt->GetYaxis()->SetRangeUser(1e1, 1e9);
  hpt->Draw();

  D0_pythiaspectrum_raw->SetLineColor(2.0);
  D0_pythiaspectrum_raw->Scale(0.5);
  D0_pythiaspectrum_raw->Draw("HISTesame");
  
  TLegend * t1 = new TLegend(0.2, 0.7, 0.65, 0.85);
  t1->SetFillColor(0);
  t1->SetTextSize(0.03);
  t1->AddEntry(hpt,"FONLL Prompt D^{0} Center Value");
  t1->AddEntry(D0_pythiaspectrum_raw, "Pythia Prompt D^{0} Raw Spectrum Shape");
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
  c_fonll_pythia->SaveAs("plots/D0_dsigmadpt_fonll_pythiapthatweight_prompt.png");
  c_fonll_pythia->SaveAs("plots/D0_dsigmadpt_fonll_pythiapthatweight_prompt.pdf");
  c_ratio_rawtofonll->SaveAs("plots/weight_pytiarawtofonll_D0_PbPb_prompt.png");
  c_ratio_rawtofonll->SaveAs("plots/weight_pytiarawtofonll_D0_PbPb_prompt.pdf");

  TFile * output = new TFile("D0_PbPb_rawtoFONLL_3to100_prompt.root","RECREATE");

  D0_pythiaspectrum->Write();
  hpt->Write();
  D0_pythiaspectrum_raw->Write();
  ratio_rawtofonll->Write();
  c_fonll_pythia->Write();
  c_ratio_rawtofonll->Write();

  output->Close();
}
