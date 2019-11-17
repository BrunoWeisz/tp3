//
// Created by Alejandro on 11/17/2019.
//

#ifndef TP3_BASE_DE_DATOS_H
#define TP3_BASE_DE_DATOS_H

#include "../src/modulos_basicos/linear_set.h"
#include "Tipos.h"
#include "Registro.h"
#include "../src/modulos_basicos/string_map.h"
#include "Tabla.h"
#include "Consulta.h"

class Base_de_Datos {

private:

string_map<Tabla> tablas;

public:

linear_set<Registro> consultar(Consulta &c);

};


#endif //TP3_BASE_DE_DATOS_H
