#include "red.h"


void red::agregar_router(int id) {
    if (routers.find(id) == routers.end()) {
        router r;
        r.id = id;
        routers[id] = r;
        cout << "router " << id << " agregado" << endl;
    } else {
        cout << "el router ya existe" << endl;
    }
}

void red::eliminar_router(int id) {
    if (routers.find(id) != routers.end()) {
        for (auto &p : routers) {
            p.second.vecinos.erase(id);
        }
        routers.erase(id);
        cout << "router " << id << " eliminado" << endl;
    } else {
        cout << "no existe ese router" << endl;
    }
}


void red::agregar_conexion(int a, int b, int costo) {
    if (routers.find(a) == routers.end() || routers.find(b) == routers.end()) {
        cout << "uno de los routers no existe" << endl;
        return;
    }
    routers[a].vecinos[b] = costo;
    routers[b].vecinos[a] = costo;
    cout << "conexion agregada entre " << a << " y " << b << " con costo " << costo << endl;
}

void red::eliminar_conexion(int a, int b) {
    if (routers.find(a) == routers.end() || routers.find(b) == routers.end()) {
        cout << "uno de los routers no existe" << endl;
        return;
    }
    routers[a].vecinos.erase(b);
    routers[b].vecinos.erase(a);
    cout << "conexion eliminada entre " << a << " y " << b << endl;
}


void red::mostrar_conexiones() {
    if (routers.empty()) {
        cout << "no hay routers en la red" << endl;
        return;
    }
    cout << "\nconexiones en la red:" << endl;
    for (auto &r : routers) {
        for (auto &v : r.second.vecinos) {
            cout << r.first << " -> " << v.first << " costo: " << v.second << endl;
        }
    }
}


void red::construir_tablas() {}
void red::cargar_desde_archivo(string nombre) {}
void red::crear_aleatoria(int n, int max_costo) {}
void red::dijkstra(int origen, int destino) {}


