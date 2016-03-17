#include <iostream>
#include <TCanvas.h>
#include <TF1.h>
#include <TLatex.h>
#include <TLegend.h>
#include <TString.h>
#include <TFile.h>
#include <TH1F.h>
#include <TStyle.h>
#include <TColor.h>
#include <TLine.h>
#include <TPad.h>
#include <TGaxis.h>

#define NPT 14
Double_t ptbins[NPT+1] = {0,1.5,2.5,3.5,4.5,5.5,7,9,11,13,16,20,28,40,100};
Double_t eff_fit_range_low_expobkg_ptbin14[14] = {1.70, 1.70, 1.77, 1.75, 1.70, 1.70, 1.70, 1.70, 1.70, 1.70, 1.70, 1.70, 1.70, 1.70};
Double_t eff_fit_range_high_expobkg_ptbin14[14] = {2.05, 2.05, 2.00, 2.00, 2.05, 2.05, 2.05, 2.05, 2.05, 2.05, 2.05, 2.05, 2.05, 2.05};

Double_t hemptyMin[NPT] = {0., 0., -0.05, 0., 0., -0.05, 0., 0., -0.05, 0., 0., -0.05, -0.05, 0.};
TLatex* tex;

void DrawSigextforpas_modi()
{
  gStyle->SetTextSize(0.05);
  gStyle->SetTextFont(42);
  gStyle->SetPadRightMargin(0.043);
  gStyle->SetPadLeftMargin(0.18);
  gStyle->SetPadTopMargin(0.1);
  gStyle->SetPadBottomMargin(0.145);
  gStyle->SetTitleX(.0f);

  void drawhistSep(TH1F* histo, Int_t iptbin, Double_t ptmin, Double_t ptmax, Int_t ipad);
  void drawhist(TH1F* histo, Int_t iptbin, TCanvas* cfg, Int_t ipad);
  void drawtex(Double_t ptmin, Double_t ptmax, Int_t ipad);

  TFile* input = new TFile("./rootfiles/Dspectrum_pbpb_data_ptbin_14_ptd_unpreMBtrig_0_cent0to100_y1.root");
  TH1F* h[NPT];
  TString hname;

  for(Int_t i=0;i<NPT;i++)
    {
      hname = Form("hfg_minbias_expobkg_%d",i);
      h[i] = (TH1F*)input->Get(hname);
    }
  /*
  TCanvas* cfg_sigextforpas=  new TCanvas("cfg_sigextforpas","",1128,780);
  cfg_sigextforpas->Clear();

  TPad *pad1 = new TPad("pad1","",0.000,0.497,0.334,0.99);
  TPad *pad2 = new TPad("pad2","",0.334,0.497,0.667,0.99);
  TPad *pad3 = new TPad("pad3","",0.667,0.497,1.000,0.99);
  TPad *pad4 = new TPad("pad4","",0.000,0.005,0.334,0.495);
  TPad *pad5 = new TPad("pad5","",0.334,0.005,0.667,0.495);
  TPad *pad6 = new TPad("pad5","",0.667,0.005,1.000,0.495);

  pad1->Draw();
  pad2->Draw();
  pad3->Draw();
  pad4->Draw();
  pad5->Draw();
  pad6->Draw();

  pad1->cd();
  drawhist(h[2],2,cfg_sigextforpas,1);
  drawtex(ptbins[2],ptbins[3],1);
  pad2->cd();
  drawhist(h[5],5,cfg_sigextforpas,2);
  drawtex(ptbins[5],ptbins[6],2);
  pad3->cd();
  drawhist(h[8],8,cfg_sigextforpas,3);
  drawtex(ptbins[8],ptbins[9],3);
  pad4->cd();
  drawhist(h[11],11,cfg_sigextforpas,4);
  drawtex(ptbins[11],ptbins[12],4);
  pad5->cd();
  drawhist(h[12],12,cfg_sigextforpas,5);
  drawtex(ptbins[12],ptbins[13],5);
  pad6->cd();
  drawhist(h[12],12,cfg_sigextforpas,6);
  
  cfg_sigextforpas->SaveAs("massfitforpas/sigextforpas.pdf");
  cfg_sigextforpas->SaveAs("massfitforpas/sigextforpas.png");
  */
//  drawhistSep(h[2],2,ptbins[2],ptbins[3],7);
//  drawhistSep(h[5],5,ptbins[5],ptbins[6],8);
//  drawhistSep(h[8],8,ptbins[8],ptbins[9],9);
//  drawhistSep(h[11],11,ptbins[11],ptbins[12],10);
  drawhistSep(h[12],12,ptbins[12],ptbins[13],11);
}

