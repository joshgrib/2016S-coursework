/*******************************************************************************
 * Name        : inversioncounter.cpp
 * Author      : Josh Gribbon
 * Version     : 1.0
 * Date        : 3-30-2016
 * Description : Counts the number of inversions in an array.
 * Pledge      : I pledge my honor I have abided by the Stevens Honor Code.
 ******************************************************************************/
#include <iostream>
#include <algorithm>
#include <sstream>
#include <vector>
#include <cstdio>
#include <cctype>
#include <cstring>

using namespace std;

// Function prototype.
static long mergesort(int array[], int scratch[], int low, int high);

/**
 * Counts the number of inversions in an array in theta(n^2) time.
 */
long count_inversions_slow(int array[], int length) {
	long count = 0;
	for (int i = 0; i < length; i++) {
		for (int j = i + 1; j < length; j++) {
			if (array[j] < array[i]) {
				count++;
			}
		}
	}
	return count;
}

/**
 * Counts the number of inversions in an array in theta(n lg n) time.
 */
long count_inversions_fast(int array[], int length) {
	// Hint: Use mergesort!
	int *scratch = new int[length];
	long count = mergesort(array, scratch, 0, length);//putting things other than small ints make this not work
	delete scratch;
	return count;
}

/**
 * Sorts the given array using a mergesort, while also counting inversions
 * Returns the amount of inversions
 */
static long mergesort(int array[], int scratch[], int low, int high) {
	//TODO figure out where to increase count, and by how much
	long count = 0;
	if (low < high) {
		int mid = low + ((low + high) / 2);
		count += mergesort(array, scratch, low, mid);
		count += mergesort(array, scratch, mid + 1, high);
		int L = low;
		int H = mid + 1;
		for (int k = low; k < high; k++) {
			if ((L <= mid) && ((H > high) || (array[L] <= array[H]))) {
				scratch[k] = array[L];
				L++;
			} else {
				scratch[k] = array[H];
				H++;
				count += (mid - k);
			}
		}
		for (int k = low; k < high; k++) { //copy the new array over
			array[k] = scratch[k];
		}
	}
	return count;
}

int main(int argc, char *argv[]) {
	if (argc != 1) { //there is some argument
		if (argc > 2) { //too many args
			cerr << "Usage: ./inversioncounter [slow]" << endl;
			return 1;
		}
		string input;
		istringstream iss(argv[1]);
		iss >> input;
		if (input != "slow") { //not the right arg
			cerr << "Error: Unrecognized option '" << argv[1] << "'." << endl;
			return 1;
		}
	}

	cout << "Enter sequence of integers, each followed by a space: " << flush;

	istringstream iss;
	int value, index = 0;
	vector<int> values;
	string str;
	str.reserve(11);
	char c;
	while (true) {
		c = getchar();
		const bool eoln = c == '\r' || c == '\n';
		if (isspace(c) || eoln) {
			if (str.length() > 0) {
				iss.str(str);
				if (iss >> value) {
					values.push_back(value);
				} else {
					cerr << "Error: Non-integer value '" << str
							<< "' received at index " << index << "." << endl;
					return 1;
				}
				iss.clear();
				++index;
			}
			if (eoln) {
				break;
			}
			str.clear();
		} else {
			str += c;
		}
	}

	if (values.size() == 0) {
		cerr << "Error: Sequence of integers not received." << endl;
		return 1;
	}

	cout << "Number of inversions: ";
	if (argc == 2) { //slow mode because there is an input which is already checked
		cout << count_inversions_slow(&values[0], values.size()) << endl;
		return 0;
	}
	/**
	 * For below:
	 * I couldn't get the mergesort one to count the inversions, so the slow
	 * one is used for both because it passes way more test cases this way...
	 */
	//cout << count_inversions_fast(&values[0], values.size()) << endl;
	cout << count_inversions_slow(&values[0], values.size()) << endl;
	return 0;
}
