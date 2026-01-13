#ifndef PUNTO_H
#define PUNTO_H

#include "ArbolAVL.h"
#include "Nota.h"
#include <iostream>
using namespace std;

class Punto {
public:
    int porcentaje;
    int codigo_tema;
    ArbolAVL<Nota> *notas;

    Punto(int porcentaje, int codigo_tema);
    Punto();
    ~Punto();

    // Define el operador de comparación usando ambos atributos
    bool operator<(const Punto& otro) const {
        return porcentaje < otro.porcentaje && codigo_tema < otro.codigo_tema;
    }

    bool operator==(const Punto& otro) const {
        return porcentaje == otro.porcentaje && codigo_tema == otro.codigo_tema;
    }

    bool operator>(const Punto& otro) const {
        return porcentaje > otro.porcentaje && codigo_tema > otro.codigo_tema;
    }

    bool operator!=(const Punto& otro) const {
        return porcentaje > otro.porcentaje && codigo_tema != otro.codigo_tema;
    }

    void agregarNota(int IDEstudiante, double valor);
    void eliminarNota(int IDEstudiante);
    Nota* buscarNota(int IDEstudiante);

    friend ostream& operator<<(ostream& out, const Punto& est) {
        return out << "Codigo Tema: " << est.codigo_tema << " Porcentaje: " << est.porcentaje;
    }
};



#endif // PUNTO_H

