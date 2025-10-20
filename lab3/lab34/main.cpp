#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <sstream>
#include <iomanip>
#include <cstdlib>

using namespace std;

struct usuario {
    string cedula;
    string clave;
    long long saldo;
};

const int N_GRUPO = 4;

string ahora() {
    time_t t = time(nullptr);
    struct tm tmv;
#ifdef _WIN32
    localtime_s(&tmv, &t);
#else
    localtime_r(&t, &tmv);
#endif
    char buf[32];
    strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", &tmv);
    return string(buf);
}


string texto_a_bits(const string &s) {
    string bits = "";
    for (size_t i = 0; i < s.size(); ++i) {
        unsigned char c = s[i];
        for (int b = 7; b >= 0; --b) bits.push_back(((c >> b) & 1) ? '1' : '0');
    }
    return bits;
}

string bits_a_texto(const string &bits) {
    string b = bits;
    while (b.size() % 8 != 0) b.push_back('0');
    string out = "";
    for (size_t i = 0; i < b.size(); i += 8) {
        unsigned char val = 0;
        for (int k = 0; k < 8; ++k) val = (val << 1) | (b[i + k] == '1' ? 1 : 0);
        out.push_back((char)val);
    }
    return out;
}

string bytes_a_hex(const string &bytes) {
    stringstream ss;
    ss << hex << setfill('0');
    for (size_t i = 0; i < bytes.size(); ++i) {
        unsigned char c = bytes[i];
        ss << setw(2) << (int)c;
    }
    return ss.str();
}

string hex_a_bytes(const string &hexs) {
    string out = "";
    for (size_t i = 0; i + 1 < hexs.size(); i += 2) {
        string h = hexs.substr(i, 2);
        char v = (char) strtol(h.c_str(), nullptr, 16);
        out.push_back(v);
    }
    return out;
}

string codificar_me2(const string &plain, int n) {
    string bits = texto_a_bits(plain);
    while (bits.size() % n != 0) bits.push_back('0');
    string out_bits = "";
    for (size_t i = 0; i < bits.size(); i += n) {

        out_bits.push_back(bits[i + n - 1]);
        for (int k = 0; k < n - 1; ++k) out_bits.push_back(bits[i + k]);
    }
    return bits_a_texto(out_bits);
}


string decodificar_me2(const string &encoded, int n) {
    string bits = texto_a_bits(encoded);
    while (bits.size() % n != 0) bits.push_back('0');
    string out_bits = "";
    for (size_t i = 0; i < bits.size(); i += n) {

        for (int k = 1; k < n; ++k) out_bits.push_back(bits[i + k]);
        out_bits.push_back(bits[i + 0]);
    }
    return bits_a_texto(out_bits);
}


bool existe_usuario(const string &ced, usuario &u) {
    ifstream in("usuarios.txt");
    if (!in.is_open()) return false;
    usuario tmp;
    while (in >> tmp.cedula >> tmp.clave >> tmp.saldo) {
        if (tmp.cedula == ced) {
            u = tmp;
            in.close();
            return true;
        }
    }
    in.close();
    return false;
}

bool anadir_usuario(const usuario &u) {
    usuario tmp;
    if (existe_usuario(u.cedula, tmp)) return false;
    ofstream out("usuarios.txt", ios::app);
    if (!out.is_open()) return false;
    out << u.cedula << " " << u.clave << " " << u.saldo << "\n";
    out.close();
    return true;
}

bool actualizar_saldo(const usuario &u_act) {
    ifstream in("usuarios.txt");
    if (!in.is_open()) return false;
    ofstream out("usuarios_tmp.txt");
    if (!out.is_open()) { in.close(); return false; }
    usuario tmp;
    bool mod = false;
    while (in >> tmp.cedula >> tmp.clave >> tmp.saldo) {
        if (tmp.cedula == u_act.cedula) {
            out << u_act.cedula << " " << u_act.clave << " " << u_act.saldo << "\n";
            mod = true;
        } else {
            out << tmp.cedula << " " << tmp.clave << " " << tmp.saldo << "\n";
        }
    }
    in.close();
    out.close();
    if (!mod) { remove("usuarios_tmp.txt"); return false; }
    remove("usuarios.txt");
    rename("usuarios_tmp.txt", "usuarios.txt");
    return true;
}


bool existe_sudo() {
    ifstream f("sudo.txt");
    bool ok = f.is_open();
    if (ok) f.close();
    return ok;
}

