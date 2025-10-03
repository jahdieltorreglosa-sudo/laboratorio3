#include <iostream>
#include <fstream>
#include <string>
using namespace std;

struct usuario {
    string cedula;
    string clave;
    int saldo;
};

int main() {
    string opcion;
    cout << "escribe si eres admin o cliente: ";
    cin >> opcion;

    if (opcion == "admin") {
        ifstream in("sudo.txt");
        if (!in.is_open()) {
            cout << "no se encontro sudo.txt" << endl;
            return 1;
        }
        string clave;
        in >> clave;
        in.close();

        string clave_ingresada;
        cout << "escribe la clave de admin: ";
        cin >> clave_ingresada;

        if (clave_ingresada != clave) {
            cout << "clave incorrecta" << endl;
            return 0;
        }

        ofstream out("usuarios.txt", ios::app);
        if (!out.is_open()) {
            cout << "no se pudo abrir usuarios.txt" << endl;
            return 1;
        }

        usuario u;
        cout << "escribe la cedula: ";
        cin >> u.cedula;
        cout << "escribe la clave: ";
        cin >> u.clave;
        cout << "escribe el saldo: ";
        cin >> u.saldo;

        out << u.cedula << " " << u.clave << " " << u.saldo << endl;
        out.close();

        cout << "usuario registrado" << endl;
    } else {
        string ced, cla;
        cout << "escribe tu cedula: ";
        cin >> ced;
        cout << "escribe tu clave: ";
        cin >> cla;

        ifstream in("usuarios.txt");
        if (!in.is_open()) {
            cout << "no se encontro usuarios.txt" << endl;
            return 1;
        }

        usuario u;
        bool encontrado = false;
        while (in >> u.cedula >> u.clave >> u.saldo) {
            if (u.cedula == ced && u.clave == cla) {
                encontrado = true;
                break;
            }
        }
        in.close();

        if (!encontrado) {
            cout << "usuario no encontrado" << endl;
            return 0;
        }

        string accion;
        cout << "quieres consultar o retirar? ";
        cin >> accion;

        if (accion == "consultar") {
            u.saldo -= 1000;
            cout << "tu saldo es: " << u.saldo << endl;
        } else if (accion == "retirar") {
            int monto;
            cout << "cuanto quieres retirar: ";
            cin >> monto;
            if (monto + 1000 > u.saldo) {
                cout << "saldo insuficiente" << endl;
            } else {
                u.saldo -= monto + 1000;
                cout << "retiro exitoso, nuevo saldo: " << u.saldo << endl;
            }
        }
    }

    return 0;
}
