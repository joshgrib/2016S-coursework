/*******************************************************************************
 * Name        : stairclimber.cpp
 * Author      : Josh Gribbon
 * Date        : 2-22-16
 * Description : Lists the number of ways to climb n stairs.
 * Pledge      : I pledge my honor I have abided by the Stevens Honor Code
 ******************************************************************************/
#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>
#include <iomanip>
using namespace std;

vector<vector<int> > bigV;
vector<int> littleV;

vector<vector<int> > get_ways(int num_stairs) {
	/**
	 * Returns a 2D vector of ints showing the ways to going up num_stairs stairs,
	 * going 1, 2, or 3 steps at a time
	 */

	if (num_stairs < 1) { //if there's no steps left
		bigV.push_back(littleV);
	}
	if (num_stairs > 0) { //if there's one or more steps left
		littleV.push_back(1);//add the steps taken
		get_ways(num_stairs - 1);//get the options for the rest of the steps
		littleV.pop_back();//remove the last element of the inside vector
	}
	if (num_stairs > 1) { //if there's 2 or more steps left
		littleV.push_back(2);
		get_ways(num_stairs - 2);
		littleV.pop_back();
	}
	if (num_stairs > 2) { //if there's 3 or more steps left
		littleV.push_back(3);
		get_ways(num_stairs - 3);
		littleV.pop_back();
	}
	return bigV;
}

void display_ways(const vector<vector<int> > &ways) {
	/**
	 * Iterate over the 2D int vector and print out all the ways to go up the stairs
	 */
	vector<vector<int> >::const_iterator row;
	vector<int>::const_iterator col;
	int way_count = 1;

	for (row = ways.begin(); row != ways.end(); ++row) { //loop through all the ways
		//formatting for the way count
		if (ways.size() > 9) {
			if (way_count < 10) {
				cout << " ";
			}
		}

		//formatting for the "array" that gets displayed
		cout << way_count << ". [";
		way_count++;
		for (col = row->begin(); col != row->end(); ++col) {
			if ((col + 1) != row->end()) {
				cout << *col << ", ";
			} else {
				cout << *col;
			}

		}
		cout << "]" << endl;
	}
}

int main(int argc, char * const argv[]) {
	if (argc != 2) {
		cerr << "Usage: ./stairclimber <number of stairs>" << endl;
		return 1;
	}
	istringstream iss(argv[1]);
	int input;
	if (!(iss >> input)) {	//letter input
		cerr << "Error: Number of stairs must be a positive integer." << endl;
		return 1;
	}
	if (input < 1) {	//non-positive input
		cerr << "Error: Number of stairs must be a positive integer." << endl;
		return 1;
	}
	vector<vector<int> > myV;
	myV = get_ways(input);

	cout << myV.size() << " way";
	if(myV.size() > 1)//plural word
			cout << "s";
	cout << " to climb " << input << " stair";
	if(myV.size() > 1)//plural word
		cout << "s";
	cout << "." << endl;
	display_ways(myV);

	return 0;
}
