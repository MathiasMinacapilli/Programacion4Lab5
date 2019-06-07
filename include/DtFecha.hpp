#ifndef _DTFECHA_HPP
#define _DTFECHA_HPP

class DtFecha {
private:
    int dia;
    int mes;
    int anio;
public:
	//constructor
    DtFecha();
    DtFecha(int dia, int mes, int anio);
    //getters
    int getDia();
    int getMes();
    int getAnio();
    //destructor
    ~DtFecha();
    //sobrecarga de operador de comparacion
    bool operator==(const DtFecha&);
};

#endif