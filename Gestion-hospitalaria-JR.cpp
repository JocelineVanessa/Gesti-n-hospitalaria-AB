﻿#include <iostream> 
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <ctime>

using namespace std;

enum PermisoIndex {
    CREAR_PACIENTE = 0,
    MODIFICAR_PACIENTE,
    ELIMINAR_PACIENTE,
    CREAR_MEDICO,
    ELIMINAR_MEDICO,
    MODIFICAR_MEDICO,
    CREAR_CITA,
    MODIFICAR_CITA,
    ELIMINAR_CITA,
    VER_CITAS,
    HISTORIAL_PACIENTE,
    MODIFICAR_HISTORIAL_PACIENTE,
    TOTAL_PERMISOS
};

class Usuario {
private:
    string nombreUsuario;
    string contraseña;
    string rol;
    vector<bool> permisos;

    void AsignarPermisosPorRol() {
        permisos.assign(TOTAL_PERMISOS, false);

        if (rol == "ADMINISTRADOR") {
            permisos[CREAR_PACIENTE] = true;
            permisos[MODIFICAR_PACIENTE] = true;
            permisos[ELIMINAR_PACIENTE] = true;
            permisos[CREAR_MEDICO] = true;
            permisos[ELIMINAR_MEDICO] = true;
            permisos[MODIFICAR_MEDICO] = true;
            permisos[CREAR_CITA] = true;
            permisos[MODIFICAR_CITA] = true;
            permisos[ELIMINAR_CITA] = true;
        }
        else if (rol == "MEDICO") {
            permisos[VER_CITAS] = true;
            permisos[HISTORIAL_PACIENTE] = true;
            permisos[MODIFICAR_HISTORIAL_PACIENTE] = true;
        }
        else if (rol == "RECEPCIONISTA") {
            permisos[CREAR_PACIENTE] = true;
            permisos[MODIFICAR_PACIENTE] = true;
            permisos[CREAR_CITA] = true;
            permisos[MODIFICAR_CITA] = true;
            permisos[ELIMINAR_CITA] = true;
            permisos[VER_CITAS] = true;
        }
    }

public:
    Usuario(string nombreUsuario, string contraseña, string rol)
        : nombreUsuario(nombreUsuario), contraseña(contraseña), rol(rol), permisos(TOTAL_PERMISOS, false) {
        AsignarPermisosPorRol();
    }

    string getNombreUsuario() const { return nombreUsuario; }
    string getRol() const { return rol; }
    const vector<bool>& getPermisos() const { return permisos; }

    bool VerificarPermiso(PermisoIndex permiso) const { return permiso < permisos.size() && permisos[permiso]; }
    bool ValidarContraseña(const string& inputContraseña) const { return inputContraseña == contraseña; }

    static void GuardarUsuarios(const vector<Usuario>& usuarios, const string& archivo) {
        ofstream file(archivo);
        if (file.is_open()) {
            for (const auto& usuario : usuarios) {
                file << usuario.nombreUsuario << "," << usuario.contraseña << "," << usuario.rol << "\n";
            }
            file.close();
        }
        else {
            cerr << "Error al abrir el archivo para guardar.\n";
        }
    }

    static void CargarUsuarios(vector<Usuario>& usuarios, const string& archivo) {
        ifstream file(archivo);
        if (file.is_open()) {
            string linea;
            while (getline(file, linea)) {
                if (linea.empty()) continue;
                stringstream ss(linea);
                string nombreUsuario, contraseña, rol;
                getline(ss, nombreUsuario, ',');
                getline(ss, contraseña, ',');
                getline(ss, rol, ',');
                usuarios.push_back(Usuario(nombreUsuario, contraseña, rol));
            }
            file.close();
        }
        else {
            cerr << "Archivo no encontrado, se creara uno nuevo al guardar.\n";
        }
    }

