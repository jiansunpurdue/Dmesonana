void Draw_prompt_Bfeeddown_eff()
{
    gStyle->SetOptStat(0);
	gStyle->SetOptTitle(0);
	TH1::SetDefaultSumw2();

	TFile * input_prompt = new TFile("./../D0_PbPb_acc_eff_ptbin_12_ybin_6_prompt_FONLLweight_cent-0to100.root");
	TH1D * d0tkefficiency_pt_prompt = ( TH1D * ) input_prompt->Get("d0tkefficiency_pt");
	TH1D * d0efficiency_pt_prompt = ( TH1D * ) input_prompt->Get("d0efficiency_pt");
	TH1D * d0accxeff_pt_prompt = ( TH1D * ) input_prompt->Get("d0accxeff_pt");

	TFile * input_Bfeeddown = new TFile("./../D0_PbPb_acc_eff_ptbin_12_ybin_6_Bfeeddown_FONLLweight_cent-0to100.root");
	TH1D * d0tkefficiency_pt_Bfeeddown = ( TH1D * ) input_Bfeeddown->Get("d0tkefficiency_pt");
	TH1D * d0efficiency_pt_Bfeeddown = ( TH1D * ) input_Bfeeddown->Get("d0efficiency_pt");
	TH1D * d0accxeff_pt_Bfeeddown = ( TH1D * ) input_Bfeeddown->Get("d0accxeff_pt");

	TCanvas * cfg_tkeff = new TCanvas("cfg_tkeff","cfg_tkeff");
	d0tkefficiency_pt_prompt->GetYaxis()->SetRangeUser(0, 0.7);
	d0tkefficiency_pt_prompt->Draw();
	d0tkefficiency_pt_Bfeeddown->SetLineColor(2.0);
	d0tkefficiency_pt_Bfeeddown->Draw("same");

    TLegend * t = new TLegend(0.45, 0.25, 0.75, 0.45);
    t->SetFillColor(0);
    t->AddEntry(d0tkefficiency_pt_prompt, "Prompt D^{0}");
    t->AddEntry(d0tkefficiency_pt_Bfeeddown,"Non-prompt D^{0}");
    t->Draw();

	TCanvas * cfg_cuteff = new TCanvas("cfg_cuteff","cfg_cuteff");
	d0efficiency_pt_prompt->GetYaxis()->SetRangeUser(0, 1.0);
	d0efficiency_pt_prompt->Draw();
	d0efficiency_pt_Bfeeddown->SetLineColor(2.0);
	d0efficiency_pt_Bfeeddown->Draw("same");

    TLegend * t = new TLegend(0.45, 0.25, 0.75, 0.45);
    t->SetFillColor(0);
    t->AddEntry(d0efficiency_pt_prompt, "Prompt D^{0}");
    t->AddEntry(d0efficiency_pt_Bfeeddown,"Non-prompt D^{0}");
    t->Draw();

	TCanvas * cfg_accxeff = new TCanvas("cfg_accxeff","cfg_accxeff");
	
	TPad *pad1 = new TPad("pad1","top pad",0.0,0.3,1.0,1.0);
	pad1->Draw();
	TPad *pad2 = new TPad("pad2","bottom pad",0.0,0.0,1.0,0.3);
	pad2->Draw();

	pad1->cd();
	d0accxeff_pt_prompt->GetYaxis()->SetRangeUser(0, 0.5);
	d0accxeff_pt_prompt->Draw();
	d0accxeff_pt_Bfeeddown->SetLineColor(2.0);
	d0accxeff_pt_Bfeeddown->Draw("same");

    TLegend * t = new TLegend(0.45, 0.25, 0.75, 0.45);
    t->SetFillColor(0);
    t->AddEntry(d0accxeff_pt_prompt, "Prompt D^{0}");
    t->AddEntry(d0accxeff_pt_Bfeeddown,"Non-prompt D^{0}");
    t->Draw();

	pad2->cd();
	TH1D * ratio_d0accxeff_BtoD_prompt = (TH1D *) d0accxeff_pt_Bfeeddown->Clone("ratio_d0accxeff_BtoD_prompt");
	ratio_d0accxeff_BtoD_prompt->Divide(d0accxeff_pt_prompt);
	ratio_d0accxeff_BtoD_prompt->GetYaxis()->SetRangeUser(0.5, 2.0);
	ratio_d0accxeff_BtoD_prompt->GetYaxis()->SetTitleOffset(0.6);
	ratio_d0accxeff_BtoD_prompt->GetYaxis()->SetLabelSize(0.07);
	ratio_d0accxeff_BtoD_prompt->GetXaxis()->SetLabelSize(0.07);
	ratio_d0accxeff_BtoD_prompt->GetYaxis()->SetTitleSize(0.08);
	ratio_d0accxeff_BtoD_prompt->GetYaxis()->SetTitle("Ratio to Prompt");
	ratio_d0accxeff_BtoD_prompt->Draw();

    TH1D * ffls3d_prompt = ( TH1D * ) input_prompt->Get("d0ffls3d_matched");
	TH1D * ffls3d_Bfeeddown = ( TH1D * ) input_Bfeeddown->Get("d0ffls3d_matched");
	TCanvas * cfg_ffls3d = new TCanvas("cfg_ffls3d","cfg_ffls3d");

	ffls3d_prompt->Scale(1.0/ffls3d_prompt->Integral(0, -1));
	ffls3d_Bfeeddown->Scale(1.0/ffls3d_Bfeeddown->Integral(0, -1));

	ffls3d_prompt->SetLineWidth(2.0);
	ffls3d_Bfeeddown->SetLineWidth(2.0);

    ffls3d_prompt->GetXaxis()->SetRangeUser(0,40);
	ffls3d_prompt->GetXaxis()->SetTitle("Decay Length Sig");
	ffls3d_prompt->GetYaxis()->SetTitle("Probability");
	ffls3d_prompt->Draw();
	ffls3d_Bfeeddown->SetLineColor(2.0);
	ffls3d_Bfeeddown->Draw("same");

    TLegend * t = new TLegend(0.45, 0.45, 0.75, 0.75);
    t->SetFillColor(0);
    t->AddEntry(ffls3d_prompt, "Prompt D^{0}");
    t->AddEntry(ffls3d_Bfeeddown,"Non-prompt D^{0}");
    t->Draw();

	cfg_ffls3d->SaveAs("plots/D0_mathced_ffls3d_prompt_Bfeeddown_fonllptweight.pdf");
	cfg_ffls3d->SaveAs("plots/D0_mathced_ffls3d_prompt_Bfeeddown_fonllptweight.png");

	cfg_tkeff->SaveAs("plots/D0_PbPb_tkeff_prompt_Feeddown_fonllptweight.pdf");
	cfg_tkeff->SaveAs("plots/D0_PbPb_tkeff_prompt_Feeddown_fonllptweight.png");
	cfg_cuteff->SaveAs("plots/D0_PbPb_cuteff_default_prompt_Feeddown_fonllptweight.pdf");
	cfg_cuteff->SaveAs("plots/D0_PbPb_cuteff_default_prompt_Feeddown_fonllptweight.png");
	cfg_accxeff->SaveAs("plots/D0_PbPb_accxeff_default_prompt_Feeddown_fonllptweight.pdf");
	cfg_accxeff->SaveAs("plots/D0_PbPb_accxeff_default_prompt_Feeddown_fonllptweight.png");

}
