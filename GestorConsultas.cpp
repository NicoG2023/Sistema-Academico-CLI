#include "GestorConsultas.h"
using namespace std;

GestorConsultas::GestorConsultas(GestorProfesores& gestorProfesores, GestorEstudiantes& gestorEstudiantes, GestorClases& gestorClases)
    : gestorProfesores(gestorProfesores), gestorEstudiantes(gestorEstudiantes), gestorClases(gestorClases) {}


void GestorConsultas::consultaPromedioEstudiante(int IDEstudiante, const std::string& materia, Profesor& profesor) {
    // Se busca si el estudiante existe
    Estudiante* estudiante = gestorEstudiantes.buscarEstudiantePorID(IDEstudiante);
    if (!estudiante) {
        std::cout << "Estudiante no encontrado." << std::endl;
        return;
    }
    // Se busca la clase que dicta el profesor
    Clases* clase = gestorClases.buscarClases(profesor.cedula);
    if (!clase) {
        std::cout << "Clase no encontrada para el profesor con c�dula: " << profesor.cedula << std::endl;
        return;
    }
    // Se busca la materia dentro de la clase
    Materias* mate = clase->buscarMaterias(materia);
    if (!mate) {
        std::cout << "Materia no encontrada: " << materia << std::endl;
        return;
    }
    if(mate->buscarEstudianteMatriculado(IDEstudiante)){
    	mate->calcularPromedioEstudiante(IDEstudiante, profesor);
    	cout<<"pasa por aca"<<endl;
    	mate->comportamientoEnTemas(IDEstudiante,profesor);
	}else{
		cout << "Estudiante no matriculado en la materia"<<endl;
		return;
	}
    
}



void GestorConsultas::consultaComportamientoPromedioCurso(const std::string& materia) {
	Clases* clase = NULL;
    Profesor* profesor = NULL;

    // Buscar la clase que tiene esta materia
    NodoArbolAVL<Clases>* rootClases = gestorClases.getRootClases();
    pila<NodoArbolAVL<Clases>*> stackClases;

    if (rootClases != NULL) {
        stackClases.Push(rootClases);
    }

    while (!stackClases.PilaVacia()) {
        NodoArbolAVL<Clases>* nodoClase = stackClases.Top();
        stackClases.Pop();

        if (nodoClase->value.buscarMaterias(materia) != NULL) {
            clase = &nodoClase->value;
            break;
        }

        if (nodoClase->left != NULL) {
            stackClases.Push(nodoClase->left);
        }
        if (nodoClase->right != NULL) {
            stackClases.Push(nodoClase->right);
        }
    }

    if (clase == NULL) {
        std::cout << "Materia no encontrada: " << materia << std::endl;
        return;
    }

    // Buscar el profesor que dicta esta clase
    NodoArbolAVL<Profesor>* rootProfesores = gestorProfesores.profesores.getRoot();
    pila<NodoArbolAVL<Profesor>*> stackProfesores;

    if (rootProfesores != NULL) {
        stackProfesores.Push(rootProfesores);
    }

    while (!stackProfesores.PilaVacia()) {
        NodoArbolAVL<Profesor>* nodoProfesor = stackProfesores.Top();
        stackProfesores.Pop();

        if (nodoProfesor->value.cedula == clase->codigo_profesor) {
            profesor = &nodoProfesor->value;
            break;
        }

        if (nodoProfesor->left != NULL) {
            stackProfesores.Push(nodoProfesor->left);
        }
        if (nodoProfesor->right != NULL) {
            stackProfesores.Push(nodoProfesor->right);
        }
    }

    if (profesor == NULL) {
        std::cout << "Profesor no encontrado para la clase de la materia: " << materia << std::endl;
        return;
    }

    // Llamar al m�todo calcularComportamientoPromedioCurso de Materias
    Materias* mate = clase->buscarMaterias(materia);
    if (mate == NULL) {
        std::cout << "Materia no encontrada en la clase." << std::endl;
        return;
    }
    
    cout<<"Profesor es: "<<profesor->nombre<<endl;
    cout<<"materia en: "<<mate->materia << " cuyo tam es: "<<mate->estudiantes.size()<<endl;

    mate->comportamientoGeneralEnTemas(*profesor);
}


