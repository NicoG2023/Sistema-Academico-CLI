#include "GestorArchivos.h"
using namespace std;

GestorArchivos::GestorArchivos(GestorProfesores& gp, GestorEstudiantes& ge, GestorClases& gc)
    : gestorProfesores(gp), gestorEstudiantes(ge), gestorClases(gc) {
}

void GestorArchivos::guardarDatos(const std::string& archivo) {
    std::ofstream outFile(archivo.c_str(), std::ios::out | std::ios::trunc);

    if (!outFile) {
        std::cerr << "Error al abrir el archivo para escribir." << std::endl;
        return;
    }

    std::stringstream buffer;
    std::stringstream bufferCortesVinculados;

    // Guardar profesores
    for (int i = 0; i < gestorProfesores.profesores.size(); ++i) {
        Profesor& profesor = gestorProfesores.profesores.obtainByReference(i);
        buffer << "PROFESOR," << profesor.cedula << "," << profesor.nombre << "," << profesor.apellido << ","
               << profesor.email << "," << profesor.telefono << "," << profesor.clases_asignadas << std::endl;
    }

    // Guardar estudiantes
    for (int i = 0; i < gestorEstudiantes.getEstudiantes().size(); ++i) {
        Estudiante& estudiante = gestorEstudiantes.getEstudiantes().obtainByReference(i);
        buffer << "ESTUDIANTE," << estudiante.IDEstudiante << "," << estudiante.nombre << std::endl;
    }

    // Guardar clases
    const ArbolAVL<Clases>& clasesAVL = gestorClases.getClases();
    for (int i = 0; i < clasesAVL.size(); ++i) {
        Clases& clase = clasesAVL.obtainByReference(i);
        buffer << "CLASE," << clase.codigo_profesor << std::endl;
    }

    // Guardar materias, sus temas, estudiantes matriculados y archivos
    for (int i = 0; i < clasesAVL.size(); ++i) {
        Clases& clase = clasesAVL.obtainByReference(i);

        for (int j = 0; j < clase.clasesProfesor->size(); ++j) {
            Materias& materia = clase.clasesProfesor->obtainByReference(j);
            buffer << "MATERIA," << clase.codigo_profesor << "," << materia.materia << std::endl;

            // Guardar temas
            for (int k = 0; k < materia.temas.size(); ++k) {
                Temas& tema = materia.temas.obtainByReference(k);
                buffer << "TEMA," << materia.materia << "," << clase.codigo_profesor << "," << tema.codigo_tema << ","
                       << tema.tema << std::endl;
            }

            // Guardar estudiantes matriculados
            for (int k = 0; k < materia.estudiantes.size(); ++k) {
                int IDEstudiante = materia.estudiantes.obtainByReference(k);
                buffer << "MATRICULA," << materia.materia << "," << clase.codigo_profesor << "," << IDEstudiante << std::endl;
            }

            // Guardar archivos
            for (int k = 0; k < materia.archivos->size(); ++k) {
            	Archivos Archivo = materia.archivos->obtainByReference(k);
            	string nombreArchivo = Archivo.nombreArchivo;
                buffer << "ARCHIVO," << materia.materia << "," << clase.codigo_profesor << "," << nombreArchivo << std::endl;
            }

            // Guardar cortes vinculados
            for (int k = 0; k < materia.cortes.size(); ++k) {
                std::string nombreCorte = materia.cortes.obtainByReference(k);
                bufferCortesVinculados << "CORTE_VINCULADO," << materia.materia << "," << clase.codigo_profesor << "," << nombreCorte << std::endl;
            }
        }
    }

    // Guardar cortes, evaluaciones, puntos y notas
    for (int i = 0; i < gestorProfesores.profesores.size(); ++i) {
        Profesor& profesor = gestorProfesores.profesores.obtainByReference(i);

        // Guardar cortes
        for (int j = 0; j < profesor.cortes.size(); ++j) {
            Corte& corte = profesor.cortes.obtainByReference(j);
            buffer << "CORTE," << profesor.cedula << "," << corte.nombre << "," << corte.porcentaje << std::endl;

            // Guardar evaluaciones
            for (int k = 0; k < corte.evaluaciones->size(); ++k) {
                Evaluacion& eval = corte.evaluaciones->obtainByReference(k);
                buffer << "EVALUACION," << profesor.cedula << "," << corte.nombre << "," << eval.nombre << std::endl;

                // Guardar puntos
                for (int l = 0; l < eval.puntos->size(); ++l) {
                    Punto& punto = eval.puntos->obtainByReference(l);
                    buffer << "PUNTO," << profesor.cedula << "," << corte.nombre << "," << eval.nombre << ","
                           << punto.porcentaje << "," << punto.codigo_tema << std::endl;

                    // Guardar notas
                    for (int m = 0; m < punto.notas->size(); ++m) {
                        Nota& nota = punto.notas->obtainByReference(m);
                        buffer << "NOTA," << profesor.cedula << "," << corte.nombre << "," << eval.nombre << ","
                               << punto.porcentaje << "," << punto.codigo_tema << "," << nota.IDEstudiante << ","
                               << nota.valor << std::endl;
                    }
                }
            }
        }
    }

    // Primero escribir todos los datos
    outFile << buffer.str();

    // Luego escribir los cortes vinculados
    outFile << bufferCortesVinculados.str();

    outFile.close();
}





