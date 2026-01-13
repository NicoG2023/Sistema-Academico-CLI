#ifndef GESTORCONSULTAS_H
#define GESTORCONSULTAS_H

#include "GestorProfesores.h"
#include "GestorEstudiantes.h"
#include "GestorClases.h"
#include "ListaSimple.h"
#include "pila.h"
#include "NodoArbolAVL.h"
#include "Profesor.h"
#include "Clases.h"
#include "Materias.h"
#include "Temas.h"
#include "Corte.h"
#include "Evaluacion.h"
#include "Punto.h"
#include "Nota.h"
#include "Estudiante.h"

class GestorConsultas {
public:
    GestorConsultas(GestorProfesores& gestorProfesores, GestorEstudiantes& gestorEstudiantes, GestorClases& gestorClases);

    void consultaPromedioEstudiante(int IDEstudiante, const string& materia, Profesor& profesor);//CONSULTA a.
    void consultaComportamientoPromedioCurso(const string& materia);//Consulta b.
    void consultaComportamientoPromedioProfesor(int codigoProfesor);//CONSULTA c.
    void consultaProfesoresPorClases(int numeroClases);//Consulta d.
    void consultaEstudiantesPorNota(double notaDada, const string& tema);

private:
    GestorProfesores& gestorProfesores;
    GestorEstudiantes& gestorEstudiantes;
    GestorClases& gestorClases;
};

#endif // GESTORCONSULTAS_H

