#ifndef _CONTROLADOREMPLEADO_HPP
#define _CONTROLADOREMPLEADO_HPP

//Librerias de C
#include <map>
#include <math.h> /* floor */
using namespace std;

#include "IEmpleado.hpp"

//Archivos
#include "Mozo.hpp"
#include "Repartidor.hpp"
#include "DtMozo.hpp"
#include "DtRepartidor.hpp"
#include "ControladorMesa.hpp"

class ControladorEmpleado : public IEmpleado{
private:
	//instancia patron Singleton
	static ControladorEmpleado *instance;
	//Constructor
	ControladorEmpleado();
	//pseudoatributos que representan colecciones de empleados
	map<int, Mozo *> mozos;
	map<int, Repartidor *> repartidores;
	//contador de numeros de empleados
	int ultimo_id;
	//atributos de memoria controlador
	string nombre_recordado;
	int numero_repartidor;
	Transporte transporte_recordado;
	int id_mozo_recordado;
	DtFecha fecha_ini_recordada;
	DtFecha fecha_fin_recordada;
	int id_repartidor_recordado;
	int pedido_recordado;

public:
	//operacion patron Singleton
	static ControladorEmpleado *getInstance();
	Mozo* getMozo(int num_mozo);
	set<int> getIdsRepartidor();
	map<int, Repartidor*> getRepartidoresDisponibles();

	//Getters
	map<int, Mozo*> getMozos();

    //caso de uso: Alta empleado
    void ingresarNombreEmpleado(string nombre);
    set<Transporte> getTransportes();
    void seleccionarTransporte(Transporte t);
	void seleccionarRepartidor(int numero_repartidor);
    Repartidor* getRepartidorRecordado();
    void borrarNumero();
    int ingresarRepartidor();
    void cancelarRepartidor();
    void ingresarMozo();
    void cancelarMozo();
    //Caso de uso: Ventas de un Mozo
    set<int> getIdsMozo();
    void seleccionarIdyFechas(int id, DtFecha fecha_ini, DtFecha fecha_fin);
    map<int, DtFactura> getVentasFacturadas();
    //Caso de uso: Modificar estado de un pedido
    void ingresarIdRepartidor(int id);
    map<int, DtDireccion> getVentasRepartidor();
    void ingresarNumeroPedido(int nro);
    void avanzarEtapaPedido();
    void cancelarPedido();

	Repartidor* getRepartidor(int num_repartidor);

	DtRepartidor getDatosIngresadosRepartidor();
	DtMozo getDatosIngresadosMozo();

	string getNombreMozo(int num_mozo);
	string getNombreRepartidor(int num_repartidor);


	//cargar datos de prueba
	bool existeEmpleado(int num);

    //destructor
	~ControladorEmpleado();

};

#endif
