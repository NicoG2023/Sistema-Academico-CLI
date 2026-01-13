#include "Materias.h"
#include <vector>
#include <sstream>
using namespace std;


Materias::Materias(const string& materia) : materia(materia), archivos(new ArbolAVL<Archivos>()) {
    // Inicialización adicional si es necesario
}

Materias::Materias(){
	
}

Materias::~Materias() {
    delete archivos; // Liberar la memoria del puntero
}

// Constructor de copia
Materias::Materias(const Materias& other) 
    : materia(other.materia), 
      temas(other.temas), 
      archivos(new ArbolAVL<Archivos>(*other.archivos)), 
      cortes(other.cortes), 
      estudiantes(other.estudiantes) {
    // Constructor de copia que realiza una copia profunda de los datos
}

// Operador de asignación
Materias& Materias::operator=(const Materias& other) {
    if (this == &other) {
        return *this; // Manejar autoasignación
    }

    // Liberar memoria existente
    delete archivos;

    // Copiar los datos del otro objeto
    materia = other.materia;
    temas = other.temas;
    archivos = new ArbolAVL<Archivos>(*other.archivos); // Copia profunda
    cortes = other.cortes;
    estudiantes = other.estudiantes;

    return *this;
}

void Materias::agregarTema(int codigo_tema, const string& tema) {
    temas.insert(Temas(codigo_tema, tema));
    std::cout << "Tema: " << tema << " agregado correctamente." << std::endl;
}

void Materias::agregarArchivo(const string& nombreArchivo) {
    if (archivos != NULL) {
        archivos->insert(Archivos(nombreArchivo));
        cout << "Archivo " << nombreArchivo << " agregado exitosamente" << endl;
    }
}

void Materias::matricularEstudiante(int IDEstudiante, GestorEstudiantes& gestorEstudiantes) {
    if (!gestorEstudiantes.estudianteExiste(IDEstudiante)) {
        std::cout << "Error: El estudiante con ID " << IDEstudiante << " no existe en el sistema." << std::endl;
        return;
    }

    if (estudiantes.find(IDEstudiante) != -1) {
        std::cout << "Error: El estudiante con ID " << IDEstudiante << " ya está matriculado en la materia " << materia << std::endl;
        return;
    }
    
    estudiantes.insert(IDEstudiante);
    std::cout << "Estudiante con ID " << IDEstudiante << " matriculado en la materia " << materia << " exitosamente." << std::endl;
}

void Materias::desmatricularEstudiante(int IDEstudiante) {
    if (estudiantes.find(IDEstudiante) == -1) {
        std::cout << "Error: El estudiante con ID " << IDEstudiante << " no está matriculado en la materia " << materia << std::endl;
        return;
    }
    estudiantes.eraseOther(IDEstudiante);
    std::cout << "Estudiante con ID " << IDEstudiante << " desmatriculado de la materia " << materia << " exitosamente." << std::endl;
}

bool Materias::buscarEstudianteMatriculado(int IDEstudiante){
	return estudiantes.find(IDEstudiante) != -1;
}

void Materias::vincularCorte(const string& nombreCorte, int profesorID, GestorProfesores& gestorProfesores) {
    Profesor* profe = gestorProfesores.buscarProfesores(profesorID);
    if (!profe) {
        std::cout << "Profesor no encontrado" << std::endl;
        return;
    }
	
    Corte* corte = profe->buscarCorte(nombreCorte);
    if (!corte) {
        std::cout << "Corte no encontrado: su nombre es "<<nombreCorte << std::endl;
        return;
    }

    // Calcular la suma de los porcentajes de los cortes existentes
    int sumaPorcentajes = 0;
    for (int i = 0; i < cortes.size(); ++i) {
        std::string nombreCorteExistente = cortes.obtainByReference(i);
        Corte* corteExistente = profe->buscarCorte(nombreCorteExistente);
        if (corteExistente) {
            sumaPorcentajes += corteExistente->porcentaje;
        }
    }

    // Verificar si la suma de los porcentajes con el nuevo corte excede el 100%
    if (sumaPorcentajes + corte->porcentaje > 100) {
        std::cout << "Error: La suma de los porcentajes de los cortes excede el 100%" << std::endl;
        return;
    }

    // Insertar el nuevo corte si no excede el 100%
    if (cortes.find(nombreCorte) == -1) {
        cortes.insert(nombreCorte);
        std::cout << "Corte vinculado exitosamente." << std::endl;
    } else {
        std::cout << "Corte anteriormente vinculado" << std::endl;
    }
}

