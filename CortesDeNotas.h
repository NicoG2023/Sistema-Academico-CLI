#ifndef CORTES_DE_NOTAS_H
#define CORTES_DE_NOTAS_H

#include <string>
#include "ArbolAVL.h"
#include "Corte.h"

class CortesDeNotas {
public:
    ArbolAVL<Corte*>* cortes;

    CortesDeNotas();
    ~CortesDeNotas();

    void agregarCorte(const std::string& tipo_evaluacion, int porcentaje);
    void agregarEvaluacion(const std::string& tipo_evaluacion, const std::string& nombreEvaluacion);
    void agregarPunto(const std::string& tipo_evaluacion, const std::string& nombreEvaluacion, int porcentajePunto, int codigo_tema);
    void eliminarCorte(const std::string& tipo_evaluacion);
    void eliminarEvaluacion(const std::string& tipo_evaluacion, const std::string& nombreEvaluacion);
    void eliminarPunto(const std::string& tipo_evaluacion, const std::string& nombreEvaluacion, int porcentajePunto, int codigo_tema);
    void buscarCorte(const std::string& tipo_evaluacion);
    void buscarEvaluacion(const std::string& tipo_evaluacion, const std::string& nombreEvaluacion);
    void buscarPunto(const std::string& tipo_evaluacion, const std::string& nombreEvaluacion, int codigo_tema);
};

#endif // CORTES_DE_NOTAS_H
