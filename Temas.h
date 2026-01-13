#ifndef TEMAS_H
#define TEMAS_H

#include <iostream>
#include <string>
using namespace std;

class Temas{
	public:
		
		int codigo_tema;
		string tema;
		
		Temas(int codigo_tema, const string& tema);
		Temas(const std::string& tema);
		Temas();
		~Temas();
		
		bool operator==(const Temas& otro) const {
        return codigo_tema == codigo_tema;
	    }
	    
	    bool operator>(const Temas& otro) const {
	        return codigo_tema > otro.codigo_tema;
	    }
	    
	    bool operator!=(const Temas& otro) const {
	        return codigo_tema > otro.codigo_tema;
	    }
	    
	    friend ostream& operator<<(ostream& out, const Temas& est){
          return out << "codigo tema: " << est.codigo_tema << ", Tema: " << est.tema<<endl;
    }
};

#endif  // TEMAS_H
