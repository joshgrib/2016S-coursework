/*******************************************************************************
 * Name        : knapsack.cpp
 * Author      : Josh Gribbon
 * Version     : 1.0
 * Date        :
 * Description : KNapsack problem
 * Pledge      : I pledge my honor I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include <vector>
using namespace std;

struct Item {
	unsigned int item_number, weight, value;
	string description;
	explicit Item(const unsigned int item_number, const unsigned int weight,
			const unsigned int value, const string &description) :
			item_number(item_number), weight(weight), value(value), description(
					description) {
	}
	friend std::ostream& operator<<(std::ostream& os, const Item &item) {
		os << "Item " << item.item_number << ": " << item.description << " ("
				<< item.weight << (item.weight == 1 ? " pound" : " pounds")
				<< ", $" << item.value << ")";
		os.flush();
		return os;
	}
};

vector<string> splitLine(const string &input, char splitBy){
	/**
	 * Given a string line of CSVs
	 * Return a vector of the values
	 */
	stringstream ss(input);
	string item;
	vector<string> tokens;
	while(getline(ss, item, splitBy)){
		tokens.push_back(item);
	}
	return tokens;
}

vector<Item> parse_file(string filename){
	/**
	 * Parse the file and return a vector of `Item`s
	 */
	ifstream infile(filename.c_str());
	vector<Item> items;
	string description, weight_s, value_s;
	int weight, value;
	int count = 1;
	string line;
	while(getline(infile, line)){
		vector<string> itemParts;
		itemParts= splitLine(line, ',');
		//get strings from the vector
		description = itemParts.at(0);
		weight_s = itemParts.at(1);
		value_s = itemParts.at(2);
		//convert to ints
		istringstream(weight_s) >> weight;
		istringstream(value_s) >> value;
		//make item and add to vector
		Item thisItem(count, weight, value, description);
		items.push_back(thisItem);
		count++;
	}
	return items;
}

int max(int a, int b){
	if(a>b)
		return a;
	return b;
}

vector<int> compute_knapsack(const int weight, vector<Item> items, const int item_count){
	vector<int> results;
	//generate blank 2D array
	int **arr = new int*[item_count+1];
	for(int i=0; i<=item_count; ++i){
		arr[i] = new int[weight+1];
		arr[i][0] = 0;//fill leftmost column with zeros
		if(i==0){
			for(int j=0; j<weight; ++j){
				arr[0][j] = 0;//fill top row with zeros
			}
		}
	}
	for(int i=0; i<=item_count; ++i){
		for(int j=0; j<=weight; ++j){
			cout << arr[i][j] << " ";
		}
		cout << endl;
	}

	/*
	int *weights = new int[item_count];
	int *values = new int[item_count];
	int *item_arr = new int[item_count];
	for(int i=0; i<item_count-1; i++){
		Item this_item = items.at(item_count);
		item_arr[item_count] = this_item.item_number;
		weights[item_count] = this_item.weight;
		values[item_count] = this_item.value;
	}
	int **arr = new int*[item_count];
	for(int i = 0; i < item_count; ++i) {
	    arr[i] = new int[weight];
	    for(int j=0; j<weight; j++){
	    	if( (i==0) || (j==0)){
	    		arr[i][j]=0;
	    	}else if(weights[i-1] <= j){
	    		arr[i][j] = max( (values[i-1] + arr[i-1][j-weights[i-1]]), arr[i-1][j]);
	    	}else{
	    		arr[i][j] = arr[i-1][j];
	    	}
	    }
	}
	for(int i=0; i<item_count; i++){
		for(int j=0; j<weight; j++){
			cout << arr[i][j] << " " << endl;
		}
		cout << endl;
	}
	//backtrack for solution
	//clean up stuff
	for(int i = 0; i < item_count; ++i) {
	    delete [] arr[i];
	}
	delete [] arr;
	delete weights;
	delete values;
	*/
	return results;
}

int main(int argc, char *argv[]) {
	if(argc != 3){
		cerr << "Usage: ./knapsack <capacity> <filename>" << endl;
		return 1;
	}
	istringstream iss(argv[1]);
	int input;
	if ( (!(iss >> input)) || (input < 0) ) {	//letter input
		cerr << "Error: Bad value '" << argv[1] << "' for capacity." << endl;
		return 1;
	}
	ifstream infile(argv[2]);
	if(!infile){
		cerr << "Error: Cannot open file '" << argv[2] << "'." << endl;
		return 1;
	}
	//convert file to vector of 'Item's
	vector<Item> items = parse_file(argv[2]);
	//get the item numbers of the solution
	vector<int> solution_item_numbers = compute_knapsack(input, items, items.size());
	return 0;
}
