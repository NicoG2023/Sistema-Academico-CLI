#ifndef LISTADOBLEENLACEORDENADA_H
#define LISTADOBLEENLACEORDENADA_H
#include <string>
#include <iostream>
#include <cmath>

using namespace std;

template <class T>
struct nodo{
	T info; 
	nodo<T> *sig, *ant;
};


template <class T>
class ListaDoble{ 
	private:
		nodo<T> *cabecera, *centinela;		
		int Tam;	
	
	public: ListaDoble(){
		cabecera = new nodo<T>;
		centinela = new nodo<T>;
		
		cabecera->ant = NULL;
		cabecera->sig=centinela;
		
		centinela->sig = NULL;
		centinela->ant=cabecera;
		Tam=0;
	}	 
	~ListaDoble() {
        // Destruir todos los nodos y liberar memoria
        nodo<T> *p = cabecera->sig;
        while (p != centinela) {
            nodo<T> *temp = p;
            p = p->sig;
            delete temp;
        }

        // Liberar cabecera y centinela
        delete cabecera;
        delete centinela;
    }			
	void insertar_dato(T info);			
	T Buscar(T info);
	nodo<T>* getFirst() {
        return cabecera->sig; // Devuelve el primer nodo
	}
	nodo<T>* getLast() {
    return centinela->ant; // Devuelve el último nodo
	}
	nodo<T>* getSentinel() {
        return centinela; // Devuelve el centinela
    }
	bool Lista_Vacia();
	bool Eliminar(T info);
	void imprimirDatos();
	T BuscarPorNombre(const string& nombre);
	int getTam() {
		return Tam;
	}
};

template <class T>
T ListaDoble<T>::BuscarPorNombre(const string& nombre) {
    nodo<T>* p = cabecera->sig;
    while (p != centinela) {
        if (p->info->nombre == nombre) {
            return p->info;
        }
        p = p->sig;
    }
    return NULL;
}


template <class T>
void ListaDoble<T>::imprimirDatos() {
    nodo<T> *p = cabecera -> sig;
    while(p != centinela){
        cout << p->info << ": " << p->info_adicional << endl;
        p = p -> sig;
    }
}

template <class T>
void ListaDoble<T>::insertar_dato(T info){

     nodo<T> *nuevo = new nodo<T>;
     nuevo -> info = info;
     nodo <T> *p = cabecera -> sig;
	 Tam++;

    while (p != centinela && info > p->info) {
        p = p->sig;
    }
	
	nuevo->ant = p->ant;
    nuevo->sig = p;
    p->ant->sig = nuevo;
    p->ant = nuevo;
	
 	 
}


template <class T>
bool ListaDoble<T>::Lista_Vacia(){//BIEN
	return cabecera->sig == centinela;
}

template <class T>
bool ListaDoble<T>::Eliminar(T info){//BIEN
	
	nodo<T> *p = cabecera -> sig;	
		
	while(p != centinela && p->info != info){
				p = p -> sig;
	}
	
	if(p != centinela && p->info == info){
		p -> ant -> sig = p -> sig;
		p -> sig -> ant = p -> ant;
		delete p;
		Tam --;
		return true;	
	}
	return false;		
	
}

template <class T>
T ListaDoble<T>::Buscar(T info) {
    if (Lista_Vacia()) {
        return NULL;
    }

    nodo<T> *p = cabecera->sig;
    while (p != centinela && p->info != info) {
        p = p->sig;
    }

    if (p != centinela) {
        return p->info;
    }

    return NULL;
}


#endif
