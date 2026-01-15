#include "Menu.h"
using namespace std;

Menu::Menu(GestorProfesores& gp, GestorEstudiantes& ge, GestorClases& gc, GestorConsultas& gcs, GestorArchivos& ga)
    : gestorProfesores(gp), gestorEstudiantes(ge), gestorClases(gc), gestorConsultas(gcs), gestorArchivos(ga) {}

void Menu::mostrarMenuPrincipal() {
    int opcion = 0;
    gestorArchivos.cargarDatos("Database");
    #ifdef _WIN32
    system("cls");
    #else
        system("clear");
    #endif
    do {
    	//system("cls");
        std::cout << "***********************************************" << std::endl;
        std::cout << "* Proyecto Final Ciencias de la Computacion I *" << std::endl;
        std::cout << "* Autores:                                    *" << std::endl;
        std::cout << "* - Nicolas Guevara Herran                    *" << std::endl;
        std::cout << "* - Juan Manuel Serrano Rodriguez             *" << std::endl;
        std::cout << "***********************************************" << std::endl;
        std::cout << "Seleccione una opcion:" << std::endl;
        std::cout << "1. Agregar Profesor" << std::endl;
        std::cout << "2. Agregar Estudiante" << std::endl;
        std::cout << "3. Agregar Materia" << std::endl;
        std::cout << "4. Generar Reporte Refuerzos" << std::endl;
        std::cout << "5. Hacer Consultas" << std::endl;
        std::cout << "6. Menu Profesor" << std::endl;
        std::cout << "7. Menu Mostrar" << std::endl;  // Nueva opci�n para el men� "MenuMostrar"
        std::cout << "8. Salir" << std::endl;
        std::cout << "Opcion: ";
        std::cin >> opcion;

        switch (opcion) {
            case 1:
                agregarProfesor();
                break;
            case 2:
                agregarEstudiante();
                break;
            case 3:
                agregarMateria();
                break;
            case 4:
                generarReporteRefuerzos();
                break;
            case 5:
                hacerConsultas();
                break;
            case 6:
                menuProfesor();
                break;
            case 7:
            	mostrarMenu();
                break;
        	case 8:
        		std::cout << "Saliendo del programa..." << std::endl;
        		//CARGAR DATOS
        		gestorArchivos.guardarDatos("Database");
        		break;
            default:
                std::cout << "Opcion invalida. Intente nuevamente." << std::endl;
                break;
        }
    } while (opcion != 8);
}

void Menu::menuProfesor() {
    int codigoProfesor;
    std::cout << "Ingrese el codigo del profesor: ";
    std::cin >> codigoProfesor;

    Profesor* profesor = gestorProfesores.buscarProfesores(codigoProfesor);
    if (!profesor) {
        std::cout << "Profesor no encontrado." << std::endl;
        return;
    }

    int opcion = 0;
    do {
        std::cout << "************** Menu Profesor **************" << std::endl;
        std::cout << "1. Agregar Corte" << std::endl;
        std::cout << "2. Agregar Evaluacion" << std::endl;
        std::cout << "3. Agregar Punto" << std::endl;
        std::cout << "4. Agregar Nota" << std::endl;
        std::cout << "5. Matricular Estudiante" << std::endl;
        std::cout << "6. Vincular Corte a Materia" << std::endl;
        std::cout << "7. Modificar Corte" << std::endl;
        std::cout << "8. Modificar Evaluacion" << std::endl;
        std::cout << "9. Modificar Punto" << std::endl;
        std::cout << "10. Cambiar Evaluacion de Corte" << std::endl;
        std::cout << "11. Generar Archivo de parcial" << std::endl;
        std::cout << "12. Subir Parcial" << std::endl;
        std::cout << "13. Volver al Menu Principal" << std::endl;
        std::cout << "Opcion: ";
        std::cin >> opcion;

        switch (opcion) {
            case 1:
                agregarCorte(*profesor);
                break;
            case 2:
                agregarEvaluacion(*profesor);
                break;
            case 3:
                agregarPunto(*profesor);
                break;
            case 4:
                agregarNota(*profesor);
                break;
            case 5:
                matricularEstudiante(*profesor);
                break;
            case 6:
                vincularCorteMateria(*profesor);
                break;
            case 7:
                modificarCorte(*profesor);
                break;
            case 8:
                modificarEvaluacion(*profesor);
                break;
            case 9:
                modificarPunto(*profesor);
                break;
            case 10:
                cambiarEvaluacionCorte(*profesor);
                break;
            case 11:
            	generarArchivoParcial(*profesor);
            	break;
            case 12:
            	subirParcial(*profesor);
            	break;
            case 13:
                std::cout << "Volviendo al menu principal..." << std::endl;
                break;
            default:
                std::cout << "Opcion invalida. Intente nuevamente." << std::endl;
                break;
        }
    } while (opcion != 13);
}

