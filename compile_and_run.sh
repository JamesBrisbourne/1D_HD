fmain=$PWD
fexe=executable
exe=1d_test
plot1=utility/plot.gnu

bash compile.sh
cd $fexe
echo ""
echo "!!!!!!!!!!!!!!!!"
echo "runing code ...."
time ./$exe
echo "finished, now plotting"
gnuplot $fmain/$plot1

