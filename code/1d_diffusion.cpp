#include <stdio.h>
#include <vector>
#include <iostream>
#include <fstream>  
#include <sstream>
#include <string>
#include <math.h>

using std::vector;

double density = 1000.0;
double thermal_conductivity = 0.5;
double specific_heat = 4000.0;
double constant = thermal_conductivity/(density + specific_heat);

struct input_variables {
	double dt;
	double dx;
	int N;
	int runs;
};

//only here to stop main() freaking out 
input_variables input();
void print_config(const std:: string &file_name, double dt, double time0, const vector<double>& T_array);
vector<double> time_integration(double dt, double dx, const vector<double>& T_array);


int main() {
	double dt = 0.1;
	double dx = 1.0;
	int runs = 50;
	double time0 = 0.0;

	printf("%f\n",constant );
	std::stringstream integration_timestep;
	integration_timestep.str("");
	integration_timestep << dt;

	std::string outFileTemperatureProfile;	
	outFileTemperatureProfile.append("Temperature_Profile_dt");
	outFileTemperatureProfile.append(integration_timestep.str());
	outFileTemperatureProfile.append(".dat");

	const input_variables inputs = input();

	// This is how to delare a vector (basically a better array), with N elements all of value 0
	
	vector<double> T_array(inputs.N,0);

	// changes the value of the first element in the array
	T_array[0] = 37;
	
	
	for (int i = 0; i < runs;i++) { // iterates for as many times as specified in the 'runs' section of the input file
		T_array = time_integration(inputs.dt, inputs.dx, T_array); // runs euler step
		time0 += inputs.dt; // increments time
		print_config(outFileTemperatureProfile, inputs.dt, time0, T_array);
	}

	return 0;
}


vector<double> time_integration(double dt, double dx, const vector<double>& T_array) {
// does the Euler integration step on 'T_array' 
// the new value for each position is loaded into 
// T_update, finally T_update becomes T_array ready 
// for the next iteration
	const int N = T_array.size();
	vector<double> T_update(N);

	// boundary conditions
	T_update[0] = T_array[0];
	T_update[N] = T_array[N];

	for (int i = 1; i < (N-1); i++) {
		// euler step
		T_update[i] = T_array[i] + constant * dt * (T_array[i-1] - 2*T_array[i] + T_array[i+1])/(dx*dx);
	}


	return T_update;
}

void print_config(const std:: string &file_name, double dt, double time0, const vector<double>& T_array) {
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
    
 
    for (int i=0;i<T_array.size();i++){
    // this line specifies what gets output to the file, "\t" indicates tabs between the data
    outFile << time0 << "\t" << i << "\t" << T_array[i] << "\t"<< std::endl;
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