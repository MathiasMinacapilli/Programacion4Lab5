//Librerias de C
#include <string>
using namespace std;

//Archivos
#include "../include/DtFecha.hpp"

DtFecha::DtFecha() {}

DtFecha::DtFecha(int dia, int mes, int anio) {
    this->dia = dia;
    this->mes = mes;
    this->anio = anio;
}

int DtFecha::getDia() const{
    return this->dia;
}

int DtFecha::getMes() const {
    return this->mes;
}

int DtFecha::getAnio() const{
    return this->anio;
}

DtFecha::~DtFecha() {}

bool DtFecha::operator==(const DtFecha &f2) {
    return ((this->getAnio() == f2.getAnio()) &&
        (this->getMes() == f2.getMes()) &&
        (this->getDia() == f2.getDia()));
}

ostream &operator<< (ostream& o, DtFecha dtf) {

    int dia_int = dtf.getDia();
    string dia = to_string(dia_int);
    if (dia_int < 10)
        dia = "0" + dia;

    int mes_int = dtf.getMes();
    string mes = to_string(mes_int);
    if (mes_int < 10)
        mes = "0" + mes;

    o << dia << "/" << mes << "/" << dtf.getAnio();
	return o;
}
