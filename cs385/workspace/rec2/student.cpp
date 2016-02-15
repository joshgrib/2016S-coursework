/*
 * student.cpp
 *
 *  Created on: Jan 29, 2016
 *      Author: josh
 *
 *      I pledge my honor I have abided by the Stevens Honor Code
 *      ~Josh Gribbon
 */

#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
using namespace std;

/*
 * A class to represent students with first and last name, gpa, and id numbers
 */
class Student {
private:
	string first_, last_;
	float gpa_;
	int id_;
public:
	/*
	 * Constructor
	 */
	Student(string first, string last, float gpa, int id) :
			first_(first), last_(last), gpa_(gpa), id_(id) {
	}
	/*
	 * Full name getter
	 */
	string full_name() const {
		return first_ + " " + last_;
	}
	/*
	 * ID getter
	 */
	int id() const {
		return id_;
	}
	/*
	 * GPA getter
	 */
	float gpa() const {
		return gpa_;
	}
	/*
	 * Pretty print all student info
	 */
	void print_info() const {
		cout << first_ << " " << last_ << ", GPA: " << fixed << setprecision(2)
				<< gpa_ << ", ID: " << id_ << endl;
	}
};

/*
 * Find all students with a GPA less than 1.00 from a vector and return them as a vector
 */
vector<Student> find_failing_students(const vector<Student> &students) {
	vector<Student> failing_students;
	for (vector<Student>::const_iterator it = students.begin();
			it != students.end(); ++it) {
		if (it->gpa() < 1.0) {
			failing_students.push_back(*it);
		}
	}
	return failing_students;
}

/*
 * Pretty print all students in the given vector
 */
void print_students(const vector<Student> &students) {
	for (vector<Student>::const_iterator it = students.begin();
			it != students.end(); ++it) {
		//now "it" is a pointer to parts of the vector
		it->print_info();
	}
}

/**
 * Allows the user to enter information for multiple students, then
 * find those students whose GPA is below 1.0 and prints them to the
 * screen.
 */
int main() {
	string first_name, last_name;
	float gpa;
	int id;
	char repeat;
	vector<Student> students;
	//collect all the student info in this do-while
	do {
		cout << "Enter student's first name: ";
		cin >> first_name;
		cout << "Enter student's last name: ";
		cin >> last_name;
		gpa = -1;
		while (gpa < 0 || gpa > 4) {
			cout << "Enter student's GPA (0.0-4.0): ";
			cin >> gpa;
		}
		cout << "Enter student's ID: ";
		cin >> id;
		students.push_back(Student(first_name, last_name, gpa, id));
		cout << "Add another student to database (Y/N)? ";
		cin >> repeat;
	} while (repeat == 'Y' || repeat == 'y');
	cout << endl << "All students:" << endl;
	print_students(students);
	cout << endl << "Failing students:";
	//create a vector to hold students and populate it
	vector<Student> failing_students;
	failing_students = find_failing_students(students);
	if (failing_students.size() < 1) {
		cout << " None" << endl;
	} else {
		cout << endl;
		//print out failing students
		for (vector<Student>::const_iterator it = failing_students.begin();
				it != failing_students.end(); ++it) {
			it->print_info();
		}

	}
	return 0;
}