void Materias::desvincularCorte(const string& nombreCorte) {
    if (cortes.find(nombreCorte) == -1) {
        std::cout << "Error: El corte " << nombreCorte << " no está registrado en la materia " << materia << std::endl;
        return;
    }

    cortes.eraseOther(nombreCorte);
    std::cout << "Corte " << nombreCorte << " desvinculado de la materia " << materia << " exitosamente." << std::endl;
}

string Materias::buscarCorte(const string& tipo_evaluacion) {
    int idx = cortes.find(tipo_evaluacion);
    if (idx == -1) {
        std::cout << "Error: El corte " << tipo_evaluacion << " no está registrado en la materia " << materia << std::endl;
        return "";
    }
    return cortes.obtainByReference(idx);
}

void Materias::agregarNota(const std::string& nombreCorte, const std::string& nombreEvaluacion, int porcentaje, int codigo_tema, int IDEstudiante, double valor, Profesor& profesor) {
    // Verificar si el estudiante está matriculado
    if (!buscarEstudianteMatriculado(IDEstudiante)) {
        std::cout << "El estudiante con ID " << IDEstudiante << " no está matriculado en la materia." << std::endl;
        return;
    }

    // Buscar el corte
    Corte* corte = profesor.buscarCorte(nombreCorte);
    if (!corte) {
        std::cout << "Corte no encontrado: " << nombreCorte << std::endl;
        return;
    }

    // Agregar la nota a la evaluación
    corte->agregarNota(nombreEvaluacion, porcentaje, codigo_tema, IDEstudiante, valor);
    std::cout << "Nota agregada exitosamente para el estudiante con ID " << IDEstudiante << std::endl;
}

void Materias::listarCortes() {
    cortes.display();
}

void Materias::listarTemas(){
	temas.display();
}

void Materias::listarEstudiantes() {
    estudiantes.display();
}

void Materias::eliminarTema(int codigo_tema) {
    temas.erase(Temas(codigo_tema, ""));
    std::cout << "Tema con código " << codigo_tema << " eliminado correctamente." << std::endl;
}

void Materias::eliminarArchivo(const string& nombreArchivo) {
    if (archivos != NULL) {
        archivos->erase(Archivos(nombreArchivo));
        cout << "Archivo " << nombreArchivo << " eliminado exitosamente" << endl;
    }
}

double Materias::calcularPromedioEstudiante(int IDEstudiante, Profesor& profesor) {
    double sumaNotas = 0.0;
    int totalEvaluaciones = 0;

    std::cout << std::endl << "Calculando promedio del estudiante con ID " << IDEstudiante << " en la materia " << materia << std::endl;

    for (unsigned int i = 0; i < cortes.size(); ++i) {
    	cout<<"entra al for"<<endl;
        std::string corteNombre = cortes.obtainByReference(i);

        std::cout << "Revisando corte: " << corteNombre << std::endl;
        Corte* corte = profesor.buscarCorte(corteNombre);
        if (corte == NULL) {
            std::cerr << "Corte no encontrado: " << corteNombre << std::endl;
            continue;
        }

        for (unsigned int j = 0; j < corte->evaluaciones->size(); ++j) {
            Evaluacion& evaluacion = corte->evaluaciones->obtainByReference(j);
            std::cout << "Evaluacion encontrada: " << evaluacion.nombre << std::endl;

            for (unsigned int k = 0; k < evaluacion.puntos->size(); ++k) {
                Punto& punto = evaluacion.puntos->obtainByReference(k);
                std::cout << "Punto encontrado: " << punto.porcentaje << std::endl;

                std::cout << "Buscando nota del estudiante con ID " << IDEstudiante << " en el punto" << std::endl;
                Nota* nota = punto.buscarNota(IDEstudiante);
                if (nota != NULL) {
                    std::cout << "Nota encontrada, estudiante ID: " << nota->IDEstudiante << ", valor: " << nota->valor << std::endl;
                    sumaNotas += nota->valor;
                    ++totalEvaluaciones;
                } else {
                    std::cout << "Nota no encontrada para el estudiante con ID " << IDEstudiante << std::endl;
                }
            }
        }
    }

    return totalEvaluaciones > 0 ? sumaNotas / totalEvaluaciones : 0.0;
}

