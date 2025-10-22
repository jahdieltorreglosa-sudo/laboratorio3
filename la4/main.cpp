#include "red.h"
using namespace std;

int main() {
    red r;
    int opcion = -1;

    while (opcion != 0) {
        cout << "\n--- menu red de enrutadores ---" << endl;
        cout << "1. agregar enrutador" << endl;
        cout << "2. remover enrutador" << endl;
        cout << "3. agregar enlace" << endl;
        cout << "4. eliminar enlace" << endl;
        cout << "5. actualizar costo de enlace" << endl;
        cout << "6. cargar topologia desde archivo" << endl;
        cout << "7. mostrar tabla de enrutamiento" << endl;
        cout << "8. obtener costo entre dos enrutadores" << endl;
        cout << "9. obtener camino eficiente entre dos enrutadores" << endl;
        cout << "0. salir" << endl;
        cout << "seleccione una opcion: ";
        cin >> opcion;

        if (opcion == 1) {
            int id;
            cout << "ingrese el id del enrutador: ";
            cin >> id;
            r.agregar_router(id);
        }
        else if (opcion == 2) {
            int id;
            cout << "ingrese el id del enrutador a eliminar: ";
            cin >> id;
            r.eliminar_router(id);
        }
        else if (opcion == 3) {
            int a, b, c;
            cout << "ingrese el enrutador origen: ";
            cin >> a;
            cout << "ingrese el enrutador destino: ";
            cin >> b;
            cout << "ingrese el costo del enlace: ";
            cin >> c;
            r.agregar_conexion(a, b, c);
        }
        else if (opcion == 4) {
            int a, b;
            cout << "ingrese el enrutador origen: ";
            cin >> a;
            cout << "ingrese el enrutador destino: ";
            cin >> b;
            r.eliminar_conexion(a, b);
        }
        else if (opcion == 5) {
            int a, b, c;
            cout << "ingrese el enrutador origen: ";
            cin >> a;
            cout << "ingrese el enrutador destino: ";
            cin >> b;
            cout << "nuevo costo del enlace: ";
            cin >> c;
            r.agregar_conexion(a, b, c);
        }
        else if (opcion == 6) {
            string modo;
            cout << "deseas cargar o guardar la topologia? ";
            cin >> modo;

            string nombre = "red.txt";

            if (modo == "cargar") {
                r.cargar_desde_archivo(nombre);
                cout << "\nred cargada correctamente desde " << nombre << endl;
                cout << "conexiones actuales:" << endl;
                r.mostrar_conexiones();
            }
            else if (modo == "guardar") {
                r.guardar_en_archivo(nombre);
                cout << "\nred guardada correctamente en " << nombre << endl;
            }
            else {
                cout << "opcion invalida" << endl;
            }
        }
        else if (opcion == 7) {
            r.mostrar_tabla_global();
        }
        else if (opcion == 8) {
            int a, b;
            cout << "ingrese el enrutador origen: ";
            cin >> a;
            cout << "ingrese el enrutador destino: ";
            cin >> b;
            if (r.routers.find(a) == r.routers.end() || r.routers.find(b) == r.routers.end()) {
                cout << "uno de los enrutadores no existe" << endl;
            } else {
                int costo = INT_MAX;
                if (r.routers[a].tabla_costos.find(b) != r.routers[a].tabla_costos.end()) {
                    costo = r.routers[a].tabla_costos[b];
                } else {
                    auto dp = r.dijkstra_dist_prev(a);
                    if (dp.first.find(b) != dp.first.end()) costo = dp.first[b];
                }
                if (costo == INT_MAX) cout << "no hay camino entre " << a << " y " << b << endl;
                else cout << "costo entre " << a << " y " << b << " es " << costo << endl;
            }
        }
        else if (opcion == 9) {
            int a, b;
            cout << "ingrese el enrutador origen: ";
            cin >> a;
            cout << "ingrese el enrutador destino: ";
            cin >> b;
            r.dijkstra(a, b);
        }
        else if (opcion == 0) {
            cout << "saliendo del programa..." << endl;
        }
        else {
            cout << "opcion no valida" << endl;
        }
    }

    return 0;
}
