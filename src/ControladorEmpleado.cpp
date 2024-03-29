//Archivos
#include "../include/ControladorEmpleado.hpp"

ControladorEmpleado *ControladorEmpleado::instance = nullptr;

ControladorEmpleado::ControladorEmpleado(){
	this->ultimo_id = 0;
}

ControladorEmpleado *ControladorEmpleado::getInstance(){
	if (instance == nullptr)
		instance = new ControladorEmpleado();
	return instance;
}

Mozo *ControladorEmpleado::getMozo(int num_mozo){
	map<int, Mozo*>::iterator it = this->mozos.find(num_mozo);
	if (it != mozos.end())
		return it->second;
	else
		throw new invalid_argument("No existe mozo con el ID ingresado");
}


map<int, Repartidor*> ControladorEmpleado::getRepartidoresDisponibles() {
	map<int, Repartidor*> res;
	map<int, Repartidor*>::iterator it;
	for(it = repartidores.begin(); it != repartidores.end(); ++it)
		res[it -> second -> getNumero()] = it -> second;
	return res;
}


/* Retorna la coleccion de mozos almacenada en el controlador */
map<int, Mozo *> ControladorEmpleado::getMozos() {
	return this->mozos;
}

//ALTA EMPLEADO

void ControladorEmpleado::ingresarNombreEmpleado(string nombre){
	this->nombre_recordado = nombre;
}

set<Transporte> ControladorEmpleado::getTransportes(){
	Transporte t1, t2, t3;
	t1 = Bici;
	t2 = Moto;
	t3 = Pie;
	set<Transporte> transportes;
 	transportes.insert(t1);
 	transportes.insert(t2);
 	transportes.insert(t3);
 	return transportes;
}

void ControladorEmpleado::seleccionarTransporte(Transporte t){
	this->transporte_recordado = t;
}

void ControladorEmpleado::seleccionarRepartidor(int numero_repartidor) {
	this -> numero_repartidor = numero_repartidor;
}

Repartidor* ControladorEmpleado::getRepartidorRecordado(){
	map<int, Repartidor *>::iterator it = this -> repartidores.find(numero_repartidor);
	if (it != this->repartidores.end())
		return (it -> second);
	else
		throw new invalid_argument("No existe repartidor con el ID ingresado");
}

void ControladorEmpleado::borrarNumero() {
    this -> numero_repartidor = 0;
}

int ControladorEmpleado::ingresarRepartidor(){
	this->ultimo_id++;
	Repartidor *nuevo_repartidor = new Repartidor(this->ultimo_id, this->nombre_recordado, this->transporte_recordado);
	//agrego repartidor a la coleccion de repartidores
	this->repartidores[nuevo_repartidor->getNumero()] = nuevo_repartidor;
	//"se olvida" del nombre recordado
	this->nombre_recordado = ' ';
	return nuevo_repartidor->getNumero();
}

void ControladorEmpleado::cancelarRepartidor(){
	//"se olvida" del nombre recordado
	this->nombre_recordado = ' ';
}

void ControladorEmpleado::ingresarMozo(){
	this->ultimo_id++;
	Mozo *nuevo_mozo = new Mozo(this->ultimo_id, this->nombre_recordado);
	//agrego mozo a la coleccion de mozo
	this->mozos[nuevo_mozo->getNumero()] = nuevo_mozo;
	//"se olvida" del nombre recordado
	this->nombre_recordado = ' ';
}
void ControladorEmpleado::cancelarMozo(){
	//"se olvida" del nombre recordado
	this->nombre_recordado = ' ';
}

//Caso de uso: Ventas de un Mozo
/* Retorna un set de int que contienen todos los id de los mozos */
set<int> ControladorEmpleado::getIdsMozo() {
	set<int> ret;
	map<int, Mozo*>::iterator it;
	for(it = this->mozos.begin(); it != this->mozos.end(); ++it)
		ret.insert((it->second)->getNumero());
	return ret;
}

set<int> ControladorEmpleado::getIdsRepartidor() {
	map<int, Repartidor*>::iterator it;
	set<int> res;
	res.clear();
	for(it = this -> repartidores.begin(); it != this -> repartidores.end(); ++it)
		res.insert(it -> first);
	return res;
}

