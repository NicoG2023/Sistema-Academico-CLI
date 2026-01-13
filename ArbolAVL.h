// ArbolAVL.h

#ifndef ARBOLAVL_H
#define ARBOLAVL_H

#include <iostream>
#include "NodoArbolAVL.h"
#include "pila.h"

template <class T>
class ArbolAVL {
    unsigned int _size;
    NodoArbolAVL<T> *root;

    void balance(NodoArbolAVL<T> **path[], int path_length);
    void balanceOther(NodoArbolAVL<T> **path[], int path_length);
    void display(NodoArbolAVL<T>* cur, int depth = 0, int state = 0);

    // Función auxiliar para hacer una copia profunda de los nodos
    NodoArbolAVL<T>* copiarNodo(const NodoArbolAVL<T>* nodo);

public:
    ArbolAVL();
    ArbolAVL(const ArbolAVL& other); // Constructor de copia
    ArbolAVL& operator=(const ArbolAVL& other); // Operador de asignación
    ~ArbolAVL();

    void insert(T value);
    void erase(T value);
    void eraseOther(T value);

    void clear();
    bool empty() const;
    unsigned int size() const;

    int find(T value) const;
    T obtain(T value) const;
    T obtainByIndex(unsigned int idx) const;
    T& obtainByReference(unsigned int idx) const;
    int lower_bound(T value) const;
    int upper_bound(T value) const;

    const T& find_min() const;
    const T& find_max() const;
    const T& operator[](unsigned int idx) const;

    void display();
    NodoArbolAVL<T>* getRoot() const;
    NodoArbolAVL<T>* findNodo(const T& value) const;
};

template <class T>
NodoArbolAVL<T>* ArbolAVL<T>::findNodo(const T& value) const {
    NodoArbolAVL<T>* current = root;
    while (current != NULL) {
        if (current->value == value) {
            return current;
        } else if (current->value > value) {
            current = current->left;
        } else {
            current = current->right;
        }
    }
    return NULL;
}


template <class T>
NodoArbolAVL<T>* ArbolAVL<T>::getRoot() const {
    return root;
}

template <class T>
NodoArbolAVL<T>* ArbolAVL<T>::copiarNodo(const NodoArbolAVL<T>* nodo) {
    if (!nodo) return NULL;
    NodoArbolAVL<T>* nuevoNodo = new NodoArbolAVL<T>(nodo->value);
    nuevoNodo->left = copiarNodo(nodo->left);
    nuevoNodo->right = copiarNodo(nodo->right);
    nuevoNodo->updateValues();
    return nuevoNodo;
}

template <class T>
ArbolAVL<T>::ArbolAVL() : root(NULL), _size(0) {}

template <class T>
ArbolAVL<T>::ArbolAVL(const ArbolAVL& other) : _size(other._size) {
    root = copiarNodo(other.root);
}

template <class T>
ArbolAVL<T>& ArbolAVL<T>::operator=(const ArbolAVL& other) {
    if (this != &other) {
        clear();
        root = copiarNodo(other.root);
        _size = other._size;
    }
    return *this;
}

template <class T>
ArbolAVL<T>::~ArbolAVL() {
    clear();
}

template <class T>
void ArbolAVL<T>::clear() {
    pila<NodoArbolAVL<T>*> stack;

    if (root != NULL)
        stack.Push(root);

    while (!stack.PilaVacia()) {
        NodoArbolAVL<T> *node = stack.Top();
        stack.Pop();

        if (node->left != NULL)
            stack.Push(node->left);

        if (node->right != NULL)
            stack.Push(node->right);
        
        if(node != NULL){
            delete node;
        }
    }

    root = NULL;
    _size = 0;
}

template <class T>
void ArbolAVL<T>::insert(T value) {
    NodoArbolAVL<T> **indirect = &root;
    NodoArbolAVL<T> **path[64];
    int path_length = 0;
    while (*indirect != NULL) {
        path[path_length++] = indirect;
        if ((*indirect)->value > value) {
            indirect = &((*indirect)->left);
        } else {
            indirect = &((*indirect)->right);
        }
    }
    *indirect = new NodoArbolAVL<T>(value);
    path[path_length++] = indirect;
    balance(path, path_length);
    _size++;
}

