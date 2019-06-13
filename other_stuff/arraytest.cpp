#include <stdio.h>
#include <vector>
#include <iostream>

int N = 100;

int main() {
	std::vector<int> test;

	test.insert(test.begin(), 100);

	test.push_back(25);
	test.push_back(13);

	for(int n : test) {
		std::cout << n << '\n';
	}
}

