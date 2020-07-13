/*******************************************************************************
 * Name    : shortestpaths.cpp
 * Author  : Joshua Mimer and Mark Pipko
 * Version : 1.0
 * Date    : November 20, 2019
 * Description : Solve the all pairs shortest paths problem with Floyd's algorithm. 
 * Pledge : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <iostream>
#include <sstream>
#include <iomanip>
#include <fstream>
#include <algorithm>
#include <iterator>
#include <string>
#include <vector>
#include <limits>
#include <climits>
using namespace std;
long num_vertices = 0;
const long INF = 999999999999999999;


long len(long num) {
    long count = 0;
    while(num >= 1) {
        count++;
        num = num / 10;
    }
    return count;
}

void display_table(long** const matrix, const string &label, const bool use_letters = false) {
	if(num_vertices == 1 && use_letters){
		cout << "Intermediate vertices:" << endl << "  A" << endl << "A -" << endl << endl; 
	}
	else{
	cout << label << endl;
	long max_val = 0;
	for (int i = 0; i < num_vertices; i++) {
		for (int j = 0; j < num_vertices; j++) {
			long cell = matrix[i][j];
				if (cell < INF && cell > max_val) {
					max_val = matrix[i][j];
				}
			}
		}
	int max_cell_width = use_letters ? len(max_val) : len(max(static_cast<long>(num_vertices), max_val));
	cout << ' ';
	for (int j = 0; j < num_vertices; j++) {
		cout << setw(max_cell_width + 1) << static_cast<char>(j + 'A');
	}
	cout << endl;
	for (int i = 0; i < num_vertices; i++) {
		cout << static_cast<char>(i + 'A');
		for (int j = 0; j < num_vertices; j++) {
			cout << " " << setw(max_cell_width);
			if (matrix[i][j] == INF) {
				cout << "-";
			} else if (use_letters) {
				cout << static_cast<char>(matrix[i][j] + 'A');
			} else {
				cout << matrix[i][j];
			}
		}
		cout << endl;
	}
	cout << endl;
}
}

 vector<char> baccing_up(int i, int j, long** intermediate, vector<char> path) {
 	if(intermediate[i][j] == INF){
	 	char a = i + 'A';
	 	char b = j + 'A';
	 	path.push_back(a);
	 	if(a != b){
	 		path.push_back(b);
	 	}
	 	return path;
	}
	vector<char> final =  baccing_up(i,intermediate[i][j], intermediate, path);
	vector<char> final1 = baccing_up(intermediate[i][j],j, intermediate, path);
	final.insert(final.end(), final1.begin() + 1, final1.end());
	return final;
 }

void print_path( long** paths, long** intermediate) {
	for(int i = 0; i < num_vertices; ++i){
		for(int j = 0; j <num_vertices; ++j){
			if(paths[i][j] == INF) {
            	cout << char('A' + i) << " -> " << char('A' + j) << ", distance: infinity, path: none" << endl;
        	}
        	else{
				cout << char('A'+i) << " -> " << char('A'+j) << ", distance: ";
				vector<char> path;
				path = baccing_up(i,j, intermediate,path);
				for(unsigned int f = 0; f < path.size(); ++f){
					if(f == 0){
						cout << paths[i][j] << ", path: " << path[0];
					}
					else{
						cout << " -> " << path[f];		
					}			
				}
			cout << endl;
		}
		}
	}

}

void floyds_alg(long** paths, long** intermediate){
	for(int k = 0; k < num_vertices; k++) {
        for(int i = 0; i < num_vertices; i++) {
            for(int j = 0; j < num_vertices; j++) {
                if(paths[i][k]+paths[k][j] < paths[i][j]) {
                    intermediate[i][j] = k;
                }
                paths[i][j] = min(paths[i][j], paths[i][k]+paths[k][j]);                
            }
        }
    }
}


int main(int argc, char * const argv[]) {
    if(argc != 2) {
        cerr << "Usage: " << argv[0] << " <filename>" << endl;
        return 1;
    }
    ifstream infile(argv[1]);
    if(!infile) {
        cerr << "Error: Cannot open file '" << argv[1] << "'." << endl;
        return 1;
    }
    string line;
    getline(infile, line);
    istringstream temp(line);
    if(!(temp >> num_vertices) || num_vertices < 1 || num_vertices > 26) {
        cerr << "Error: Invalid number of vertices '" << temp.str() << "' on line 1." << endl;
        return 1;
    }
    vector<string> entries;
    int line_number=2;
        while (getline(infile, line)) {
                istringstream iss(line);
                string a, b, c;
                long edgeweight;
                if (!(iss >> a >> b >> c)) {
                    cerr << "Error: Invalid edge data '" << iss.str() << "' on line " << line_number << "." << endl;
                    return 1;
                }
                iss >> a >> b >> c;
                entries.push_back(a);
                entries.push_back(b);
                entries.push_back(c);
                if(entries[0].at(0) < 'A' || entries[0].at(0) > ('A'+ num_vertices)) {
                    cerr << "Error: Starting vertex '" << a << "' on line " << line_number << " is not among valid values A-" << char(('A'+ num_vertices -1)) << "." << endl;
                    return 1;
                }
                if(entries[1].at(0) < 'A' || entries[1].at(0) > ('A'+ num_vertices)) {
                    cerr << "Error: Ending vertex '" << b << "' on line " << line_number << " is not among valid values A-" << char(('A'+ num_vertices -1)) << "." << endl;
                    infile.close();
                    return 1;
                }
                entries.clear();
                istringstream is_valid(c);
                if(!(is_valid >> edgeweight) || edgeweight < 1) {
                    cerr << "Error: Invalid edge weight '" << c << "' on line " << line_number << "." << endl;
                    return 1;
                }
            line_number++;
        }
        infile.close();
    long** distances = new long*[num_vertices];
    long** paths = new long*[num_vertices];
    long** intermediate = new long*[num_vertices];
    for(int i = 0; i < num_vertices; ++i){
        distances[i] = new long[num_vertices];
        paths[i] = new long[num_vertices];
        intermediate[i] = new long[num_vertices];        
        for(int k=0; k<num_vertices; ++k){
        	distances[i][k] = INF;
        	paths[i][k] = INF;
        	intermediate[i][k] = INF;
        }
    }  
    ifstream file(argv[1]);
    string ignore;
    getline(file, ignore);
    char a,b;
    long c;
    while(file >> a >> b >> c) {
        distances[a-65][b-65] = c;
    }
    for(int i = 0; i < num_vertices; i++) {
    	distances[i][i] = 0;
        for(int j = 0; j < num_vertices; j++) {
            paths[i][j] = distances[i][j];
        }
    }
    floyds_alg(paths,intermediate);
    display_table(distances, "Distance matrix:");
    display_table(paths, "Path lengths:");
    display_table(intermediate, "Intermediate vertices:",true);
    print_path(paths, intermediate);
    for (int i = 0; i < num_vertices; i++) {
        delete [] distances[i]; 
        delete [] intermediate[i];
        delete [] paths[i];
    }
}