    static bool CrearUsuario(vector<Usuario>& usuarios) {
        string nombre, contraseña, rol;
        cout << "Ingrese el nombre del nuevo usuario: ";
        cin >> nombre;
        cout << "Ingrese la contraseña: ";
        cin >> contraseña;
        cout << "Ingrese el rol (ADMINISTRADOR, RECEPCIONISTA, MEDICO): ";
        cin >> rol;

        if (rol != "ADMINISTRADOR" && rol != "RECEPCIONISTA" && rol != "MEDICO") {
            cout << "Rol no valido. Usuario no creado.\n";
            return false;
        }
        usuarios.push_back(Usuario(nombre, contraseña, rol));
        return true;
    }

    static void CrearMedico() {
        ofstream file("medicos.csv", ios::app);
        if (!file.is_open()) {
            cerr << "Error al abrir el archivo para guardar el medico.\n";
            return;
        }

        string nombre, apellido, dni, correo, telefono, especialidad;
        int diaNacimiento, mesNacimiento, añoNacimiento;

        cout << "Ingrese el nombre del medico: ";
        cin >> nombre;
        cout << "Ingrese el apellido del medico: ";
        cin >> apellido;
        cout << "Ingrese el DNI del medico: ";
        cin >> dni;
        cout << "Ingrese el correo del medico: ";
        cin >> correo;
        cout << "Ingrese el telefono del medico: ";
        cin >> telefono;
        cout << "Ingrese el dia de nacimiento del medico: ";
        cin >> diaNacimiento;
        cout << "Ingrese el mes de nacimiento del medico: ";
        cin >> mesNacimiento;
        cout << "Ingrese el anio de nacimiento del medico: ";
        cin >> añoNacimiento;
        cout << "Ingrese la especialidad del medico: ";
        cin >> especialidad;

        time_t t = time(0);
        tm* now = localtime(&t);
        int añoActual = now->tm_year + 1900;
        int mesActual = now->tm_mon + 1;
        int diaActual = now->tm_mday;

        int edad = añoActual - añoNacimiento;
        if (mesActual < mesNacimiento || (mesActual == mesNacimiento && diaActual < diaNacimiento)) {
            edad--;
        }

        file << nombre << "," << apellido << "," << dni << "," << correo << "," << telefono << "," << añoNacimiento << "," << edad << "," << especialidad << "\n";
        file.close();

        cout << "Medico creado exitosamente:\n";
        cout << "Nombre: " << nombre << " " << apellido << "\n";
        cout << "DNI: " << dni << "\n";
        cout << "Correo: " << correo << "\n";
        cout << "Telefono: " << telefono << "\n";
        cout << "Fecha de nacimiento: " << diaNacimiento << "/" << mesNacimiento << "/" << añoNacimiento << "\n";
        cout << "Edad: " << edad << "\n";
        cout << "Especialidad: " << especialidad << "\n";
    }

    static void EliminarMedico() {
        string dni;
        cout << "Ingrese el DNI del medico a eliminar: ";
        cin >> dni;

        ifstream inputFile("medicos.csv");
        ofstream tempFile("temp.csv");

        if (inputFile.is_open() && tempFile.is_open()) {
            string linea;
            bool encontrado = false;
            while (getline(inputFile, linea)) {
                if (linea.find(dni) == string::npos) {
                    tempFile << linea << "\n";
                }
                else {
                    encontrado = true;
                }
            }
            inputFile.close();
            tempFile.close();

            remove("medicos.csv");
            rename("temp.csv", "medicos.csv");

            if (encontrado) {
                cout << "Medico eliminado exitosamente.\n";
            }
            else {
                cout << "Medico no encontrado.\n";
            }
        }
        else {
            cerr << "Error al abrir el archivo para eliminar el medico.\n";
        }
    }

    static void MostrarMedicos() {
        ifstream file("medicos.csv");
        if (file.is_open()) {
            string linea;
            cout << "Lista de medicos:\n";
            cout << "--------------------------------------------------\n";
            while (getline(file, linea)) {
                if (!linea.empty()) {
                    cout << linea << "\n";
                }
            }
            cout << "--------------------------------------------------\n";
            file.close();
        }
        else {
            cerr << "Archivo de medicos no encontrado.\n";
        }
    }

