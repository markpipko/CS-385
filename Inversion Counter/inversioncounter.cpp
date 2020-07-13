/*******************************************************************************
 * Name        : inversioncounter.cpp
 * Author      : Mark Pipko
 * Version     : 1.0
 * Date        : October 21, 2019
 * Description : Counts the number of inversions in an array.
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <iostream>
#include <algorithm>
#include <sstream>
#include <vector>
#include <cstdio>
#include <cctype>
#include <cstring>

using namespace std;

// Function prototype.
static long mergesort(int array[], int scratch[], int low, int high);

/**
 * Counts the number of inversions in an array in theta(n^2) time.
 */
long count_inversions_slow(int array[], int length) {
    // TODO
    long count = 0;
    for(int i=0; i<length-1; i++){
        for(int k=i+1; k<length; k++){
            if(array[i] > array[k]){
                count++;
            }
        }
    }
    return count;
}

/**
 * Counts the number of inversions in an array in theta(n lg n) time.
 */
long count_inversions_fast(int array[], int length) {
    // TODO
    // Hint: Use mergesort!
    int *scratch = new int[length];
    long temp = mergesort(array,scratch,0,length-1);
    delete [] scratch;
    return temp;
}

static long mergesort(int array[], int scratch[], int low, int high) {
    // TODO
    long num = 0;
    if(high > low){
        int mid = low + (high-low)/2;
        num += mergesort(array, scratch, low, mid);
        num += mergesort(array, scratch, mid+1, high);
        int l = low;
        int h = mid+1;
        for(int i=low; i<=high;i++){
            if(l<=mid && (h>high || array[l] <= array[h])){
                    scratch[i] = array[l];
                    l++;
                }
            else{
                    num+= mid+1-l;
                    scratch[i] = array[h];
                    h++;
                }
        }
        for(int i=low;i<=high;i++){
            array[i] = scratch[i];
        }
    }
    return num;
}


int main(int argc, char *argv[]) {
    // TODO: parse command-line argument
    if(argc > 2){
        cout << "Usage: ./inversioncounter [slow]" << endl;
        return 1;
    }
    if(argc == 2){
        istringstream iss(argv[1]);
        string str;
        iss >> str;
        if(str.compare("slow") != 0){
            cerr << "Error: Unrecognized option '"<< str << "'." << endl;      
            return 1; 
        }
    }
    cout << "Enter sequence of integers, each followed by a space: " << flush;

    istringstream iss;
    int value, index = 0;
    vector<int> values;
    string str;
    str.reserve(11);
    char c;
    while (true) {
        c = getchar();
        const bool eoln = c == '\r' || c == '\n';
        if (isspace(c) || eoln) {
            if (str.length() > 0) {
                iss.str(str);
                if (iss >> value) {
                    values.push_back(value);
                } else {
                    cerr << "Error: Non-integer value '" << str
                         << "' received at index " << index << "." << endl;
                    return 1;
                }
                iss.clear();
                ++index;
            }
            if (eoln) {
                break;
            }
            str.clear();
        } else {
            str += c;
        }
    }

    // TODO: produce output
    if(values.size() == 0){
        cerr << "Error: Sequence of integers not received." << endl;
        return 1;
    }
    if(argc==2){
        cout << "Number of inversions: " << count_inversions_slow(&values[0], values.size()) << endl;
    }
   else{
        cout << "Number of inversions: " << count_inversions_fast(&values[0], values.size()) << endl;
    }
    return 0;
}