void GestorConsultas::consultaComportamientoPromedioProfesor(int codigoProfesor) {
    Clases* clase = gestorClases.buscarClases(codigoProfesor);
    if (!clase) {
        std::cout << "No se encontraron clases para el profesor con c�digo: " << codigoProfesor << std::endl;
        return;
    }

    clase->comportamientoPromedioPorTemas(gestorProfesores);
}

void GestorConsultas::consultaProfesoresPorClases(int numeroClases) {
    gestorClases.consultarProfesoresPorNumeroClases(numeroClases);
}

void GestorConsultas::consultaEstudiantesPorNota(double notaDada, const std::string& tema) {
    Lista<InformacionNota> estudiantesConNotaMayor;  // Lista para almacenar informaci�n de notas superiores a notaDada

    const ArbolAVL<Clases>& clasesAVL = gestorClases.getClases();
    for (unsigned int i = 0; i < clasesAVL.size(); i++) {
        const Clases& clase = clasesAVL.obtainByReference(i);

        Profesor* profesor = gestorProfesores.buscarProfesores(clase.codigo_profesor);
        if (profesor) {
            for (unsigned int j = 0; j < clase.clasesProfesor->size(); j++) {
                Materias& materia = clase.clasesProfesor->obtainByReference(j);

                int codigoTema = -1;
                for (unsigned int k = 0; k < materia.temas.size(); k++) {
                    Temas& temaActual = materia.temas.obtainByReference(k);
                    if (temaActual.tema == tema) {
                        codigoTema = temaActual.codigo_tema;
                        break;
                    }
                }

                if (codigoTema != -1) {
                    for (unsigned int m = 0; m < materia.cortes.size(); m++) {
                        std::string nombreCorte = materia.cortes.obtainByReference(m);
                        Corte* corte = profesor->buscarCorte(nombreCorte);
                        if (corte) {
                            for (unsigned int n = 0; n < corte->evaluaciones->size(); n++) {
                                Evaluacion& evaluacion = corte->evaluaciones->obtainByReference(n);

                                for (unsigned int p = 0; p < evaluacion.puntos->size(); p++) {
                                    Punto& punto = evaluacion.puntos->obtainByReference(p);

                                    if (punto.codigo_tema == codigoTema) {
                                        for (unsigned int q = 0; q < punto.notas->size(); q++) {
                                            Nota& nota = punto.notas->obtainByReference(q);
                                            if (nota.valor > notaDada) {
                                                Estudiante* estudiante = gestorEstudiantes.buscarEstudiantePorID(nota.IDEstudiante);
                                                if (estudiante) {
                                                    InformacionNota infoNota(estudiante->IDEstudiante, estudiante->nombre, evaluacion.nombre, punto.porcentaje, punto.codigo_tema, nota.valor);
                                                    estudiantesConNotaMayor.insertar_final(infoNota);
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    if (estudiantesConNotaMayor.lista_vacia()) {
        std::cout << "No hay estudiantes con notas mayores a " << notaDada << " en el tema " << tema << "." << std::endl;
    } else {
        std::cout << "Estudiantes con notas mayores a " << notaDada << " en el tema " << tema << ":" << std::endl;
        for (unsigned int i = 1; i <= estudiantesConNotaMayor.getTam(); i++) {
            InformacionNota infoNota = estudiantesConNotaMayor.buscar_nodo(i);
            std::cout << "ID: " << infoNota.idEstudiante << ", Nombre: " << infoNota.nombreEstudiante
                      << ", Evaluaci�n: " << infoNota.nombreEvaluacion << ", Punto: " << infoNota.porcentaje
                      << "%, Nota: " << infoNota.valorNota << std::endl;
        }
    }
}










