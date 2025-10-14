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
    int opcion;
    cout << "elige una opcion:" << endl;
    cout << "1. codificar archivo" << endl;
    cout << "2. decodificar archivo" << endl;
    cout << "opcion: ";
    cin >> opcion;