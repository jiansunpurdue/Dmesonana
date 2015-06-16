#include <iostream>
#include <iomanip>


#define ERROR_SYS_CUTEFF_PERCEN 8.6e-2
#define ERROR_SYS_PT_PERCEN 0.5e-2
#define ERROR_SYS_PT_PTHAT 0.0e-2
using namespace std;

double ERROR_SYS_TKEFF_PERCEN = 9999.0;
double ERROR_SYS_FIT_PERCEN_cent0to100_10ptbin[10] = { 18.3e-2, 4.7e-2, 5.0e-2, 3.5e-2, 3.7e-2, 6.9e-2, 8.4e-2, 4.7e-2, 9.9e-2, 22.6e-2};
double ERROR_SYS_FIT_PERCEN_cent0to10_9ptbin[9] = { 26.2e-2, 9.1e-2, 10.6e-2, 13.3e-2, 14.3e-2, 7.2e-2, 18.6e-2, 4.2e-2, 31.2e-2};
double ERROR_SYS_FIT_PERCEN_cent0to20_9ptbin[9] = { 24.2e-2, 5.2e-2, 7.7e-2, 5.5e-2, 8.2e-2, 5.9e-2, 12.7e-2, 9.3e-2, 25.6e-2};

double ERROR_SYS_FIT_PERCEN_cent0to10_5ptbin[5] = { 26.2e-2, 8.0e-2, 13.9e-2, 4.0e-2, 11.8e-2};
double ERROR_SYS_FIT_PERCEN_cent10to30_5ptbin[5] = { 6.8e-2, 8.5e-2, 6.3e-2, 6.1e-2, 6.8e-2};
double ERROR_SYS_FIT_PERCEN_cent30to50_5ptbin[5] = { 1.5e-2, 4.0e-2, 4.2e-2, 10.0e-2, 6.3e-2};
double ERROR_SYS_FIT_PERCEN_cent50to100_5ptbin[5] = { 13.6e-2, 8.9e-2, 6.8e-2, 6.8e-2, 8.8e-2};

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

	syserrorPer_fit = new double[Nptbin];
	syserrorPer_total = new double[Nptbin];

	for( int i = 0; i < Nptbin; i++ ) syserrorPer_total[i] = 0;

	for( int i = 0; i < Nptbin; i++ )  syserrorPer_fit[i] = 0;

	if( cent_low == 0 && cent_high == 100 && Nptbin == 10)
	{
		for( int i = 0; i < Nptbin; i++ )
			syserrorPer_fit[i] = ERROR_SYS_FIT_PERCEN_cent0to100_10ptbin[i];
	}

	if( cent_low == 0 && cent_high == 10 && Nptbin == 9)
	{
		for( int i = 0; i < Nptbin; i++ )
			syserrorPer_fit[i] = ERROR_SYS_FIT_PERCEN_cent0to10_9ptbin[i];
	}

	if( cent_low == 0 && cent_high == 20 && Nptbin == 9)
	{
		for( int i = 0; i < Nptbin; i++ )
			syserrorPer_fit[i] = ERROR_SYS_FIT_PERCEN_cent0to20_9ptbin[i];
	}

	if( cent_low == 0 && cent_high == 10 && Nptbin == 5)
	{
		for( int i = 0; i < Nptbin; i++ )
			syserrorPer_fit[i] = ERROR_SYS_FIT_PERCEN_cent0to10_5ptbin[i];
	}

	if( cent_low == 10 && cent_high == 30 && Nptbin == 5)
	{
		for( int i = 0; i < Nptbin; i++ )
			syserrorPer_fit[i] = ERROR_SYS_FIT_PERCEN_cent10to30_5ptbin[i];
	}

	if( cent_low == 30 && cent_high == 50 && Nptbin == 5)
	{
		for( int i = 0; i < Nptbin; i++ )
			syserrorPer_fit[i] = ERROR_SYS_FIT_PERCEN_cent30to50_5ptbin[i];
	}

	if( cent_low == 50 && cent_high == 100 && Nptbin == 5)
	{
		for( int i = 0; i < Nptbin; i++ )
			syserrorPer_fit[i] = ERROR_SYS_FIT_PERCEN_cent50to100_5ptbin[i];
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

void systematics_RAA()
{
	int Nptbin;
	int cent_low;
	int cent_high;
	TFile * input_promptfraction;

	Nptbin = 10;
	cent_low = 0;
	cent_high = 100;
	input_promptfraction = new TFile("Bfraction_method1_ptbin_12_cent0to100.root");
	calculatesyserror( Nptbin, cent_low, cent_high, input_promptfraction);
	input_promptfraction->Close();

	Nptbin = 9;
	cent_low = 0;
	cent_high = 10;
	input_promptfraction = new TFile("Bfraction_method1_ptbin_12_cent0to10.root");
	calculatesyserror( Nptbin, cent_low, cent_high, input_promptfraction);
	input_promptfraction->Close();


	Nptbin = 9;
	cent_low = 0;
	cent_high = 20;
	input_promptfraction = new TFile("Bfraction_method1_ptbin_12_cent0to20.root");
	calculatesyserror( Nptbin, cent_low, cent_high, input_promptfraction);
	input_promptfraction->Close();

	Nptbin = 5;
	cent_low = 0;
	cent_high = 10;
	input_promptfraction = new TFile("Bfraction_method1_ptbin_7_cent0to10.root");
	calculatesyserror( Nptbin, cent_low, cent_high, input_promptfraction);
	input_promptfraction->Close();

	Nptbin = 5;
	cent_low = 10;
	cent_high = 30;
	input_promptfraction = new TFile("Bfraction_method1_ptbin_7_cent10to30.root");
	calculatesyserror( Nptbin, cent_low, cent_high, input_promptfraction);
	input_promptfraction->Close();

	Nptbin = 5;
	cent_low = 30;
	cent_high = 50;
	input_promptfraction = new TFile("Bfraction_method1_ptbin_7_cent30to50.root");
	calculatesyserror( Nptbin, cent_low, cent_high, input_promptfraction);
	input_promptfraction->Close();

	Nptbin = 5;
	cent_low = 50;
	cent_high = 100;
	input_promptfraction = new TFile("Bfraction_method1_ptbin_7_cent50to100.root");
	calculatesyserror( Nptbin, cent_low, cent_high, input_promptfraction);
	input_promptfraction->Close();
//


}