void Materias::comportamientoEnTemas(int IDEstudiante, Profesor& profesor) {
    std::cout << "Calculando el comportamiento del estudiante con ID " << IDEstudiante << " en los temas:" << std::endl;

    // Recorrer todos los cortes de la materia
    for (unsigned int i = 0; i < cortes.size(); ++i) {
        std::string corteNombre = cortes.obtainByReference(i);
        Corte* corte = profesor.buscarCorte(corteNombre);

        if (corte != NULL) {
            std::cout << "Revisando corte: " << corte->nombre << std::endl;

            // Recorrer todas las evaluaciones del corte
            for (unsigned int j = 0; j < corte->evaluaciones->size(); ++j) {
                Evaluacion& evaluacion = corte->evaluaciones->obtainByReference(j);
                std::cout << "  Evaluacion: " << evaluacion.nombre << std::endl;

                // Recorrer todos los puntos de la evaluación
                for (unsigned int k = 0; k < evaluacion.puntos->size(); ++k) {
                    Punto& punto = evaluacion.puntos->obtainByReference(k);
                    std::cout << "    Punto: " << punto.codigo_tema << " (" << punto.porcentaje << "%)" << std::endl;

                    // Buscar la nota del estudiante en este punto
                    Nota* nota = punto.buscarNota(IDEstudiante);
                    if (nota != NULL) {
                        // Buscar el nombre del tema en el árbol de temas
                        std::string temaNombre = "Tema no encontrado";
                        for (unsigned int t = 0; t < temas.size(); ++t) {
                            Temas& tema = temas.obtainByReference(t);
                            if (tema.codigo_tema == punto.codigo_tema) {
                                temaNombre = tema.tema;
                                break;
                            }
                        }

                        std::string veredicto;
                        if (nota->valor < 3.0) {
                            veredicto = "bajo";
                        } else if (nota->valor >= 3.0 && nota->valor <= 3.8) {
                            veredicto = "medio";
                        } else {
                            veredicto = "alto";
                        }

                        std::cout << "      Tema: " << temaNombre << ", Nota: " << nota->valor << ", Comportamiento: " << veredicto << std::endl;
                    } else {
                        std::cout << "      Nota no encontrada para el estudiante con ID " << IDEstudiante << std::endl;
                    }
                }
            }
        } else {
            std::cout << "Corte no encontrado: " << corteNombre << std::endl;
        }
    }
}

