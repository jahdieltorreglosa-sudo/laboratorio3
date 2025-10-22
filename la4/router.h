#ifndef ROUTER_H
#define ROUTER_H


#include <map>
#include <vector>
using namespace std;

class router {
public:
    int id;
    map<int,int> vecinos;
    map<int,int> tabla_costos;
    map<int, vector<int>> caminos;
};
#endif // ROUTER_H
