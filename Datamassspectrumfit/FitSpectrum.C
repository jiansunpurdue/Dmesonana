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
#include <TLegend.h>
#include "Math/MinimizerOptions.h"

#include "./../PtBins.h"
#include "FitFunction_expobkg.C"
#include "FitFunction_poly2bkg.C"
#include "FitFunction_linearbkg.C"
#include "FitFunction_expobkg_floatwidth.C"
	
TH1F * hfg_minbias[15];

int rapidityrange = 2;

bool evtunprescaleMB = false;

void drawcfg( int cent_low, int cent_high, int cfg_N_row, int cfg_N_column)
{

	char hname[100];
	char cfgname[200];
	
	//expobkg bkg default fit
	TH1F * hfg_minbias_expobkg[15];
    for( int i = 0; i < NPT; i++ )
    {
        sprintf(hname, "hfg_minbias_expobkg_%d", i);
        hfg_minbias_expobkg[i] = ( TH1F * ) hfg_minbias[i]->Clone(hname);
    }

	TH1D * N_mb_expobkg = new TH1D("N_mb_expobkg","N_mb_expobkg",NPT,ptbins);
	N_mb_expobkg->Sumw2();
	TH1D * N_mb_expobkg_count = new TH1D("N_mb_expobkg_count","N_mb_expobkg_count",NPT,ptbins);
	N_mb_expobkg_count->Sumw2();
    TH1F * hfg_massmean_expobkg = new TH1F( "hfg_massmean_expobkg", "hfg_massmean_expobkg", NPT, ptbins);
    hfg_massmean_expobkg->Sumw2();
    TH1F * hfg_masssigma_expobkg = new TH1F("hfg_masssigma_expobkg","hfg_masssigma_expobkg",NPT, ptbins);
    hfg_masssigma_expobkg->Sumw2();
	TCanvas* cfg_mb_expobkg; 
	if( NPT == 12 ) 
		cfg_mb_expobkg = new TCanvas("cfg_mb_expobkg", "cfg_mb_expobkg", 700, 900);
	else
		cfg_mb_expobkg = new TCanvas("cfg_mb_expobkg", "cfg_mb_expobkg", 700, 600);
	cfg_mb_expobkg->Divide(cfg_N_row, cfg_N_column);
    
	for ( int i = 1; i < NPT -1 ; i++ )
//    for ( int i = 1; i < 3; i++ )
		fit_hist_expobkg( hfg_minbias_expobkg[i], cfg_mb_expobkg, i, N_mb_expobkg, N_mb_expobkg_count, hfg_massmean_expobkg, hfg_masssigma_expobkg, cent_low, cent_high);

//	return;
	
	sprintf(cfgname,"plots/D0_PbPb_data_ptbin_%d_ptd_unpreMBtrig_%d_cent%dto%d_expobkg_doublegauss.pdf",NPT, evtunprescaleMB, cent_low, cent_high);
	cfg_mb_expobkg->SaveAs(cfgname);
	sprintf(cfgname,"plots/D0_PbPb_data_ptbin_%d_ptd_unpreMBtrig_%d_cent%dto%d_expobkg_doublegauss.gif",NPT, evtunprescaleMB, cent_low, cent_high);
	cfg_mb_expobkg->SaveAs(cfgname);


	//poly2 bkg fit
	TH1F * hfg_minbias_poly2bkg[15];
    for( int i = 0; i < NPT; i++ )
    {
        sprintf(hname, "hfg_minbias_poly2bkg_%d", i);
        hfg_minbias_poly2bkg[i] = ( TH1F * ) hfg_minbias[i]->Clone(hname);
    }

	TH1D * N_mb_poly2bkg = new TH1D("N_mb_poly2bkg","N_mb_poly2bkg",NPT,ptbins);
	N_mb_poly2bkg->Sumw2();
    TH1F * hfg_massmean_poly2bkg = new TH1F( "hfg_massmean_poly2bkg", "hfg_massmean_poly2bkg", NPT, ptbins);
    hfg_massmean_poly2bkg->Sumw2();
    TH1F * hfg_masssigma_poly2bkg = new TH1F("hfg_masssigma_poly2bkg","hfg_masssigma_poly2bkg",NPT, ptbins);
    hfg_masssigma_poly2bkg->Sumw2();
	TCanvas* cfg_mb_poly2bkg; 
	if( NPT == 12 ) 
		cfg_mb_poly2bkg = new TCanvas("cfg_mb_poly2bkg", "cfg_mb_poly2bkg", 700, 900);
	else
		cfg_mb_poly2bkg = new TCanvas("cfg_mb_poly2bkg", "cfg_mb_poly2bkg", 700, 600);
	cfg_mb_poly2bkg->Divide(cfg_N_row, cfg_N_column);
   
    for ( int i = 1; i < NPT -1 ; i++ )
		fit_hist_poly2bkg( hfg_minbias_poly2bkg[i], cfg_mb_poly2bkg, i, N_mb_poly2bkg, hfg_massmean_poly2bkg, hfg_masssigma_poly2bkg, cent_low, cent_high);

	sprintf(cfgname,"plots/D0_PbPb_data_ptbin_%d_ptd_unpreMBtrig_%d_cent%dto%d_poly2bkg_doublegauss.pdf",NPT, evtunprescaleMB, cent_low, cent_high);
	cfg_mb_poly2bkg->SaveAs(cfgname);
	sprintf(cfgname,"plots/D0_PbPb_data_ptbin_%d_ptd_unpreMBtrig_%d_cent%dto%d_poly2bkg_doublegauss.gif",NPT, evtunprescaleMB, cent_low, cent_high);
	cfg_mb_poly2bkg->SaveAs(cfgname);



	//linear bkg fit
	TH1F * hfg_minbias_linearbkg[15];
    for( int i = 0; i < NPT; i++ )
    {
        sprintf(hname, "hfg_minbias_linearbkg_%d", i);
        hfg_minbias_linearbkg[i] = ( TH1F * ) hfg_minbias[i]->Clone(hname);
    }

	TH1D * N_mb_linearbkg = new TH1D("N_mb_linearbkg","N_mb_linearbkg",NPT,ptbins);
	N_mb_linearbkg->Sumw2();
    TH1F * hfg_massmean_linearbkg = new TH1F( "hfg_massmean_linearbkg", "hfg_massmean_linearbkg", NPT, ptbins);
    hfg_massmean_linearbkg->Sumw2();
    TH1F * hfg_masssigma_linearbkg = new TH1F("hfg_masssigma_linearbkg","hfg_masssigma_linearbkg",NPT, ptbins);
    hfg_masssigma_linearbkg->Sumw2();
	TCanvas* cfg_mb_linearbkg; 
	if( NPT == 12 ) 
		cfg_mb_linearbkg = new TCanvas("cfg_mb_linearbkg", "cfg_mb_linearbkg", 700, 900);
	else
		cfg_mb_linearbkg = new TCanvas("cfg_mb_linearbkg", "cfg_mb_linearbkg", 700, 600);
	cfg_mb_linearbkg->Divide(cfg_N_row, cfg_N_column);
    
	for ( int i = 1; i < NPT -1 ; i++ )
		fit_hist_linearbkg( hfg_minbias_linearbkg[i], cfg_mb_linearbkg, i, N_mb_linearbkg, hfg_massmean_linearbkg, hfg_masssigma_linearbkg, cent_low, cent_high);

	sprintf(cfgname,"plots/D0_PbPb_data_ptbin_%d_ptd_unpreMBtrig_%d_cent%dto%d_linearbkg_doublegauss.pdf",NPT, evtunprescaleMB, cent_low, cent_high);
	cfg_mb_linearbkg->SaveAs(cfgname);
	sprintf(cfgname,"plots/D0_PbPb_data_ptbin_%d_ptd_unpreMBtrig_%d_cent%dto%d_linearbkg_doublegauss.gif",NPT, evtunprescaleMB, cent_low, cent_high);
	cfg_mb_linearbkg->SaveAs(cfgname);

	
	//expobkg_floatwidth bkg float width
	TH1F * hfg_minbias_expobkg_floatwidth[15];
    for( int i = 0; i < NPT; i++ )
    {
        sprintf(hname, "hfg_minbias_expobkg_floatwidth_%d", i);
        hfg_minbias_expobkg_floatwidth[i] = ( TH1F * ) hfg_minbias[i]->Clone(hname);
    }

	TH1D * N_mb_expobkg_floatwidth = new TH1D("N_mb_expobkg_floatwidth","N_mb_expobkg_floatwidth",NPT,ptbins);
	N_mb_expobkg_floatwidth->Sumw2();
    TH1F * hfg_massmean_expobkg_floatwidth = new TH1F( "hfg_massmean_expobkg_floatwidth", "hfg_massmean_expobkg_floatwidth", NPT, ptbins);
    hfg_massmean_expobkg_floatwidth->Sumw2();
    TH1F * hfg_masssigma_expobkg_floatwidth = new TH1F("hfg_masssigma_expobkg_floatwidth","hfg_masssigma_expobkg_floatwidth", NPT, ptbins);
    hfg_masssigma_expobkg_floatwidth->Sumw2();
	TH1F * hfg_fitalpha_expobkg_floatwidth = new TH1F("hfg_fitalpha_expobkg_floatwidth", "hfg_fitalpha_expobkg_floatwidth", NPT, ptbins);
	hfg_fitalpha_expobkg_floatwidth->Sumw2();
	
	TCanvas* cfg_mb_expobkg_floatwidth; 
	if( NPT == 12 ) 
		cfg_mb_expobkg_floatwidth = new TCanvas("cfg_mb_expobkg_floatwidth", "cfg_mb_expobkg_floatwidth", 700, 900);
	else
		cfg_mb_expobkg_floatwidth = new TCanvas("cfg_mb_expobkg_floatwidth", "cfg_mb_expobkg_floatwidth", 700, 600);
	cfg_mb_expobkg_floatwidth->Divide(cfg_N_row, cfg_N_column);
    
	for ( int i = 1; i < NPT -1 ; i++ )
		fit_hist_expobkg_floatwidth( hfg_minbias_expobkg_floatwidth[i], cfg_mb_expobkg_floatwidth, i, N_mb_expobkg_floatwidth, hfg_massmean_expobkg_floatwidth, hfg_masssigma_expobkg_floatwidth, cent_low, cent_high, hfg_fitalpha_expobkg_floatwidth);

	sprintf(cfgname,"plots/D0_PbPb_data_ptbin_%d_ptd_unpreMBtrig_%d_cent%dto%d_expobkg_floatwidth_doublegauss.pdf",NPT, evtunprescaleMB, cent_low, cent_high);
	cfg_mb_expobkg_floatwidth->SaveAs(cfgname);
	sprintf(cfgname,"plots/D0_PbPb_data_ptbin_%d_ptd_unpreMBtrig_%d_cent%dto%d_expobkg_floatwidth_doublegauss.gif",NPT, evtunprescaleMB, cent_low, cent_high);
	cfg_mb_expobkg_floatwidth->SaveAs(cfgname);




	char outputfile[200];
	sprintf(outputfile,"rootfiles/Dspectrum_pbpb_data_ptbin_%d_ptd_unpreMBtrig_%d_cent%dto%d.root", NPT, evtunprescaleMB, cent_low, cent_high);
	TFile * output = new TFile(outputfile,"RECREATE");
	N_mb_expobkg->Write();
	N_mb_expobkg_count->Write();
	cfg_mb_expobkg->Write();
	hfg_massmean_expobkg->Write();
	hfg_masssigma_expobkg->Write();
    for( int i = 0; i < NPT; i++ )
        hfg_minbias_expobkg[i]->Write();

	N_mb_poly2bkg->Write();
	cfg_mb_poly2bkg->Write();
	hfg_massmean_poly2bkg->Write();
	hfg_masssigma_poly2bkg->Write();
    for( int i = 0; i < NPT; i++ )
        hfg_minbias_poly2bkg[i]->Write();

	N_mb_linearbkg->Write();
	cfg_mb_linearbkg->Write();
	hfg_massmean_linearbkg->Write();
	hfg_masssigma_linearbkg->Write();
    for( int i = 0; i < NPT; i++ )
        hfg_minbias_linearbkg[i]->Write();

	N_mb_expobkg_floatwidth->Write();
	cfg_mb_expobkg_floatwidth->Write();
	hfg_massmean_expobkg_floatwidth->Write();
	hfg_masssigma_expobkg_floatwidth->Write();
	hfg_fitalpha_expobkg_floatwidth->Write();
    for( int i = 0; i < NPT; i++ )
        hfg_minbias_expobkg_floatwidth[i]->Write();

	output->Close();


}

