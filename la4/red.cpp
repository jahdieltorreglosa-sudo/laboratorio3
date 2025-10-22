#include "red.h"
#include <fstream>
#include <climits>
#include <queue>
#include <algorithm>
#include <cstdlib>

void red::agregar_router(int id) {
    if (routers.find(id) == routers.end()) {
        router r;
        r.id = id;
        routers[id] = r;
        cout << "enrutador " << id << " agregado" << endl;
        construir_tablas();
    } else {
        cout << "el enrutador ya existe" << endl;
    }
}

void red::eliminar_router(int id) {
    if (routers.find(id) != routers.end()) {
        for (auto &p : routers) {
            p.second.vecinos.erase(id);
        }
        routers.erase(id);
        cout << "enrutador " << id << " eliminado" << endl;
        construir_tablas();
    } else {
        cout << "no existe ese enrutador" << endl;
    }
}

void red::agregar_conexion(int a, int b, int costo) {
    if (routers.find(a) == routers.end() || routers.find(b) == routers.end()) {
        cout << "uno de los enrutadores no existe" << endl;
        return;
    }
    routers[a].vecinos[b] = costo;
    routers[b].vecinos[a] = costo;
    cout << "enlace agregado entre " << a << " y " << b << " con costo " << costo << endl;
    construir_tablas();
}

void red::eliminar_conexion(int a, int b) {
    if (routers.find(a) == routers.end() || routers.find(b) == routers.end()) {
        cout << "uno de los enrutadores no existe" << endl;
        return;
    }
    routers[a].vecinos.erase(b);
    routers[b].vecinos.erase(a);
    cout << "enlace eliminado entre " << a << " y " << b << endl;
    construir_tablas();
}

void red::mostrar_conexiones() {
    if (routers.empty()) {
        cout << "no hay enrutadores en la red" << endl;
        return;
    }
    cout << "\nconexiones actuales:" << endl;
    for (auto &r : routers) {
        for (auto &v : r.second.vecinos) {
            cout << r.first << " -> " << v.first << " costo: " << v.second << endl;
        }
    }
}

void red::mostrar_tabla_global() {
    if (routers.empty()) {
        cout << "no hay enrutadores" << endl;
        return;
    }
    vector<int> ids;
    for (auto &p : routers) ids.push_back(p.first);
    sort(ids.begin(), ids.end());
    cout << "\t";
    for (int id : ids) cout << id << "\t";
    cout << endl;
    for (int i : ids) {
        cout << i << "\t";
        for (int j : ids) {
            int c = INT_MAX;
            if (routers[i].tabla_costos.find(j) != routers[i].tabla_costos.end()) {
                c = routers[i].tabla_costos[j];
            }
            if (c == INT_MAX) cout << "inf\t"; else cout << c << "\t";
        }
        cout << endl;
    }
}

void red::cargar_desde_archivo(string nombre) {
    ifstream archivo(nombre);
    if (!archivo.is_open()) {
        cout << "no se pudo abrir el archivo" << endl;
        return;
    }
    routers.clear();
    int a, b, c;
    while (archivo >> a >> b >> c) {
        if (routers.find(a) == routers.end()) {
            router r; r.id = a; routers[a] = r;
        }
        if (routers.find(b) == routers.end()) {
            router r; r.id = b; routers[b] = r;
        }
        routers[a].vecinos[b] = c;
        routers[b].vecinos[a] = c;
    }
    archivo.close();
    construir_tablas();
    cout << "topologia cargada desde " << nombre << endl;
}

pair<map<int,int>, map<int,int>> red::dijkstra_dist_prev(int origen) {
    map<int,int> dist;
    map<int,int> previo;
    for (auto &r : routers) dist[r.first] = INT_MAX;
    if (routers.find(origen) == routers.end()) return {dist, previo};
    dist[origen] = 0;
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pq;
    pq.push({0, origen});
    while (!pq.empty()) {
        auto top = pq.top(); pq.pop();
        int d = top.first;
        int u = top.second;
        if (d > dist[u]) continue;
        for (auto &v : routers[u].vecinos) {
            int w = v.first;
            int peso = v.second;
            if (dist[u] + peso < dist[w]) {
                dist[w] = dist[u] + peso;
                previo[w] = u;
                pq.push({dist[w], w});
            }
        }
    }
    return {dist, previo};
}

void red::dijkstra(int origen, int destino) {
    if (routers.find(origen) == routers.end() || routers.find(destino) == routers.end()) {
        cout << "uno de los enrutadores no existe" << endl;
        return;
    }
    auto dp = dijkstra_dist_prev(origen);
    auto dist = dp.first;
    auto previo = dp.second;
    if (dist[destino] == INT_MAX) {
        cout << "no hay camino entre " << origen << " y " << destino << endl;
        return;
    }
    cout << "costo minimo entre " << origen << " y " << destino << " es " << dist[destino] << endl;
    cout << "camino: ";
    vector<int> camino;
    for (int nodo = destino; nodo != origen; nodo = previo[nodo]) camino.push_back(nodo);
    camino.push_back(origen);
    for (int i = camino.size() - 1; i >= 0; i--) {
        cout << camino[i];
        if (i > 0) cout << " -> ";
    }
    cout << endl;
}

void red::crear_aleatoria(int n, int max_costo) {
    routers.clear();
    srand(1);
    for (int i = 1; i <= n; i++) {
        router r; r.id = i; routers[i] = r;
    }
    for (int i = 1; i <= n; i++) {
        for (int j = i + 1; j <= n; j++) {
            int enlace = rand() % 2;
            if (enlace == 1) {
                int costo = 1 + rand() % max_costo;
                routers[i].vecinos[j] = costo;
                routers[j].vecinos[i] = costo;
            }
        }
    }
    construir_tablas();
    cout << "red aleatoria creada con " << n << " enrutadores" << endl;
}

void red::guardar_en_archivo(const string &nombre) {
    ofstream f(nombre);
    if (!f.is_open()) {
        cout << "no se pudo abrir el archivo para escribir" << endl;
        return;
    }

    for (auto &p : routers) {
        int a = p.first;
        for (auto &v : p.second.vecinos) {
            int b = v.first;
            int costo = v.second;
            if (a < b) {
                f << a << " " << b << " " << costo << "\n";
            }
        }
    }

    f.close();
    cout << "topologia guardada en " << nombre << endl;
}

void red::construir_tablas() {
    for (auto &p : routers) {
        int origen = p.first;
        auto dp = dijkstra_dist_prev(origen);
        auto dist = dp.first;
        auto previo = dp.second;
        routers[origen].tabla_costos.clear();
        routers[origen].caminos.clear();
        for (auto &q : dist) {
            int destino = q.first;
            if (dist[destino] == INT_MAX) continue;
            routers[origen].tabla_costos[destino] = dist[destino];
            vector<int> path;
            int at = destino;
            while (at != origen) {
                path.push_back(at);
                at = previo[at];
            }
            path.push_back(origen);
            reverse(path.begin(), path.end());
            routers[origen].caminos[destino] = path;
        }
    }
}
