#ifndef PROFESOR_H
#define PROFESOR_H

#include <iostream>
#include <string>
#include "Corte.h"
#include "ArbolAVL.h"
using namespace std;

class Profesor {
  public:
    int cedula;
    string nombre;
    string apellido;
    string email;
    string telefono;
    int clases_asignadas;
    ArbolAVL<Corte> cortes;
    
    Profesor(int cedula, const std::string& nombre, const std::string& apellido, const std::string& email, const std::string& telefono, int clases_asignadas);
    ~Profesor();
    
    bool operator==(const Profesor& otro) const {
        return cedula == otro.cedula;
    }
    
    bool operator>(const Profesor& otro) const {
        return cedula > otro.cedula;
    }
    
    bool operator!=(const Profesor& otro) const {
        return cedula > otro.cedula;
    }

    void agregarCorte(const string& tipo_evaluacion, int porcentaje);
    void eliminarCorte(const string& tipo_evaluacion);
    Corte* buscarCorte(const string& tipo_evaluacion);
    
    bool modificarCorte(const string& nombreCorte, int nuevoPorcentaje, const string& nuevoNombreCorte);
    bool modificarEvaluacion(const string& nombreCorte, const string& nombreEvaluacion, const string& nuevoNombreEvaluacion);
    bool modificarPunto(const string& nombreCorte, const string& nombreEvaluacion, int porcentajePunto, int codigo_tema, int nuevoPorcentaje, int nuevoCodigoTema);
    bool cambiarEvaluacionDeCorte(const string& nombreEvaluacion, const string& nombreCorteOrigen, const string& nombreCorteDestino);
    
    friend ostream& operator<<(ostream& out, const Profesor& est){
          return out << "Nombre: " << est.nombre << " Apellido: " << est.apellido << " Cedula: " << est.cedula << " Email: "<<est.email<<" Clases Asignadas: "<<est.clases_asignadas<<endl;
    }
};

#endif // PROFESOR_H
