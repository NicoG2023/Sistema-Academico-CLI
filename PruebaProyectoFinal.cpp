#include <iostream>
#include "GestorProfesores.h"
#include "GestorEstudiantes.h"
#include "GestorClases.h"
#include "GestorConsultas.h"
#include "GestorArchivos.h"
#include "Menu.h"
#include <locale>

using namespace std;

void configurarLocale() {
    std::setlocale(LC_ALL, "es_ES.UTF-8");
}

int main() {
	
	configurarLocale();
	
    GestorEstudiantes gestorEstudiantes;
    GestorProfesores gestorProfesores;
    GestorClases gestorClases(gestorProfesores);
    GestorConsultas gestorConsultas(gestorProfesores, gestorEstudiantes, gestorClases);
    GestorArchivos gestorArchivos(gestorProfesores, gestorEstudiantes, gestorClases);

    Menu menu(gestorProfesores, gestorEstudiantes, gestorClases, gestorConsultas, gestorArchivos);
    menu.mostrarMenuPrincipal();

    return 0;
}

