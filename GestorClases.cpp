#include "GestorClases.h"
using namespace std;

GestorClases::GestorClases() : gestorProfesores(*(new GestorProfesores())) {}

GestorClases::GestorClases(GestorProfesores& gestorProfesores) : gestorProfesores(gestorProfesores) {}

GestorClases::~GestorClases() {
    delete &gestorProfesores; // Si `gestorProfesores` se cre� con `new` en el constructor sin par�metros
}

NodoArbolAVL<Clases>* GestorClases::getRootClases() const {
    return clases.getRoot();
}

void GestorClases::listarClases() {
    clases.display();
}

Clases* GestorClases::buscarClases(int codigo_profesor){
	int idx = clases.find(Clases(codigo_profesor));
    if (idx == -1) {
        std::cout << "Clase con c�digo de profesor no encontrada" << std::endl;
        return NULL;
    }
    return &clases.obtainByReference(idx);
}

//profesor existe, clase ya agregada a profesor, materia ya agregada a profesor
void GestorClases::agregarClase(int codigo_profesor) {
    Clases clase(codigo_profesor);
    clases.insert(clase);
}

void GestorClases::agregarMateria(int codigo_profesor, const string& materia) {
	Profesor* profe = gestorProfesores.buscarProfesores(codigo_profesor);
	if(profe){
		Clases* clase = buscarClases(codigo_profesor);
	    if (clase) {
	    	if(clase->clasesProfesor->size() < profe->clases_asignadas){
	    		clase->clasesProfesor->insert(Materias(materia));
	    		std::cout << "Materia agregada exitosamente." << std::endl;
			}else{
				cout << "No se pueden agregar mas clases al profesor."<<endl;
			}
	        
	    } else {
	        cout<<"Clase no encontrada."<<endl;
	    }
	}else{
		cout << "Profesor no encontrado."<<endl;
	}
    
}

Temas* GestorClases::buscarTemaPorCodigo(int codigoTema) {
    const ArbolAVL<Clases>& clasesAVL = getClases();
    for (int i = 0; i < clasesAVL.size(); ++i) {
        const Clases& clase = clasesAVL.obtainByReference(i);
        for (int j = 0; j < clase.clasesProfesor->size(); ++j) {
            Materias& materia = clase.clasesProfesor->obtainByReference(j);
            for (int k = 0; k < materia.temas.size(); ++k) {
                Temas& tema = materia.temas.obtainByReference(k);
                if (tema.codigo_tema == codigoTema) {
                    return &tema;
                }
            }
        }
    }
    return NULL;
}


void GestorClases::eliminarClase(int codigo_profesor) {
    int idx = clases.find(Clases(codigo_profesor));
    if (idx == -1) {
        std::cout << "Error: Clase con c�digo de profesor " << codigo_profesor << " no encontrada." << std::endl;
        return;
    }
    clases.erase(clases.obtainByReference(idx));
    std::cout << "Clase con c�digo de profesor " << codigo_profesor << " eliminada." << std::endl;
}

void GestorClases::consultarProfesoresPorNumeroClases(int numeroClases) {
    Lista<NodoProfesor> listaProfesores;

    // Recorrer todas las clases
    for (unsigned int i = 0; i < clases.size(); ++i) {
        Clases& clase = clases.obtainByReference(i);
        int codigoProfesor = clase.codigo_profesor;
        int cantidadMaterias = clase.clasesProfesor->size();
        

        if (cantidadMaterias == numeroClases) {
            NodoProfesor nuevoNodo(codigoProfesor, cantidadMaterias);
            listaProfesores.insertar_final(nuevoNodo);
        }
    }

    // Mostrar la lista de profesores
    if (listaProfesores.lista_vacia()) {
        std::cout << "No hay profesores con " << numeroClases << " clases." << std::endl;
    } else {
        std::cout << "Profesores con " << numeroClases << " clases:" << std::endl;
        for (int i = 1; i <= listaProfesores.getTam(); i++) {
            NodoProfesor temp = listaProfesores.buscar_nodo(i);
            Profesor* profesor = gestorProfesores.buscarProfesores(temp.cedula);
            if (profesor) {
                std::cout << "C�dula: " << profesor->cedula << ", Nombre: " << profesor->nombre << ", Materias: ";

                // Recorrer las clases para encontrar las materias del profesor
                for (unsigned int j = 0; j < clases.size(); ++j) {
                    Clases& clase = clases.obtainByReference(j);

                    if (clase.codigo_profesor == profesor->cedula) {
                        // Recorrer las materias del profesor
                        for (unsigned int k = 0; k < clase.clasesProfesor->size(); ++k) {
                            Materias& materia = clase.clasesProfesor->obtainByReference(k);

                            if (k > 0) {
                                std::cout << ", ";
                            }
                            std::cout << materia.materia;
                        }
                    }
                }
                std::cout << std::endl;
            } else {
                std::cerr << "Profesor no encontrado para la c�dula: " << temp.cedula << std::endl;
            }
        }
    }
}

const ArbolAVL<Clases>& GestorClases::getClases() const {
    return clases;
}


