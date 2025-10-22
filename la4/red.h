#ifndef RED_H
#define RED_H

#endif // RED_H
#include <iostream>
#include <map>
#include <vector>
#include <string>
#include "router.h"

using namespace std;

class red {
public:
    map<int, router> routers;
    void agregar_router(int id);
    void eliminar_router(int id);
    void agregar_conexion(int a, int b, int costo);
    void eliminar_conexion(int a, int b);
    void mostrar_conexiones();
    void mostrar_tabla_global();
    void construir_tablas();
    void cargar_desde_archivo(string nombre);
    void guardar_en_archivo(const string &nombre);
    void crear_aleatoria(int n, int max_costo);
    pair<map<int,int>, map<int,int>> dijkstra_dist_prev(int origen);
    void dijkstra(int origen, int destino);
};