void Menu::mostrarMenu() {
    int opcion = 0;

    do {
        std::cout << "************** Menu Mostrar **************" << std::endl;
        std::cout << "1. Mostrar Profesores" << std::endl;
        std::cout << "2. Mostrar Estudiantes" << std::endl;
        std::cout << "3. Mostrar Materias de un Profesor" << std::endl;
        std::cout << "4. Mostrar Cortes de un Profesor" << std::endl;
        std::cout << "5. Mostrar Evaluaciones de un Corte" << std::endl;
        std::cout << "6. Mostrar Puntos de una Evaluacion" << std::endl;
        std::cout << "7. Mostrar Notas de una Evaluacion" << std::endl;
        std::cout << "8. Mostrar Temas de una Materia" << std::endl;
        std::cout << "9. Volver al Menu Principal" << std::endl;
        std::cout << "Opcion: ";
        std::cin >> opcion;

        switch (opcion) {
            case 1:
                mostrarProfesores();
                break;
            case 2:
                mostrarEstudiantes();
                break;
            case 3:
                mostrarMateriasProfesor();
                break;
            case 4:
                mostrarCortesProfesor();
                break;
            case 5:
                mostrarEvaluacionesCorte();
                break;
            case 6:
                mostrarPuntosEvaluacion();
                break;
            case 7:
                mostrarNotasEvaluacion();
                break;
            case 8:
                mostrarTemasMateria();
                break;
            case 9:
                std::cout << "Volviendo al menu principal..." << std::endl;
                break;
            default:
                std::cout << "Opcion invalida. Intente nuevamente." << std::endl;
                break;
        }
    } while (opcion != 9);
}

void Menu::hacerConsultas() {
    int opcion = 0;
    
    do {
        std::cout << "************** Menu de Consultas **************" << std::endl;
        std::cout << "1. Promedio y Comportamiento de estudiante perteneciente a un curso especifico" << std::endl;
        std::cout << "2. Comportamiento Promedio de los estudiantes en un curso especifico" << std::endl;
        std::cout << "3. Comportamiento Promedio de todos los estudiantes que toman clase con el mismo profesor" << std::endl;
        std::cout << "4. Lista de los profesores que tienen un numero de clases dado" << std::endl;
        std::cout << "5. Lista de estudiantes que tienen nota superior a una nota dada" << std::endl;
        std::cout << "6. Volver al Menu Principal" << std::endl;
        std::cout << "Opcion: ";
        std::cin >> opcion;
        std::cin.ignore(10000, '\n'); // Limpiar el buffer de entrada

        switch (opcion) {
            case 1:
                consultaPromedioComportamientoEstudiante();
                break;
            case 2:
                consultaComportamientoPromedioCurso();
                break;
            case 3:
                consultaComportamientoPromedioProfesor();
                break;
            case 4:
                consultaProfesoresPorNumeroClases();
                break;
            case 5:
                consultaEstudiantesPorNota();
                break;
            case 6:
                std::cout << "Volviendo al Menu Principal..." << std::endl;
                break;
            default:
                std::cout << "Opcion invalida. Intente nuevamente." << std::endl;
                break;
        }
    } while (opcion != 6);
}

