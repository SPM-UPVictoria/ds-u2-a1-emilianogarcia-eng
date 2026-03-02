#ifndef PILA_H
#define PILA_H
#include "Vector.h"

template <class T>
class Pila {
private:
    Vector<T> elementos;
public:
    void push(const T& valor) { elementos.push_back(valor); }
    void pop() { elementos.pop_back(); }
    T top() const { return elementos[elementos.size() - 1]; }
    bool vacia() const { return elementos.size() == 0; }
    void limpiar() { while (!vacia()) pop(); }
};
#endif
