#include <stdio.h>
#include <vector>
#include <iostream>

int N = 4;
std::vector<double> T_update;
double dt = 0.0001;
double dx = 0.1;


int main(void) {
	std::vector<double> T_array;
	std::fill (T_array.begin(), T_array.begin()+10, 0);
	T_array.insert(T_array.begin(), 100);
	

	printf("%f\n",T_update[1]);
}