void Menu::agregarProfesor() {
    int cedula, clases_asignadas;
    std::string nombre, apellido, email, telefono;

    std::cout << "Ingrese la cedula del profesor: ";
    std::cin >> cedula;
    std::cin.ignore(10000, '\n'); // Limpiar el buffer de entrada

    std::cout << "Ingrese el nombre del profesor: ";
    std::getline(std::cin, nombre);

    std::cout << "Ingrese el apellido del profesor: ";
    std::getline(std::cin, apellido);

    std::cout << "Ingrese el email del profesor: ";
    std::getline(std::cin, email);

    std::cout << "Ingrese el telefono del profesor: ";
    std::getline(std::cin, telefono);

    std::cout << "Ingrese la cantidad de clases que dicta el profesor: ";
    std::cin >> clases_asignadas;
    std::cin.ignore(10000, '\n'); // Limpiar el buffer de entrada

    gestorProfesores.agregarProfesor(cedula, nombre, apellido, email, telefono, clases_asignadas);
    gestorClases.agregarClase(cedula);

    std::cout << "Profesor agregado exitosamente." << std::endl;
}

void Menu::agregarEstudiante() {
    int ID;
    std::string nombre;
    cout<<"Ingrese el ID del estudiante: ";
    cin>>ID;
    std::cin.ignore(10000, '\n');
    std::cout << "Ingrese el nombre del estudiante: ";
    std::getline(std::cin, nombre);
    gestorEstudiantes.agregarEstudiante(ID, nombre);
    std::cout << "Estudiante agregado exitosamente." << std::endl;
}

void Menu::agregarMateria() {
    int codigoProfesor;
    std::string nombreMateria;
    std::cout << "Ingrese el codigo del profesor: ";
    std::cin >> codigoProfesor;
    std::cin.ignore(10000, '\n');
    std::cout << "Ingrese el nombre de la materia: ";
    getline(cin, nombreMateria);
    gestorClases.agregarMateria(codigoProfesor, nombreMateria);
}

void Menu::generarReporteRefuerzos() {
    gestorArchivos.generarReporteRefuerzo();
    std::cout << "Reporte de refuerzos generado exitosamente." << std::endl;
}

void Menu::agregarCorte(Profesor& profesor) {
    std::string nombreCorte;
    int porcentaje;

    // Aseg�rate de limpiar el buffer de entrada antes de leer el nombre del corte
    std::cin.ignore(10000, '\n'); // Usamos un valor grande para ignorar cualquier car�cter restante

    std::cout << "Ingrese el nombre del corte: ";
    std::getline(std::cin, nombreCorte);

    std::cout << "Ingrese el porcentaje del corte: ";
    std::cin >> porcentaje;

    profesor.agregarCorte(nombreCorte, porcentaje);
}

void Menu::agregarEvaluacion(Profesor& profesor) {
    std::string nombreCorte, nombreEvaluacion;

    // Aseg�rate de limpiar el buffer de entrada antes de leer el nombre del corte
    std::cin.ignore(10000, '\n'); // Usamos un valor grande para ignorar cualquier car�cter restante

    std::cout << "Ingrese el nombre del corte: ";
    std::getline(std::cin, nombreCorte);

    std::cout << "Ingrese el nombre de la evaluacion: ";
    std::getline(std::cin, nombreEvaluacion);

    Corte* corte = profesor.buscarCorte(nombreCorte);
    if (corte) {
        corte->agregarEvaluacion(nombreEvaluacion);
        std::cout << "Evaluacion agregada exitosamente." << std::endl;
    } else {
        std::cout << "Corte no encontrado." << std::endl;
    }
}


