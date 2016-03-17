void Coutdatapoints_pbpbdata()
{
	TFile * inputdata_cent0to10 = new TFile("rootfiles/PromptRAA_D0_PbPb_spectrum_fonll_effunpre_cent0to10_ptbin12_y1_dataplusfonll.root");

    TH1D* D0_pbpb_spectrum = (TH1D *) inputdata_cent0to10->Get("D0_pbpb_spectrum");
	TGraphAsymmErrors* D0_pbpb_spectrum_syserror = ( TGraphAsymmErrors* ) inputdata_cent0to10->Get("D0_pbpb_spectrum_syserror");

   
    cout << "from stat TH1!!!!!!!!!!!!!!!!" << endl;
    cout << "pt center: ";
    for(int i = 0; i < D0_pbpb_spectrum->GetNbinsX(); i++ )
	{
		cout << D0_pbpb_spectrum->GetBinCenter(i+1) << ", ";
	}
	cout << endl;

	cout << "center: ";
	for(int i = 0; i < D0_pbpb_spectrum->GetNbinsX(); i++ )
	{
		cout << D0_pbpb_spectrum->GetBinContent(i+1) * 23.20<< ", ";
	}
	cout << endl;

	cout << "stat error: ";
	for(int i = 0; i < D0_pbpb_spectrum->GetNbinsX(); i++ )
		cout << D0_pbpb_spectrum->GetBinError(i+1) * 23.20<< ", ";
	cout << endl;

    cout << "from sys TGraph!!!!!!!!!!!!!!!!" << endl;
    cout << "pt center: ";
	for( int i = 0; i < D0_pbpb_spectrum_syserror->GetN(); i++ )
	{
		cout << D0_pbpb_spectrum_syserror->GetX()[i]  << ", ";
	}
	cout << endl;
	
	cout << "center: ";
	for( int i = 0; i < D0_pbpb_spectrum_syserror->GetN(); i++ )
	{
		cout << D0_pbpb_spectrum_syserror->GetY()[i] * 23.20<< ", ";
	}
	cout << endl;

	cout << "sys upper error: ";
	for( int i = 0; i < D0_pbpb_spectrum_syserror->GetN(); i++ )
	{
		cout << D0_pbpb_spectrum_syserror->GetErrorYhigh(i) * 23.20<< ", ";
	}
	cout << endl;

	cout << "sys lower error: ";
	for( int i = 0; i < D0_pbpb_spectrum_syserror->GetN(); i++ )
	{
		cout << D0_pbpb_spectrum_syserror->GetErrorYlow(i) * 23.20 << ", ";
	}
	cout << endl;
}
