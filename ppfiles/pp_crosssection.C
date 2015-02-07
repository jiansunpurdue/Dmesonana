
void pp_crosssection()
{
	gStyle->SetOptStat(0);
	gStyle->SetOptTitle(0);
	TH1::SetDefaultSumw2();
	TFile * input_MC = new TFile("Dspectrum_pp_MC_genmatch_histo_ptbin_11_cuts2p0.root");
	TFile * input_data = new TFile("Dspectrum_pp_histo_ptbin_11_Jet40.root");

	TH1D * N_gendpt = ( TH1D * ) input_MC->Get("N_gendpt");
	TH1D * N_mb_matched = ( TH1D * ) input_MC->Get("N_mb_matched");
	TH1D * N_mb = ( TH1D * ) input_MC->Get("N_mb");

	TH1D * recoeff_matched = ( TH1D * ) N_mb_matched->Clone("recoeff_matched");
	recoeff_matched->Divide(N_mb_matched, N_gendpt, 1.0, 1.0, "B");

	TH1D * recoeff_fitting = ( TH1D * ) N_mb->Clone("recoeff_fitting");
	recoeff_fitting->Divide(N_mb, N_gendpt, 1.0, 1.0, "B");

	TCanvas * recoeff = new TCanvas("recoeff","recoeff");

	recoeff_matched->GetXaxis()->SetRangeUser(5.0,35);
    recoeff_matched->SetLineColor(1.0);
    recoeff_matched->SetMarkerColor(1.0);	
    recoeff_matched->GetXaxis()->SetTitle("D Meson Pt");
    recoeff_matched->GetYaxis()->SetTitle("Reco Eff");
    recoeff_matched->SetMarkerSize(0.8);
    recoeff_matched->SetMarkerStyle(20);
    recoeff_matched->Draw("ep");

    recoeff_fitting->SetLineColor(4.0);
    recoeff_fitting->SetMarkerColor(4.0);	
    recoeff_fitting->GetXaxis()->SetTitle("D Meson Pt");
    recoeff_fitting->GetYaxis()->SetTitle("Reco Eff");
    recoeff_fitting->SetMarkerSize(0.8);
    recoeff_fitting->SetMarkerStyle(20);
	recoeff_fitting->Draw("epsame");

	TH1D * ratio_matched_fitting = ( TH1D *) recoeff_matched->Clone("ratio_matched_fitting");
	ratio_matched_fitting->Divide(N_mb,N_mb_matched,1.0,1.0,"B");


// for data
	TH1D * d0raw_data = ( TH1D * ) input_data->Get("N_Jettrig");
	TH1D * d0raw_data_overeff = ( TH1D * ) d0raw_data->Clone("d0raw_data_overeff");
	d0raw_data_overeff->Divide(recoeff_matched);   // corrected by acceptance * reco eff

    //for triger eff
	TFile * input_trigeff = new TFile("Jettrig_eff_pp_ptbin_11_nocuts.root");
    TH1D * Jettrig_eff_pp = ( TH1D * ) input_trigeff->Get("Jettrig_eff_pp");
	TH1D * d0raw_data_overrecoeff = ( TH1D *) d0raw_data_overeff->Clone("d0raw_data_overrecoeff");
	d0raw_data_overeff->Divide(Jettrig_eff_pp);
//	d0raw_data_overeff->Scale(1./(5.3 * 1.0E6));  // 1/Lpp
    d0raw_data_overeff->Scale(1./5.3);
    d0raw_data_overeff->Scale(1./0.0389);
	d0raw_data_overeff->Scale(1./2.0);
	
	TCanvas *d0spectrum_pbpb = new TCanvas("d0spectrum_pbpb","d0spectrum_pbpb");
	gPad->SetLogy();

    d0raw_data_overeff->SetLineWidth(2.0);
    d0raw_data_overeff->GetXaxis()->SetTitle("D Meson Pt");
    d0raw_data_overeff->GetXaxis()->SetRangeUser(5.,35);
    d0raw_data_overeff->GetYaxis()->SetTitle("d#sigma/dp_{T}");

    d0raw_data_overeff->SetLineColor(4.0);
    d0raw_data_overeff->SetMarkerSize(0.8);
    d0raw_data_overeff->SetMarkerStyle(20);
    d0raw_data_overeff->SetMarkerColor(4.0);
    d0raw_data_overeff->Draw("ep");

	TFile * fonllinput = new TFile("./FONLL/fonll/outputDzero.root");
	TGraphAsymmErrors * d0fonllcrosssection = ( TGraphAsymmErrors *) fonllinput->Get("gaeSigmaDecayDzero");
	d0fonllcrosssection->SetLineWidth(2.0);
	d0fonllcrosssection->Draw("psame");

	TGraphAsymmErrors * d0datafonllscale = ( TGraphAsymmErrors * ) d0fonllcrosssection->Clone("d0datafonllscale");
    double scale =  d0raw_data_overeff->GetBinContent(9)/d0datafonllscale->GetY()[7];
	cout << "scale: " << scale << endl;
	for (int i=0;i<d0datafonllscale->GetN();i++){
		d0datafonllscale->GetY()[i] = d0datafonllscale->GetY()[i] * scale;
		d0datafonllscale->SetPointEYhigh(i,d0datafonllscale->GetErrorYhigh(i)*scale);
		d0datafonllscale->SetPointEYlow(i,d0datafonllscale->GetErrorYlow(i)*scale); 
	}

	d0datafonllscale->SetLineColor(2.0);
	d0datafonllscale->Draw("psame");


    TLatex Tl;
    Tl.SetNDC();
    Tl.SetTextAlign(12);
    Tl.SetTextSize(0.03);
	Tl.DrawLatex(0.3,0.8, "CMS Preliminary, 2013 pp, #sqrt{S_{NN}} = 2.76 TeV");
    Tl.DrawLatex(0.5,0.7, "#left|#eta#right| < 2.0");

	TLegend * t = new TLegend(0.5, 0.4, 0.85, 0.7);
	t->SetFillColor(0);
	t->SetTextSize(0.02);
	t->AddEntry(d0raw_data_overeff,"pp data","LP");
	t->AddEntry(d0fonllcrosssection,"FONLL","LP");
	t->AddEntry(d0datafonllscale,"Scaled FONLL","LP");
	t->Draw();
//	TLegend * t2 = new TLegend(0.5, 0.4, 0.85, 0.5);
//	t2->SetFillColor(0);
//	t2->AddEntry(d0datafonllscale,"FONLL Scaled to data in 20 to 28","LP");
//	t2->Draw();


// end data
//
	TFile * output = new TFile("pp_crosssection_D0_pp_d2p0.root","RECREATE");
	d0fonllcrosssection->Write();
	recoeff->Write();
	recoeff_matched->Write();
	recoeff_fitting->Write();
	ratio_matched_fitting->Write();
	d0spectrum_pbpb->Write();
	d0raw_data->Write();
	d0raw_data_overeff->Write();
	Jettrig_eff_pp->Write();
	d0raw_data_overrecoeff->Write();
}
