//for analysis
//#define NPT  11
//double ptbins[NPT+1] = {0,4.5,5.5,7,9,11,13,16,20,28,40,100};
#define NPT  13
double ptbins[NPT+1] = {0,2.5,3.5,4.5,5.5,7,9,11,13,16,20,28,40,100};

//#define NPT 6
//double ptbins[NPT+1] = {0.,4.5,7.0,11.0,20.,40.,100.};

//#define NY 12

//double ybins[NY+1] = {-2.0, -1.8, -1.6, -1.2, -0.8, -0.4, 0, 0.4, 0.8, 1.2, 1.6, 1.8, 2.0};

#define NY 6
double ybins[NY+1] = {-2.0, -1.5, -0.7, 0, 0.7, 1.5, 2.0};

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
////cut
//const double cut_pt_edge = 13.0;
//const double ffls3dcut[2] = {4.0,2.0};
//const double cosalphacut  = 0.975;
//const double fchi2cut = 3.0;
//
//tmva cut
#define NCUTPT 13
const double cut_pt_edge[NCUTPT+1] = {0,2.5,3.5,4.5,5.5,7,9,11,13,16,20,28,40,100};

const double ffls3dcut[NCUTPT] = {5.77,  5.77,  7.37,  6.80,  6.36,  6.28,  4.49,  4.18,  3.94,  3.65,  3.78,  4.40,  3.18};
const double alphacut[NCUTPT]  = {0.071, 0.071, 0.053, 0.053, 0.060, 0.068, 0.119, 0.108, 0.091, 0.089, 0.082, 0.071, 0.133};
const double fprobcut[NCUTPT]  = {0.151, 0.151, 0.128, 0.182, 0.167, 0.100, 0.100, 0.072, 0.110, 0.055, 0.041, 0.046, 0.020};


//#define NCUTPT 11
//const double cut_pt_edge[NCUTPT+1] = {0,4.5,5.5,7,9,11,13,16,20,28,40,100};
//const double ffls3dcut[NCUTPT] = {3.98, 3.98, 4.14, 3.87, 4.36, 3.68, 3.59, 3.25, 2.76, 3.18, 3.18};
//const double alphacut[NCUTPT]  = {0.065, 0.065, 0.069, 0.053, 0.066, 0.075, 0.06, 0.061, 0.055, 0.133, 0.133};
//const double fprobcut[NCUTPT] = {0.082, 0.082, 0.209, 0.113, 0.093, 0.057, 0.107, 0.025, 0.068, 0.020, 0.020};
//
//const double ffls3dcut[NCUTPT] = {3.98,  5.11,  4.44,  3.59,  3.37,  3.45,  3.54,  3.29,  2.62,  2.77,  3.18};
//const double alphacut[NCUTPT]  = {0.065, 0.073, 0.070, 0.070, 0.085, 0.094, 0.134, 0.106, 0.086, 0.089, 0.133};
//const double fprobcut[NCUTPT]  = {0.082, 0.094, 0.024, 0.025, 0.021, 0.016, 0.006, 0.002, 0.004, 0.004, 0.020};

//absy2
//const double ffls3dcut[NCUTPT] = {6.24,  6.24,  4.61,  4.26,  3.76,  3.66,  3.34,  3.09,  2.69,  2.93,  3.18};
//const double alphacut[NCUTPT]  = {0.046, 0.046, 0.044, 0.059, 0.075, 0.076, 0.056, 0.062, 0.056, 0.032, 0.133};
//const double fprobcut[NCUTPT]  = {0.107, 0.107, 0.066, 0.100, 0.085, 0.070, 0.021, 0.030, 0.084, 0.014, 0.020};

//abys2prompt
//const double ffls3dcut[NCUTPT] = {3.81,  3.81,  4.55,  3.92,  3.77,  3.57,  3.10,  2.88,  2.71,  4.35,  3.18};
//const double alphacut[NCUTPT]  = {0.056, 0.056, 0.040, 0.060, 0.063, 0.057, 0.043, 0.059, 0.059, 0.036, 0.133};
//const double fprobcut[NCUTPT]  = {0.267, 0.267, 0.095, 0.104, 0.086, 0.038, 0.047, 0.053, 0.033, 0.081, 0.020};
//>>gai
//const double ffls3dcut[NCUTPT] = {3.81,  3.81,  3.91,  3.92,  3.77,  3.57,  3.37,  2.88,  2.71,  2.63,  3.18};
//const double alphacut[NCUTPT]  = {0.056, 0.056, 0.048, 0.060, 0.063, 0.057, 0.053, 0.059, 0.059, 0.042, 0.133};
//const double fprobcut[NCUTPT]  = {0.267, 0.267, 0.065, 0.104, 0.086, 0.038, 0.025, 0.053, 0.033, 0.050, 0.020};

//abys1prompt
//const double ffls3dcut[NCUTPT] = {4.81,  4.81,  5.11,  4.21,  3.97,  3.53,  3.60,  2.79,  2.57,  2.75,  3.18};
//const double alphacut[NCUTPT]  = {0.074, 0.074, 0.080, 0.075, 0.075, 0.089, 0.115, 0.129, 0.101, 0.081, 0.133};
//const double fprobcut[NCUTPT]  = {0.164, 0.164, 0.033, 0.018, 0.011, 0.026, 0.039, 0.009, 0.005, 0.002, 0.020};
