#ifndef LIBRARYANALYZE_LIGHT_HISTO_H
#define LIBRARYANALYZE_LIGHT_HISTO_H

#include <vector>

#include "TFile.h"
#include "TTree.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TF1.h"
#include "TCanvas.h"
#include "TROOT.h"
#include "TStyle.h"
#include "TMath.h"
#include "TVector3.h"
#include "TRandom3.h"
#include "TGraph.h"
#include "THStack.h"
#include "TColor.h"
#include "TLegend.h"
#include "TMarker.h"

// -----------------------------------------------------------
// -----------------------------------------------------------
// Use this file to set the configurable parameters for the mc
// -----------------------------------------------------------
// -----------------------------------------------------------

using namespace std;

///-------------------------------------
/// Custom Sorting Function
///-------------------------------------
bool sort_function(std::pair<double, int> pair1, std::pair<double, int> pair2)
{ return (pair1.first < pair2.first); }
///-------------------------------------


///-------------------------------------
//--------WHAT to generate?-------------
///-------------------------------------
bool fixed_energy = false; double fixedE = 100.0; //MeV
bool supernova = false;
bool solar = false;
bool gen_argon = false;
bool gen_Co60B = false;
bool gen_Co60G1 = false;
bool gen_Co60G2 = false;
bool gen_Ar42 = false;
bool gen_K42 = false;
bool gen_40KB = false;
bool gen_40KG = false;
bool gen_Kr85B1 = false;
bool gen_Kr85B2 = true;
bool gen_Kr85G1 = false;
bool gen_Kr85G2 = false;
bool gen_radon = false;
bool gen_Po218 = false;
bool gen_Pb214 = false;
bool gen_Bi214 = false;
bool gen_Po214 = false;
///-------------------------------------
///-------------------------------------
///-------DO timing calculations?-------
///-------------------------------------
bool do_timings = true;
double step_size = 1.0; 	// step size for discretisation of timing array in cm
///-------------------------------------
//--------WHERE to generate?-------------
///-------------------------------------
// Choose one only!
bool random_pos = true;         // For simulating gamma decay, you need to change the range of positions!
bool fixed_xpos = false; 	// needs updating, range getting random position from is not valid for dune library
bool fixed_yz_pos = false;
bool fixed_pos = false;	

//double PosMin[3] = {4.77e-1,-600.,0.}; 	//For random_pos option, generate in this range
//double PosMax[3] = {1.477,600,1395};     //This range is only a plane
double PosMin[3] = {10.,-658.,0.};      //For random_pos option, generate in this range
double PosMax[3] = {363.,600,1400};     //This range is whole detector

// Middle of the detector
double fixedX = (PosMax[0]+PosMin[0]) / 2; 	// cm 
double fixedY = (PosMax[1]+PosMin[1]) / 2; 	// cm 
double fixedZ = (PosMax[2]+PosMin[2]) / 2; 	// cm





///-------------------------------------
//-------- make time cut?-------------
///-------------------------------------
bool cut = false; 		// NB you can always make time cuts when you're analysing the files
double time_cut = 0.1; 	// in microseconds - 0.1 mu_s = 100 ns


///-------------------------------------
//------Light System Configuration------
///-------------------------------------
//--------------------------------------
///Config List:
///0 = Full Foils
///1 = Cath Foils
///2 = VUV only
const int config = 1; // cathode foils only configuration for dune
//--------------------------------------
//--------------------------------------

//--------------------------------------
// These bools are used in the scintillation timing functions
std::string libraryfile;
bool reflected;
bool reflT;
//--------------------------------------

//--------------------------------------
//TTree branches and data products:
//-------------------------------------
TFile event_file("event_file_Kr85B2_DUNE_tw1.root", "RECREATE", "Event File");

TTree *data_tree = new TTree("data_tree", "data tree");
TTree *data_tree_vuv = new TTree("data_tree_vuv", "data tree_vuv");
TTree *data_tree_vis = new TTree("data_tree_vis", "data tree_vis");

TTree *event_tree = new TTree("event_tree", "event tree");
double data_time;
double data_time_vuv;
double data_time_vis;

int data_pmt;
int data_pmt_vuv;
int data_pmt_vis;

int data_event;
int data_event_vuv;
int data_event_vis;

double data_x_pos;
double data_x_pos_vuv;
double data_x_pos_vis;

double data_y_pos;
double data_y_pos_vuv;
double data_y_pos_vis;

double data_z_pos;
double data_z_pos_vuv;
double data_z_pos_vis;

int event_no;
int event_vox;
double event_x_pos;
double event_y_pos;
double event_z_pos;
double event_E;
double event_decay_time;

//--------------------------------------

///-------------------------------------
//----LAr & Ar39 properties--------------------
///-------------------------------------
const double MassE = 0.510998910; 	// mass electron - MeV/c^2
const double Q_Ar = 0.565;			//Q value of decay - Ar39
const double Q_Co60B = 0.318;		//End point of beta decay of Co60[MeV]
const double Q_Ar42 = 0.599;		//End point of beta decay of Ar42[MeV]
const double Q_K42 = 3.525;
const double Q_40KB = 1.35;		//End point of beta decay of 40K[MeV]
const double Q_Kr85B1 = 0.84;		//End point of beta decay of Kr85[MeV]
const double Q_Kr85B2 = 0.687;
const double Q_Kr85G1 = 0.151;
const double Q_Kr85G2 = 0.305;
const double Q_Pb214 = 1.03;
const double Q_Bi214 = 3.2;

const double t_singlet = 0.000000006; 		//6ns
const double t_triplet = 0.0000015; 		//1.5 us
const double scint_time_window = 0.00001; 	//10 us