template <class T>
void ArbolAVL<T>::eraseOther(T value) {
    NodoArbolAVL<T> **indirect = &root;  // to generalize insertion
    NodoArbolAVL<T> **path[100];  // to update height values
    int pathSize = 0;

    while (*indirect != NULL && (*indirect)->value != value) {
        path[pathSize++] = indirect;
        if ((*indirect)->value > value)
            indirect = &((*indirect)->left);
        else
            indirect = &((*indirect)->right);
    }

    if (*indirect == NULL) return;

    path[pathSize++] = indirect;

    if ((*indirect)->left == NULL && (*indirect)->right == NULL) {
        delete *indirect;
        *indirect = NULL;
        pathSize--;
    } else if ((*indirect)->right == NULL) {
        NodoArbolAVL<T> *toRemove = *indirect;
        *indirect = (*indirect)->left;
        delete toRemove;
        pathSize--;
    } else {
        NodoArbolAVL<T> **successor = &((*indirect)->right);
        while ((*successor)->left != NULL) {
            path[pathSize++] = successor;
            successor = &((*successor)->left);
        }

        if (*successor == (*indirect)->right) {
            (*successor)->left = (*indirect)->left;
            NodoArbolAVL<T> *toRemove = *indirect;
            *indirect = *successor;
            delete toRemove;
        } else {
            NodoArbolAVL<T> *tmp = *path[pathSize - 1], *suc = *successor;
            tmp->left = (*successor)->right;
            suc->left = (*indirect)->left;
            suc->right = (*indirect)->right;
            delete *indirect;
            *indirect = suc;
            path[pathSize - 1] = &(suc->right);
        }
    }

    balanceOther(path, pathSize);
    _size--;
}

template <class T>
void ArbolAVL<T>::erase(T value) {
    NodoArbolAVL<T> **indirect = &root;
    NodoArbolAVL<T> **path[64];
    int path_length = 0;

    while (*indirect != NULL && !((*indirect)->value == value)) {
        path[path_length++] = indirect;
        if ((*indirect)->value > value)
            indirect = &((*indirect)->left);
        else
            indirect = &((*indirect)->right);
    }

    if (*indirect == NULL)
        return;

    path[path_length++] = indirect;

    NodoArbolAVL<T> *toRemove = *indirect;

    if (toRemove->left == NULL && toRemove->right == NULL) {
        *indirect = NULL;
    } else if (toRemove->right == NULL) {
        *indirect = toRemove->left;
    } else if (toRemove->left == NULL) {
        *indirect = toRemove->right;
    } else {
        NodoArbolAVL<T> **successor = &((*indirect)->right);
        while ((*successor)->left != NULL) {
            path[path_length++] = successor;
            successor = &((*successor)->left);
        }
        NodoArbolAVL<T> *temp = *successor;
        *successor = (*successor)->right;
        temp->left = toRemove->left;
        temp->right = toRemove->right;
        *indirect = temp;
    }

    delete toRemove;
    balance(path, path_length);
    _size--;
}

template <class T>
void ArbolAVL<T>::balanceOther(NodoArbolAVL<T> **path[], int pathSize) {
    for (int i = pathSize - 1; i >= 0; --i) {
        (*path[i])->updateValuesOther();
        if ((*path[i])->balanceFactorOther() >= 2 && (*path[i])->left->balanceFactorOther() >= 0)
            *path[i] = (*path[i])->right_rotate();
        else if ((*path[i])->balanceFactorOther() >= 2) {
            (*path[i])->left = (*path[i])->left->left_rotate();
            *path[i] = (*path[i])->right_rotate();
        } else if ((*path[i])->balanceFactorOther() <= -2 && (*path[i])->right->balanceFactorOther() <= 0)
            *path[i] = (*path[i])->left_rotate();
        else if ((*path[i])->balanceFactorOther() <= -2) {
            (*path[i])->right = ((*path[i])->right)->right_rotate();
            *path[i] = (*path[i])->left_rotate();
        }
    }
}

template <class T>
void ArbolAVL<T>::balance(NodoArbolAVL<T> **path[], int path_length) {
    for (int i = path_length - 1; i >= 0; i--) {
        if (*path[i] == NULL) {
            continue; // Asegúrate de que el nodo no es nulo
        }

        (*path[i])->updateValues();

        if ((*path[i])->balanceFactor() >= 2 && (*path[i])->left->balanceFactor() >= 0)
            *path[i] = (*path[i])->right_rotate();
        else if ((*path[i])->balanceFactor() >= 2) {
            (*path[i])->left = (*path[i])->left->left_rotate();
            *path[i] = (*path[i])->right_rotate();
        } else if ((*path[i])->balanceFactor() <= -2 && (*path[i])->right->balanceFactor() <= 0)
            *path[i] = (*path[i])->left_rotate();
        else if ((*path[i])->balanceFactor() <= -2) {
            (*path[i])->right = ((*path[i])->right)->right_rotate();
            *path[i] = (*path[i])->left_rotate();
        }
    }
}

template <class T>
bool ArbolAVL<T>::empty() const {
    return _size == 0;
}

template <class T>
unsigned int ArbolAVL<T>::size() const {
    return _size;
}

