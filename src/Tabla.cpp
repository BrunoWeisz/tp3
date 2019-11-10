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

void Tabla::insertar(Registro &r) {
    Valor clav = r[_clave];
    bool estaba = false;
    for (Registro re : _registros) {
        if (re[_clave] == clav) {
            _registros.erase(re);
            estaba = true;
            break;
        }
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