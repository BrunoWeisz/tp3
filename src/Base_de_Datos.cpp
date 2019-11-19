//
// Created by Alejandro on 11/17/2019.
//

#include "Base_de_Datos.h"

//FALTA COMPLETAR ESTEEEEEEEEEEEEEEE -----
//                                        |
//                                        V


//OJO NO ME ESTA DEJANDO AUMENTAR LOS ITERADORES
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
        Registro r = *it;
        int posCampo = r.damePosicion(campo);
        while (it != tabla.registros().end()) { //Hace n veces el ciclo (siendo n la cantidad de registros de la tabla)
            r = *it; //Esto es por referencia o por copia?
            if (r.porNumero(posCampo) == valor) {//O(|v|),
                aDevolver.fast_insert(r);
            }
            ++it;
        }
    }
}

void Base_de_Datos::joinConClaves(Consulta &c, linear_set<Registro> &aDevolver) {
    Tabla t1 = tablas.at(c.subconsulta1().subconsulta1().nombre_tabla()); //O(|t|)
    Tabla t2 = tablas.at(c.subconsulta1().subconsulta2().nombre_tabla()); //O(|t|)
    Tabla *tMenos; //O(1)
    Tabla *tMas; //O(1)
    if (t1.registros().size() <= t2.registros().size()) {//O(1)
        tMenos = &t1; //O(1)
        tMas = &t2; //O(1)
    } else {
        tMenos = &t2; //O(1)
        tMas = &t1; //O(1)
    }
    linear_set<Valor>::iterator it = tMenos->valores().begin(); //O(1)?
    while (it != tMenos->valores().end()) { // lo hace min(n1,n2) veces
        Valor v1 = *it;
        //Si el valor para la clave de la tabla tMin del registro r1 es igual al valor para la clave de la tabla tablaMas
        if (tMas->esta(v1)) { //O(|v|)
            aDevolver.fast_insert(unirReg(tMenos->operator[](v1),
                                          tMas->operator[](v1))); // O(unirReg + agregarRegistroResultanteAConj)
            //                                ^                ^                         osea, O(|v|+|c|)*k
            //                                L O(|v|)         L O(|v|)
        }

        ++it;
    }
}

void Base_de_Datos::interFroms(Consulta &c, linear_set<Registro> &aDevolver) {
    Tabla t1 = tablas[c.subconsulta1().nombre_tabla()];
    Tabla t2 = tablas[c.subconsulta2().nombre_tabla()];
    Tabla *tMenos; //O(1)
    Tabla *tMas; //O(1)
    if (t1.registros().size() <= t2.registros().size()) {//O(1)
        tMenos = &t1; //O(1)
        tMas = &t2; //O(1)
    } else {
        tMenos = &t2; //O(1)
        tMas = &t1; //O(1)
    }
    linear_set<Valor>::iterator it = tMenos->valores().begin(); //O(1)?

    while (it != tMenos->valores().end()) {
        Valor v1 = *it;
        if (tMas->esta(v1)) {//Osea comparten la misma clave O(|v|)
            aDevolver.fast_insert(tMenos->operator[](v1));
        }

        ++it;
    }


}


void Base_de_Datos::interSelects(Consulta &c, linear_set<Registro> &aDevolver) {
    Tabla t = tablas[c.subconsulta1().subconsulta1().nombre_tabla()];
    NombreCampo c1 = c.subconsulta1().campo1();
    NombreCampo c2 = c.subconsulta2().campo1();
    Valor v1 = c.subconsulta1().valor();
    Valor v2 = c.subconsulta2().valor();
    linear_set<Registro>::iterator it = t.registros().begin(); //O(1)?
    Registro r = *it;
    int posCampo1 = r.damePosicion(c1);
    int posCampo2 = r.damePosicion(c2);
    while (it != t.registros().end()) {
        r = *it;
        if (r.porNumero(posCampo1) == v1 && r.porNumero(posCampo2) == v2) {
            aDevolver.fast_insert(r);
        }

        ++it;
    }
}

void Base_de_Datos::select(Consulta &c, linear_set<Registro> &aDevolver) { //O(|c|+k*|v|+ r*(|v|+|c|)), con k=#registrosSubconsulta y r=#registrosFinal
    linear_set<Registro> regSubCons = consultar(const_cast<Consulta &>(c.subconsulta1())); //No se que verga hice aca
    linear_set<Registro>::iterator it = regSubCons.begin(); //O(1)?
    Registro r=*it;
    int campoPos=r.damePosicion(c.campo1());//O(|c|)
    while (it != regSubCons.end()) { //Hace n veces el ciclo (siendo n la cantidad de registros de la tabla)
         r = *it; //Esto es por referencia o por copia?
        if (r.porNumero(campoPos) == c.valor()) {//O(|v|)
            aDevolver.fast_insert(r); //O(|v|+|c|)
        }
        ++it;
    }
}