/* Selecciona el id y el rango de fechas para obtener las ventas facturadas*/
void ControladorEmpleado::seleccionarIdyFechas(int id, DtFecha fecha_ini, DtFecha fecha_fin) {
	this->id_mozo_recordado = id;
	this->fecha_ini_recordada = fecha_ini;
	this->fecha_fin_recordada = fecha_fin;
}
/* Retorna una coleccion de DtFactura que representa las ventas facturadas
asociadas al mozo que tiene el id que se selecciono */
map<int, DtFactura> ControladorEmpleado::getVentasFacturadas() {
	map<int, DtFactura> res;
	ControladorVenta* cont_venta = ControladorVenta::getInstance();
	res = cont_venta->getVentasLocalesDelMozoFacturadas(this->id_mozo_recordado, this->fecha_ini_recordada, this->fecha_fin_recordada);
	return res;
}

//MODIFICAR ETAPA PEDIDO
void ControladorEmpleado::ingresarIdRepartidor(int id){
	map<int, Repartidor *>::iterator it = this->repartidores.find(id);
	if (it != this->repartidores.end()){
		this -> id_repartidor_recordado = id;
	}
	else throw new invalid_argument("No existe repartidor con el ID ingresado");
}

map<int, DtDireccion> ControladorEmpleado::getVentasRepartidor(){
	map<int, DtDireccion> resultado;
	ControladorVenta *cont_venta = ControladorVenta::getInstance();
	map<int, VentaADomicilio *> ventas_repartidor = cont_venta->obtenerVentasRepartidor(this->id_repartidor_recordado);
	map<int, VentaADomicilio *>::iterator it;
	for (it = ventas_repartidor.begin(); it != ventas_repartidor.end(); ++it){
		DtDireccion dir = it->second->getCliente()->getDireccion();
		int numero = it->second->getNumero();
		resultado[numero] = dir;
	}
	return resultado;
}

void ControladorEmpleado::ingresarNumeroPedido(int nro){
	this -> pedido_recordado = nro;
}

void ControladorEmpleado::avanzarEtapaPedido(){
	ControladorVenta *cont_venta = ControladorVenta::getInstance();
	map<int, VentaADomicilio *> ventas_repartidor = cont_venta->obtenerVentasRepartidor(this->id_repartidor_recordado);
	VentaADomicilio *venta = ventas_repartidor[this->pedido_recordado];
	venta->avanzarEtapaVenta();
}

void ControladorEmpleado::cancelarPedido(){
	ControladorVenta *cont_venta = ControladorVenta::getInstance();
	map<int, VentaADomicilio *> ventas_repartidor = cont_venta->obtenerVentasRepartidor(this->id_repartidor_recordado);
	VentaADomicilio *venta = ventas_repartidor[this->pedido_recordado];
	venta->cancelarVenta();
}

//cargar datos de prueba
Repartidor *ControladorEmpleado::getRepartidor(int numero_repartidor){
	map<int, Repartidor *>::iterator it = this->repartidores.find(numero_repartidor);
	if (it != this->repartidores.end())
		return it->second;
	else throw new invalid_argument("No existe repartidor con el ID ingresado");
}
bool ControladorEmpleado::existeEmpleado(int num){
	map<int, Mozo*>::iterator it_mozos = this->mozos.find(num);
	map<int, Repartidor *>::iterator it_rep = this->repartidores.find(num);
	if (it_mozos == this->mozos.end())
		if (it_rep == this->repartidores.end())
			return false;
		else return true;

	else
		return true;
}


DtRepartidor ControladorEmpleado::getDatosIngresadosRepartidor(){
	DtRepartidor datos = DtRepartidor(this->ultimo_id, this->nombre_recordado, this->transporte_recordado);
	return datos;
}

DtMozo ControladorEmpleado::getDatosIngresadosMozo(){
	DtMozo datos = DtMozo(this->ultimo_id, this->nombre_recordado);
	return datos;
}

string ControladorEmpleado::getNombreMozo(int num_mozo) {
	map<int, Mozo*>::iterator it = this->mozos.find(num_mozo);
	if(it != this->mozos.end()) {
		Mozo *mozo = getMozo(num_mozo);
		return mozo -> getNombre();
	} else
		throw new invalid_argument("No existe mozo con el ID ingresado");
}

string ControladorEmpleado::getNombreRepartidor(int num_repartidor) {
	map<int, Repartidor*>::iterator it = this -> repartidores.find(num_repartidor);
	if (it != this -> repartidores.end()) {
		Repartidor *repartidor = getRepartidor(num_repartidor);
		return repartidor -> getNombre();
	} else
		throw new invalid_argument ("No existe repartidor con el ID ingresado");
}

//destructor
ControladorEmpleado::~ControladorEmpleado(){}
