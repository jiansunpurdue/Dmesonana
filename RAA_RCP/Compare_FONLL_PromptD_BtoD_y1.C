#include "TH1F.h"
#include <cmath>
#include "TGraphAsymmErrors.h"
#include "TLegend.h"
#include "TCanvas.h"
#include <fstream>
#include <iostream>

#define BIN_NUM 396 //pPb_pt:220,pPb_y:40,pp_pt:222,pp_y:45
#define HMIN 1      //pPb_pt:5,pPb_y:-2,pp_pt:9,pp_y:0
#define HMAX 100     //pPb_pt:55,pPb_y:2,pp_pt:120,pp_y:2.25

#define MAXGENDMESON 100

#define H_REBIN 12

int Compare_FONLL_PromptD_BtoD_y1()
{

  gROOT->SetStyle("Plain");
  gStyle->SetOptTitle(0);
  gStyle->SetOptStat(0);
  TH1::SetDefaultSumw2();

  ifstream getdata("./../FONLL/fonll/FONLLInputs/fo_Dzero_pp_2.76_y1.dat");

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
      hpt->SetBinContent(i+1,0.557 * central[i]);
//      hpt->SetBinContent(i+1,0.557 * max_all[i]);
      hminall->SetBinContent(i+1,min_all[i]);
      hmaxall->SetBinContent(i+1,max_all[i]);
      hminsc->SetBinContent(i+1,min_sc[i]);
      hmaxsc->SetBinContent(i+1,max_sc[i]);
      hminmass->SetBinContent(i+1,min_mass[i]);
      hmaxmass->SetBinContent(i+1,max_mass[i]);
      hminpdf->SetBinContent(i+1,min_pdf[i]);
      hmaxpdf->SetBinContent(i+1,max_pdf[i]);
  }


  TFile * input_BFONLL = new TFile("./BtoD_fromyenjie/rapidity1p0/BtoD-0-100.root");
  TH1D * BtoD_central = (TH1D *) input_BFONLL->Get("hDFromBPt");
  BtoD_central->Scale(0.5); //contain both D0 and anti-D0
  double bin_edge[BIN_NUM+1];

  for( int i = 0; i < BIN_NUM+1; i++ )
  {
	  bin_edge[i] = 1.0 + 0.25 * i;
  }

  TH1D * BtoD_central_rebin = (TH1D *) BtoD_central->Rebin( BIN_NUM, "BtoD_central_rebin", bin_edge);
  BtoD_central_rebin->Rebin(H_REBIN);
  BtoD_central_rebin->Scale(1.0/H_REBIN);


  TFile * input_PbPb_MC = new TFile("/home/sun229/store/v2_analysisfiles/Dmesonana_hiforest_PbPbD0tokaonpion_Pthat0153050_D0pt1p0_tkpt1p0eta1p1_2760GeV_0803_all.root");
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
  TH1D * D0_pythiaspectrum_bmom = new TH1D("D0_pythiaspectrum_bmom","D0_pythiaspectrum_bmom",BIN_NUM,HMIN,HMAX);

  
  for( int ievent = 0; ievent < gendmesontree->GetEntries(); ievent++ )
  {
	  gendmesontree->GetEntry(ievent);
	  for( int igend = 0; igend < ngend; igend++ )
	  {
		  if( TMath::Abs( dy[igend] ) > 1.0 ) continue;

		  if( dpt[igend] > 2.0 * pthat )   continue;
//          if( pthat < 30 )   continue;
          if( pt_Bmom[igend] < 0 )
		      D0_pythiaspectrum->Fill(dpt[igend], weight_pthat);

		  if( pt_Bmom[igend] > 0 )
			  D0_pythiaspectrum_bmom->Fill(dpt[igend], weight_pthat);

	  }
  }

  for (int i=0;i<D0_pythiaspectrum->GetNbinsX();i++)
  {
	 D0_pythiaspectrum->SetBinContent(i+1,D0_pythiaspectrum->GetBinContent(i+1) * 1e9 / ( 2 * D0_pythiaspectrum->GetBinWidth(i+1) ));
	 D0_pythiaspectrum->SetBinError(i+1,D0_pythiaspectrum->GetBinError(i+1) * 1e9 / ( 2 * D0_pythiaspectrum->GetBinWidth(i+1) ));

	 D0_pythiaspectrum_bmom->SetBinContent(i+1,D0_pythiaspectrum_bmom->GetBinContent(i+1) * 1e9 / ( 2 * D0_pythiaspectrum_bmom->GetBinWidth(i+1) ));
	 D0_pythiaspectrum_bmom->SetBinError(i+1,D0_pythiaspectrum_bmom->GetBinError(i+1) * 1e9 / ( 2 * D0_pythiaspectrum_bmom->GetBinWidth(i+1) ));
  }

  hpt->Rebin(H_REBIN);
  D0_pythiaspectrum->Rebin(H_REBIN);
  D0_pythiaspectrum_bmom->Rebin(H_REBIN);

  hpt->Scale(1./H_REBIN);
  D0_pythiaspectrum->Scale(1./H_REBIN);
  D0_pythiaspectrum_bmom->Scale(1./H_REBIN);

  TCanvas* c_fonll_pythia = new TCanvas("c_fonll_pythia","c_fonll_pythia");
