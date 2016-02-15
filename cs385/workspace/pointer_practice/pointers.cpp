/*
 * pointers.cpp
 *
 *  Created on: Jan 26, 2016
 *      Author: josh
 */

#include <iosream>
using namespace std;

int main(){
	int x=5, y=6;
	int *z;
	z = &x;
	cout << z << endl;
	cout << *z << endl;
	return 0;
}


