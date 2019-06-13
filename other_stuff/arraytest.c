#include <stdio.h>
#include <vector>

int N = 100;

int main() {
	vector<int> testvector (N);
	fill(testvector.begin(), testvector.begin()+N, 0);
	printf("%d",testvector);
}

