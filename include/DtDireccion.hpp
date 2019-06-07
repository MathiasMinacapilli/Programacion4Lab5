#ifndef _DTDIRECCION_HPP
#define _DTDIRECCION_HPP

//Librerias de C
#include <set>
#include <string>
using namespace std;


class DtDireccion {
private:
   string calle;
   int numeroPuerta;
   string esquina1;
   string esquina2;
public:
    DtDireccion();
    DtDireccion(string calle, int numeroPuerta, string esquina1, string esquina2);
    string getCalle();
    int getNumeroPuerta();
    string getEsquina1();
    string getEsquina2();
    ~DtDireccion();
};

#endif
