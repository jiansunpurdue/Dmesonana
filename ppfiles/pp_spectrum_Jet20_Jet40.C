
void pp_spectrum_Jet20_Jet40()
{
	gStyle->SetOptStat(0);
	gStyle->SetOptTitle(0);
	TH1::SetDefaultSumw2();
	TFile * input_MC = new TFile("Dspectrum_pp_MC_genmatch_histo_ptbin_11_y2p0_d2p0.root");
	TFile * input_data = new TFile("Dspectrum_pp_histo_ptbin_11_y2p0_d2p0_Jet40.root");

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
	
	TH1D * d0raw_data_Jet40 = ( TH1D * ) input_data->Get("N_Jettrig_Jet40");
	TH1D * d0raw_data_overeff_Jet40 = ( TH1D * ) d0raw_data_Jet40->Clone("d0raw_data_overeff_Jet40");

	d0raw_data_overeff->Divide(recoeff_matched);   // corrected by acceptance * reco eff
    d0raw_data_overeff_Jet40->Divide(recoeff_matched);

    //for triger eff
	TFile * input_trigeff = new TFile("Jettrig_eff_pp_nocuts_y2p0.root");
//    TFile * input_trigeff = new TFile("Jettrig_eff_pp_cuts_0p5.root");

    TH1D * Jettrig_eff_pp = ( TH1D * ) input_trigeff->Get("Jettrig_eff_pp");
	TH1D * d0raw_data_overrecoeff = ( TH1D *) d0raw_data_overeff->Clone("d0raw_data_overrecoeff");
	d0raw_data_overeff->Divide(Jettrig_eff_pp);

	TH1D * Jettrig_eff_pp_Jet40 = ( TH1D * ) input_trigeff->Get("Jettrig_eff_pp_Jet40");
	d0raw_data_overeff_Jet40->Divide(Jettrig_eff_pp_Jet40);
	
	d0raw_data_overeff->Scale(1./5.43);
//    d0raw_data_overeff->Scale(1./3.21313);
	d0raw_data_overeff->Scale(1./0.0388);
	d0raw_data_overeff_Jet40->Scale(1./5.43);
//    d0raw_data_overeff_Jet40->Scale(1./3.21313);
	d0raw_data_overeff_Jet40->Scale(1./0.0388);

	d0raw_data_overeff->Scale(1./2.0);
	d0raw_data_overeff_Jet40->Scale(1./2.0);
	
	TCanvas *d0spectrum_pbpb = new TCanvas("d0spectrum_pbpb","d0spectrum_pbpb");
//	d0spectrum_pbpb->Divide(1,2);
//	d0spectrum_pbpb->cd(1);
    TPad *pad1 = new TPad("pad1","top pad",0.0,0.3,1.0,1.0);
    pad1->Draw();
    TPad *pad2 = new TPad("pad2","bottom pad",0.0,0.0,1.0,0.3);
    pad2->Draw();

    pad1->cd();
	gPad->SetLogy();

    d0raw_data_overeff->GetXaxis()->SetTitle("D Meson Pt");
    d0raw_data_overeff->GetXaxis()->SetRangeUser(5.,35);
    d0raw_data_overeff->GetYaxis()->SetTitle("d#sigma/dp_{T}");

    d0raw_data_overeff->SetLineColor(4.0);
    d0raw_data_overeff->SetMarkerSize(0.8);
    d0raw_data_overeff->SetMarkerStyle(20);
    d0raw_data_overeff->SetMarkerColor(4.0);
    d0raw_data_overeff->SetLineWidth(2.0);
    d0raw_data_overeff->Draw("ep");

    d0raw_data_overeff_Jet40->SetLineColor(8.0);
    d0raw_data_overeff_Jet40->SetMarkerSize(0.8);
    d0raw_data_overeff_Jet40->SetMarkerStyle(20);
    d0raw_data_overeff_Jet40->SetMarkerColor(8.0);
    d0raw_data_overeff_Jet40->SetLineWidth(2.0);
    d0raw_data_overeff_Jet40->Draw("epsame");

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
  //      d0datafonllscale->Draw("pssame");

    
	TLatex Tl;
    Tl.SetNDC();
    Tl.SetTextAlign(12);
    Tl.SetTextSize(0.03);
	Tl.DrawLatex(0.3,0.8, "CMS Preliminary, 2013 pp, #sqrt{s_{NN}} = 2.76 TeV");
    Tl.DrawLatex(0.5,0.7, "#left|y#right| < 2.0");

	TLegend * t = new TLegend(0.55, 0.5, 0.85, 0.7);
	t->SetFillColor(0);
	t->SetTextSize(0.03);
	t->AddEntry(d0raw_data_overeff,"pp data Jet20","LP");
	t->AddEntry(d0raw_data_overeff_Jet40,"pp data Jet40","LP");
	t->AddEntry(d0fonllcrosssection, "FONLL", "LP");
//	t->AddEntry(d0datafonllscale, "Scaled FONLL", "LP");
	t->Draw();
//	TLegend * t2 = new TLegend(0.5, 0.4, 0.85, 0.5);
//	t2->SetFillColor(0);
//	t2->AddEntry(d0datafonllscale,"FONLL Scaled to data in 20 to 28","LP");
//	t2->Draw();
    
//	d0spectrum_pbpb->cd(2);
    pad2->cd();

	TH1D * d0dateoverfonll = (TH1D *) d0raw_data_overeff->Clone("d0dateoverfonll");
    TH1D * d0dateoverfonll_Jet40 =  (TH1D *) d0raw_data_overeff_Jet40->Clone("d0dateoverfonll_Jet40");

	for( int i = 0; i < d0fonllcrosssection->GetN(); i++ )
	{
		d0dateoverfonll->SetBinContent( i+2, d0dateoverfonll->GetBinContent(i+2) / d0fonllcrosssection->GetY()[i] );
		d0dateoverfonll->SetBinError( i+2, d0dateoverfonll->GetBinError(i+2) / d0fonllcrosssection->GetY()[i] );

		d0dateoverfonll_Jet40->SetBinContent( i+2, d0dateoverfonll_Jet40->GetBinContent(i+2) / d0fonllcrosssection->GetY()[i] );
		d0dateoverfonll_Jet40->SetBinError( i+2, d0dateoverfonll_Jet40->GetBinError(i+2) / d0fonllcrosssection->GetY()[i] );
	}


	TGraphAsymmErrors * d0fonllratio = ( TGraphAsymmErrors * ) d0fonllcrosssection->Clone("d0fonllratio");

	for (int i=0;i<d0fonllratio->GetN();i++){
		double middlevalue = d0fonllcrosssection->GetY()[i];
		d0fonllratio->GetY()[i] = 1.0;
		d0fonllratio->SetPointEYhigh(i,d0fonllratio->GetErrorYhigh(i) / middlevalue);
		d0fonllratio->SetPointEYlow(i,d0fonllratio->GetErrorYlow(i) / middlevalue);
	}

	TGraphAsymmErrors * d0datafonllscaleoverfonll = ( TGraphAsymmErrors * ) d0datafonllscale->Clone("d0datafonllscaleoverfonll");
	for( int i=0; i < d0datafonllscaleoverfonll->GetN() ; i++ ){
    	double fonllmiddlevalue = d0fonllcrosssection->GetY()[i];
		d0datafonllscaleoverfonll->GetY()[i] = d0datafonllscale->GetY()[i]/fonllmiddlevalue;
    	d0datafonllscaleoverfonll->SetPointEYhigh(i,d0datafonllscaleoverfonll->GetErrorYhigh(i) / fonllmiddlevalue);
    	d0datafonllscaleoverfonll->SetPointEYlow(i,d0datafonllscaleoverfonll->GetErrorYlow(i) / fonllmiddlevalue);
	}

    d0dateoverfonll->GetYaxis()->SetTitle("*/FONLL");
	d0dateoverfonll->GetYaxis()->SetRangeUser(0,2.0);
	d0dateoverfonll->Draw("ep");
	d0dateoverfonll_Jet40->Draw("epsame");
    d0fonllratio->Draw("psame");
//	d0datafonllscaleoverfonll->Draw("pssame");

	


// end data
//
	TFile * output = new TFile("pp_xsection_D0_pp_d2p0_Jet40.root","RECREATE");
	recoeff->Write();
	recoeff_matched->Write();
	recoeff_fitting->Write();
	ratio_matched_fitting->Write();
	d0spectrum_pbpb->Write();
	d0raw_data->Write();
	d0raw_data_overeff->Write();
	d0raw_data_overeff_Jet40->Write();
	Jettrig_eff_pp->Write();
	d0raw_data_overrecoeff->Write();
}
