
//Librerias de C
#include <set>
using namespace std;

//Archivos
#include "DtProducto.hpp";
#include "Producto.hpp";

class Venta {
private:
    int numero;
    float descuento;
public:
    virtual void agregarProductoAVenta(Producto prod);
    virtual bool buscarProducto(Producto p);
    virtual bool estaFacturada();
    virtual void eliminarProducto(Producto prod, int cantidad);
    virtual void facturar();
    virtual set<DtProducto> obtenerProductos();
};
