void Coutdatapoints()
{
	TFile * inputppreference = new TFile("ppdatadrivenplusFONLL_12ptbin_y1.root");

	TGraphAsymmErrors* gaeSigmaDzero = ( TGraphAsymmErrors* ) inputppreference->Get("gaeSigmaDzero");

    cout << "pt center: ";
	for( int i = 0; i < gaeSigmaDzero->GetN(); i++ )
	{
		cout << gaeSigmaDzero->GetX()[i] << ", ";
	}
	cout << endl;
	
	cout << "center: ";
	for( int i = 0; i < gaeSigmaDzero->GetN(); i++ )
	{
		cout << gaeSigmaDzero->GetY()[i] << ", ";
	}
	cout << endl;

	cout << "upper error: ";
	for( int i = 0; i < gaeSigmaDzero->GetN(); i++ )
	{
		cout << gaeSigmaDzero->GetErrorYhigh(i) << ", ";
	}

	cout << "lower error: ";
	for( int i = 0; i < gaeSigmaDzero->GetN(); i++ )
	{
		cout << gaeSigmaDzero->GetErrorYlow(i) << ", ";
	}
}