void Materias::comportamientoGeneralEnTemas(Profesor& profesor){
    std::cout << "Profesor en materia es: " << profesor.nombre << std::endl;
    std::cout << "La materia es: " << materia << std::endl;

    if (estudiantes.empty()) {
        std::cout << "No hay estudiantes matriculados en la materia" << std::endl;
        return;
    }

    const int MAX_TEMAS = 100;
    struct TemaPromedio {
        double sumaNotas;
        int conteoNotas;
    };

    TemaPromedio temasPromedios[MAX_TEMAS] = {};

    for (unsigned int i = 0; i < estudiantes.size(); ++i) {
        int IDEstudiante = estudiantes.obtainByReference(i);

        pila<NodoArbolAVL<std::string>*> stackCortes;
        if (cortes.getRoot() != NULL) {
            stackCortes.Push(cortes.getRoot());
        }

        while (!stackCortes.PilaVacia()) {
            NodoArbolAVL<std::string>* currentCorte = stackCortes.Top();
            stackCortes.Pop();

            std::string corteNombre = currentCorte->value;
            Corte* corte = profesor.buscarCorte(corteNombre);

            if (corte != NULL) {
                pila<NodoArbolAVL<Evaluacion>*> stackEvaluaciones;
                if (corte->evaluaciones->getRoot() != NULL) {
                    stackEvaluaciones.Push(corte->evaluaciones->getRoot());
                }

                while (!stackEvaluaciones.PilaVacia()) {
                    NodoArbolAVL<Evaluacion>* currentEvaluacion = stackEvaluaciones.Top();
                    stackEvaluaciones.Pop();

                    Evaluacion& evaluacion = currentEvaluacion->value;

                    pila<NodoArbolAVL<Punto>*> stackPuntos;
                    if (evaluacion.puntos->getRoot() != NULL) {
                        stackPuntos.Push(evaluacion.puntos->getRoot());
                    }

                    while (!stackPuntos.PilaVacia()) {
                        NodoArbolAVL<Punto>* currentPunto = stackPuntos.Top();
                        stackPuntos.Pop();

                        Punto& punto = currentPunto->value;
                        Nota* nota = punto.buscarNota(IDEstudiante);
                        if (nota != NULL) {
                            int codigoTema = punto.codigo_tema;
                            double valorNota = nota->valor;

                            if (codigoTema < MAX_TEMAS) {
                                temasPromedios[codigoTema].sumaNotas += valorNota;
                                temasPromedios[codigoTema].conteoNotas++;
                            } else {
                                std::cout << "Error: Código de tema " << codigoTema << " fuera de rango" << std::endl;
                            }
                        }

                        if (currentPunto->right != NULL) {
                            stackPuntos.Push(currentPunto->right);
                        }
                        if (currentPunto->left != NULL) {
                            stackPuntos.Push(currentPunto->left);
                        }
                    }

                    if (currentEvaluacion->right != NULL) {
                        stackEvaluaciones.Push(currentEvaluacion->right);
                    }
                    if (currentEvaluacion->left != NULL) {
                        stackEvaluaciones.Push(currentEvaluacion->left);
                    }
                }
            } else {
                std::cout << "Corte no encontrado: " << corteNombre << std::endl;
            }

            if (currentCorte->right != NULL) {
                stackCortes.Push(currentCorte->right);
            }
            if (currentCorte->left != NULL) {
                stackCortes.Push(currentCorte->left);
            }
        }
    }

    std::cout << "Promedio de comportamiento en los temas:" << std::endl;
    for (int i = 0; i < MAX_TEMAS; ++i) {
        if (temasPromedios[i].conteoNotas > 0) {
            double promedio = temasPromedios[i].sumaNotas / temasPromedios[i].conteoNotas;
            std::string veredicto = (promedio >= 3.8) ? "Alto" : (promedio >= 3.0) ? "Medio" : "Bajo";

            std::string temaNombre = "Tema no encontrado";
            for (unsigned int t = 0; t < temas.size(); ++t) {
                Temas& tema = temas.obtainByReference(t);
                if (tema.codigo_tema == i) {
                    temaNombre = tema.tema;
                    break;
                }
            }

            std::cout << "Tema: " << temaNombre << ", Promedio: " << promedio << ", Comportamiento: " << veredicto << std::endl;
        }
    }
}


struct InformacionPunto {
    int codigoTema;
    double sumaNotas;
    int cantidadNotas;

    InformacionPunto() : codigoTema(0), sumaNotas(0), cantidadNotas(0) {}
    InformacionPunto(int tema, double suma, int cantidad) : codigoTema(tema), sumaNotas(suma), cantidadNotas(cantidad) {}
};

