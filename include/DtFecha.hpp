#ifndef _DTFECHA_HPP
#define _DTFECHA_HPP

//Librerias de C
#include <ostream>
using namespace std;

class DtFecha {
private:
    int dia;
    int mes;
    int anio;
public:
	//Constructor
    DtFecha();
    DtFecha(int dia, int mes, int anio);

    //Destructor
    ~DtFecha();

    //Getters
    int getDia() const;
    int getMes() const;
    int getAnio() const;

    //Sobrecarga de operador de comparación
    bool operator==(const DtFecha&);
};

ostream &operator<< (ostream&, DtFecha);

#endif
