#ifdef _VANILLA_ROOT_
#include <iostream>
#include "TSystem.h"
#include "TString.h"
#include "TStopwatch.h"
#include "StNbdFitMaker.h"
#endif
//____________________________________________________________________________________________________
void doNbdFitMaker(
    const Char_t*  outputFileName    = "",
    const Int_t    nevents           = 1000,
    const Char_t*  realData          = "run11.MonTrg.refMultCorrWithWeight.histo.root",
    const Char_t*  glauber           = "ncoll_npart.root",
    const Double_t multiplicityCut   = 100,
    const Double_t npp               = 1.37,
    const Double_t k                 = 1.0,
    const Double_t x                 = 0.13,
    const Double_t efficiency        = 1.00,
    const Double_t triggerbias       = 1.00,
    const Bool_t   isConstEfficiency = kTRUE
)
{
#ifndef _VANILLA_ROOT_
	gSystem->Load("St_base");
	gSystem->Load("StUtilities");
	gSystem->Load("StGlauberUtilities");
	gSystem->Load("StCentralityMaker");
	gSystem->Load("StGlauberTree");
	gSystem->Load("StFastGlauberMcMaker");
#else
#if ROOT_VERSION_CODE >= ROOT_VERSION(6, 0, 0)
  R__LOAD_LIBRARY(StFastGlauberMcMaker.so);
  R__LOAD_LIBRARY(StUtilities.so);
  R__LOAD_LIBRARY(StGlauberUtilities.so);
  R__LOAD_LIBRARY(StCentralityMaker.so);
  R__LOAD_LIBRARY(StGlauberTree.so);
#else
	gSystem->Load("StUtilities");
	gSystem->Load("StGlauberUtilities");
	gSystem->Load("StCentralityMaker");
	gSystem->Load("StGlauberTree");
	gSystem->Load("StFastGlauberMcMaker");
#endif
#endif

  StNbdFitMaker* maker = new StNbdFitMaker();

  // Set parameters
  maker->SetParameters(npp, k, x, efficiency, triggerbias, isConstEfficiency);

  // Set low multiplicity cut off for fitting
  maker->SetMinimumMultiplicityCut(multiplicityCut);

 // maker->ReadData(realData, glauber, "hRefMultCorr");
  maker->ReadData(realData, glauber, "hRefMult");
   //maker->ReadData(realData, glauber, "hRefMultCorr_Weighted");

  // Fit
  maker->Fit(nevents, outputFileName);
}

//____________________________________________________________________________________________________
void scan(
    const Int_t    nevents = 200000,
    const Char_t*  realData = "run11.MonTrg.refMultCorrWithWeight.histo.root",
    const Char_t*  glauber  = "ncoll_npart.root",
    const Double_t multiplicityCut = 100,
    const Int_t    nppbin = 10, const Double_t nppmin = 1.1,  const Double_t nppmax = 1.5,
    const Int_t    kbin   = 10,  const Double_t kmin   = 4.0,  const Double_t kmax   = 10.0,
    const Int_t    xbin   = 10, const Double_t xmin   = 0.1, const Double_t xmax   = 0.2,
    //const Double_t x = 0.12,
    //const Int_t effbin = 50, const Double_t effmin = 0.08, const Double_t effmax = 0.18,
    const Double_t efficiency        = 1.00,
    const Double_t triggerbias       = 1.00,
    const Bool_t   isConstEfficiency = kTRUE
)
{
#ifndef _VANILLA_ROOT_
	gSystem->Load("St_base");
	gSystem->Load("StUtilities");
	gSystem->Load("StGlauberUtilities");
	gSystem->Load("StCentralityMaker");
	gSystem->Load("StGlauberTree");
	gSystem->Load("StFastGlauberMcMaker");
#else
#if ROOT_VERSION_CODE >= ROOT_VERSION(6, 0, 0)
  R__LOAD_LIBRARY(StFastGlauberMcMaker.so);
  R__LOAD_LIBRARY(StUtilities.so);
  R__LOAD_LIBRARY(StGlauberUtilities.so);
  R__LOAD_LIBRARY(StCentralityMaker.so);
  R__LOAD_LIBRARY(StGlauberTree.so);
#else
	gSystem->Load("StUtilities");
	gSystem->Load("StGlauberUtilities");
	gSystem->Load("StCentralityMaker");
	gSystem->Load("StGlauberTree");
	gSystem->Load("StFastGlauberMcMaker");
#endif
#endif

  StNbdFitMaker* maker = new StNbdFitMaker();

  // Set low multiplicity cut off for fitting
  maker->SetMinimumMultiplicityCut(multiplicityCut);

  //// Dump centrality bin boundary 
  //maker->DoCentralityDetermination();

  // Set dummy parameters
  maker->SetParameters(nppmin, kmin, xmin, efficiency, triggerbias, isConstEfficiency);
  //maker->SetParameters(nppmin, kmin, x, effmin, triggerbias, isConstEfficiency);

  // Read input files
  //maker->ReadData(realData, glauber, "hRefMultCorr");
  maker->ReadData(realData, glauber, "hRefMult");
  //maker->ReadData(realData, glauber, "hRefMultCorr_Weighted");

  // Fit
  maker->Scan(
		  nevents, 
		  nppbin, nppmin, nppmax, 
		  kbin, kmin, kmax, 
		  xbin, xmin, xmax,
		  efficiency, triggerbias, isConstEfficiency
		  );
  //maker->Scan(nevents, nppbin, nppmin, nppmax, kbin, kmin, kmax, x,
  //    effbin, effmin, effmax, triggerbias, isConstEfficiency);
}