void Materias::generarArchivosParciales(GestorProfesores& gestorProfesores, int profesorID) {
    Lista<InformacionPunto> listaPromedios[100]; // Suponiendo un máximo de 100 parciales

    Profesor* profesor = gestorProfesores.buscarProfesores(profesorID);
    if (!profesor) {
        std::cout << "Profesor no encontrado" << std::endl;
        return;
    }

    pila<NodoArbolAVL<std::string>*> stackCortes;
    if (cortes.getRoot()) stackCortes.Push(cortes.getRoot());

    // Recorrer todos los cortes utilizando DFS
    while (!stackCortes.PilaVacia()) {
        NodoArbolAVL<std::string>* nodoCorte = stackCortes.Pop();
        std::string nombreCorte = nodoCorte->value;

        Corte* corte = profesor->buscarCorte(nombreCorte);

        if (corte) {
            pila<NodoArbolAVL<Evaluacion>*> stackEvaluaciones;
            if (corte->evaluaciones->getRoot()) stackEvaluaciones.Push(corte->evaluaciones->getRoot());

            // Recorrer todas las evaluaciones del corte utilizando DFS
            while (!stackEvaluaciones.PilaVacia()) {
                NodoArbolAVL<Evaluacion>* nodoEvaluacion = stackEvaluaciones.Pop();
                Evaluacion& evaluacion = nodoEvaluacion->value;

                // Verificar si el nombre de la evaluación contiene "Parcial"
                if (evaluacion.nombre.find("Parcial") != std::string::npos) {
                    // Extraer el número del parcial
                    std::string numeroParcialStr = evaluacion.nombre.substr(evaluacion.nombre.find("Parcial") + 7);
                    int numeroParcial = atoi(numeroParcialStr.c_str());

                    pila<NodoArbolAVL<Punto>*> stackPuntos;
                    if (evaluacion.puntos->getRoot()) stackPuntos.Push(evaluacion.puntos->getRoot());

                    // Recorrer todos los puntos de la evaluación utilizando DFS
                    while (!stackPuntos.PilaVacia()) {
                        NodoArbolAVL<Punto>* nodoPunto = stackPuntos.Pop();
                        Punto& punto = nodoPunto->value;

                        double sumaNotas = 0;
                        int cantidadNotas = 0;

                        pila<NodoArbolAVL<Nota>*> stackNotas;
                        if (punto.notas->getRoot()) stackNotas.Push(punto.notas->getRoot());

                        // Recorrer todas las notas del punto utilizando DFS
                        while (!stackNotas.PilaVacia()) {
                            NodoArbolAVL<Nota>* nodoNota = stackNotas.Pop();
                            Nota& nota = nodoNota->value;

                            sumaNotas += nota.valor;
                            cantidadNotas++;

                            if (nodoNota->left) stackNotas.Push(nodoNota->left);
                            if (nodoNota->right) stackNotas.Push(nodoNota->right);
                        }

                        // Calcular el promedio de la pregunta
                        double promedio = (cantidadNotas > 0) ? (sumaNotas / cantidadNotas) : 0;

                        // Buscar si ya existe un punto con el mismo codigoTema en la lista de este parcial
                        bool encontrado = false;
                        for (int m = 1; m <= listaPromedios[numeroParcial].getTam(); ++m) {
                            InformacionPunto& info = listaPromedios[numeroParcial].buscar_nodoByReference(m);
                            if (info.codigoTema == punto.codigo_tema) {
                                info.sumaNotas += sumaNotas;
                                info.cantidadNotas += cantidadNotas;
                                encontrado = true;
                                break;
                            }
                        }

                        // Si no se encontró, añadir una nueva entrada
                        if (!encontrado) {
                            listaPromedios[numeroParcial].insertar_final(InformacionPunto(punto.codigo_tema, sumaNotas, cantidadNotas));
                        }

                        if (nodoPunto->left) stackPuntos.Push(nodoPunto->left);
                        if (nodoPunto->right) stackPuntos.Push(nodoPunto->right);
                    }
                }

                if (nodoEvaluacion->left) stackEvaluaciones.Push(nodoEvaluacion->left);
                if (nodoEvaluacion->right) stackEvaluaciones.Push(nodoEvaluacion->right);
            }
        }

        if (nodoCorte->left) stackCortes.Push(nodoCorte->left);
        if (nodoCorte->right) stackCortes.Push(nodoCorte->right);
    }

    // Generar archivos para cada parcial
    for (int i = 0; i < 100; ++i) {
        if (listaPromedios[i].getTam() > 0) {
            std::ostringstream filename;
            filename << "Parcial" << i << ".txt";
            std::ofstream outFile(filename.str().c_str());

            for (int j = 1; j <= listaPromedios[i].getTam(); ++j) {
                InformacionPunto& info = listaPromedios[i].buscar_nodoByReference(j);
                double promedio = (info.cantidadNotas > 0) ? (info.sumaNotas / info.cantidadNotas) : 0;
                outFile << "Pregunta " << info.codigoTema << ": " << promedio << std::endl;
            }

            outFile.close();
        }
    }
}

