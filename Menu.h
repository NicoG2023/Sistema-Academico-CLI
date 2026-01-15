#ifndef MENU_H
#define MENU_H

#include <iostream>
#include <string>

#ifdef _WIN32
  #include <windows.h>
#else
  #include <unistd.h>   // usleep
#endif

#include "GestorProfesores.h"
#include "GestorEstudiantes.h"
#include "GestorClases.h"
#include "GestorConsultas.h"
#include "GestorArchivos.h"

class Menu {
public:
    Menu(GestorProfesores& gp, GestorEstudiantes& ge, GestorClases& gc, GestorConsultas& gcs, GestorArchivos& ga);
    void mostrarMenuPrincipal();

private:
    void agregarProfesor();
    void agregarEstudiante();
    void agregarMateria();
    void generarReporteRefuerzos();

    void hacerConsultas();

    void consultaPromedioComportamientoEstudiante();
    void consultaComportamientoPromedioCurso();
    void consultaComportamientoPromedioProfesor();
    void consultaProfesoresPorNumeroClases();
    void consultaEstudiantesPorNota();

    void menuProfesor();

    void agregarCorte(Profesor &profesor);
    void agregarEvaluacion(Profesor &profesor);
    void agregarPunto(Profesor &profesor);
    void agregarNota(Profesor &profesor);
    void matricularEstudiante(Profesor &profesor);
    void vincularCorteMateria(Profesor &profesor);
    void modificarCorte(Profesor &profesor);
    void modificarEvaluacion(Profesor &profesor);
    void modificarPunto(Profesor &profesor);
    void cambiarEvaluacionCorte(Profesor &profesor);
    void generarArchivoParcial(Profesor &profesor);
    void subirParcial(Profesor &profesor);

    void mostrarMenu();

    void mostrarProfesores();
    void mostrarEstudiantes();
    void mostrarMateriasProfesor();
    void mostrarCortesProfesor();
    void mostrarEvaluacionesCorte();
    void mostrarPuntosEvaluacion();
    void mostrarNotasEvaluacion();
    void mostrarTemasMateria();

    GestorProfesores& gestorProfesores;
    GestorEstudiantes& gestorEstudiantes;
    GestorClases& gestorClases;
    GestorConsultas& gestorConsultas;
    GestorArchivos& gestorArchivos;
};

#endif // MENU_H
