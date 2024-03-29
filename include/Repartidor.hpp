#ifndef _REPARTIDOR_HPP
#define _REPARTIDOR_HPP

//Librerias de C
#include <string>
#include <map>
using namespace std;

//Archivos
#include "Empleado.hpp"
#include "Transporte.hpp"
#include "VentaADomicilio.hpp"

class Repartidor : public Empleado {
private:
   Transporte medioTransporte;
public:
    //Constructor
    Repartidor(int numero, string nombre, Transporte medioTransporte);

    //Destructor
    ~Repartidor();

    //Getters
    Transporte getTransporte();
};

#endif
