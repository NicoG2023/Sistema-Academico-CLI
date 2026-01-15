#ifndef ARCHIVOS_H
#define ARCHIVOS_H

#include <iostream>
#include <string>
#include "ArbolAVL.h"

using namespace std;

class Archivos {
  public:
    
    string nombreArchivo;
    
    Archivos(const string& nombreArchivo);
    ~Archivos();
    
    bool operator==(const Archivos& otro) const {
        return nombreArchivo == nombreArchivo;
    }
    
    bool operator>(const Archivos& otro) const {
        return nombreArchivo > otro.nombreArchivo;
    }
    
    bool operator!=(const Archivos& otro) const {
        return nombreArchivo > otro.nombreArchivo;
    }
    friend ostream& operator<<(ostream& out, const Archivos& est){
          return out << "Nombre: " << est.nombreArchivo;
    }
    
};

#endif
