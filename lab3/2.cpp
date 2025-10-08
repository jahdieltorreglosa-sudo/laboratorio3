#include <iostream>
#include <fstream>
#include <string>
using namespace std;

string binario_a_texto(string bits) {
    string texto = "";
    for (int i = 0; i + 7 < bits.size(); i += 8) {
        int valor = 0;
        for (int j = 0; j < 8; j++) {
            valor = valor * 2 + (bits[i + j] - '0');
        }
        texto += char(valor);
    }
    return texto;
}

// metodo inverso de codificacion 1
// (para simplificar: se vuelve a aplicar el mismo metodo sobre el archivo codificado)
string metodo1_inverso(string bits, int n) {
    return metodo1(bits, n); // en este caso es simetrico
}

// metodo inverso de codificacion 2
string metodo2_inverso(string bits, int n) {
    string salida = "";
    for (int i = 0; i < bits.size(); i += n) {
        string bloque = bits.substr(i, n);
        if (bloque.size() > 0) {
            string nuevo = "";
            for (int j = 1; j < bloque.size(); j++) {
                nuevo += bloque[j];
            }
            nuevo += bloque[0];
            salida += nuevo;
        }
    }
    return salida;
}

int main() {
    string archivo_entrada, archivo_salida;
    int semilla, metodo;

    cout << "escribe el archivo que vas a decodificar: ";
    cin >> archivo_entrada;
    cout << "escribe el archivo donde quieres guardar: ";
    cin >> archivo_salida;
    cout << "dime la semilla: ";
    cin >> semilla;
    cout << "dime el metodo (1 o 2): ";
    cin >> metodo;

    ifstream in(archivo_entrada.c_str());
    if (!in.is_open()) {
        cout << "no se pudo abrir el archivo" << endl;
        return 1;
    }
    string bits = "", linea;
    while (getline(in, linea)) {
        bits += linea;
    }
    in.close();

    string decodificado;
    if (metodo == 1) decodificado = metodo1_inverso(bits, semilla);
    else decodificado = metodo2_inverso(bits, semilla);

    string texto = binario_a_texto(decodificado);

    ofstream out(archivo_salida.c_str());
    if (!out.is_open()) {
        cout << "no se pudo abrir el archivo de salida" << endl;
        return 1;
    }
    out << texto;
    out.close();

    cout << "archivo decodificado listo" << endl;
    return 0;
}
