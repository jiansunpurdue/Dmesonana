
double syserrorPer_upper_ptbin7_cent0to10[7] = { 0.217, 0.244, 0.236, 0.256, 0.226, 0.211, 0.210};
double syserrorPer_lower_ptbin7_cent0to10[7] = { 0.217, 0.244, 0.236, 0.256, 0.226, 0.211, 0.210};

double syserrorPer_upper_ptbin7_cent10to30[7] = { 0.222, 0.203, 0.239, 0.212, 0.202, 0.193, 0.219};
double syserrorPer_lower_ptbin7_cent10to30[7] = { 0.222, 0.203, 0.239, 0.212, 0.202, 0.193, 0.219};

double syserrorPer_upper_ptbin7_cent30to50[7] = { 0.148, 0.162, 0.155, 0.145, 0.142, 0.136, 0.134};
double syserrorPer_lower_ptbin7_cent30to50[7] = { 0.148, 0.162, 0.155, 0.145, 0.142, 0.136, 0.134};

double syserrorPer_upper_ptbin7_cent50to100[7] = { 0.259, 0.165, 0.157, 0.146, 0.144, 0.140, 0.260};
double syserrorPer_lower_ptbin7_cent50to100[7] = { 0.259, 0.165, 0.157, 0.146, 0.144, 0.140, 0.260};


double syserrorPer_lower_ptbin7_cent50to100_notk_noselection[7];

double syserrorPer_upper_ptbin7_cent0to10_RCP[7];
double syserrorPer_upper_ptbin7_cent10to30_RCP[7];
double syserrorPer_upper_ptbin7_cent30to50_RCP[7];

void systematics_RCP_y1()
{
	double error_tk_0to30 = 9.3e-2;
	double error_tk_30to100 = 9.3e-2;
	double error_tk_0to30_RCP = 0.0;
	double error_tk_30to50_RCP = 0.0;

	double error_selection_0to100 = TMath::Sqrt( 11.4e-2 * 11.4e-2 + 0.05 * 0.05 );  // plus decay length
	double error_selection_0to30 = TMath::Sqrt( 14.1e-2 * 14.1e-2 + 0.05 * 0.05 );
	double error_selection_30to100 = TMath::Sqrt( 5.2e-2 * 5.2e-2 + 0.05 * 0.05 );

	for( int i = 0; i < 7; i++ )
	{
		syserrorPer_lower_ptbin7_cent50to100_notk_noselection[i] = TMath::Sqrt( syserrorPer_lower_ptbin7_cent50to100[i] * syserrorPer_lower_ptbin7_cent50to100[i] - error_tk_30to100 * error_tk_30to100 - error_selection_30to100 * error_selection_30to100 );
	}

    cout << "RCP sys, centrality 0 to 10%: ";
	for( int i = 0; i < 7; i++ )
	{
		double error_notk_noselection_1 = TMath::Sqrt( syserrorPer_lower_ptbin7_cent0to10[i] * syserrorPer_lower_ptbin7_cent0to10[i] - error_tk_0to30 * error_tk_0to30 - error_selection_0to30 * error_selection_0to30);

		syserrorPer_upper_ptbin7_cent0to10_RCP[i] = TMath::Sqrt( error_notk_noselection_1 * error_notk_noselection_1 + syserrorPer_lower_ptbin7_cent50to100_notk_noselection[i] * syserrorPer_lower_ptbin7_cent50to100_notk_noselection[i] + error_tk_0to30_RCP * error_tk_0to30_RCP + 8.9e-2 * 8.9e-2);  // plus difference of cut efficiency uncertainty

		cout <<  syserrorPer_upper_ptbin7_cent0to10_RCP[i] << " ,";
	}

	cout << endl;

	cout << "RCP sys, centrality 10 to 30%: ";

	for( int i = 0; i < 7; i++ )
	{
		double error_notk_noselection_1 = TMath::Sqrt( syserrorPer_lower_ptbin7_cent10to30[i] * syserrorPer_lower_ptbin7_cent10to30[i] - error_tk_0to30 * error_tk_0to30 - error_selection_0to30 * error_selection_0to30);

		syserrorPer_upper_ptbin7_cent10to30_RCP[i] = TMath::Sqrt( error_notk_noselection_1 * error_notk_noselection_1 + syserrorPer_lower_ptbin7_cent50to100_notk_noselection[i] * syserrorPer_lower_ptbin7_cent50to100_notk_noselection[i] + error_tk_0to30_RCP * error_tk_0to30_RCP + 8.9e-2 * 8.9e-2);

		cout << syserrorPer_upper_ptbin7_cent10to30_RCP[i] << " ,";
	}

	cout << endl;

	cout << "RCP sys, centrality 30 to 50%: ";

	for( int i = 0; i < 7; i++ )
	{
		double error_notk_noselection_1 = TMath::Sqrt( syserrorPer_lower_ptbin7_cent30to50[i] * syserrorPer_lower_ptbin7_cent30to50[i] - error_tk_30to100 * error_tk_30to100 - error_selection_30to100 * error_selection_30to100);

		syserrorPer_upper_ptbin7_cent30to50_RCP[i] = TMath::Sqrt( error_notk_noselection_1 * error_notk_noselection_1 + syserrorPer_lower_ptbin7_cent50to100_notk_noselection[i] * syserrorPer_lower_ptbin7_cent50to100_notk_noselection[i] + 0.0 * 0.0 );

		cout << syserrorPer_upper_ptbin7_cent30to50_RCP[i] << " ,";
	}

	cout << endl;
}