void drawhistSep(TH1F* histo, Int_t iptbin, Double_t ptmin, Double_t ptmax, Int_t ipad)
{
  gStyle->SetPadTickX(1);
  gStyle->SetPadTickY(1);
  TGaxis::SetMaxDigits(6);
  TCanvas* cfg_sigextforpas_Sep = new TCanvas(Form("cfg_sigextforpas_Sep%d",ipad),"",600,600);

  Double_t fit_range_low = eff_fit_range_low_expobkg_ptbin14[iptbin];
  Double_t fit_range_high = eff_fit_range_high_expobkg_ptbin14[iptbin];

  TH1F* hempty  = new TH1F(Form("hempty%d",ipad),"",50,fit_range_low,fit_range_high);
  hempty->SetStats(0);
  hempty->GetXaxis()->SetTitle("m_{#piK} (GeV/c^{2})");
  hempty->SetYTitle("Entries / (10 MeV/c^{2})");
  hempty->GetXaxis()->SetTitleOffset(1.0);
  hempty->GetYaxis()->SetTitleOffset(1.8);
  hempty->GetXaxis()->SetLabelOffset(0.007);
  hempty->GetYaxis()->SetLabelOffset(0.007);
  hempty->GetXaxis()->SetTitleSize(0.04);
  hempty->GetYaxis()->SetTitleSize(0.04);
  hempty->GetXaxis()->SetTitleFont(42);
  hempty->GetYaxis()->SetTitleFont(42);
  hempty->GetXaxis()->SetLabelFont(42);
  hempty->GetYaxis()->SetLabelFont(42);
  hempty->GetXaxis()->SetLabelSize(0.04);
  hempty->GetYaxis()->SetLabelSize(0.04);
  hempty->SetMaximum(histo->GetMaximum()*1.4);
  if(iptbin<10) hempty->SetMaximum(histo->GetMaximum()*1.3);
  if( iptbin == 12 ) hempty->SetMaximum(histo->GetMaximum()*1.5);
  hempty->Draw();

  Int_t ci = TColor::GetColor("#000099");
  histo->SetLineColor(ci);
  histo->SetMarkerStyle(24);
  histo->SetMarkerSize(0.8);
  histo->SetStats(0);
  histo->Draw("same");

  TF1* fit_fun = histo->GetFunction("fit_fun");
  TF1* fit_fun_sgnl = new TF1("fit_fun_sgnl","[0]*([3]*Gaus(x,[1],[2])/(sqrt(2*3.14159)*[2])+(1-[3])*Gaus(x,[1],[4])/(sqrt(2*3.14159)*[4]))",fit_range_low,fit_range_high);
  fit_fun_sgnl->SetParameters(fit_fun->GetParameter(0),fit_fun->GetParameter(1),fit_fun->GetParameter(2),fit_fun->GetParameter(3),fit_fun->GetParameter(4));
  TF1* fit_fun_bg = (TF1*)fit_fun->Clone("fit_fun_bg");
  for(Int_t ipar=0;ipar<9;ipar++)
    {
      fit_fun_bg->SetParameter(ipar,0);
    }
  TF1* fit_fun_swap = new TF1("fit_fun_swap","gausn(0)*([4]/0.01)*(1.0/[3])",fit_range_low,fit_range_high);
  fit_fun_swap->SetParameters(fit_fun->GetParameter(5),fit_fun->GetParameter(6),fit_fun->GetParameter(7),fit_fun->GetParameter(8),fit_fun->GetParameter(0));

  fit_fun_swap->SetFillColor(kGreen+4);
  fit_fun_swap->SetFillStyle(3005);
  fit_fun_swap->SetLineColor(kGreen+4);
  fit_fun_swap->SetLineWidth(3);
  fit_fun_swap->SetLineStyle(1);
  fit_fun_swap->Draw("same");

  fit_fun_bg->SetLineColor(4);
  fit_fun_bg->SetLineWidth(3);
  fit_fun_bg->SetLineStyle(2);
  fit_fun_bg->Draw("same");

  fit_fun_sgnl->SetFillColor(kOrange-3);
  fit_fun_sgnl->SetFillStyle(3002);
  fit_fun_sgnl->SetLineColor(kOrange-3);
  fit_fun_sgnl->SetLineWidth(3);
  fit_fun_sgnl->SetLineStyle(2);
  fit_fun_sgnl->Draw("same");

  fit_fun->SetLineColor(kRed);
  fit_fun->SetLineWidth(2);
  fit_fun->Draw("same");

  histo->SetMarkerStyle(20);
  histo->SetMarkerColor(kBlack);
  histo->SetLineColor(kBlack);
  histo->Draw("samee");

  TLegend* leg = new TLegend(0.62,0.55,0.80,0.85,NULL,"brNDC");
  leg->SetBorderSize(0);
  leg->SetTextSize(0.04);
  leg->SetTextFont(42);
  leg->SetFillStyle(0);
  leg->AddEntry(histo,"Data","pl");
  leg->AddEntry(fit_fun,"Fit","l");
  leg->AddEntry(fit_fun_sgnl,"D^{0}+#bar{D^{#lower[0.2]{0}}} Signal","f");
  leg->AddEntry(fit_fun_bg,"Combinatorial","l");
  leg->AddEntry(fit_fun_swap,"Misid. D^{0}","f");
  leg->Draw("same");
//
//  tex = new TLatex(0.19,0.96,"#scale[1.15]{CMS} Preliminary         PbPb #sqrt{s_{NN}} = 2.76 TeV");
//  tex->SetNDC();
//  tex->SetTextFont(42);
//  tex->SetTextSize(0.043);
//  tex->SetLineWidth(2);
//  tex->Draw();
//
  
  TLatex Tl;
  Tl.SetNDC();
  Tl.SetTextAlign(12);
  Tl.SetTextSize(0.04);
  Tl.SetTextFont(42);
  Tl.DrawLatex(0.18,0.93, "#scale[1.25]{CMS} Preliminary");
  Tl.DrawLatex(0.62,0.93, "PbPb #sqrt{s_{NN}} = 2.76 TeV");

  tex = new TLatex(0.22,0.70,Form("%.1f < p_{T} < %.1f GeV/c",ptmin,ptmax));
  tex->SetNDC();
  tex->SetTextFont(42);
  tex->SetTextSize(0.04);
  tex->SetLineWidth(2);
  tex->Draw();

  tex = new TLatex(0.22,0.80,"Cent. 0-100%");
  tex->SetNDC();
  tex->SetTextFont(42);
  tex->SetTextSize(0.04);
  tex->SetLineWidth(2);
  tex->Draw();

  tex = new TLatex(0.22,0.75,"|y| < 1.0");
  tex->SetNDC();
  tex->SetTextFont(42);
  tex->SetTextSize(0.04);
  tex->SetLineWidth(2);
  tex->Draw();

  TH1F* histo_copy_nofitfun = ( TH1F * ) histo->Clone("histo_copy_nofitfun");
  histo_copy_nofitfun->GetFunction("fit_fun")->Delete();
  histo_copy_nofitfun->Draw("same");

  cfg_sigextforpas_Sep->SaveAs(Form("massfitforpas/sigextforpas_%d_cent0to100.pdf",ipad-6));
  cfg_sigextforpas_Sep->SaveAs(Form("massfitforpas/sigextforpas_%d_cent0to100.png",ipad-6));
}

