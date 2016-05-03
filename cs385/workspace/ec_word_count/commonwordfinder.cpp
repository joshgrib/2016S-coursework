/*
 * word_count.cpp
 *
 *  Created on: May 2, 2016
 *      Author: josh
 */

/**
 * PROBLEMS
 * 1)Numbers are aligned based on the longest word in the file,
 *   not based on the longest word printed
 * 2)Words within the same count are not alphabetized
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
	int count;
	string description;
	int operator< (const node& other) const
	{return count < other.count;}
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
		char illegal_chars[] = ".,!\"#$%&'()*+`-/:;<>=?@'[]{}^_|";
		for(unsigned int i=0; i<31; ++i){
			word.erase( remove(word.begin(), word.end(), illegal_chars[i]), word.end() );
		}
		//make all letters lowercase
		transform( word.begin(), word.end(), word.begin(), ::tolower);
		words.push_back(word);
	}
	return words;
}

int main(int argc, char *argv[]) {
	if(argc != 2 && argc != 3){
		cerr << "Usage: ./commonwordfinder <filename> [limit]" << endl;
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
	//put words into tree
	while(words.size()!=0){
		string word = words.back();
		words.pop_back();
		if(rbt->find(word) != rbt->end()){//successful search
			rbt->find(word)->second++;
		}else{//word already in tree
			rbt->insert(word, 1);
		}
	}
	//traverse tree and put in priority queue
	typename RedBlackTree<string, int>::iterator it = rbt->begin();
	priority_queue<node> PQ;
	unsigned int biggest_word_length = 0;
	while (it != rbt->end()) {
		node myN;
		myN.count = it->second;
		myN.description = it->first;
		if(myN.description.length() > biggest_word_length){
			biggest_word_length = myN.description.length();
		}
		PQ.push(myN);
	    ++it;
	}
	cout << "Total unique words: " << rbt->size() << endl;
	//get digits in limit
	int digits = 0;
	int num = limit;
	while(num){
		num /= 10;
		digits++;
	}
	for(int i=1; (i<=limit && (unsigned int)i<=rbt->size()); i++){
		cout << setw(digits) << i << ". ";
		node thisN = PQ.top();
		PQ.pop();
		int digits2 = 0;
		int num = thisN.count;
		while(num){
			num /= 10;
			digits2++;
		}
		cout <<  thisN.description;
		int offset = biggest_word_length - thisN.description.length() + (digits2+1);
		cout << setw(offset) << thisN.count;
		cout << endl;
	}
	delete rbt;
	return 0;
}