    static void MostrarUsuarios(const vector<Usuario>& usuarios) {
        cout << "Lista de usuarios y permisos:\n";
        cout << "--------------------------------------------------\n";
        cout << "Nombre de Usuario\tRol\tPermisos\n";
        cout << "--------------------------------------------------\n";
        for (const auto& usuario : usuarios) {
            cout << usuario.getNombreUsuario() << "\t\t" << usuario.getRol() << "\t";

            const vector<bool>& permisos = usuario.getPermisos();
            cout << "[ ";
            for (size_t i = 0; i < permisos.size(); ++i) {
                cout << (permisos[i] ? "Si" : "No") << (i < permisos.size() - 1 ? ", " : " ");
            }
            cout << "]\n";
        }
        cout << "--------------------------------------------------\n";
    }
};

bool IniciarSesion(const string& nombreUsuario, const string& contraseña, const vector<Usuario>& usuarios, Usuario& usuarioAutenticado) {
    for (const auto& usuario : usuarios) {
        if (usuario.getNombreUsuario() == nombreUsuario && usuario.ValidarContraseña(contraseña)) {
            usuarioAutenticado = usuario;
            return true;
        }
    }
    return false;
}

int main() {
    cout << "Bienvenido\n";
    vector<Usuario> usuarios;
    const string archivoUsuarios = "usuarios.csv";

    Usuario::CargarUsuarios(usuarios, archivoUsuarios);

    if (usuarios.empty()) {
        cout << "No se encontraron usuarios. Creando usuario administrador...\n";
        usuarios.push_back(Usuario("JocelineRamirez", "1234", "ADMINISTRADOR"));
        Usuario::GuardarUsuarios(usuarios, archivoUsuarios);
        cout << "Usuario administrador creado con exito\n";
    }

    string nombreUsuario, contraseña;
    cout << "Ingrese el nombre de usuario: ";
    cin >> nombreUsuario;
    cout << "Ingrese la contraseña: ";
    cin >> contraseña;

    Usuario usuarioAutenticado("", "", "");
    if (IniciarSesion(nombreUsuario, contraseña, usuarios, usuarioAutenticado)) {
        cout << "Inicio de sesion exitoso como " << usuarioAutenticado.getRol() << ".\n";

        if (usuarioAutenticado.getRol() == "ADMINISTRADOR") {
            char opcion;
            bool salir = false;

            while (!salir) {
                cout << "Opciones:\n";
                cout << "1. Crear nuevo usuario\n";
                cout << "2. Mostrar lista de usuarios\n";
                cout << "3. Crear medico\n";
                cout << "4. Mostrar lista de medicos\n";
                cout << "5. Guardar y salir\n";
                cout << "6. Eliminar medico\n"; 
                cout << "Ingrese su opcion: ";
                cin >> opcion;

                if (opcion == '1') {
                    if (Usuario::CrearUsuario(usuarios)) {
                        cout << "Usuario creado exitosamente\n";
                    }
                }
                else if (opcion == '2') {
                    Usuario::MostrarUsuarios(usuarios);
                }
                else if (opcion == '3') {
                    Usuario::CrearMedico();
                }
                else if (opcion == '4') {
                    Usuario::MostrarMedicos();
                }
                else if (opcion == '5') {
                    Usuario::GuardarUsuarios(usuarios, archivoUsuarios);
                    cout << "Usuarios guardados con exito\n";
                    salir = true;
                }
                else if (opcion == '6') {
                    Usuario::EliminarMedico();
                }
                else {
                    cout << "Opcion no valida.\n";
                }
              
            } 
        }
        else {
            cout << "No tiene permisos para realizar esta accion.\n";
        }
    }
    else {
        cout << "Usuario o contraseña incorrectos.\n";
    }

    return 0;
}
