#ifndef MATERIAS_H
#define MATERIAS_H

#include <iostream>
#include <string>
#include "ArbolAVL.h"
#include "ListaSimple.h"
#include "Temas.h"
#include "Archivos.h"
#include "Corte.h"
#include "Estudiante.h"
#include "GestorProfesores.h"
#include "GestorEstudiantes.h"
#include "pila.h"

using namespace std;

class Materias {
public:
    string materia;
    ArbolAVL<Temas> temas;
    ArbolAVL<Archivos> *archivos;
    ArbolAVL<string> cortes; //se enlaza los cortes que maneja la materia
    ArbolAVL<int> estudiantes; //se enlaza los estudiantes inscritos en la materia
    
    // Constructor de copia
    Materias(const Materias& other);
    Materias();

    // Operador de asignación
    Materias& operator=(const Materias& other);
    
    Materias(const string& materia);
    ~Materias();

    bool operator<(const Materias& otro) const {
        return materia < otro.materia;
    }

    bool operator>(const Materias& otro) const {
        return materia > otro.materia;
    }

    bool operator==(const Materias& otro) const {
        return materia == otro.materia;
    }

    bool operator!=(const Materias& otro) const {
        return materia != otro.materia;
    }

    void agregarTema(int codigo_tema, const string& tema);
    void agregarArchivo(const string& nombreArchivo);
    void agregarNota(const string& nombreCorte, const string& nombreEvaluacion, int porcentaje, int codigo_tema, int IDEstudiante, double valor, Profesor& profesor);
    void eliminarTema(int codigo_tema);
    void eliminarArchivo(const string& nombreArchivo);
    void vincularCorte(const string& nombreCorte, int profesorID, GestorProfesores& gestorProfesores);
    void desvincularCorte(const string& nombreCorte);
    string buscarCorte(const string& tipo_evaluacion);
    Estudiante buscarEstudiante(const string& nombreEstudiante);
    int calcularPorcentajeTotal();

    void matricularEstudiante(int IDEstudiante, GestorEstudiantes& gestorEstudiantes);
    void desmatricularEstudiante(int IDEstudiante);
    bool buscarEstudianteMatriculado(int IDEstudiante);

    void listarCortes();
    void listarEstudiantes();
    void listarTemas();
    
    double calcularPromedioEstudiante(int IDEstudiante, Profesor& profesor);
    void comportamientoEnTemas(int IDEstudiante, Profesor& profesor);
    void comportamientoGeneralEnTemas(Profesor& profesor);
    
    void generarArchivosParciales(GestorProfesores& gestorProfesores, int profesorID);
    void subirParcial(const string& filename, GestorEstudiantes& gestorEstudiantes, int profesorID, GestorProfesores& gestorProfesores);

    friend ostream& operator<<(ostream& out, const Materias& est) {
        return out << "Materia: " << est.materia << endl;
    }
};

#endif
