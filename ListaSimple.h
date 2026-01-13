#ifndef LISTASIMPLE_H
#define LISTASIMPLE_H

#include <iostream>

using namespace std;

struct InformacionNota {
    int idEstudiante;
    std::string nombreEstudiante;
    std::string nombreEvaluacion;
    int porcentaje;
    int codigoTema;
    double valorNota;

    InformacionNota() : idEstudiante(0), nombreEstudiante(""), nombreEvaluacion(""), porcentaje(0), codigoTema(0), valorNota(0.0) {}

    InformacionNota(int id, const std::string& nombre, const std::string& eval, int porcentaje, int tema, double valor)
        : idEstudiante(id), nombreEstudiante(nombre), nombreEvaluacion(eval), porcentaje(porcentaje), codigoTema(tema), valorNota(valor) {}
};


struct NodoProfesor {
    int cedula;
    int contadorClases;
    
    NodoProfesor(int ced = 0, int cont = 0) : cedula(ced), contadorClases(cont) {}

    bool operator<(const NodoProfesor& otro) const {
        return cedula < otro.cedula;
    }

    bool operator>(const NodoProfesor& otro) const {
        return cedula > otro.cedula;
    }
};

template <class T>
struct nodoSimple {
    T Dato;
    nodoSimple<T> *sig;
};

template <class T>
class Lista {
private:
    nodoSimple<T> *cab;
    int Tam;    

    // Métodos auxiliares para quicksort
    int partition(int low, int high, bool (*compare)(const T&, const T&));
    void quickSort(int low, int high, bool (*compare)(const T&, const T&));

public:
    Lista() {
        cab = NULL;
        Tam = 0;
    }

    void insertar_final(T info);
    void insertar_inicio(T info);
    T borrar_nodo(int pos);
    T buscar_nodo(int pos);
    T& buscar_nodoByReference(int pos);
    bool lista_vacia();
    void imprimirLista();
    int getTam() const {
        return Tam;
    }

    // Método de ordenación
    void quickSort(bool (*compare)(const T&, const T&));
};

template <class T>
T& Lista<T>::buscar_nodoByReference(int pos) {
    if (pos < 1 || pos > Tam) {
        cerr << "Posición inválida" << endl;
        std::cout<<"Posición inválida en buscar_nodo";
    }

    nodoSimple<T> *aux = cab;

    for (int i = 1; i < pos; i++) {
        aux = aux->sig;
    }
    return aux->Dato;
}

template <class T>
void Lista<T>::imprimirLista() {
    nodoSimple <T> *aux = cab;

    while (aux != NULL) {
        cout << aux->Dato << " ";
        aux = aux->sig;
    }
    cout << endl;
}

template <class T>
bool Lista<T>::lista_vacia() {
    return cab == NULL;
}

template <class T>
void Lista<T>::insertar_final(T info) {
    nodoSimple<T> *nuevo, *aux;
    nuevo = new nodoSimple <T>;
    nuevo->Dato = info;
    nuevo->sig = NULL;
    if (lista_vacia()) {
        cab = nuevo;
    } else {
        aux = cab;
        while (aux->sig != NULL)
            aux = aux->sig;
        aux->sig = nuevo;
    }
    Tam++;
}

template <class T>
void Lista<T>::insertar_inicio(T info) {
    nodoSimple<T> *aux = new nodoSimple<T>;
    aux->sig = cab;
    aux->Dato = info;
    cab = aux;
    Tam++;
}

template <class T>
T Lista<T>::borrar_nodo(int pos) {
    if (pos < 1 || pos > Tam) {
        cerr << "Posicion invalida" << endl;
        return T();  // Return default T
    }
    nodoSimple<T> *aux = cab;
    nodoSimple<T> *anterior = NULL;

    if (pos == 1) {
        cab = aux->sig;
        T dato = aux->Dato;
        delete aux;
        Tam--;
        return dato;
    }
    for (int i = 1; i < pos; i++) {
        anterior = aux;
        aux = aux->sig;
    }

    anterior->sig = aux->sig;
    T dato = aux->Dato;
    delete aux;
    Tam--;
    return dato;
}

template <class T>
T Lista<T>::buscar_nodo(int pos) {
    if (pos < 1 || pos > Tam) {
        cerr << "Posición inválida" << endl;
        return T();  // Return default T
    }

    nodoSimple<T> *aux = cab;

    for (int i = 1; i < pos; i++) {
        aux = aux->sig;
    }
    return aux->Dato;
}

// Métodos auxiliares para quicksort
template <class T>
int Lista<T>::partition(int low, int high, bool (*compare)(const T&, const T&)) {
    T pivot = buscar_nodo(high);
    int i = low - 1;
    for (int j = low; j < high; j++) {
        if (compare(buscar_nodo(j), pivot)) {
            i++;
            T temp = buscar_nodo(i);
            borrar_nodo(i);
            insertar_inicio(buscar_nodo(j));
            borrar_nodo(j + 1);
            insertar_inicio(temp);
        }
    }
    T temp = buscar_nodo(i + 1);
    borrar_nodo(i + 1);
    insertar_inicio(buscar_nodo(high));
    borrar_nodo(high + 1);
    insertar_inicio(temp);
    return i + 1;
}

template <class T>
void Lista<T>::quickSort(int low, int high, bool (*compare)(const T&, const T&)) {
    if (low < high) {
        int pi = partition(low, high, compare);
        quickSort(low, pi - 1, compare);
        quickSort(pi + 1, high, compare);
    }
}

template <class T>
void Lista<T>::quickSort(bool (*compare)(const T&, const T&)) {
    quickSort(1, getTam(), compare);
}

#endif

