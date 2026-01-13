#ifndef CORTE_H
#define CORTE_H

#include "ArbolAVL.h"
#include "Evaluacion.h"
using namespace std;

class Corte {
public:
    string nombre;
    int porcentaje;
    ArbolAVL<Evaluacion> *evaluaciones;

    // Constructor
    Corte(const std::string& nombre, int porcentaje)
        : nombre(nombre), porcentaje(porcentaje), evaluaciones(new ArbolAVL<Evaluacion>()) {}
        
    Corte();

    // Destructor
    ~Corte() {
        delete evaluaciones;
    }

    // Constructor de copia
    Corte(const Corte& other)
        : nombre(other.nombre), porcentaje(other.porcentaje), evaluaciones(new ArbolAVL<Evaluacion>(*other.evaluaciones)) {}

    // Operador de asignación
    Corte& operator=(const Corte& other) {
        if (this != &other) {
            delete evaluaciones;
            nombre = other.nombre;
            porcentaje = other.porcentaje;
            evaluaciones = new ArbolAVL<Evaluacion>(*other.evaluaciones);
        }
        return *this;
    }

    bool operator<(const Corte& otro) const {
        return nombre < otro.nombre;
    }

    bool operator>(const Corte& otra) const {
        return nombre > otra.nombre;
    }

    bool operator!=(const Corte& otro) const {
        return nombre != otro.nombre;
    }

    bool operator==(const Corte& otro) const {
        return nombre == otro.nombre;
    }

    void agregarEvaluacion(const string& nombreEvaluacion);
    void agregarPunto(const string& nombreEvaluacion, int porcentajePunto, int codigo_tema);
    void agregarNota(const string& nombreEvaluacion, int porcentajePunto, int codigo_tema,int IDEstudiante, double valor);
    void eliminarNota(const string& nombreEvaluacion, int porcentajePunto, int codigo_tema, int IDEstudiante);
    void eliminarEvaluacion(const string& nombreEvaluacion);
    void eliminarPunto(const string& nombreEvaluacion, int porcentajePunto, int codigo_tema);
    Evaluacion buscarEvaluacion(const string& nombreEvaluacion);
    Evaluacion* buscarEvaluaciones(const string& nombreEvaluacion);
    Punto* buscarPuntos(const string& nombreEvaluacion, int porcentajePunto, int codigo_tema);
    Nota* buscarNotas(const string& nombreEvaluacion, int porcentajePunto, int codigo_tema, int IDEstudiante);
    Punto buscarPunto(const string& nombreEvaluacion, int porcentajePunto, int codigo_tema);
    Nota buscarNota(const string& nombreEvaluacion, int porcentajePunto, int codigo_tema, int IDEstudiante);
    
    void listarEvaluaciones();
    void listarPuntos(const string& nombreEvaluacion);
    void listarNotas(const string& nombreEvaluacion, int porcentajePunto, int codigo_tema);

    friend ostream& operator<<(ostream& out, const Corte& est) {
        return out << "Nombre: " << est.nombre << ", Porcentaje: " << est.porcentaje<<endl;
    }
};



#endif // CORTE_H

