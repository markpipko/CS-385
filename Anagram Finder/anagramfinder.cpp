/*******************************************************************************
 * Name    : anagramfinder.cpp
 * Author  : Mark Pipko
 * Version : 1.0
 * Date    : November 11, 2019
 * Description : Finds the longest anagram.
 * Pledge : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
#include <sstream>
#include <cctype>
#include <algorithm> 
#include <fstream>
#include <stddef.h>
#include <bits/stdc++.h> 
using namespace std;

vector< vector<string> > create(vector<string> strs){
	map<string, vector< string>> umap;	
	vector< vector<string> > collect;
	for(unsigned int i=0; i<strs.size(); i++){
		string temp = strs[i];
		transform(temp.begin(), temp.end(), temp.begin(), ::tolower);
		sort(temp.begin(), temp.end());
		//if the key is found else
		if(umap.find(temp) != umap.end()){
			umap[temp].push_back(strs[i]);
		}
		else{
			vector<string> create{strs[i]};
			umap[temp] = create;
		}
	}	
	for(auto x : umap){
		sort(x.second.begin(),x.second.end());
		collect.push_back(x.second);
	}
	sort(collect.begin(),collect.end());
	return collect;
}

void show(vector<vector<string>> collect){
	vector<vector<string>> most;
	//find the max amount of anagrams and stores the largest groups
	unsigned int max = 0;
	for(unsigned int i=0; i<collect.size(); i++){
		if(max < collect[i].size()){
			max = collect[i].size();
			most.clear();
			most.push_back(collect[i]);
		}
		else if(max == collect[i].size()){
			most.push_back(collect[i]);
		}
	}
	//print out the anagram groups
	if(max > 1){
		sort(most.begin(),most.end());
		cout << "Max anagrams: " << max <<endl;
		for(unsigned int i=0; i<most.size(); i++){
			if(i==most.size()-1){
				for(unsigned int k=0; k<most[i].size(); k++){
					cout << most[i][k]<<endl;
				}
			}
			else{
				for(unsigned int k=0; k<most[i].size(); k++){
					cout << most[i][k] << endl;
				}
				cout << endl;
			}
		}
	}
	else{
		cout << "No anagrams found." << endl;
	}
}	

int main(int argc, char * const argv[]){
	if(argc != 2){
		cerr << "Usage: ./anagramfinder <dictionary file>" << endl;
		return 1;
	}
	ifstream inFile(argv[1]);
	if(!inFile){
		cerr << "Error: File '"<< argv[1] << "' not found." << endl;
		return 1;
	}
	string str;
	vector<string> strs;
	while(getline(inFile,str)){
		if(str.length() > 0){
			strs.push_back(str);
		}
	}
	show(create(strs));
	return 0;
}