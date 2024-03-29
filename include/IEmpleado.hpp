#ifndef _IEMPLEADO_HPP
#define _IEMPLEADO_HPP

//Librerias de C
#include <map>
#include <string>
#include <set>
using namespace std;

//Archivos
#include "Mozo.hpp"
#include "Repartidor.hpp"
#include "Transporte.hpp"
#include "DtFactura.hpp"
#include "DtMesasMozo.hpp"
#include "DtMozo.hpp"
#include "DtRepartidor.hpp"

class IEmpleado {
protected:
    //constructor protected porque es abstracta
    IEmpleado();
public:
    virtual Mozo *getMozo(int num_mozo) = 0;
    virtual void ingresarNombreEmpleado(string nombre) = 0;
    virtual set<Transporte> getTransportes() = 0;
    virtual set<int> getIdsRepartidor() = 0;
    virtual map<int, Repartidor*> getRepartidoresDisponibles() = 0;
    virtual void seleccionarTransporte(Transporte t) = 0;
    virtual void seleccionarRepartidor(int numero_repartidor) = 0;
    virtual Repartidor* getRepartidorRecordado() = 0;
    virtual void borrarNumero() = 0;
    virtual int ingresarRepartidor() = 0;
    virtual void cancelarRepartidor() = 0;
    virtual void ingresarMozo() = 0;
    virtual void cancelarMozo() = 0;
    //Caso de uso: Ventas de un Mozo
    virtual set<int> getIdsMozo() = 0;
    virtual void seleccionarIdyFechas(int id, DtFecha fecha_ini, DtFecha fecha_fin) = 0;
    virtual map<int, DtFactura> getVentasFacturadas() = 0;
    //Caso de uso: Modificar etapa de un pedido
    virtual void ingresarIdRepartidor(int id) = 0;
    virtual map<int, DtDireccion> getVentasRepartidor() = 0;
    virtual void ingresarNumeroPedido(int nro) = 0;
    virtual void avanzarEtapaPedido() = 0;
    virtual void cancelarPedido() = 0;

    virtual DtRepartidor getDatosIngresadosRepartidor() = 0;
    virtual DtMozo getDatosIngresadosMozo() = 0;

    virtual string getNombreMozo(int num_mozo) = 0;
    virtual string getNombreRepartidor(int num_repartidor) = 0;


    //destructor
    virtual ~IEmpleado(); // virtual y vacío
};

#endif
