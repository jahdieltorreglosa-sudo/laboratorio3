#include <iostream>
#include <fstream>
#include <string>
using namespace std;


string texto_a_binario(string texto) {
    string binario = "";
    for (char c : texto) {
        for (int j = 7; j >= 0; j--) {
            binario += ((c >> j) & 1) ? '1' : '0';
        }
    }
    return binario;
}

string binario_a_texto(string bits) {
    string texto = "";
    for (int i = 0; i + 8 <= (int)bits.size(); i += 8) {
        int valor = 0;
        for (int j = 0; j < 8; j++) {
            valor = valor * 2 + (bits[i + j] - '0');
        }
        texto += char(valor);
    }
    return texto;
}

string metodo1(string bits, int n) {
    string salida = "";
    for (int i = 0; i < bits.size(); i += n) {
        string bloque = bits.substr(i, n);

        if (i == 0) {
            for (char b : bloque)
                salida += (b == '0') ? '1' : '0';
        } else {
            string anterior = bits.substr(i - n, n);
            int unos = 0, ceros = 0;
            for (char b : anterior) (b == '1') ? unos++ : ceros++;

            if (unos == ceros) {
                for (char b : bloque)
                    salida += (b == '0') ? '1' : '0';
            } else if (ceros > unos) {
                for (int j = 0; j < bloque.size(); j++)
                    salida += (j % 2 == 0) ? ((bloque[j] == '0') ? '1' : '0') : bloque[j];
            } else {
                for (int j = 0; j < bloque.size(); j++)
                    salida += (j % 3 == 0) ? ((bloque[j] == '0') ? '1' : '0') : bloque[j];
            }
        }
    }
    return salida;
}


string metodo1_inverso(string bits, int n) {
    string salida = "";
    for (int i = 0; i < bits.size(); i += n) {
        string bloque = bits.substr(i, n);

        if (i == 0) {
            for (char b : bloque)
                salida += (b == '0') ? '1' : '0';
        } else {
            string anterior_decod = salida.substr(i - n, n);
            int unos = 0, ceros = 0;
            for (char b : anterior_decod) (b == '1') ? unos++ : ceros++;

            if (unos == ceros) {
                for (char b : bloque)
                    salida += (b == '0') ? '1' : '0';
            } else if (ceros > unos) {
                for (int j = 0; j < bloque.size(); j++)
                    salida += (j % 2 == 0) ? ((bloque[j] == '0') ? '1' : '0') : bloque[j];
            } else {
                for (int j = 0; j < bloque.size(); j++)
                    salida += (j % 3 == 0) ? ((bloque[j] == '0') ? '1' : '0') : bloque[j];
            }
        }
    }
    return salida;
}

string metodo2(string bits, int n) {
    string salida = "";
    for (int i = 0; i < bits.size(); i += n) {
        string bloque = bits.substr(i, n);
        if (!bloque.empty()) {
            salida += bloque.substr(1) + bloque[0];
        }
    }
    return salida;
}


string metodo2_inverso(string bits, int n) {
    string salida = "";
    for (int i = 0; i < bits.size(); i += n) {
        string bloque = bits.substr(i, n);
        if (!bloque.empty()) {
            salida += bloque.back() + bloque.substr(0, bloque.size() - 1);
        }
    }
    return salida;
}

int main() {
    try {
        int opcion, metodo, semilla;
        string archivo_entrada, archivo_salida;

        cout << "CODIFICADOR--DECODIFICADOR" << endl;
        cout << "1. Codificar\n2. Decodificar\nOpcion: ";
        cin >> opcion;

        cout << "Metodo (1 o 2): ";
        cin >> metodo;

        cout << "ingresa n: ";
        cin >> semilla;

        cout << "Archivo de entrada: ";
        cin >> archivo_entrada;

        cout << "Archivo de salida: ";
        cin >> archivo_salida;

        ifstream entrada(archivo_entrada);
        if (!entrada.is_open()) {
            cerr << "no se pudo abrir el archivo de entrada." << endl;
            return 1;
        }

        string contenido((istreambuf_iterator<char>(entrada)), istreambuf_iterator<char>());
        entrada.close();

        if (contenido.empty()) {
            cerr << "archivo vacio." << endl;
            return 1;
        }

        string resultado;

        if (opcion == 1) {

            string binario = texto_a_binario(contenido);
            resultado = (metodo == 1) ? metodo1(binario, semilla) : metodo2(binario, semilla);
        } else {

            string decod_bits = (metodo == 1) ? metodo1_inverso(contenido, semilla)
                                              : metodo2_inverso(contenido, semilla);
            resultado = binario_a_texto(decod_bits);
        }

        ofstream salida(archivo_salida);
        if (!salida.is_open()) {
            cerr << "no se pudo crear el archivo de salida." << endl;
            return 1;
        }

        salida << resultado;
        salida.close();

        cout << "Operacion completada correctamente." << endl;
        cout << "Archivo generado: " << archivo_salida << endl;

    } catch (const exception &e) {
        cerr << "Error: " << e.what() << endl;
    }

    return 0;
}
