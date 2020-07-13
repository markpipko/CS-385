/*******************************************************************************
 * Name        : stairclimber.cpp
 * Author      : Mark Pipko
 * Date        : September 23, 2019
 * Description : Lists the number of ways to climb n stairs.
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>
#include <iomanip>

using namespace std;

vector< vector<int> > get_ways(int num_stairs) {
    // TODO: Return a vector of vectors of ints representing
    // the different combinations of ways to climb num_stairs
    // stairs, moving up either 1, 2, or 3 stairs at a time.
    vector<vector<int>> ways;
    if(num_stairs <= 0){
    	vector<int> temp;
    	ways.push_back(temp);
    }
    else{
    	for(int i=1; i<4; i++){
    		if(num_stairs >= i){
    			vector<vector<int>> result;
    			result = get_ways(num_stairs - i);
    			for(vector<int> r: result){
    					r.insert(r.cbegin(),i);
    					ways.push_back(r);
    			}
    		}
    	}
    }
    return ways;
}

void display_ways(const vector< vector<int> > &ways) {
    // TODO: Display the ways to climb stairs by iterating over
    // the vector of vectors and printing each combination.
    if(ways[0].size() == 1){
    	cout << ways.size() << " way to climb " << ways[0].size() << " stair." << endl;
    }
    else{
    	cout << ways.size() << " ways to climb " << ways[0].size() << " stairs." << endl;
    }
    for(long unsigned int i=0; i<ways.size(); i++){
    	if(ways.size() < 10){
    		cout << i+1 << ". [";  
    	}
    	else{
    		if(i+1 < 10){
    			cout << " " << i+1 << ". [";  
    		}
    		else{
    			cout << i+1 << ". [";  
    		} 
    	}    	 
    	for(long unsigned int k=0; k<ways[i].size(); k++){
    		if(k == ways[i].size() - 1){
    			cout << ways[i][k] << "]" << endl;
    		}
    		else{
    			cout << ways[i][k] << ", ";
    		}
    	}
    }
}

int main(int argc, char * const argv[]) {
	if(argc == 1){
		cout << "Usage: ./stairclimber <number of stairs>" << endl;
		return 1;
	}
	istringstream iss;
	iss.str(argv[1]);
	int n;
	if(argc > 2){
		cout << "Usage: ./stairclimber <number of stairs>" << endl;
	}
	else if(!(iss >> n) || n <= 0){
		cout << "Error: Number of stairs must be a positive integer." << endl;
	}
	else{
		display_ways(get_ways(n));
	}
}
