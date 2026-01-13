#include "Evaluacion.h"
#include "ArbolAVL.h"

Evaluacion::Evaluacion(const std::string& nombre)
    : nombre(nombre) {
    puntos = new ArbolAVL<Punto>();
}

// Constructor de copia
Evaluacion::Evaluacion(const Evaluacion& other)
    : nombre(other.nombre), puntos(new ArbolAVL<Punto>(*other.puntos)) {}

// Operador de asignación
Evaluacion& Evaluacion::operator=(const Evaluacion& other) {
    if (this != &other) {
        delete puntos; // Liberar la memoria existente
        nombre = other.nombre;
        puntos = new ArbolAVL<Punto>(*other.puntos); // Copiar el árbol AVL
    }
    return *this;
}

Evaluacion::Evaluacion() {
    puntos = new ArbolAVL<Punto>();
}

Evaluacion::~Evaluacion() {
    delete puntos;
}

void Evaluacion::agregarPunto(int porcentajePunto, int codigo_tema) {
    puntos->insert(Punto(porcentajePunto, codigo_tema));
}

void Evaluacion::eliminarPunto(int porcentajePunto, int codigo_tema) {
    puntos->erase(Punto(porcentajePunto, codigo_tema));
}



