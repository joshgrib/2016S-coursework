/*******************************************************************************
 * Name        : sieve.cpp
 * Author      : Josh Gribbon
 * Date        : 2-8-16
 * Description : Sieve of Eratosthenes
 * Pledge      : I pledge my honor I have abided by the Stevens Honor System
 ******************************************************************************/
#include <cmath>
#include <iomanip>
#include <iostream>
#include <sstream>

using namespace std;

class PrimesSieve {
public:
    PrimesSieve(int limit) : is_prime_(new bool[limit + 1]), limit_(limit) {
        /**
         * Constructor - run sieve() which will find the primes up to the limit
         */
    	sieve();
    }

    ~PrimesSieve() {
    	/**
    	 * Deconstructor - delete what we don't need anymore
    	 */
        delete [] is_prime_;
    }

    inline int num_primes() const {
        return num_primes_;
    }

    void display_primes() const {
        /*
         * Display all prime numbers nicely
         * Lines are 80 characters at most
         * If theres one line then primes are seperated by a single space
         * If there are multiple lines then a right-aligned table should be printed
         */

    	ostringstream resp;
    	const int max_prime_width = num_digits(max_prime_);
    	const int primes_per_row = 80 / (max_prime_width + 1);
    	const int rows = num_primes()/primes_per_row;//number of rows starting at 0
    	int prime_count = 2;//because I place 2 in before the loop it starts on the second prime

    	if(rows!=0){//set preceding spaces if there's multiple rows
    		for(int i=0; i<max_prime_width-1; i++){
    			resp << " ";
    		}
    	}
    	resp << "2";

    	for(int i=3; i<=limit_; i++){
    		if(is_prime_[i]){
    			if(rows==0 /*|| prime_count%primes_per_row==1*/){//if there's only going to be one row, then only one space between primes
    				resp << " ";
    			}else if(prime_count%primes_per_row==1){
    				resp << setw(max_prime_width);
    			}else{//if its multiple rows then we need multiple spaces
    				resp << setw(max_prime_width+1);
    			}
    			resp << i;
    			if(prime_count%primes_per_row==0){//if this was the last prime of the row, indent
    				resp << endl;
    			}
    			prime_count++;
    		}
    	}

    	cout << "Primes up to " << limit_ << ":" << endl;
    	cout << resp.str();

    }

private:
    bool * const is_prime_; //const here means it can't be modified outside of the constructor
    const int limit_;
    int num_primes_, max_prime_;

    int count_num_primes() const {
        /**
         * Count the amount of prime numbers up to and including limit_ and return the amount
         */
    	int count = 0;
    	for(int i=2; i<=limit_; i++){
    		if(is_prime_[i]){
    			count++;
    		}
    	}
    	return count;
    }

    int num_digits(int num) const {
    	/**
    	 * Return the number of digits in the given integer
    	 */
    	int count = 1;
    	while(num/10 >= 1){
    		count++;
    		num = num/10;
    	}
    	return count;
    }

    void sieve() {
    	/**
    	 * Go through is_prime_, and array of size limit_, and set all values to true, then set all non-prime values to false
    	 */
    	fill_n(is_prime_, limit_+1, true);//fill the array with "true" bool values
    	for(int i=2; i <= sqrt(limit_); i++){
    		if(is_prime_[i]){
    			for(int j=i*i; j <= limit_; j=j+i){
    				is_prime_[j]=false;
    			}
    		}
    	}
    	for(int i=limit_; i>1; i--){
    		if(is_prime_[i]){
    			max_prime_=i;
    			break;
    		}
    	}
    	num_primes_ = count_num_primes();
    }
};

int main(void) {
    cout << "**************************** " <<  "Sieve of Eratosthenes" <<
            " ****************************" << endl;
    cout << "Search for primes up to: ";
    string limit_str;
    cin >> limit_str;
    int limit;

    // Use stringstream for conversion. Don't forget to #include <sstream>
    istringstream iss(limit_str);

    // Check for error.
    if ( !(iss >> limit) ) {
        cerr << "Error: Input is not an integer." << endl;
        return 1;
    }
    if (limit < 2) {
        cerr << "Error: Input must be an integer >= 2." << endl;
        return 1;
    }

    PrimesSieve myS(limit);
    cout << endl << "Number of primes found: " << myS.num_primes() << endl;
    myS.display_primes();

    cout << endl;

    return 0;
}
