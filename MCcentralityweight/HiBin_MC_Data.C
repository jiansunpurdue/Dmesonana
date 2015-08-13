void HiBin_MC_Data()
{
    TH1::SetDefaultSumw2();

	TFile * input_mc = new TFile("/home/sun229/DmesonAna/sl6ana/v2_pbpb_08062015/CMSSW_5_3_24/src/UserCode/OpenHF/Dmesonana/Dmesonanarooffiles/Dmesonana_hiforest_PbPbD0tokaonpion_Pthat0153050_D0pt1p0_tkpt1p0eta1p1_2760GeV_0803_onlymatched.root");
	TFile * input_data = new TFile("/home/sun229/store/v2_analysisfiles/Dmesonana_Rereco_MBtrig_hfcandv2_d0pt1p0_tk1p0_etacut_tight_d2p0_alpha0p2_prob0p05_6lumi_0804_all.root");

	TTree * recotree_mc = (TTree *) input_mc->Get("recodmesontree");
	TTree * recotree_data = (TTree *) input_data->Get("recodmesontree");

	TH1D * h_hiBin_mc = new TH1D("h_hiBin_mc","h_hiBin_mc", 40, 0, 200);
	TH1D * h_hiBin_data = new TH1D("h_hiBin_data","h_hiBin_data", 40, 0, 200);

//    recotree_mc->Draw("hiBin>>h_hiBin_mc");
	recotree_mc->Draw("hiBin>>h_hiBin_mc","","goff");
	recotree_data->Draw("hiBin>>h_hiBin_data","","goff");
	
	h_hiBin_mc->Rebin(2);
	h_hiBin_data->Rebin(2);

    h_hiBin_mc->Draw();

	TH1D * h_hiBin_normal_mc = (TH1D *) h_hiBin_mc->Clone("h_hiBin_normal_mc");
	TH1D * h_hiBin_normal_data = (TH1D *) h_hiBin_data->Clone("h_hiBin_normal_data");

	h_hiBin_normal_mc->Scale(1.0/h_hiBin_normal_mc->Integral(0,-1));
	h_hiBin_normal_data->Scale(1.0/h_hiBin_normal_data->Integral(0,-1));

	TH1D * h_hibin_dataovermc = ( TH1D * ) h_hiBin_normal_mc->Clone("h_hibin_dataovermc");
	h_hibin_dataovermc->Divide(h_hiBin_normal_data, h_hiBin_normal_mc, 1.0, 1.0);

	h_hibin_dataovermc->Draw();

	TFile * output_hibin_mc_data = new TFile("output_hibin_mc_data.root","RECREATE");

	h_hiBin_mc->Write();
	h_hiBin_data->Write();
	h_hibin_dataovermc->Write();

	output_hibin_mc_data->Close();
}
