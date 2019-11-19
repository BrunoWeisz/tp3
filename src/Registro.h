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
    ~Registro();
    set<NombreCampo> campos() const;
    Valor& operator[](const NombreCampo& campo);
    const Valor& operator[](const NombreCampo& campo) const;
    void operator+( Registro &r);
    Valor& porNumero(const int a);
    void definir(NombreCampo n, Valor v);
    int damePosicion(const NombreCampo& campo);

private:
    // COMPLETAR con la representación privada.

    //Esto seria mi idea, cualquier cosa comentenlo.
    struct tripla {
        int posicionEnArreglo;
        NombreCampo campo;
        Valor valor;
        tripla(int pos, NombreCampo camp,Valor val) : posicionEnArreglo(pos), campo(camp), valor(val) {};
    };

    vector<tripla*> _ordenados;
    string_map<tripla> _valorEnCampo;
    set<NombreCampo> _campos;



};

#endif /*__REGISTRO_H__*/
