#ifndef GESTORARCHIVOS_H
#define GESTORARCHIVOS_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "GestorProfesores.h"
#include "GestorEstudiantes.h"
#include "GestorClases.h"
#include "ListaSimple.h"

using namespace std;

struct PromedioTema {
    std::string tema;
    double promedio;

    bool operator<(const PromedioTema& otro) const {
        return promedio < otro.promedio;
    }

    bool operator>(const PromedioTema& otro) const {
        return promedio > otro.promedio;
    }
};

class GestorArchivos {
	public:
	
		GestorArchivos(GestorProfesores& gp, GestorEstudiantes& ge, GestorClases& gc);
		
	    void guardarDatos(const string& archivo);
	    void cargarDatos(const string& archivo);
	    void generarReporteRefuerzo();
    private:
    	GestorProfesores& gestorProfesores;
    	GestorEstudiantes& gestorEstudiantes;
    	GestorClases& gestorClases;
};

#endif // GESTORARCHIVOS_H

