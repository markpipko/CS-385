/*******************************************************************************
 * Name        : unique.cpp
 * Author      : Mark Pipko
 * Date        : September 17, 2019
 * Description : Determining uniqueness of chars with int as bit vector.
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <iostream>
#include <cctype>

using namespace std;

bool is_all_lowercase(const string &s) {
    // TODO: returns true if all characters in string are lowercase
    // letters in the English alphabet; false otherwise.
    for(unsigned int i=0; i<s.length(); i++){
    	if( s[i] > 96 && s[i] < 123 ){

    	}
    	else{
    		return false;
    	}
    }
    return true;
}

bool all_unique_letters(const string &s) {
    unsigned int byte = 0; 
    for( unsigned int i=0; i<s.length(); i++){
    	unsigned int temp = 1<<(s[i] - 97);
    	if(temp == 0){
    		temp++;
    	}
    	if((byte & temp)  > 0){
    		return false;
    	}
    	else{
    		byte = byte | temp;
    	}
    }
    return true;
}

int main(int argc, char * const argv[]) {
    // TODO: reads and parses command line arguments.
    // Calls other functions to produce correct output.
    if(argc == 1){
    	cout << "Usage: ./unique <string>";
    }

    else if(argc > 2){
    	cout << "Usage: ./unique <string>" ;
    }

    else if(is_all_lowercase(argv[1])){
    	if(all_unique_letters(argv[1])){
    		cout << "All letters are unique.";
    	}
    	else{
    		cout << "Duplicate letters found.";
    	}
    }
    else{
    	cout << "Error: String must contain only lowercase letters.";
    }
}
