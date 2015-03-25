#include <string>
#include <vector>
#include <map>
#include <iostream>
#include <TFile.h>
#include <TH1F.h>
#include <TF1.h>
#include <TNamed.h>
#include <TNtuple.h>
#include <TTree.h>
#include <TMath.h>
#include <TCanvas.h>
#include <TStyle.h>
#include <TLatex.h>
#include <cstdlib>
#include "Math/MinimizerOptions.h"
#include <iomanip>

#include "PtBins.h"
using namespace std;

float ptmin = 4.5;
float ptmax = 5.5;

bool evtunprescaleMB = false;   //false to fit raw counts without unprescale MB trigger
bool isMC = false;

float cut_m_low = 1.70;
float cut_m_high = 2.05;
int massbin = 35;
float hiBin_low = -0.5;
float hiBin_high = 199.5;
float rapidityrange = 2.0;

TH1F* hfg_minbias;  //for D0

TString channel = "Dzero_PbPb";
TString func = "AlphaSA";//SA, Default, AlphaSA

void book_hist()
{
  char hname[100], pt_range[1000];
  sprintf(pt_range, "pt: %.1f %.1f", ptmin, ptmax);
  sprintf(hname, "hfg_minbias");
  hfg_minbias = new TH1F(hname, pt_range, massbin, cut_m_low, cut_m_high);
  hfg_minbias->Sumw2();
}

void write_histo( TFile* output)
{
  hfg_minbias->Write();
  output->Close();
}

int decideptbin(float ptlow, float pthigh)
{
  
  int ipt=-1,i=0;
  for (i=1;i<NPT;i++)
    {
      if(ptlow==ptbins[i]&&pthigh==ptbins[i+1])
	{
	  ipt = i-1;
	  break;
	}
    }
  if(ipt<0)
    {
      cout<<"╔═══════════════════════╗"<<endl;
      cout<<"║ ERROR: NOT PRESET BIN ║"<<endl;
      cout<<"╚═══════════════════════╝"<<endl;
    }
  return ipt;
  
}

