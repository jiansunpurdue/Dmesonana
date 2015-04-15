#include <string>
#include <vector>
#include <map>
#include <iostream>
#include <TFile.h>
#include <TH1F.h>
#include <TH2D.h>
#include <TMath.h>
#include <TF1.h>
#include <TNamed.h>
#include <TNtuple.h>
#include <TTree.h>
#include <TMath.h>
#include <TCanvas.h>
#include <TStyle.h>
#include <TLatex.h>
#include "Math/MinimizerOptions.h"

#include "PtBins.h"

#define MAXGENDMESON 100
using namespace std;

bool isPrompt = true;

float hiBin_low = -0.5;
float hiBin_high = 199.5;
double dautrackcut = 1.5;

double lowptedge_d0 = 3.5;
double highptedge_d0 = 40.0;

TH1D* d0genpt_fonllweighted;

TH1D* d0genpt;
TH1D* d0genpt_acceptance;
TH1D* d0candpt_matched;
TH1D* d0candpt_matched_cuts;

TH1D* d0geny;
TH1D* d0geny_acceptance;
TH1D* d0candy_matched;
TH1D* d0candy_matched_cuts;

TH2D* d0genypt;
TH2D* d0genypt_acceptance;
TH2D* d0candypt_matched;
TH2D* d0candypt_matched_cuts;

TH1D* d0ffls3d_matched;

float cut_m_low = 1.70;
float cut_m_high = 2.05;
int massbin = 35;

void book_hist()
{
	TH1::SetDefaultSumw2();

	d0genpt_fonllweighted = new TH1D("d0genpt_fonllweighted","d0genpt_fonllweighted",392,2,100);
	d0genpt_fonllweighted->Sumw2();

	d0genpt = new TH1D("d0genpt","d0genpt", NPT, ptbins);
	d0genpt_acceptance = new TH1D("d0genpt_acceptance","d0genpt_acceptance", NPT, ptbins);
	d0candpt_matched = new TH1D("d0candpt_matched", "d0candpt_matched", NPT, ptbins);
	d0candpt_matched_cuts = new TH1D("d0candpt_matched_cuts", "d0candpt_matched_cuts", NPT, ptbins);
    d0genpt->Sumw2(); d0genpt_acceptance->Sumw2(); d0candpt_matched->Sumw2(); d0candpt_matched_cuts->Sumw2();
   
    d0geny = new TH1D("d0geny","d0geny", NY, ybins);
	d0geny_acceptance = new TH1D("d0geny_acceptance","d0geny_acceptance", NY, ybins);
	d0candy_matched = new TH1D("d0candy_matched","d0candy_matched", NY, ybins);
	d0candy_matched_cuts = new TH1D("d0candy_matched_cuts","d0candy_matched_cuts", NY, ybins);
	d0geny->Sumw2(); d0geny_acceptance->Sumw2(); d0candy_matched->Sumw2(); d0candy_matched_cuts->Sumw2();

	d0genypt = new TH2D( "d0genypt", "d0genypt", NY, ybins, NPT, ptbins);
	d0genypt_acceptance = new TH2D( "d0genypt_acceptance", "d0genypt_acceptance", NY, ybins, NPT, ptbins);
	d0candypt_matched = new TH2D( "d0candypt_matched", "d0candypt_matched", NY, ybins, NPT, ptbins);
	d0candypt_matched_cuts = new TH2D( "d0candypt_matched_cuts", "d0candypt_matched_cuts", NY, ybins, NPT, ptbins);
    d0genypt->Sumw2();  d0genypt_acceptance->Sumw2(); d0candypt_matched->Sumw2(); d0candypt_matched_cuts->Sumw2();

	d0ffls3d_matched = new TH1D("d0ffls3d_matched", "d0ffls3d_matched", 200, 0, 100);
	d0ffls3d_matched->Sumw2();
}

