#ifndef EVALUACION_H
#define EVALUACION_H

#include "ArbolAVL.h"
#include "Punto.h"
#include <string>

class Evaluacion {
public:
    std::string nombre;
    ArbolAVL<Punto> *puntos; // Árbol AVL para manejar los puntos

    Evaluacion(const std::string& nombre);
    Evaluacion();
    ~Evaluacion();
    
    // Constructor de copia
    Evaluacion(const Evaluacion& other);

    // Operador de asignación
    Evaluacion& operator=(const Evaluacion& other);

    bool operator<(const Evaluacion& otra) const {
        return nombre < otra.nombre;
    }

    bool operator>(const Evaluacion& otra) const {
        return nombre > otra.nombre;
    }

    bool operator!=(const Evaluacion& otra) const {
        return nombre != otra.nombre;
    }

    bool operator==(const Evaluacion& otro) const {
        return nombre == otro.nombre;
    }
    
    void agregarPunto(int porcentajePunto, int codigo_tema);
    void eliminarPunto(int porcentajePunto, int codigo_tema);

    friend ostream& operator<<(ostream& out, const Evaluacion& est) {
        return out << "Nombre: " << est.nombre;
    }
};

#endif // EVALUACION_H

