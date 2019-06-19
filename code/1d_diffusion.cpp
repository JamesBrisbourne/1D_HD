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
void print_config(const std:: string &file_name, double dt, double time0, const vector<vector<double>>& T_array);
vector<vector<double>> time_integration(double dt, double dx, const vector<vector<double>>& T_array);
//double prefactor(const vector<vector<double>>& T_array, int iter); 


int main() {
	double dt = 0.1;
	double dx = 1.0;
	int runs = 50;
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
	
	vector<vector<double>> T_array(4, vector<double> (inputs.N, 0));

	for (int i = 0; i < inputs.N; i++) {
		T_array[1][i] = 0.5;
		T_array[2][i] = 1000;
		T_array[3][i] = 4000;
}
	T_array[2][6] = 1000000;


	// changes the value of the first element in the array
	T_array[0][0] = 37.0;
	print_config(outFileTemperatureProfile, inputs.dt, time0, T_array);

	
	for (int i = 0; i < inputs.runs;i++) { // iterates for as many times as specified in the 'runs' section of the input file
		T_array = time_integration(inputs.dt, inputs.dx, T_array); // runs euler step
		//printf("%f", time0);

		time0 += inputs.dt; // increments time
		print_config(outFileTemperatureProfile, inputs.dt, time0, T_array);
	}

	return 0;
}

vector<vector<double>> time_integration(double dt, double dx, const vector<vector<double>>& T_array) {
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

	//printf("%f", T_array[0][0]);

	for (int i = 1; i < (N-1); i++) {
		// euler step


		if ((T_array[1][i] == T_array[1][i-1]) && (T_array[1][i] == T_array[1][i+1])) {
			prefactor = (T_array[1][i]/( T_array[2][i] + T_array[3][i]));
			printf("%d",i);

			//printf("check");
		}

		else if ((T_array[1][i]) != (T_array[1][i+1])) {
			//printf("Check");
			prefactor =  (((T_array[1][i])+(T_array[1][i+1]))/2) / ((((T_array[2][i])+(T_array[2][i+1]))/2) * (((T_array[3][i])+(T_array[3][i+1]))/2)  );
			printf("%d",i);
		}

		else if ((T_array[1][i]) != (T_array[1][i-1])) {
			prefactor =  (((T_array[1][i])+(T_array[1][i-1]))/2) / ((((T_array[2][i])+(T_array[2][i-1]))/2) * (((T_array[3][i])+(T_array[3][i-1]))/2)  );
			printf("%d", i);
		}

		T_update[0][i] = T_array[0][i] + prefactor * dt * (T_array[0][i-1] - 2*T_array[0][i] + T_array[0][i+1])/(dx*dx);
	}
	printf("\n");
	return T_update;
}

// double prefactor(const vector<vector<double>>& T_array, int iter) {
// 	//prefactor_result = thermal_conductivity/(density + specific_heat);
// 	double prefactor_result = 0.0;
// 	//printf("%f", T_array[1][1]);
// 	prefactor_result = T_array[1][iter]/( T_array[2][iter] +T_array[3][iter]);
// 	//printf("%f",prefactor_result);
// 	return prefactor_result;
// }

void print_config(const std:: string &file_name, double dt, double time0, const vector<vector<double>>& T_array) {
// handles all the needs of outputting data to a file.
// the output file name is specified by the arguement used
// when calling the function.

    if (abs(time0 - dt) < (-dt/100.0)) {
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
    outFile << time0 << "\t" << i << "\t" << T_array[0][i] << "\t"<< std::endl;
        }

    // for (int i = 0; i < T_array.size(); i++) {
    // 	for (int j = 0; j < T_array[i].size(); j++) {
    // 		outFile << time0 << "\t" << i << "\t" << T_array[0][i] << "\t"<< std::endl;
    // 	}
    // 	outFile << std::endl;
    // }

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