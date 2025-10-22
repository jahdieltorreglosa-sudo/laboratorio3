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
            string archivo;
            cout << "ingrese el nombre del archivo: ";
            cin >> archivo;
            r.cargar_desde_archivo(archivo);
        }
        else if (opcion == 7) {
            r.mostrar_conexiones();
        }
        else if (opcion == 8) {
            int a, b;
            cout << "ingrese el enrutador origen: ";
            cin >> a;
            cout << "ingrese el enrutador destino: ";
            cin >> b;
            r.dijkstra(a, b);
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
