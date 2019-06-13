f0 = "Temperature_Profile_dt0.1.dat"
set pm3d map
set xlabel "x-coordinate"
set ylabel "time"
set cblabel "temperature"
set terminal png enhanced size "1000,800" font ",20"
set output "Temperature_Profile.png"
splot f0 u 2:1:3 w pm3d t ""
