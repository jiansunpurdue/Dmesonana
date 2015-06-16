#include <iostream>
#include <iomanip>

#define ERROR_SYS_PT_PERCEN 1.0e-2
#define ERROR_SYS_PT_PTHAT 0.0e-2
using namespace std;

double ERROR_SYS_TKEFF_PERCEN = 9999.0;
double ERROR_SYS_CUTEFF_PERCEN = 9999.0;

//double ERROR_SYS_FIT_PERCEN_cent0to100_12ptbin[12] = { 7.7e-2, 2.4e-2, 3.7e-2, 5.9e-2, 5.7e-2, 4.4e-2, 2.9e-2, 6.5e-2, 4.9e-2, 6.1e-2, 8.6e-2, 17.7e-2};
//double ERROR_SYS_FIT_PERCEN_cent0to10_11ptbin[11] = { 12.8e-2, 4.2e-2, 3.3e-2, 7.5e-2, 7.7e-2, 4.7e-2, 5.5e-2, 4.6e-2, 10.5e-2, 10.6e-2, 6.7e-2};
//double ERROR_SYS_FIT_PERCEN_cent0to20_11ptbin[11] = { 10.2e-2, 3.0e-2, 4.4e-2, 7.3e-2, 7.0e-2, 5.6e-2, 6.7e-2, 2.3e-2, 9.0e-2, 11.8e-2, 9.5e-2};
//
//double ERROR_SYS_FIT_PERCEN_cent0to10_7ptbin[7] = { 12.8e-2, 4.2e-2, 3.3e-2, 7.1e-2, 3.9e-2, 6.8e-2, 5.7e-2};
//double ERROR_SYS_FIT_PERCEN_cent10to30_7ptbin[7] = { 11.1e-2, 2.2e-2, 6.9e-2, 5.0e-2, 4.3e-2, 3.6e-2, 11.8e-2};
//double ERROR_SYS_FIT_PERCEN_cent30to50_7ptbin[7] = { 6.5e-2, 1.9e-2, 2.4e-2, 6.2e-2, 3.8e-2, 12.4e-2, 4.1e-2};
//double ERROR_SYS_FIT_PERCEN_cent50to100_7ptbin[7] = { 15.7e-2, 5.5e-2, 4.2e-2, 6.8e-2, 4.4e-2, 9.0e-2, 24.7e-2};
//
//for centrality 0-100%
//pt bins: 1.5,2.5,3.5,4.5,5.5,7,9,11,13,16,20,28,40
double ERROR_SYS_FIT_PERCEN_cent0to100_12ptbin[12] = { 6.0e-2, 6.0e-2, 6.0e-2, 6.0e-2, 6.0e-2, 6.0e-2, 6.0e-2, 6.0e-2, 6.0e-2, 6.0e-2, 6.0e-2, 17.7e-2};
//for centrality 0-10%
//pt bins: 1.5,2.5,3.5,4.5,5.5,7,9,11,13,16,20,28
double ERROR_SYS_FIT_PERCEN_cent0to10_11ptbin[11] = { 12.8e-2, 7.0e-2, 7.0e-2, 7.0e-2, 7.0e-2, 7.0e-2, 7.0e-2, 7.0e-2, 11.0e-2, 11.0e-2, 11.0e-2};
//for centrality 0-20%
//pt bins: 1.5,2.5,3.5,4.5,5.5,7,9,11,13,16,20,28
double ERROR_SYS_FIT_PERCEN_cent0to20_11ptbin[11] = { 10.2e-2, 6.0e-2, 6.0e-2, 6.0e-2, 6.0e-2, 6.0e-2, 6.0e-2, 6.0e-2, 10.0e-2, 10.0e-2, 10.0e-2};

//1.5, 2.5, 3.5, 4.5, 7.0, 11.0, 16.0, 28
double ERROR_SYS_FIT_PERCEN_cent0to10_7ptbin[7] = { 12.8e-2, 6.0e-2, 6.0e-2, 6.0e-2, 6.0e-2, 6.0e-2, 6.0e-2};
double ERROR_SYS_FIT_PERCEN_cent10to30_7ptbin[7] = { 11.1e-2, 5.0e-2, 5.0e-2, 5.0e-2, 5.0e-2, 5.0e-2, 11.8e-2};
double ERROR_SYS_FIT_PERCEN_cent30to50_7ptbin[7] = { 6.0e-2, 6.0e-2, 6.0e-2, 6.0e-2, 6.0e-2, 10.0e-2, 10.0e-2};
double ERROR_SYS_FIT_PERCEN_cent50to100_7ptbin[7] = { 15.7e-2, 7.0e-2, 7.0e-2, 7.0e-2, 7.0e-2, 7.0e-2, 24.7e-2};
//
double *syserrorPer_fit;
double *syserrorPer_total;

