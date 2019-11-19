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
    Tabla* tMenos; //O(1)
    Tabla* tMas; //O(1)
    if (t1.registros().size() <= t2.registros().size()) {//O(1)
        tMenos=&t1; //O(1)
        tMas=&t2; //O(1)
    } else {
        tMenos=&t2; //O(1)
        tMas=&t1; //O(1)
    }
    linear_set<Valor>::iterator it = tMenos->valores().begin(); //O(1)?
    while (it != tMenos->valores().end()) { // lo hace min(n1,n2) veces
        Valor v1 = *it;
        //Si el valor para la clave de la tabla tMin del registro r1 es igual al valor para la clave de la tabla tablaMas
        if (tMas->esta(v1)) { //O(|v|)
            aDevolver.fast_insert(unirReg(tMenos->operator[](v1),tMas->operator[](v1))); // O(unirReg + agregarRegistroResultanteAConj)
            //                                ^                ^                         osea, O(|v|+|c|)*k
            //                                L O(|v|)         L O(|v|)
        }
    }
}

void Base_de_Datos::interFroms(Consulta &c, linear_set<Registro> &aDevolver) {
    Tabla t1=tablas[c.subconsulta1().nombre_tabla()];
    Tabla t2=tablas[c.subconsulta2().nombre_tabla()];
    Tabla* tMenos; //O(1)
    Tabla* tMas; //O(1)
    if (t1.registros().size() <= t2.registros().size()) {//O(1)
        tMenos=&t1; //O(1)
        tMas=&t2; //O(1)
    } else {
        tMenos=&t2; //O(1)
        tMas=&t1; //O(1)
    }
    linear_set<Valor>::iterator it = tMenos->valores().begin(); //O(1)?

    while(it!=tMenos->valores().end()){
        Valor v1= *it;
        if (tMas->esta(v1)) {//Osea comparten la misma clave O(|v|)
            aDevolver.fast_insert(tMenos->operator[](v1));
        }
    }


}


void Base_de_Datos::interSelects(Consulta &c, linear_set<Registro> &aDevolver) {
    Tabla t= tablas[c.subconsulta1().subconsulta1().nombre_tabla()];
    NombreCampo c1=c.subconsulta1().campo1();
    NombreCampo c2=c.subconsulta2().campo1();
    Valor v1=c.subconsulta1().valor();
    Valor v2=c.subconsulta2().valor();
    linear_set<Registro>::iterator it = t.registros().begin(); //O(1)?
    Registro r= *it;
    int posCampo1=r.damePosicion(c1);
    int posCampo2=r.damePosicion(c2);
    while(it!=t.registros().end()){
        r=*it;
        if(r.porNumero(posCampo1)==v1 && r.porNumero(posCampo2)==v2){
            aDevolver.fast_insert(r);
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
    }else if(c.tipo_consulta()==INTER &&c.subconsulta1().tipo_consulta()==FROM && c.subconsulta2().tipo_consulta()==FROM
    && tablas[c.subconsulta1().nombre_tabla()].dar_campos()==tablas[c.subconsulta2().nombre_tabla()].dar_campos()// tienen los mismos campos
    && tablas[c.subconsulta1().nombre_tabla()].clave()==tablas[c.subconsulta1().nombre_tabla()].clave()// tienen la misma clave
    ){
        interFroms(c,aDevolver);
    }else if(c.tipo_consulta()==INTER && c.subconsulta1().tipo_consulta()==SELECT && c.subconsulta2().tipo_consulta()==SELECT
    && c.subconsulta1().subconsulta1().tipo_consulta()==FROM && c.subconsulta2().subconsulta1().tipo_consulta()==FROM
    && c.subconsulta1().subconsulta1().nombre_tabla()==c.subconsulta2().subconsulta1().nombre_tabla()){
        interSelects(c,aDevolver);
    } else if (c.tipo_consulta() == FROM) {
        aDevolver = tablas.at(c.nombre_tabla()).registros();
    } else if (c.tipo_consulta() == SELECT) {
        select(c, aDevolver);
    }


    return aDevolver;
}