void Base_de_Datos::match(Consulta &c, linear_set<Registro> &aDevolver) {//O(|c|+k*|v|+ r*(|v|+|c|)), con k=#registrosSubconsulta y r=#registrosFinal
    NombreCampo campo1=c.campo1();
    NombreCampo campo2=c.campo2();
    linear_set<Registro> regSubCons = consultar(const_cast<Consulta &>(c.subconsulta1())); //No se que verga hice aca
    linear_set<Registro>::iterator it = regSubCons.begin(); //O(1)?
    Registro r=*it;
    int campo1Pos=r.damePosicion(c.campo1());//O(|c|)
    int campo2Pos=r.damePosicion(c.campo2());//O(|c|)

    while(it!=regSubCons.end()){
        r=*it;
        if(r.porNumero(campo1Pos)==r.porNumero(campo2Pos)){//O(|v)
            aDevolver.fast_insert(r); //O(|v|+|c|)
        }

        ++it;
    }
}

void Base_de_Datos::proj(Consulta &c, linear_set<Registro> &aDevolver) {
    linear_set<Registro> regSubCons = consultar(const_cast<Consulta &>(c.subconsulta1())); //No se que verga hice aca
    linear_set<Registro>::iterator it = regSubCons.begin(); //O(1)?
    Registro r=*it;

    while(it!=regSubCons.end()){
        r=*it;
        Registro aAgregar=Registro();

        for(NombreCampo n : r.campos()){
            if(c.conj_campos().count(n)==1){
                aAgregar.definir(n,r.operator[](n));
            }
        }

        aDevolver.fast_insert(aAgregar);

        ++it;
    }
}

void Base_de_Datos::rename(Consulta &c, linear_set<Registro> &aDevolver) {
    linear_set<Registro> regSubCons = consultar(const_cast<Consulta &>(c.subconsulta1())); //No se que verga hice aca
    linear_set<Registro>::iterator it = regSubCons.begin(); //O(1)?

    Registro r=*it;

    while(it!=regSubCons.end()){
        r=*it;
        Registro aAgregar=Registro();

        for(NombreCampo n : r.campos()){
            if(n==c.campo1()){
                aAgregar.definir(c.campo1(),r.operator[](n));
            }else{
                aAgregar.definir(c.campo1(),r.operator[](n));
            }
        }
        aDevolver.fast_insert(aAgregar);
        ++it;
    }
}

void Base_de_Datos::inter(Consulta &c, linear_set<Registro> &aDevolver) {
    linear_set<Registro> regSubCons1 = consultar(const_cast<Consulta &>(c.subconsulta1())); //No se que verga hice aca
    linear_set<Registro> regSubCons2 = consultar(const_cast<Consulta &>(c.subconsulta2())); //No se que verga hice aca
    linear_set<Registro>::iterator fin = regSubCons1.end(); //O(1)?
    linear_set<Registro>::iterator it = regSubCons1.begin(); //O(1)?
    linear_set<Registro>* otro=&regSubCons2;
    if(regSubCons1.size()>regSubCons2.size()){
        it=regSubCons2.begin();
        fin=regSubCons2.end();
        otro=&regSubCons1;
    }

    while(it!=fin){
        Registro r= *it;
        if(otro->count(r)==1){
            aDevolver.fast_insert(r);
        }
        ++it;
    }
}

void Base_de_Datos::Union(Consulta &c, linear_set<Registro> &aDevolver) {
    linear_set<Registro> regSubCons1 = consultar(const_cast<Consulta &>(c.subconsulta1())); //No se que verga hice aca
    linear_set<Registro> regSubCons2 = consultar(const_cast<Consulta &>(c.subconsulta2())); //No se que verga hice aca
    for(Registro r: regSubCons1){
        aDevolver.fast_insert(r);
    }

    for(Registro r: regSubCons2){
        aDevolver.insert(r);
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
    } else if (c.tipo_consulta() == INTER && c.subconsulta1().tipo_consulta() == FROM &&
               c.subconsulta2().tipo_consulta() == FROM
               && tablas[c.subconsulta1().nombre_tabla()].dar_campos() ==
                  tablas[c.subconsulta2().nombre_tabla()].dar_campos()// tienen los mismos campos
               && tablas[c.subconsulta1().nombre_tabla()].clave() ==
                  tablas[c.subconsulta1().nombre_tabla()].clave()// tienen la misma clave
            ) {
        interFroms(c, aDevolver);
    } else if (c.tipo_consulta() == INTER && c.subconsulta1().tipo_consulta() == SELECT &&
               c.subconsulta2().tipo_consulta() == SELECT
               && c.subconsulta1().subconsulta1().tipo_consulta() == FROM &&
               c.subconsulta2().subconsulta1().tipo_consulta() == FROM
               && c.subconsulta1().subconsulta1().nombre_tabla() == c.subconsulta2().subconsulta1().nombre_tabla()) {
        interSelects(c, aDevolver);
    } else if (c.tipo_consulta() == FROM) {
        aDevolver = tablas.at(c.nombre_tabla()).registros();
    } else if (c.tipo_consulta() == SELECT) {
        select(c, aDevolver);
    } else if( c.tipo_consulta()==MATCH){
        match(c,aDevolver);
    }else if(c.tipo_consulta()==PROJ){
        proj(c,aDevolver);
    }else if(c.tipo_consulta()==RENAME){
        rename(c,aDevolver);
    }else if (c.tipo_consulta()==INTER){
        inter(c,aDevolver);
    }else if(c.tipo_consulta()==UNION){
        Union(c,aDevolver);
    }


    return aDevolver;
}
