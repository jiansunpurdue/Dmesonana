double syserrorPer_upper_ptbin5_cent0to10[5] = { 0.343, 0.255, 0.253, 0.189, 0.218};
double syserrorPer_lower_ptbin5_cent0to10[5] = { 0.343, 0.255, 0.253, 0.189, 0.218};

double syserrorPer_upper_ptbin5_cent10to30[5] = { 0.231, 0.226, 0.203, 0.194, 0.196};
double syserrorPer_lower_ptbin5_cent10to30[5] = { 0.231, 0.226, 0.203, 0.194, 0.196};

double syserrorPer_upper_ptbin5_cent30to50[5] = { 0.131, 0.123, 0.111, 0.139, 0.115};
double syserrorPer_lower_ptbin5_cent30to50[5] = { 0.131, 0.123, 0.111, 0.139, 0.115};

double syserrorPer_upper_ptbin5_cent50to100[5] = { 0.167, 0.131, 0.117, 0.117, 0.130};
double syserrorPer_lower_ptbin5_cent50to100[5] = { 0.167, 0.131, 0.117, 0.117, 0.130};


double syserrorPer_lower_ptbin5_cent50to100_notk_noselection[5];

double syserrorPer_upper_ptbin5_cent0to10_RCP[5];
double syserrorPer_upper_ptbin5_cent10to30_RCP[5];
double syserrorPer_upper_ptbin5_cent30to50_RCP[5];

void systematics_RCP()
{
	double error_tk_0to30 = 16.0e-2;
	double error_tk_30to100 = 4.0e-2;
	double error_tk_0to30_RCP = 12.0e-2;
	double error_tk_30to50_RCP = 0.0;

	double error_selection_0to100 = 8.6e-2;

	for( int i = 0; i < 5; i++ )
	{
		syserrorPer_lower_ptbin5_cent50to100_notk_noselection[i] = TMath::Sqrt( syserrorPer_lower_ptbin5_cent50to100[i] * syserrorPer_lower_ptbin5_cent50to100[i] - error_tk_30to100 * error_tk_30to100 - error_selection_0to100 * error_selection_0to100 );
	}

    cout << "RCP sys, centrality 0 to 10%: ";
	for( int i = 0; i < 5; i++ )
	{
		double error_notk_noselection_1 = TMath::Sqrt( syserrorPer_lower_ptbin5_cent0to10[i] * syserrorPer_lower_ptbin5_cent0to10[i] - error_tk_0to30 * error_tk_0to30 - error_selection_0to100 * error_selection_0to100);

		syserrorPer_upper_ptbin5_cent0to10_RCP[i] = TMath::Sqrt( error_notk_noselection_1 * error_notk_noselection_1 + syserrorPer_lower_ptbin5_cent50to100_notk_noselection[i] * syserrorPer_lower_ptbin5_cent50to100_notk_noselection[i] + error_tk_0to30_RCP * error_tk_0to30_RCP );

		cout <<  syserrorPer_upper_ptbin5_cent0to10_RCP[i] << " ,";
	}

	cout << endl;

	cout << "RCP sys, centrality 10 to 30%: ";

	for( int i = 0; i < 5; i++ )
	{
		double error_notk_noselection_1 = TMath::Sqrt( syserrorPer_lower_ptbin5_cent10to30[i] * syserrorPer_lower_ptbin5_cent10to30[i] - error_tk_0to30 * error_tk_0to30 - error_selection_0to100 * error_selection_0to100);

		syserrorPer_upper_ptbin5_cent10to30_RCP[i] = TMath::Sqrt( error_notk_noselection_1 * error_notk_noselection_1 + syserrorPer_lower_ptbin5_cent50to100_notk_noselection[i] * syserrorPer_lower_ptbin5_cent50to100_notk_noselection[i] + error_tk_0to30_RCP * error_tk_0to30_RCP);

		cout << syserrorPer_upper_ptbin5_cent10to30_RCP[i] << " ,";
	}

	cout << endl;

	cout << "RCP sys, centrality 30 to 50%: ";

	for( int i = 0; i < 5; i++ )
	{
		double error_notk_noselection_1 = TMath::Sqrt( syserrorPer_lower_ptbin5_cent30to50[i] * syserrorPer_lower_ptbin5_cent30to50[i] - error_tk_30to100 * error_tk_30to100 - error_selection_0to100 * error_selection_0to100);

		syserrorPer_upper_ptbin5_cent30to50_RCP[i] = TMath::Sqrt( error_notk_noselection_1 * error_notk_noselection_1 + syserrorPer_lower_ptbin5_cent50to100_notk_noselection[i] * syserrorPer_lower_ptbin5_cent50to100_notk_noselection[i] );

		cout << syserrorPer_upper_ptbin5_cent30to50_RCP[i] << " ,";
	}

	cout << endl;
}

