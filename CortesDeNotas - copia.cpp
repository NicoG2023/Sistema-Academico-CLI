#include "CortesDeNotas.h"
using namespace std;

CortesDeNotas::CortesDeNotas() {
    cortes = new ArbolAVL<Corte*>(); // Inicializa el árbol
}

CortesDeNotas::~CortesDeNotas() {
    // Destruir cada Corte en el árbol antes de eliminar el árbol en sí
    while (!cortes->empty()) {
        Corte* corte = (*cortes)[0]; // Encuentra el corte más pequeño
        delete corte; // Elimina el objeto Corte
        cortes->erase(corte); // Elimina el nodo del árbol
    }
    delete cortes; // Elimina el árbol en sí
}



//INSERCIONES
void CortesDeNotas::agregarCorte(const string& tipo_evaluacion, int porcentaje) {
    if (cortes == NULL) {
        cortes = new ArbolAVL<Corte*>();
    }
    // Crea el nuevo corte y agrégalo al árbol
    Corte* nuevoCorte = new Corte(tipo_evaluacion, porcentaje, NULL);
    cortes->insert(nuevoCorte);
}

void CortesDeNotas::agregarEvaluacion(const string& tipo_evaluacion, const string& nombreEvaluacion) {
    // Encuentra el corte por su nombre (tipo_evaluacion)
    int indiceCorte = cortes->find(new Corte(tipo_evaluacion, 0, NULL));

    if (indiceCorte != -1) {
        Corte* corte = (*cortes)[indiceCorte];
        if (corte->evaluaciones == NULL) {
            corte->evaluaciones = new ArbolAVL<Evaluacion*>();
        }

        // Crea la nueva evaluación y agrégala al árbol
        Evaluacion* nuevaEvaluacion = new Evaluacion(nombreEvaluacion, new ArbolAVL<Punto>());
        corte->evaluaciones->insert(nuevaEvaluacion);
    } else {
        std::cout << "Corte no encontrado: " << tipo_evaluacion << std::endl;
    }
}

void CortesDeNotas::agregarPunto(const string& tipo_evaluacion, const string& nombreEvaluacion, int porcentajePunto, int codigo_tema) {
    // Encuentra el corte según el tipo de evaluación
    int indiceCorte = cortes->find(new Corte(tipo_evaluacion, 0, NULL));

    if (indiceCorte != -1) {
        Corte* corte = (*cortes)[indiceCorte];

        // Encuentra la evaluación según su nombre
        int indiceEvaluacion = corte->evaluaciones->find(new Evaluacion(nombreEvaluacion, NULL));

        if (indiceEvaluacion != -1) {
            Evaluacion* evaluacion = (*corte->evaluaciones)[indiceEvaluacion];
            Punto nuevoPunto(porcentajePunto, codigo_tema);

            // Verifica si el nuevo porcentaje no excede el 100%
            int porcentajeActual = 0;
            for (int i = 0; i < evaluacion->puntos->size(); ++i) {
                porcentajeActual += (*evaluacion->puntos)[i].porcentaje;
            }

            if (porcentajeActual + porcentajePunto <= 100) {
                evaluacion->puntos->insert(nuevoPunto);
                std::cout << "Punto agregado exitosamente." << std::endl;
            } else {
                std::cout << "Error: La suma de los porcentajes excede el 100%." << std::endl;
            }
        } else {
            std::cout << "Evaluación no encontrada: " << nombreEvaluacion << std::endl;
        }
    } else {
        std::cout << "Corte no encontrado: " << tipo_evaluacion << std::endl;
    }
}





//ELIMINACIONES
void CortesDeNotas::eliminarCorte(const string& tipo_evaluacion) {
    int indiceCorte = cortes->find(new Corte(tipo_evaluacion, 0, NULL));

    if (indiceCorte != -1) {
        cortes->erase((*cortes)[indiceCorte]);
        std::cout << "Corte eliminado exitosamente." << std::endl;
    } else {
        std::cout << "Corte no encontrado: " << tipo_evaluacion << std::endl;
    }
}

void CortesDeNotas::eliminarEvaluacion(const string& tipo_evaluacion, const string& nombreEvaluacion) {
    // Encuentra el corte según el tipo de evaluación
    int indiceCorte = cortes->find(new Corte(tipo_evaluacion, 0, NULL));

    if (indiceCorte != -1) {
        Corte* corte = (*cortes)[indiceCorte];

        // Encuentra la evaluación según su nombre
        int indiceEvaluacion = corte->evaluaciones->find(new Evaluacion(nombreEvaluacion, NULL));

        if (indiceEvaluacion != -1) {
            corte->evaluaciones->erase((*corte->evaluaciones)[indiceEvaluacion]);
            std::cout << "Evaluación eliminada exitosamente." << std::endl;
        } else {
            std::cout << "Evaluación no encontrada: " << nombreEvaluacion << std::endl;
        }
    } else {
        std::cout << "Corte no encontrado: " << tipo_evaluacion << std::endl;
    }
}

