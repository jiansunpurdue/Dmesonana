void Jettrig_pp_D0eff()
{
	gStyle->SetOptStat(0);
	gStyle->SetOptTitle(0);
	TH1::SetDefaultSumw2();
//	TFile * input = new TFile("Dspectrum_pp_MC_genmatch_histo_ptbin_16_trigeff_nocuts_spike.root");
    TFile * input = new TFile("Dspectrum_pp_MC_genmatch_histo_ptbin_11_trigeff_nocuts_spike.root");

	TH1D * N_mb_matched = (TH1D *) input->Get("N_mb_matched");
	TH1D * N_Jettrig_matched = (TH1D *) input->Get("N_Jettrig_matched");
	TH1D * N_Jet20_matched = (TH1D *) input->Get("N_Jet20_matched");
	TH1D * N_Jet40_matched = (TH1D *) input->Get("N_Jet40_matched");
	TH1D * N_Jet60_matched = (TH1D *) input->Get("N_Jet60_matched");
	TH1D * N_Jet80_matched = (TH1D *) input->Get("N_Jet80_matched");
	TH1D * N_Jet100_matched = (TH1D *) input->Get("N_Jet100_matched");

	TCanvas * cfg = new TCanvas("cfg","cfg",800,800);
	cfg->Divide(2,1);

	cfg->cd(1);
	gPad->SetLogy();

	N_mb_matched->SetLineWidth(2);
	N_Jettrig_matched->SetLineWidth(2);
	N_Jet20_matched->SetLineWidth(2);
	N_Jet40_matched->SetLineWidth(2);
	N_Jet60_matched->SetLineWidth(2);
	N_Jet80_matched->SetLineWidth(2);
	N_Jet100_matched->SetLineWidth(2);

	N_mb_matched->SetLineColor(1);
	N_Jettrig_matched->SetLineColor(4);
	N_Jet20_matched->SetLineColor(2);
	N_Jet40_matched->SetLineColor(3);
	N_Jet60_matched->SetLineColor(6);
	N_Jet80_matched->SetLineColor(7);
    N_Jet100_matched->SetLineColor(50);

	N_mb_matched->SetMinimum(0.00000001);
	N_mb_matched->GetXaxis()->SetTitle("D Meson Pt");
	N_mb_matched->GetYaxis()->SetTitle("dN/dp_{T}");

	N_mb_matched->DrawCopy("ep");
	N_Jettrig_matched->DrawCopy("epsame");
	N_Jet20_matched->DrawCopy("epsame");
	N_Jet40_matched->DrawCopy("epsame");
	N_Jet60_matched->DrawCopy("epsame");
	N_Jet80_matched->DrawCopy("epsame");
	N_Jet100_matched->DrawCopy("epsame");

    TLegend * t = new TLegend(0.5,0.5,0.85,0.85);
    t->SetFillColor(0);
    t->SetTextSize(0.05);
    t->AddEntry(N_mb_matched,"MinBias");
    t->AddEntry(N_Jettrig_matched,"Jet Combined");
    t->AddEntry(N_Jet20_matched,"Jet20");
    t->AddEntry(N_Jet40_matched,"Jet40");
    t->AddEntry(N_Jet60_matched,"Jet60");
    t->AddEntry(N_Jet80_matched,"Jet80");
    t->AddEntry(N_Jet100_matched,"Jet100");

    t->Draw();

	cfg->cd(2);
	N_Jettrig_matched->GetXaxis()->SetTitle("D Meson Pt");
	N_Jettrig_matched->GetYaxis()->SetTitle("*/MinBias");

	N_Jettrig_matched->Divide(N_Jettrig_matched,N_mb_matched,1.0,1.0,"B");
	N_Jet20_matched->Divide(N_Jet20_matched,N_mb_matched,1.0,1.0,"B");
	N_Jet40_matched->Divide(N_Jet40_matched,N_mb_matched,1.0,1.0,"B");
	N_Jet60_matched->Divide(N_Jet60_matched,N_mb_matched,1.0,1.0,"B");
	N_Jet80_matched->Divide(N_Jet80_matched,N_mb_matched,1.0,1.0,"B");
	N_Jet100_matched->Divide(N_Jet100_matched,N_mb_matched,1.0,1.0,"B");

	N_Jettrig_matched->DrawCopy("ep");
	N_Jet20_matched->DrawCopy("epsame");
	N_Jet40_matched->DrawCopy("epsame");
	N_Jet60_matched->DrawCopy("epsame");
	N_Jet80_matched->DrawCopy("epsame");
	N_Jet100_matched->DrawCopy("epsame");

	TCanvas * jettrigeff = new TCanvas("jettrigeff","jettrigeff");
	N_Jettrig_matched->GetXaxis()->SetTitle("D Meson Pt");
	N_Jettrig_matched->GetYaxis()->SetTitle("Trig Eff");
	N_Jettrig_matched->DrawCopy("ep");

	TH1D * Jettrig_eff_pp = (TH1D *) N_Jettrig_matched->Clone("Jettrig_eff_pp");

	TFile * output = new TFile("Jettrig_eff_pp.root","RECREATE");
	Jettrig_eff_pp->Write();
	jettrigeff->Write();
	cfg->Write();
}
