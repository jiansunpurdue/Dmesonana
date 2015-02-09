void Jettrig_ppb_D0eff()
{
	gStyle->SetOptStat(0);
	gStyle->SetOptTitle(0);
	TH1::SetDefaultSumw2();
	TFile * input_pPb_MB = new TFile("rootfiles/Dspectrum_pPb_minbias_histo_ptbin_11_expobkg_Nbin20.root");
    TFile * input_pPb_highpt = new TFile("rootfiles/Dspectrum_pPb_highpt_histo_ptbin_11_expobkg_Nbin20.root");
//    TFile * input_pPb_MB = new TFile("rootfiles/Dspectrum_pPb_minbias_histo_ptbin_14_expobkg_Nbin20.root");
//	TFile * input_pPb_highpt = new TFile("rootfiles/Dspectrum_pPb_highpt_histo_ptbin_14_expobkg_Nbin20.root");

	TH1D * N_mb = (TH1D *) input_pPb_MB->Get("N_mb");
	TH1D * N_Jettrig = (TH1D *) input_pPb_highpt->Get("N_Jettrig");
	TH1D * N_Jet20 = (TH1D *) input_pPb_highpt->Get("N_Jet20");
	TH1D * N_Jet40 = (TH1D *) input_pPb_highpt->Get("N_Jet40");
	TH1D * N_Jet60 = (TH1D *) input_pPb_highpt->Get("N_Jet60");
	TH1D * N_Jet80 = (TH1D *) input_pPb_highpt->Get("N_Jet80");
	TH1D * N_Jet100 = (TH1D *) input_pPb_highpt->Get("N_Jet100");

	TCanvas * cfg = new TCanvas("cfg","cfg",800,800);
	cfg->Divide(2,1);

	cfg->cd(1);
	gPad->SetLogy();

	N_mb->SetLineWidth(2);
	N_Jettrig->SetLineWidth(2);
	N_Jet20->SetLineWidth(2);
	N_Jet40->SetLineWidth(2);
	N_Jet60->SetLineWidth(2);
	N_Jet80->SetLineWidth(2);
	N_Jet100->SetLineWidth(2);

	N_mb->SetLineColor(1);
	N_Jettrig->SetLineColor(4);
	N_Jet20->SetLineColor(2);
	N_Jet40->SetLineColor(3);
	N_Jet60->SetLineColor(6);
	N_Jet80->SetLineColor(7);
    N_Jet100->SetLineColor(50);

	N_mb->SetMinimum(0.00000001);
	N_mb->GetXaxis()->SetTitle("D Meson Pt");
	N_mb->GetYaxis()->SetTitle("dN/dp_{T}");

	N_mb->DrawCopy("ep");
	N_Jettrig->DrawCopy("epsame");
	N_Jet20->DrawCopy("epsame");
	N_Jet40->DrawCopy("epsame");
	N_Jet60->DrawCopy("epsame");
	N_Jet80->DrawCopy("epsame");
	N_Jet100->DrawCopy("epsame");

    TLegend * t = new TLegend(0.5,0.5,0.85,0.85);
    t->SetFillColor(0);
    t->SetTextSize(0.05);
    t->AddEntry(N_mb,"MinBias");
    t->AddEntry(N_Jettrig,"Jet Combined");
    t->AddEntry(N_Jet20,"Jet20");
    t->AddEntry(N_Jet40,"Jet40");
    t->AddEntry(N_Jet60,"Jet60");
    t->AddEntry(N_Jet80,"Jet80");
    t->AddEntry(N_Jet100,"Jet100");

    t->Draw();

	cfg->cd(2);
	N_Jettrig->GetXaxis()->SetTitle("D Meson Pt");
	N_Jettrig->GetYaxis()->SetTitle("*/MinBias");

	N_Jettrig->Divide(N_Jettrig,N_mb,1.0,1.0,"B");
//    N_Jettrig->Divide(N_Jettrig,N_mb,1.0,1.0);
	N_Jet20->Divide(N_Jet20,N_mb,1.0,1.0,"B");
	N_Jet40->Divide(N_Jet40,N_mb,1.0,1.0,"B");
	N_Jet60->Divide(N_Jet60,N_mb,1.0,1.0,"B");
	N_Jet80->Divide(N_Jet80,N_mb,1.0,1.0,"B");
	N_Jet100->Divide(N_Jet100,N_mb,1.0,1.0,"B");

	N_Jettrig->DrawCopy("ep");
	N_Jet20->DrawCopy("epsame");
	N_Jet40->DrawCopy("epsame");
	N_Jet60->DrawCopy("epsame");
	N_Jet80->DrawCopy("epsame");
	N_Jet100->DrawCopy("epsame");

	TCanvas * jettrigeff = new TCanvas("jettrigeff","jettrigeff");
	N_Jettrig->GetXaxis()->SetTitle("D Meson Pt");
	N_Jettrig->GetYaxis()->SetTitle("Trig Eff");
	N_Jettrig->DrawCopy("ep");

	TH1D * Jettrig_eff_ppb = (TH1D *) N_Jettrig->Clone("Jettrig_eff_ppb");

	TFile * output = new TFile("Jettrig_eff_ppb.root","RECREATE");
	Jettrig_eff_ppb->Write();
	jettrigeff->Write();
	cfg->Write();
}
