#include "Registro.h"

Registro::Registro() {
    //COMPLETAR(Registro);
}

set<NombreCampo> Registro::campos() const {
    //COMPLETAR(campos);
}

Valor& Registro::operator[](const NombreCampo& campo) {
    //COMPLETAR(operator[]);
}


Valor& Registro:: porNumero(const int a){
    return valores[a];
}

int Registro:: damePosicion(const NombreCampo& campo){
    int a=dameCampos.at(campo);
    return a;
}
