f0 = "Temperature_Profile_dt0.1.dat"
set pm3d map
set xlabel "X-coordinate"
set ylabel "Time"
set cblabel "Temperature"

set terminal unknown 
splot f0 u 2:1:3 w pm3d t ""



ymax = GPVAL_DATA_Y_MAX
set yrange [0:ymax]
set title "Plot to show how the temperature varies with spacial position and time"
set terminal pngcairo size 1000,600 font ",10"
set output "Temperature_Profile.png"
splot f0 u 2:1:3 w pm3d t ""

