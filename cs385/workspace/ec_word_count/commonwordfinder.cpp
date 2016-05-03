/*
 * word_count.cpp
 *
 *  Created on: May 2, 2016
 *      Author: josh
 */

/**
 * PROBLEMS
 * 1)Words within the same count are not alphabetized
 * 2)Because top words are gotten before alphabetizing,
 *   they're not always the right ones
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
		char illegal_chars[] = ".,!\"#$%&*+/:;<>=?@()[]{}^_|1234567890";
		for(unsigned int i=0; i<38; ++i){
			word.erase( remove(word.begin(), word.end(), illegal_chars[i]), word.end() );
		}
		//make all letters lowercase
		transform( word.begin(), word.end(), word.begin(), ::tolower);
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

bool sort_nodes( node const &first, node const &second )
{
   if (first.count < second.count)
      return true;
   else if (second.count < first.count)
      return false;
   else{//equal
      return first.description  < second.description;
   }
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
		}else{//word not in tree
			rbt->insert(word, 1);
		}
	}
	//traverse tree and put in priority queue
	typename RedBlackTree<string, int>::iterator it = rbt->begin();
	priority_queue<node> PQ;
	while (it != rbt->end()) {
		node myN;
		myN.count = it->second;
		myN.description = it->first;
		PQ.push(myN);
	    ++it;
	}
	cout << "Total unique words: " << rbt->size() << endl;
	vector<node> toPrint;
	unsigned int biggest_word_length = 0;
	/*get front "limit" nodes from the priority queue
	 * put this in a vector
	 * and find the biggest word length
	 */
	for(int i=1; (i<=limit && (unsigned int)i<=rbt->size()); i++){
		//get the nodes to print and find the longest word to print
		node thisN = PQ.top();
		PQ.pop();
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
	reverse(toPrint.begin(), toPrint.end());
	int count = 1;
	while(toPrint.size()!=0 && count <= limit){
		node thisN = toPrint.back();
		toPrint.pop_back();
		int word_count = thisN.count;
		vector<string> sameCountWords;
		while(toPrint.back().count == word_count){//next node is the same count as this one
			sameCountWords.push_back(toPrint.back().description);
			toPrint.pop_back();
		}
		sort(sameCountWords.rbegin(), sameCountWords.rend());
		//reverse(sameCountWords.begin(), sameCountWords.end());
		while(!sameCountWords.empty()){
			string word = sameCountWords.back();
			sameCountWords.pop_back();
			printLine(count, word, word_count, biggest_word_length, digits);
			count++;
		}
		printLine(count, thisN.description, thisN.count, biggest_word_length, digits);
		count++;
	}
	delete rbt;
	return 0;
}
