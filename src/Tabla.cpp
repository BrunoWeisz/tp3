#include "Tabla.h"

Tabla::Tabla(linear_set<NombreCampo> &campos, NombreCampo &clave) : _clave(clave), _campos(campos) {
    linear_set<Registro> registros;
    _registros = registros;
    linear_set<Valor> claves;
    _claves = claves;
    string_map<Registro> regs;
    _data = regs;
}

linear_set<NombreCampo> &Tabla::dar_campos() { //const?
    return _campos;
}

Valor &Tabla::clave() {
    return _clave;
}

linear_set<Registro> &Tabla::registros() { //Const?
    return _registros;
}

linear_set<Valor> &Tabla::valores() { //Const?
    return _claves;
}

bool Tabla::esta(const Valor &clave){
    return _data.count(clave)==1;
}


void Tabla::insertar(Registro &r) {
    Valor clav = r[_clave];
    bool estaba = false;

    linear_set<Registro>::iterator itRegistros = _registros.begin();
    while (itRegistros != _registros.end()){
        Registro re = *itRegistros;
        if (re[_clave] == clav) {
            _registros.erase(re);
            estaba = true;
            break;
        }
        ++itRegistros;
    }

    _registros.fast_insert(r);
    _data.insert(make_pair(clav, r));
    if (!estaba) {
        _claves.fast_insert(clav);
    }
}

void Tabla::borrar(Valor v) {
    if (_data.count(v) == 1) {
        _data.erase(v);
        _claves.erase(v);
        _registros.erase(_data[v]);
    }
}

Registro &Tabla::operator[](const Valor &clave) {
    return (_data[clave]);
}