
#ifdef _VANILLA_ROOT_
#include <iostream>
#include <fstream>
#include "TH2.h"
#include "TChain.h"
#include "TString.h"
#include "TFile.h"
#include "TString.h"
#include "TStopwatch.h"

#endif
//____________________________________________________________________________________________________
void addNcollVsNpart(
		const Char_t* inputFileList = "./LIST/tree.default.list"
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

	std::ifstream fin(inputFileList);
	if(!fin)
	{
		std::cout << Form("addNcollVsNpart can't open %s", inputFileList);
		return;
	}

	TChain t("tree");
	TString file;
	while(fin>>file)
	{
		std::cout << "Add " << file << " into chain" << std::endl;
		t.Add(file);
	}

	TH2* hNcoll_Npart = new TH2D
		("hNcoll_Npart", "hNcoll_Npart;Npart;Ncoll;",
		 //      StGlauberConstUtilities::GetNpartBin(), 0, StGlauberConstUtilities::GetNpartMax(),
		 //      StGlauberConstUtilities::GetNcollBin(), 0, StGlauberConstUtilities::GetNcollMax()
		 500, 0, 500, 1800, 0, 1800
		);
	t.Draw("ncoll:npart>>hNcoll_Npart", "npart>=2&&ncoll>=1");

	// Write output ROOT file
	TFile* outputFile = TFile::Open("ncoll_npart.root", "recreate");
	hNcoll_Npart->Print();
	hNcoll_Npart->Write();
	outputFile->Close();
}


#ifdef _VANILLA_ROOT_
int main(int argc, char *argv[]) {

	const char* inputFileList;

  switch (argc) {
  case 2:
    inputFileList = argv[1];
    break;
  default:
    std::cout << "Usage: addNcollVsNpart inputFileList" << std::endl; 
		return -1;
  }
  TStopwatch timer;
  timer.Start();
  addNcollVsNpart(inputFileList);
  timer.Stop();
  timer.Print();
}
#endif // #ifdef _VANILLA_ROOT_