void Menu::agregarPunto(Profesor& profesor) {
    int porcentaje, codigoTema;
    std::string nombreCorte, nombreEvaluacion;
    std::cin.ignore(10000, '\n');
    std::cout << "Ingrese el nombre del corte: ";
    getline(cin, nombreCorte);
    std::cout << "Ingrese el nombre de la evaluacion: ";
    getline(cin, nombreEvaluacion);
    std::cout << "Ingrese el porcentaje del punto: ";
    std::cin >> porcentaje;
    std::cout << "Ingrese el codigo del tema: ";
    std::cin >> codigoTema;
    Corte* corte = profesor.buscarCorte(nombreCorte);
    if (corte) {
        Evaluacion* evaluacion = corte->buscarEvaluaciones(nombreEvaluacion);
        if (evaluacion) {
            corte->agregarPunto(nombreEvaluacion,porcentaje,codigoTema);
            std::cout << "Punto agregado exitosamente." << std::endl;
        } else {
            std::cout << "Evaluacion no encontrada." << std::endl;
        }
    } else {
        std::cout << "Corte no encontrado." << std::endl;
    }
}

void Menu::agregarNota(Profesor& profesor) {
    std::string nombreCorte, nombreEvaluacion;
    int porcentaje, codigoTema, IDEstudiante;
    double valor;
    std::cin.ignore(10000, '\n');
    std::cout << "Ingrese el nombre del corte: ";
    getline(cin, nombreCorte);
    std::cout << "Ingrese el nombre de la evaluacion: ";
    getline(cin, nombreEvaluacion);
    std::cout << "Ingrese el porcentaje del punto: ";
    std::cin >> porcentaje;
    std::cout << "Ingrese el codigo del tema: ";
    std::cin >> codigoTema;
    std::cout << "Ingrese el ID del estudiante: ";
    std::cin >> IDEstudiante;
    std::cout << "Ingrese la nota: ";
    std::cin >> valor;
    Corte* corte = profesor.buscarCorte(nombreCorte);
    if (corte) {
        corte->agregarNota(nombreEvaluacion, porcentaje, codigoTema, IDEstudiante, valor);
        std::cout << "Nota agregada exitosamente." << std::endl;
    } else {
        std::cout << "Corte no encontrado." << std::endl;
    }
}

void Menu::matricularEstudiante(Profesor& profesor) {
    std::string nombreMateria;
    int IDEstudiante;
    std::cin.ignore(10000, '\n');
    std::cout << "Ingrese el nombre de la materia: ";
    getline(cin, nombreMateria);
    std::cout << "Ingrese el ID del estudiante: ";
    std::cin >> IDEstudiante;
    Clases* clase = gestorClases.buscarClases(profesor.cedula);
    if (clase) {
        Materias* materia = clase->buscarMaterias(nombreMateria);
        if (materia) {
            materia->matricularEstudiante(IDEstudiante, gestorEstudiantes);
            std::cout << "Estudiante matriculado exitosamente." << std::endl;
        } else {
            std::cout << "Materia no encontrada." << std::endl;
        }
    } else {
        std::cout << "Clase no encontrada." << std::endl;
    }
}

void Menu::vincularCorteMateria(Profesor& profesor) {
    std::string nombreCorte, nombreMateria;
    std::cin.ignore(10000, '\n');
    std::cout << "Ingrese el nombre del corte: ";
    getline(cin, nombreCorte);
    std::cout << "Ingrese el nombre de la materia: ";
    getline(cin, nombreMateria);
    Clases* clase = gestorClases.buscarClases(profesor.cedula);
    if (clase) {
        Materias* materia = clase->buscarMaterias(nombreMateria);
        if (materia) {
            materia->vincularCorte(nombreCorte, profesor.cedula, gestorProfesores);
        } else {
            std::cout << "Materia no encontrada." << std::endl;
        }
    } else {
        std::cout << "Clase no encontrada." << std::endl;
    }
}