//____________________________________________________________________________________________________
void simulateMultiplicity(
    const Char_t*  outputFileName  = "test.root",
    const Int_t    nevents         = 500000,
    const Char_t*  glauber         = "ncoll_npart.root",
    const Double_t npp             = 2.9,
    const Double_t k               = 2.0,
    const Double_t x               = 0.20,
    const Double_t efficiency      = 1.00,
    const Double_t triggerbias     = 1.00,
    const Bool_t   isConstEfficiency = kTRUE
){
#ifndef _VANILLA_ROOT_
	gSystem->Load("St_base");
	gSystem->Load("StUtilities");
	gSystem->Load("StGlauberUtilities");
	gSystem->Load("StCentralityMaker");
	gSystem->Load("StGlauberTree");
	gSystem->Load("StFastGlauberMcMaker");
#else
#if ROOT_VERSION_CODE >= ROOT_VERSION(6, 0, 0)
  R__LOAD_LIBRARY(StFastGlauberMcMaker.so);
  R__LOAD_LIBRARY(StUtilities.so);
  R__LOAD_LIBRARY(StGlauberUtilities.so);
  R__LOAD_LIBRARY(StCentralityMaker.so);
  R__LOAD_LIBRARY(StGlauberTree.so);
#else
	gSystem->Load("StUtilities");
	gSystem->Load("StGlauberUtilities");
	gSystem->Load("StCentralityMaker");
	gSystem->Load("StGlauberTree");
	gSystem->Load("StFastGlauberMcMaker");
#endif
#endif

  StNbdFitMaker* maker = new StNbdFitMaker();

  // Set parameters
  maker->SetParameters(npp, k, x, efficiency, triggerbias, isConstEfficiency);

  // Read input files
  // maker->ReadGlauber(glauber, 3000, 0, 3000);

  // Fit
  // maker->Simulate(nevents, outputFileName);
}



#ifdef _VANILLA_ROOT_
int main(int argc, char *argv[]) {

  const Char_t*  outputFileName;
  Int_t    nevents;
  const Char_t*  realData;
  const Char_t*  glauber;
  Double_t multiplicityCut;
  Double_t npp;
  Double_t k;
  Double_t x;
  Double_t efficiency;
  Double_t triggerbias;
  Bool_t   isConstEfficiency;

  switch (argc) {
  case 12:

    outputFileName    = argv[1];
    nevents           = atoi(argv[2]);
    realData          = argv[3];
    glauber           = argv[4];
    multiplicityCut   = atof(argv[5]);
    npp               = atof(argv[6]);
    k                 = atof(argv[7]);
    x                 = atof(argv[8]);
    efficiency        = atof(argv[9]);
    triggerbias       = atof(argv[10]);
    isConstEfficiency = ( atoi(argv[11]) != 0 ) ? true : false;

    break;
  default:
    std::cout << "Usage: doNbdFitMaker outputFileName nevents realData glauber multiplicityCut npp k x efficiency triggerbias isConstEfficiency" << std::endl; 
		return -1;
  }
  TStopwatch timer;
  timer.Start();
  doNbdFitMaker(outputFileName,nevents,realData,glauber,multiplicityCut,npp,k,x,efficiency,triggerbias,isConstEfficiency);
  scan(nevents, realData, glauber, multiplicityCut, 10, 1.1, 1.5, 10, 4.0, 10.0, 10, 0.1, 0.2, efficiency, triggerbias, isConstEfficiency);
  timer.Stop();
  timer.Print();
}
#endif // #ifdef _VANILLA_ROOT_