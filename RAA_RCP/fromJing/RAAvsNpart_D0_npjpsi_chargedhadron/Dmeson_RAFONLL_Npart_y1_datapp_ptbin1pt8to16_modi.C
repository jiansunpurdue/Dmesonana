#include <iostream>
#include <TFile.h>
#include <TStyle.h>
#include <TGraphAsymmErrors.h>
#include <TCanvas.h>
#include <TLegend.h>
#include <TLatex.h>
#include <TF1.h>
#include <TBox.h>
#include <TAxis.h>
#include <TMath.h>
#include <fstream>

Double_t AliceRAA_ptbin1pt8to16[6] = {0.15, 0.19, 0.25, 0.32, 0.36, 0.59};
TLatex* tex;
void Dmeson_RAFONLL_Npart_y1_datapp_ptbin1pt8to16_modi()
{
  gStyle->SetOptTitle(0);
  gStyle->SetOptStat(0);
  gStyle->SetPadTickX(1);
  gStyle->SetPadTickY(1);
  
  TGraphAsymmErrors* D0_fonll_raa_errorsys[6];
  TGraphAsymmErrors* D0_fonll_raa_errordata[6];
  TGraphAsymmErrors* D0_fonll_raa_errorfonll[6];
  
  TFile* input_cent0to10 = new TFile("rootfiles/PromptRAA_D0_PbPb_spectrum_fonll_effunpre_cent0to10_ptbin3_y1_dataplusfonll.root");
  D0_fonll_raa_errorsys[0] = (TGraphAsymmErrors*)input_cent0to10->Get("D0_fonll_raa_errorsys");
  D0_fonll_raa_errordata[0] = (TGraphAsymmErrors*)input_cent0to10->Get("D0_fonll_raa_errordata");
  D0_fonll_raa_errorfonll[0] = (TGraphAsymmErrors*)input_cent0to10->Get("D0_fonll_raa_errorfonll");  
  TFile* input_cent10to20 = new TFile("rootfiles/PromptRAA_D0_PbPb_spectrum_fonll_effunpre_cent10to20_ptbin3_y1_dataplusfonll.root");
  D0_fonll_raa_errorsys[1] = (TGraphAsymmErrors*)input_cent10to20->Get("D0_fonll_raa_errorsys");
  D0_fonll_raa_errordata[1] = (TGraphAsymmErrors*)input_cent10to20->Get("D0_fonll_raa_errordata");
  D0_fonll_raa_errorfonll[1] = (TGraphAsymmErrors*)input_cent10to20->Get("D0_fonll_raa_errorfonll");
  TFile* input_cent20to30 = new TFile("rootfiles/PromptRAA_D0_PbPb_spectrum_fonll_effunpre_cent20to30_ptbin3_y1_dataplusfonll.root");
  D0_fonll_raa_errorsys[2] = (TGraphAsymmErrors*)input_cent20to30->Get("D0_fonll_raa_errorsys");
  D0_fonll_raa_errordata[2] = (TGraphAsymmErrors*)input_cent20to30->Get("D0_fonll_raa_errordata");
  D0_fonll_raa_errorfonll[2] = (TGraphAsymmErrors*)input_cent20to30->Get("D0_fonll_raa_errorfonll");
  TFile* input_cent30to40 = new TFile("rootfiles/PromptRAA_D0_PbPb_spectrum_fonll_effunpre_cent30to40_ptbin3_y1_dataplusfonll.root");
  D0_fonll_raa_errorsys[3] = (TGraphAsymmErrors*)input_cent30to40->Get("D0_fonll_raa_errorsys");
  D0_fonll_raa_errordata[3] = (TGraphAsymmErrors*)input_cent30to40->Get("D0_fonll_raa_errordata");
  D0_fonll_raa_errorfonll[3] = (TGraphAsymmErrors*)input_cent30to40->Get("D0_fonll_raa_errorfonll");
  TFile* input_cent40to50 = new TFile("rootfiles/PromptRAA_D0_PbPb_spectrum_fonll_effunpre_cent40to50_ptbin3_y1_dataplusfonll.root");
  D0_fonll_raa_errorsys[4] = (TGraphAsymmErrors*)input_cent40to50->Get("D0_fonll_raa_errorsys");
  D0_fonll_raa_errordata[4] = (TGraphAsymmErrors*)input_cent40to50->Get("D0_fonll_raa_errordata");
  D0_fonll_raa_errorfonll[4] = (TGraphAsymmErrors*)input_cent40to50->Get("D0_fonll_raa_errorfonll");
  TFile* input_cent50to100 = new TFile("rootfiles/PromptRAA_D0_PbPb_spectrum_fonll_effunpre_cent50to100_ptbin3_y1_dataplusfonll.root");
  D0_fonll_raa_errorsys[5] = (TGraphAsymmErrors*)input_cent50to100->Get("D0_fonll_raa_errorsys");
  D0_fonll_raa_errordata[5] = (TGraphAsymmErrors*)input_cent50to100->Get("D0_fonll_raa_errordata");
  D0_fonll_raa_errorfonll[5] = (TGraphAsymmErrors*)input_cent50to100->Get("D0_fonll_raa_errorfonll");
  
  TCanvas* D0_RAFONLL_1ptbin = new TCanvas("D0_RAFONLL_1ptbin","D0_RAFONLL_1ptbin");
  
  D0_fonll_raa_errorsys[0]->GetYaxis()->SetRangeUser(0,2.5);
  D0_fonll_raa_errorsys[0]->Draw("A2");
  
  D0_fonll_raa_errorfonll[0]->Draw("2");
  D0_fonll_raa_errordata[0]->Draw("P");
  
  D0_fonll_raa_errorfonll[1]->SetLineColor(4.0);
  D0_fonll_raa_errordata[1]->SetLineColor(4.0);
  D0_fonll_raa_errordata[1]->SetMarkerColor(4.0);
  D0_fonll_raa_errorfonll[1]->Draw("2");
  D0_fonll_raa_errordata[1]->Draw("P");
  
  D0_fonll_raa_errorfonll[2]->SetLineColor(2.0);
  D0_fonll_raa_errordata[2]->SetLineColor(2.0);
  D0_fonll_raa_errordata[2]->SetMarkerColor(2.0);
  D0_fonll_raa_errorfonll[2]->Draw("2");
  D0_fonll_raa_errordata[2]->Draw("P");
  
  D0_fonll_raa_errorfonll[3]->SetLineColor(kCyan+2);
  D0_fonll_raa_errordata[3]->SetLineColor(kCyan+2);
  D0_fonll_raa_errordata[3]->SetMarkerColor(kCyan+2);
  D0_fonll_raa_errorfonll[3]->Draw("2");
  D0_fonll_raa_errordata[3]->Draw("P");
  
  TLegend* t = new TLegend(0.5, 0.7, 0.85, 0.85);
  t->SetFillColor(0);
  t->SetTextFont(42);
  t->AddEntry(D0_fonll_raa_errordata[0], "Centrality 0-10%", "PL");
  t->AddEntry(D0_fonll_raa_errordata[1], "Centrality 10-20%", "PL");
  t->AddEntry(D0_fonll_raa_errordata[2], "Centrality 20-30%", "PL");
  t->AddEntry(D0_fonll_raa_errordata[3], "Centrality 30-40%", "PL");
  t->AddEntry(D0_fonll_raa_errordata[4], "Centrality 40-50%", "PL");
  t->AddEntry(D0_fonll_raa_errordata[5], "Centrality 50-100%", "PL");
  t->Draw();
  
  //	D0_RAFONLL_1ptbin->SaveAs("results/D0_RAFONLL_ptbin1pt8to16_cent01020304050100_y1_dataplusfonll.png");
  //	D0_RAFONLL_1ptbin->SaveAs("results/D0_RAFONLL_ptbin1pt8to16_cent01020304050100_y1_dataplusfonll.pdf");
    
  Double_t step = 10.;
  Double_t Npart_central[6] = {22.06, 86.23, 130.06, 187.35, 261.49, 355.45};
  Double_t Npart_error[6];
  Double_t Npart_pt8to16[6];
  Double_t Npart_npjpsi_pt6p5to30[6];
  
  Double_t RAA_D0_pt8to16[6];
  Double_t RAA_D0_pt8to16_errordata_yl[6];
  Double_t RAA_D0_pt8to16_errordata_yh[6];
  Double_t RAA_D0_pt8to16_errorfonll_yl[6];
  Double_t RAA_D0_pt8to16_errorfonll_yh[6];
  Double_t RAA_D0_pt8to16_errorsys_yl[6];
  Double_t RAA_D0_pt8to16_errorsys_yh[6];
  
  Double_t RAA_npjpsi_pt6p5to30[6] = { 0.79, 0.75, 0.59, 0.54, 0.49, 0.40};
  Double_t RAA_npjpsi_pt6p5to30_errordata_yl[6] = { 0.11, 0.09, 0.06, 0.05, 0.04, 0.03};
  Double_t RAA_npjpsi_pt6p5to30_errordata_yh[6] = { 0.11, 0.09, 0.06, 0.05, 0.04, 0.03};
  Double_t RAA_npjpsi_pt6p5to30_errorsys_yl[6] = { 0.08, 0.08, 0.06, 0.06, 0.05, 0.04};
  Double_t RAA_npjpsi_pt6p5to30_errorsys_yh[6] = { 0.08, 0.08, 0.06, 0.06, 0.05, 0.04};
  
  for(int i=0;i<6;i++)
    {
      //Npart_error[i] = step/2.;
      //Npart_pt8to16[i] = Npart_central[i] - 1.5 * step;
      //Npart_pt8to16[i] = Npart_central[i] - 0.5 * step;
      //Npart_pt7to11[i]  = Npart_central[i] + step * 0.5;
      //Npart_pt11to16[i]  = Npart_central[i] + step * 1.5;
      //Npart_pt16to28[i]  = Npart_central[i] + 2.5 * step;
      step = 10.0;
      Npart_error[i] = step/2.;
      //Npart_pt8to16[i] = Npart_central[i] - 0.5 * step;
      //Npart_npjpsi_pt6p5to30[i] = Npart_central[i] + 0.5 * step;
      Npart_pt8to16[i] = Npart_central[i];
      //Npart_npjpsi_pt6p5to30[i] = Npart_central[i] + step;
      Npart_npjpsi_pt6p5to30[i] = Npart_central[i];
    }
  
  for(int i=0;i<6;i++)
    {
      RAA_D0_pt8to16[i] = D0_fonll_raa_errordata[5-i]->GetY()[1];
      cout << " RAA from CMS: " << RAA_D0_pt8to16[i] << endl;
      cout << " RAA from Alice: " << AliceRAA_ptbin1pt8to16[5-i] << endl;
      cout << " Ratio to Alice: " << RAA_D0_pt8to16[i]/AliceRAA_ptbin1pt8to16[5-i] << endl;
      RAA_D0_pt8to16_errordata_yl[i] = D0_fonll_raa_errordata[5-i]->GetErrorYlow(1);
      RAA_D0_pt8to16_errordata_yh[i] = D0_fonll_raa_errordata[5-i]->GetErrorYhigh(1);
      RAA_D0_pt8to16_errorfonll_yl[i] = D0_fonll_raa_errorfonll[5-i]->GetErrorYlow(1);
      RAA_D0_pt8to16_errorfonll_yh[i] = D0_fonll_raa_errorfonll[5-i]->GetErrorYhigh(1);
      RAA_D0_pt8to16_errorsys_yl[i] = D0_fonll_raa_errorsys[5-i]->GetErrorYlow(1);
      RAA_D0_pt8to16_errorsys_yh[i] = D0_fonll_raa_errorsys[5-i]->GetErrorYhigh(1);      
    }
  
  //systematic from TAA, NMB and Br
  
  RAA_D0_pt8to16_errorsys_yl[0] = TMath::Sqrt(RAA_D0_pt8to16_errorsys_yl[0]*RAA_D0_pt8to16_errorsys_yl[0]+0.151*0.151+0.03*0.03);
  RAA_D0_pt8to16_errorsys_yl[1] = TMath::Sqrt(RAA_D0_pt8to16_errorsys_yl[1]*RAA_D0_pt8to16_errorsys_yl[1]+0.110*0.110+0.03*0.03);
  RAA_D0_pt8to16_errorsys_yl[2] = TMath::Sqrt(RAA_D0_pt8to16_errorsys_yl[2]*RAA_D0_pt8to16_errorsys_yl[2]+0.086*0.086+0.03*0.03);
  RAA_D0_pt8to16_errorsys_yl[3] = TMath::Sqrt(RAA_D0_pt8to16_errorsys_yl[3]*RAA_D0_pt8to16_errorsys_yl[3]+0.067*0.067+0.03*0.03);
  RAA_D0_pt8to16_errorsys_yl[4] = TMath::Sqrt(RAA_D0_pt8to16_errorsys_yl[4]*RAA_D0_pt8to16_errorsys_yl[4]+0.054*0.054+0.03*0.03);
  RAA_D0_pt8to16_errorsys_yl[5] = TMath::Sqrt(RAA_D0_pt8to16_errorsys_yl[5]*RAA_D0_pt8to16_errorsys_yl[5]+0.045*0.045+0.03*0.03);
  
  RAA_D0_pt8to16_errorsys_yh[0] = TMath::Sqrt(RAA_D0_pt8to16_errorsys_yh[0]*RAA_D0_pt8to16_errorsys_yh[0]+0.151*0.151+0.03*0.03);
  RAA_D0_pt8to16_errorsys_yh[1] = TMath::Sqrt(RAA_D0_pt8to16_errorsys_yh[1]*RAA_D0_pt8to16_errorsys_yh[1]+0.110*0.110+0.03*0.03);
  RAA_D0_pt8to16_errorsys_yh[2] = TMath::Sqrt(RAA_D0_pt8to16_errorsys_yh[2]*RAA_D0_pt8to16_errorsys_yh[2]+0.086*0.086+0.03*0.03);
  RAA_D0_pt8to16_errorsys_yh[3] = TMath::Sqrt(RAA_D0_pt8to16_errorsys_yh[3]*RAA_D0_pt8to16_errorsys_yh[3]+0.067*0.067+0.03*0.03);
  RAA_D0_pt8to16_errorsys_yh[4] = TMath::Sqrt(RAA_D0_pt8to16_errorsys_yh[4]*RAA_D0_pt8to16_errorsys_yh[4]+0.054*0.054+0.03*0.03);
  RAA_D0_pt8to16_errorsys_yh[5] = TMath::Sqrt(RAA_D0_pt8to16_errorsys_yh[5]*RAA_D0_pt8to16_errorsys_yh[5]+0.045*0.045+0.03*0.03);
  
  TGraphAsymmErrors* RAA_D0_pt8to16_errordata_Npart = new TGraphAsymmErrors(6, Npart_pt8to16, RAA_D0_pt8to16, Npart_error, Npart_error, RAA_D0_pt8to16_errordata_yl, RAA_D0_pt8to16_errordata_yh);
  TGraphAsymmErrors* RAA_D0_pt8to16_errorfonll_Npart = new TGraphAsymmErrors(6, Npart_pt8to16, RAA_D0_pt8to16, Npart_error, Npart_error, RAA_D0_pt8to16_errorfonll_yl, RAA_D0_pt8to16_errorfonll_yh);
  TGraphAsymmErrors* RAA_D0_pt8to16_errorsys_Npart = new TGraphAsymmErrors(6, Npart_pt8to16, RAA_D0_pt8to16, Npart_error, Npart_error, RAA_D0_pt8to16_errorsys_yl, RAA_D0_pt8to16_errorsys_yh);
  
  TCanvas * D0_RAFONLL_Npart = new TCanvas("D0_RAFONLL_Npart","D0_RAFONLL_Npart", 600, 600);
  RAA_D0_pt8to16_errorsys_Npart->GetYaxis()->SetRangeUser(0, 1.6);
  RAA_D0_pt8to16_errorsys_Npart->GetYaxis()->SetTitle("R*_{#kern[-0.3]{AA}} , R_{AA}");
  RAA_D0_pt8to16_errorsys_Npart->GetXaxis()->SetLimits(0, 401);
  RAA_D0_pt8to16_errorsys_Npart->GetXaxis()->SetTitle("N_{part}");
  RAA_D0_pt8to16_errorsys_Npart->SetFillStyle(1001);
  RAA_D0_pt8to16_errorsys_Npart->SetFillColor(kRed-9);
  RAA_D0_pt8to16_errorsys_Npart->SetLineColor(kRed-9);
  RAA_D0_pt8to16_errorsys_Npart->Draw("A2");
  
  RAA_D0_pt8to16_errorfonll_Npart->SetFillColor(0);
  RAA_D0_pt8to16_errorfonll_Npart->SetFillStyle(0);
  RAA_D0_pt8to16_errorfonll_Npart->SetLineColor(kRed);
  RAA_D0_pt8to16_errorfonll_Npart->Draw("2");
  
  RAA_D0_pt8to16_errordata_Npart->SetFillStyle(1001);
  RAA_D0_pt8to16_errordata_Npart->SetFillColor(kRed-9);
  RAA_D0_pt8to16_errordata_Npart->SetLineColor(kRed-9);
  RAA_D0_pt8to16_errordata_Npart->SetMarkerStyle(20);
  RAA_D0_pt8to16_errordata_Npart->SetMarkerSize(1.0);
  RAA_D0_pt8to16_errordata_Npart->SetLineColor(2.0);
  RAA_D0_pt8to16_errordata_Npart->SetMarkerColor(2.0);
  RAA_D0_pt8to16_errordata_Npart->Draw("P");
  
  TGraphAsymmErrors* RAA_npjpsi_pt6p5to30_errordata_Npart = new TGraphAsymmErrors(6, Npart_npjpsi_pt6p5to30, RAA_npjpsi_pt6p5to30, Npart_error, Npart_error, RAA_npjpsi_pt6p5to30_errordata_yl, RAA_npjpsi_pt6p5to30_errordata_yh);
  TGraphAsymmErrors* RAA_npjpsi_pt6p5to30_errorsys_Npart = new TGraphAsymmErrors(6, Npart_npjpsi_pt6p5to30, RAA_npjpsi_pt6p5to30, Npart_error, Npart_error, RAA_npjpsi_pt6p5to30_errorsys_yl, RAA_npjpsi_pt6p5to30_errorsys_yh);
  
  RAA_npjpsi_pt6p5to30_errorsys_Npart->SetFillStyle(1001);
  RAA_npjpsi_pt6p5to30_errorsys_Npart->SetFillColor(kBlue-9);
  RAA_npjpsi_pt6p5to30_errorsys_Npart->SetLineColor(kBlue-9);
  RAA_npjpsi_pt6p5to30_errorsys_Npart->Draw("2");
  
  RAA_npjpsi_pt6p5to30_errordata_Npart->SetFillStyle(1001);
  RAA_npjpsi_pt6p5to30_errordata_Npart->SetFillColor(kBlue-9);
  RAA_npjpsi_pt6p5to30_errordata_Npart->SetLineColor(kBlue-9);
  RAA_npjpsi_pt6p5to30_errordata_Npart->SetMarkerStyle(21);
  RAA_npjpsi_pt6p5to30_errordata_Npart->SetMarkerSize(1.0);
  RAA_npjpsi_pt6p5to30_errordata_Npart->SetLineColor(4.0);
  RAA_npjpsi_pt6p5to30_errordata_Npart->SetMarkerColor(4.0);
  RAA_npjpsi_pt6p5to30_errordata_Npart->Draw("P");

  const int NUM_BIN_charged = 6;
  Double_t Npart_charged[NUM_BIN_charged],raa_charged[NUM_BIN_charged],stat_charged[NUM_BIN_charged],syst_charged[NUM_BIN_charged];
  Double_t temp;
  ifstream ifcharged("raacharged/RAAvsNpart_Hadron.txt");
  for(int i=0;i<NUM_BIN_charged;i++)
    {
      ifcharged>>temp;
      ifcharged>>temp;
      ifcharged>>Npart_charged[i];
      cout<<Npart_charged[i]<<"  ";
      ifcharged>>temp;
      ifcharged>>temp;
      ifcharged>>raa_charged[i];
      ifcharged>>stat_charged[i];
      ifcharged>>syst_charged[i];
      cout<<raa_charged[i]<<"  "<<stat_charged[i]<<"  "<<syst_charged[i]<<endl;
    }
  TGraphAsymmErrors* RAA_npcharge_errordata_Npart = new TGraphAsymmErrors(NUM_BIN_charged, Npart_charged, raa_charged, Npart_error, Npart_error, stat_charged, stat_charged);
  TGraphAsymmErrors* RAA_npcharge_errorsys_Npart = new TGraphAsymmErrors(NUM_BIN_charged, Npart_charged, raa_charged, Npart_error, Npart_error, syst_charged, syst_charged);
  RAA_npcharge_errorsys_Npart->SetFillStyle(1001);
  RAA_npcharge_errorsys_Npart->SetFillColor(16);
  RAA_npcharge_errorsys_Npart->SetLineColor(16);
  RAA_npcharge_errorsys_Npart->Draw("2");
  RAA_npcharge_errordata_Npart->SetFillStyle(1001);
  RAA_npcharge_errordata_Npart->SetFillColor(16);
  RAA_npcharge_errordata_Npart->SetMarkerStyle(22);
  RAA_npcharge_errordata_Npart->SetMarkerSize(1.0);
  RAA_npcharge_errordata_Npart->SetLineColor(12);
  RAA_npcharge_errordata_Npart->SetMarkerColor(12);
  RAA_npcharge_errordata_Npart->Draw("P");

  TBox* g = new TBox(1,1-0.09,11,1+0.09);
  g->SetLineColor(30);
  g->SetFillColor(30);
  g->Draw();
  
  TF1* fun = new TF1("fun", "1.0", 0, 500);
  fun->SetLineColor(1.0);
  fun->SetLineStyle(3);
  fun->SetLineWidth(0.1);
  fun->Draw("same");
  
  D0_RAFONLL_Npart->RedrawAxis();
  
  TLegend* t2 = new TLegend(0.12, 0.84, 0.45, 0.88);
  t2->SetFillColor(0);
  t2->SetBorderSize(0);
  t2->SetTextSize(0.036);
  t2->SetTextFont(42);
  t2->AddEntry(RAA_D0_pt8to16_errordata_Npart, "Prompt D^{0} R*_{#kern[-0.3]{AA}}", "PL");
  t2->Draw();
  TLegend* t3 = new TLegend(0.12, 0.62, 0.45, 0.74);
  t3->SetFillColor(0);
  t3->SetBorderSize(0);
  t3->SetTextSize(0.036);
  t3->SetTextFont(42);
  t3->SetTextColor(kRed+2);
  t3->AddEntry(RAA_D0_pt8to16_errorsys_Npart, "Syst._{} PbPb", "f");
  t3->AddEntry((TObject*)0, "data+T_{AA}+N_{MB}+BR", "");
  t3->AddEntry(RAA_D0_pt8to16_errorfonll_Npart, "Err. pp reference", "f");
  t3->Draw();
  
  tex = new TLatex(0.13,0.805,"8.0 < p_{T} < 16.0 GeV/c");
  tex->SetNDC();
  tex->SetTextFont(42);
  tex->SetTextSize(0.036);
  tex->SetLineWidth(2);
  tex->Draw();
  tex = new TLatex(0.13,0.755,"|y| < 1.0");
  tex->SetNDC();
  tex->SetTextFont(42);
  tex->SetTextSize(0.036);
  tex->SetLineWidth(2);
  tex->Draw();

  TLegend* tnp = new TLegend(0.49, 0.84, 0.87, 0.88);
  tnp->SetFillColor(0);
  tnp->SetBorderSize(0);
  tnp->SetTextSize(0.036);
  tnp->SetTextFont(42);
  tnp->AddEntry(RAA_npcharge_errordata_Npart, "Charged particle R_{AA}", "PL");
  tnp->Draw();
  TLegend* tnp2 = new TLegend(0.49, 0.70, 0.87, 0.74);
  tnp2->SetFillColor(0);
  tnp2->SetBorderSize(0);
  tnp2->SetTextSize(0.036);
  tnp2->SetTextFont(42);
  tnp2->AddEntry(RAA_npcharge_errorsys_Npart, "Syst.", "F");
  tnp2->Draw();

  tex = new TLatex(0.51,0.805,"7.2 < p_{T} < 9.6 GeV/c");
  tex->SetNDC();
  tex->SetTextFont(42);
  tex->SetTextSize(0.036);
  tex->SetLineWidth(2);
  tex->Draw();
  tex = new TLatex(0.51,0.755,"|#eta| < 1.0");
  tex->SetNDC();
  tex->SetTextFont(42);
  tex->SetTextSize(0.036);
  tex->SetLineWidth(2);
  tex->Draw();
  
  TLegend* tchg = new TLegend(0.42, 0.54, 0.80, 0.58);
  tchg->SetFillColor(0);
  tchg->SetBorderSize(0);
  tchg->SetTextSize(0.036);
  tchg->SetTextFont(42);
  tchg->AddEntry(RAA_npjpsi_pt6p5to30_errordata_Npart, "Non-prompt J/#psi R_{AA}", "PL");
  tchg->Draw();
  TLegend* tchg2 = new TLegend(0.42, 0.405, 0.80, 0.485);
  tchg2->SetFillColor(0);
  tchg2->SetBorderSize(0);
  tchg2->SetTextSize(0.036);
  tchg2->SetTextFont(42);
  tchg2->AddEntry(RAA_npjpsi_pt6p5to30_errorsys_Npart, "Syst.", "F");
  tchg2->AddEntry(g, "Syst. pp luminosity", "F");
  tchg2->Draw();

  tex = new TLatex(0.44,0.505,"6.5 < p_{T} < 30.0 GeV/c, |y| < 1.2");
  tex->SetNDC();
  tex->SetTextFont(42);
  tex->SetTextSize(0.036);
  tex->SetLineWidth(2);
  tex->Draw();

  TLatex Tl;
  Tl.SetNDC();
  Tl.SetTextAlign(12);
  Tl.SetTextSize(0.04);
  Tl.SetTextFont(42);
  Tl.DrawLatex(0.125,0.93, "#scale[1.25]{CMS} Preliminary");
  Tl.DrawLatex(0.53,0.93, "PbPb #sqrt{s_{NN}} = 2.76 TeV");
  
  D0_RAFONLL_Npart->RedrawAxis();
  
  D0_RAFONLL_Npart->SaveAs("results/D0_RAFONLL_Npart_ptbin1pt8to16_cent01020304050100_y1_dataplusfonll.png");
  D0_RAFONLL_Npart->SaveAs("results/D0_RAFONLL_Npart_ptbin1pt8to16_cent01020304050100_y1_dataplusfonll.pdf");
  
}

////Alice 356.6516957292244, 0.14555268462277304
//260.60050594553644, 0.19425332449506905
//186.20486735839614, 0.2526832699774082
//129.13853979248114, 0.32339659907198204
//85.02117125038892, 0.3589480661787583
//33.3227364348426, 0.5895942966139527
//
//
