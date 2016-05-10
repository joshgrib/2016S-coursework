/*
 * word_count.cpp
 *
 *  Created on: May 2, 2016
 *      Author: josh
 */

#include "rbtree.h"
#include <iostream>
#include <sstream>
#include <iomanip>
#include <sstream>
#include <string>
#include <fstream>
#include <algorithm>
#include <queue>

using namespace std;

struct node{
	/*
	 * Represents a node for the tree and vectors
	 */
	int count;
	string description;
	int operator< (const node& other) const{
		/*
		 * Sort based on count and then description
		 */
		if(count==other.count){
			return other.description < description;
		}else{
			return count < other.count;
		}
	}
};

vector<string> get_words(string filename){
	/*
	 * Takes in the string filename, already checked to be present
	 * Returns a vector of the words in the file
	 */
	ifstream infile(filename.c_str());
	vector<string> words;
	string word;
	while(infile >> word){
		//remove anything that isn't a letter
		char illegal_chars[] = ".,!\"#$%&*+/:;<>=?@()[]{}^_|1234567890";
		for(unsigned int i=0; i<38; ++i){
			word.erase( remove(word.begin(), word.end(), illegal_chars[i]), word.end() );
		}
		//make all letters lowercase
		transform( word.begin(), word.end(), word.begin(), ::tolower);
		//don't add if there's no characters
		if(!(word==" " || word.empty())){
			words.push_back(word);
		}
	}
	return words;
}

void printLine(int count, string word, int word_count, int biggest_word_length, int digits){
	/*
	 * Prints a line in the form
	 * 1. words   3
	 * 2. printed 2
	 * 3. like    2
	 * 4. this    1
	 */
	cout << setw(digits) << count << ". ";
	int digits2 = 0;
	int num = word_count;
	while(num){
		num /= 10;
		digits2++;
	}
	cout <<  word;
	int offset = biggest_word_length - word.length() + (digits2+1);
	cout << setw(offset) << word_count;
	cout << endl;
}

int main(int argc, char *argv[]) {
	//parse CLAs
	if(argc != 2 && argc != 3){
		cerr << "Usage: " << argv[0] << " <filename> [limit]" << endl;
		return 1;
	}
	ifstream infile(argv[1]);
	if(!infile){
		cerr << "Error: Cannot open file '" << argv[1] << "' for input." << endl;
		return 1;
	}
	int limit;
	if(argc == 3){
		istringstream iss(argv[2]);
		if(!(iss >> limit) || (limit < 1)){
			cerr << "Error: Invalid limit '" << argv[2] << "' received." << endl;
			return 1;
		}
	}else{
		limit = 10;
	}
	RedBlackTree<string, int> *rbt = new RedBlackTree<string, int>();
	vector<string> words = get_words(argv[1]);

	//put words into tree and get counts of each
	while(words.size()!=0){
		string word = words.back();
		words.pop_back();
		if(rbt->find(word) != rbt->end()){//successful search
			rbt->find(word)->second++;
		}else{//word not in tree
			rbt->insert(word, 1);
		}
	}

	//traverse tree and put in vector
	typename RedBlackTree<string, int>::iterator it = rbt->begin();
	vector<node> word_nodes;
	while (it != rbt->end()) {
		node myN;
		myN.count = it->second;
		myN.description = it->first;
		word_nodes.push_back(myN);
	    ++it;
	}

	//sort vector by count and then by description
	sort(word_nodes.begin(), word_nodes.end());
	cout << "Total unique words: " << word_nodes.size() << endl;
	vector<node> toPrint;
	unsigned int biggest_word_length = 0;

	//take the amount of nodes to print and put them in a new vector
	for(int i=1; (i<=limit && (unsigned int)i<=rbt->size()); i++){
		//get the nodes to print and find the longest word to print
		node thisN = word_nodes.back();
		word_nodes.pop_back();
		if(thisN.description.length() > biggest_word_length){
			biggest_word_length = thisN.description.length();
		}
		toPrint.push_back(thisN);
	}

	//get digits in limit
	int digits = 0;
	int num = limit;
	while(num){
		num /= 10;
		digits++;
	}
	if( (limit<10) || (toPrint.size()<10) ){
		digits = 1;
	}
	reverse(toPrint.begin(), toPrint.end());
	int count = 1;

	//print out the words
	while(toPrint.size()!=0){
		node thisN = toPrint.back();
		toPrint.pop_back();
		printLine(count, thisN.description, thisN.count, biggest_word_length, digits);
		count++;
	}

	//cleanup
	delete rbt;
	return 0;
}
