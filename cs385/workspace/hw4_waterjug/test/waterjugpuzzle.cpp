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
	/**
	 * Checks the user input to make sure:
	 * Inputs are all non-negative integers
	 * Jug capacities are positive
	 * Goals are all less than jug capacities
	 * Total goal gallons are equal to the capacity of jug c
	 */
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

int a_cap, b_cap, c_cap, a_goal, b_goal, c_goal;//capacities and goals

class State{
public:
	int a_, b_, c_;
	vector<string> steps;
	explicit State(int a, int b, int c, vector<string> prevSteps, string newStep) : a_(a), b_(b), c_(c){
		steps = prevSteps;
		if(newStep != ""){
			steps.push_back(newStep);
		}
	}
	vector<string> get_steps(){
		return steps;
	}
	bool is_goal(){
		if((a_==a_goal) && (b_==b_goal) && (c_==c_goal)){
			return true;
		}
		return false;
	}
};

queue<State> bfsQ;
vector< vector<int> > checked;
vector<State> checked2;

bool already_checked(vector<int> V){
	/**
	 * Returns if an integer vector of 3 jug capacities has been checked before
	 */
	if(find(checked.begin(), checked.end(), V) != checked.end()){
		//this state has been checked before
		return true;
	}
	return false;
}

vector<int> state_to_vector(State state){
	/**
	 * Convert a State object to a integer vector to add to the "checked" vector
	 */
	vector<int> V;
	V.push_back(state.a_);
	V.push_back(state.b_);
	V.push_back(state.c_);
	return V;
}

void add_next_to_queue(State state){
	/**
	 * Given a State object:
	 * Check if it has been checked before, if it has do nothing
	 * Find all next possible states and add any that haven't been checked yet to the queue
	 */
	vector<int> V = state_to_vector(state);
	if(already_checked(V)){
		//state has been checked before so don't do anything with it
		return;
	}
	checked.push_back(V);//it hasn't been checked so add that it has

	//for convenience
	int A = state.a_;
	int B = state.b_;
	int C = state.c_;

	//C --> A
    int diff1;
    if((A+C) > a_cap){
        //all of C can't be poured into A
        diff1 = a_cap-A;
    }else{
        //all of C can be poured into A
        diff1 = C;
    }
    //B --> A
    int diff2;
    if((B+A) > a_cap){
        diff2 = a_cap-A;
    }else{
        diff2 = B;
    }
    //C --> B
    int diff3;
    if((C+B) > b_cap){
        diff3 = b_cap-B;
    }else{
        diff3 = C;
    }
    //A --> B
    int diff4;
    if((A+B) > b_cap){
        diff4 = b_cap-B;
    }else{
        diff4 = A;
    }
    //B --> C
    int diff5;
    if((B+C) > c_cap){
        diff5 = c_cap-C;
    }else{
        diff5 = B;
    }
    //A --> C
    int diff6;
    if((A+C) > c_cap){
        diff6 = c_cap-C;
    }else{
        diff6 = A;
    }

    //handle plurality of gallon VS gallons
    ostringstream step1, step2, step3, step4, step5, step6;
    string plurality1 = "";
    if(diff1 > 1){
    	plurality1 = "s";
    }
    string plurality2 = "";
    if(diff2 > 1){
       	plurality2 = "s";
    }
    string plurality3 = "";
    if(diff3 > 1){
       	plurality3 = "s";
    }
    string plurality4 = "";
    if(diff4 > 1){
       	plurality4 = "s";
    }
    string plurality5 = "";
    if(diff5 > 1){
       	plurality5 = "s";
    }
    string plurality6 = "";
    if(diff6 > 1){
       	plurality6 = "s";
    }

    //The step instructions to add to the State objects
    step1 << "Pour " << diff1 << " gallon" << plurality1 << " from C to A. (" << (A+diff1) << ", " << B         << ", " << (C-diff1) << ")";
    step2 << "Pour " << diff2 << " gallon" << plurality2 << " from B to A. (" << (A+diff2) << ", " << (B-diff2) << ", " << C         << ")";
    step3 << "Pour " << diff3 << " gallon" << plurality3 << " from C to B. (" << A         << ", " << (B+diff3) << ", " << (C-diff3) << ")";
    step4 << "Pour " << diff4 << " gallon" << plurality4 << " from A to B. (" << (A-diff4) << ", " << (B+diff4) << ", " << C         << ")";
    step5 << "Pour " << diff5 << " gallon" << plurality5 << " from B to C. (" << A         << ", " << (B-diff5) << ", " << (C+diff5) << ")";
    step6 << "Pour " << diff6 << " gallon" << plurality6 << " from A to C. (" << (A-diff6) << ", " << B         << ", " << (C+diff6) << ")";

    //create the State objects
    State S1(A+diff1, B, C-diff1, state.get_steps(), step1.str());
    State S2(A+diff2, B-diff2, C, state.get_steps(), step2.str());
    State S3(A, B+diff3, C-diff3, state.get_steps(), step3.str());
    State S4(A-diff4, B+diff4, C, state.get_steps(), step4.str());
    State S5(A, B-diff5, C+diff5, state.get_steps(), step5.str());
    State S6(A-diff6, B, C+diff6, state.get_steps(), step6.str());

    //create integer vectors
    vector<int> V1 = state_to_vector(S1);
    vector<int> V2 = state_to_vector(S2);
    vector<int> V3 = state_to_vector(S3);
    vector<int> V4 = state_to_vector(S4);
    vector<int> V5 = state_to_vector(S5);
    vector<int> V6 = state_to_vector(S6);

    //add any positions that haven't been checked yet to the queue
    if(!already_checked(V1))
    	bfsQ.push(S1);
    if(!already_checked(V2))
    	bfsQ.push(S2);
    if(!already_checked(V3))
    	bfsQ.push(S3);
    if(!already_checked(V4))
    	bfsQ.push(S4);
    if(!already_checked(V5))
    	bfsQ.push(S5);
    if(!already_checked(V6))
    	bfsQ.push(S6);
    return;
}

vector<string> bfs(){
    /**
     * Runs a breadth first search and builds a vector of steps to a solution
     * Returns a vector of strings of steps for the solution
     */
	vector<string> steps;//to store the steps
	//the first line
	ostringstream init;
	init << "Initial state. (0, 0, " << c_cap << ")";
	steps.push_back(init.str());
	State initial(0, 0, c_cap, steps, "");
	bfsQ.push(initial);

	while(bfsQ.size()>0){
		State current = bfsQ.front();//get the front of the queue
		if(current.is_goal()){
			//if this is the goal then stop
			steps =  current.get_steps();
			break;
		}
		add_next_to_queue(current);//get the next steps and add the appropriate ones to the queue
		bfsQ.pop();//pop off the front of the queue
	}
	return steps;
}

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

    //get the steps to solve it as a vector of strings
    vector<string> steps = bfs();
    vector<string>::const_iterator step;
    ostringstream resp;
    //figure out what the steps are as an oss
    for (step = steps.begin(); step != steps.end(); ++step) {
    	resp << *step << "\n";
    }
    ostringstream res;
    res << "Initial state. (0, 0, " << c_cap << ")\n";
    //if there's one step and it's not the goal, say there's no solution
    if((resp.str()==res.str()) && (a_goal!=0) && (b_goal!=0)){
        cout << "No solution." << endl;
    }else{//otherwise print the steps
        cout << resp.str();
    }
    return 0;
}
