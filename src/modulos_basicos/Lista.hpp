#include "Lista.h"

template <typename T>
Lista<T>::Lista():length(0),_primero(NULL),_ultimo(NULL) {
    // Completar
}

template <typename T>
Lista<T>::Lista(const Lista<T>& l) : Lista() {
    //Inicializa una lista vacía y luego utiliza operator= para no duplicar el código de la copia de una lista.
    *this = l;
}

template <typename T>
Lista<T>::~Lista() {
    // Completar
    while (_primero != NULL) {
        Nodo* p = _primero;
        _primero = _primero->siguiente;
        delete p;
    }

}

template <typename T>
Lista<T>& Lista<T>::operator=(const Lista<T>& aCopiar) {
    // Completar
    for(int i=length;i>0;i--){
        eliminar(i-1);
    }
    while(length<aCopiar.length){
        agregarAtras(aCopiar.iesimo(length));
    }

    return *this;

}

template <typename T>
void Lista<T>::agregarAdelante(const T& elem) {
    // Completar
    Nodo* nuevo = new Nodo(elem);
    nuevo->siguiente = _primero;
    if(length>0) {
        _primero->anterior = nuevo;
    }
    _primero = nuevo;
    if(length==0){
        _ultimo=nuevo;
    }
    length++;
}

template <typename T>
void Lista<T>::agregarAtras(const T& elem) {
    // Completar
    Nodo* nuevo = new Nodo(elem);
    nuevo->anterior = _ultimo;
    if(length>0){
    _ultimo->siguiente=nuevo;
    }
    _ultimo = nuevo;
    if(length==0){
        _primero=nuevo;
    }
    length++;
}

template <typename T>
void Lista<T>::eliminar(Nat i) {
    // Completar
    assert(i<length && i>=0);
    Nodo* actual=_primero;
    if(length==1){
        _primero= nullptr;
        _ultimo= nullptr;
        delete actual;
        length--;
        return;
    }

    for(int j=0;j<i;j++){
        actual=actual->siguiente;
    }
    Nodo* anterior=actual->anterior;
    Nodo* siguiente=actual->siguiente;

    if(actual==_primero){
        _primero=siguiente;
    }
    if(actual==_ultimo){
        _ultimo==anterior;
    }
    if(anterior!=NULL){
    anterior->siguiente=siguiente;
    }

    if(siguiente!=NULL){
        siguiente->anterior=anterior;
    }
    delete actual;
    length--;




}

template <typename T>
int Lista<T>::longitud() const {
    // Completar
    return length;
}

template <typename T>
const T& Lista<T>::iesimo(Nat i) const {
    // Completar
    assert(i<length || i>=0);
    Nodo* actual=_primero;
    for(;i>0;i--){
        actual=actual->siguiente;
    }

    return actual->valor;
}

template <typename T>
T& Lista<T>::iesimo(Nat i) {
    // Completar (hint: es igual a la anterior...)
    assert(i<length || i>=0);
    Nodo* actual=_primero;
    for(int j=0;j<i;j++){
        actual=actual->siguiente;
    }

    return actual->valor;
}

template <typename T>
void Lista<T>::mostrar(ostream& o) {
    // Completar

}

template <typename T>
void Lista<T>:: swapear(Nodo& n1, Nodo& n2){
    T* valAux=n1.valor;
    n1.

}
template <typename T>
Lista<T>::Nodo::Nodo(const T& elem): valor(elem), siguiente(NULL),anterior(NULL) {}
