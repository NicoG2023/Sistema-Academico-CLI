#include "Corte.h"
using namespace std;

// Inserciones
void Corte::agregarEvaluacion(const string& nombreEvaluacion) {
    Evaluacion nuevaEvaluacion(nombreEvaluacion);
    nuevaEvaluacion.puntos = new ArbolAVL<Punto>();
    evaluaciones->insert(nuevaEvaluacion);
    std::cout << "Evaluacion " << nombreEvaluacion << " agregada exitosamente" << endl;
}

void Corte::agregarPunto(const string& nombreEvaluacion, int porcentajePunto, int codigo_tema) {
	Evaluacion* eval = buscarEvaluaciones(nombreEvaluacion);
	if(eval){
		int sumaPorcentajes = 0;
		for(int i = 0; i < eval->puntos->size(); ++i){
			Punto& puntoExistente = eval->puntos->obtainByReference(i);
			sumaPorcentajes += puntoExistente.porcentaje;
		}
		if(sumaPorcentajes + porcentajePunto > 100){
			cout << "Error: La suma de los porcentajes de los puntos excede el 100%" << endl;
            return;
		}else{
			eval->puntos->insert(Punto(porcentajePunto, codigo_tema));
        	cout << "Punto agregado exitosamente en evaluacion: " << eval->nombre << endl;
		}
	}else{
		cout<<"Evaluacion no encontrada."<<endl;
	}
}


void Corte::agregarNota(const string& nombreEvaluacion, int porcentajePunto, int codigo_tema, int IDEstudiante, double valor) {
    int idx = evaluaciones->find(Evaluacion(nombreEvaluacion));
    if (idx != -1) {
        Evaluacion& eval = evaluaciones->obtainByReference(idx);
        int idxPunto = eval.puntos->find(Punto(porcentajePunto, codigo_tema));
        if (idxPunto != -1) {
            Punto& punto = eval.puntos->obtainByReference(idxPunto);
            punto.notas->insert(Nota(valor, IDEstudiante));
        } else {
            cout << "Punto no encontrado en la evaluacion: " << nombreEvaluacion << " al intentar agregar nota" << endl;
        }
    } else {
        cout << "Evaluacion no encontrada: " << nombreEvaluacion << endl;
    }
}


// B�squedas

Evaluacion Corte::buscarEvaluacion(const string& nombreEvaluacion) {
    int idx = evaluaciones->find(Evaluacion(nombreEvaluacion));
    if (idx != -1) {
        return evaluaciones->obtainByReference(idx);
    } else {
        cout << "Evaluacion no encontrada: " << nombreEvaluacion << endl;
        return Evaluacion("");
    }
}

Punto Corte::buscarPunto(const string& nombreEvaluacion, int porcentajePunto, int codigo_tema) {
    int idx = evaluaciones->find(Evaluacion(nombreEvaluacion));
    if (idx != -1) {
        Evaluacion& eval = evaluaciones->obtainByReference(idx);
        int idxPunto = eval.puntos->find(Punto(porcentajePunto, codigo_tema));
        if (idxPunto != -1) {
            return eval.puntos->obtainByReference(idxPunto);
        } else {
            cout << "Punto no encontrado en la evaluacion: " << nombreEvaluacion << endl;
            return Punto(0, 0);
        }
    } else {
        cout << "Evaluacion no encontrada: " << nombreEvaluacion << endl;
        return Punto(0, 0);
    }
}

Nota Corte::buscarNota(const string& nombreEvaluacion, int porcentajePunto, int codigo_tema, int IDEstudiante) {
    int idx = evaluaciones->find(Evaluacion(nombreEvaluacion));
    if (idx != -1) {
        Evaluacion& eval = evaluaciones->obtainByReference(idx);
        int idxPunto = eval.puntos->find(Punto(porcentajePunto, codigo_tema));
        if (idxPunto != -1) {
            Punto& punto = eval.puntos->obtainByReference(idxPunto);
            int idxNota = punto.notas->find(Nota(IDEstudiante, 0.0));
            if (idxNota != -1) {
                return punto.notas->obtainByReference(idxNota);
            } else {
                cout << "Nota no encontrada para el estudiante con ID: " << IDEstudiante << endl;
                return Nota(0, 0.0);
            }
        } else {
            cout << "Punto no encontrado en la evaluacion: " << nombreEvaluacion << endl;
            return Nota(0, 0.0);
        }
    } else {
        cout << "Evaluacion no encontrada: " << nombreEvaluacion << endl;
        return Nota(0, 0.0);
    }
}