bool crear_sudo(const string &clave) {
    string cod = codificar_me2(clave, N_GRUPO);
    string hexed = bytes_a_hex(cod);
    ofstream out("sudo.txt");
    if (!out.is_open()) return false;
    out << hexed << "\n";
    out.close();
    return true;
}

bool leer_sudo(string &clave_out) {
    ifstream in("sudo.txt");
    if (!in.is_open()) return false;
    string hexed;
    in >> hexed;
    in.close();
    string bytes = hex_a_bytes(hexed);
    string dec = decodificar_me2(bytes, N_GRUPO);

    size_t pos = dec.find('\0');
    if (pos != string::npos) dec = dec.substr(0, pos);
    clave_out = dec;
    return true;
}

bool log_transaccion(const string &linea) {
    string cod = codificar_me2(linea, N_GRUPO);
    string hexed = bytes_a_hex(cod);
    ofstream out("transactions.txt", ios::app);
    if (!out.is_open()) return false;
    out << hexed << "\n";
    out.close();
    return true;
}


int main() {

    if (!existe_sudo()) {
        cout << "No se encontro sudo.txt. Crear clave admin ahora? (si/no): ";
        string r; cin >> r;
        if (r == "si") {
            cout << "Ingrese nueva clave admin: ";
            string nueva; cin >> nueva;
            if (!crear_sudo(nueva)) {
                cout << "Error creando sudo.txt\n";
                return 1;
            }
            cout << "sudo.txt creado (codificado).\n";
        } else {
            cout << "Continuando sin modo admin configurado.\n";
        }
    }

    cout << "escribe si eres admin o cliente: ";
    string opcion; cin >> opcion;

    if (opcion == "admin") {
        string clave_archivo;
        if (!leer_sudo(clave_archivo)) {
            cout << "No se pudo leer sudo.txt\n";
            return 1;
        }
        cout << "escribe la clave de admin: ";
        string clave_ing; cin >> clave_ing;
        if (clave_ing != clave_archivo) {
            cout << "clave incorrecta\n";
            return 0;
        }

        usuario u;
        cout << "escribe la cedula: "; cin >> u.cedula;
        cout << "escribe la clave: "; cin >> u.clave;
        cout << "escribe el saldo: "; cin >> u.saldo;

        if (!anadir_usuario(u)) {
            cout << "error: cedula ya registrada o archivo inaccesible\n";
            return 1;
        }
        cout << "usuario registrado\n";

        string linea = ahora() + " | " + u.cedula + " | REGISTRO | 0 | 0 | " + to_string(u.saldo);
        if (!log_transaccion(linea)) cout << "advertencia: no se pudo escribir transactions.txt\n";
    }
    else if (opcion == "cliente") {
        string ced, cla;
        cout << "escribe tu cedula: "; cin >> ced;
        cout << "escribe tu clave: "; cin >> cla;

        usuario u;
        if (!existe_usuario(ced, u)) {
            cout << "usuario no encontrado\n";
            return 0;
        }
        if (u.clave != cla) {
            cout << "clave incorrecta\n";
            return 0;
        }

        cout << "quieres consultar o retirar? "; string accion; cin >> accion;
        const long long FEE = 1000;

        if (accion == "consultar") {
            if (u.saldo < FEE) {
                cout << "saldo insuficiente para pagar la cuota (1000 COP)\n";
                return 0;
            }
            u.saldo -= FEE;
            if (!actualizar_saldo(u)) {
                cout << "error actualizando archivo usuarios\n";
                return 1;
            }
            cout << "tu saldo es: " << u.saldo << "\n";
            string linea = ahora() + " | " + u.cedula + " | CONSULTA | 0 | 1000 | " + to_string(u.saldo);
            log_transaccion(linea);
        }
        else if (accion == "retirar") {
            int monto; cout << "cuanto quieres retirar??: "; cin >> monto;
            if (monto <= 0) { cout << "monto invalido\n"; return 0; }
            long long total = monto + FEE;
            if (total > u.saldo) {
                cout << "saldo insuficiente\n";
                return 0;
            }
            u.saldo -= total;
            if (!actualizar_saldo(u)) { cout << "error actualizando archivo usuarios\n"; return 1; }
            cout << "Retiro exitoso\n";
            cout << "Nuevo saldo: " << u.saldo << "\n";

            string linea = ahora() + " | " + u.cedula + " | RETIRO | " + to_string(monto) + " | 1000 | " + to_string(u.saldo);
            log_transaccion(linea);
        }
        else {
            cout << "accion no valida\n";
        }
    }
    else {
        cout << "opcion no valida\n";
    }

    return 0;
}
