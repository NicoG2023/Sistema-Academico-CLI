#ifndef NODOARBOLAVL_H
#define NODOARBOLAVL_H

#include <iostream>
#include <algorithm>

template <class T>
struct NodoArbolAVL {
    NodoArbolAVL *left;
    NodoArbolAVL *right;
    
    T value;
    int count;  // Número de nodos en este subárbol
    int height;
    
    NodoArbolAVL(T value);
    ~NodoArbolAVL();
    void updateValues();
    void updateValuesOther();
    int balanceFactor();
    int balanceFactorOther();
    
    
    NodoArbolAVL* left_rotate();
    NodoArbolAVL* right_rotate();
};

template <class T>
NodoArbolAVL<T>::NodoArbolAVL(T value)
    : left(NULL), right(NULL), value(value), count(1), height(1) {}

template <class T>
NodoArbolAVL<T>::~NodoArbolAVL() {
    if (left) {
        delete left;
        left = NULL;
    }
    if (right) {
        delete right;
        right = NULL;
    }
    /*std::cout << "Destruyendo nodo con valor: " << value << std::endl;
    std::cout << "left: " << left << std::endl;
    std::cout << "right: " << right << std::endl;*/
}

template <class T>
void NodoArbolAVL<T>::updateValues() {
    count = (left ? left->count : 0) + (right ? right->count : 0) + 1;
    height = std::max(left ? left->height : 0, right ? right->height : 0) + 1;
}

template <class T>
void NodoArbolAVL<T>::updateValuesOther() {
    count = (left != NULL ? left->count : 0) + (right != NULL ? right->count : 0) + 1;
    height = std::max(left != NULL ? left->height : 0, right != NULL ? right->height : 0) + 1;
}

template <class T>
int NodoArbolAVL<T>::balanceFactor() {
    return (left ? left->height : 0) - (right ? right->height : 0);
}

template <class T>
int NodoArbolAVL<T>::balanceFactorOther() {
    return (left != NULL ? left->height : 0) - (right != NULL ? right->height : 0);
}

template <class T>
NodoArbolAVL<T>* NodoArbolAVL<T>::left_rotate() {
    NodoArbolAVL* R = right;
    right = right->left;
    R->left = this;
    
    this->updateValues();  // El orden es importante
    R->updateValues();
    
    return R;
}

template <class T>
NodoArbolAVL<T>* NodoArbolAVL<T>::right_rotate() {
    NodoArbolAVL* L = left;
    left = left->right;
    L->right = this;
    
    this->updateValues();  // El orden es importante
    L->updateValues();
    
    return L;
}

#endif // NODOARBOLAVL_H

