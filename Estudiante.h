#ifndef ESTUDIANTE_H
#define ESTUDIANTE_H

#include <iostream>
#include <string>
#include "ArbolAVL.h"
#include "Nota.h"

using namespace std;

class Estudiante {
public:
    int IDEstudiante;
    string nombre;

    Estudiante(int IDEstudiante, const string& nombre) : IDEstudiante(IDEstudiante), nombre(nombre) {}

    bool operator<(const Estudiante& otro) const {
        if (IDEstudiante == 0 || otro.IDEstudiante == 0) {
            return nombre < otro.nombre;
        }
        return IDEstudiante < otro.IDEstudiante;
    }

    bool operator>(const Estudiante& otro) const {
        if (IDEstudiante == 0 || otro.IDEstudiante == 0) {
            return nombre > otro.nombre;
        }
        return IDEstudiante > otro.IDEstudiante;
    }

    bool operator==(const Estudiante& otro) const {
        if (IDEstudiante == 0 || otro.IDEstudiante == 0) {
            return nombre == otro.nombre;
        }
        return IDEstudiante == otro.IDEstudiante;
    }

    bool operator!=(const Estudiante& otro) const {
        if (IDEstudiante == 0 || otro.IDEstudiante == 0) {
            return nombre != otro.nombre;
        }
        return IDEstudiante != otro.IDEstudiante;
    }

    friend std::ostream& operator<<(std::ostream& out, const Estudiante& est) {
        return out << "Estudiante [Nombre: " << est.nombre << ", ID: " << est.IDEstudiante << "]"<<endl;
    }
};

#endif // ESTUDIANTE_H

