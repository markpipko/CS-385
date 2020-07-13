/*******************************************************************************
 * Name        : sieve.cpp
 * Author      : Mark Pipko
 * Date        : September 19th, 2019
 * Description : Sieve of Eratosthenes
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System. 
 ******************************************************************************/
#include <cmath>
#include <iomanip>
#include <iostream>
#include <sstream>

using namespace std;

class PrimesSieve {
public:
    PrimesSieve(int limit);

    ~PrimesSieve() {
        delete [] is_prime_;
    }

    int num_primes() const {
        return num_primes_;
    }

    void display_primes() const;

private:
    //Instance variables
    bool * const is_prime_;
    const int limit_;
    int num_primes_, max_prime_;

    //Method declarations
    int count_num_primes() const;
    void sieve();
    static int num_digits(int num);
};

    PrimesSieve::PrimesSieve(int limit) : is_prime_{new bool[limit + 1]}, limit_{limit} {
        sieve();
    }

     void PrimesSieve::display_primes() const {
        // TODO: write code to display the primes in the format specified in the
        // requirements document.
        int max_prime_width = num_digits(max_prime_),
        primes_per_row = 80 / (max_prime_width + 1);

        if(count_num_primes() < primes_per_row){ //If theres only one row
            max_prime_width = 1;
        }

        int full = 0; //keeps track of how many elements in the row to see if full or not
        for(int i=2; i<=limit_; i++){
            if(is_prime_[i]){
                if(i != max_prime_){ //is the loop up to the last prime that will be printed
                    if(full == primes_per_row - 1){ //row is about to be full
                        cout << setw(max_prime_width) << i << endl;
                        full = 0;
                    }
                    else{
                        cout << setw(max_prime_width) << i << " ";
                        full++;
                    }
                }
                else{
                    cout << i << endl;
                }
            }
        }
    }

    int PrimesSieve::count_num_primes() const {
        // TODO: write code to count the number of primes found
        int num = 0;
        for(int i=2; i<=limit_; i++){
            if(is_prime_[i]){
                num++;
            }
        }
        return num;
    }

    int PrimesSieve::num_digits(int num) {
        // TODO: write code to determine how many digits are in an integer
        // Hint: No strings are needed. Keep dividing by 10.
        int digit = 0;
        while(num>=1){
            num = num/10;
            digit++;
        }
        return digit;
    }

    void PrimesSieve::sieve() {
        // TODO: write sieve algorithm
        for(int i=2; i<=limit_; i++){
            is_prime_[i] = true;
        }
        for(int i=2; i<=sqrt(limit_); i++){
            if(is_prime_[i]){
                for(int k=i*i; k<=limit_; k=k+i){
                    is_prime_[k] = false;
                }
            }
        }
        for(int i=2; i<= limit_; i++){ // finds the max or last prime
            if(is_prime_[i]){
                max_prime_ = i;
            }
        }
        num_primes_ = count_num_primes();
    }


int main() {
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

    // TODO: write code that uses your class to produce the desired output.
    PrimesSieve num = PrimesSieve(limit);
    cout <<"\n" << "Number of primes found: " << 
    num.num_primes(); cout << "\n" << "Primes up to " << limit << ":" << endl;
    num.display_primes();
    return 0;
}
