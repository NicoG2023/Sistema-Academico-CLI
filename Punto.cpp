#include "Punto.h"
using namespace std;

Punto::Punto()
    : porcentaje(0), codigo_tema(0), notas(new ArbolAVL<Nota>()) {}

Punto::Punto(int porcentaje, int codigo_tema)
    : porcentaje(porcentaje), codigo_tema(codigo_tema), notas(new ArbolAVL<Nota>()) {}

Punto::~Punto() {}

void Punto::agregarNota(int IDEstudiante, double valor){
	notas->insert(Nota(valor,IDEstudiante));
	cout<<"Nota agregada exitosamente"<<endl;
}

void Punto::eliminarNota(int IDEstudiante){
	Nota notaAEliminar(0.0, IDEstudiante);
    notas->erase(notaAEliminar);
}

Nota* Punto::buscarNota(int IDEstudiante) {
    int idx = notas->find(Nota(0.0, IDEstudiante));
    if (idx == -1) {
        return NULL;
    }
    return &notas->obtainByReference(idx);
}
