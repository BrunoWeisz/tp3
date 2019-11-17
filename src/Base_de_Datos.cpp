//
// Created by Alejandro on 11/17/2019.
//

#include "Base_de_Datos.h"

//Como se escribia para devolver por referencia?
linear_set<Registro> Base_de_Datos::consultar(Consulta &c) {

    //1 y 2)De complejidad
    if (c.tipo_consulta() == SELECT && c.subconsulta1().tipo_consulta() == FROM) {
        string campo = c.campo1(); //O(|c|)
        string nombreDeLaTabla = c.subconsulta1().nombre_tabla();//O(|t|)
        string valor = c.valor(); //O(|v|)
        Tabla tabla = tablas.at(
                nombreDeLaTabla);// O(|t|) porque devuelve por referencia, solo tiene que encontrar a la tabla que, en un trie es O(|t|)
        linear_set<Registro> aDevolver; //O(1), creo el set de registros que voy a devolver.


        //Caso select con clave:
        if (campo == tabla.clave()) {//O(|c|)
            aDevolver.fast_insert(tabla[valor]);//O(1) el fast_insert y O(|v|) el tabla[valor] --> O(|v|)
            return aDevolver; //O(1) porque devuelvo por referencia??
            //Luego, si es select por clave en total es O(|c|+|v|+|t|)
        } else {
            linear_set<Registro>::iterator it = tabla.registros().begin();

            while (it != tabla.registros().end()) {
                Registro r = *it;
                if (r[campo] == valor) {
                    aDevolver.fast_insert(r);
                }
            }
            return aDevolver;
        }

        //Caso select sin clave:

    }
}