void Gethisto( TFile * input)
{
	char hname[100];

	for( int i = 0; i < NPT; i++ )
	{
		sprintf(hname, "hfg_minbias_%d", i);
		hfg_minbias[i] = ( TH1F * ) input->Get(hname);
	}
	return;

}

void FitSpectrum()
{
	TH1::SetDefaultSumw2();
	gStyle->SetOptTitle(1);
	gStyle->SetOptStat(0);
	gStyle->SetTitleX(0.1f);
	gStyle->SetTitleW(0.8f);
	gStyle->SetTitleFontSize(0.06);

	TFile * input;
	TFile * output;
	int cent_low;
	int cent_high; 
	int cfg_N_row;
	int cfg_N_column;

	input = new TFile("./rootfiles/Masshisto_data_ptbin_12_ptd_unpreMBtrig_0_cent-0to100.root");
	Gethisto( input );
    for ( int i = 1; i < NPT -1 ; i++ )
	{
		if( hfg_minbias[i]->GetFunction("fit_fun") )
			hfg_minbias[i]->GetFunction("fit_fun")->Delete();
	}

    cfg_N_row = 3;
	cfg_N_column = 4;
	cent_low = 0;
	cent_high = 100;
	drawcfg( cent_low, cent_high, cfg_N_row, cfg_N_column);


	input = new TFile("./rootfiles/Masshisto_data_ptbin_12_ptd_unpreMBtrig_0_cent-0to10.root");
	Gethisto( input );
    for ( int i = 1; i < NPT -1 ; i++ )
	{
		if( hfg_minbias[i]->GetFunction("fit_fun") )
			hfg_minbias[i]->GetFunction("fit_fun")->Delete();
	}

    cfg_N_row = 3;
	cfg_N_column = 4;
	cent_low = 0;
	cent_high = 10;
	drawcfg( cent_low, cent_high, cfg_N_row, cfg_N_column);

//
//	input = new TFile("./rootfiles/Masshisto_data_ptbin_12_ptd_unpreMBtrig_0_cent-0to20.root");
//	Gethisto( input );
//    for ( int i = 1; i < NPT -1 ; i++ )
//	{
//		if( hfg_minbias[i]->GetFunction("fit_fun") )
//			hfg_minbias[i]->GetFunction("fit_fun")->Delete();
//	}
//
//    cfg_N_row = 3;
//	cfg_N_column = 4;
//	cent_low = 0;
//	cent_high = 20;
//	drawcfg( cent_low, cent_high, cfg_N_row, cfg_N_column);
//
//
//	input = new TFile("./rootfiles/Masshisto_data_ptbin_7_ptd_unpreMBtrig_0_cent-0to10.root");
//	Gethisto( input );
//    for ( int i = 1; i < NPT -1 ; i++ )
//	{
//		if( hfg_minbias[i]->GetFunction("fit_fun") )
//			hfg_minbias[i]->GetFunction("fit_fun")->Delete();
//	}
//
//    cfg_N_row = 3;
//	cfg_N_column = 2;
//	cent_low = 0;
//	cent_high = 10;
//	drawcfg( cent_low, cent_high, cfg_N_row, cfg_N_column);
//
//
//	input = new TFile("./rootfiles/Masshisto_data_ptbin_7_ptd_unpreMBtrig_0_cent10to30.root");
//	Gethisto( input );
//    for ( int i = 1; i < NPT -1 ; i++ )
//	{
//		if( hfg_minbias[i]->GetFunction("fit_fun") )
//			hfg_minbias[i]->GetFunction("fit_fun")->Delete();
//	}
//
//    cfg_N_row = 3;
//	cfg_N_column = 2;
//	cent_low = 10;
//	cent_high = 30;
//	drawcfg( cent_low, cent_high, cfg_N_row, cfg_N_column);
//
//
//	input = new TFile("./rootfiles/Masshisto_data_ptbin_7_ptd_unpreMBtrig_0_cent30to50.root");
//	Gethisto( input );
//    for ( int i = 1; i < NPT -1 ; i++ )
//	{
//		if( hfg_minbias[i]->GetFunction("fit_fun") )
//			hfg_minbias[i]->GetFunction("fit_fun")->Delete();
//	}
//
//    cfg_N_row = 3;
//	cfg_N_column = 2;
//	cent_low = 30;
//	cent_high = 50;
//	drawcfg( cent_low, cent_high, cfg_N_row, cfg_N_column);
//
//
//	input = new TFile("./rootfiles/Masshisto_data_ptbin_7_ptd_unpreMBtrig_0_cent50to100.root");
//	Gethisto( input );
//    for ( int i = 1; i < NPT -1 ; i++ )
//	{
//		if( hfg_minbias[i]->GetFunction("fit_fun") )
//			hfg_minbias[i]->GetFunction("fit_fun")->Delete();
//	}
//
//    cfg_N_row = 3;
//	cfg_N_column = 2;
//	cent_low = 50;
//	cent_high = 100;
//	drawcfg( cent_low, cent_high, cfg_N_row, cfg_N_column);
//
}
