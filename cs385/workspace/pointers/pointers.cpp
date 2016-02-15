/*
 * pointers.cpp
 *
 *  Created on: Jan 26, 2016
 *      Author: josh
 */

#include <iostream>
using namespace std;

void display_array(int array[], const int length){
	cout << "[";
	for (int i=0; i<length; ++i){
		if(i != 0){
			cout << ", ";
		}
		cout << array[i];
	}
	cout << "]" << endl;
}

void display_array_ptr(int array[], const int length){
	cout << "[";
	//gets a pointer for where you are in the array and where the end is, then compares pointers to see when you're at the end
	for (int *ptr = array, *end = array + length; ptr < end; ++ptr){
		if(ptr != array){
			cout << ", ";
		}
		cout << *ptr;
	}
	cout << "]" << endl;
}

void pass_by_value(int x){
	//makes a copy local to this function, will not change the value in the main
	x = 20;
}

void pass_by_pointer(int *x){
	//function takes in a pointer, then it's dereferenced and changed - will affect the value in main
	*x = 10;
}

void pass_by_reference(int &x){
	//makes a new object with the same address in memory, so changes here also affect the input from main
	//if you don't want to modify it you could make a constant reference
	x = 10;
}

int main(void){
	int x=5, y=6;
	int *z;
	z = &x;
	cout << z << endl;//0x7ffd16cee22c
	cout << *z << endl;//5

	cout << x << " " << y << endl;//5 6
	*z = 7;
	cout << x <<  y << endl; //76
	z = &y;
	*z = 7;
	cout << "x= " << x << ", " << "y= " << y << endl;//x= 7, y= 7
	cout << ++z << endl;//0x7ffd16cee234
	//cout << *z << endl;//BAD idea: may or may not work

	int* values = new int[y];
	for (int i=0; i<y; i++){
		values[i] = i;
	}
	display_array_ptr(values, y);//[0, 1, 2, 3, 4, 5, 6]
	delete [] values;//garbage collection to delete the entire array of values

	pass_by_value(x);
	cout << "x= " << x << ", " << "y= " << y << endl;//x= 7, y= 7
	pass_by_pointer(&x);
	pass_by_reference(y);
	cout << "x= " << x << ", " << "y= " << y << endl;//x= 10, y= 10
	return 0;
}

