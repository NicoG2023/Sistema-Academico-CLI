#ifndef PILA_H
#define PILA_H

#include "estructura.h"
#include <stdexcept>

// Implementación genérica de pila
template <typename T>
class pila {
    nodo<T> *cab; // Puntero a la cabecera de la pila
public:
    pila();
    void Push(T v);
    T Pop();
    bool PilaVacia() const;
    T Top() const; // Devuelve el elemento en la cima de la pila sin eliminarlo
    ~pila();
};

template <typename T>
pila<T>::pila() {
    cab = new nodo<T>;
    cab->sig = NULL;
}

template <typename T>
void pila<T>::Push(T v) {
    nodo<T> *t = new nodo<T>;
    t->dato = v;
    t->sig = cab->sig;
    cab->sig = t;
}

template <typename T>
T pila<T>::Pop() {
    if (PilaVacia()) {
        throw std::underflow_error("Pila vacía, no se puede hacer Pop.");
    }
    T x;
    nodo<T> *t = cab->sig;
    cab->sig = t->sig;
    x = t->dato;
    delete t;
    return x;
}

template <typename T>
T pila<T>::Top() const {
    if (PilaVacia()) {
        throw std::underflow_error("Pila vacía, no se puede acceder al Top.");
    }
    return cab->sig->dato; // Devuelve el valor sin eliminar
}

template <typename T>
bool pila<T>::PilaVacia() const {
    return cab->sig == NULL;
}

template <typename T>
pila<T>::~pila() {
    nodo<T> *t = cab;
    while (t != NULL) {
        cab = t;
        t = t->sig;
        delete cab;
    }
}

#endif // PILA_H
