#!/bin/bash
fmain=$PWD
fexe=executable
exe=1d_test
plot1=utility/plot.gnu

Results=Run_1



if [ -d $Results ]
then
	echo "The folder $Results exist. change name or delete the folder"
	exit
else
mkdir $Results
fi

cd $fexe

for dt0 in `seq 1 2`
do
cd $fmain/$fexe
dt=$(echo $dt0 | awk '{print $1/10.0}' )
echo "time step is: " $dt
f1=dt_$dt

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
time_step:      $dt         [-]
discretisation_x:       1.0         [-]
N:          10                  [-]
run:            100             [-]        
EOF

cd $fexe
echo ""
echo "!!!!!!!!!!!!!!!!"
echo "runing code ...."
time ./$exe
echo "finished, now plotting"
gnuplot plot.gnu
cp Temperature_Profile.png $fmain/$Results/Temperature_Profile_dt$dt.png
echo "finished time step of ", $dt
echo ""
echo ""

done