void CortesDeNotas::eliminarPunto(const string& tipo_evaluacion, const string& nombreEvaluacion, int porcentajePunto, int codigo_tema) {
    int indiceCorte = cortes->find(new Corte(tipo_evaluacion, 0, NULL));

    if (indiceCorte != -1) {
        Corte* corte = (*cortes)[indiceCorte];
        int indiceEvaluacion = corte->evaluaciones->find(new Evaluacion(nombreEvaluacion, NULL));

        if (indiceEvaluacion != -1) {
            Evaluacion* evaluacion = (*corte->evaluaciones)[indiceEvaluacion];
            Punto puntoParaEliminar(porcentajePunto, codigo_tema);
            int indicePunto = evaluacion->puntos->find(puntoParaEliminar);

            if (indicePunto != -1) {
                evaluacion->puntos->erase(puntoParaEliminar);
                std::cout << "Punto eliminado exitosamente." << std::endl;
            } else {
                std::cout << "Punto no encontrado." << std::endl;
            }
        } else {
            std::cout << "Evaluación no encontrada: " << nombreEvaluacion << std::endl;
        }
    } else {
        std::cout << "Corte no encontrado: " << tipo_evaluacion << std::endl;
    }
}

//BUSQUEDAS

void CortesDeNotas::buscarCorte(const std::string& tipo_evaluacion) {
    int indiceCorte = cortes->find(new Corte(tipo_evaluacion, 0, NULL));

    if (indiceCorte != -1) {
        Corte* corte = (*cortes)[indiceCorte];
        std::cout << "Nombre del Corte: " << corte->nombre << std::endl;
        std::cout << "Porcentaje: " << corte->porcentaje << std::endl;

        if (corte->evaluaciones != NULL) {
            std::cout << "Evaluaciones: " << std::endl;
            for (int i = 0; i < corte->evaluaciones->size(); ++i) {
                Evaluacion* eval = (*corte->evaluaciones)[i];
                std::cout << "  - " << eval->nombre << std::endl;
            }
        } else {
            std::cout << "No hay evaluaciones." << std::endl;
        }
    } else {
        std::cout << "Corte no encontrado: " << tipo_evaluacion << std::endl;
    }
}

void CortesDeNotas::buscarEvaluacion(const std::string& tipo_evaluacion, const std::string& nombreEvaluacion) {
    int indiceCorte = cortes->find(new Corte(tipo_evaluacion, 0, NULL));

    if (indiceCorte != -1) {
        Corte* corte = (*cortes)[indiceCorte];
        int indiceEvaluacion = corte->evaluaciones->find(new Evaluacion(nombreEvaluacion, NULL));

        if (indiceEvaluacion != -1) {
            Evaluacion* eval = (*corte->evaluaciones)[indiceEvaluacion];
            std::cout << "Nombre de la Evaluación: " << eval->nombre << std::endl;
            std::cout << "Cantidad de puntos: " << eval->puntos->size() << std::endl;
        } else {
            std::cout << "Evaluación no encontrada: " << nombreEvaluacion << std::endl;
        }
    } else {
        std::cout << "Corte no encontrado: " << tipo_evaluacion << std::endl;
    }
}

void CortesDeNotas::buscarPunto(const string& tipo_evaluacion, const string& nombreEvaluacion, int codigo_tema) {
    int indiceCorte = cortes->find(new Corte(tipo_evaluacion, 0, NULL));

    if (indiceCorte != -1) {
        Corte* corte = (*cortes)[indiceCorte];
        int indiceEvaluacion = corte->evaluaciones->find(new Evaluacion(nombreEvaluacion, NULL));

        if (indiceEvaluacion != -1) {
            Evaluacion* eval = (*corte->evaluaciones)[indiceEvaluacion];

            // Busca un punto con el código de tema especificado
            for (int i = 0; i < eval->puntos->size(); ++i) {
                Punto punto = (*eval->puntos)[i];
                if (punto.codigo_tema == codigo_tema) {
                    cout << "Punto encontrado:" << endl;
                    cout << "  Porcentaje: " << punto.porcentaje << endl;
                    cout << "  Código del tema: " << punto.codigo_tema << endl;
                    return;
                }
            }

            std::cout << "Punto no encontrado con el código de tema: " << codigo_tema << endl;
        } else {
            std::cout << "Evaluación no encontrada: " << nombreEvaluacion << endl;
        }
    } else {
        std::cout << "Corte no encontrado: " << tipo_evaluacion << endl;
    }
}



