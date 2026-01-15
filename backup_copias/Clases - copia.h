#ifndef CLASES_H
#define CLASES_H

#include <iostream>
#include <string>
#include "ArbolAVL.h"
#include "Materias.h"

using namespace std;

class Clases {
public:
    int codigo_profesor;
    ArbolAVL<Materias> *clasesProfesor;
    
    Clases(int codigo_profesor);
    Clases();
    ~Clases();
    
    // Constructor de copia
    Clases(const Clases& other);

    // Operador de asignación
    Clases& operator=(const Clases& other);
    
    bool operator==(const Clases& otro) const {
        return codigo_profesor == otro.codigo_profesor;
    }
    
    bool operator>(const Clases& otro) const {
        return codigo_profesor > otro.codigo_profesor;
    }
    
    bool operator!=(const Clases& otro) const {
        return codigo_profesor != otro.codigo_profesor;
    }
    
    void eliminarMateria(const string& materia);
    Materias buscarMateria(const string& materia);
    void listarMaterias();
    Materias* buscarMaterias(const string& materia);
    
    void comportamientoPromedioPorTemas(GestorProfesores& gestorProfesores);
	    
    friend ostream& operator<<(ostream& out, const Clases& est) {
        return out << "codigo profesor: " << est.codigo_profesor;
    }
private:
	NodoArbolAVL<Materias>* findNodo(const std::string& materia);
};

#endif // CLASES_H

