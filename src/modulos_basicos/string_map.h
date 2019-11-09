#ifndef STRING_MAP_H_
#define STRING_MAP_H_

#include <string>
#include <vector>
#include <array>

using namespace std;

template<typename T>
class string_map {
public:
    /**
    CONSTRUCTOR
    * Construye un diccionario vacio.
    **/
    string_map();

    /**
    CONSTRUCTOR POR COPIA
    * Construye un diccionario por copia.
    **/
    string_map(const string_map<T> &aCopiar);

    /**
    OPERADOR ASIGNACION
     */
    string_map &operator=(const string_map &d);

    /**
    DESTRUCTOR
    **/
    ~string_map();

    /**
    INSERT 
    * Inserta un par clave, valor en el diccionario
    **/
    void insert(const pair<string, T> &valor);

    /**
    COUNT
    * Devuelve la cantidad de apariciones de la clave (0 o 1).
    * Sirve para identificar si una clave está definida o no.
    **/

    int count(const string &key) const;

    /**
    AT
    * Dada una clave, devuelve su significado.
    * PRE: La clave está definida.
    --PRODUCE ALIASING--
    -- Versión modificable y no modificable
    **/
    const T &at(const string &key) const;

    T &at(const string &key);

    /**
    ERASE
    * Dada una clave, la borra del diccionario junto a su significado.
    * PRE: La clave está definida.
    --PRODUCE ALIASING--
    **/
    void erase(const string &key);

    /**
     SIZE
     * Devuelve cantidad de claves definidas */
    int size() const;

    /**
     EMPTY
     * devuelve true si no hay ningún elemento en el diccionario */
    bool empty() const;
    void mostrar(ostream &os) const;
    /** OPTATIVO
    * operator[]
    * Acceso o definición de pares clave/valor
    **/
    T &operator[](const string &key);

private:

    struct Nodo {
        //vector<Nodo*> siguientes;
        array<Nodo *, 256> siguientes;
        //Nodo *siguientes[256];
        T *definicion;
        int cantHijos;
        string clave;

        Nodo() : cantHijos(0), definicion(nullptr),clave("") {
            for(int i=0; i<siguientes.size();i++){
                siguientes[i]= nullptr;
            }

        };
    };

    void destruirDesdeNodo(Nodo *n) {
        if (n != nullptr) {
            for (int i = 0; i < n->siguientes.size(); i++) {
                destruirDesdeNodo(n->siguientes[i]);
                n->siguientes[i] = nullptr;
            }
            delete (n->definicion);
            n->definicion = nullptr;
            delete n;
        }
    }

    Nodo *copiarDesdeNodo(Nodo *n) {
        if (n != nullptr) {
            Nodo *nuevo = new Nodo();
            if (n->definicion != nullptr) {
                nuevo->definicion = new T(*(n->definicion));
            } else {
                nuevo->definicion = nullptr;
            }
            nuevo->clave=n->clave;
            nuevo->cantHijos = n->cantHijos;
            for (int i = 0; i < nuevo->siguientes.size(); i++) {
                if (n->siguientes[i] != nullptr) {
                    nuevo->siguientes[i] = copiarDesdeNodo(n->siguientes[i]);
                } else {
                    nuevo->siguientes[i] = nullptr;
                }
            }
            return nuevo;
        } else {
            return nullptr;
        }
    }

    int mostrar(const std::string& prefix,Nodo * n, bool esUltimo,ostream &os) const;

    Nodo *raiz;
    int _size;
};

#include "string_map.hpp"

#endif // STRING_MAP_H_
