/*
 * Josh Gribbon
 * CS385 - Recitation 1
 *
 * I pledge my honor I have abided by the Stevens Honor Code
 */
#include <iostream>
#include <sstream>
using namespace std;

int gcd_rec(int a, int b) {
	/*Finds the greatest common denominator of a and b recursively*/
	if ((a < 0) || (b < 0)) {
		cerr << "Both numbers must be positive" << endl;
		return -1;
	}
	if (b == 0)
		return a;
	if (a == b)
		return a;
	return gcd_rec(b, a % b);
}

int gcd_iter(int a, int b) {
	/*Finds the greatest common denominator of a and b iteratively*/
	if ((a < 0) || (b < 0)) {
		cerr << "Both numbers must be positive" << endl;
		return -1;
	}
	int c;
	while (b != 0) {
		c = b;
		b = a % b;
		a = c;
	}
	return a;
}

int main(int argc, char *argv[]) {
	if (argc != 3) { //3 because we want two, and the file counts as one
		cerr << "Usage: ./gcd <integer m> <integer n>" << endl;
		return 1;
	}
	istringstream iss(argv[1]);//set iss and iss2 and the command line arguments
	istringstream iss2(argv[2]);
	int a, b;
	if (!(iss >> a)) {
		cerr << "Error: The first argument is not a valid integer." << endl;
		return 1;
	} else if (!(iss2 >> b)) {
		cerr << "Error: The second argument is not a valid integer." << endl;
		return 1;
	} else {
		cout << "Iterative: gcd(" << a << ", " << b << ") = " << gcd_iter(a, b)
				<< endl;
		cout << "Recursive: gcd(" << a << ", " << b << ") = " << gcd_rec(a, b)
				<< endl;
		return 0;
	}
	return 1;
}