const int scint_yield_electron = 24000;	// Scintillation yield of LAr at 500 V/cm
const double activity_Ar = 1.; 			// Ar39 roughly 1 Bq/k
///-------------------------------------

///-------------------------------------
//----SN properties---------------------
///-------------------------------------
const double Eav = 20.;				// Average energy for SN spectrum
const double expected_sn = 2.8;		// For poisson weighting
///-------------------------------------

///-------------------------------------
//----Radon properties---------------------
///-------------------------------------
const int scint_yield_alpha = 16800; 	// SY of alpha particles at 500 V/cm - from larsoft
const double activity_Rn = 0.000021; 	// Bq/kg
const double massAlpha = 3727.3794; 	// alpha particle mass - MeV/c^2
const double Q_Rn = 5.590; 				// deposited energy from a radon decay - Rn-222 --> Po-218
const double Q_Po218 = 6.0;
const double Q_Po214 = 7.7;
///-------------------------------------

///-------------------------------------
//----TPC and PMT properties---------------------
///-------------------------------------
// QE of Arapucas, mesh efficiency  + /0.46 to remove bar attenuation factor included in library
const double quantum_efficiency = 0.025*0.7/0.46; 		
const double catcov = 0.8; 	// proportion of cathode covered by TPB
const double vuvfrac = 0.5;
const double visfrac = (1-vuvfrac) + 0.8*vuvfrac; 	// rest of PMTs (1-vuvfrac) sensitive to vis light + account for TPB covered PMTs' ability to

const double mass = 0.001396*(PosMax[0]-PosMin[0])*(PosMax[1]-PosMin[1])*(PosMax[2]-PosMin[2]); // density = 1.396 g/cm^3

const double frame_time = 0.0025; // 2.5 miliseconds; equivalent to the drift time of electrons in DUNE
const double time_window = 1; //readout window (running time of the simulation in seconds)
const double time_frames = int(time_window/frame_time); // number of frames registered

///-------------------------------------

///-------------------------------------
//----Number of Events------------------
///-------------------------------------
// Fixed energy (electron like) events:
const int max_events_FE = 1;

// Ar-39 events:
//const int max_events_Ar = 10;
const int max_events_Ar = activity_Ar * mass * time_window;//FULL volume for 1 TPC
const int Ar_decays_per_sec = activity_Ar* mass; // decay rate in one TPC

// Radon events:
const int max_events_Rn = 5.584e-5 * (PosMax[0]-PosMin[0])*(PosMax[1]-PosMin[1])*(PosMax[2]-PosMin[2]) * time_window;
const int max_events_Po218 = max_events_Rn;
const int max_events_Po214 = max_events_Rn;
const int max_events_Pb214 = max_events_Rn;
const int max_events_Bi214 = max_events_Rn;
//const int max_events_Rn = activity_Rn * mass * time_window;//Half volume for 1 (NOTE: for a small time window, this will probably return 0)
const double Rn_decays_per_sec = activity_Rn* mass; // decay rate in one TPC

// Supernova events:
const int max_events_SN = time_frames;
//int max_events_SN = utility::poisson(expected_sn,gRandom->Uniform(1.),1.);

// Solar neutrino events:
 const int max_events_SO = 1;
//int max_events_SO = utility::poisson(expected_sn,gRandom->Uniform(1.),1.);

const int max_events_Co60B = 8.2e-5 * (PosMax[0]-PosMin[0])*(PosMax[1]-PosMin[1])*(PosMax[2]-PosMin[2]) * time_window;//For beta decay, near 100% would have beta decay and 200% gamma decay
const int max_events_Co60G1 = max_events_Co60B;
const int max_events_Co60G2 = max_events_Co60B;
const int max_events_Ar42 = 1.283768e-7 * (PosMax[0]-PosMin[0])*(PosMax[1]-PosMin[1])*(PosMax[2]-PosMin[2]) * time_window;//1.41e-3 Bq*cm^-3 from mcc11 simulation
const int max_events_K42 = max_events_Ar42 * 0.819;
const int max_events_40KB = 2.7195e-3 * (PosMax[0]-PosMin[0])*(PosMax[1]-PosMin[1])*(PosMax[2]-PosMin[2]) * time_window * 0.8928;//89.28% ratio for beta decay
const int max_events_40KG = 2.7195e-3 * (PosMax[0]-PosMin[0])*(PosMax[1]-PosMin[1])*(PosMax[2]-PosMin[2]) * time_window * 0.1072;//10.72% ratio for gamma decay
const int max_events_Kr85B1 = 1.6e-4 * (PosMax[0]-PosMin[0])*(PosMax[1]-PosMin[1])*(PosMax[2]-PosMin[2]) * time_window * 0.785;//near 100% of Kr82 would have beta decay
const int max_events_Kr85B2 = 1.6e-4 * (PosMax[0]-PosMin[0])*(PosMax[1]-PosMin[1])*(PosMax[2]-PosMin[2]) * time_window * 0.14;
const int max_events_Kr85G1 = 1.6e-4 * (PosMax[0]-PosMin[0])*(PosMax[1]-PosMin[1])*(PosMax[2]-PosMin[2]) * time_window * 0.785 * 0.752;
const int max_events_Kr85G2 = max_events_Kr85B2;

//--------------------------------------
//--------------------------------------
// Don't change these
// used to read optical channel locations into
vector<vector<double>> myfile_data;
// initialise library access class
LibraryAccess lar_light;
// lists of variables for generating
vector<double> energy_list;
vector<double> decay_time_list;
vector<vector<double>> position_list;
vector<int> voxel_list;

#endif
