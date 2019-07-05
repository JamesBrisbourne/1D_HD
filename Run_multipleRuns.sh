#!/bin/bash
fmain=$PWD
fexe=executable
exe=1d_test
plot1=utility/plot.gnu

Results=Run_4



if [ -d $Results ]
then
	echo "The folder $Results exist. change name or delete the folder"
	exit
else
mkdir $Results
fi

cd $fexe

for runs0 in `seq 1 10000`
do
cd $fmain/$fexe
runs=$(echo $runs0 | awk '{print $1*100}' )
echo "number of runs: " $runs
f1=runs_$runs

if [ -d $f1 ]
then
	"folder $f1 exist"
	exit
else
	mkdir $f1
fi


cd $f1
mkdir $fexe
mkdir input
cp $fmain/$fexe/$exe $fexe/
cp $fmain/$plot1 $fexe/
cat << EOF > input/input.in
time_step:      0.0000001         [-]
discretisation_x:       0.001         [-]
N:          100                  [-]
run:            $runs             [-]        
EOF

cd $fexe
echo ""
echo "!!!!!!!!!!!!!!!!"
echo "runing code ...."
time ./$exe
echo "finished, now plotting"
gnuplot plot.gnu
cp Temperature_Profile.png $fmain/$Results/Temperature_Profile_runs$runs.png
echo "finished time step of ", $runs
echo ""
echo ""

done


