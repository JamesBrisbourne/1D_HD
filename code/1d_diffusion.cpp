#include <stdio.h>
#include <vector>
#include <iostream>
#include <fstream>  
#include <sstream>
#include <string>
#include <math.h>

using std::vector;

int N = 5;
vector<double> T_update(N,0);
vector<double> T_array(N,0);
double dt = 0.1;
double dx = 1.0;
int runs = 50;
double time0 = 0.0;



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
	T_array.resize(N,0);
	T_array.resize(N,0);
	T_array.insert(T_array.begin(), 10000);
	
	//printf("%f",T_array[0]);
	for (int i = 0; i < runs;i++) {
		time_integration(dt);
		time0 += dt;
		print_config(outFileTemperatureProfile);
	}
	
	printf("%f\n",T_array[1]);

	//printf("%f\n",T_array[0]);
	
	return 0;
}


double time_integration(double dt) {
	//printf("%f",T_array[0]);
	T_update[0] = T_array[0];
	T_update[N] = T_array[N];

	for (int i = 1; i < (N-1); i++) {
		T_update[i] = T_array[i] + dt * (T_array[i-1] - 2*T_array[i] + T_array[i+1])/(dx*dx);
		//printf("%d \t %f\n",i,T_update[i]);


	}
	T_array = T_update;
	

	return 0;
	//return T_update;
}

void print_config(const std:: string &file_name) {
    if (abs(time0 - dt) < (dt/100.0)) {
    	std::ofstream outFile(file_name);
    	std::cout << "write to file "<<file_name << std::endl;
    }
    std::ofstream outFile(file_name, std::ofstream::app);
    if(!outFile)
    {
        std::cout << std::endl << "Failed to open the file: "<< file_name <<std::endl;
        exit(1);
    }  
    
 
    for (int i=0;i<N;i++){
    outFile << time0 << "\t" << i << "\t" << T_array[i] << "\t"<< std::endl;
        }
        outFile << std::endl;
    outFile.close();
}

void input() {
	std::string s1, s2; //dummy variables to take column 1 and 2 from the input file



	std::string file_name ="../input/input.in";

    
    std::ifstream inFile(file_name);
    std::cout << "read from file "<< file_name << std::endl;
    
    if(!inFile)
    {
        std::cout << std::endl << "Failed to read from the file: "<< file_name << std::endl;
        exit(1);
    }  
    
	inFile >> s1 >> dt >> s2;
	std::cout << s1 << "\t" << dt << "\t" << s2 << std::endl;  
	inFile >> s1 >> dx >> s2;
	std::cout << s1 << "\t" << dx << "\t" << s2 << std::endl;
	inFile >> s1 >> N >> s2;
	std::cout << s1 << "\t" << N << "\t" << s2 << std::endl;
	inFile >> s1 >> runs >> s2;
	std::cout << s1 << "\t" << runs << "\t" << s2 << std::endl;


    
}