void fit_hist( TH1F * histo, TCanvas *cfg, float ptlow, float pthigh)
{
  
  ROOT::Math::MinimizerOptions::SetDefaultMaxFunctionCalls(100000); 
  cfg->cd();
  
  histo->SetMarkerSize(0.8);
  histo->SetLineColor(2);
  histo->SetMarkerColor(2);
  histo->SetMarkerStyle(20);
  histo->GetXaxis()->SetNdivisions(505);
  histo->GetXaxis()->SetTitle("m_{#piK} (GeV)");
  histo->GetYaxis()->SetTitle("Counts");
  histo->GetXaxis()->SetRangeUser(cut_m_low, cut_m_high);
  TF1* fit_fun = new TF1("fit_fun", "gausn(0) + pol2(3)", cut_m_low, cut_m_high);
  float max = histo->GetMaximum();
  
  float p0 = 1000, p1 = 1.87, p2 = 0.02;
  float p0_L = 0, p1_L = 1.84, p2_L = 0;
  float p0_H = 2*max, p1_H = 1.9, p2_H = 0.05;
  
  float p3 = -1. * max, p4 = max, p5 = -1. * max;
  
  int pass = 0;
  int fittingtry = 0;
  
  char sig_print[100], chi2_print[100], bkg_print[100], sign_print[100];
  
  while (!pass)
    {
      fit_fun->SetParameter(0, p0);
      fit_fun->SetParameter(1, p1);
      fit_fun->SetParameter(2, p2);
      
      fit_fun->SetParLimits(0, p0_L, p0_H);
      fit_fun->SetParLimits(1, p1_L, p1_H);
      fit_fun->SetParLimits(2, p2_L, p2_H);
      
      if(fittingtry == 0)
	{
	  histo->Fit(fit_fun,"","", cut_m_low, cut_m_high);
	}
      else
	{ 
	  histo->Fit(fit_fun,"","", cut_m_low, cut_m_high);
	}
      histo->Draw();
      
      TF1* fit_fun_1st = (TF1*)fit_fun->Clone("fit_fun_1st");
      fit_fun_1st->SetParameter(3, 0);
      fit_fun_1st->SetParameter(4, 0);
      fit_fun_1st->SetParameter(5, 0);

      TF1* fit_fun_bg = (TF1*)fit_fun->Clone("fit_fun_bg");
      fit_fun_bg->SetParameter(0, 0);
      fit_fun_bg->SetParameter(1, 0);
      fit_fun_bg->SetParameter(2, 0);
    
      fit_fun_bg->SetLineColor(8);
      fit_fun_bg->Draw("same");
      
      fittingtry++;
      
      float binwidth = histo->GetBinWidth(10);
      float ptbinwidth = pthigh-ptlow;
      
      float Nsig = fit_fun->GetParameter(0)/(binwidth);
      float err_Nsig = fit_fun->GetParError(0)/(binwidth);
      float fitchi2 = fit_fun->GetChisquare();
      int noffreepara = fit_fun->GetNumberFreeParameters();
      int noffitpoints = fit_fun->GetNumberFitPoints();
      
      cout << " fitchi2: " << fitchi2 << "   noffreepara: " << noffreepara << "  noffitpoints: " << noffitpoints << endl;
      
      float sigma = fit_fun->GetParameter(2);
      float mu    = fit_fun->GetParameter(1);
      
      float Nbkg = fit_fun_bg->Integral(mu-2*sigma,mu+2*sigma)/binwidth;
      cout << "Nsig integral "<<fit_fun_1st->Integral(mu-2*sigma,mu+2*sigma)/binwidth
	   <<" Nbkg integral "<<fit_fun_bg->Integral(mu-2*sigma,mu+2*sigma)/binwidth
	   <<" mu "<<mu<<" sigma "<<sigma<<" bin width "<<binwidth<<endl;
      cout << " pt min "<<ptlow<<" pt max "<<pthigh<<" fittingtry "<<fittingtry<<endl;
      cout << "Nsig total integral "<<fit_fun_1st->Integral(0, 10)/binwidth<<endl<<endl;
      
      if(!isMC)
	{
	  sprintf( sig_print,"N_{sig} = %7.1f #pm %7.1f", Nsig, err_Nsig);
	}
      else
	{
	  sprintf( sig_print,"N_{sig} = %7.5f #pm %7.5f", Nsig, err_Nsig);
	  sprintf( chi2_print, "#chi^{2}#/d.o.f = %3.2f", fitchi2/( noffitpoints - noffreepara));
	  sprintf( bkg_print, "N_{bkg} = %7.5f", Nbkg);
	  sprintf( sign_print, "S = %7.5f", Nsig/sqrt(Nsig+Nbkg));
	}
      
      if(fittingtry == 2)
	{
	  TLatex Tl;
	  Tl.SetNDC();
	  Tl.SetTextAlign(12);
	  Tl.SetTextSize(0.037);
	  Tl.DrawLatex(0.55,0.8, sig_print);
	  if(isMC)
	    {
	      Tl.DrawLatex(0.55,0.7, chi2_print);
	      Tl.DrawLatex(0.55,0.6, bkg_print);
	      Tl.DrawLatex(0.55,0.5, sign_print);
	    }
	}
      
      if (fittingtry == 2)  
	{
	  pass = 1;
	}
      if(!pass) 
	{
	  p0 = fit_fun->GetParameter(0);
	  p1 = fit_fun->GetParameter(1);
	  p2 = fit_fun->GetParameter(2);
        }
      
  }
  return;
}

