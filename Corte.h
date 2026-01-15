#ifndef CORTE_H
#define CORTE_H

#include <string>
#include <iostream>
#include "ArbolAVL.h"
#include "Evaluacion.h"

class Corte {
public:
    std::string nombre;
    int porcentaje;
    ArbolAVL<Evaluacion>* evaluaciones;

    // Constructor principal
    Corte(const std::string& nombre, int porcentaje)
        : nombre(nombre), porcentaje(porcentaje), evaluaciones(new ArbolAVL<Evaluacion>()) {}

    // Constructor por defecto (si lo usas en algún lado)
    Corte() : nombre(""), porcentaje(0), evaluaciones(new ArbolAVL<Evaluacion>()) {}

    // Destructor
    ~Corte() { delete evaluaciones; }

    // Copy ctor
    Corte(const Corte& other)
        : nombre(other.nombre),
          porcentaje(other.porcentaje),
          evaluaciones(new ArbolAVL<Evaluacion>(*other.evaluaciones)) {}

    // Asignación
    Corte& operator=(const Corte& other) {
        if (this != &other) {
            delete evaluaciones;
            nombre = other.nombre;
            porcentaje = other.porcentaje;
            evaluaciones = new ArbolAVL<Evaluacion>(*other.evaluaciones);
        }
        return *this;
    }

    bool operator<(const Corte& otro) const { return nombre < otro.nombre; }
    bool operator>(const Corte& otro) const { return nombre > otro.nombre; }
    bool operator!=(const Corte& otro) const { return nombre != otro.nombre; }
    bool operator==(const Corte& otro) const { return nombre == otro.nombre; }

    void agregarEvaluacion(const std::string& nombreEvaluacion);
    void agregarPunto(const std::string& nombreEvaluacion, int porcentajePunto, int codigo_tema);
    void agregarNota(const std::string& nombreEvaluacion, int porcentajePunto, int codigo_tema,int IDEstudiante, double valor);
    void eliminarNota(const std::string& nombreEvaluacion, int porcentajePunto, int codigo_tema, int IDEstudiante);
    void eliminarEvaluacion(const std::string& nombreEvaluacion);
    void eliminarPunto(const std::string& nombreEvaluacion, int porcentajePunto, int codigo_tema);

    Evaluacion buscarEvaluacion(const std::string& nombreEvaluacion);
    Evaluacion* buscarEvaluaciones(const std::string& nombreEvaluacion);
    Punto* buscarPuntos(const std::string& nombreEvaluacion, int porcentajePunto, int codigo_tema);
    Nota* buscarNotas(const std::string& nombreEvaluacion, int porcentajePunto, int codigo_tema, int IDEstudiante);

    Punto buscarPunto(const std::string& nombreEvaluacion, int porcentajePunto, int codigo_tema);
    Nota buscarNota(const std::string& nombreEvaluacion, int porcentajePunto, int codigo_tema, int IDEstudiante);

    void listarEvaluaciones();
    void listarPuntos(const std::string& nombreEvaluacion);
    void listarNotas(const std::string& nombreEvaluacion, int porcentajePunto, int codigo_tema);

    friend std::ostream& operator<<(std::ostream& out, const Corte& c) {
        return out << "Nombre: " << c.nombre << ", Porcentaje: " << c.porcentaje << std::endl;
    }
};

#endif // CORTE_H
