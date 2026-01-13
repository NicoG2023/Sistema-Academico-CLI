#ifndef NOTA_H
#define NOTA_H

#include <iostream>
using namespace std;
class Nota {
public:
    double valor;
    int IDEstudiante;

    Nota(double valor, int IDEstudiante) : valor(valor), IDEstudiante(IDEstudiante) {}
    Nota();
    ~Nota();
    
    Nota(const Nota& other);
    Nota& operator=(const Nota& other);

    bool operator<(const Nota& otra) const {
        return IDEstudiante < otra.IDEstudiante;
    }

    bool operator>(const Nota& otra) const {
        return IDEstudiante > otra.IDEstudiante;
    }

    bool operator==(const Nota& otra) const {
        return IDEstudiante == otra.IDEstudiante;
    }

    bool operator!=(const Nota& otra) const {
        return IDEstudiante != otra.IDEstudiante;
    }

    friend std::ostream& operator<<(std::ostream& out, const Nota& est) {
        return out << "Valor: " << est.valor << ", Pertenece a estudiante cuyo ID es: " << est.IDEstudiante <<endl;
    }
};

#endif // NOTA_H

