#include <iostream>
#include <map>
#include <vector>

using namespace std;
int main() {
    vector<string> routers = {"A","B","C"};
    map<string, map<string,int>> conexiones;
    conexiones["A"]["B"] = 4;
    cout << "A->B costo: " << conexiones["A"]["B"] << endl;
    return 0; }
