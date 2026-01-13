#include "Profesor.h"
using namespace std;

Profesor::Profesor(int cedula, const std::string& nombre, const std::string& apellido, const std::string& email, const std::string& telefono, int clases_asignadas)
    : cedula(cedula), nombre(nombre), apellido(apellido), email(email), telefono(telefono), clases_asignadas(clases_asignadas) {}

Profesor::~Profesor() {
    for (int i = 0; i < cortes.size(); i++) {
        Corte& corte = cortes.obtainByReference(i);
        delete corte.evaluaciones;
    }
}

void Profesor::agregarCorte(const std::string& tipo_evaluacion, int porcentaje) {
    Corte nuevoCorte(tipo_evaluacion, porcentaje);
    cortes.insert(nuevoCorte);
    std::cout << "Corte " << tipo_evaluacion << " agregado exitosamente" << std::endl;
}


void Profesor::eliminarCorte(const std::string& tipo_evaluacion) {
    int idx = cortes.find(Corte(tipo_evaluacion, 0)); // El porcentaje no es relevante para la eliminación
    if (idx != -1) {
        Corte& corte = cortes.obtainByReference(idx);
        delete corte.evaluaciones;
        cortes.erase(Corte(tipo_evaluacion, 0));
    }
}

Corte* Profesor::buscarCorte(const std::string& tipo_evaluacion) {
    int idx = cortes.find(Corte(tipo_evaluacion, 0));
    if (idx == -1) {
        cout<<"Corte no encontrado. su nombre es: "<<tipo_evaluacion<<endl;
        return NULL;
    }
    return &cortes.obtainByReference(idx);
}

bool Profesor::modificarCorte(const string& nombreCorte, int nuevoPorcentaje, const string& nuevoNombreCorte) {
    Corte* corte = buscarCorte(nombreCorte);
    if (corte) {
        for (int i = 0; i < corte->evaluaciones->size(); i++) {
            Evaluacion& evaluacion = corte->evaluaciones->obtainByReference(i);
            for (int j = 0; j < evaluacion.puntos->size(); j++) {
                Punto& punto = evaluacion.puntos->obtainByReference(j);
                if (!punto.notas->empty()) {
                    cout << "No se puede modificar el corte porque ya tiene notas registradas." << endl;
                    return false;
                }
            }
        }
        corte->porcentaje = nuevoPorcentaje;
        corte->nombre = nuevoNombreCorte;
        return true;
    } else {
        cout << "Corte no encontrado: " << nombreCorte << endl;
        return false;
    }
}

bool Profesor::modificarEvaluacion(const string& nombreCorte, const string& nombreEvaluacion, const string& nuevoNombreEvaluacion) {
    Corte* corte = buscarCorte(nombreCorte);
    if (corte) {
        int idx = corte->evaluaciones->find(Evaluacion(nombreEvaluacion));
        if (idx != -1) {
            Evaluacion& evaluacion = corte->evaluaciones->obtainByReference(idx);
            for (int j = 0; j < evaluacion.puntos->size(); j++) {
                Punto& punto = evaluacion.puntos->obtainByReference(j);
                if (!punto.notas->empty()) {
                    cout << "No se puede modificar la evaluación porque ya tiene notas registradas." << endl;
                    return false;
                }
            }
            evaluacion.nombre = nuevoNombreEvaluacion;
            return true;
        } else {
            cout << "Evaluación no encontrada: " << nombreEvaluacion << endl;
            return false;
        }
    } else {
        cout << "Corte no encontrado: " << nombreCorte << endl;
        return false;
    }
}

bool Profesor::modificarPunto(const string& nombreCorte, const string& nombreEvaluacion, int porcentajePunto, int codigo_tema, int nuevoPorcentaje, int nuevoCodigoTema) {
    Corte* corte = buscarCorte(nombreCorte);
    if (corte) {
        int idx = corte->evaluaciones->find(Evaluacion(nombreEvaluacion));
        if (idx != -1) {
            Evaluacion& evaluacion = corte->evaluaciones->obtainByReference(idx);
            int idxPunto = evaluacion.puntos->find(Punto(porcentajePunto, codigo_tema));
            if (idxPunto != -1) {
                Punto& punto = evaluacion.puntos->obtainByReference(idxPunto);
                if (punto.notas->empty()) {
                    punto.porcentaje = nuevoPorcentaje;
                    punto.codigo_tema = nuevoCodigoTema;
                    return true;
                } else {
                    cout << "El punto ya tiene notas registradas, no se puede modificar." << endl;
                    return false;
                }
            } else {
                cout << "Punto no encontrado en la evaluación: " << nombreEvaluacion << endl;
                return false;
            }
        } else {
            cout << "Evaluación no encontrada: " << nombreEvaluacion << endl;
            return false;
        }
    } else {
        cout << "Corte no encontrado: " << nombreCorte << endl;
        return false;
    }
}

bool Profesor::cambiarEvaluacionDeCorte(const string& nombreEvaluacion, const string& nombreCorteOrigen, const string& nombreCorteDestino) {
    Corte* corteOrigen = buscarCorte(nombreCorteOrigen);
    Corte* corteDestino = buscarCorte(nombreCorteDestino);

    if (corteOrigen && corteDestino) {
        int idx = corteOrigen->evaluaciones->find(Evaluacion(nombreEvaluacion));
        if (idx != -1) {
            Evaluacion& evaluacion = corteOrigen->evaluaciones->obtainByReference(idx);
            for (int j = 0; j < evaluacion.puntos->size(); j++) {
                Punto& punto = evaluacion.puntos->obtainByReference(j);
                if (!punto.notas->empty()) {
                    cout << "No se puede cambiar la evaluación de corte porque ya tiene notas registradas." << endl;
                    return false;
                }
            }
            corteOrigen->evaluaciones->erase(evaluacion);
            corteDestino->evaluaciones->insert(evaluacion);
            return true;
        } else {
            cout << "Evaluación no encontrada en el corte de origen: " << nombreEvaluacion << endl;
            return false;
        }
    } else {
        if (!corteOrigen) {
            cout << "Corte de origen no encontrado: " << nombreCorteOrigen << endl;
        }
        if (!corteDestino) {
            cout << "Corte de destino no encontrado: " << nombreCorteDestino << endl;
        }
        return false;
    }
}


