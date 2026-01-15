#ifndef CORTES_DE_NOTAS_H
#define CORTES_DE_NOTAS_H

#include "ArbolAVL.h"
#include "Corte.h"
using namespace std;

class CortesDeNotas {
public:
    ArbolAVL<Corte*>* cortes = NULL;

    CortesDeNotas(); // Constructor
    ~CortesDeNotas(); // Destructor

    void agregarCorte(const string& tipo_evaluacion, int porcentaje);
    void agregarEvaluacion(const string& tipo_evaluacion, const string& nombreEvaluacion);
    void agregarPunto(const string& tipo_evaluacion, const string& nombreEvaluacion, int porcentajePunto, int codigo_tema);
    void eliminarCorte(const string& tipo_evaluacion);
    void eliminarEvaluacion(const string& tipo_evaluacion, const string& nombreEvaluacion);
    void eliminarPunto(const string& tipo_evaluacion, const string& nombreEvaluacion, int porcentajePunto, int codigo_tema);
    void buscarCorte(const string& tipo_evaluacion);
    void buscarEvaluacion(const string& tipo_evaluacion, const string& nombreEvaluacion);
    void buscarPunto(const string& tipo_evaluacion, const string& nombreEvaluacion, int codigo_tema);
};

#endif // CORTES_DE_NOTAS_H

