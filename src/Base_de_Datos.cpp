//
// Created by Alejandro on 11/17/2019.
//

#include "Base_de_Datos.h"
//FALTA COMPLETAR ESTEEEEEEEEEEEEEEE -----
//                                        |
//                                        V
Registro Base_de_Datos::unirReg(const Registro &r1, const Registro &r2) {
    Registro Union;

    return Union;
}


void Base_de_Datos::selectDeFrom(Consulta &c, linear_set<Registro> &aDevolver) {
    string campo = c.campo1(); //O(|c|)
    string nombreDeLaTabla = c.subconsulta1().nombre_tabla();//O(|t|)
    string valor = c.valor(); //O(|v|)
    Tabla tabla = tablas.at(
            nombreDeLaTabla);// O(|t|) porque devuelve por referencia, solo tiene que encontrar a la tabla que, en un trie es O(|t|)


    if (campo == tabla.clave()) {//O(|c|)
        //Caso select con clave:
        aDevolver.fast_insert(tabla[valor]);//O(1) el fast_insert y O(|v|) el tabla[valor] --> O(|v|)
        //Luego, si es select por clave en total es O(|c|+|v|+|t|)
    } else {
        //Caso select sin clave
        linear_set<Registro>::iterator it = tabla.registros().begin(); //O(1)?
        while (it != tabla.registros().end()) { //Hace n veces el ciclo (siendo n la cantidad de registros de la tabla)
            Registro r = *it; //Esto es por referencia o por copia?
            if (r[campo] == valor) {//O(|v|), pues r[campo] es O(1) ya que la cantidad de campos es constante
                aDevolver.fast_insert(r);
            }
        }
    }
}

void Base_de_Datos::select(Consulta &c, linear_set<Registro> &aDevolver) {
    linear_set<Registro> regSubCons = consultar(const_cast<Consulta &>(c.subconsulta1())); //No se que verga hice aca
    linear_set<Registro>::iterator it = regSubCons.begin(); //O(1)?
    while (it != regSubCons.end()) { //Hace n veces el ciclo (siendo n la cantidad de registros de la tabla)
        Registro r = *it; //Esto es por referencia o por copia?
        if (r[c.campo1()] == c.valor()) {//O(|v|), pues r[campo] es O(1) ya que la cantidad de campos es constante
            aDevolver.fast_insert(r);
        }
    }
}

void Base_de_Datos::joinConClaves(Consulta &c, linear_set<Registro> &aDevolver) {
    Tabla t1 = tablas.at(c.subconsulta1().subconsulta1().nombre_tabla()); //O(|t|)
    Tabla t2 = tablas.at(c.subconsulta1().subconsulta2().nombre_tabla()); //O(|t|)
    linear_set<Registro> regMenos;//O(1)
    Tabla tablaMas = t1;
    string claveMenos;
    if (t1.registros().size() <= t2.registros().size()) {//O(1)
        regMenos = t1.registros();//O(1)
        claveMenos = t1.clave();//O(|c|)
        tablaMas = t2;//O(1)
    } else {
        regMenos = t2.registros();//O(1)
        claveMenos = t2.clave();//O(|c|)
        tablaMas = t1;//O(1)
    }
    linear_set<Registro>::iterator it = regMenos.begin(); //O(1)?
    while (it != regMenos.end()) {
        Registro r1 = *it;
        //Si el valor para la clave de la tabla tMin del registro r1 es igual al valor para la clave de la tabla tablaMas
        if (r1[claveMenos] == tablaMas[r1[claveMenos]][tablaMas.clave()]) {
            aDevolver.fast_insert(unirReg(r1, tablaMas[r1[claveMenos]]));
        }
    }
}


//Como se escribia para devolver por referencia?
linear_set<Registro> Base_de_Datos::consultar(Consulta &c) {
    linear_set<Registro> aDevolver;
    //1 y 2)De complejidad
    if (c.tipo_consulta() == SELECT && c.subconsulta1().tipo_consulta() == FROM) {
        selectDeFrom(c, aDevolver);
    } else if (c.tipo_consulta() == MATCH && c.subconsulta1().tipo_consulta() == PRODUCT &&
               c.subconsulta1().subconsulta1().tipo_consulta() == FROM &&
               c.subconsulta1().subconsulta2().tipo_consulta() == FROM) {
        joinConClaves(c, aDevolver);
    } else if (c.tipo_consulta() == FROM) {
        aDevolver = tablas.at(c.nombre_tabla()).registros();
    } else if (c.tipo_consulta() == SELECT) {
        select(c, aDevolver);
    }


    return aDevolver;
}
