#include <iostream>
#include <map>
#include <vector>
using namespace std;

int main() {
    vector<int> routers = {1, 2, 3};
    map<int, map<int, int>> conexiones;

    conexiones[1][2] = 4;
    conexiones[2][1] = 4;
    conexiones[2][3] = 3;
    conexiones[3][2] = 3;
    conexiones[1][3] = 10;
    conexiones[3][1] = 10;

    cout << "1->2 costo: " << conexiones[1][2] << endl;
    cout << "2->3 costo: " << conexiones[2][3] << endl;
    cout << "1->3 costo: " << conexiones[1][3] << endl;

    cout << "la red tiene " << routers.size() << " routers." << endl;
    cout << "routers disponibles: ";
    for (int i = 0; i < routers.size(); i++) {
        cout << routers[i] << " ";
    }
    cout << endl;

    cout << "\nconexiones en la red:" << endl;
    for (int i = 0; i < routers.size(); i++) {
        int r = routers[i];
        for (auto &vecino : conexiones[r]) {
            cout << r << " -> " << vecino.first << "  costo: " << vecino.second << endl;
        }
    }

    int origen, destino;
    cout << "\nescribe el numero del router de origen: ";
    cin >> origen;
    cout << "escribe el numero del router de destino: ";
    cin >> destino;

    if (conexiones[origen][destino] > 0) {
        cout << "el costo de " << origen << " a " << destino << " es: " << conexiones[origen][destino] << endl;
    } else {
        cout << "no hay conexion directa entre " << origen << " y " << destino << endl;
    }

    char opcion;
    cout << "\nquieres agregar una nueva conexion? (s/n): ";
    cin >> opcion;

    while (opcion == 's' || opcion == 'S') {
        int nuevo_origen, nuevo_destino, nuevo_costo;
        cout << "ingresa router origen: ";
        cin >> nuevo_origen;
        cout << "ingresa router destino: ";
        cin >> nuevo_destino;
        cout << "ingresa el costo: ";
        cin >> nuevo_costo;

        conexiones[nuevo_origen][nuevo_destino] = nuevo_costo;
        conexiones[nuevo_destino][nuevo_origen] = nuevo_costo;

        cout << "\nconexion agregada: " << nuevo_origen << " <-> " << nuevo_destino 
             << " con costo " << nuevo_costo << endl;

        cout << "\nlista actualizada de conexiones:" << endl;
        for (int i = 0; i < routers.size(); i++) {
            int r = routers[i];
            for (auto &vecino : conexiones[r]) {
                cout << r << " -> " << vecino.first << "  costo: " << vecino.second << endl;
            }
        }

        cout << "\nquieres agregar otra conexion? (s/n): ";
        cin >> opcion;
    }

    cout << "\nprograma terminado." << endl;
    return 0;
}
