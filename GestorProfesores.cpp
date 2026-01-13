#include "GestorProfesores.h"

using namespace std;

GestorProfesores::GestorProfesores() {
}

GestorProfesores::~GestorProfesores() {
}


bool GestorProfesores::profesorExiste(int cedula) {
    return profesores.find(Profesor(cedula, "", "", "", "", 0)) != -1;
}

void GestorProfesores::agregarProfesor(int cedula, const string& nombre, const string& apellido, const string& email, const string& telefono, int clases_asignadas) {
    Profesor nuevoProfesor(cedula, nombre, apellido, email, telefono, clases_asignadas);
    profesores.insert(nuevoProfesor);
    std::cout << "Profesor: "<<nombre<< " agregado correctamente." << std::endl;
}



Profesor& GestorProfesores::buscarProfesor(int cedula) {
    int idx = profesores.find(Profesor(cedula, "", "", "", "", 0));
    if (idx == -1) {
        cout<<"Profesor no encontrado"<<endl;
    }
    return profesores.obtainByReference(idx);
}

Profesor* GestorProfesores::buscarProfesores(int cedula){
	int idx = profesores.find(Profesor(cedula, "", "", "", "", 0));
    if (idx == -1) {
        cout<<"Profesor no encontrado"<<endl;
    }
    return &profesores.obtainByReference(idx);
}

void GestorProfesores::eliminarProfesor(int cedula) {
    Profesor profesorAEliminar(cedula, "", "", "", "", 0);
    profesores.erase(profesorAEliminar);
}

//GUARDADO DE LAS ESTRUCTURAS

//CARGA DE DATOS


