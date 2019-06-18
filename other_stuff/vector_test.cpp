

#include <iostream>
#include <vector>

using namespace std;

int N = 30;


int main() {
	// initialises 2D vector 
	vector<vector<double>> T_array(4, vector<double> (N, 0));
	T_array[0][5] = 5;


	//prints all of the vector elements in blocks 
	for (int i = 0; i < T_array.size(); i++) {
    	for (int j = 0; j < T_array[i].size(); j++) {
        	cout << T_array[i][j];
    	}
    	cout << std::endl;
	}

	return 0;

}
