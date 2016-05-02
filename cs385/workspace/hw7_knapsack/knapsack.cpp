/*******************************************************************************
 * Name        : knapsack.cpp
 * Author      : Josh Gribbon
 * Version     : 1.0
 * Date        : 5-1-16
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
	int item_number, weight, value;
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
	int weight=0, value=0;
	int count = 1;
	string line;
	while(getline(infile, line)){
		vector<string> itemParts;
		itemParts= splitLine(line, ',');
		//get strings from the vector
		if(itemParts.size() != 3){
			cerr << "Error: Line number " << count << " does not contain 3 fields." << endl;
			throw exception();
		}
		description = itemParts.at(0);
		weight_s = itemParts.at(1);
		value_s = itemParts.at(2);
		//convert to ints
		istringstream iss_w(weight_s);
		 if(!iss_w >> weight){
			 cerr << "Error: Invalid weight '" << iss_w << "' on line number " << count << "." << endl;
			 throw exception();
		 }
		istringstream iss_v(value_s);
		 if(!iss_v >> value){
			 cerr << "Error: Invalid value '" << iss_v << "' on line number " << count << "." << endl;
			 throw exception();
		 }
		//make item and add to vector
		Item thisItem(count, weight, value, description);
		items.push_back(thisItem);
		count++;
	}
	return items;
}

void print_items(vector<Item> items, int item_count){
	/**
	 * Given a vector of items and the size of the vector
	 * Print out all the items in order
	 */
	for(int i=0; i<item_count; ++i){
		cout << "   " << items.at(i) << endl;
	}
}

void print_weight_value(vector<Item> items, int item_count){
	/**
	 * Given a vector of items and the size of the vector
	 * Print the total weight and value of the items
	 */
	int weight = 0;
	int value = 0;
	for(int i=0; i<item_count; ++i){
		weight += items.at(i).weight;
		value += items.at(i).value;
	}
	cout << "Total weight: " << weight << " pounds" << endl;
	cout << "Total value : $" << value << endl;
}

int max(int a, int b){
	/**
	 * Return the max of two integers
	 */
	if(a>b)
		return a;
	return b;
}

vector<Item> compute_knapsack(const int weight, vector<Item> items, const int item_count){
	//generate 2D array
	int **arr = new int*[item_count+1];
	for(int i=0; i<=item_count; ++i){
		arr[i] = new int[weight+1];
		for(int j=0; j<=weight; j++){
			if( (i==0) || (j==0)){
				arr[i][j] = 0;
			}else if (items.at(i-1).weight <= j){
				arr[i][j] = max( (items.at(i-1).value + arr[i-1][j-items.at(i-1).weight]), arr[i-1][j]);
			}else{
				arr[i][j] = arr[i-1][j];
			}
		}
	}
	//backtrack for answers
	vector<Item> result, temp;
	int i = weight;
	int j = item_count;
	while(i>0){//I don't think I need j here too
		if(arr[i][j] > arr[i-1][j]){//add an item
			//cout << "Adding " << items.at(i-1) << endl;
			temp.push_back(items.at(i-1));
			j = j-items.at(i-1).weight;
		}
		i--;
	}
	vector<Item>::iterator it=temp.end();
	while(it != temp.begin()){
		result.push_back(*(--it));
	}
	//print out array
	/*
	for(int i=0; i<=item_count; ++i){
		for(int j=0; j<=weight; ++j){
			cout << arr[i][j] << " ";
		}
		cout << endl;
	}
	*/
	//cleanup
	for(int i = 0; i <= item_count; ++i) {
	    delete [] arr[i];
	}
	delete [] arr;
	return result;
}

int main(int argc, char *argv[]) {
	if(argc != 3){
		cerr << "Usage: ./knapsack <capacity> <filename>" << endl;
		return 1;
	}
	istringstream iss(argv[1]);
	int capacity;
	if ( (!(iss >> capacity)) || (capacity < 0) ) {	//letter input
		cerr << "Error: Bad value '" << argv[1] << "' for capacity." << endl;
		return 1;
	}
	ifstream infile(argv[2]);
	if(!infile){
		cerr << "Error: Cannot open file '" << argv[2] << "'." << endl;
		return 1;
	}
	//convert file to vector of 'Item's
	vector<Item> items;
	try{
		items = parse_file(argv[2]);
	}
	catch(...){
		return 1;
	}
	cout << "Candidate items to place in knapsack:" << endl;
	print_items(items, items.size());
	cout << "Capacity: " << capacity << " pounds" << endl;
	//get the item numbers of the solution
	vector<Item> solution_items = compute_knapsack(capacity, items, items.size());
	cout << "Items to place in knapsack:" << endl;
	print_items(solution_items, solution_items.size());
	print_weight_value(solution_items, solution_items.size());
	return 0;
}
