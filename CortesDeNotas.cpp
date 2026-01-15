#include "CortesDeNotas.h"
#include <iostream>

using namespace std;

CortesDeNotas::CortesDeNotas() {
    cortes = new ArbolAVL<Corte*>(); // Inicializa el árbol
}

CortesDeNotas::~CortesDeNotas() {
    // Destruir cada Corte* en el árbol antes de eliminar el árbol en sí
    while (!cortes->empty()) {
        Corte* corte = (*cortes)[0]; // Asume que [0] devuelve el menor
        cortes->erase(corte);        // Quita del árbol
        delete corte;                // Libera memoria del Corte
    }
    delete cortes;
}



// INSERCIONES
void CortesDeNotas::agregarCorte(const string& tipo_evaluacion, int porcentaje) {
    if (cortes == NULL) {
        cortes = new ArbolAVL<Corte*>();
    }

    // Tu Corte solo tiene (string, int)
    Corte* nuevoCorte = new Corte(tipo_evaluacion, porcentaje);
    cortes->insert(nuevoCorte);
}

void CortesDeNotas::agregarEvaluacion(const string& tipo_evaluacion, const string& nombreEvaluacion) {
    // OJO: find espera Corte* porque tu árbol es ArbolAVL<Corte*>
    // Creamos un "Corte temporal" solo para buscar por nombre.
    Corte* key = new Corte(tipo_evaluacion, 0);
    int indiceCorte = cortes->find(key);
    delete key;

    if (indiceCorte != -1) {
        Corte* corte = (*cortes)[indiceCorte];

        // Corte.h: evaluaciones es ArbolAVL<Evaluacion>*, NO de punteros
        if (corte->evaluaciones == NULL) {
            corte->evaluaciones = new ArbolAVL<Evaluacion>();
        }

        // Evaluacion.h (por tus errores) tiene ctor Evaluacion(string)
        Evaluacion nuevaEvaluacion(nombreEvaluacion);
        corte->evaluaciones->insert(nuevaEvaluacion);
    } else {
        cout << "Corte no encontrado: " << tipo_evaluacion << endl;
    }
}

void CortesDeNotas::agregarPunto(const string& tipo_evaluacion, const string& nombreEvaluacion,
                                int porcentajePunto, int codigo_tema) {
    Corte* keyC = new Corte(tipo_evaluacion, 0);
    int indiceCorte = cortes->find(keyC);
    delete keyC;

    if (indiceCorte == -1) {
        cout << "Corte no encontrado: " << tipo_evaluacion << endl;
        return;
    }

    Corte* corte = (*cortes)[indiceCorte];
    if (corte->evaluaciones == NULL) {
        cout << "No hay evaluaciones en el corte: " << tipo_evaluacion << endl;
        return;
    }

    // Buscar evaluación por nombre (como objeto)
    Evaluacion keyE(nombreEvaluacion);
    int indiceEvaluacion = corte->evaluaciones->find(keyE);

    if (indiceEvaluacion == -1) {
        cout << "Evaluación no encontrada: " << nombreEvaluacion << endl;
        return;
    }

    // Ahora es objeto, no puntero
    Evaluacion& evaluacion = (*corte->evaluaciones)[indiceEvaluacion];

    Punto nuevoPunto(porcentajePunto, codigo_tema);

    // Verifica si el nuevo porcentaje no excede el 100%
    int porcentajeActual = 0;
    for (int i = 0; i < (int)evaluacion.puntos->size(); ++i) {
        porcentajeActual += (*evaluacion.puntos)[i].porcentaje;
    }

    if (porcentajeActual + porcentajePunto <= 100) {
        evaluacion.puntos->insert(nuevoPunto);
        cout << "Punto agregado exitosamente." << endl;
    } else {
        cout << "Error: La suma de los porcentajes excede el 100%." << endl;
    }
}



// ELIMINACIONES
void CortesDeNotas::eliminarCorte(const string& tipo_evaluacion) {
    Corte* key = new Corte(tipo_evaluacion, 0);
    int indiceCorte = cortes->find(key);
    delete key;

    if (indiceCorte != -1) {
        Corte* corte = (*cortes)[indiceCorte];
        cortes->erase(corte);
        delete corte;
        cout << "Corte eliminado exitosamente." << endl;
    } else {
        cout << "Corte no encontrado: " << tipo_evaluacion << endl;
    }
}

void CortesDeNotas::eliminarEvaluacion(const string& tipo_evaluacion, const string& nombreEvaluacion) {
    Corte* keyC = new Corte(tipo_evaluacion, 0);
    int indiceCorte = cortes->find(keyC);
    delete keyC;

    if (indiceCorte == -1) {
        cout << "Corte no encontrado: " << tipo_evaluacion << endl;
        return;
    }

    Corte* corte = (*cortes)[indiceCorte];
    if (corte->evaluaciones == NULL) {
        cout << "No hay evaluaciones en el corte." << endl;
        return;
    }

    Evaluacion keyE(nombreEvaluacion);
    int indiceEvaluacion = corte->evaluaciones->find(keyE);

    if (indiceEvaluacion != -1) {
        // Borramos por valor (objeto)
        Evaluacion evalAEliminar = (*corte->evaluaciones)[indiceEvaluacion];
        corte->evaluaciones->erase(evalAEliminar);
        cout << "Evaluación eliminada exitosamente." << endl;
    } else {
        cout << "Evaluación no encontrada: " << nombreEvaluacion << endl;
    }
}

