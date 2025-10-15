#include <iostream>
#include <fstream>
#include <string>
using namespace std;

//parte 1

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
// parte 2


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

string metodo1_inverso

string metodo2_inverso(string bits, int n) {
    string salida = "";
    for //(int i = 0; i

//parte 3

int main() {
    int opcion;
    cout << "Elige una opción:" << endl;
    cout << "1. Codificar archivo" << endl;
    cout << "2. Decodificar archivo" << endl;
    cout << "Opción: ";
    cin >> opcion;

    string archivo_entrada, archivo_salida;
    int semilla, metodo;

    if (opcion == 1) {
        cout << "escribe el nombre del archivo de entrada: ";
        cin >> archivo_entrada;
        cout << "escribe el nombre del archivo de salida: ";
        cin >> archivo_salida;
        cout << "dime la semilla (n): ";
        cin >> semilla;
        cout << "dime el metodo (1 o 2): ";
        cin >> metodo;

  else if (opcion == 2) {
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