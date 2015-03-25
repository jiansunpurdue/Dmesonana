#include <TTree.h>
#include <TH1D.h>
#include <TFile.h>
#include <TString.h>
#include <TCut.h>
#include <TCanvas.h>
#include <TF1.h>
#include <TLegend.h>

//TString inputdata="/data/dmeson/Ntuple/Dmesonana_Rereco_MBtrig_d0pt4p5_nodalphacuts_pt1p5_tight_3lumi_0131_part1_fortmva.root";
//TString inputdata="/data/dmeson/Ntuple/Dmesonana_Rereco_MBtrig_d0pt3p0_d1p8_pt1p5_v1_tight_1213_6lumi_cuts_noprobchi2cut_vz_v4.root";
TString inputdata="/afs/cern.ch/work/j/jisun/public/Dmesonana/Dmesonana_Rereco_MBtrig_d0pt3p0_nodalphacuts_pt1p5_tight_3lumi_0131_part12_part2_missinglumi.lis_1000To2500.root";
TString inputmc="/data/dmeson/Ntuple/Dmesonana_hiforest_PbPb_Pyquen_D0embedded_D0pt3_pthat015305080_1217_1223_all_vz_v2.root";
TString cutdata="dcandeta>-2.0&&dcandeta<2.0&&dcanddau1pt>1.5&&dcanddau2pt>1.5&&abs(dcandmass-1.864)>0.1&&abs(dcandmass-1.864)<0.15";
TString cutmc="MinBias&&dcandeta>-2.0&&dcandeta<2.0&&dcanddau1pt>1.5&&dcanddau2pt>1.5&&(matchedtogen&&nongendoublecounted)";
TString cutsample="((dcandpt<13.&&dcandffls3d>4.)||(dcandpt>13.&&dcandffls3d>2.))&&dcandcosalpha>0.975&&dcandfchi2>3.";
//TString cutsample="dcandffls3d>4.&&TMath::ACos(dcandcosalpha)<0.5&&dcandfprob>0.05";
Bool_t presample=false;
Float_t ptmin=3.5;
Float_t ptmax=4.5;

void variableLoop(TString var, TString vartitle, TString varname, double min, double max, int i)
{
  TFile *infData = new TFile(inputdata);
  TTree *ntData = (TTree*) infData->Get("recodmesontree");
  TFile *infMC = new TFile(inputmc);
  TTree *ntMC = (TTree*) infMC->Get("recodmesontree");

  TCanvas *c = new TCanvas(Form("c%i",i),"",600,600);
  
  TH1D* hSignal = new TH1D("hSignal","",50,min,max);
  TH1D* hBackground = new TH1D("hBackground","",50,min,max);

  if(presample)
    {
      ntMC->Project("hSignal",Form("%s",var.Data()),Form("dcandpt>%f&&dcandpt<%f&&%s&&%s",ptmin,ptmax,cutmc.Data(),cutsample.Data()));
      ntData->Project("hBackground",Form("%s",var.Data()),Form("dcandpt>%f&&dcandpt<%f&&%s&&%s",ptmin,ptmax,cutdata.Data(),cutsample.Data()));
    }
  else
    {
      ntMC->Project("hSignal",Form("%s",var.Data()),Form("dcandpt>%f&&dcandpt<%f&&%s",ptmin,ptmax,cutmc.Data()));
      ntData->Project("hBackground",Form("%s",var.Data()),Form("dcandpt>%f&&dcandpt<%f&&%s",ptmin,ptmax,cutdata.Data()));
    }
  double normBackground=0,normSignal=0;
  normBackground = hBackground->GetEntries();
  hBackground->Sumw2();
  normSignal = hSignal->GetEntries();
  //cout<<normBackground<<" "<<normSignal<<endl;
  
  hBackground->Scale(1./normBackground);
  //hBackground->Sumw2();
  hSignal->Scale(1./normSignal); 

  hSignal->SetXTitle(Form("%s",vartitle.Data()));
  hSignal->SetYTitle("#Probability");
  hSignal->SetTitleOffset(1.5,"Y");
  if(hBackground->GetMaximum()>hSignal->GetMaximum()) hSignal->SetMaximum(hBackground->GetMaximum()*1.2);
  else hSignal->SetMaximum(hSignal->GetMaximum()*1.2);

  hSignal->SetLineColor(4.0);
  hSignal->SetFillStyle(3345);
  hSignal->SetFillColor(4.0);
  hSignal->SetLineWidth(2);
  hSignal->SetStats(0);

  hBackground->SetLineColor(1.0);
  hBackground->SetMarkerColor(1.0);
  hBackground->SetMarkerStyle(20);
  hBackground->SetMarkerSize(0.8);
  hBackground->SetStats(0);

  hSignal->Draw("");
  //hSignal->Draw("HISTe");
  hBackground->Draw("epsame");

  TLegend* leg1 = new TLegend(0.55,0.75,0.85,0.85);
  leg1->AddEntry((TObject*)0,Form("%.1f<p_{T}<%.1f GeV",ptmin,ptmax),"");
  leg1->AddEntry((TObject*)0,Form("%s",vartitle.Data()),"");
  leg1->SetBorderSize(0);
  leg1->SetFillStyle(0);
  leg1->Draw("same");

  TLegend *leg = new TLegend(0.55,0.65,0.85,0.75);
  leg->AddEntry(hSignal,"Signal","f");
  leg->AddEntry(hBackground,"Background","PL");
  leg->SetBorderSize(0);
  leg->SetFillStyle(0);
  leg->Draw("same");

  c->SaveAs(Form("DataMCResult/ptplots/varcomparison_%s_%.1f_%.1f.pdf",varname.Data(),ptmin,ptmax));
}

void DataMCcomparison()
{
  variableLoop("dcandffls3d", "decay length", "ffls3d", 0., 40., 2);
  variableLoop("TMath::ACos(dcandcosalpha)", "#alpha", "alpha", 0, 3.1416, 3);
  variableLoop("dcandfprob", "dcandfprob", "prob", 0., 1., 4);
}