void Menu::modificarCorte(Profesor& profesor){
	std::string nombreCorte, nombreNuevoCorte;
	int nuevoPorcentaje;
	std::cin.ignore(10000, '\n');
	std::cout << "Ingrese el nombre del corte: ";
    getline(cin, nombreCorte);
    std::cout << "Ingrese el nuevo nombre del corte: ";
    getline(cin, nombreNuevoCorte);
    std::cout << "Ingrese el nuevo porcentaje del corte: ";
    cin >> nuevoPorcentaje;
    profesor.modificarCorte(nombreCorte, nuevoPorcentaje, nombreNuevoCorte);
}

void Menu::modificarEvaluacion(Profesor& profesor){
	std::string nombreCorte, nombreEvaluacion, nuevoNombreEvaluacion;
	std::cin.ignore(10000, '\n');
	std::cout << "Ingrese el nombre del corte: ";
    getline(cin, nombreCorte);
    std::cout << "Ingrese el nombre de la evaluacion: ";
    getline(cin, nombreEvaluacion);
    std::cout << "Ingrese el nuevo nombre de la evalucion: ";
    getline(cin, nuevoNombreEvaluacion);
    profesor.modificarEvaluacion(nombreCorte, nombreEvaluacion, nuevoNombreEvaluacion);
}

void Menu::modificarPunto(Profesor& profesor){
	std::string nombreCorte, nombreEvaluacion;
	int porcentajePunto, codigo_tema, nuevoPorcentaje, nuevoCodigoTema;
	std::cin.ignore(10000, '\n');
	std::cout << "Ingrese el nombre del corte: ";
    getline(cin, nombreCorte);
    std::cout << "Ingrese el nombre de la evaluacion: ";
    getline(cin, nombreEvaluacion);
    std::cout << "Ingrese el porcentaje del punto que desea cambiar: ";
    cin>>porcentajePunto;
    std::cout << "Ingrese el codigo del tema vinculado con el punto que desea cambiar: ";
    cin>>codigo_tema;
    std::cout << "Ingrese el nuevo porcentaje del punto: ";
    cin>>nuevoPorcentaje;
    std::cout << "Ingrese el nuevo codigo de tema vinculado con el punto que desea cambiar: ";
    cin>>nuevoCodigoTema;
    profesor.modificarPunto(nombreCorte, nombreEvaluacion, porcentajePunto, codigo_tema, nuevoPorcentaje, nuevoCodigoTema);
}

void Menu::cambiarEvaluacionCorte(Profesor &profesor){
	std::string nombreEvaluacion, nombreCorteOrigen, nombreCorteDestino;
	std::cin.ignore(10000, '\n');
	std::cout << "Ingrese el nombre del corte donde se encuentra la evaluacion a cambiar: ";
    getline(cin, nombreCorteOrigen);
    std::cout << "Ingrese el nombre de la evaluacion: ";
    getline(cin, nombreEvaluacion);
    std::cout << "Ingrese el nombre del corte a donde va a poner la evaluacion: ";
    getline(cin, nombreCorteDestino);
    if(profesor.cambiarEvaluacionDeCorte(nombreEvaluacion,nombreCorteOrigen,nombreCorteDestino)){
    	cout<<"Evaluacion cambiada de corte exitosamente."<<endl;
	}else{
		cout<<"no fue posible realizar esta accion"<<endl;
	}
}

void Menu::generarArchivoParcial(Profesor &profesor){
	string materia;
	std::cin.ignore(10000, '\n');
	std::cout << "Ingrese el nombre de la materia de la cual desea generar los archivos de parcial: ";
    getline(cin, materia);
    Clases* clase = gestorClases.buscarClases(profesor.cedula);
    if(clase){
    	Materias* mate = clase->buscarMaterias(materia);
    	if(mate){
    		mate->generarArchivosParciales(gestorProfesores, profesor.cedula);
		}else{
			cout<<"Materia no encontrada."<<endl;
		}
	}else{
		cout<<"Clase no encontrada"<<endl;
	}
}