void fit()
{
  book_hist();
  
  TH1D * hf_mb = new TH1D("hf_mb","hf_mb",10,-5,5);
  hf_mb->Sumw2();
  
  TFile * input = new TFile("/data/dmeson/Ntuple/Dmesonana_Rereco_MBtrig_d0pt3p0_d1p8_pt1p5_v1_tight_1213_6lumi_cuts_noprobchi2cut_vz_v4.root");
  TTree * recodmesontree = (TTree *) input->Get("recodmesontree");

  int MinBias;
  int MinBias_Prescl;
  
  int ndcand;
  int hiBin;
  double pthatweight;
  double trigweight;

  int ptindex = decideptbin(ptmin,ptmax);

  vector<int> *dtype = 0, *passingcuts = 0;
  vector<float> *dcandmass = 0, *dcandpt = 0, *dcandy = 0, *dcandphi = 0, *dcandffls3d = 0, *dcandcosalpha = 0, *dcandfprob = 0, *dcandfchi2 = 0;
  vector<float> *dcanddau1eta = 0, *dcanddau2eta = 0;
  vector<float> *dcanddau1pt = 0, *dcanddau2pt = 0;
  vector<float> *dcandeta = 0;
  
  recodmesontree->SetBranchAddress("MinBias", &MinBias);
  recodmesontree->SetBranchAddress("MinBias_Prescl", &MinBias_Prescl);
  recodmesontree->SetBranchAddress("hiBin", &hiBin);
  recodmesontree->SetBranchAddress("pthatweight", &pthatweight);
  recodmesontree->SetBranchAddress("trigweight", &trigweight);
  recodmesontree->SetBranchAddress("ndcand", &ndcand);
  recodmesontree->SetBranchAddress("dtype", &dtype);
  recodmesontree->SetBranchAddress("passingcuts", &passingcuts);
  recodmesontree->SetBranchAddress("dcandmass", &dcandmass);
  recodmesontree->SetBranchAddress("dcandpt", &dcandpt);
  recodmesontree->SetBranchAddress("dcandy", &dcandy);
  recodmesontree->SetBranchAddress("dcandphi", &dcandphi);
  recodmesontree->SetBranchAddress("dcandffls3d", &dcandffls3d);
  recodmesontree->SetBranchAddress("dcandcosalpha", &dcandcosalpha);
  recodmesontree->SetBranchAddress("dcandfprob", &dcandfprob);
  recodmesontree->SetBranchAddress("dcandfchi2", &dcandfchi2);
  recodmesontree->SetBranchAddress("dcanddau1eta", &dcanddau1eta);
  recodmesontree->SetBranchAddress("dcanddau2eta", &dcanddau2eta);
  recodmesontree->SetBranchAddress("dcanddau1pt", &dcanddau1pt);
  recodmesontree->SetBranchAddress("dcanddau2pt", &dcanddau2pt);
  recodmesontree->SetBranchAddress("dcandeta", &dcandeta);

  cout<<"ptindex: "<<ptindex<<endl;
  cout<<ffls3dcut[ptindex]<<" "<<alphacut[ptindex]<<" "<<fprobcut[ptindex]<<" "<<fchi2cut[ptindex]<<endl;	      
  
  for ( int entry = 0; entry < recodmesontree->GetEntries(); entry++ )
    {
      recodmesontree->GetEntry(entry);
      if( entry % 1000000 == 0 ) cout<<setiosflags(ios::left)<<setw(10)<<entry<<" / "<<setiosflags(ios::left)<<setw(10)<<recodmesontree->GetEntries()<<"Events"<<endl;
      if( !MinBias ) continue;
      if( ndcand != dtype->size() || ndcand != passingcuts->size() || ndcand != dcandmass->size() || ndcand != dcandpt->size() ) cout << "Error!!!!!!!!" << endl;
      if( hiBin < hiBin_low || hiBin > hiBin_high )   continue;
      
      hf_mb->Fill(MinBias, MinBias_Prescl);
      for( int icand = 0; icand < ndcand; icand++ )
	{
	  if( dtype->at(icand) != 2 )   cout << " Error!!!!!!! Just working on D0 now" << endl;
	  if(func=="AlphaSA")
	    {
	      if( dcandffls3d->at(icand)<ffls3dcut[ptindex] || TMath::ACos(dcandcosalpha->at(icand))>alphacut[ptindex] || dcandfprob->at(icand)<fprobcut[ptindex] || dcandfchi2->at(icand)>fchi2cut[ptindex])  continue;
	    }
	  else
	    {
	      if( dcandffls3d->at(icand)<ffls3dcut[ptindex] || dcandcosalpha->at(icand)<cosalphacut[ptindex] || dcandfprob->at(icand)<fprobcut[ptindex] || dcandfchi2->at(icand)>fchi2cut[ptindex])  continue;
	    }
	  
	  if( TMath::Abs( dcandeta->at(icand) ) > 2.0 )  continue;
	  if( TMath::Abs( dcanddau1pt->at(icand) ) < 1.5 || TMath::Abs( dcanddau2pt->at(icand) ) < 1.5 )   continue;
	  if( TMath::Abs( dcanddau1eta->at(icand) ) > 2.4 || TMath::Abs( dcanddau2eta->at(icand) ) > 2.4 )   continue;
	  if( dcandpt->at(icand)>ptmax || dcandpt->at(icand)<ptmin) continue;

	  double weight=1.0;
	  if(!isMC)
	    {
	      weight = MinBias_Prescl;
	    }
	  else
	    {
	      weight = pthatweight;
	    }
	  if( !evtunprescaleMB )
	    {
	      weight = 1.0;
	    }
	  hfg_minbias->Fill(dcandmass->at(icand), weight);
	}
    }
  
  gStyle->SetOptFit(0);
  gStyle->SetOptStat(0);

  TCanvas* cfg_mb = new TCanvas("cfg_mb", "cfg_mb", 500, 500);
  fit_hist(hfg_minbias, cfg_mb, ptmin, ptmax);

  cfg_mb->SaveAs(Form("plots/plot_%s/fit/%s/massSpectrum_%.1f_%.1f_notMax.pdf",channel.Data(),func.Data(),ptmin,ptmax));

}

