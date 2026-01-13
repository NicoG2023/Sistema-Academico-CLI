#ifndef GESTORCLASES_H
#define GESTORCLASES_H

#include <iostream>
#include <string>
#include "ArbolAVL.h"
#include "ListaSimple.h"
#include "Clases.h"
#include "GestorProfesores.h"

using namespace std;

class GestorClases {
public:
    GestorClases(GestorProfesores& gestorProfesores);
    GestorClases();
    ~GestorClases();

    void agregarClase(int codigo_profesor);
    void agregarMateria(int codigo_profesor, const string& materia);
    NodoArbolAVL<Clases>* getRootClases() const;
    void eliminarClase(int codigo_profesor);
    void listarClases();
    Clases* buscarClases(int codigo_profesor);
    Temas* buscarTemaPorCodigo(int codigoTema);
    
    void consultarProfesoresPorNumeroClases(int numeroClases);//Consulta d.

    const ArbolAVL<Clases>& getClases() const;

private:
    ArbolAVL<Clases> clases;
    GestorProfesores& gestorProfesores;  // Referencia a GestorProfesores
};

inline bool compararPorCedula(const NodoProfesor& a, const NodoProfesor& b) {
    	return a.cedula < b.cedula;
}

#endif // GESTORCLASES_H