void Menu::subirParcial(Profesor &profesor) {
    string filename, materia;
    std::cin.ignore(10000, '\n');
	std::cout << "Ingrese el nombre de la materia de la cual desea subir un parcial: ";
    getline(cin, materia);
    std::cout << "Ingrese el nombre del archivo: ";
    getline(cin, filename);
    Clases* clase = gestorClases.buscarClases(profesor.cedula);
    if(clase){
    	Materias* mate = clase->buscarMaterias(materia);
    	if(mate){
    		mate->subirParcial(filename,gestorEstudiantes,profesor.cedula, gestorProfesores);
		}else{
			cout<<"Materia no encontrada."<<endl;
		}
	}else{
		cout<<"Clase no encontrada"<<endl;
	}
}

void Menu::mostrarProfesores() {
    gestorProfesores.profesores.display();
}

void Menu::mostrarEstudiantes() {
    gestorEstudiantes.listarEstudiantes();
}

void Menu::mostrarMateriasProfesor() {
    int codigoProfesor;
    std::cout << "Ingrese la cedula del profesor: ";
    std::cin >> codigoProfesor;

    Clases* clase = gestorClases.buscarClases(codigoProfesor);
    if (clase) {
        clase->listarMaterias();
    } else {
        std::cout << "Profesor no encontrado o sin clases asignadas." << std::endl;
    }
}

void Menu::mostrarCortesProfesor() {
    int codigoProfesor;
    std::cout << "Ingrese el codigo del profesor: ";
    std::cin >> codigoProfesor;

    Profesor* profesor = gestorProfesores.buscarProfesores(codigoProfesor);
    if (profesor) {
        profesor->cortes.display();
    } else {
        std::cout << "Profesor no encontrado." << std::endl;
    }
}

void Menu::mostrarEvaluacionesCorte() {
    int codigoProfesor;
    std::string nombreCorte;
    std::cout << "Ingrese el codigo del profesor: ";
    std::cin >> codigoProfesor;
    std::cin.ignore(10000, '\n');
    std::cout << "Ingrese el nombre del corte: ";
    getline(cin, nombreCorte);

    Profesor* profesor = gestorProfesores.buscarProfesores(codigoProfesor);
    if (profesor) {
        Corte* corte = profesor->buscarCorte(nombreCorte);
        if (corte) {
            corte->listarEvaluaciones();
        } else {
            std::cout << "Corte no encontrado." << std::endl;
        }
    } else {
        std::cout << "Profesor no encontrado." << std::endl;
    }
}

void Menu::mostrarPuntosEvaluacion() {
    int codigoProfesor;
    std::string nombreCorte, nombreEvaluacion;
    std::cout << "Ingrese el codigo del profesor: ";
    std::cin >> codigoProfesor;
    std::cin.ignore(10000, '\n');
    std::cout << "Ingrese el nombre del corte: ";
    getline(cin, nombreCorte);
    std::cout << "Ingrese el nombre de la evaluacion: ";
    getline(cin, nombreEvaluacion);

    Profesor* profesor = gestorProfesores.buscarProfesores(codigoProfesor);
    if (profesor) {
        Corte* corte = profesor->buscarCorte(nombreCorte);
        if (corte) {
            Evaluacion* evaluacion = corte->buscarEvaluaciones(nombreEvaluacion);
            if (evaluacion) {
                evaluacion->puntos->display();
            } else {
                std::cout << "Evaluacion no encontrada." << std::endl;
            }
        } else {
            std::cout << "Corte no encontrado." << std::endl;
        }
    } else {
        std::cout << "Profesor no encontrado." << std::endl;
    }
}

