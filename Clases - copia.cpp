#include "Clases.h"

Clases::Clases(int codigo_profesor) : codigo_profesor(codigo_profesor) {
	clasesProfesor = new ArbolAVL<Materias>();
}

Clases::Clases() : codigo_profesor(0) {
	clasesProfesor = new ArbolAVL<Materias>();
}

Clases::~Clases() {
	delete clasesProfesor;
}

// Constructor de copia
Clases::Clases(const Clases& other)
    : codigo_profesor(other.codigo_profesor), clasesProfesor(new ArbolAVL<Materias>(*other.clasesProfesor)) {}

// Operador de asignación
Clases& Clases::operator=(const Clases& other) {
    if (this != &other) {
        delete clasesProfesor; // Liberar la memoria existente
        codigo_profesor = other.codigo_profesor;
        clasesProfesor = new ArbolAVL<Materias>(*other.clasesProfesor); // Copiar el árbol AVL
    }
    return *this;
}

void Clases::eliminarMateria(const string& materia) {
    Materias mat(materia);
    clasesProfesor->erase(mat);
    cout << "Materia " << materia << " eliminada" << endl;
}

Materias Clases::buscarMateria(const string& materia) {
    int idx = clasesProfesor->find(Materias(materia));
    if (idx == -1) {
        std::cout<<"Materia no encontrada"<<std::endl;
    }
    return clasesProfesor->obtainByReference(idx);
}

Materias* Clases::buscarMaterias(const string& materia) {
    int idx = clasesProfesor->find(Materias(materia));
    if (idx == -1) {
        return NULL;
    }
    return &clasesProfesor->obtainByReference(idx);
}

void Clases::listarMaterias(){
	clasesProfesor->display();
}

NodoArbolAVL<Materias>* Clases::findNodo(const std::string& materia) {
    NodoArbolAVL<Materias>* current = clasesProfesor->getRoot();
    while (current != NULL) {
        if (current->value.materia == materia) {
            return current;
        } else if (current->value.materia > materia) {
            current = current->left;
        } else {
            current = current->right;
        }
    }
    return NULL;
}

void Clases::comportamientoPromedioPorTemas(GestorProfesores& gestorProfesores) {
    NodoArbolAVL<Materias>* currentMateria = clasesProfesor->getRoot();
    pila<NodoArbolAVL<Materias>*> stackMaterias;
    
    Profesor* profesor = gestorProfesores.buscarProfesores(codigo_profesor);
    if (!profesor) {
        std::cout << "Profesor no encontrado para el código: " << codigo_profesor << std::endl;
        return;
    }

    while (currentMateria != NULL || !stackMaterias.PilaVacia()) {
        while (currentMateria != NULL) {
            stackMaterias.Push(currentMateria);
            currentMateria = currentMateria->left;
        }

        currentMateria = stackMaterias.Top();
        stackMaterias.Pop();

        // Obtenemos el comportamiento promedio por temas de esta materia
        Materias& materia = currentMateria->value;
        std::cout << "voy por aca bro"<<std::endl;
        std::cout << "Materia: " << materia.materia << std::endl;
        materia.comportamientoGeneralEnTemas(*profesor);

        currentMateria = currentMateria->right;
    }
}


