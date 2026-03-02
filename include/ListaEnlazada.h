#ifndef LISTA_ENLAZADA_H
#define LISTA_ENLAZADA_H

template <class T>
struct Nodo {
    T dato;
    Nodo* siguiente;
    Nodo(T d) : dato(d), siguiente(nullptr) {}
};

template <class T>
class ListaEnlazada {
private:
    Nodo<T>* cabeza;
    Nodo<T>* cola;

public:
    ListaEnlazada() : cabeza(nullptr), cola(nullptr) {}
    ~ListaEnlazada() { limpiar(); }

    void agregar(const T& elemento) {
        Nodo<T>* nuevo = new Nodo<T>(elemento);
        if (!cabeza) {
            cabeza = cola = nuevo;
        } else {
            cola->siguiente = nuevo;
            cola = nuevo;
        }
    }

    void eliminar_ultimo() {
        if (!cabeza) return;
        if (cabeza == cola) {
            delete cabeza;
            cabeza = cola = nullptr;
            return;
        }
        Nodo<T>* actual = cabeza;
        while (actual->siguiente != cola) actual = actual->siguiente;
        delete cola;
        cola = actual;
        cola->siguiente = nullptr;
    }

    void limpiar() {
        while (cabeza) {
            Nodo<T>* temp = cabeza;
            cabeza = cabeza->siguiente;
            delete temp;
        }
        cola = nullptr;
    }

    Nodo<T>* get_cabeza() const { return cabeza; }
};
#endif
