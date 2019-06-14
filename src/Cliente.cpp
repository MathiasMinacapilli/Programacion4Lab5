//Librerias de C
#include <set>
#include <string>
using namespace std;

//Archivos
#include "../include/Cliente.hpp"

//Constructor por defecto
Cliente::Cliente(){}

//constructor por parametros
Cliente::Cliente(string telefono, string nombre, DtDireccion direccion, set<DtActualizacion> etapaPedidos){
	this->telefono = telefono;
	this->nombre = nombre;
	this->direccion = direccion;
	this->etapaPedidos = etapaPedidos;
}

//getters
string Cliente::getTelefono(){
	return this->telefono;
}

string Cliente::getNombre(){
	return this->nombre;
}

DtDireccion Cliente::getDireccion(){
	return this->direccion;
}

//patron observer
void Cliente::subscribirse() {
	ControladorVenta *cont_venta = ControladorVenta::getInstance();
	cont_venta -> subscribirCliente(this->telefono);
}

void Cliente::dessubscribirse() {
	ControladorVenta *cont_venta = ControladorVenta::getInstance();
	cont_venta -> desSubscribirCliente(string telefono);
}


void Cliente::bajaSuscripcion() {}
vector<DtActualizacion> Cliente::consultarPedidos() {
	return this -> etapaPedidos;
}
void Cliente::notificar(DtActualizacion actualizacion) {
	this -> etapaPedidos.push_back(actualizacion);
}
