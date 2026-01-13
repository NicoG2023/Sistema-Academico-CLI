#ifndef ESTRUCTURA_H     
#define ESTRUCTURA_H 

//Nicolás Guevara Herrán
//Juan Manuel Serrano

template <typename T>
struct nodo {
    T dato;
    nodo<T>* sig;
};

#endif