void write_histo( TFile * output)
{
   output->cd();
   d0genpt_fonllweighted->Write();
   d0genpt->Write(); d0genpt_acceptance->Write();  d0candpt_matched->Write();  d0candpt_matched_cuts->Write();
   d0geny->Write();   d0geny_acceptance->Write();  d0candy_matched->Write();   d0candy_matched_cuts->Write();
   d0genypt->Write(); d0genypt_acceptance->Write();  d0candypt_matched->Write();  d0candypt_matched_cuts->Write();
   d0ffls3d_matched->Write();
}

//
//int decideybin( float dy)
//{
//	int iy = -1;
//	for( int i = 0 ; i < NY; i++)
//	{
//		if( dy >= ybins[i] && dy < ybins[i+1] )  { iy = i; break;}
//	}
//	return iy;
//}
//



void decideeffectivecuts(double dpt, double &effectiveffls3dcut, double &effectivecosalphacut, double &effectiveprobcut)
{
    for( int i = 0; i < NCUTPT; i++ )
    {
        if( dpt >= cut_pt_edge[i] && dpt < cut_pt_edge[i+1] )
        {
            effectiveffls3dcut = ffls3dcut[i];
            effectivecosalphacut = TMath::Cos(alphacut[i]);
            effectiveprobcut = fprobcut[i];
            break;
        }
    }
    return;
}

