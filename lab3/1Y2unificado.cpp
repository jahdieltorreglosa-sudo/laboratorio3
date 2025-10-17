#include <iostream>
#include <fstream>
#include <string>
using namespace std;

string texto_a_binario(string texto) {
    string binario = "";
    for (int i = 0; i < texto.size(); i++) {
        unsigned char c = texto[i];
        for (int j = 7; j >= 0; j--) {
            if (c & (1 << j)) {
                binario += "1";
            } else {
                binario += "0";
            }
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
                if (bloque[j] == '0') {
                    salida += '1';
                } else {
                    salida += '0';
                }
            }
        } else {
            string anterior = salida.substr(i - n, n);
            int unos = 0, ceros = 0;
            for (int j = 0; j < anterior.size(); j++) {
                if (anterior[j] == '1') {
                    unos++;
                } else {
                    ceros++;
                }
            }

            if (unos == ceros) {
                for (int j = 0; j < bloque.size(); j++) {
                    if (bloque[j] == '0') {
                        salida += '1';
                    } else {
                        salida += '0';
                    }
                }
            } else if (ceros > unos) {
                for (int j = 0; j < bloque.size(); j++) {
                    if (j % 2 == 0) {
                        if (bloque[j] == '0') {
                            salida += '1';
                        } else {
                            salida += '0';
                        }
                    } else {
                        salida += bloque[j];
                    }
                }
            } else {
                for (int j = 0; j < bloque.size(); j++) {
                    if (j % 3 == 0) {
                        if (bloque[j] == '0') {
                            salida += '1';
                        } else {
                            salida += '0';
                        }
                    } else {
                        salida += bloque[j];
                    }
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

string binario_a_texto(string bits) {
    string texto = "";
    for (int i = 0; i + 8 <= bits.size(); i += 8) {
        int valor = 0;
        for (int j = 0; j < 8; j++) {
            valor = valor * 2 + (bits[i + j] - '0');
        }
        texto += char(valor);
    }
    return texto;
}

string metodo1_inverso(string bits, int n) {
    return metodo1(bits, n);
}

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
    int opcion, metodo, semilla;
    string archivo_entrada, archivo_salida;

    cout << "1. Codificar" << endl;
    cout << "2. Decodificar" << endl;
    cout << "Elija una opcion: ";
    cin >> opcion;

    cout << "Ingrese la semilla: ";
    cin >> semilla;

    cout << "Ingrese el metodo (1 o 2): ";
    cin >> metodo;

    cout << "Ingrese el nombre del archivo de entrada: ";
    cin >> archivo_entrada;

    cout << "Ingrese el nombre del archivo de salida: ";
    cin >> archivo_salida;

    ifstream entrada(archivo_entrada);
    if (!entrada.is_open()) {
        cout << "No se pudo abrir el archivo de entrada" << endl;
        return 0;
    }

    string contenido = "", linea;
    while (getline(entrada, linea)) {
        if (opcion == 1) {
            contenido += linea + "\n";
        } else {
            contenido += linea;
        }
    }
    entrada.close();

    if (opcion == 1 && !contenido.empty()) {
        contenido.pop_back();
    }

    string resultado;
    if (opcion == 1) {
        string binario = texto_a_binario(contenido);
        if (metodo == 1) {
            resultado = metodo1(binario, semilla);
        } else {
            resultado = metodo2(binario, semilla);
        }
    } else {
        string decodificado;
        if (metodo == 1) {
            decodificado = metodo1_inverso(contenido, semilla);
        } else {
            decodificado = metodo2_inverso(contenido, semilla);
        }
        resultado = binario_a_texto(decodificado);
    }

    ofstream salida(archivo_salida);
    if (!salida.is_open()) {
        cout << "No se pudo abrir el archivo de salida" << endl;
        return 0;
    }
    salida << resultado;
    salida.close();

    cout << "Operacion completada." << endl;

    return 0;
}