void GestorArchivos::cargarDatos(const std::string& archivo) {
    std::ifstream inFile(archivo.c_str(), std::ios::in | std::ios::binary);
    if (!inFile) {
        std::cerr << "Error al abrir el archivo de datos." << std::endl;
        return;
    }

    std::string linea;

    while (std::getline(inFile, linea)) {
        std::istringstream iss(linea);
        std::string tipo;
        std::getline(iss, tipo, ',');

        if (tipo == "PROFESOR") {
            int cedula, clases_asignadas;
            std::string nombre, apellido, email, telefono;
            std::string cedulaStr, clases_asignadasStr;
            
            std::getline(iss, cedulaStr, ',');
            std::getline(iss, nombre, ',');
            std::getline(iss, apellido, ',');
            std::getline(iss, email, ',');
            std::getline(iss, telefono, ',');
            std::getline(iss, clases_asignadasStr, ',');

            cedula = atoi(cedulaStr.c_str());
            clases_asignadas = atoi(clases_asignadasStr.c_str());

            gestorProfesores.agregarProfesor(cedula, nombre, apellido, email, telefono, clases_asignadas);
            std::cout << "Profesor agregado: " << nombre << " " << apellido << std::endl;
        } else if (tipo == "ESTUDIANTE") {
            int IDEstudiante;
            std::string nombre;
            std::string IDEstudianteStr;
            
            std::getline(iss, IDEstudianteStr, ',');
            std::getline(iss, nombre);

            IDEstudiante = atoi(IDEstudianteStr.c_str());

            // Eliminar espacios adicionales
            nombre.erase(nombre.find_last_not_of(" \n\r\t") + 1);
            nombre.erase(0, nombre.find_first_not_of(" \n\r\t"));

            gestorEstudiantes.agregarEstudiante(IDEstudiante, nombre);
            std::cout << "Estudiante agregado: " << nombre << std::endl;
        } else if (tipo == "CLASE") {
            int codigo_profesor;
            std::string codigo_profesorStr;

            std::getline(iss, codigo_profesorStr, ',');
            codigo_profesor = atoi(codigo_profesorStr.c_str());

            gestorClases.agregarClase(codigo_profesor);
            std::cout << "Clase agregada para profesor: " << codigo_profesor << std::endl;
        } else if (tipo == "MATERIA") {
            int codigo_profesor;
            std::string nombre_materia;
            std::string codigo_profesorStr;

            std::getline(iss, codigo_profesorStr, ',');
            std::getline(iss, nombre_materia);

            codigo_profesor = atoi(codigo_profesorStr.c_str());

            // Eliminar espacios adicionales
            nombre_materia.erase(nombre_materia.find_last_not_of(" \n\r\t") + 1);
            nombre_materia.erase(0, nombre_materia.find_first_not_of(" \n\r\t"));

            gestorClases.agregarMateria(codigo_profesor, nombre_materia);
            std::cout << "Materia agregada: " << nombre_materia << " para profesor: " << codigo_profesor << std::endl;
        } else if (tipo == "TEMA") {
            std::string nombre_materia;
            int codigo_profesor, codigo_tema;
            std::string tema;
            std::string codigo_profesorStr, codigo_temaStr;

            std::getline(iss, nombre_materia, ',');
            std::getline(iss, codigo_profesorStr, ',');
            std::getline(iss, codigo_temaStr, ',');
            std::getline(iss, tema);

            codigo_profesor = atoi(codigo_profesorStr.c_str());
            codigo_tema = atoi(codigo_temaStr.c_str());

            Clases* clase = gestorClases.buscarClases(codigo_profesor);
            if (clase) {
                Materias* materia = clase->buscarMaterias(nombre_materia);
                if (materia) {
                    // Eliminar espacios adicionales
                    tema.erase(tema.find_last_not_of(" \n\r\t") + 1);
                    tema.erase(0, tema.find_first_not_of(" \n\r\t"));
                    materia->agregarTema(codigo_tema, tema);
                    std::cout << "Tema agregado: " << tema << " a la materia: " << nombre_materia << std::endl;
                }
            }
        } else if (tipo == "CORTE") {
            int cedulaProfesor;
            std::string nombreCorte;
            int porcentaje;
            std::string cedulaProfesorStr, porcentajeStr;

            std::getline(iss, cedulaProfesorStr, ',');
            std::getline(iss, nombreCorte, ',');
            std::getline(iss, porcentajeStr, ',');

            cedulaProfesor = atoi(cedulaProfesorStr.c_str());
            porcentaje = atoi(porcentajeStr.c_str());

            Profesor* profesor = gestorProfesores.buscarProfesores(cedulaProfesor);
            if (profesor) {
                // Eliminar espacios adicionales
                nombreCorte.erase(nombreCorte.find_last_not_of(" \n\r\t") + 1);
                nombreCorte.erase(0, nombreCorte.find_first_not_of(" \n\r\t"));
                profesor->agregarCorte(nombreCorte, porcentaje);
                std::cout << "Corte agregado: " << nombreCorte << " al profesor: " << profesor->nombre << std::endl;
            }
        } else if (tipo == "EVALUACION") {
            int cedulaProfesor;
            std::string nombreCorte, nombreEvaluacion;
            std::string cedulaProfesorStr;

            std::getline(iss, cedulaProfesorStr, ',');
            std::getline(iss, nombreCorte, ',');
            std::getline(iss, nombreEvaluacion);

            cedulaProfesor = atoi(cedulaProfesorStr.c_str());

            Profesor* profesor = gestorProfesores.buscarProfesores(cedulaProfesor);
            if (profesor) {
                Corte* corte = profesor->buscarCorte(nombreCorte);
                if (corte) {
                    // Eliminar espacios adicionales
                    nombreEvaluacion.erase(nombreEvaluacion.find_last_not_of(" \n\r\t") + 1);
                    nombreEvaluacion.erase(0, nombreEvaluacion.find_first_not_of(" \n\r\t"));
                    corte->agregarEvaluacion(nombreEvaluacion);
                    std::cout << "Evaluacion agregada: " << nombreEvaluacion << " al corte: " << nombreCorte << std::endl;
                }
            }
        } else if (tipo == "PUNTO") {
            int cedulaProfesor;
            std::string nombreCorte, nombreEvaluacion;
            int porcentaje, codigo_tema;
            std::string cedulaProfesorStr, porcentajeStr, codigo_temaStr;

            std::getline(iss, cedulaProfesorStr, ',');
            std::getline(iss, nombreCorte, ',');
            std::getline(iss, nombreEvaluacion, ',');
            std::getline(iss, porcentajeStr, ',');
            std::getline(iss, codigo_temaStr, ',');

            cedulaProfesor = atoi(cedulaProfesorStr.c_str());
            porcentaje = atoi(porcentajeStr.c_str());
            codigo_tema = atoi(codigo_temaStr.c_str());

            Profesor* profesor = gestorProfesores.buscarProfesores(cedulaProfesor);
            if (profesor) {
                Corte* corte = profesor->buscarCorte(nombreCorte);
                if (corte) {
                    Evaluacion* evaluacion = corte->buscarEvaluaciones(nombreEvaluacion);
                    if (evaluacion) {
                        evaluacion->agregarPunto(porcentaje, codigo_tema);
                        std::cout << "Punto agregado: " << porcentaje << " al tema: " << codigo_tema << std::endl;
                    }
                }
            }
        } else if (tipo == "NOTA") {
            int cedulaProfesor, IDEstudiante;
            std::string nombreCorte, nombreEvaluacion;
            int porcentaje, codigo_tema;
            double valor;
            std::string cedulaProfesorStr, porcentajeStr, codigo_temaStr, IDEstudianteStr, valorStr;

            std::getline(iss, cedulaProfesorStr, ',');
            std::getline(iss, nombreCorte, ',');
            std::getline(iss, nombreEvaluacion, ',');
            std::getline(iss, porcentajeStr, ',');
            std::getline(iss, codigo_temaStr, ',');
            std::getline(iss, IDEstudianteStr, ',');
            std::getline(iss, valorStr);

            cedulaProfesor = atoi(cedulaProfesorStr.c_str());
            porcentaje = atoi(porcentajeStr.c_str());
            codigo_tema = atoi(codigo_temaStr.c_str());
            IDEstudiante = atoi(IDEstudianteStr.c_str());
            valor = atof(valorStr.c_str());

            Profesor* profesor = gestorProfesores.buscarProfesores(cedulaProfesor);
            if (profesor) {
                Corte* corte = profesor->buscarCorte(nombreCorte);
                if (corte) {
                    Evaluacion* evaluacion = corte->buscarEvaluaciones(nombreEvaluacion);
                    if (evaluacion) {
                        Punto* punto = corte->buscarPuntos(evaluacion->nombre, porcentaje, codigo_tema);
                        if (punto) {
                            punto->agregarNota(IDEstudiante, valor);
                            std::cout << "Nota agregada: " << valor << " para estudiante: " << IDEstudiante << std::endl;
                        }
                    }
                }
            }
        } else if (tipo == "MATRICULA") {
            std::string nombre_materia;
            int codigo_profesor, IDEstudiante;
            std::string codigo_profesorStr, IDEstudianteStr;

            std::getline(iss, nombre_materia, ',');
            std::getline(iss, codigo_profesorStr, ',');
            std::getline(iss, IDEstudianteStr, ',');

            codigo_profesor = atoi(codigo_profesorStr.c_str());
            IDEstudiante = atoi(IDEstudianteStr.c_str());

            Clases* clase = gestorClases.buscarClases(codigo_profesor);
            if (clase) {
                Materias* materia = clase->buscarMaterias(nombre_materia);
                if (materia) {
                    materia->matricularEstudiante(IDEstudiante, gestorEstudiantes);
                    std::cout << "Estudiante matriculado: " << IDEstudiante << " en la materia: " << nombre_materia << std::endl;
                }
            }
        } else if (tipo == "CORTE_VINCULADO") {
            std::string nombre_materia, nombre_corte;
            int codigo_profesor;
            std::string codigo_profesorStr;

            std::getline(iss, nombre_materia, ',');
            std::getline(iss, codigo_profesorStr, ',');
            std::getline(iss, nombre_corte, ',');

            codigo_profesor = atoi(codigo_profesorStr.c_str());

            Clases* clase = gestorClases.buscarClases(codigo_profesor);
            if (clase) {
                Materias* materia = clase->buscarMaterias(nombre_materia);
                if (materia) {
                    // Eliminar espacios adicionales
                    nombre_corte.erase(nombre_corte.find_last_not_of(" \n\r\t") + 1);
                    nombre_corte.erase(0, nombre_corte.find_first_not_of(" \n\r\t"));
                    materia->vincularCorte(nombre_corte, codigo_profesor, gestorProfesores);
                    std::cout << "Corte vinculado: " << nombre_corte << " a la materia: " << nombre_materia << std::endl;
                }
            }
        }
    }
    inFile.close();
}