//  c_fonll_pythia->Divide(2,1);

//  c_fonll_pythia->cd(1);
  gPad->SetLogy();
  D0_pythiaspectrum->GetXaxis()->SetRangeUser(3.5, 45);
  D0_pythiaspectrum->GetYaxis()->SetRangeUser(1e0, 1e9);
  D0_pythiaspectrum->GetYaxis()->SetTitle("d#sigma/dp_{T}(D^{0}) (pb b GeV-1c)");
  D0_pythiaspectrum->GetXaxis()->SetTitle("D^{0} p_{T} (GeV/c)");
  D0_pythiaspectrum->Draw();

  D0_pythiaspectrum_bmom->SetLineColor(2.0);
  D0_pythiaspectrum_bmom->Draw("same");

  hpt->SetLineColor(4.0);
  hpt->Draw("same");

  BtoD_central_rebin->SetLineColor(3.0);
  BtoD_central_rebin->SetMarkerStyle(1);
  BtoD_central_rebin->Draw("same");


  TLegend * t = new TLegend(0.22, 0.7, 0.85, 0.85);
  t->SetFillColor(0);
  t->AddEntry((TObject*)0,"|y| < 1.0","");
  t->AddEntry(hpt,"FONLL Prompt D0 Center Value");
  t->AddEntry(BtoD_central_rebin, "FONLL B Feed-down D0 Center Value");
  t->AddEntry(D0_pythiaspectrum, "Pythia Prompt D0, Pthat Weighted");
  t->AddEntry(D0_pythiaspectrum_bmom, "Pythia B Feed-down D0, Pthat Weighted");
  t->Draw();
  
  TCanvas* c_fonll_pythia_ratio = new TCanvas("c_fonll_pythia_ratio","c_fonll_pythia_ratio");
  TH1D * ratio_pythia_fonll = ( TH1D * ) D0_pythiaspectrum->Clone("ratio_pythia_fonll");
  TH1D * ratio_pythia_Bmom_pythia = ( TH1D * ) D0_pythiaspectrum_bmom->Clone("ratio_pythia_Bmom_pythia");

  TH1D * ratio_fonll_Bfraction = ( TH1D * ) BtoD_central_rebin->Clone("ratio_fonll_Bfraction");
  ratio_fonll_Bfraction->Divide(hpt);

  ratio_pythia_fonll->Divide(hpt);
  ratio_pythia_Bmom_pythia->Divide(D0_pythiaspectrum_bmom, D0_pythiaspectrum, 1.0, 1.0);

  ratio_pythia_fonll->GetYaxis()->SetRangeUser(0., 3.0);
  ratio_pythia_fonll->GetYaxis()->SetTitle("Ratio");


  ratio_pythia_Bmom_pythia->GetYaxis()->SetRangeUser(0.,0.3);
  ratio_pythia_Bmom_pythia->GetYaxis()->SetTitle("Ratio");
  ratio_pythia_Bmom_pythia->GetXaxis()->SetRangeUser(3.0, 60.0);
  ratio_pythia_Bmom_pythia->SetLineColor(6.0);
  ratio_pythia_Bmom_pythia->SetLineWidth(2.0);
  ratio_pythia_Bmom_pythia->Draw();

  ratio_fonll_Bfraction->SetLineWidth(2.0);
  ratio_fonll_Bfraction->Draw("same");

//  ratio_pythia_fonll->Draw("same");
  
  TLegend * t1 = new TLegend(0.15, 0.7, 0.85, 0.85);
  t1->SetFillColor(0);
  t1->AddEntry(ratio_pythia_Bmom_pythia, "Pythia Non-prompt D0 / Pythia Prompt D0");
  t1->AddEntry( ratio_fonll_Bfraction, "Central FONLL Non-prompt D0 / Central FONLL Prompt D0");
  t1->Draw();

//  c_fonll_pythia->SaveAs("plots/D0_prompt_BtoD_spectrum_pythia_FONLL.png");
//  c_fonll_pythia->SaveAs("plots/D0_prompt_BtoD_spectrum_pythia_FONLL.pdf");
//  c_fonll_pythia_ratio->SaveAs("plots/Ratio_D0_prompt_BtoD_spectrum_pythia_FONLL.png");
//  c_fonll_pythia_ratio->SaveAs("plots/Ratio_D0_prompt_BtoD_spectrum_pythia_FONLL.pdf");

//  TFile * output = new TFile("D0_Compare_pythiapthatweighttofonll_pythiaBfraction.root","RECREATE");
//
//  D0_pythiaspectrum->Write();
//  D0_pythiaspectrum_bmom->Write();
//  ratio_fonll_Bfraction->Write();
//  hpt->Write();
//  ratio_pythia_fonll->Write();
//  ratio_pythia_Bmom_pythia->Write();
//
//  output->Close();
}