std::string intToString(int num) {
    std::stringstream ss;
    ss << num;
    return ss.str();
}

struct NodoPila {
    NodoArbolAVL<Punto>* nodo;
    int codigoTema;

    NodoPila() : nodo(NULL), codigoTema(0) {} // Constructor por defecto

    NodoPila(NodoArbolAVL<Punto>* n, int ct) : nodo(n), codigoTema(ct) {}
};


void Materias::subirParcial(const std::string& filename, GestorEstudiantes& gestorEstudiantes, int profesorID, GestorProfesores& gestorProfesores) {
    if (archivos->size() >= 3) {
        std::cout << "Error: No se pueden subir más de 3 parciales." << std::endl;
        return;
    }

    std::ifstream inFile(filename.c_str());
    if (!inFile.is_open()) {
        std::cout << "Error al abrir el archivo." << std::endl;
        return;
    }

    std::string linea;
    int numeroParcial;
    if (std::getline(inFile, linea)) {
        std::istringstream iss(linea);
        iss >> numeroParcial;
    } else {
        std::cout << "Error: Archivo vacío o formato incorrecto." << std::endl;
        return;
    }

    archivos->insert(filename);

    while (std::getline(inFile, linea)) {
        std::istringstream iss(linea);
        std::string nombreCompleto;
        double nota;
        Lista<double> notas;

        // Leer nombre completo del estudiante hasta el primer tabulador
        std::getline(iss, nombreCompleto, '\t');

        // Leer las notas separadas por tabuladores
        while (iss >> nota) {
            notas.insertar_final(nota);
        }

        Estudiante* estudiante = gestorEstudiantes.buscarEstudiantePorElNombre(nombreCompleto);
        if (!estudiante) {
            std::cout << "Estudiante no encontrado: " << nombreCompleto << std::endl;
            continue;
        }

        Profesor* profesor = gestorProfesores.buscarProfesores(profesorID);
        if (!profesor) {
            std::cout << "Profesor no encontrado" << std::endl;
            return;
        }

        std::string nombreCorte = "Parcial" + intToString(numeroParcial);
        Corte* corte = profesor->buscarCorte(nombreCorte);
        if (!corte) {
            std::cout << "Corte no encontrado: " << nombreCorte << std::endl;
            return;
        }

        // Buscar la evaluación dentro del corte
        Evaluacion* evaluacion = corte->buscarEvaluaciones("Examen Parcial " + intToString(numeroParcial));
        if (!evaluacion) {
            std::cout << "Evaluación no encontrada: " << "Examen Parcial " + intToString(numeroParcial) << std::endl;
            return;
        }

        // Recorrer el árbol de puntos y asignar las notas
        pila<NodoPila> pilaPuntos;
        NodoArbolAVL<Punto>* raiz = evaluacion->puntos->getRoot();

        if (raiz != NULL) {
            int codigoTema = 1;
            pilaPuntos.Push(NodoPila(raiz, codigoTema));

            while (!pilaPuntos.PilaVacia()) {
                NodoPila actual = pilaPuntos.Pop();
                NodoArbolAVL<Punto>* nodoActual = actual.nodo;

                if (nodoActual->right != NULL) {
                    pilaPuntos.Push(NodoPila(nodoActual->right, actual.codigoTema));
                }
                if (nodoActual->left != NULL) {
                    pilaPuntos.Push(NodoPila(nodoActual->left, actual.codigoTema));
                }

                if (actual.codigoTema <= notas.getTam()) {
                    double n = notas.buscar_nodo(actual.codigoTema);
                    corte->agregarNota(evaluacion->nombre, nodoActual->value.porcentaje, nodoActual->value.codigo_tema, estudiante->IDEstudiante, n);
                    actual.codigoTema++;
                }
            }
        } else {
            std::cout << "Error: No hay puntos en la evaluación " << evaluacion->nombre << std::endl;
        }
    }

    inFile.close();
    std::cout << "Parcial subido exitosamente." << std::endl;
}



