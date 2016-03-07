/*******************************************************************************
 * Name        : waterjugpuzzle.cpp
 * Author      : Josh Gribbon
 * Date        : 3-9-16
 * Description : Finds a way to pour water between jugs to get to a certain end situation
 * Pledge      : I pledge my honor I have abided by the Stevens Honor Code
 ******************************************************************************/
#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <queue>
#include <stack>
using namespace std;

/**
 * VALGRIND CHECK
 * On linux lab:
 * "valgrind --leak-check=yes ./waterjugpuzzle <cap A> <cap B> <cap C> <goal A> <goal B> <goal C>"
 *
 * Look for "All heap blocks were freed -- no leaks are possible"
 *
 * If you have leaks change "yes" to "full" to see all the leaks
 */

int check_input(char * const argv[6]){
    int a_jug, b_jug, c_jug, a_goal, b_goal, c_goal;
    istringstream iss1(argv[1]);
    iss1 >> a_jug;
    if(iss1.fail() || (a_jug < 1)){
        cerr << "Error: Invalid capacity '"<< argv[1] <<"' for jug A." << endl;
        return 1;
    }
    istringstream iss2(argv[2]);
    iss2 >> b_jug;
    if(iss2.fail() || (b_jug < 1)){
        cerr << "Error: Invalid capacity '"<< argv[2] <<"' for jug B." << endl;
        return 1;
    }
    istringstream iss3(argv[3]);
    iss3 >> c_jug;
    if(iss3.fail() || (c_jug < 1)){
        cerr << "Error: Invalid capacity '"<< argv[3] <<"' for jug C." << endl;
        return 1;
    }
    istringstream iss4(argv[4]);
    iss4 >> a_goal;
    if(iss4.fail() || (a_goal < 0)){
        cerr << "Error: Invalid goal '"<< argv[4] <<"' for jug A." << endl;
        return 1;
    }
    istringstream iss5(argv[5]);
    iss5 >> b_goal;
    if(iss5.fail() || (b_goal < 0)){
        cerr << "Error: Invalid goal '"<< argv[5] <<"' for jug B." << endl;
        return 1;
    }
    istringstream iss6(argv[6]);
    iss6 >> c_goal;
    if(iss6.fail() || (c_goal < 0)){
        cerr << "Error: Invalid goal '"<< argv[6] <<"' for jug C." << endl;
        return 1;
    }
    if(a_goal > a_jug){
        cerr << "Error: Goal cannot exceed capacity of jug A." << endl;
        return 1;
    }
    if(b_goal > b_jug){
        cerr << "Error: Goal cannot exceed capacity of jug B." << endl;
        return 1;
    }
    if(c_goal > c_jug){
        cerr << "Error: Goal cannot exceed capacity of jug C." << endl;
        return 1;
    }
    if((a_goal+b_goal+c_goal)!=c_jug){
        cerr << "Error: Total gallons in goal state must be equal to the capacity of jug C." << endl;
        return 1;
    }
    return 0;
}

class Vertex{
	/**
	 * Class to represent a vertex, being a state of the 3 jugs
	 */
public:
	int A, B, C;
	bool checked;
	explicit Vertex(int A_init, int B_init, int C_init){
		A = A_init;
		B = B_init;
		C = C_init;
		checked=false;
	}
};

vector< vector<int> > checked;
int a_cap, b_cap, c_cap, a_goal, b_goal, c_goal;//capacities and goals
queue<Vertex> bfsQ;
stack<Vertex> solution;

