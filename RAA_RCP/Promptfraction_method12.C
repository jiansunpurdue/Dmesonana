void Promptfraction_method12()
{
	TFile * input_method1 = new TFile("Bfraction_method1.root");
//	TFile * input_method2_raa = new TFile("Bfraction_method2_RAA.root");
    TFile * input_method2_raa = new TFile("Bfraction_method2.root");

	TGraphAsymmErrors* gaePromptfraction_method1 = ( TGraphAsymmErrors* ) input_method1->Get("gaePromptfraction");
	TGraphAsymmErrors* gaePromptfraction_method2 = ( TGraphAsymmErrors* ) input_method2_raa->Get("gaePromptfraction");

	gaePromptfraction_method1->SetLineColor(2.0);
	gaePromptfraction_method1->SetMarkerColor(2.0);

	gaePromptfraction_method2->SetLineColor(4.0);
	gaePromptfraction_method2->SetMarkerColor(4.0);

	TCanvas * cfg_promptfraction_method12 = new TCanvas("cfg_promptfraction_method12","cfg_promptfraction_method12");

	gaePromptfraction_method1->Draw("AP");
	gaePromptfraction_method2->Draw("Psame");
}
