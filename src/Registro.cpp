#include "Registro.h"

Registro::Registro() {
    //COMPLETAR(Registro);
}

Registro::~Registro() {
    //COMPLETAR(Registro);
    for(int i=0;i<_ordenados.size();i++){
        _valorEnCampo.erase(_ordenados[i]->campo);
    }
}

set<NombreCampo> Registro::campos() const {
    //COMPLETAR(campos);
    return _campos;
}

Valor& Registro::operator[](const NombreCampo& campo) {
    //COMPLETAR(operator[]);
    return _valorEnCampo.at(campo).valor;
}

void Registro:: definir(NombreCampo n, Valor v){
    _campos.insert(n);
    tripla t= tripla(_ordenados.size(),n,v);
    pair<string, tripla> entrada=make_pair(n,t);
    _valorEnCampo.insert(entrada);
    _ordenados.push_back(&_valorEnCampo.at(n));

    int posicionArreglo=_ordenados.size()-1;
    int posicionCaracter=0;

    while(posicionArreglo>0 && posicionCaracter<n.size() &&_ordenados[posicionArreglo-1]->campo.size()>posicionCaracter ){
        if(int(_ordenados[posicionArreglo-1]->campo[posicionCaracter])>=int(n[posicionCaracter])){
            _ordenados[posicionArreglo-1]->posicionEnArreglo++;
            _ordenados[posicionArreglo]->posicionEnArreglo--;
            swap(_ordenados[posicionArreglo-1],_ordenados[posicionArreglo]);
            posicionArreglo--;
        }else{
            posicionCaracter++;
        }
    }

}

Valor& Registro:: porNumero(const int a){
    return _ordenados[a]->valor;
}

int Registro:: damePosicion(const NombreCampo& campo){
    return _valorEnCampo.at(campo).posicionEnArreglo;
}