bool has_solution(int A, int B, int C){
	/**
	 * Accidentally made a DFS but it finds out if there's a solution
	 * well so I figured I'd use it anyway
	 */
    vector<int> combo;
    combo.push_back(C);
    combo.push_back(B);
    combo.push_back(A);
    if(find(checked.begin(), checked.end(), combo) != checked.end()){
        //this combo has been checked before
        return false;
    }
    checked.push_back(combo);

    if((A==a_goal) && (B==b_goal) && (C==c_goal)){
        //Reached the goal
        return true;
    }

    bool result = false;

    int diff;

    //C --> A
    if((A+C) > a_cap){
        //all of C can't be poured into A
        diff = a_cap-A;
    }else{
        //all of C can be poured into A
        diff = C;
    }
    if(has_solution(A+diff, B, C-diff) && !result){
        result = true;
        ostringstream resp;
        //cout << "Pour " << diff << " gallons from C to A. (" << A+diff << ", " << B << ", " << C-diff << ")" << endl;
    }

    //B --> A
    if((B+A) > a_cap){
        diff = a_cap-A;
    }else{
        diff = B;
    }
    if(has_solution(A+diff, B-diff, C) && !result){
        result = true;
        //cout << "Pour " << diff << " gallons from B to A. (" << A+diff << ", " << B-diff << ", " << C << ")" << endl;
    }

    //C --> B
    if((C+B) > b_cap){
        diff = b_cap-B;
    }else{
        diff = C;
    }
    if(has_solution(A, B+diff, C-diff) && !result){
        result = true;
        //cout << "Pour " << diff << " gallons from C to B. (" << A << ", " << B+diff << ", " << C-diff << ")" << endl;
    }

    //A --> B
    if((A+B) > b_cap){
        diff = b_cap-B;
    }else{
        diff = A;
    }
    if(has_solution(A-diff, B+diff, C) && !result){
        result = true;
        //cout << "Pour " << diff << " gallons from A to B. (" << A-diff << ", " << B+diff << ", " << C << ")" << endl;
    }

    //B --> C
    if((B+C) > c_cap){
        diff = c_cap-C;
    }else{
        diff = B;
    }
    if(has_solution(A, B-diff, C+diff) && !result){
        result = true;
        //cout << "Pour " << diff << " gallons from B to C. (" << A << ", " << B-diff << ", " << C+diff << ")" << endl;
    }

    //A --> C
    if((A+C) > c_cap){
        diff = c_cap-C;
    }else{
        diff = A;
    }
    if(has_solution(A-diff, B, C+diff) && !result){
        result = true;
        //cout << "Pour " << diff << " gallons from A to C. (" << A-diff << ", " << B << ", " << C+diff << ")" << endl;
    }

    return result;
}

bool getNext(int A, int B, int C){
	/**
	 * Add the current combo to the queue if it hasn't been checked yet
	 * Find the next possible combo and recurse
	 */
	if((A==a_goal) && (B=b_goal) && (C==c_goal)){
		return true;
	}
	vector<int> combo;
	combo.push_back(C);
    combo.push_back(B);
    combo.push_back(A);
    if(find(checked.begin(), checked.end(), combo) != checked.end()){
    	//this combo has been checked before
    	//cout << "(" << A << ", " << B << ", " << C << ") has been checked before." << endl;
	    return false;
    }
    Vertex V(A, B, C);
    bfsQ.push(V);
    checked.push_back(combo);

    //C --> A
    int diff1;
    if((A+C) > a_cap){
        //all of C can't be poured into A
        diff1 = a_cap-A;
    }else{
        //all of C can be poured into A
        diff1 = C;
    }
    Vertex V1(A+diff1, B, C-diff1);

    //B --> A
    int diff2;
    if((B+A) > a_cap){
        diff2 = a_cap-A;
    }else{
        diff2 = B;
    }
    Vertex V2(A+diff2, B-diff2, C);

    //C --> B
    int diff3;
    if((C+B) > b_cap){
        diff3 = b_cap-B;
    }else{
        diff3 = C;
    }
    Vertex V3(A, B+diff3, C-diff3);

    //A --> B
    int diff4;
    if((A+B) > b_cap){
        diff4 = b_cap-B;
    }else{
        diff4 = A;
    }
    Vertex V4(A-diff4, B+diff4, C);

    //B --> C
    int diff5;
    if((B+C) > c_cap){
        diff5 = c_cap-C;
    }else{
        diff5 = B;
    }
    Vertex V5(A, B-diff5, C+diff5);

    //A --> C
    int diff6;
    if((A+C) > c_cap){
        diff6 = c_cap-C;
    }else{
        diff6 = A;
    }
    Vertex V6(A-diff6, B, C+diff6);

    /*bfsQ.push(V1);
    bfsQ.push(V2);
    bfsQ.push(V3);
    bfsQ.push(V4);
    bfsQ.push(V5);
    bfsQ.push(V6);*/
    //get the next ones for them all
    if(getNext(V1.A, V1.B, V1.C)){
    	solution.push(V1);
    	//return true;
    }
    if(getNext(V2.A, V2.B, V2.C)){
        solution.push(V2);
        //return true;
    }
    if(getNext(V3.A, V3.B, V3.C)){
        solution.push(V3);
        //return true;
    }
    if(getNext(V4.A, V4.B, V4.C)){
        solution.push(V4);
        //return true;
    }
    if(getNext(V5.A, V5.B, V5.C)){
        solution.push(V5);
        //return true;
    }
    if(getNext(V6.A, V6.B, V6.C)){
        solution.push(V6);
        //return true;
    }
    return false;
}

