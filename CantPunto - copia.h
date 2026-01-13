#ifndef CANTPUNTO_H
#define CANTPUNTO_H
#include "Punto.h"
#include "ArbolAVL.h"
#include <string>

class CantPunto {
public:
	string nombre;
    ArbolAVL<Punto>* puntos;

    CantPunto();
    
    bool operator<(const CantPunto& otro) const {
        return this->nombre < otro.nombre;
    }
};

#endif // PUNTO_H
