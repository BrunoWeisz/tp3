#ifndef TP3_TABLA_H
#define TP3_TABLA_H

#include "../src/modulos_basicos/linear_set.h"
#include "Tipos.h"
#include "Registro.h"
#include "../src/modulos_basicos/string_map.h"

class Tabla {
private:

    linear_set<NombreCampo> _campos;
    NombreCampo _clave;
    linear_set<Registro> _registros;
    linear_set<Valor> _claves;
    string_map<Registro> _data;

public:

    Tabla(linear_set<NombreCampo> &campos, NombreCampo &clave); //O(1)

    linear_set<NombreCampo> &dar_campos();//const? //O(1) !!!!!!!!!!!!!!!!!!

    Valor &clave();//O(1)

    linear_set<Valor> &valores(); //Const? // O(1)

    linear_set<Registro> &registros();// Const? //O(1)  !!!!!!!!!!!!!!!!!!!11

    void insertar(Registro &r); //O(n*(|c| + |v|))

    void borrar(Valor v); //O(|v|) o bien O(n*(|v| + |c|))

    Registro &operator[](const Valor &clave); //O(|v|)

    bool esta(const Valor &clave); //O(|v|)


};


#endif //TP3_TABLA_H
