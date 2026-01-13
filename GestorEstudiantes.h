#ifndef GESTORESTUDIANTES_H
#define GESTORESTUDIANTES_H

#include <iostream>
#include <string>
#include "ArbolAVL.h"
#include "Estudiante.h"

using namespace std;

class GestorEstudiantes {
public:
	
    GestorEstudiantes();
    ~GestorEstudiantes();

    void agregarEstudiante(int id, const string& nombre);
    void eliminarEstudiante(int id);
    bool estudianteExiste(int id);
    Estudiante buscarEstudiante(int id);
    void actualizarEstudiante(int id, const string& nuevoNombre);
    Estudiante* buscarEstudiantePorID(int IDEstudiante);
    Estudiante* buscarEstudiantePorElNombre(const string& nombre);

    void listarEstudiantes();
    
    const ArbolAVL<Estudiante>& getEstudiantes() const;

private:
    ArbolAVL<Estudiante> estudiantes;
};

#endif // GESTORESTUDIANTES_H

