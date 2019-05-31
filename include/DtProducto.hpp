#ifndef _DTPRODUCTO_HPP
#define _DTPRODUCTO_HPP

//Librerias de C
#include <string>
using namespace std;

//Archivos

class DtProducto {
private:
    int codigo;
    string descripcion;
    float precio;
public:
    DtProducto(int codigo, string descripcion, float precio); //
    int getCodigo();
    string getDescripcion();
    float getPrecio();
    ~DtProducto();
};

#endif