void calculatesyserror( int Nptbin, int cent_low, int cent_high, TFile * input_promptfraction)
{
	cout << "*******************************************************************" << endl;
	cout << " **************  cent_low: " << cent_low << "     " << "cent_high: " << cent_high << " ******************* " << endl;

    gStyle->SetOptTitle(0);
    gStyle->SetOptStat(0);
    TH1::SetDefaultSumw2();

	TGraphAsymmErrors * promptD0faction = ( TGraphAsymmErrors *) input_promptfraction->Get("gaePromptfraction");

	if( cent_low == 0 && cent_high == 100 )  ERROR_SYS_TKEFF_PERCEN = 14.0e-2;
	if( cent_low == 0 && cent_high == 10 )  ERROR_SYS_TKEFF_PERCEN = 16.0e-2;
	if( cent_low == 0 && cent_high == 20 )  ERROR_SYS_TKEFF_PERCEN = 16.0e-2;
	if( cent_low == 10 && cent_high == 30 )  ERROR_SYS_TKEFF_PERCEN = 16.0e-2;
	if( cent_low == 30 && cent_high == 50 )  ERROR_SYS_TKEFF_PERCEN = 4.0e-2;
	if( cent_low == 50 && cent_high == 100 )  ERROR_SYS_TKEFF_PERCEN = 4.0e-2;

	if( cent_low == 0 && cent_high == 100 )  ERROR_SYS_CUTEFF_PERCEN = 5.0e-2;
	if( cent_high <= 30 )   ERROR_SYS_CUTEFF_PERCEN = 13.7e-2;
	if( cent_low >= 30 )    ERROR_SYS_CUTEFF_PERCEN = 16.3e-2;

	ERROR_SYS_CUTEFF_PERCEN = TMath::Sqrt( ERROR_SYS_CUTEFF_PERCEN * ERROR_SYS_CUTEFF_PERCEN + 0.05 * 0.05 );

	cout << "   ERROR_SYS_CUTEFF_PERCEN: " << ERROR_SYS_CUTEFF_PERCEN << endl;

	syserrorPer_fit = new double[Nptbin];
	syserrorPer_total = new double[Nptbin];

	for( int i = 0; i < Nptbin; i++ ) syserrorPer_total[i] = 0;

	for( int i = 0; i < Nptbin; i++ )  syserrorPer_fit[i] = 0;

	if( cent_low == 0 && cent_high == 100 && Nptbin == 12)
	{
		for( int i = 0; i < Nptbin; i++ )
			syserrorPer_fit[i] = ERROR_SYS_FIT_PERCEN_cent0to100_12ptbin[i];
	}

	if( cent_low == 0 && cent_high == 10 && Nptbin == 11)
	{
		for( int i = 0; i < Nptbin; i++ )
			syserrorPer_fit[i] = ERROR_SYS_FIT_PERCEN_cent0to10_11ptbin[i];
	}

	if( cent_low == 0 && cent_high == 20 && Nptbin == 11)
	{
		for( int i = 0; i < Nptbin; i++ )
			syserrorPer_fit[i] = ERROR_SYS_FIT_PERCEN_cent0to20_11ptbin[i];
	}

	if( cent_low == 0 && cent_high == 10 && Nptbin == 7)
	{
		for( int i = 0; i < Nptbin; i++ )
			syserrorPer_fit[i] = ERROR_SYS_FIT_PERCEN_cent0to10_7ptbin[i];
	}

	if( cent_low == 10 && cent_high == 30 && Nptbin == 7)
	{
		for( int i = 0; i < Nptbin; i++ )
			syserrorPer_fit[i] = ERROR_SYS_FIT_PERCEN_cent10to30_7ptbin[i];
	}

	if( cent_low == 30 && cent_high == 50 && Nptbin == 7)
	{
		for( int i = 0; i < Nptbin; i++ )
			syserrorPer_fit[i] = ERROR_SYS_FIT_PERCEN_cent30to50_7ptbin[i];
	}

	if( cent_low == 50 && cent_high == 100 && Nptbin == 7)
	{
		for( int i = 0; i < Nptbin; i++ )
			syserrorPer_fit[i] = ERROR_SYS_FIT_PERCEN_cent50to100_7ptbin[i];
	}
 
    cout << "syserror_promptfraction_Per: ";

	for( int i = 0; i < Nptbin; i++ )
	{
		double syserror_promptfraction_Per = promptD0faction->GetErrorYhigh(i)/promptD0faction->GetY()[i];
//		cout << setprecision(3) << syserror_promptfraction_Per * 100 << "/\%  &  ";
        cout << fixed << setprecision(1) << 100 * syserror_promptfraction_Per << "\\" << "%  &  ";
	}

	cout << endl;
	
	for( int i = 0; i < Nptbin; i++ )
	{
		double syserror_promptfraction_Per = promptD0faction->GetErrorYhigh(i)/promptD0faction->GetY()[i];
		cout << fixed << setprecision(3) << syserror_promptfraction_Per << ", " ;
	}

	cout << endl;

	for( int i = 0; i < Nptbin; i++ )
	{
		double syserror_promptfraction_Per = promptD0faction->GetErrorYhigh(i)/promptD0faction->GetY()[i];
		//cout << "  ERROR_SYS_TKEFF_PERCEN: " << ERROR_SYS_TKEFF_PERCEN << "  ERROR_SYS_CUTEFF_PERCEN: " << ERROR_SYS_CUTEFF_PERCEN << "  ERROR_SYS_PT_PERCEN: " << ERROR_SYS_PT_PERCEN << "  ERROR_SYS_PT_PTHAT: " << ERROR_SYS_PT_PTHAT << "   syserrorPer_fit: " << syserrorPer_fit[i] << "   syserror_promptfraction_Per: " << syserror_promptfraction_Per << endl;
		syserrorPer_total[i] = TMath::Sqrt( ERROR_SYS_TKEFF_PERCEN * ERROR_SYS_TKEFF_PERCEN + ERROR_SYS_CUTEFF_PERCEN * ERROR_SYS_CUTEFF_PERCEN + ERROR_SYS_PT_PERCEN * ERROR_SYS_PT_PERCEN + ERROR_SYS_PT_PTHAT * ERROR_SYS_PT_PTHAT + syserrorPer_fit[i] * syserrorPer_fit[i] + syserror_promptfraction_Per * syserror_promptfraction_Per );
		//cout << " total: " << setprecision(3) << syserrorPer_total[i] << endl;
	}

	cout << " tot uncertainty: ";
	for( int i = 0; i < Nptbin; i++ )
	{
		cout << fixed << setprecision(1) << 100 * syserrorPer_total[i] << "\\" << "%  &  ";
	}
	cout << endl;
	
	for( int i = 0; i < Nptbin; i++ )
	{
		cout << fixed << setprecision(3) << syserrorPer_total[i] << ", ";
	}
	cout << endl;
}

