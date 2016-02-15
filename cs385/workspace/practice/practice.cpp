/*
 * practice.cpp
 *
 *  Created on: Jan 21, 2016
 *      Author: josh
 */
//ctrl-shift-f autoformats everything

#include <iostream>
#include <sstream>
#include <iomanip>
#include <vector>
using namespace std;

class MyPoint {
public:
	MyPoint(int x, int y, float z) : x_(x), y_(y), z_(z) {};//x_(x) sets the private variable x_ to be the input x
	void print_coords() const {
		cout << "x:" << x_ << " y:" << y_ << fixed << setprecision(2) << " z:" <<  z_;
	}
	int get_x() const{
		/*
		 * Returns the value of x
		 */
		return x_;
	}
private:
	int x_, y_, z_;
};

int main(int argc, char *argv[]){//takes in an integer for the argument count, and an array of pointers to strings for the arguments
	if(argc != 3){//3 because we want two, and the file counts as one
		cerr << "Usage: " << argv[0] << " <firstname> <lastname>" << endl;
		return 1;
	}
	cout << "Hello, " << argv[1] << " " << argv[2] << "!" << endl;

	string s("45");
	int n;
	istringstream iss;

	iss.str(s);
	if( !(iss >> n) ){
		cerr << "NO" << endl;
		return 1;
	}
	cout << "n is " << n << endl;

	MyPoint point(3, 4, 5);
	point.print_coords();

	/*
	MyPoint point2 = new MyPoint(3, 4, 5);//this is worse because now you have to make sure you delete it or there will be a memory leak
	point2->print_coords();
	delete point2;
	*/

	vector<MyPoint> points;
	//points[0] gets you that element, points.begin gives a pointer
	MyPoint point2(3, 4, 5);
	points.push_back(point2);

	//iterating over a vector
	vector<MyPoint> points_above_2;
	for(vector<MyPoint>::const_iterator it = points.begin(); it != points.end(); ++it){
		//now "it" is a pointer to parts of the vector
		it -> print_coords();
		if(it -> get_x() > 2){
			points_above_2.push_back(*it);//"it" is a pointer, so we need to dereference the value to add it to the array
		}
	}

	return 0;
}
