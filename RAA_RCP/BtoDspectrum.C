#define BIN_NUM 392
#define HMIN 2      //pPb_pt:5,pPb_y:-2,pp_pt:9,pp_y:0
#define HMAX 100     //pPb_pt:55,pPb_y:2,pp_pt:120,pp_y:2.25

#define REBIN 10     //pPb_pt:6,pPb_y:4,pp_pt:8,pp_y:4
#define REBINp 11    //pPb_pt:7,pPb_y:5,pp_pt:9,pp_y:5

void BtoDspectrum()
{
    gStyle->SetOptTitle(0);
    gStyle->SetOptStat(0);
    TH1::SetDefaultSumw2();

	TFile * input = new TFile("BtoD_cent0to100.root");

	TH1D * BtoD_max_raa = (TH1D *)input->Get("hDFromBPtMax");
	TH1D * BtoD_central_raa = (TH1D *)input->Get("hDFromBPtCentral");
	TH1D * BtoD_min_raa = (TH1D *)input->Get("hDFromBPtMin");

	BtoD_max_raa->Scale(0.5);
	BtoD_central_raa->Scale(0.5);
	BtoD_min_raa->Scale(0.5);

	cout << " bin width: " << BtoD_max_raa->GetBinWidth(10) << "    " << BtoD_central_raa->GetBinWidth(10) << "   " << BtoD_min_raa->GetBinWidth(10) << endl;

    double bin_edge[BIN_NUM+1];

    for( int i = 0; i < BIN_NUM+1; i++ )
    {
		bin_edge[i] = 2.0 + 0.25 * i; //0.25 is the binwidth of BtoD_max_raa
    }

	TH1D * BtoD_max_raa_rebin = (TH1D *) BtoD_max_raa->Rebin(BIN_NUM, "BtoD_max_raa_rebin", bin_edge);
	TH1D * BtoD_central_raa_rebin = (TH1D *) BtoD_central_raa->Rebin(BIN_NUM, "BtoD_central_raa_rebin", bin_edge);
	TH1D * BtoD_min_raa_rebin = (TH1D *) BtoD_min_raa->Rebin(BIN_NUM, "BtoD_min_raa_rebin", bin_edge);

	TCanvas * cfg_fonllBtoD = new TCanvas("cfg_fonllBtoD","cfg_fonllBtoD");
	gPad->SetLogy();
	BtoD_max_raa_rebin->Draw();
	BtoD_central_raa_rebin->Draw("same");
	BtoD_min_raa_rebin->Draw("same");

    //Rebin Edge
    double rebin[REBINp] = {3.5,4.5,5.5,7,9,11,13,16,20,28,40};
  
    TH1F* hpt_rebin = (TH1F*)BtoD_central_raa_rebin->Rebin(REBIN,"hpt_rebin",rebin);
    TH1F* hminall_rebin = (TH1F*)BtoD_min_raa_rebin->Rebin(REBIN,"hminall_rebin",rebin);
    TH1F* hmaxall_rebin = (TH1F*)BtoD_max_raa_rebin->Rebin(REBIN,"hmaxall_rebin",rebin);
  
    //bin middle
    double apt[REBIN] = {4,5,6.25,8,10,12,14.5,18,24,34};//pPb_pt
    //bin half width
    double aptl[REBIN] = {0.5,0.5,0.75,1,1,1,1.5,2,4,6};//pPb_pt
    double asigma[REBIN],aminall[REBIN],amaxall[REBIN],aerrorl[REBIN],aerrorh[REBIN];
    //number of every rebined bin
    double bin_num[REBIN] = {4,4,6,8,8,8,12,16,32,48};//pPb_pt
  
    for( int j=0;j<REBIN;j++)
    {
		float tem;
  
        tem = hpt_rebin->GetBinContent(j+1);
        asigma[j] = tem/bin_num[j];
  
        tem = hminall_rebin->GetBinContent(j+1);
        aminall[j] = tem/bin_num[j];
  
        tem = hmaxall_rebin->GetBinContent(j+1);
        amaxall[j] = tem/bin_num[j];

		aerrorl[j] = asigma[j]-aminall[j];//all,sc,mass,pdf
		aerrorh[j] = amaxall[j]-asigma[j];//all,sc,mass,pdf
	}

	TGraphAsymmErrors* gaeSigmaBtoD = new TGraphAsymmErrors(REBIN, apt, asigma, aptl, aptl, aerrorl, aerrorh);

	TFile* promptfonllinput = new TFile("./../FONLL/fonll/outputDzero.root");
	TGraphAsymmErrors * d0fonllspectrum = ( TGraphAsymmErrors *) promptfonllinput->Get("gaeSigmaDzero");

	TCanvas * cfg_BtoDrebin = new TCanvas("cfg_BtoDrebin","cfg_BtoDrebin");
    gPad->SetLogy();

    gaeSigmaBtoD->GetXaxis()->SetRangeUser(3.5, 40);
	gaeSigmaBtoD->GetYaxis()->SetRangeUser(1e1, 1e9);
	gaeSigmaBtoD->GetXaxis()->SetTitle("D^{0} p_{T} (GeV/c)");
	gaeSigmaBtoD->GetYaxis()->SetTitle("d#sigma/dp_{T}(D^{0}) (pb b GeV-1c)");
	gaeSigmaBtoD->SetLineWidth(0.5);
	gaeSigmaBtoD->SetMarkerStyle(20);
	gaeSigmaBtoD->SetMarkerSize(0.8);
	gaeSigmaBtoD->SetMarkerColor(4.0);
	gaeSigmaBtoD->SetLineColor(4.0);
	gaeSigmaBtoD->Draw("AP");
//
//    d0fonllspectrum->SetLineWidth(0.5);
//	d0fonllspectrum->SetMarkerStyle(20);
//	d0fonllspectrum->SetMarkerSize(0.8);
//	d0fonllspectrum->SetMarkerColor(1.0);
//	d0fonllspectrum->SetLineColor(1.0);
//	d0fonllspectrum->Draw("Psame");
//
    TLegend * t = new TLegend(0.35, 0.75, 0.85, 0.85);
    t->SetFillColor(0);
//    t->AddEntry(d0fonllspectrum, "FONLL Prompt D^{0}", "PL");
    t->AddEntry(gaeSigmaBtoD, "FONLL B Feed-down D^{0} with RAA Scale", "PL");
    t->Draw();    
  
}
