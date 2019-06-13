#include <stdio.h>
#include <vector>
#include <iostream>
#include <fstream>  
#include <sstream>
#include <string>
#include <math.h>

using std::vector;

int N = 5;

// This is how to delare a vector (basically a better array), with N elements all of value 0
vector<double> T_update(N,0);
vector<double> T_array(N,0);


double dt = 0.1;
double dx = 1.0;
int runs = 50;
double time0 = 0.0;


//only here to stop main() freaking out 
void input();
void print_config(const std:: string &file_name);
double time_integration(double dt);


int main() {


	std::stringstream integration_timestep;
	integration_timestep.str("");
	integration_timestep << dt;

	std::string outFileTemperatureProfile;	
	outFileTemperatureProfile.append("Temperature_Profile_dt");
	outFileTemperatureProfile.append(integration_timestep.str());
	outFileTemperatureProfile.append(".dat");

	input();
	// resizes all of the arrays because the value of N has been changed via the input file
	T_array.resize(N,0);
	T_update.resize(N,0);

	// changes the value of the first element in the array
	T_array.insert(T_array.begin(), 10000);
	
	for (int i = 0; i < runs;i++) { // iterates for as many times as specified in the 'runs' section of the input file
		time_integration(dt); // runs euler step
		time0 += dt; // increments time
		print_config(outFileTemperatureProfile);
	}

	return 0;
}


double time_integration(double dt) {
// does the Euler integration step on 'T_array' 
// the new value for each position is loaded into 
// T_update, finally T_update becomes T_array ready 
// for the next iteration


	// boundary conditions
	T_update[0] = T_array[0];
	T_update[N] = T_array[N];

	for (int i = 1; i < (N-1); i++) {
		T_update[i] = T_array[i] + dt * (T_array[i-1] - 2*T_array[i] + T_array[i+1])/(dx*dx);
	}

	T_array = T_update;

	return 0;
}

void print_config(const std:: string &file_name) {
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
    
 
    for (int i=0;i<N;i++){
    // this line specifies what gets output to the file, "\t" indicates tabs between the data
    outFile << time0 << "\t" << i << "\t" << T_array[i] << "\t"<< std::endl;
        }

    outFile << std::endl;

    outFile.close();
}

void input() {

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
    
    //  read the first and second column from the input file
	inFile >> s1 >> dt >> s2;
	// print this to terminal
	std::cout << s1 << "\t" << dt << "\t" << s2 << std::endl;  
	
	inFile >> s1 >> dx >> s2;
	std::cout << s1 << "\t" << dx << "\t" << s2 << std::endl;
	
	inFile >> s1 >> N >> s2;
	std::cout << s1 << "\t" << N << "\t" << s2 << std::endl;
	
	inFile >> s1 >> runs >> s2;
	std::cout << s1 << "\t" << runs << "\t" << s2 << std::endl;

}