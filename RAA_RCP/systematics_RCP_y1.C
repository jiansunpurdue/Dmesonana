//double syserrorPer_upper_ptbin7_cent0to10[7] = {0.246, 0.203, 0.195, 0.213, 0.184, 0.190, 0.187};
//double syserrorPer_lower_ptbin7_cent0to10[7] = {0.246, 0.203, 0.195, 0.213, 0.184, 0.190, 0.187};
//
//double syserrorPer_upper_ptbin7_cent10to30[7] = {0.333, 0.208, 0.206, 0.189, 0.182, 0.174, 0.205};
//double syserrorPer_lower_ptbin7_cent10to30[7] = {0.333, 0.208, 0.206, 0.189, 0.182, 0.174, 0.205};
//
//double syserrorPer_upper_ptbin7_cent30to50[7] = {0.144, 0.102, 0.087, 0.094, 0.078, 0.150, 0.076};
//double syserrorPer_lower_ptbin7_cent30to50[7] = {0.144, 0.102, 0.087, 0.094, 0.078, 0.150, 0.076};
//
//double syserrorPer_upper_ptbin7_cent50to100[7] = {0.167, 0.100, 0.080, 0.096, 0.078, 0.115, 0.248};
//double syserrorPer_lower_ptbin7_cent50to100[7] = {0.167, 0.100, 0.080, 0.096, 0.078, 0.115, 0.248};
//
//
double syserrorPer_upper_ptbin7_cent0to10[7] = { 0.287, 0.238, 0.235, 0.250, 0.237, 0.230, 0.227};
double syserrorPer_lower_ptbin7_cent0to10[7] = { 0.287, 0.238, 0.235, 0.250, 0.237, 0.230, 0.227};

double syserrorPer_upper_ptbin7_cent10to30[7] = {0.255, 0.248, 0.245, 0.237, 0.229, 0.225, 0.249};
double syserrorPer_lower_ptbin7_cent10to30[7] = {0.255, 0.248, 0.245, 0.237, 0.229, 0.225, 0.249};

double syserrorPer_upper_ptbin7_cent30to50[7] = {0.209, 0.195, 0.190, 0.191, 0.189, 0.204, 0.203};
double syserrorPer_lower_ptbin7_cent30to50[7] = {0.209, 0.195, 0.190, 0.191, 0.189, 0.204, 0.203};

double syserrorPer_upper_ptbin7_cent50to100[7] = {0.246, 0.197, 0.193, 0.192, 0.191, 0.190, 0.304};
double syserrorPer_lower_ptbin7_cent50to100[7] = {0.246, 0.197, 0.193, 0.192, 0.191, 0.190, 0.304};


double syserrorPer_lower_ptbin7_cent50to100_notk_noselection[7];

double syserrorPer_upper_ptbin7_cent0to10_RCP[7];
double syserrorPer_upper_ptbin7_cent10to30_RCP[7];
double syserrorPer_upper_ptbin7_cent30to50_RCP[7];

void systematics_RCP_y1()
{
	double error_tk_0to30 = 16.0e-2;
	double error_tk_30to100 = 4.0e-2;
	double error_tk_0to30_RCP = 12.0e-2;
	double error_tk_30to50_RCP = 0.0;

	double error_selection_0to100 = TMath::Sqrt( 5.0e-2 * 5.0e-2 + 0.05 * 0.05 );
	double error_selection_0to30 = TMath::Sqrt( 13.7e-2 * 13.7e-2 + 0.05 * 0.05 );
	double error_selection_30to100 = TMath::Sqrt( 16.3e-2 * 16.3e-2 + 0.05 * 0.05 );

	for( int i = 0; i < 7; i++ )
	{
		syserrorPer_lower_ptbin7_cent50to100_notk_noselection[i] = TMath::Sqrt( syserrorPer_lower_ptbin7_cent50to100[i] * syserrorPer_lower_ptbin7_cent50to100[i] - error_tk_30to100 * error_tk_30to100 - error_selection_30to100 * error_selection_30to100 );
	}

    cout << "RCP sys, centrality 0 to 10%: ";
	for( int i = 0; i < 7; i++ )
	{
		double error_notk_noselection_1 = TMath::Sqrt( syserrorPer_lower_ptbin7_cent0to10[i] * syserrorPer_lower_ptbin7_cent0to10[i] - error_tk_0to30 * error_tk_0to30 - error_selection_0to30 * error_selection_0to30);

		syserrorPer_upper_ptbin7_cent0to10_RCP[i] = TMath::Sqrt( error_notk_noselection_1 * error_notk_noselection_1 + syserrorPer_lower_ptbin7_cent50to100_notk_noselection[i] * syserrorPer_lower_ptbin7_cent50to100_notk_noselection[i] + error_tk_0to30_RCP * error_tk_0to30_RCP );

		cout <<  syserrorPer_upper_ptbin7_cent0to10_RCP[i] << " ,";
	}

	cout << endl;

	cout << "RCP sys, centrality 10 to 30%: ";

	for( int i = 0; i < 7; i++ )
	{
		double error_notk_noselection_1 = TMath::Sqrt( syserrorPer_lower_ptbin7_cent10to30[i] * syserrorPer_lower_ptbin7_cent10to30[i] - error_tk_0to30 * error_tk_0to30 - error_selection_0to30 * error_selection_0to30);

		syserrorPer_upper_ptbin7_cent10to30_RCP[i] = TMath::Sqrt( error_notk_noselection_1 * error_notk_noselection_1 + syserrorPer_lower_ptbin7_cent50to100_notk_noselection[i] * syserrorPer_lower_ptbin7_cent50to100_notk_noselection[i] + error_tk_0to30_RCP * error_tk_0to30_RCP);

		cout << syserrorPer_upper_ptbin7_cent10to30_RCP[i] << " ,";
	}

	cout << endl;

	cout << "RCP sys, centrality 30 to 50%: ";

	for( int i = 0; i < 7; i++ )
	{
		double error_notk_noselection_1 = TMath::Sqrt( syserrorPer_lower_ptbin7_cent30to50[i] * syserrorPer_lower_ptbin7_cent30to50[i] - error_tk_30to100 * error_tk_30to100 - error_selection_30to100 * error_selection_30to100);

		syserrorPer_upper_ptbin7_cent30to50_RCP[i] = TMath::Sqrt( error_notk_noselection_1 * error_notk_noselection_1 + syserrorPer_lower_ptbin7_cent50to100_notk_noselection[i] * syserrorPer_lower_ptbin7_cent50to100_notk_noselection[i] );

		cout << syserrorPer_upper_ptbin7_cent30to50_RCP[i] << " ,";
	}

	cout << endl;
}