void AcceptanceandRecoEff_match_FONLLweight()
{
    TH1::SetDefaultSumw2();
    
    book_hist();
 
    TFile * input_fonllweight;
    if( isPrompt )
		input_fonllweight = new TFile("D0_PbPb_rawtoFONLL_3to100_prompt.root");
	else
		input_fonllweight = new TFile("D0_PbPb_rawtoFONLL_3to100_Bfeeddown.root");

	TH1D * fonllweight = ( TH1D * ) input_fonllweight->Get("ratio_rawtofonll");

	TFile * input = new TFile("rootfiles/Dmesonana_hiforest_official_PbPbD0tokaonpion_Pt0153050_2760GeV_0323_all_v1.root");
	TTree * recodmesontree = (TTree *) input->Get("recodmesontree");
	TTree * gendmesontree = (TTree *) input->Get("gendmesontree");
	recodmesontree->AddFriend(gendmesontree);

	float pthat;
	int ngend;
	float dpt[MAXGENDMESON];
	float dy[MAXGENDMESON];
	float pt_ddau[MAXGENDMESON][3];
	float eta_ddau[MAXGENDMESON][3];
	float pt_Bmom[MAXGENDMESON];
	gendmesontree->SetBranchAddress("pthat", &pthat);
	gendmesontree->SetBranchAddress("ngend", &ngend);
	gendmesontree->SetBranchAddress("dpt", dpt);
	gendmesontree->SetBranchAddress("dy", dy);
	gendmesontree->SetBranchAddress("pt_ddau", pt_ddau);
	gendmesontree->SetBranchAddress("eta_ddau", eta_ddau);
	gendmesontree->SetBranchAddress("pt_Bmom", pt_Bmom);
    
    int MinBias;
    int MinBias_Prescl;

    int ndcand;
    int hiBin;
    double pthatweight;
    double trigweight;
    vector<int> *dtype = 0, *passingcuts = 0;
    vector<float> *dcandmass = 0, *dcandpt = 0, *dcandeta = 0, *dcandy = 0, *dcandphi = 0, *dcandffls3d = 0, *dcandcosalpha = 0, *dcandfprob = 0, *dcandfchi2 = 0;
    vector<float> *dcanddau1eta = 0, *dcanddau2eta = 0;
	vector<int>   *matchedtogen = 0, *dcandmatchedpdg = 0, *nongendoublecounted = 0;
	vector<float> *dcandmatchedpt = 0, *dcandmatchedeta = 0, *dcandmatchedphi = 0, *dcandmatchnofdau = 0;
	vector<float> *matched_pt_Bmom = 0;

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
    recodmesontree->SetBranchAddress("dcandeta", &dcandeta);
	recodmesontree->SetBranchAddress("dcandy", &dcandy);
    recodmesontree->SetBranchAddress("dcandphi", &dcandphi);
    recodmesontree->SetBranchAddress("dcandffls3d", &dcandffls3d);
    recodmesontree->SetBranchAddress("dcandcosalpha", &dcandcosalpha);
    recodmesontree->SetBranchAddress("dcandfprob", &dcandfprob);
    recodmesontree->SetBranchAddress("dcandfchi2", &dcandfchi2);
	recodmesontree->SetBranchAddress("matchedtogen", &matchedtogen);
	recodmesontree->SetBranchAddress("nongendoublecounted", &nongendoublecounted);
	recodmesontree->SetBranchAddress("dcandmatchedpt", &dcandmatchedpt);
	recodmesontree->SetBranchAddress("dcandmatchedeta", &dcandmatchedeta);
	recodmesontree->SetBranchAddress("dcandmatchedphi", &dcandmatchedphi);
    recodmesontree->SetBranchAddress("dcanddau1eta", &dcanddau1eta);
    recodmesontree->SetBranchAddress("dcanddau2eta", &dcanddau2eta);
	recodmesontree->SetBranchAddress("matched_pt_Bmom", &matched_pt_Bmom);
    
   for ( int entry = 0; entry < recodmesontree->GetEntries(); entry++ )
   {
	   recodmesontree->GetEntry(entry);
	   if( entry % 1000000 == 0 )  cout << entry+1 << "st event" << endl;
	   if( !MinBias ) continue;
	   if( ndcand != dtype->size() || ndcand != passingcuts->size() || ndcand != dcandmass->size() || ndcand != dcandpt->size() )   //check 
		   cout << "Error!!!!!!!!" << endl;
	   if( hiBin < hiBin_low || hiBin > hiBin_high )   continue;

       double weight = -999;
	   
	   for( int igend = 0; igend < ngend; igend++ )
	   {
		   if( dy[igend] < -2.0 || dy[igend] > 2.0 )   continue;

		   if( isPrompt )
			   { if( pt_Bmom[igend] > 0 )   continue; } //tell if is from B feed down or not
		   else
			   { if( pt_Bmom[igend] < 0 )   continue;  }

		   if(  dpt[igend] <  lowptedge_d0 ||  dpt[igend] > highptedge_d0 )   continue;

           weight = fonllweight->GetBinContent( fonllweight->FindBin( dpt[igend] ) );

           d0genpt_fonllweighted->Fill( dpt[igend], weight);
		   d0genpt->Fill( dpt[igend], weight);
		   d0geny->Fill( dy[igend], weight);
		   d0genypt->Fill( dy[igend], dpt[igend], weight);

		   if( pt_ddau[igend][0] > dautrackcut && pt_ddau[igend][1] > dautrackcut )
			   if ( TMath::Abs( eta_ddau[igend][0] ) < 2.4 && TMath::Abs( eta_ddau[igend][1] ) < 2.4 )
			   {
				   d0genpt_acceptance->Fill( dpt[igend], weight);
				   d0geny_acceptance->Fill( dy[igend], weight);
				   d0genypt_acceptance->Fill( dy[igend], dpt[igend], weight);
			   }

	   }

	   for( int icand = 0; icand < ndcand; icand++ )
	   {
		   if( dtype->at(icand) != 2 )   cout << " Error!!!!!!! Just working on D0 now" << endl;
		   
		   if( dcandy->at(icand) < -2.0 || dcandy->at(icand) > 2.0 )   continue;
		   if( TMath::Abs( dcanddau1eta->at(icand) ) > 2.4 || TMath::Abs( dcanddau2eta->at(icand) ) > 2.4 )   continue;

		   if( isPrompt )
			   { if( matched_pt_Bmom->at(icand) > 0 )   continue; }
		   else
			   { if( matched_pt_Bmom->at(icand) < 0 )   continue; }

//		   if( ( dcandpt->at(icand)  <  lowptedge_d0 && dcandmatchedpt->at(icand) < lowptedge_d0 ) || ( dcandpt->at(icand) > highptedge_d0 && dcandmatchedpt->at(icand) > highptedge_d0 ) )   continue;

		   if( dcandmatchedpt->at(icand) < lowptedge_d0  || dcandmatchedpt->at(icand) > highptedge_d0 )   continue;

		   weight = fonllweight->GetBinContent( fonllweight->FindBin( dcandpt->at(icand) ) );

		   if( matchedtogen->at(icand) == 1 && nongendoublecounted->at(icand) == 1)
		   {
			   d0candpt_matched->Fill( dcandmatchedpt->at(icand), weight);
			   d0candy_matched->Fill( dcandy->at(icand), weight);
			   d0candypt_matched->Fill( dcandy->at(icand), dcandmatchedpt->at(icand), weight);
			   d0ffls3d_matched->Fill( dcandffls3d->at(icand), weight);
		   }

           double effectiveffls3dcut = 100000.;
           double effectivecosalphacut = 2.0;
           double effectiveprobcut = -1.0;

           decideeffectivecuts(dcandpt->at(icand), effectiveffls3dcut, effectivecosalphacut, effectiveprobcut);
//         if( dcandpt->at(icand) > 7.0 )
//         cout << "dcandpt: " << dcandpt->at(icand) << "  " << effectiveffls3dcut << "  " << effectiveprobcut << endl;

           if( dcandffls3d->at(icand) < effectiveffls3dcut || dcandcosalpha->at(icand) < effectivecosalphacut || dcandfprob->at(icand) < effectiveprobcut )
               continue;
//           if( dcandffls3d->at(icand) < effectiveffls3dcut || dcandfprob->at(icand) < effectiveprobcut )
//			   continue;

		   if( matchedtogen->at(icand) == 1 && nongendoublecounted->at(icand) == 1)
		   {
			   d0candpt_matched_cuts->Fill( dcandmatchedpt->at(icand), weight);
			   d0candy_matched_cuts->Fill( dcandy->at(icand), weight);
			   d0candypt_matched_cuts->Fill( dcandy->at(icand), dcandmatchedpt->at(icand), weight);
		   }
	   }
   }

   gStyle->SetOptFit(0);
   gStyle->SetOptStat(0);
   gStyle->SetOptTitle(0);
   gStyle->SetHistMinimumZero(kTRUE);

//   TCanvas * cfg_d0acceptance_pt = new TCanvas("cfg_d0acceptance_pt","cfg_d0acceptance_pt");
//   TH1D * d0acceptance_pt = (TH1D *) d0genpt_acceptance->Clone("d0acceptance_pt");
//   d0acceptance_pt->Divide(d0genpt_acceptance, d0genpt, 1.0, 1.0, "B");
//   d0acceptance_pt->SetLineWidth(2.0);
//   d0acceptance_pt->GetYaxis()->SetTitle("Acceptance");
//   d0acceptance_pt->GetXaxis()->SetRangeUser(4.0, 38);
//   d0acceptance_pt->GetXaxis()->SetTitle("D0 p_{T} (GeV/c)");
//   d0acceptance_pt->Draw("EP");
//
//   TCanvas * cfg_d0acceptance_y = new TCanvas("cfg_d0acceptance_y","cfg_d0acceptance_y");
//   TH1D * d0acceptance_y = (TH1D *) d0geny_acceptance->Clone("d0acceptance_y");
//   d0acceptance_y->Divide(d0geny_acceptance, d0geny, 1.0, 1.0, "B");
//   d0acceptance_y->SetLineWidth(2.0);
//   d0acceptance_y->GetYaxis()->SetTitle("Acceptance");
//   d0acceptance_y->GetXaxis()->SetTitle("y");
//   d0acceptance_y->Draw("EP");
//
//   TCanvas * cfg_d0acceptance_ypt = new TCanvas("cfg_d0acceptance_ypt","cfg_d0acceptance_ypt");
//   TH2D * d0acceptance_ypt = ( TH2D *) d0genypt_acceptance->Clone("d0acceptance_ypt");
//   d0acceptance_ypt->Divide(d0genypt_acceptance, d0genypt, 1.0, 1.0, "B");
//   d0acceptance_ypt->GetXaxis()->SetTitle("y");
//   d0acceptance_ypt->GetYaxis()->SetRangeUser(4.0, 38);
//   d0acceptance_ypt->GetYaxis()->SetTitle("D0 p_{T} (GeV/c)");
//   d0acceptance_ypt->Draw("COLZ");
//
//   TCanvas * cfg_d0efficiency_pt = new TCanvas("cfg_d0efficiency_pt","cfg_d0efficiency_pt");
//   TH1D * d0efficiency_pt = (TH1D *) d0candpt_matched_cuts->Clone("d0efficiency_pt");
//   d0efficiency_pt->Divide(d0candpt_matched_cuts, d0genpt_acceptance, 1.0, 1.0, "B");
//   d0efficiency_pt->SetLineWidth(2.0);
//   d0efficiency_pt->GetYaxis()->SetTitle("Efficiency");
//   d0efficiency_pt->GetXaxis()->SetRangeUser(4.0, 38);
//   d0efficiency_pt->GetXaxis()->SetTitle("D0 p_{T} (GeV/c)");
//   d0efficiency_pt->Draw("EP");
//
//   TCanvas * cfg_d0efficiency_y = new TCanvas("cfg_d0efficiency_y","cfg_d0efficiency_y");
//   TH1D * d0efficiency_y = (TH1D *) d0candy_matched_cuts->Clone("d0efficiency_y");
//   d0efficiency_y->Divide(d0candy_matched_cuts, d0geny_acceptance, 1.0, 1.0, "B");
//   d0efficiency_y->SetLineWidth(2.0);
//   d0efficiency_y->GetYaxis()->SetTitle("Efficiency");
//   d0efficiency_y->GetXaxis()->SetTitle("y");
//   d0efficiency_y->Draw("EP");
//
//   TCanvas * cfg_d0efficiency_ypt = new TCanvas("cfg_d0efficiency_ypt","cfg_d0efficiency_ypt");
//   TH2D * d0efficiency_ypt = ( TH2D *) d0candypt_matched_cuts->Clone("d0efficiency_ypt");
//   d0efficiency_ypt->Divide(d0candypt_matched_cuts, d0genypt_acceptance, 1.0, 1.0, "B");
//   d0efficiency_ypt->GetXaxis()->SetTitle("y");
//   d0efficiency_ypt->GetYaxis()->SetRangeUser(4.0, 38);
//   d0efficiency_ypt->GetYaxis()->SetTitle("D0 p_{T} (GeV/c)");
//   d0efficiency_ypt->Draw("COLZ");
//   
//
//
   TCanvas * cfg_d0tkefficiency_pt = new TCanvas("cfg_d0tkefficiency_pt","cfg_d0tkefficiency_pt");
   TH1D * d0tkefficiency_pt = (TH1D *) d0candpt_matched->Clone("d0tkefficiency_pt");
   d0tkefficiency_pt->Divide(d0candpt_matched, d0genpt, 1.0, 1.0, "B");
   d0tkefficiency_pt->SetLineWidth(2.0);
   d0tkefficiency_pt->GetYaxis()->SetTitle("#alpha #times #varepsilon_{reco}");
   d0tkefficiency_pt->GetXaxis()->SetRangeUser(4.0, 38);
   d0tkefficiency_pt->GetXaxis()->SetTitle("D0 p_{T} (GeV/c)");
   d0tkefficiency_pt->Draw("EP");

   TCanvas * cfg_d0tkefficiency_y = new TCanvas("cfg_d0tkefficiency_y","cfg_d0tkefficiency_y");
   TH1D * d0tkefficiency_y = (TH1D *) d0candy_matched->Clone("d0tkefficiency_y");
   d0tkefficiency_y->Divide(d0candy_matched, d0geny, 1.0, 1.0, "B");
   d0tkefficiency_y->SetLineWidth(2.0);
   d0tkefficiency_y->GetYaxis()->SetTitle("#alpha #times #varepsilon_{reco}");
   d0tkefficiency_y->GetXaxis()->SetTitle("y");
   d0tkefficiency_y->Draw("EP");

   TCanvas * cfg_d0tkefficiency_ypt = new TCanvas("cfg_d0tkefficiency_ypt","cfg_d0tkefficiency_ypt");
   TH2D * d0tkefficiency_ypt = ( TH2D *) d0candypt_matched->Clone("d0tkefficiency_ypt");
   d0tkefficiency_ypt->Divide(d0candypt_matched, d0genypt, 1.0, 1.0, "B");
   d0tkefficiency_ypt->GetXaxis()->SetTitle("y");
   d0tkefficiency_ypt->GetYaxis()->SetRangeUser(4.0, 38);
   d0tkefficiency_ypt->GetYaxis()->SetTitle("D0 p_{T} (GeV/c)");
   d0tkefficiency_ypt->Draw("COLZ");

   TCanvas * cfg_d0efficiency2_pt = new TCanvas("cfg_d0efficiency2_pt","cfg_d0efficiency2_pt");
   TH1D * d0efficiency_pt = (TH1D *) d0candpt_matched_cuts->Clone("d0efficiency_pt");
   d0efficiency_pt->Divide(d0candpt_matched_cuts, d0candpt_matched, 1.0, 1.0, "B");
   d0efficiency_pt->SetLineWidth(2.0);
   d0efficiency_pt->GetYaxis()->SetTitle("#varepsilon_{cuts}");
   d0efficiency_pt->GetXaxis()->SetRangeUser(4.0, 38);
   d0efficiency_pt->GetXaxis()->SetTitle("D0 p_{T} (GeV/c)");
   d0efficiency_pt->Draw("EP");

   TCanvas * cfg_d0efficiency2_y = new TCanvas("cfg_d0efficiency2_y","cfg_d0efficiency2_y");
   TH1D * d0efficiency_y = (TH1D *) d0candy_matched_cuts->Clone("d0efficiency_y");
   d0efficiency_y->Divide(d0candy_matched_cuts, d0candy_matched, 1.0, 1.0, "B");
   d0efficiency_y->SetLineWidth(2.0);
   d0efficiency_y->GetYaxis()->SetTitle("#varepsilon_{cuts}");
   d0efficiency_y->GetXaxis()->SetTitle("y");
   d0efficiency_y->Draw("EP");

   TCanvas * cfg_d0efficiency2_ypt = new TCanvas("cfg_d0efficiency2_ypt","cfg_d0efficiency2_ypt");
   TH2D * d0efficiency_ypt = ( TH2D *) d0candypt_matched_cuts->Clone("d0efficiency_ypt");
   d0efficiency_ypt->Divide(d0candypt_matched_cuts, d0candypt_matched, 1.0, 1.0, "B");
   d0efficiency_ypt->GetXaxis()->SetTitle("y");
   d0efficiency_ypt->GetYaxis()->SetRangeUser(4.0, 38);
   d0efficiency_ypt->GetYaxis()->SetTitle("D0 p_{T} (GeV/c)");
   d0efficiency_ypt->Draw("COLZ");

   TCanvas * cfg_d0accxeff_pt = new TCanvas("cfg_d0accxeff_pt","cfg_d0accxeff_pt");
   TH1D * d0accxeff_pt = (TH1D *) d0candpt_matched_cuts->Clone("d0accxeff_pt");
   d0accxeff_pt->Divide(d0candpt_matched_cuts, d0genpt, 1.0, 1.0, "B");
   d0accxeff_pt->SetLineWidth(2.0);
   d0accxeff_pt->GetYaxis()->SetTitle("#alpha #times #varepsilon_{reco} #times #varepsilon_{cuts}");
   d0accxeff_pt->GetXaxis()->SetRangeUser(4.0, 38);
   d0accxeff_pt->GetXaxis()->SetTitle("D0 p_{T} (GeV/c)");
   d0accxeff_pt->Draw("EP");

   TCanvas * cfg_d0accxeff_y = new TCanvas("cfg_d0accxeff_y","cfg_d0accxeff_y");
   TH1D * d0accxeff_y = (TH1D *) d0candy_matched_cuts->Clone("d0accxeff_y");
   d0accxeff_y->Divide(d0candy_matched_cuts, d0geny, 1.0, 1.0, "B");
   d0accxeff_y->SetLineWidth(2.0);
   d0accxeff_y->GetYaxis()->SetTitle("#alpha #times #varepsilon_{reco} #times #varepsilon_{cuts}");
   d0accxeff_y->GetXaxis()->SetTitle("y");
   d0accxeff_y->Draw("EP");

   TCanvas * cfg_d0accxeff_ypt = new TCanvas("cfg_d0accxeff_ypt","cfg_d0accxeff_ypt");
   TH2D * d0accxeff_ypt = ( TH2D *) d0candypt_matched_cuts->Clone("d0accxeff_ypt");
   d0accxeff_ypt->Divide(d0candypt_matched_cuts, d0genypt, 1.0, 1.0, "B");
   d0accxeff_ypt->GetXaxis()->SetTitle("y");
   d0accxeff_ypt->GetYaxis()->SetRangeUser(4.0, 38);
   d0accxeff_ypt->GetYaxis()->SetTitle("D0 p_{T} (GeV/c)");
   d0accxeff_ypt->Draw("COLZ");
   
	
//	   cfg_d0acceptance_pt->SaveAs("plots/acceptandeff/D0_PbPb_acceptance_pt.pdf");
//	   cfg_d0acceptance_pt->SaveAs("plots/acceptandeff/D0_PbPb_acceptance_pt.png");
//	   cfg_d0acceptance_y->SaveAs("plots/acceptandeff/D0_PbPb_acceptance_y.pdf");
//	   cfg_d0acceptance_y->SaveAs("plots/acceptandeff/D0_PbPb_acceptance_y.png");
//	   cfg_d0acceptance_ypt->SaveAs("plots/acceptandeff/D0_PbPb_acceptance_ypt.pdf");
//	   cfg_d0acceptance_ypt->SaveAs("plots/acceptandeff/D0_PbPb_acceptance_ypt.png");
//	   cfg_d0efficiency_pt->SaveAs("plots/acceptandeff/D0_PbPb_efficiency_pt.pdf");
//	   cfg_d0efficiency_pt->SaveAs("plots/acceptandeff/D0_PbPb_efficiency_pt.png");
//	   cfg_d0efficiency_y->SaveAs("plots/acceptandeff/D0_PbPb_efficiency_y.pdf");
//	   cfg_d0efficiency_y->SaveAs("plots/acceptandeff/D0_PbPb_efficiency_y.png");
//	   cfg_d0efficiency_ypt->SaveAs("plots/acceptandeff/D0_PbPb_efficiency_ypt.pdf");
//	   cfg_d0efficiency_ypt->SaveAs("plots/acceptandeff/D0_PbPb_efficiency_ypt.png");

       cfg_d0tkefficiency_pt->SaveAs("plots/acceptandeff/D0_PbPb_tkefficiency_pt.pdf");
	   cfg_d0tkefficiency_pt->SaveAs("plots/acceptandeff/D0_PbPb_tkefficiency_pt.png");
	   cfg_d0tkefficiency_y->SaveAs("plots/acceptandeff/D0_PbPb_tkefficiency_y.pdf");
	   cfg_d0tkefficiency_y->SaveAs("plots/acceptandeff/D0_PbPb_tkefficiency_y.png");
	   cfg_d0tkefficiency_ypt->SaveAs("plots/acceptandeff/D0_PbPb_tkefficiency_ypt.pdf");
	   cfg_d0tkefficiency_ypt->SaveAs("plots/acceptandeff/D0_PbPb_tkefficiency_ypt.png");

	   cfg_d0efficiency2_pt->SaveAs("plots/acceptandeff/D0_PbPb_efficiency2_pt.pdf");
	   cfg_d0efficiency2_pt->SaveAs("plots/acceptandeff/D0_PbPb_efficiency2_pt.png");
	   cfg_d0efficiency2_y->SaveAs("plots/acceptandeff/D0_PbPb_efficiency2_y.pdf");
	   cfg_d0efficiency2_y->SaveAs("plots/acceptandeff/D0_PbPb_efficiency2_y.png");
	   cfg_d0efficiency2_ypt->SaveAs("plots/acceptandeff/D0_PbPb_efficiency2_ypt.pdf");
	   cfg_d0efficiency2_ypt->SaveAs("plots/acceptandeff/D0_PbPb_efficiency2_ypt.png");

	   cfg_d0accxeff_pt->SaveAs("plots/acceptandeff/D0_PbPb_accxeff_pt.pdf");
	   cfg_d0accxeff_pt->SaveAs("plots/acceptandeff/D0_PbPb_accxeff_pt.png");
	   cfg_d0accxeff_y->SaveAs("plots/acceptandeff/D0_PbPb_accxeff_y.pdf");
	   cfg_d0accxeff_y->SaveAs("plots/acceptandeff/D0_PbPb_accxeff_y.png");
	   cfg_d0accxeff_ypt->SaveAs("plots/acceptandeff/D0_PbPb_accxeff_ypt.pdf");
	   cfg_d0accxeff_ypt->SaveAs("plots/acceptandeff/D0_PbPb_accxeff_ypt.png");


   char outputfile[200];
   if( isPrompt )
	   sprintf(outputfile,"D0_PbPb_acc_eff_ptbin_%d_ybin_%d_prompt_FONLLweight_cent%2.0fto%2.0f.root", NPT, NY, hiBin_low * 0.5, hiBin_high * 0.5);
   else
	   sprintf(outputfile,"D0_PbPb_acc_eff_ptbin_%d_ybin_%d_Bfeeddown_FONLLweight_cent%2.0fto%2.0f.root", NPT, NY, hiBin_low * 0.5, hiBin_high * 0.5);

   TFile * output = new TFile(outputfile,"RECREATE");
   write_histo( output );
//   cfg_d0acceptance_pt->Write();
//   cfg_d0acceptance_y->Write();
//   cfg_d0acceptance_ypt->Write();
//   cfg_d0efficiency_pt->Write();
//   cfg_d0efficiency_y->Write();
//   cfg_d0efficiency_ypt->Write();
   cfg_d0tkefficiency_pt->Write();
   cfg_d0tkefficiency_y->Write();
   cfg_d0tkefficiency_ypt->Write();
   cfg_d0efficiency2_pt->Write();
   cfg_d0efficiency2_y->Write();
   cfg_d0efficiency2_ypt->Write();
   cfg_d0accxeff_pt->Write();
   cfg_d0accxeff_y->Write();
   cfg_d0accxeff_ypt->Write();

   d0tkefficiency_pt->Write();
   d0tkefficiency_y->Write();
   d0tkefficiency_ypt->Write();

   d0efficiency_ypt->Write();
   d0efficiency_y->Write();
   d0efficiency_pt->Write();

   d0accxeff_pt->Write();
   d0accxeff_y->Write();
   d0accxeff_ypt->Write();
   output->Close();

}