Evaluacion* Corte::buscarEvaluaciones(const std::string& nombreEvaluacion) {
    int idx = evaluaciones->find(Evaluacion(nombreEvaluacion));
    if (idx != -1) {
        return &evaluaciones->obtainByReference(idx);
    }
    return NULL;
}

// M�todo para buscar un punto en una evaluaci�n espec�fica por porcentaje y c�digo de tema
Punto* Corte::buscarPuntos(const std::string& nombreEvaluacion, int porcentajePunto, int codigo_tema) {
    Evaluacion* eval = buscarEvaluaciones(nombreEvaluacion);
    if (eval) {
        int idxPunto = eval->puntos->find(Punto(porcentajePunto, codigo_tema));
        if (idxPunto != -1) {
            return &eval->puntos->obtainByReference(idxPunto);
        }
    }
    return NULL;
}

// M�todo para buscar una nota en un punto espec�fico de una evaluaci�n espec�fica por ID de estudiante
Nota* Corte::buscarNotas(const std::string& nombreEvaluacion, int porcentajePunto, int codigo_tema, int IDEstudiante) {
    Punto* punto = buscarPuntos(nombreEvaluacion, porcentajePunto, codigo_tema);
    if (punto) {
        int idxNota = punto->notas->find(Nota(0.0, IDEstudiante));
        if (idxNota != -1) {
            return &punto->notas->obtainByReference(idxNota);
        }
    }
    return NULL;
}

// Eliminaciones

void Corte::eliminarNota(const string& nombreEvaluacion, int porcentajePunto, int codigo_tema, int IDEstudiante) {
    int idx = evaluaciones->find(Evaluacion(nombreEvaluacion));
    if (idx != -1) {
        Evaluacion& eval = evaluaciones->obtainByReference(idx);
        
        // Obtener el �ndice del punto
        int idxPunto = eval.puntos->find(Punto(porcentajePunto, codigo_tema));
        if (idxPunto != -1) {
            Punto& punto = eval.puntos->obtainByReference(idxPunto);
            punto.notas->erase(Nota(IDEstudiante, 0.0));
            
            // Actualizar el punto en la evaluaci�n
            eval.puntos->erase(Punto(porcentajePunto, codigo_tema));
            eval.puntos->insert(punto);
            
            // Actualizar la evaluaci�n en el corte
            evaluaciones->erase(Evaluacion(nombreEvaluacion));
            evaluaciones->insert(eval);
        } else {
            cout << "Punto no encontrado en la evaluacion: " << nombreEvaluacion << endl;
        }
    } else {
        cout << "Evaluacion no encontrada: " << nombreEvaluacion << endl;
    }
}

void Corte::eliminarEvaluacion(const string& nombreEvaluacion) {
    evaluaciones->erase(Evaluacion(nombreEvaluacion));
}

void Corte::eliminarPunto(const string& nombreEvaluacion, int porcentajePunto, int codigo_tema) {
    int idx = evaluaciones->find(Evaluacion(nombreEvaluacion));
    if (idx != -1) {
        Evaluacion& eval = evaluaciones->obtainByReference(idx);
        eval.puntos->erase(Punto(porcentajePunto, codigo_tema));
    } else {
        cout << "Evaluacion no encontrada: " << nombreEvaluacion << endl;
    }
}

void Corte::listarEvaluaciones() {
    evaluaciones->display();
}

void Corte::listarPuntos(const string& nombreEvaluacion) {
    int idx = evaluaciones->find(Evaluacion(nombreEvaluacion));
    if (idx != -1) {
        Evaluacion& eval = evaluaciones->obtainByReference(idx);
        cout << "Mostrando puntos en evaluacion: " << eval.nombre << endl;
        eval.puntos->display();
    } else {
        cout << "Evaluacion no encontrada: " << nombreEvaluacion << endl;
    }
}

void Corte::listarNotas(const string& nombreEvaluacion, int porcentajePunto, int codigo_tema) {
    int idx = evaluaciones->find(Evaluacion(nombreEvaluacion));
    if (idx != -1) {
        Evaluacion& eval = evaluaciones->obtainByReference(idx);
        int idxPunto = eval.puntos->find(Punto(porcentajePunto, codigo_tema));
        if (idxPunto != -1) {
            Punto& punto = eval.puntos->obtainByReference(idxPunto);
            punto.notas->display();
        } else {
            cout << "Punto no encontrado en la evaluacion: " << nombreEvaluacion << endl;
        }
    } else {
        cout << "Evaluacion no encontrada: " << nombreEvaluacion << endl;
    }
}