void systematics_RAA_y1()
{
	int Nptbin;
	int cent_low;
	int cent_high;
	TFile * input_promptfraction;

	Nptbin = 12;
	cent_low = 0;
	cent_high = 100;
	input_promptfraction = new TFile("rootfiles/Bfraction_method1_ptbin_14_cent0to100_y1.root");
	calculatesyserror( Nptbin, cent_low, cent_high, input_promptfraction);
	input_promptfraction->Close();

	Nptbin = 11;
	cent_low = 0;
	cent_high = 10;
	input_promptfraction = new TFile("rootfiles/Bfraction_method1_ptbin_14_cent0to10_y1.root");
	calculatesyserror( Nptbin, cent_low, cent_high, input_promptfraction);
	input_promptfraction->Close();


	Nptbin = 11;
	cent_low = 0;
	cent_high = 20;
	input_promptfraction = new TFile("rootfiles/Bfraction_method1_ptbin_14_cent0to20_y1.root");
	calculatesyserror( Nptbin, cent_low, cent_high, input_promptfraction);
	input_promptfraction->Close();

	Nptbin = 7;
	cent_low = 0;
	cent_high = 10;
	input_promptfraction = new TFile("rootfiles/Bfraction_method1_ptbin_9_cent0to10_y1.root");
	calculatesyserror( Nptbin, cent_low, cent_high, input_promptfraction);
	input_promptfraction->Close();

	Nptbin = 7;
	cent_low = 10;
	cent_high = 30;
	input_promptfraction = new TFile("rootfiles/Bfraction_method1_ptbin_9_cent10to30_y1.root");
	calculatesyserror( Nptbin, cent_low, cent_high, input_promptfraction);
	input_promptfraction->Close();

	Nptbin = 7;
	cent_low = 30;
	cent_high = 50;
	input_promptfraction = new TFile("rootfiles/Bfraction_method1_ptbin_9_cent30to50_y1.root");
	calculatesyserror( Nptbin, cent_low, cent_high, input_promptfraction);
	input_promptfraction->Close();

	Nptbin = 7;
	cent_low = 50;
	cent_high = 100;
	input_promptfraction = new TFile("rootfiles/Bfraction_method1_ptbin_9_cent50to100_y1.root");
	calculatesyserror( Nptbin, cent_low, cent_high, input_promptfraction);
	input_promptfraction->Close();



}
