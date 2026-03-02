#include <iostream>
#include <fstream>
#include "Vector.h"
#include "Matriz.h"
#include "ListaEnlazada.h"
#include "Pila.h"
#include "Cola.h"
#include "Transformacion.h"

using namespace std;

class SistemaTransformaciones {
private:
    Vector<double> funcionOriginal;
    Matriz<double>* matrizT;
    ListaEnlazada<Transformacion> historial;
    Pila<Transformacion> undoPila;
    Cola<Transformacion> redoCola;
    int nivelActual;

public:
    SistemaTransformaciones() : matrizT(nullptr), nivelActual(0) {}
    ~SistemaTransformaciones() { if (matrizT) delete matrizT; }

    void ingresarFuncion() {
        int n;
        cout << "\nIngrese el tamano de la funcion discreta N: ";
        cin >> n;
        funcionOriginal = Vector<double>(n);
        cout << "Ingrese los " << n << " valores:\n";
        for (int i = 0; i < n; i++) {
            cout << "f(" << i << "): ";
            cin >> funcionOriginal[i];
        }
        cout << ">>> Funcion ingresada correctamente.\n";
    }

    void generarMatriz() {
        if (funcionOriginal.size() == 0) {
            cout << ">>> Error: Primero ingresa la funcion (Opcion 1).\n"; 
            return; 
        }
        int n = funcionOriginal.size();
        if (matrizT) delete matrizT;
        matrizT = new Matriz<double>(n, n);
        
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (i == j) (*matrizT)(i, j) = 1;
                else if (i == j + 1) (*matrizT)(i, j) = -1;
                else (*matrizT)(i, j) = 0;
            }
        }
        cout << ">>> Matriz generada correctamente.\n";
    }

    void aplicarTransformacion() {
        if (!matrizT) { 
            cout << ">>> Error: Genere la matriz primero (Opcion 2).\n"; 
            return; 
        }
        
        Vector<double> input = (nivelActual == 0) ? funcionOriginal : undoPila.top().datos;
        Vector<double> g = (*matrizT) * input;
        
        nivelActual++;
        Transformacion t(g, nivelActual);
        historial.agregar(t);
        undoPila.push(t);
        redoCola.limpiar(); // Al aplicar un cambio nuevo, el futuro (redo) se borra
        
        cout << ">>> Transformacion nivel " << nivelActual << " aplicada con exito.\n";
    }

    void mostrarHistorial() {
        Nodo<Transformacion>* actual = historial.get_cabeza();
        if (!actual) {
            cout << "\n>>> No hay transformaciones en el historial.\n";
            return;
        }
        cout << "\n--- HISTORIAL DE TRANSFORMACIONES ---\n";
        while (actual) {
            cout << "Nivel: " << actual->dato.nivel 
                 << " | Media: " << actual->dato.media 
                 << " | Min: " << actual->dato.minimo 
                 << " | Max: " << actual->dato.maximo << "\n";
            actual = actual->siguiente;
        }
        cout << "-------------------------------------\n";
    }

    void deshacer() {
        if (undoPila.vacia()) { 
            cout << ">>> Nada que deshacer.\n"; 
            return; 
        }
        Transformacion t = undoPila.top();
        undoPila.pop();
        redoCola.enqueue(t);
        historial.eliminar_ultimo();
        nivelActual--;
        cout << ">>> Deshecho. Nivel actual regresó a: " << nivelActual << "\n";
    }

    void rehacer() {
        if (redoCola.vacia()) { 
            cout << ">>> Nada que rehacer.\n"; 
            return; 
        }
        Transformacion t = redoCola.front();
        redoCola.dequeue();
        undoPila.push(t);
        historial.agregar(t);
        nivelActual++;
        cout << ">>> Rehecho. Nivel actual avanzo a: " << nivelActual << "\n";
    }

    void exportarReporte() {
        ofstream archivo("../docs/reporte.txt");
        if (!archivo.is_open()) { 
            cout << ">>> Error al abrir archivo. Asegurate de que la carpeta docs/ exista.\n"; 
            return; 
        }
        archivo << "--- REPORTE DE TRANSFORMACIONES ---\n";
        Nodo<Transformacion>* actual = historial.get_cabeza();
        if (!actual) archivo << "No se aplicaron transformaciones.\n";
        
        while (actual) {
            archivo << "Nivel: " << actual->dato.nivel << "\n"
                    << "Vector Resultante: [ ";
            for (int i = 0; i < actual->dato.datos.size(); i++) {
                archivo << actual->dato.datos[i] << " ";
            }
            archivo << "]\nMin: " << actual->dato.minimo 
                    << " | Max: " << actual->dato.maximo 
                    << " | Promedio: " << actual->dato.media << "\n\n";
            actual = actual->siguiente;
        }
        archivo.close();
        cout << ">>> Reporte exportado exitosamente en la carpeta docs/reporte.txt\n";
    }
};

int main() {
    SistemaTransformaciones sistema;
    int opcion;
    cout << "=========================================\n";
    cout << "   SISTEMA DE TRANSFORMACIONES DISCRETAS \n";
    cout << "=========================================\n";
    do {
        cout << "\nMENU PRINCIPAL\n";
        cout << "1. Ingresar funcion discreta\n";
        cout << "2. Generar matriz transformadora\n";
        cout << "3. Aplicar transformacion\n";
        cout << "4. Mostrar historial y estadisticas\n";
        cout << "5. Deshacer ultima transformacion (Undo)\n";
        cout << "6. Rehacer transformacion (Redo)\n";
        cout << "7. Exportar reporte a texto\n";
        cout << "8. Salir\n";
        cout << "Elige una opcion papu: ";
        cin >> opcion;
        
        switch (opcion) {
            case 1: sistema.ingresarFuncion(); break;
            case 2: sistema.generarMatriz(); break;
            case 3: sistema.aplicarTransformacion(); break;
            case 4: sistema.mostrarHistorial(); break;
            case 5: sistema.deshacer(); break;
            case 6: sistema.rehacer(); break;
            case 7: sistema.exportarReporte(); break;
            case 8: cout << "Saliendo... ¡Fierro!\n"; break;
            default: cout << ">>> Opcion invalida, tirale de nuevo.\n";
        }
    } while (opcion != 8);
    return 0;
}
