#include <stdio.h>
#include <vectors>

int N = 4;
vector<double> T_update;
double dt = 0.0001;
double dx = 0.1;


double time_integration(double *T_array, double dt);

int main(void) {
	vector<double> T_array;
	fill (T_array.begin(), T_array,begin()+10, 0)
	T_array.insert(T_array.begin(), 100)
	
	//printf("%f",T_array[1]);
	time_integration(T_array, dt);


	printf("%f\n",T_update[1]);
	

}


double time_integration(double *T_array, double dt) {
	//printf("%f",T_array[0]);
	T_update[0] = T_array[0];
	T_update[N] = T_array[N];

	for (int i = 1; i < (N-2); i++) {
		T_update[i] = dt * (T_array[i-1] - 2*T_array[i] + T_array[i+1])/(dx*dx);
		printf("%d",i);

	}
	
	return *T_update;
}