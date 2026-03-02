#ifndef MATRIZ_H
#define MATRIZ_H
#include "Vector.h"

template <class T>
class Matriz {
private:
    T** datos;
    int filas;
    int columnas;

public:
    Matriz(int f, int c) : filas(f), columnas(c) {
        datos = new T*[filas];
        for (int i = 0; i < filas; i++) {
            datos[i] = new T[columnas]();
        }
    }

    ~Matriz() {
        for (int i = 0; i < filas; i++) delete[] datos[i];
        delete[] datos;
    }

    T& operator()(int f, int c) { return datos[f][c]; }
    const T& operator()(int f, int c) const { return datos[f][c]; }

    Vector<T> operator*(const Vector<T>& v) const {
        if (columnas != v.size()) throw std::invalid_argument("Dimensiones incompatibles");
        Vector<T> resultado(filas);
        for (int i = 0; i < filas; i++) {
            T suma = 0;
            for (int j = 0; j < columnas; j++) {
                suma += datos[i][j] * v[j];
            }
            resultado[i] = suma;
        }
        return resultado;
    }
};
#endif
