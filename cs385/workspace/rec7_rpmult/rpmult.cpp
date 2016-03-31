/*******************************************************************************
 * Name        : rpmult.cpp
 * Author      : Josh Gribbon
 * Date        : 3-9-16
 * Description : DOes russian peasant multiplication with bit shifting
 * Pledge      : I pledge my honor I have abided by the Stevens Honor Code
 ******************************************************************************/
#include <iostream>
#include <sstream>
using namespace std;

unsigned long russian_peasant_multiplication(unsigned int m, unsigned int n){
	unsigned long res = 0;
	while (n > 0){
		if (n & 1)
			res = res + m;
		m = m << 1;
		n = n >> 1;
	}
	return res;
}

int main(int argc, char * const argv[]){
	if (argc != 3) {
	    cerr << "Usage: ./rpmult <integer m> <integer n>" << endl;
	    return 1;
	}
	int first, second;
	istringstream iss1(argv[1]);
	iss1 >> first;
	if(iss1.fail() || (first < 0)){
		cerr << "Error: The first argument is not a valid nonnegative integer." << endl;
		return 1;
	}
	istringstream iss2(argv[2]);
	iss2 >> second;
	if(iss2.fail() || (second < 0)){
		cerr << "Error: The second argument is not a valid nonnegative integer." << endl;
		return 1;
	}
	unsigned long result = 0;
	result = russian_peasant_multiplication(first, second);
	cout << first << " x " << second << " = " << result << endl;

	return 0;
}


