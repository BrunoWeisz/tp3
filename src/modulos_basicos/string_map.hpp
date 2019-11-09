#include <iostream>
#include "string_map.h"

template<typename T>
string_map<T>::string_map():_size(0), raiz(nullptr) {
    // COMPLETAR
}

template<typename T>
string_map<T>::string_map(const string_map<T> &aCopiar)
        : string_map() { *this = aCopiar; } // Provisto por la catedra: utiliza el operador asignacion para realizar la copia.

template<typename T>
string_map<T> &string_map<T>::operator=(const string_map<T> &d) {
    // COMPLETAR
    if (raiz != nullptr) {
        destruirDesdeNodo(raiz);
    }
    if (d.raiz != nullptr) {
        raiz = copiarDesdeNodo(d.raiz);
    }
    _size = d._size;
}


template<typename T>
string_map<T>::~string_map() {
    // COMPLETAR
    if (raiz != nullptr) {
        destruirDesdeNodo(raiz);
    }
}


template<typename T>
void string_map<T>::insert(const pair<string, T> &valor) {
    if (_size == 0) {
        Nodo *n = new Nodo();
        raiz = n;
    }

    Nodo *actual = raiz;
    string palabra = valor.first;
    for (int i = 0; i < palabra.size(); i++) {
        char mostrar = palabra[i];
        if (actual->siguientes[int(palabra[i])] == NULL) {
            Nodo *nuevo = new Nodo;
            actual->siguientes[int(palabra[i])] = nuevo;
            actual->cantHijos++;
            for (i; i < palabra.size(); i++) {
                nuevo->clave.push_back(palabra[i]);
            }
            nuevo->definicion = new T(valor.second);
            actual = nuevo;
        } else {
            Nodo *anterior = actual;
            int actDeAnt = int(palabra[i]);//en que posicion se encuentra el actual en los siguientes del anterior;
            actual = actual->siguientes[int(palabra[i])];
            int j = 0;
            for (j = 0;
                 j < actual->clave.size() && (i + j) < palabra.size() && actual->clave[j] == palabra[i + j]; j++) {}
            if (j < actual->clave.size() &&
                (i + j) < palabra.size()) { // es decir, hay parte de la palabra que no coincide
                Nodo *reestructurar = new Nodo;
                reestructurar->definicion = actual->definicion;
                actual->definicion = nullptr;
                actual->siguientes[int(actual->clave[j])] = reestructurar;
                actual->cantHijos++;
                for (int k = j; k < actual->clave.size(); k++) {
                    (reestructurar->clave).push_back(actual->clave[k]);
                }
                int longClave = actual->clave.size();
                for (int k = j; k < longClave; k++) {
                    actual->clave.pop_back();
                }
                //con esto primero divido el nodo como necesito^

                Nodo *nuevo = new Nodo;
                actual->siguientes[int(palabra[i + j])] = nuevo;
                actual->cantHijos++;
                i=i+j;
                for (; i < palabra.size(); i++) {
                    nuevo->clave.push_back(palabra[i]);
                }
                nuevo->definicion = new T(valor.second);
                //i=palabra.size();
            } else if (j == actual->clave.size() && (i + j) == palabra.size()) {
                //en este caso voy a estar poniendo una clave que ya existe
                delete actual->definicion;
                actual->definicion = new T(valor.second);
                i = palabra.size();
            } else if (j == actual->clave.size() && (i + j) < palabra.size()) {
                //ya voy a haber modificado el actual y voy a seguir bajando
                i = i + j - 1;
            } else {
                //este caso seria cuando la longitud de la clave en esa posicion es mayor que de lo que tendria que agregar
                //TENGO QUE REESTRUCTURAR ARRIBLA Y QUE EL NODO DE ABAJO SEA EL QUE TENIA ANTES ASI CONSERVO LOS SIGUIENTES;
                Nodo *reestructurar = new Nodo;
                anterior->siguientes[actDeAnt] = reestructurar;
                reestructurar->definicion = new T(valor.second);
                for (int k = 0; k < j; k++) {
                    reestructurar->clave.push_back(actual->clave[k]);
                }
                string aux = actual->clave;
                actual->clave = "";
                for (int k = j; k < aux.size(); k++) {
                    actual->clave.push_back(aux[k]);
                }
                reestructurar->siguientes[int(actual->clave[0])] = actual;
                reestructurar->cantHijos++;
                i = palabra.size();//quiero que el ciclo termine;
            }
        }
    }
    _size++;
}


template<typename T>
T &string_map<T>::operator[](const string &clave) {
    // COMPLETAR
}


template<typename T>
int string_map<T>::count(const string &clave) const {
    if (_size == 0) {
        return 0;
    }
    Nodo *actual = raiz;
    for (int i = 0; i < clave.size();) {
        if (actual->siguientes[int(clave[i])] == nullptr) {
            return 0;
        }
        actual = actual->siguientes[int(clave[i])];
        int j = 0;
        for (j = i; (i - j) < actual->clave.size() && actual->clave[i - j] == clave[i]; i++) {}
        if ((i - j) != actual->clave.size()) {
            return 0;
        }

    }
    if (actual->definicion != nullptr) {
        return 1;
    } else {
        return 0;
    }
}

