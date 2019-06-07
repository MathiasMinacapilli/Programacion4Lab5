//Archivos
#include "../include/DtActualizacion.hpp"

DtActualizacion::DtActualizacion(DtFechaYHora fechaYHora, string nombre, string telefono, set<DtProducto> datosProducto, string nombreRepartidor, Etapa* etapaActual) {
    this->fechaYHora = fechaYHora;
    this->nombre = nombre;
    this->telefono = telefono;
    this->datosProducto = datosProducto;
    this->nombreRepartidor = nombreRepartidor;
    this->etapaActual = etapaActual;
}
    
DtFechaYHora DtActualizacion::getFechaYHora() const{
    return this->fechaYHora;
}

string DtActualizacion::getNombre() {
    return this->nombre;
}

string DtActualizacion::getTelefono() {
    return this->telefono;
}

set<DtProducto> DtActualizacion::getDatosProducto() {
    return this->datosProducto;
}

string DtActualizacion::getNombreRepartidor() {
    return this->nombreRepartidor;
}

Etapa* DtActualizacion::getEtapaActual() {
    return this->etapaActual;
}

bool DtActualizacion::operator<(const DtActualizacion &act2) const{
    DtFechaYHora dt_fecha_hora1 = this->fechaYHora;
    DtFechaYHora dt_fecha_hora2 = act2.getFechaYHora();
    return (dt_fecha_hora1 <= dt_fecha_hora2);
}

DtActualizacion::~DtActualizacion() {}
