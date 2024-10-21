#ifndef CLIENTES_H
#define CLIENTES_H

#include <iostream>
#include <string>

class Cliente {
private:
    string nombre;
    int id;  
    // Otros atributos, como historial de compras, dirección, etc.

public:
    Cliente(string nombre, int id) : nombre(nombre), id(id) {}

    string getNombre() { return nombre; }
    int getId() { return id; }

};

class NodoCliente {
public:
    Cliente cliente;
    NodoCliente* izquierda;
    NodoCliente* derecha;

    NodoCliente(Cliente cli) : cliente(cli), izquierda(nullptr), derecha(nullptr) {}
};

class BSTCliente {
private:
    NodoCliente* raiz;

    // Función recursiva para insertar clientes en el BST
    NodoCliente* insertarRecursivo(NodoCliente* nodo, Cliente cli) {
        if (nodo == nullptr) {
            return new NodoCliente(cli);  // Crear un nuevo nodo si llegamos al final
        }
        if (cli.getNombre() < nodo->cliente.getNombre()) {
            nodo->izquierda = insertarRecursivo(nodo->izquierda, cli);
        } else if (cli.getNombre() > nodo->cliente.getNombre()) {
            nodo->derecha = insertarRecursivo(nodo->derecha, cli);
        }
        return nodo;
    }

    // Función recursiva para buscar clientes por nombre
    NodoCliente* buscarRecursivo(NodoCliente* nodo, string nombre) {
        if (nodo == nullptr || nodo->cliente.getNombre() == nombre) {
            return nodo;
        }
        if (nombre < nodo->cliente.getNombre()) {
            return buscarRecursivo(nodo->izquierda, nombre);
        }
        return buscarRecursivo(nodo->derecha, nombre);
    }

    // Función recursiva para eliminar un cliente por nombre
    NodoCliente* eliminarRecursivo(NodoCliente* nodo, string nombre) {
        if (nodo == nullptr) return nodo;

        if (nombre < nodo->cliente.getNombre()) {
            nodo->izquierda = eliminarRecursivo(nodo->izquierda, nombre);
        } else if (nombre > nodo->cliente.getNombre()) {
            nodo->derecha = eliminarRecursivo(nodo->derecha, nombre);
        } else {
            // Caso 1: Nodo hoja
            if (nodo->izquierda == nullptr && nodo->derecha == nullptr) {
                delete nodo;
                return nullptr;
            }
            // Caso 2: Un solo hijo
            if (nodo->izquierda == nullptr) {
                NodoCliente* temp = nodo->derecha;
                delete nodo;
                return temp;
            } else if (nodo->derecha == nullptr) {
                NodoCliente* temp = nodo->izquierda;
                delete nodo;
                return temp;
            }
            // Caso 3: Dos hijos
            NodoCliente* temp = minValorNodo(nodo->derecha);  // Encuentra el sucesor
            nodo->cliente = temp->cliente;  // Copia el valor del sucesor
            nodo->derecha = eliminarRecursivo(nodo->derecha, temp->cliente.getNombre());
        }
        return nodo;
    }

    // Encuentra el nodo con el valor mínimo
    NodoCliente* minValorNodo(NodoCliente* nodo) {
        NodoCliente* actual = nodo;
        while (actual && actual->izquierda != nullptr) {
            actual = actual->izquierda;
        }
        return actual;
    }

    // Función recursiva para buscar clientes por ID
    NodoCliente* buscarPorIdRecursivo(NodoCliente* nodo, int id) {
        if (nodo == nullptr || nodo->cliente.getId() == id) {
            return nodo;
        }

        NodoCliente* izq = buscarPorIdRecursivo(nodo->izquierda, id);
        if (izq != nullptr) return izq;

        return buscarPorIdRecursivo(nodo->derecha, id);
    }

public:
    BSTCliente() : raiz(nullptr) {}

    // Insertar cliente
    void insertar(Cliente cli) {
        raiz = insertarRecursivo(raiz, cli);
    }

    // Buscar cliente por nombre
    Cliente* buscar(string nombre) {
        NodoCliente* resultado = buscarRecursivo(raiz, nombre);
        if (resultado != nullptr) {
            return &resultado->cliente;
        } else {
            return nullptr;
        }
    }

    // Buscar cliente por ID
    Cliente* buscarPorId(int id) {
        NodoCliente* resultado = buscarPorIdRecursivo(raiz, id);
        if (resultado != nullptr) {
            return &resultado->cliente;
        } else {
            return nullptr;
        }
    }

    // Eliminar cliente por nombre
    void eliminar(string nombre) {
        raiz = eliminarRecursivo(raiz, nombre);
    }

    // Recorrer y mostrar clientes en orden
    void inorderRecursivo(NodoCliente* nodo) {
        if (nodo == nullptr) return;
        inorderRecursivo(nodo->izquierda);
        std::cout << "Cliente: " << nodo->cliente.getNombre() << " (ID: " << nodo->cliente.getId() << ")" << std::endl;
        inorderRecursivo(nodo->derecha);
    }

    void mostrarClientesEnOrden() {
        inorderRecursivo(raiz);
    }
};


#endif //CLIENTES_H