bool compararPorPromedio(const PromedioTema& a, const PromedioTema& b) {
    return a.promedio < b.promedio;
}

void GestorArchivos::generarReporteRefuerzo() {
    Lista<PromedioTema> listaPromedios;

    // Recorrer todos los profesores
    for (int i = 0; i < gestorProfesores.profesores.size(); ++i) {
        Profesor& profesor = gestorProfesores.profesores.obtainByReference(i);

        // Recorrer todos los cortes del profesor
        for (int j = 0; j < profesor.cortes.size(); ++j) {
            Corte& corte = profesor.cortes.obtainByReference(j);

            // Recorrer todas las evaluaciones del corte
            for (int k = 0; k < corte.evaluaciones->size(); ++k) {
                Evaluacion& evaluacion = corte.evaluaciones->obtainByReference(k);

                // Recorrer todos los puntos de la evaluación
                for (int l = 0; l < evaluacion.puntos->size(); ++l) {
                    Punto& punto = evaluacion.puntos->obtainByReference(l);

                    // Calcular la nota promedio para cada punto
                    double sumaNotas = 0.0;
                    int cantidadNotas = punto.notas->size();
                    for (int m = 0; m < cantidadNotas; ++m) {
                        Nota& nota = punto.notas->obtainByReference(m);
                        sumaNotas += nota.valor;
                    }
                    double promedio = (cantidadNotas > 0) ? (sumaNotas / cantidadNotas) : 0.0;

                    // Guardar el promedio en la estructura
                    Temas* tema = gestorClases.buscarTemaPorCodigo(punto.codigo_tema);
                    if (tema) {
                        bool encontrado = false;
                        for (int n = 1; n <= listaPromedios.getTam(); n++) {
                            PromedioTema temp = listaPromedios.buscar_nodo(n);
                            if (temp.tema == tema->tema) {
                                temp.promedio += promedio;
                                listaPromedios.borrar_nodo(n);
                                listaPromedios.insertar_final(temp);
                                encontrado = true;
                                break;
                            }
                        }
                        if (!encontrado) {
                            PromedioTema nuevoPromedio;
                            nuevoPromedio.tema = tema->tema;
                            nuevoPromedio.promedio = promedio;
                            listaPromedios.insertar_final(nuevoPromedio);
                        }
                    }
                }
            }
        }
    }

    // Calcular el promedio general por tema
    for (int i = 1; i <= listaPromedios.getTam(); i++) {
        PromedioTema& promedioTema = listaPromedios.buscar_nodoByReference(i);
        promedioTema.promedio /= gestorClases.getClases().size(); // Número total de clases
    }

    // Ordenar los promedios por nota utilizando quicksort
    listaPromedios.quickSort(compararPorPromedio);

    // Escribir los resultados en el archivo refuerzo.txt
    std::ofstream outFile("refuerzo.txt");
    for (int i = 1; i <= listaPromedios.getTam(); i++) {
        PromedioTema promedioTema = listaPromedios.buscar_nodo(i);
        outFile << promedioTema.tema << " " << promedioTema.promedio << std::endl;
    }
    outFile.close();
}