bool BFS(){
	getNext(0, 0, c_cap);//populate the queue
	/*
    while(!bfsQ.empty()){
		//Vertex V = bfsQ.front();
		bfsQ.pop();
		//cout << "(" << V.A << ", " << V.B << ", " << V.C << ")" << endl;
	}
    */
    while(!solution.empty()){
        Vertex V = solution.top();
        solution.pop();
        cout << "(" << V.A << ", " << V.B << ", " << V.C << ")" << endl;
    }
	return true;
}

void bfs(){
	/**
	 * In class explanation
	 * 	Put initial state on queue
	 * 	While queue is not empty
	 * 		Let head of queue be 'current'
	 * 		Generate all successors of current
	 * 		For each one:
	 * 			Check if it's the goal
	 * 			Check if it's been seen before
	 * 			If not, push on queue
	 * 		Pop head of queue
	 */
}

/**
 * To keep track of steps
 * 	class State
 * 		int a_, b_, c_;
 * 		vector<string> directions;
 * 		Each state will have the jug values and a list of how to get to that specific state through BFS
 * 		WHen you get to the goal just iterate over the vector and print it all out
 */

int main(int argc, char * const argv[]){
    if (argc != 7) {
        cerr << "Usage: ./waterjugpuzzle <cap A> <cap B> <cap C> <goal A> <goal B> <goal C>" << endl;
        return 1;
    }
    if(check_input(argv)){
        return 1;
    }
    int arr[6];
    for(int i=0; i<6; i++){
        istringstream iss(argv[i+1]);
        int val;
        iss >> val;
        arr[i] = val;
    }
    a_cap = arr[0];
    b_cap = arr[1];
    c_cap = arr[2];
    a_goal = arr[3];
    b_goal = arr[4];
    c_goal = arr[5];
    //cout << "Going for goal(" << a_goal << ", " << b_goal << ", " << c_goal << ")" << endl;
    /*
    if(!dfs(0, 0, arr[2])){
        cout << "No solution." << endl;
        return 0;
    }
    */
    if(!has_solution(0, 0, c_cap)){
    	cout << "No solution." << endl;
    	return 0;
    }else{
    	cout << "Initial state. (0, 0, " << c_cap << ")" << endl;
    	if((a_goal==0) && (b_goal==0)){
    		return 0;
    	}
    	BFS();
    	while(solution.size()!=0){
    		//Vertex V = solution.top();
    		solution.pop();
    		//cout << "(" << V.A << ", " << V.B << ", " << V.C << ")" << endl;
    	}
    }
    return 0;
}