void CortesDeNotas::eliminarPunto(const string& tipo_evaluacion, const string& nombreEvaluacion,
                                 int porcentajePunto, int codigo_tema) {
    Corte* keyC = new Corte(tipo_evaluacion, 0);
    int indiceCorte = cortes->find(keyC);
    delete keyC;

    if (indiceCorte == -1) {
        cout << "Corte no encontrado: " << tipo_evaluacion << endl;
        return;
    }

    Corte* corte = (*cortes)[indiceCorte];
    if (corte->evaluaciones == NULL) {
        cout << "No hay evaluaciones en el corte." << endl;
        return;
    }

    Evaluacion keyE(nombreEvaluacion);
    int indiceEvaluacion = corte->evaluaciones->find(keyE);

    if (indiceEvaluacion == -1) {
        cout << "Evaluación no encontrada: " << nombreEvaluacion << endl;
        return;
    }

    Evaluacion& evaluacion = (*corte->evaluaciones)[indiceEvaluacion];
    Punto puntoParaEliminar(porcentajePunto, codigo_tema);

    int indicePunto = evaluacion.puntos->find(puntoParaEliminar);
    if (indicePunto != -1) {
        evaluacion.puntos->erase(puntoParaEliminar);
        cout << "Punto eliminado exitosamente." << endl;
    } else {
        cout << "Punto no encontrado." << endl;
    }
}



// BUSQUEDAS
void CortesDeNotas::buscarCorte(const std::string& tipo_evaluacion) {
    Corte* keyC = new Corte(tipo_evaluacion, 0);
    int indiceCorte = cortes->find(keyC);
    delete keyC;

    if (indiceCorte != -1) {
        Corte* corte = (*cortes)[indiceCorte];
        cout << "Nombre del Corte: " << corte->nombre << endl;
        cout << "Porcentaje: " << corte->porcentaje << endl;

        if (corte->evaluaciones != NULL) {
            cout << "Evaluaciones: " << endl;
            for (int i = 0; i < (int)corte->evaluaciones->size(); ++i) {
                Evaluacion& eval = (*corte->evaluaciones)[i];
                cout << "  - " << eval.nombre << endl;
            }
        } else {
            cout << "No hay evaluaciones." << endl;
        }
    } else {
        cout << "Corte no encontrado: " << tipo_evaluacion << endl;
    }
}

void CortesDeNotas::buscarEvaluacion(const std::string& tipo_evaluacion, const std::string& nombreEvaluacion) {
    Corte* keyC = new Corte(tipo_evaluacion, 0);
    int indiceCorte = cortes->find(keyC);
    delete keyC;

    if (indiceCorte == -1) {
        cout << "Corte no encontrado: " << tipo_evaluacion << endl;
        return;
    }

    Corte* corte = (*cortes)[indiceCorte];
    if (corte->evaluaciones == NULL) {
        cout << "No hay evaluaciones en el corte." << endl;
        return;
    }

    Evaluacion keyE(nombreEvaluacion);
    int indiceEvaluacion = corte->evaluaciones->find(keyE);

    if (indiceEvaluacion != -1) {
        Evaluacion& eval = (*corte->evaluaciones)[indiceEvaluacion];
        cout << "Nombre de la Evaluación: " << eval.nombre << endl;
        cout << "Cantidad de puntos: " << eval.puntos->size() << endl;
    } else {
        cout << "Evaluación no encontrada: " << nombreEvaluacion << endl;
    }
}

void CortesDeNotas::buscarPunto(const string& tipo_evaluacion, const string& nombreEvaluacion, int codigo_tema) {
    Corte* keyC = new Corte(tipo_evaluacion, 0);
    int indiceCorte = cortes->find(keyC);
    delete keyC;

    if (indiceCorte == -1) {
        cout << "Corte no encontrado: " << tipo_evaluacion << endl;
        return;
    }

    Corte* corte = (*cortes)[indiceCorte];
    if (corte->evaluaciones == NULL) {
        cout << "No hay evaluaciones en el corte." << endl;
        return;
    }

    Evaluacion keyE(nombreEvaluacion);
    int indiceEvaluacion = corte->evaluaciones->find(keyE);

    if (indiceEvaluacion == -1) {
        cout << "Evaluación no encontrada: " << nombreEvaluacion << endl;
        return;
    }

    Evaluacion& eval = (*corte->evaluaciones)[indiceEvaluacion];

    // Busca un punto con el código de tema especificado
    for (int i = 0; i < (int)eval.puntos->size(); ++i) {
        Punto punto = (*eval.puntos)[i];
        if (punto.codigo_tema == codigo_tema) {
            cout << "Punto encontrado:" << endl;
            cout << "  Porcentaje: " << punto.porcentaje << endl;
            cout << "  Código del tema: " << punto.codigo_tema << endl;
            return;
        }
    }

    cout << "Punto no encontrado con el código de tema: " << codigo_tema << endl;
}
