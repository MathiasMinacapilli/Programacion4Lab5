#ifndef _CONTROLADORMESA_HPP
#define _CONTROLADORMESA_HPP

//Librerias de C
using namespace std;
#include <set>
#include <map>

//Archivos
#include "IMesa.hpp"
#include "Mesa.hpp"
#include "DtMesasMozo.hpp"
#include "ControladorVenta.hpp"
#include "ControladorEmpleado.hpp"

class ControladorMesa : public IMesa {
private:
    //constructor
    ControladorMesa();
    //instancia patron Singleton
    static ControladorMesa *instance;

    map<int, Mesa*> mesas;
    Mesa* mesa_recordada;
    int num_mozo_recordado;
    set<int> posibles_mesas;
    set<int> mesas_seleccionadas;
public:
    bool existeMesa(int num_mesa);
    //operacion patron Singleton
    static ControladorMesa *getInstance();
    //Facturación de una venta - generarFactura() - ControladorVenta
    void finalizarVenta();
    //Quitar Producto a una Venta - getProductosVenta() - ControladorVenta
    VentaLocal * obtenerVenta(int numero);
    //Iniciar Venta en Mesas
    set<int> getMesasMozoSinVentas(int num_mozo);
    void seleccionarMesasVenta(set<int> numeros);
    set<int> getMesasSeleccionadas();
    void agregarMesa(Mesa *m);
    void iniciarVenta();
    void cancelarVenta();
    //Caso de uso: Asignar automaticamente mozos a mesas
    map<int, DtMesasMozo> asignarMozosAMesas();
    map<int, Mesa*> getMesas();

    set<int> getNumeroMesas();

};

#endif
