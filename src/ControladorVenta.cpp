//Librerias de C
#include <map>
#include <set>

//Archivos
#include "../include/ControladorVenta.hpp"
#include "../include/ControladorProducto.hpp"
#include "../include/ControladorMesa.hpp"
#include "../include/ControladorCliente.hpp"
#include "../include/DtFactura.hpp"


//inicializacion de instancia
ControladorVenta *ControladorVenta::instance = nullptr;

//constructor
ControladorVenta::ControladorVenta(){}

ControladorVenta *ControladorVenta::getInstance() {
  if (instance == nullptr)
    instance = new ControladorVenta();
  return instance;
}

//BAJA PRODUCTO - eliminarProducto - ControladorProducto
bool ControladorVenta::estaEnVentaSinFacturar(Producto *p) {
  map<int, VentaLocal*>::iterator it_local;
  bool encontre_producto = false;
  bool existe_factura;
  for(it_local = ventasLocales.begin(); ((it_local != ventasLocales.end()) && (!encontre_producto)); ++it_local) {
    existe_factura = (it_local -> second) -> estaFacturada();
    if (!existe_factura)
      encontre_producto = (it_local->second) -> buscarProducto(p);
  }
  return encontre_producto;
}

//INICIAR VENTA EN MESAS - iniciarVenta - ControladorMesa
VentaLocal *ControladorVenta::crearVenta() {
  VentaLocal *ve = new VentaLocal((this -> numero_venta) + 1, 0, nullptr);
  (this -> numero_venta)++;
  ventasLocales.insert(pair<int, VentaLocal *>(ve -> getNumero(), ve));
  return ve;
}

//AGREGAR PRODUCTO A UNA VENTA
void ControladorVenta::ingresarNumeroMesa(int numero) {
    ControladorMesa* cont_mesa = ControladorMesa::getInstance();
    if (cont_mesa -> existeMesa(numero)){
        this -> numero_mesa = numero;
    } else {
        throw new invalid_argument("\nNo existe mesa asociada al número ingresado.");
    }
}
map<int, DtProducto> ControladorVenta::obtenerProductosDisponibles() {
  ControladorProducto *cont_prod;
  cont_prod = ControladorProducto::getInstance();
  map<int, DtProducto> dtprods = cont_prod -> getProductosDisponibles();
  return dtprods;
}
void ControladorVenta::seleccionarProdYCant(DtProductoCantidad producto_cantidad) {
  ControladorProducto *cont_prod;
  cont_prod = ControladorProducto::getInstance();
  Producto* prod = cont_prod -> encontrarProducto(producto_cantidad);
  this -> prod = prod;
  this -> cantidad = producto_cantidad.getCantidad();
}
void ControladorVenta::agregarProductoAVenta() {
  ControladorMesa *cont_mesa;
  cont_mesa = ControladorMesa::getInstance();
  Venta* v = cont_mesa -> obtenerVenta(this -> numero_mesa);
  v -> agregarProductoAVenta(this -> prod, this -> cantidad);
}
void ControladorVenta::cancelarProductoAVenta() {
  prod = nullptr;
  cantidad = 0;
  numero_mesa = 0;
  v = nullptr;
}

//QUITAR PRODUCTO A VENTA
map<int, DtProducto> ControladorVenta::getProductosVenta (int numMesa) {
  ControladorMesa *cont_mesa;
  cont_mesa = ControladorMesa::getInstance();
  Venta* v = cont_mesa -> obtenerVenta(this -> numero_mesa);
  map<int, DtProducto> productos_venta = v -> obtenerProductos();
  this -> v = v;
  return productos_venta;
}
//seleccionarProdYCant
void ControladorVenta::eliminarProductoDeVenta() {
  (this -> v) -> eliminarProducto(this -> prod, this -> cantidad);
}
void ControladorVenta::cancelarEliminarProductoDeVenta() {
  //QUE ONDA CON ESTO?
  //QUE ES LIBERAR LA MEMORIA??
  // AYUDAAA!!
  prod = nullptr;
  cantidad = 0;
  v = nullptr;
}

//FACTURACION DE UNA VENTA
//ingresarNumeroMesa
void ControladorVenta::ingresarPorcentajeDescuento(float descuento) {
  ControladorMesa *cont_mesa;
  cont_mesa = ControladorMesa::getInstance();
  VentaLocal *v = cont_mesa -> obtenerVenta(this -> numero_mesa);
  v -> setDescuento(descuento);
}

DtFactura* ControladorVenta::generarFactura() {
  ControladorMesa *cont_mesa;
  cont_mesa = ControladorMesa::getInstance();
  VentaLocal *v = cont_mesa -> obtenerVenta(this -> numero_mesa);
  DtFactura* factura = v -> facturar();
  cont_mesa -> finalizarVenta();
  return factura;
}

//VENTA A DOMICILIO
//FALTAN OP
//FALTAN OP
//FALTAN OP
//FALTAN OP
//FALTAN OP
//FALTAN OP
bool ControladorVenta::ingresarTelefono(string telefono) {
    this -> telefono_recordado = telefono;
    ControladorCliente *cont_cliente;
    cont_cliente = ControladorCliente::getInstance();
    return (cont_cliente -> existeCliente(telefono));
}

//obtenerProductosDisponibles

void ControladorVenta::almacenarProducto(DtProductoCantidad prod_y_cant) {
    ControladorProducto *cont_prod;
    cont_prod = ControladorProducto::getInstance();
    contr_prod -> seleccionarProductoYCantidad(prod_y_cant);
}

