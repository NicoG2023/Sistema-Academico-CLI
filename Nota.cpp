#include "Nota.h"

Nota::Nota(){
}

Nota::~Nota() {}

Nota::Nota(const Nota& other):IDEstudiante(other.IDEstudiante), valor(other.valor){
}

Nota& Nota::operator=(const Nota& other){
	if(this != &other){
		IDEstudiante = other.IDEstudiante;
		valor = other.valor;
	}
	return *this;
}
