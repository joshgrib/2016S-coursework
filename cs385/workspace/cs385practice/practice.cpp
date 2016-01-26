/*
 * practice.cpp
 *
 *  Created on: Jan 21, 2016
 *      Author: josh
 */
//ctrl-shift-f autoformats everything

#include <iostream>
#include <sstream>
using namespace std;

//the namespace operator is two colons. Like the . operator in python. std::cout vs std.cout

int main(int argc, char *argv[]){//takes in an integer for the argument count, and an array of pointers to strings for the arguments
	if(argc != 3){//3 because we want two, and the file counts as one
		cerr << "Usage: " << argv[0] << " <firstname> <lastname>" << endl;
		return 1;
	}
	cout << "Hello, " << argv[1] << " " << argv[2] << "!" << endl;

	string s("45");
	int n;
	istringstream iss;

	iss.str(s);
	if( !(iss >> n) ){
		cerr << "NO" << endl;
		return 1;
	}
	cout << "n is " << n << endl;

	return 0;
}

/*Building and running
Build with the hammer
Run with the play button
Clean with Project>Clean
*/
