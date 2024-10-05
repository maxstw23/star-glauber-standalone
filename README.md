# STAR Glauber standalone

This project allows one to work with STAR's Glauber code with plain ROOT. Adapted from Vinh Luong and modified slightly for easier operation without grid access by Xiatong Wu. 

Please note the procedures below describe a significantly simplified workflow of the official STAR Glauber procedures, which can be found at https://github.com/star-bnl/star-sw/tree/main/StRoot/PWGTools/CentralityCalibration/Glauber/star_glauber

Prerequisite:
- ROOT
- CMake (ver. 3.1 or higher)

## Step 0.

```bash
git clone https://github.com/maxstw23/star-glauber-standalone
cd star-glauber-standalone
```
## Step 1. Compilation
```bash
mkdir build
cd build
cmake -B. -S../StRoot/
make -j4
```

## Step 2. Generate Glauber Tree

Generate a simple tree without parameter tuning, which will be used to generate a ncoll vs. npart correlation. For 1000 events, 200 GeV AuAu and deformation set to true, one can run 
```bash
./doFastGlauberMcMaker oTest.root 1000 AuAu 200 default 1 0.0
```
Then, generate a ncoll vs. npart correlation by
```bash
echo "oTest.root" > test.list
./addNcollVsNpart test.list
```

Note that for all executables, execute them without argument will print help messages. 

## Step 3. Parameter Scan
Next, we can start the parameter scanning process, the core step for centrality definition using Glauber. The idea is to determine a best set of parameters that allow Glauber simulated multiplicity distribution to best represent STAR's refmult distribution. The scan is performed over three parameters: $N_pp$, $k$ and $x$. To change the range of these parameters, one needs to modify line 217 in ../doNbdFitMaker.C and then recompile. 

Otherwise, for 10000 events and use the sample 19.6 GeV refmult distribution:
```bash
mkdir RatioChi2Files
./doNbdFitMaker oTest2.root 10000 ../run19_19p6GeV.root ncoll_npart.root 50 1.37 1.0 0.13 1. 1. 1 > oTest2.out
```
This will generate many small Ratio*.root files and one Chi2*.root file in the RatioChi2Files.

## Step 4. Find Best Parameter
Find the best set of parameters by finding the minimum chi2/ndf. The information was stored in oTest2.out in the previous step. 
```bash
cp -R ../getBestChi2_fromCat ./
cd getBestChi2_fromCat
./extractChi2Lines.sh
./genMinChi2List.sh
```
You can now find the centrality definition in centrality_def. The Ratio*.root file corresponding to the minimum chi2/ndf can be also found in the list minChi2_file.list. 
