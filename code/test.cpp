#include <stdio.h>
#include <vector>
#include <iostream>
#include <fstream>  
#include <sstream>
#include <string>
#include <math.h>
#include <numeric>
#include <iomanip>

using std::vector;

// double density = 1000.0;
// double thermal_conductivity = 0.5;
// double specific_heat = 4000.0;
// double constant = thermal_conductivity/(density + specific_heat);

struct input_variables {
	double dt;
	double dx;
	int N;
	int runs;
};

//only here to stop main() freaking out 
input_variables input();
void print_config(const std:: string &file_name, double dt, double time0, const vector<vector<double>>& T_array, vector<double> analytic_sol);
vector<vector<double>> time_integration(double dt, double dx, const vector<vector<double>>& T_array, double time0);
//double prefactor(const vector<vector<double>>& T_array, int iter); 


int main() {
	double dt = 0.1;
	
	double time0 = 0.0;

	const input_variables inputs = input();

	std::stringstream integration_timestep;
	integration_timestep.str("");
	integration_timestep << dt;

	//integration_timestep << inputs.dt; THIS WILL FIX FILE NAME ISSUE BUT BREAK OTHER THINGS

	std::string outFileTemperatureProfile;	
	outFileTemperatureProfile.append("Temperature_Profile_dt");
	outFileTemperatureProfile.append(integration_timestep.str());
	outFileTemperatureProfile.append(".dat");

	// This is how to delare a vector (basically a better array), with N elements all of value 0
	
	vector<vector<double>> T_array(4, vector<double> (inputs.N+1, 0));
	vector<double> analytic_sol(inputs.N+1, 0);
	vector<double> difference(inputs.N+1, 0);

	for (int i = 0; i < inputs.N+1; i++) {
		T_array[1][i] = 1.0;
		T_array[2][i] = 1.0;
		T_array[3][i] = 1.0;
	}


	for (int i = 1; i < inputs.N; i++) {
		T_array[0][i] = sin((4.0*atan(1)*i)/inputs.N);
		printf("%f", T_array[0][i]);
	}


	// changes the value of the first element in the array
	T_array[0][0] = 0.0;
	T_array[0][inputs.N] = 0.0;


	print_config(outFileTemperatureProfile, inputs.dt, time0, T_array, analytic_sol);

	
	for (int i = 0; i < inputs.runs;i++) { // iterates for as many times as specified in the 'runs' section of the input file
		for (int i = 1; i < (inputs.N-1); i++) {
			analytic_sol[i] = (sin(M_PI*i/inputs.N))*(exp(-((M_PI)*(M_PI)*time0)/(inputs.N*inputs.N*inputs.dx*inputs.dx)));
		}

		T_array = time_integration(inputs.dt, inputs.dx, T_array, time0); // runs euler step
		
		time0 += inputs.dt; // increments time
		//difference[i] = T_array[0][i] - analytic_sol[i];
		print_config(outFileTemperatureProfile, inputs.dt, time0, T_array, analytic_sol);
	}



	return 0;
   }

vector<vector<double>> time_integration(double dt, double dx, const vector<vector<double>>& T_array, double time0) {
// does the Euler integration step on 'T_array' 
// the new value for each position is loaded into 
// T_update, finally T_update becomes T_array ready 
// for the next iteration

	const int N = T_array[0].size();
	double prefactor = 0.0;
	vector<vector<double>> T_update(4, vector<double> (N, 0));

	T_update = T_array;
	
	// boundary conditions
	T_update[0][0] = T_array[0][0];
	T_update[0][N] = T_array[0][N];

for (int i = 1; i < (N-1); i++) {
	T_update[0][i] = T_array[0][i] + ((1.0*dt)/(dx*dx) * (T_array[0][i+1] - 2.0*T_array[0][i] + T_array[0][i-1]));

}


return T_update;
}



void print_config(const std:: string &file_name, double dt, double time0, const vector<vector<double>>& T_array, vector<double> analytic_sol) {
// handles all the needs of outputting data to a file.
// the output file name is specified by the arguement used
// when calling the function.

    if (abs(time0 - dt) < (dt/100.0)) {
    	std::ofstream outFile(file_name);
    	std::cout << "write to file " << file_name << std::endl;
    }
    std::ofstream outFile(file_name, std::ofstream::app);
    if(!outFile)
    {
        std::cout << std::endl << "Failed to open the file: "<< file_name <<std::endl;
        exit(1);
    }  
    
 
    for (int i=0;i < T_array[0].size();i++){
    // this line specifies what gets output to the file, "\t" indicates tabs between the data
    outFile << time0 << "\t" << i << "\t" << T_array[0][i] << "\t" << analytic_sol[i] << "\t" << std::endl;
        }

    outFile << std::endl;

    outFile.close();
}

input_variables input() {

	std::string s1, s2; //dummy variables to take column 1 and 2 from the input file

	std::string file_name ="../input/input.in"; //self explanatory
    
    std::ifstream inFile(file_name);

    std::cout << "read from file "<< file_name << std::endl;
    
    // error checking when reading the file
    if(!inFile)
    {
        std::cout << std::endl << "Failed to read from the file: "<< file_name << std::endl;
        exit(1);
    }

    input_variables result;
    
    //  read the first and second column from the input file
	inFile >> s1 >> result.dt >> s2;
	// print this to terminal
	std::cout << s1 << "\t" << result.dt << "\t" << s2 << std::endl;  
	
	inFile >> s1 >> result.dx >> s2;
	std::cout << s1 << "\t" << result.dx << "\t" << s2 << std::endl;
	
	inFile >> s1 >> result.N >> s2;
	std::cout << s1 << "\t" << result.N << "\t" << s2 << std::endl;
	
	inFile >> s1 >> result.runs >> s2;
	std::cout << s1 << "\t" << result.runs << "\t" << s2 << std::endl;
	return result;
}