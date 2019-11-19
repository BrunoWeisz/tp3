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
Registro unirReg(Registro& r1, Registro& r2);

public:

linear_set<Registro> consultar(Consulta &c);
void selectDeFrom(Consulta &c, linear_set<Registro> &aDevolver);
void joinConClaves(Consulta &c, linear_set<Registro> &aDevolver);
void interFroms(Consulta &c, linear_set<Registro> &aDevolver);
void interSelects(Consulta &c, linear_set<Registro> &aDevolver);
void select(Consulta &c, linear_set<Registro> &aDevolver);
void match(Consulta &c, linear_set<Registro> &aDevolver);
void proj(Consulta &c, linear_set<Registro> &aDevolver);
void rename(Consulta &c, linear_set<Registro> &aDevolver);
void inter(Consulta &c, linear_set<Registro> &aDevolver);
void Union(Consulta &c, linear_set<Registro> &aDevolver);
void product(Consulta &c, linear_set<Registro> &aDevolver);







};


#endif //TP3_BASE_DE_DATOS_H
