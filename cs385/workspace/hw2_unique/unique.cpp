/*******************************************************************************
 * Name        : unique.cpp
 * Author      : Josh Gribbon
 * Date        : 2-15-16
 * Description : Determining uniqueness of chars with int as bit vector.
 * Pledge      : I pledge my honor I have abided by the Stevens Honor Code.
 ******************************************************************************/
#include <iostream>
#include <cctype>
using namespace std;

#include <sstream>

bool is_all_lowercase(const string &s) {
	/**
	 * Checks if the string is all lowercase letters
	 * Returns false if any characters are not lowercase letters
	 * Returns false otherwise
	 */
	for (int i = 0; i < int(s.length()); i++) {
		if (!islower(s[i])) {
			return false;
		}
	}
	return true;
}
bool all_unique_letters(const string &s) {
	/**
	 * Checks if all letters in the string are unique by bitshifting and using an int as storage
	 * Returns false if any duplicates are found
	 * Returns true otherwise
	 */
	int letter_storage = 0;//to keep track of the letter we've seen
	int val;//to hold the amount to bitshift
	for (int i = 0; i < int(s.length()); i++) {
		val = s[i] - 'a';
		if (letter_storage & (1 << val)) {//if there's a 1 in the storage place for this letter, it's been seen before
			return false;
		}
		letter_storage |= 1 << val;//if it hasn't been seen, set that it has been now
	}
	return true;
}
int main(int argc, char * const argv[]) {
	/**
	 * Takes in a single string as a command line argument
	 * Checks that there is one string of all lowercase letters, and then prints out if all letters are unique
	 * Returns 1 on any error, 0 otherwise
	 */
	if (argc != 2) { //2 because we want one, and the file counts as one
		cerr << "Usage: ./unique <string>" << endl;
		return 1;
	}
	istringstream iss(argv[1]);
	string input;
	if (!(iss >> input)) {
		//This shouldn't happen but I just wanted to be safe
		cerr << "Error: Something went wrong here..." << endl;
		return 1;
	}
	if (!is_all_lowercase(input)) {
		cerr << "Error: String must contain only lowercase letters." << endl;
		return 1;
	}
	if (all_unique_letters(input)) {
		cout << "All letters are unique." << endl;
	} else {
		cout << "Duplicate letters found." << endl;
	}
	return 0;
}
