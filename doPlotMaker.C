#ifdef _VANILLA_ROOT_
#include <iostream>
#include "TString.h"
#include "TStopwatch.h"
#include "StGlauberPlotMaker.h"
#endif
void doPlotMaker(
		const TString name   = "Npart",
		const TString energy = "200",
		const UInt_t  mode   = 1 // Take maximum difference as a systematic error
		)
{
	// type            description                  node
	// default          default                      default
	// small            small R, large d             small
	// large            large R, small d             large
	// smallXsec        small sigma_{NN}             smallXsec
	// largeXsec        large sigma_{NN}             largeXsec
	// gray             gray disk profile            gray
	// gauss            gaussian profile             gauss
	// smallNpp         small (npp, x)               default
	// largeNpp         large (npp, x)               default
	// smallTotal       -5% total cross section      default
	// largeTotal       +5% total cross section      default


#ifndef _VANILLA_ROOT_
	gSystem->Load("St_base");
	gSystem->Load("StUtilities");
	gSystem->Load("StGlauberAnalysisMaker");
#else
#if ROOT_VERSION_CODE >= ROOT_VERSION(6, 0, 0)
  R__LOAD_LIBRARY(StUtilities.so);
  R__LOAD_LIBRARY(StGlauberAnalysisMaker.so);
#else
	gSystem->Load("StUtilities");
	gSystem->Load("StGlauberAnalysisMaker");
#endif
#endif
	
	StGlauberPlotMaker* maker = new StGlauberPlotMaker(name);
	//  const Int_t nFiles = 11 ;
	//  const TString type[] = {
	//    "default", "small", "large", "smallXsec", "largeXsec",
	//    "gray", "gauss", "smallNBD", "largeNBD", "smallTotal", "largeTotal"
	//  };
	//  const Int_t nFiles = 1 ;
	//  const Int_t nFiles = 10 ;
	//  const Int_t nFiles = 12 ;
	//  const TString type[] = {
	//    "default", "small", "large", "smallXsec", "largeXsec",
	//    "gauss", "smallNpp", "largeNpp", "smallTotal", "largeTotal",
	//    "lowrw", "highrw"
	//  };

	const Int_t nFiles = 10 ;
	const TString type[] = 
	{
		"default",  "small",    "large", "smallXsec",  "largeXsec",
		"smallNpp", "largeNpp", "gauss", "smallTotal", "largeTotal"
		//    "smallNpp", "largeNpp", "gauss"
	};

	//----------------------------------------------------------------------------------------------------
	// Description for Au+Au 200 GeV Run10 (default)
	//----------------------------------------------------------------------------------------------------
	TString description[] = 
	{
		"default",
		"small R, large d",
		"large R, small d",
		"small #sigma_{NN}=41mb",
		"large #sigma_{NN}=43mb",
		//    "small n_{pp}: (npp, x) = (2.55, 0.11)",
		//    "large n_{pp}: (npp, x) = (2.31, 0.15)",
		"small n_{pp}: (npp, x) = (2.153, 0.13)",
		"large n_{pp}: (npp, x) = (1.948, 0.17)",
		"gauss profile",
		"-5% total cross section",
		"+5% total cross section"
	};

	if( energy.Contains("200") ) 
	{
		std::cout << "Initialize 200 GeV" << std::endl;
	}

	//----------------------------------------------------------------------------------------------------
	// Description for Au+Au 39 GeV Run10
	//----------------------------------------------------------------------------------------------------
	if( energy.Contains("39") ) 
	{
		std::cout << "Initialize 39 GeV" << std::endl;
		description[3] = "small #sigma_{NN}=33mb" ;
		description[4] = "large #sigma_{NN}=35mb" ;
		description[5] = "small n_{pp}: (npp, x) = (1.44, 0.14)" ;
		description[6] = "large n_{pp}: (npp, x) = (1.60, 0.10)" ;
	}

#if 0
	const TString description[] = {
		"default",
		"-2% R, +10% d",
		"+2% R, -10% d",
		"small #sigma_{NN}=33mb",
		"large #sigma_{NN}=35mb",
		//    "gray disk profile",
		"gaussian profile",
		"small n_{pp}: (npp, x) = (1.44, 0.14)",
		"large n_{pp}: (npp, x) = (1.60, 0.10)",
		"-5% total cross section",
		"+5% total cross section",
		"Re-weighting +(-) 2#sigma for p_{0}(p_{1})",
		"Re-weighting -(+) 2#sigma for p_{0}(p_{1})"
	};
#endif

	//----------------------------------------------------------------------------------------------------
	// Description for Au+Au 11.5 GeV Run10
	//----------------------------------------------------------------------------------------------------
	if( energy.Contains("11.5") ) {
		std::cout << "Initialize 11.5 GeV" << std::endl;
		description[3] = "small #sigma_{NN}=30.2mb" ;
		description[4] = "large #sigma_{NN}=32.2mb" ;
		description[5] = "small n_{pp}: (npp, x) = (1.01, 0.14)" ;
		description[6] = "large n_{pp}: (npp, x) = (1.11, 0.10)" ;
	}

#if 0
	const TString description[] = {
		"default",
		"small R, large d",
		"large R, small d",
		"small #sigma_{NN}=30.2mb",
		"large #sigma_{NN}=32.2mb",
		"gaussian profile",
		"small n_{pp}: (npp, x) = (0.82, 0.14)",
		"large n_{pp}: (npp, x) = (0.90, 0.10)",
		"-5% total cross section",
		"+5% total cross section"
	};
#endif
	//----------------------------------------------------------------------------------------------------
	// Description for Au+Au 7.7 GeV Run10
	//----------------------------------------------------------------------------------------------------
	if( energy.Contains("7.7") ) {
		std::cout << "Initialize 7.7 GeV" << std::endl;
		description[3] = "small #sigma_{NN}=29.8mb" ;
		description[4] = "large #sigma_{NN}=31.8mb" ;
		description[5] = "small n_{pp}: (npp, x) = (0.85, 0.14)" ;
		description[6] = "large n_{pp}: (npp, x) = (0.93, 0.10)" ;
	}

#if 0
	const TString description[] = {
		"default",
		"small R, large d",
		"large R, small d",
		"small #sigma_{NN}=29.8mb",
		"large #sigma_{NN}=31.8mb",
		//    "gaussian profile",
		"small n_{pp}: (npp, x) = (0.85, 0.14)",
		"large n_{pp}: (npp, x) = (0.93, 0.10)",
		"-5% total cross section",
		"+5% total cross section"
	};
	//    "small n_{pp}: (npp, x) = (0.82, 0.14)", // Fast offline
	//    "large n_{pp}: (npp, x) = (0.90, 0.10)", // Fast offline
#endif

	for(Int_t i=0; i<nFiles; i++)
	{
		std::cout << description[i] << std::endl;
		const TString tableName(Form("./table/table_%s_%s_vs_centrality.txt", type[i].Data(), name.Data()));
		maker->Read(tableName, description[i]) ;
	}

	maker->Draw(mode) ;
}

#ifdef _VANILLA_ROOT_
int main(int argc, char *argv[]) {

	const char* name;
	const char* energy;
	UInt_t  mode;

  switch (argc) {
  case 4:
    name   = argv[1];
    energy = argv[2];
    mode   = atoi(argv[3]);
    break;
  default:
    std::cout << "Usage: doPlotMaker name energy mode" << std::endl; 
		return -1;
  }
  TStopwatch timer;
  timer.Start();
  doPlotMaker(name,energy,mode);
  timer.Stop();
  timer.Print();
}
#endif // #ifdef _VANILLA_ROOT_