template<typename T>
const T &string_map<T>::at(const string &clave) const {
    // COMPLETAR
    Nodo *actual = raiz;
    for (int i = 0; i < clave.size();) {
        actual = actual->siguientes[int(clave[i])];
        for (int j = i; (i - j) < actual->clave.size() && actual->clave[i - j] == clave[i]; i++) {};
    }

    return *(actual->definicion);
}

template<typename T>
T &string_map<T>::at(const string &clave) {
    // COMPLETAR
    Nodo *actual = raiz;
    for (int i = 0; i < clave.size();) {
        actual = actual->siguientes[int(clave[i])];
        for (int j = i; (i - j) < actual->clave.size() && actual->clave[i - j] == clave[i]; i++) {};
    }

    return *(actual->definicion);
}

template<typename T>
void string_map<T>::erase(const string &clave) {
    if (_size == 1) {
        _size = 0;
        destruirDesdeNodo(raiz);
        raiz = nullptr;
    } else {
        Nodo *actual = raiz;
        Nodo *anterior = raiz;
        Nodo* anteriorDeAnterior=raiz;
        int claveAntDeAnt=0;
        int claveActDeAnt = 0;
        for (int i = 0; i < clave.size();) {
            anteriorDeAnterior=anterior;
            anterior = actual;
            claveAntDeAnt=claveActDeAnt;
            claveActDeAnt = int(clave[i]);
            actual = actual->siguientes[int(clave[i])];
            for (int j = i; (i - j) < actual->clave.size() && actual->clave[i - j] == clave[i]; i++) {};
        }
        if ((anterior->cantHijos == 1 || (anterior->cantHijos == 2 && anterior->definicion != nullptr) ||
             anterior->cantHijos > 2) && actual->cantHijos == 0) {
            destruirDesdeNodo(actual);
            anterior->siguientes[claveActDeAnt] = nullptr;
            anterior->cantHijos--;
        } else if (anterior->cantHijos == 2 && actual->cantHijos == 0) {//tabmien se que el anterior no esta definido
            destruirDesdeNodo(actual);
            anterior->siguientes[claveActDeAnt] = nullptr;
            anterior->cantHijos--;
            Nodo*elOtro;
            for (int u = 0; u < anterior->siguientes.size(); u++) {
                if(anterior->siguientes[u]!= nullptr){
                    elOtro=anterior->siguientes[u];
                    anterior->siguientes[u]= nullptr;
                }
            }
           anterior->definicion=elOtro->definicion;
            anterior->clave=anterior->clave+elOtro->clave;
            delete elOtro;
            anterior->cantHijos--;
        }else if(actual->cantHijos>1){
            delete actual->definicion;
            actual->definicion=nullptr;
        }else if( actual->cantHijos==1){
           //cout<<"LLEGUEACA";
            delete actual->definicion;
            Nodo* elSiguiente;
            int indiceSiguiente;
            for (int u = 0; u < actual->siguientes.size(); u++) {
                if(actual->siguientes[u]!= nullptr){
                    elSiguiente=actual->siguientes[u];
                    actual->siguientes[u]= nullptr;
                    indiceSiguiente=u;
                }
            }
            elSiguiente->clave=actual->clave+elSiguiente->clave;
            anterior->siguientes[claveActDeAnt]=elSiguiente;
            delete actual;
        }

        _size--;
    }
}

template<typename T>
int string_map<T>::size() const {
    // COMPLETAR
    return _size;
}

template<typename T>
bool string_map<T>::empty() const {
    // COMPLETAR
    return (raiz == nullptr);
}

template<typename T>
int string_map<T>::mostrar(const std::string &prefix, Nodo *n, bool esUltimo,ostream &os) const {
    int cantHijos=0;
    if (n != nullptr) {
        os << prefix;

        os << (esUltimo ? "├──" : "└──");

        // print the value of the node
        os << n->clave<<"("<<n->cantHijos<<")"<< endl;
        cantHijos=cantHijos+n->cantHijos;
        // enter the next tree level - left and right branch
        for (int i = 0; i < n->siguientes.size(); i++) {
            if (n->siguientes[i] != nullptr) {
                if (i == n->siguientes.size() - 1) {
                    cantHijos=cantHijos+mostrar(prefix + (esUltimo ? "│   " : "    "), n->siguientes[i], true,os );
                } else {
                    cantHijos=cantHijos+mostrar(prefix + (esUltimo ? "│   " : "    "), n->siguientes[i], false, os);
                }
            }
        }

        return cantHijos;
    }
}


template<typename T>
void string_map<T>::mostrar(ostream &os) const {
    int cantNodos=mostrar("", raiz, false, os);
    os<<"\n"<<"Cantidad de nodos: "<<cantNodos<<"\n";
}


template<typename T>
ostream &operator<<(ostream &os, const string_map<T> &s) {
    s.mostrar(os);
    os << "\n";
    os<<"-----------";
    os << "\n";
    return os;
}