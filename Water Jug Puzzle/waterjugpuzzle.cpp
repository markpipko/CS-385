/*******************************************************************************
 * Name        : waterjugpuzzle.cpp
 * Author      : Mark Pipko & Joshua Mimer
 * Date        : October 2, 2019
 * Description : Solves the famous water jug puzzle. 
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <iostream>
#include <string>
#include <sstream>
#include <queue>
#include <vector>

using namespace std;

int capacity_a, capacity_b, capacity_c;
string build;
int goal[2];
bool made = false;

//Creates a class used for the states of each jug of water.
struct State {
private:
    vector<string> directions;
    int jug_a, jug_b, jug_c;
public:
    State(int _a, int _b, int _c, vector<string> adjacent){
    jug_a = _a;
    jug_b = _b;
    jug_c = _c;
    directions = adjacent;
}
    string to_string() {
    ostringstream oss;
    oss << "(" << jug_a << ", " << jug_b << ", " << jug_c << ")";
    return oss.str();
}
    vector<string> get_directions() {
        return directions;
    }
    void g_vector() {
        for(unsigned int i= 0; i<directions.size(); i++) {
            cout << directions[i] << endl;
        }
    }
    int get_a() {
        return jug_a;
    }

    int get_b() {
        return jug_b;
    }

    int get_c() {
        return jug_c;
    }
};
vector<string> directions(int a, int b, int c) {
    vector<string> directions;
    stringstream iss;
    iss << "Initial state. (" << a << ", " << b << ", " << c << ")";
    directions.push_back(iss.str());
    return directions;
    }

string too_string(int a, int b, int c) {
    string hoj;
    stringstream iss;
    iss << "(" << a << ", " << b << ", " << c << ")";
    hoj = iss.str();
    return hoj;
}
queue<State> Q;

void BFS(int jug_a, int jug_b, int jug_c) {
    //creates 2d array to see if a state has been visited
    bool **visited = new bool*[capacity_a + 1];
    for (int i = 0; i < capacity_a + 1; i++) {
        visited[i] = new bool[capacity_b + 1];
        fill(visited[i], visited[i] + capacity_b + 1, false);
    }
    vector<string> first;
    State states(jug_a, jug_b, jug_c, directions(jug_a, jug_b, jug_c));
    Q.push(states);
    while (!Q.empty()) {
        jug_a = Q.front().get_a();
        jug_b = Q.front().get_b();
        jug_c = Q.front().get_c();
        visited[jug_a][jug_b] = true;
        if ((jug_a == goal[0]) && (jug_b == goal[1])) {
            Q.front().g_vector();
            made = true;
            break;
        }
        State top = Q.front();
        Q.pop();

        for(int i = 1; i < 7; i++){
            //A to C.
            if (i==1) {
                int temp1 = jug_c;
                int a = jug_a + jug_c;
                int b = jug_b;
                int c = 0;
                while(a > capacity_a){
                    a-=1;
                    c+=1;
                    temp1--;
                }
                stringstream iss;
                if (temp1 == 1) {
                    build = "Pour 1 gallon from C to A. ";
                } else {
                    iss << temp1;
                    build = "Pour " + iss.str() + " gallons from C to A. ";
                }
                if (!visited[a][b]) {
                    vector<string> path = top.get_directions() ;
                    path.push_back(build + too_string(a, b, c));
                    State c_a(a, b, c, path);
                    Q.push(c_a);
                }
            }

            // B to A.
            if (i==2) {
                int temp2 = jug_b;
                int a = jug_a + jug_b;
                int b = 0;
                int c = jug_c;
                while(a > capacity_a){
                    a-=1;
                    b+=1;
                    temp2--;
                }
                stringstream iss;
                if (temp2 == 1) {
                    build = "Pour 1 gallon from B to A. ";
                } else {
                    iss << temp2;
                    build = "Pour " + iss.str() + " gallons from B to A. ";
                }
                if (!visited[a][b]) {
                    vector<string> path = top.get_directions();
                    path.push_back(build + too_string(a, b, c));
                    State b_a(a, b, c, path);
                    Q.push(b_a);
                    }
                }
            //C to B.
            if (i==3) {
                int temp3 = jug_c;
                int b = jug_c + jug_b;
                int a = jug_a;
                int c = 0;
                while(b > capacity_b){
                    b-=1;
                    c+=1;
                    temp3--;
                }
                stringstream iss;
                if (temp3 == 1) {
                    build = "Pour 1 gallon from C to B. ";
                } else {
                    iss << temp3;
                    build = "Pour " + iss.str() + " gallons from C to B. ";
                }
                if (!visited[a][b]) {
                    vector<string> path = top.get_directions();
                    path.push_back(build + too_string(a, b, c));
                    State c_b(a, b, c, path);
                    Q.push(c_b);
                }
            }

            //A to B.
            if (i==4) {
                int temp4 = jug_a;
                int c = jug_c;
                int b = jug_a + jug_b;
                int a = 0;
                while(b > capacity_b){
                    b-=1;
                    a+=1;
                    temp4--;
                }
                stringstream iss;
                if(temp4 == 1){
                    build = "Pour 1 gallon from A to B. ";
                }
                else{
                    iss << temp4;
                    build = "Pour " + iss.str() + " gallons from A to B. ";
                }
                if (!visited[a][b]) {
                    vector<string> path = top.get_directions();
                    path.push_back(build + too_string(a, b, c));
                    State a_b(a, b, c, path);
                    Q.push(a_b);
                    }
                }
            //B to C.
            if (i==5) {
                int temp5 = jug_b;
                int c = jug_b + jug_c;
                int a = jug_a;
                int b = 0;
                while(c > capacity_c){
                    c-=1;
                    b+=1;
                    temp5--;
                }
                stringstream iss;
                if (temp5 == 1) {
                    build = "Pour 1 gallon from B to C. ";
                } else {
                    iss << temp5;
                    build = "Pour " + iss.str() + " gallons from B to C. ";
                }
                if (!visited[a][b]) {
                    vector<string> path = top.get_directions();
                    path.push_back(build + too_string(a, b, c));
                    State b_c(a, b, c, path);
                    Q.push(b_c);
                    }
                }
            //A to C.
            if (i==6) {
                int temp6 = jug_a;
                int c = jug_a + jug_c;
                int b = jug_b;
                int a = 0;
                while(c > capacity_c){
                    c-=1;
                    a+=1;
                    temp6--;
                }         
                stringstream iss;
                if (temp6 == 1) {
                    build = "Pour 1 gallon from A to C. ";
                } else {
                    iss << temp6;
                    build = "Pour " + iss.str() + " gallons from A to C. ";
                }
                if (!visited[a][b]) {
                    vector<string> path = top.get_directions();
                    path.push_back(build + too_string(a, b, c));
                    State a_c(a, b, c, path);
                    Q.push(a_c);
                    }
                }
        }
        }
    
    if (!made)
        cout << "No solution." << endl;

    delete[] visited;
}
int main(int argc, char * const argv[]) {

    if (argc != 7) {
        cerr << "Usage: " << argv[0] << " <cap A> <cap B> <cap C> <goal A> <goal B> <goal C>" << endl;
        return 1;
    }

    int cA, cB, cC, gA, gb, gC;
    istringstream iss_1(argv[1]);
    istringstream iss_2(argv[2]);
    istringstream iss_3(argv[3]);
    istringstream iss_4(argv[4]);
    istringstream iss_5(argv[5]);
    istringstream iss_6(argv[6]);
    if(!(iss_1 >> cA) || cA < 0){
        cerr << "Error: Invalid capacity '" << iss_1.str() << "' for jug A." << endl;
        return 1;
    }
    if(!(iss_2 >> cB) || cB < 0){
        cerr << "Error: Invalid capacity '" << iss_2.str() << "' for jug B." << endl;
        return 1;
    }
    if(!(iss_3 >> cC) || cC < 0){
        cerr << "Error: Invalid capacity '" << iss_3.str() << "' for jug C." << endl;
        return 1;
    }
    if(!(iss_4 >> gA) || gA < 0){
        cerr << "Error: Invalid goal '" << iss_4.str() << "' for jug A." << endl;
        return 1;
    }
    if(!(iss_5 >> gb) || gb < 0){
        cerr << "Error: Invalid goal '" << iss_5.str() << "' for jug B." << endl;
        return 1;
    }
    if(!(iss_6 >> gC) || gC < 0){
        cerr << "Error: Invalid goal '" << iss_6.str() << "' for jug C." << endl;
        return 1;
    }
    if(cC == 0){
        cerr << "Error: Invalid capacity '0' for jug C." << endl;
        return 1;
    }
    if(gA > cA){
        cerr << "Error: Goal cannot exceed capacity of jug A." << endl;
        return 1;
    }
    if(gb > cB){
        cerr << "Error: Goal cannot exceed capacity of jug B." << endl;
        return 1;
    }
    if(gC > cC){
        cerr << "Error: Goal cannot exceed capacity of jug C." << endl;
        return 1;
    }
    if(gC + gb + gA != cC){
        cerr << "Error: Total gallons in goal state must be equal to the capacity of jug C." << endl;
        return 1;
    }
    goal[0] = gA;
    goal[1] = gb;
    goal[2] = gC;
    capacity_a = cA;
    capacity_b = cB;
    capacity_c = cC;
    BFS(0, 0, capacity_c);
}
