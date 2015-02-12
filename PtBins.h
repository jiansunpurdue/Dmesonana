//double ptbins[NPT+1] = {0,4,5,7,9,11,14,17,20,30,40,100};
//double ptbins[NPT+1] = {0,3,3.5,4.0,4.5,5.5,7,9,11,13,16,20,28,40,100};
//for analysis
#define NPT  11
double ptbins[NPT+1] = {0,4.5,5.5,7,9,11,13,16,20,28,40,100};
//double ptbins[NPT+1] = {0,3.5,4.5,5.5,7,9,11,13,16,20,28,40};

//#define NPT 6
//double ptbins[NPT+1] = {0.,4.5,7.0,11.0,20.,40.,100.};

//#define NPT 7
//double ptbins[NPT+1] = {0.,4.5,7.0,11.0,20.,28.,40.,100.};

//#define NY 12

//double ybins[NY+1] = {-2.0, -1.8, -1.6, -1.2, -0.8, -0.4, 0, 0.4, 0.8, 1.2, 1.6, 1.8, 2.0};

//#define NY 6
//double ybins[NY+1] = {-2.0, -1.5, -0.7, 0, 0.7, 1.5, 2.0};

//pp triger efficiency
//#define NPT  16
//double ptbins[NPT+1] = {0,4.5,5.5,7,9,11,13,16,18,20,22,25,30,35,40,45,60};
//pPb trigger efficiency
//#define NPT  14
//double ptbins[NPT+1] = {0,4.5,5.5,7,9,11,13,16,18,20,22,24,28,40,100};

//#define NPT 1
//double ptbins[NPT+1] = {4.5, 40};
//#define NY 1
//double ybins[NY+1] = {-2.0, 2.0};
//
//cut
const double cut_pt_edge = 13.0;
const double ffls3dcut[2] = {4.0,2.0};
const double cosalphacut  = 0.975;
const double fchi2cut = 3.0;