void drawhist(TH1F* histo, Int_t iptbin, TCanvas* cfg, Int_t ipad)
{
  TGaxis::SetMaxDigits(6);
  cfg->cd(ipad);
  Double_t fit_range_low = eff_fit_range_low_expobkg_ptbin14[iptbin];
  Double_t fit_range_high = eff_fit_range_high_expobkg_ptbin14[iptbin];

  TH1F* hempty  = new TH1F(Form("hempty%d",ipad),"",50,fit_range_low,fit_range_high);
  hempty->GetXaxis()->SetTitle("m_{#piK} (GeV/c^{2})");
  hempty->SetYTitle("Entries / (10 MeV/c^{2})");
  hempty->GetXaxis()->SetTitleOffset(1.0);
  hempty->GetYaxis()->SetTitleOffset(1.8);//different pads
  hempty->GetXaxis()->SetLabelOffset(0.007);
  hempty->GetYaxis()->SetLabelOffset(0.007);
  hempty->GetXaxis()->SetTitleSize(0.04);
  hempty->GetYaxis()->SetTitleSize(0.04);
  hempty->GetXaxis()->SetTitleFont(42);
  hempty->GetYaxis()->SetTitleFont(42);
  hempty->GetXaxis()->SetLabelFont(42);
  hempty->GetYaxis()->SetLabelFont(42);
  hempty->GetXaxis()->SetLabelSize(0.04);
  hempty->GetYaxis()->SetLabelSize(0.04);
  Double_t max = histo->GetMaximum();
  histo->SetMaximum(1.15*max);
  hempty->SetAxisRange(hemptyMin[iptbin],histo->GetMaximum()*1.2,"Y");
  if( iptbin > 10 )  hempty->SetAxisRange(hemptyMin[iptbin],histo->GetMaximum()*1.3,"Y");
  hempty->SetStats(0);
  if(ipad!=6) hempty->Draw();

  Int_t ci = TColor::GetColor("#000099");
  histo->SetLineColor(ci);
  histo->SetMarkerStyle(24);
  histo->SetMarkerSize(0.8);
  histo->SetStats(0);
  if(ipad!=6) histo->Draw("same");

  TF1* fit_fun = histo->GetFunction("fit_fun");
  TF1* fit_fun_sgnl = new TF1("fit_fun_sgnl","[0]*([3]*Gaus(x,[1],[2])/(sqrt(2*3.14159)*[2])+(1-[3])*Gaus(x,[1],[4])/(sqrt(2*3.14159)*[4]))",fit_range_low,fit_range_high);
  fit_fun_sgnl->SetParameters(fit_fun->GetParameter(0),fit_fun->GetParameter(1),fit_fun->GetParameter(2),fit_fun->GetParameter(3),fit_fun->GetParameter(4));
  TF1* fit_fun_bg = (TF1*)fit_fun->Clone("fit_fun_bg");
  for(Int_t ipar=0;ipar<9;ipar++)
    {
      fit_fun_bg->SetParameter(ipar,0);
    }
  TF1* fit_fun_swap = new TF1("fit_fun_swap","gausn(0)*([4]/0.01)*(1.0/[3])",fit_range_low,fit_range_high);
  fit_fun_swap->SetParameters(fit_fun->GetParameter(5),fit_fun->GetParameter(6),fit_fun->GetParameter(7),fit_fun->GetParameter(8),fit_fun->GetParameter(0));

  fit_fun_swap->SetFillColor(kGreen+4);
  fit_fun_swap->SetFillStyle(3005);
  fit_fun_swap->SetLineColor(kGreen+4);
  fit_fun_swap->SetLineWidth(3);
  fit_fun_swap->SetLineStyle(1);
  if(ipad!=6) fit_fun_swap->Draw("same");

  fit_fun_bg->SetLineColor(4);
  fit_fun_bg->SetLineWidth(3);
  fit_fun_bg->SetLineStyle(2);
  if(ipad!=6) fit_fun_bg->Draw("same");

  fit_fun_sgnl->SetFillColor(kOrange-3);
  fit_fun_sgnl->SetFillStyle(3002);
  fit_fun_sgnl->SetLineColor(kOrange-3);
  fit_fun_sgnl->SetLineWidth(3);
  fit_fun_sgnl->SetLineStyle(2);
  if(ipad!=6) fit_fun_sgnl->Draw("same");

  fit_fun->SetLineColor(kRed);
  fit_fun->SetLineWidth(2);
  if(ipad!=6) fit_fun->Draw("same");

  histo->SetMarkerStyle(20);
  histo->SetMarkerColor(kBlack);
  histo->SetLineColor(kBlack);
  if(ipad!=6) histo->Draw("samee");

  Float_t binwidth = histo->GetBinWidth(10);
  Float_t ptbinwidth = ptbins[iptbin+1] - ptbins[iptbin];

  Float_t Nsig = fit_fun->GetParameter(0)/(binwidth);
  Float_t err_Nsig = fit_fun->GetParError(0)/(binwidth);
  Float_t fitmean = fit_fun->GetParameter(1)*1000.;
  Float_t fitmeanerror = fit_fun->GetParError(1)*1000.;
  Float_t fitsigma = ( fit_fun->GetParameter(2) * fit_fun->GetParameter(3) + fit_fun->GetParameter(4) * ( 1.0 -  fit_fun->GetParameter(3) ) ) * 1000;
  Float_t fitsigmaerror = ( fit_fun->GetParError(2) * fit_fun->GetParameter(3) + fit_fun->GetParError(4) * ( 1.0 -  fit_fun->GetParameter(3) ) ) * 1000;

  if(ipad==1)
    {
      TLegend* leg1 = new TLegend(0.10,0.68,0.60,0.83);
      leg1->SetBorderSize(0);
      leg1->SetTextSize(0.05);
      leg1->SetTextFont(42);
      leg1->SetFillStyle(0);
      leg1->AddEntry((TObject*)0,Form("#mu = %.1f #pm %.1f MeV/c^{2}",fitmean,fitmeanerror),"");
      leg1->AddEntry((TObject*)0,Form("N_{sig} = %.1f #pm %.1f",Nsig,err_Nsig),"");
      leg1->Draw("same");
    }
  else if(ipad<6)
    {
      TLegend* legN = new TLegend(0.10,0.68,0.60,0.83);
      legN->SetBorderSize(0);
      legN->SetTextSize(0.05);
      legN->SetTextFont(42);
      legN->SetFillStyle(0);
      legN->AddEntry((TObject*)0,Form("#mu =%.1f #pm %.1f MeV/c^{2}",fitmean,fitmeanerror),"");
      legN->AddEntry((TObject*)0,Form("N_{sig}=%.1f #pm %.1f",Nsig,err_Nsig),"");
      legN->Draw("same");      
    }

  TLegend* leg = new TLegend(0.05,0.25,0.60,0.70,NULL,"brNDC");
  leg->SetBorderSize(0);
  leg->SetTextSize(0.055);
  leg->SetTextFont(42);
  leg->SetFillStyle(0);
  leg->AddEntry(histo,"Data","pl");
  leg->AddEntry(fit_fun,"Fit","l");
  leg->AddEntry(fit_fun_sgnl,"D^{0}+#bar{D^{#lower[0.2]{0}}} Signal","f");
  leg->AddEntry(fit_fun_bg,"Combinatorial","l");
  leg->AddEntry(fit_fun_swap,"Misid. D^{0}","f");
  if(ipad==6) leg->Draw();

  if(ipad==6)
  {
     TLatex Tl;
     Tl.SetNDC();
     Tl.SetTextAlign(12);
     Tl.SetTextSize(0.055);
     Tl.SetTextFont(42);
     Tl.DrawLatex(0.07,0.90, "#scale[1.15]{CMS} Preliminary PbPb #sqrt{s_{NN}} = 2.76 TeV");
     TString centrality;
     centrality.Form("Cent. %d-%d%%", 0,100);
     cout << centrality << endl;
     Tl.DrawLatex(0.07,0.82, centrality);
     Tl.DrawLatex(0.07,0.74, "|y| < 1.0");
  }

  TH1F* histo_copy_nofitfun = ( TH1F * ) histo->Clone("histo_copy_nofitfun");
  histo_copy_nofitfun->GetFunction("fit_fun")->Delete();
  histo_copy_nofitfun->Draw("same");
}

void drawtex(Double_t ptmin, Double_t ptmax, Int_t ipad)
{
  tex = new TLatex(0.225,0.85,Form("%.1f < p_{T} < %.1f GeV/c",ptmin,ptmax));
  tex->SetNDC();
  tex->SetTextFont(42);
  tex->SetTextSize(0.05);
  tex->SetLineWidth(2);
  tex->Draw();
}
