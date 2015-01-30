#include <TTree.h>
#include <TH1D.h>
#include <TFile.h>
#include <TString.h>
#include <TCut.h>
#include <TCanvas.h>
#include <TF1.h>
#include <TLegend.h>

TString inputdata="/afs/cern.ch/work/w/wangj/public/dmeson/candbase/Dmesonana_PPJet_Jettrig_obj_pt0p5_d0dstar_alpha1p0_highpurity_1209_all_Candbase.root";
TString inputmc="/afs/cern.ch/work/w/wangj/public/dmeson/candbase/Dmesonana_hiforest_D0filtered_2760GeV_D0pt3_pthat015305080120_1220_1222_all_Candbase.root";

TString cutdata="dcandeta>-2.0&&dcandeta<2.0&&dcanddau1pt>0.5&&dcanddau2pt>0.5&&abs(dcandmass-1.864)>0.1&&abs(dcandmass-1.864)<0.15";
TString cutmc="dcandeta>-2.0&&dcandeta<2.0&&dcanddau1pt>0.5&&dcanddau2pt>0.5&&matchedtogen!=0";

void variableLoop(TString var, TString vartitle, double min, double max, int i)
{
  TFile *infData = new TFile(inputdata);
  TTree *ntData = (TTree*) infData->Get("ntDzero");
  TFile *infMC = new TFile(inputmc);
  TTree *ntMC = (TTree*) infMC->Get("ntDzero");

  TCanvas *c = new TCanvas(Form("c%i",i),"",600,600);
  
  TH1D* hSignal = new TH1D("hSignal","",50,min,max);
  TH1D* hBackground = new TH1D("hBackground","",50,min,max);

  ntMC->Project("hSignal",Form("%s",var.Data()),Form("%s",cutmc.Data()));
  ntData->Project("hBackground",Form("%s",var.Data()),Form("%s",cutdata.Data()));

  double normBackground=0,normSignal=0;
  normBackground = hBackground->GetEntries();
  normSignal = hSignal->GetEntries();
  cout<<normBackground<<" "<<normSignal<<endl;
  
  hBackground->Scale(1./normBackground);
  hSignal->Scale(1./normSignal); 

  hBackground->SetXTitle(Form("%s",vartitle.Data()));
  hBackground->SetYTitle("#Probability");
  hBackground->SetTitleOffset(1.5,"Y");
  if(hBackground->GetMaximum()>hSignal->GetMaximum()) hBackground->SetMaximum(hBackground->GetMaximum()*1.2);
  else hBackground->SetMaximum(hSignal->GetMaximum()*1.2);

  hBackground->SetLineColor(kBlue+1);
  hBackground->SetFillStyle(1001);
  hBackground->SetFillColor(kBlue-9);
  hBackground->SetLineWidth(3);
  hBackground->SetStats(0);

  hSignal->SetLineColor(kRed);
  hSignal->SetFillStyle(3004);
  hSignal->SetFillColor(kRed);
  hSignal->SetLineWidth(3);
  hSignal->SetStats(0);

  hBackground->Draw();
  hSignal->Draw("same");
  
  TLegend *leg = new TLegend(0.11,0.75,0.50,0.9);
  leg->AddEntry(hBackground,"Background","f");
  leg->AddEntry(hSignal,"Signal","f");
  leg->SetBorderSize(0);
  leg->SetFillStyle(0);
  leg->Draw("same");
  TLegend *leg1 = new TLegend(0.60,0.7,0.90,0.9);
  leg1->AddEntry((TObject*)0,Form("%s",vartitle.Data()),"");
  leg1->SetBorderSize(0);
  leg1->SetFillStyle(0);
  leg1->Draw("same");

  c->SaveAs(Form("DataMCResult/varcomparison_%s.pdf",var.Data()));
}

void DataMCcomparison()
{
  variableLoop("dcandfchi2", "chi2", 0., 20., 1);
  variableLoop("dcandffls3d", "decay length", 0., 50., 2);
  variableLoop("dcandalpha", "pointing angle", 0., 1., 3);
  variableLoop("dcandfprob", "dcandfprob", 0., 1., 4);
}

