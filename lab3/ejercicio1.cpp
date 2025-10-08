#include <iostream>
#include <fstream>
#include <string>
using namespace std;

string texto_a_binario(string texto) {
    string binario = "";
    for (int i = 0; i < texto.size(); i++) {
        unsigned char c = texto[i];
        for (int j = 7; j >= 0; j--) {
            if (c & (1 << j)) binario += "1";
            else binario += "0";
        }
    }
    return binario;
}

string metodo1(string bits, int n) {
    string salida = "";
    for (int i = 0; i < bits.size(); i += n) {
        string bloque = bits.substr(i, n);
        if (i == 0) {
            for (int j = 0; j < bloque.size(); j++) {
                salida += (bloque[j] == '0') ? '1' : '0';
            }
        } else {
            string anterior = salida.substr(i - n, n);
            int unos = 0, ceros = 0;
            for (int j = 0; j < anterior.size(); j++) {
                if (anterior[j] == '1') unos++;
                else ceros++;
            }
            if (unos == ceros) {
                for (int j = 0; j < bloque.size(); j++) {
                    salida += (bloque[j] == '0') ? '1' : '0';
                }
            } else if (ceros > unos) {
                for (int j = 0; j < bloque.size(); j++) {
                    if ((j % 2) == 0) salida += (bloque[j] == '0') ? '1' : '0';
                    else salida += bloque[j];
                }
            } else {
                for (int j = 0; j < bloque.size(); j++) {
                    if ((j % 3) == 0) salida += (bloque[j] == '0') ? '1' : '0';
                    else salida += bloque[j];
                }
            }
        }
    }
    return salida;
}

string metodo2(string bits, int n) {
    string salida = "";
    for (int i = 0; i < bits.size(); i += n) {
        string bloque = bits.substr(i, n);
        if (bloque.size() > 0) {
            salida += bloque[bloque.size() - 1];
            for (int j = 0; j < bloque.size() - 1; j++) {
                salida += bloque[j];
            }
        }
    }
    return salida;
}

int main() {
    string archivo_entrada, archivo_salida;
    int semilla, metodo;

    cout << "escribe el nombre del archivo de entrada: ";
    cin >> archivo_entrada;
    cout << "escribe el nombre del archivo de salida: ";
    cin >> archivo_salida;
    cout << "dime la semilla (n): ";
    cin >> semilla;
    cout << "dime el metodo (1 o 2): ";
    cin >> metodo;

    ifstream in(archivo_entrada.c_str());
    if (!in.is_open()) {
        cout << "no se pudo abrir el archivo de entrada" << endl;
        return 1;
    }

    string texto = "", linea;
    while (getline(in, linea)) {
        texto += linea + "\n";
    }
    in.close();

    string binario = texto_a_binario(texto);
    string codificado;
    if (metodo == 1) codificado = metodo1(binario, semilla);
    else codificado = metodo2(binario, semilla);

    ofstream out(archivo_salida.c_str());
    if (!out.is_open()) {
        cout << "no se pudo abrir el archivo de salida" << endl;
        return 1;
    }
    out << codificado;
    out.close();

    cout << "archivo codificado correctamente" << endl;
    return 0;
}
