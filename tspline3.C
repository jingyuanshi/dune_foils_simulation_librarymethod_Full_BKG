#include "TFile.h"
#include "TF1.h"
#include "TGraph.h"

//This code is used to solve the terrible fit by TSpline3

int tspline3()
{
  TGraph *g = new TGraph("hep_energy_spectrum.txt");
  TSpline3 *spline = new TSpline3("hepspline",g);
  TFile *f = new TFile("hep_neu_energy_spline.root","RECREATE");
  spline->Write();
  g->Write();
  f->Close();

  return 0;
}
