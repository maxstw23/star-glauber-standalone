#!/bin/bash
############################################################
# original author Zaochen Ye
# new STAR users are responsible to improve the script
############################################################

rm allout.list
rm catLOG_for_MinChi2

# inDir=../glauberOut

# find $inDir/LOG_Scan -name "*.out" > allout.list

inDir=../

find $inDir -maxdepth 1 -name "*.out" > allout.list

echo "generating catLOG_for_MinChi2, be patient !!!"

for ifile in $(cat allout.list)
do
	#head -44 ${ifile} | tail -1 >> catLOG_for_MinChi2 #if turn off centrality definition 
	#head -206 ${ifile} | tail -1 >> catLOG_for_MinChi2  #if with centrality definition
	# find the line with "chi2/ndf" and print this line to catLOG_for_MinChi2
	grep "chi2/ndf" ${ifile} >> catLOG_for_MinChi2
done

echo "generated catLOG_for_MinChi2"

exit


