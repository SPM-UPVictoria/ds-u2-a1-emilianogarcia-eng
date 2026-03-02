#ifndef VECTOR_H
#define VECTOR_H
#include <stdexcept>

template <class T>
class Vector {
private:
    T* datos;
    int capacidad;
    int cantidad;

    void redimensionar(int nueva_capacidad) {
        T* nuevos_datos = new T[nueva_capacidad];
        for (int i = 0; i < cantidad; i++) {
            nuevos_datos[i] = datos[i];
        }
        delete[] datos;
        datos = nuevos_datos;
        capacidad = nueva_capacidad;
    }

public:
    Vector(int size = 0) : capacidad(size > 0 ? size : 10), cantidad(size) {
        datos = new T[capacidad]();
    }

    ~Vector() { delete[] datos; }

    Vector(const Vector& otro) : capacidad(otro.capacidad), cantidad(otro.cantidad) {
        datos = new T[capacidad];
        for (int i = 0; i < cantidad; i++) datos[i] = otro.datos[i];
    }

    Vector& operator=(const Vector& otro) {
        if (this != &otro) {
            delete[] datos;
            capacidad = otro.capacidad;
            cantidad = otro.cantidad;
            datos = new T[capacidad];
            for (int i = 0; i < cantidad; i++) datos[i] = otro.datos[i];
        }
        return *this;
    }

    void push_back(const T& valor) {
        if (cantidad == capacidad) redimensionar(capacidad * 2);
        datos[cantidad++] = valor;
    }

    void pop_back() {
        if (cantidad > 0) cantidad--;
    }

    void pop_front() {
        if (cantidad > 0) {
            for (int i = 0; i < cantidad - 1; i++) datos[i] = datos[i + 1];
            cantidad--;
        }
    }

    T& operator[](int index) { return datos[index]; }
    const T& operator[](int index) const { return datos[index]; }

    int size() const { return cantidad; }
};
#endif

