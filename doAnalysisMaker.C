#ifdef _VANILLA_ROOT_
#include <iostream>
#include "TSystem.h"
#include "TString.h"
#include "TStopwatch.h"
#include "StGlauberAnalysisMaker.h"
#endif
//____________________________________________________________________________________________________
void doAnalysisMaker(
		const TString system        = "AuAu_39GeV",
		const TString inputFileList = "tmp.list",
		const TString outputFile    = "ana.root",
		const TString type          = "default",
		const TString tabledir      = "./table",
		const Bool_t  doReweighting = kFALSE,
		const Bool_t  doUnitWeight  = kFALSE,
		const UShort_t debug        = 0
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

	StGlauberAnalysisMaker* maker = new StGlauberAnalysisMaker(type, system, outputFile, tabledir);
	
	if(debug)         maker->DebugOn();
	if(doReweighting) maker->ReweightingOn() ;
	if(doUnitWeight)  maker->UnitWeightOn() ;
	
	maker->Run(inputFileList);
	maker->Finish();
}

//____________________________________________________________________________________________________
void doAnalysisMakerOneFile( 
		const TString system        = "AuAu_39GeV",
		const TString inputFile     = "icmaker.root",
		const TString outputFile    = "ana.root",
		const TString type          = "default",
		const TString tabledir       = "./table",
		const Bool_t  doReweighting = kFALSE,
		const Bool_t  doUnitWeight  = kFALSE,
		const UShort_t debug        = 3
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

	StGlauberAnalysisMaker* maker = new StGlauberAnalysisMaker(type, system, outputFile, tabledir);

	if(debug)         maker->DebugOn();
	if(doReweighting) maker->ReweightingOn() ;
	if(doUnitWeight)  maker->UnitWeightOn() ;

	maker->RunFile(inputFile);
	maker->Finish();
}


#ifdef _VANILLA_ROOT_
int main(int argc, char *argv[]) {

	const char* system;
	const char* inputFileList;
	const char* outputFile;
	const char* type;
	const char* tabledir;
	Bool_t  		doReweighting;
	Bool_t  		doUnitWeight;
	UShort_t 		debug;

  switch (argc) {
  case 9:
    system 				= argv[1];
		inputFileList = argv[2];
		outputFile		= argv[3];
		type					= argv[4];
		tabledir			= argv[5];
		doReweighting = ( atoi(argv[6]) != 0 ) ? true : false;
		doUnitWeight  = ( atoi(argv[7]) != 0 ) ? true : false;
		debug					= atoi(argv[8]);
    break;
  default:
    std::cout << "Usage: doAnalysisMaker system  inputFileList  outputFile  type  tabledir  doReweighting  doUnitWeight  debug" << std::endl; 
		return -1;
  }
  TStopwatch timer;
  timer.Start();
  doAnalysisMaker(system,inputFileList,outputFile,type,tabledir,doReweighting,doUnitWeight,debug);
  timer.Stop();
  timer.Print();
}
#endif // #ifdef _VANILLA_ROOT_