#ifndef GESTORPROFESORES_H
#define GESTORPROFESORES_H

#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <sstream>
#include "Profesor.h"
#include "ArbolAVL.h"

using namespace std;

class GestorProfesores {
	
	public:
		GestorProfesores();
		~GestorProfesores();
		
		ArbolAVL<Profesor> profesores;
		
		void agregarProfesor(int cedula, const string& nombre, const string& apellido, const string& email, const string& telefono, int clases_asignadas);
		void eliminarProfesor(int cedula);
		Profesor& buscarProfesor(int cedula);
		Profesor* buscarProfesores(int cedula);
		bool profesorExiste(int cedula);
		
		void guardar(const string& filename) const;
		void cargar(const string& filename);
		
		void subirNotas(const string& filename);
		
		
	private:
};

#endif
