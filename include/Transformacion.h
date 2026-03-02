#ifndef TRANSFORMACION_H
#define TRANSFORMACION_H
#include "Vector.h"

class Transformacion {
public:
    Vector<double> datos;
    double minimo, maximo, media;
    int nivel;

    Transformacion() : minimo(0), maximo(0), media(0), nivel(0) {}
    Transformacion(const Vector<double>& v, int n) : datos(v), nivel(n) {
        calcularEstadisticas();
    }

    void calcularEstadisticas() {
        if (datos.size() == 0) return;
        minimo = maximo = datos[0];
        double suma = 0;
        for (int i = 0; i < datos.size(); i++) {
            if (datos[i] < minimo) minimo = datos[i];
            if (datos[i] > maximo) maximo = datos[i];
            suma += datos[i];
        }
        media = suma / datos.size();
    }
};
#endif