template <class T>
int ArbolAVL<T>::find(T value) const {
    NodoArbolAVL<T> *node = root;
    unsigned int idx = 0;

    while (node != NULL) {
        if (node->value == value) {
            return idx + (node->left ? node->left->count : 0);
        } else if (node->value > value) {
            node = node->left;
        } else {
            idx += (node->left ? node->left->count : 0) + 1;
            node = node->right;
        }
    }

    return -1; // El valor no fue encontrado
}



template <class T>
T ArbolAVL<T>::obtain(T value) const {
    int index = find(value);  // Utiliza el método find existente para obtener el índice
    if (index == -1) {
        std::cerr << "Value not found in AVL Tree" << std::endl;
        // Retornar un valor por defecto o manejar de otra manera
        return T();
    }
    return (*this)[index];  // Utiliza el operador[] para obtener el valor en el índice encontrado
}

template <class T>
T ArbolAVL<T>::obtainByIndex(unsigned int idx) const {
    if (idx >= _size) {
        std::cerr << "Index out of range" << std::endl;
        // Retornar un valor por defecto o manejar de otra manera
        return T();
    }

    pila<NodoArbolAVL<T>*> stack;
    NodoArbolAVL<T> *current = root;
    unsigned int count = 0;

    while (current != NULL || !stack.PilaVacia()) {
        while (current != NULL) {
            stack.Push(current);
            current = current->left;
        }

        current = stack.Top();
        stack.Pop();

        if (count == idx) {
            return current->value;
        }
        count++;

        current = current->right;
    }

    std::cerr << "Index out of range" << std::endl;
    // Retornar un valor por defecto o manejar de otra manera
    return T();
}

template <class T>
int ArbolAVL<T>::lower_bound(T value) const {
    NodoArbolAVL<T> *node = root;
    unsigned int idx = 0;

    while (node != NULL) {
        if (node->value >= value)
            node = node->left;
        else {
            idx += (node->left ? node->left->count : 0) + 1;
            node = node->right;
        }
    }

    return idx;
}

template <class T>
int ArbolAVL<T>::upper_bound(T value) const {
    NodoArbolAVL<T> *node = root;
    unsigned int idx = 0;

    while (node != NULL) {
        if (node->value > value)
            node = node->left;
        else {
            idx += (node->left ? node->left->count : 0) + 1;
            node = node->right;
        }
    }

    return idx;
}

template <class T>
T& ArbolAVL<T>::obtainByReference(unsigned int idx) const {
    if (idx >= _size) {
        std::cout<<"Index out of range";
    }

    NodoArbolAVL<T> *cur = root;
    while (cur != NULL) {
        unsigned int left = cur->left != NULL ? cur->left->count : 0;

        if (left == idx) {
            return cur->value;
        } else if (left < idx) {
            idx -= left + 1;
            cur = cur->right;
        } else {
            cur = cur->left;
        }
    }

    std::cout<<"Index out of range";
}


template <class T>
const T& ArbolAVL<T>::find_min() const {
    NodoArbolAVL<T> *cur = root;

    while (cur->left != NULL)
        cur = cur->left;

    return cur->value;
}

template <class T>
const T& ArbolAVL<T>::find_max() const {
    NodoArbolAVL<T> *cur = root;

    while (cur->right != NULL)
        cur = cur->right;

    return cur->value;
}

template <class T>
const T& ArbolAVL<T>::operator[](unsigned int idx) const {
    NodoArbolAVL<T> *cur = root;
    unsigned int left = cur->left != NULL ? cur->left->count : 0;

    while (left != idx) {
        if (left < idx) {
            idx -= left + 1;
            cur = cur->right;
            left = cur->left != NULL ? cur->left->count : 0;
        } else {
            cur = cur->left;
            left = cur->left != NULL ? cur->left->count : 0;
        }
    }

    return cur->value;
}

template <class T>
void ArbolAVL<T>::display() {
    if (root == NULL) {
        std::cout << "Empty" << std::endl;
        return;
    }

    pila<NodoArbolAVL<T>*> stack;
    NodoArbolAVL<T>* current = root;

    while (current != NULL || !stack.PilaVacia()) {
        while (current != NULL) {
            stack.Push(current);
            current = current->left;
        }

        current = stack.Top();
        stack.Pop();

        std::cout << current->value; // Imprimir el valor del nodo

        current = current->right;
    }

    std::cout << std::endl;
}

template <class T>
void ArbolAVL<T>::display(NodoArbolAVL<T> *cur, int depth, int state) {
    if (cur->left != NULL)
        display(cur->left, depth + 1, 1);

    for (int i = 0; i < depth; i++)
        std::cout << "     ";

    if (state == 1) // Izquierdo
        std::cout << "+---";
    else if (state == 2) // Derecho
        std::cout << "+---";

    std::cout << "[" << cur->value << "] - (" << cur->count << ", " << cur->height << ")" << std::endl;

    if (cur->right != NULL)
        display(cur->right, depth + 1, 2);
}

#endif // ARBOLAVL_H

