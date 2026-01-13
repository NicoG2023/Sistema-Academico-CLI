#include "Temas.h"
using namespace std;

Temas::Temas(int codigo_tema, const string& nombre_tema) : codigo_tema(codigo_tema), tema(nombre_tema) {}

Temas::Temas(){
	
}

Temas::Temas(const std::string& tema) : codigo_tema(0), tema(tema) {}

Temas::~Temas() {}