void Menu::mostrarNotasEvaluacion() {
    int codigoProfesor;
    std::string nombreCorte, nombreEvaluacion;
    int porcentajePunto, codigoTema;
    std::cout << "Ingrese el codigo del profesor: ";
    std::cin >> codigoProfesor;
    std::cin.ignore(10000, '\n');
    std::cout << "Ingrese el nombre del corte: ";
    getline(cin, nombreCorte);
    std::cout << "Ingrese el nombre de la evaluacion: ";
    getline(cin, nombreEvaluacion);
    std::cout << "Ingrese el porcentaje del punto: ";
    std::cin >> porcentajePunto;
    std::cout << "Ingrese el codigo del tema: ";
    std::cin >> codigoTema;

    Profesor* profesor = gestorProfesores.buscarProfesores(codigoProfesor);
    if (profesor) {
        Corte* corte = profesor->buscarCorte(nombreCorte);
        if (corte) {
            Punto* punto = corte->buscarPuntos(nombreEvaluacion, porcentajePunto, codigoTema);
            if (punto) {
                punto->notas->display();
            } else {
                std::cout << "Punto no encontrado." << std::endl;
            }
        } else {
            std::cout << "Corte no encontrado." << std::endl;
        }
    } else {
        std::cout << "Profesor no encontrado." << std::endl;
    }
}

void Menu::mostrarTemasMateria() {
    std::string nombreMateria;
    int codigoProfe;
    std::cin.ignore(10000, '\n');
    std::cout << "Ingrese el nombre de la materia: ";
    getline(cin, nombreMateria);
    cout<<"Ingrese la cedula del profesor que dicta la materia:";
    cin >> codigoProfe;
	Clases* clase = gestorClases.buscarClases(codigoProfe);
	if(clase){
		Materias* mate = clase->buscarMaterias(nombreMateria);
		if(mate){
			cout<<"llega por aca"<<endl;
			mate->listarTemas();
		}else{
			cout<<"Materia no encontrada."<<endl;
		}
	}else{
		cout<<"Clase no encontrada"<<endl;
	}
}

void Menu::consultaPromedioComportamientoEstudiante() {
    int IDEstudiante, ced;
    std::string materia;
    std::cout << "Ingrese el ID del estudiante: ";
    std::cin >> IDEstudiante;
    std::cin.ignore(10000, '\n');
    std::cout << "Ingrese el nombre de la materia: ";
    std::getline(std::cin, materia);
    cout<<"Ingrese la cedula del profesor que dicta la materia: ";
    cin>>ced;
    Profesor& profe = gestorProfesores.buscarProfesor(ced);
    
    gestorConsultas.consultaPromedioEstudiante(IDEstudiante, materia, profe);
}

void Menu::consultaComportamientoPromedioCurso() {
    std::string materia;
    std::cout << "Ingrese el nombre de la materia: ";
    std::getline(std::cin, materia);
    
    gestorConsultas.consultaComportamientoPromedioCurso(materia);
}

void Menu::consultaComportamientoPromedioProfesor() {
    int codigoProfesor;
    std::cout << "Ingrese el codigo del profesor: ";
    std::cin >> codigoProfesor;
    std::cin.ignore(10000, '\n');
    
    gestorConsultas.consultaComportamientoPromedioProfesor(codigoProfesor);
}

void Menu::consultaProfesoresPorNumeroClases() {
    int numeroClases;
    std::cout << "Ingrese el numero de clases: ";
    std::cin >> numeroClases;
    std::cin.ignore(10000, '\n');
    
    gestorConsultas.consultaProfesoresPorClases(numeroClases);
}

void Menu::consultaEstudiantesPorNota() {
    double notaDada;
    std::string tema;
    std::cout << "Ingrese la nota dada: ";
    std::cin >> notaDada;
    std::cin.ignore(10000, '\n');
    std::cout << "Ingrese el nombre del tema: ";
    std::getline(std::cin, tema);
    
    gestorConsultas.consultaEstudiantesPorNota(notaDada, tema);
}

