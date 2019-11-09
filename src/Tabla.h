#ifndef TP3_TABLA_H
#define TP3_TABLA_H

#include "../src/modulos_basicos/linear_set.h"
#include "Tipos.h"
#include "Registro.h"
#include "string_map.h"

class Tabla {
private:

    linear_set<NombreCampo> _campos;
    NombreCampo _clave;
    linear_set<Registro> _registros;
    linear_set<Valor> _claves;
    string_map<Registro> _data;

public:



};


#endif //TP3_TABLA_H
