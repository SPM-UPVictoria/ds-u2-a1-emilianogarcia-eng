#ifndef COLA_H
#define COLA_H
#include "Vector.h"

template <class T>
class Cola {
private:
    Vector<T> elementos;
public:
    void enqueue(const T& valor) { elementos.push_back(valor); }
    void dequeue() { elementos.pop_front(); }
    T front() const { return elementos[0]; }
    bool vacia() const { return elementos.size() == 0; }
    void limpiar() { while (!vacia()) dequeue(); }
};
#endif
