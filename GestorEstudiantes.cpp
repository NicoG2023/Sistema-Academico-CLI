#include "GestorEstudiantes.h"
using namespace std;
GestorEstudiantes::GestorEstudiantes() {}

GestorEstudiantes::~GestorEstudiantes() {}

void GestorEstudiantes::agregarEstudiante(int id, const string& nombre) {
    Estudiante nuevoEstudiante(id, nombre);
    estudiantes.insert(nuevoEstudiante);
    cout<<"Estudiante " << nombre << " agregado correctamente." << endl;
}

void GestorEstudiantes::eliminarEstudiante(int id) {
    Estudiante est(id, "");
    estudiantes.erase(est);
}

bool GestorEstudiantes::estudianteExiste(int id) {
    return estudiantes.find(Estudiante(id, "")) != -1;
}

Estudiante GestorEstudiantes::buscarEstudiante(int id) {
    int idx = estudiantes.find(Estudiante(id, ""));
    if (idx == -1) {
        std::cout<<"Estudiante no encontrado"<<std::endl;
    }
    return estudiantes.obtainByReference(idx);
}

Estudiante* GestorEstudiantes::buscarEstudiantePorID(int IDEstudiante){
	int idx = estudiantes.find(Estudiante(IDEstudiante, "")); // Se asume que el constructor de Estudiante permite inicializar con nombre y ID
    if (idx == -1) {
        return NULL;
    }
    return &estudiantes.obtainByReference(idx);
}

Estudiante* GestorEstudiantes::buscarEstudiantePorElNombre(const std::string& nombre) {
    Estudiante temp(0, nombre); // Crear un estudiante temporal con el nombre limpio
    int idx = estudiantes.find(temp);
    if (idx == -1) {
        return NULL;
    }
    return &estudiantes.obtainByReference(idx);
}




void GestorEstudiantes::actualizarEstudiante(int id, const string& nuevoNombre) {
    Estudiante est = buscarEstudiante(id);
    estudiantes.erase(est);
    est.nombre = nuevoNombre;
    estudiantes.insert(est);
}

void GestorEstudiantes::listarEstudiantes() {
    estudiantes.display();
}

const ArbolAVL<Estudiante>& GestorEstudiantes::getEstudiantes() const{
	return estudiantes;
}

