#include "Registro.h"

Registro::Registro() {}

Registro::~Registro() {
    for (int i = 0; i < _ordenados.size(); i++) {
        _valorEnCampo.erase(_ordenados[i]->campo);
    }
}

set<NombreCampo> Registro::campos() const {//O(1)
    return _campos;
}

Valor &Registro::operator[](const NombreCampo &campo) {
    return _valorEnCampo.at(campo).valor;
}

void Registro::definir(NombreCampo n, Valor v) { //O(|c|+|v|)
    _campos.insert(n); //O(1)?
    tripla t = tripla(_ordenados.size(), n, v); //O(1+|c|+|v|)
    pair<string, tripla> entrada = make_pair(n, t); //O(1)?
    _valorEnCampo.insert(entrada);//O(|c|)
    _ordenados.push_back(&_valorEnCampo.at(n));//O(|c|)

    int posicionArreglo = _ordenados.size() - 1; //O(1)
    int posicionCaracter = 0; //O(1)

    while (posicionArreglo > 0 && posicionCaracter < n.size() &&
           _ordenados[posicionArreglo - 1]->campo.size() >
           posicionCaracter) { //O(k+|c|)=O(|c|) con k= cantidad de campos
        if (int(_ordenados[posicionArreglo - 1]->campo[posicionCaracter]) >= int(n[posicionCaracter])) {
            _ordenados[posicionArreglo - 1]->posicionEnArreglo++;//O(1)
            _ordenados[posicionArreglo]->posicionEnArreglo--;//O(1)
            swap(_ordenados[posicionArreglo - 1], _ordenados[posicionArreglo]);//O(1)?
            posicionArreglo--;//O(1)
        } else {
            posicionCaracter++;//O(1)
        }
    }

}

Valor &Registro::porNumero(const int a) {//O(1)
    return _ordenados[a]->valor;
}

int Registro::damePosicion(const NombreCampo &campo) { //O(|c|)
    return _valorEnCampo.at(campo).posicionEnArreglo;
}