map<int, Repartidor*> ControladorVenta::obtenerRepartidores() {
    ControladorEmpleado *cont_emp;
    cont_emp = ControladorEmpleado::getInstance();
    map<int, Repartidor*> repartidores = cont_emp -> getRepartidoresDisponibles();
    return repartidores;
}

void ControladorVenta::elegirRepartidor(int numero_repartidor) {
    ControladorEmpleado *cont_emp;
    cont_emp = ControladorEmpleado::getInstance();
    cont_emp -> seleccionarRepartidor(numero_repartidor);
}

void ControladorVenta::crearVentaADomicilio(bool quiere_repartidor) {
    ControladorProducto *cont_prod;
    cont_prod = ControladorProducto::getInstance();
    ControladorCliente *cont_cliente;
    cont_cliente = ControladorCliente::getInstance();
    this -> numero_venta++;
    map<int, CantidadProducto*> cant_prods = cont_prod -> getProductosAlmacenados();
    if (quiere_repartidor) {
        ControladorEmpleado *cont_emp;
        cont_emp = ControladorEmpleado::getInstance();
    } else {
        
    }
}

void ControladorVenta::cancelarVentaADomicilio() {
    //QUE ONDA CON ESTO?
    //QUE ES LIBERAR LA MEMORIA??
    // AYUDAAA!!
    prod = nullptr;
    cantidad = 0;
    v = nullptr;
}

DtFactura* ControladorVenta::generarFacturaDomiclio() {
  DtFactura* factura = venta_domicilio -> facturar();
  return factura;
}

//RESUMEN FACTURACION DE 1 DIA DADA LA FECHA
void ControladorVenta::ingresarFecha(DtFecha fecha) {
  this -> fecha_venta = fecha;
}

map<int, DtFactura> ControladorVenta::getFacturasYTotalFecha(float &totalfacturado) {
  map<int, VentaLocal *>::iterator it_local;
  map<int, VentaADomicilio *>::iterator it_domicilio;
  map<int, DtFactura> res;
  VentaLocal* ventalocal;
  VentaADomicilio *ventadomicilio;
  Factura* factura;
  DtFactura dtfactura;
  totalfacturado = 0;
  for(it_local = ventasLocales.begin(); it_local != ventasLocales.end(); ++it_local) {
    ventalocal = it_local -> second;
    if (ventalocal -> estaFacturada()) {
      factura = ventalocal -> getFactura();
      DtFecha fecha_factura = DtFecha((factura -> getFechaYHora()).getDia(), (factura -> getFechaYHora()).getMes(), (factura -> getFechaYHora()).getAnio());
      if (fecha_factura == this -> fecha_venta) {
        dtfactura = factura -> getDatosFactura();
        res.insert(pair<int, DtFactura>(dtfactura.getCodigo(), dtfactura));
        totalfacturado +=  dtfactura.getPrecioTotal();
      }
    }
  }
  for(it_domicilio = ventasDomicilio.begin(); it_domicilio != ventasDomicilio.end(); ++it_domicilio) {
    ventadomicilio = it_domicilio -> second;
    if (ventalocal -> estaFacturada()) {
      factura = ventadomicilio -> getFactura();
      DtFecha fecha_factura = DtFecha((factura -> getFechaYHora()).getDia(), (factura -> getFechaYHora()).getMes(), (factura -> getFechaYHora()).getAnio());
      if (fecha_factura == this -> fecha_venta) {
        dtfactura = factura -> getDatosFactura();
        res.insert(pair<int, DtFactura>(dtfactura.getCodigo(), dtfactura));
        totalfacturado +=  dtfactura.getPrecioTotal();
      }
    }
  }
  return res;
}

//CONSULTAR ACTUALIZACIONES DE PEDIDOS A DOMICILIO POR PARTE DEL ADMINISTRADOR
vector<DtActualizacion> ControladorVenta::getListadoActualizaciones() {
  vector<DtActualizacion> aux;
  vector<DtActualizacion> res;
  res.clear();
  map<int, VentaADomicilio *>::iterator it;
  for (it = this->ventasDomicilio.begin(); it != this->ventasDomicilio.end(); ++it){
      aux = (it -> second) -> getActualizaciones();
      res.insert(res.end(), aux.begin(), aux.end() );
  }
  return res;

}


//funciones auxiliares para implementar patron Observer
void ControladorVenta::suscribirCliente(string telefono){
  map<int, VentaADomicilio *>::iterator it;
  for (it = this->ventasDomicilio.begin(); it != this->ventasDomicilio.end(); ++it){
    Cliente *cliente = it->second->getCliente();
    if (cliente->getTelefono() == telefono)
      it->second->setObservador(cliente);
  }
}


void ControladorVenta::desSuscribirCliente(string telefono){
  map<int, VentaADomicilio *>::iterator it;
  for (it = this->ventasDomicilio.begin(); it != this->ventasDomicilio.end(); ++it){
    Cliente *cliente = it->second->getCliente();
    if (cliente->getTelefono() == telefono)
      it->second->borrarObservador();
  }
}

vector<DtActualizacion> getActualizacionesCliente(string telefono){
  ControladorCliente *cont_cliente = ControladorCliente::getInstance();
  Cliente *cliente = cont_cliente->getCliente(telefono);
  if (cliente != nullptr)
    return cliente->consultarPedidos();
}