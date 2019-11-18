#ifndef __REGISTRO_H__
#define __REGISTRO_H__

#include <set>
#include <vector>

#include "Tipos.h"
#include "modulos_basicos/string_map.h"

using namespace std;

class Registro {
public:
    Registro();
    set<NombreCampo> campos() const;
    Valor& operator[](const NombreCampo& campo);
    Valor& porNumero(const int a);
    int damePosicion(const NombreCampo& campo);

private:
    // COMPLETAR con la representación privada.

    //Esto seria mi idea, cualquier cosa comentenlo.

    vector<Valor> valores;
    string_map <int> dameCampos;

};

#endif /*__REGISTRO_H__*/
