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
	for(int i=1; i<=item_count; ++i){
		int i_weight = items.at(i-1).weight;
		int i_value = items.at(i-1).value;
		for(int j=1; j<=weight; ++j){
			int cell_value;
			int use_it = arr[i-1][j];
			int lose_it = i_value + arr[i-1][j-i_weight];
			if(j>=i_weight){
				cell_value = max(use_it, lose_it);
			}else{
				cell_value = lose_it;
			}
			arr[i][j] = cell_value;
		}
	}
	//backtrack for answers
	vector<Item> result;
	int i = weight;
	int j = item_count;
	while(i>0){//I don't think I need j here too
		if(arr[i][j] > arr[i-1][j]){//add an item
			cout << "Adding " << items.at(i-1) << endl;
			result.push_back(items.at(i-1));
			j = j-items.at(i-1).weight;
		}
		i--;
	}
	for(int i=0; i<=item_count; ++i){
		for(int j=0; j<=weight; ++j){
			cout << arr[i][j] << " ";
		}
		cout << endl;
	}

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
	vector<Item> items = parse_file(argv[2]);
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
