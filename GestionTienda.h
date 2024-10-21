/*Aksel Deneken A01711966*/

#ifndef GESTIONTIENDA_H_
#define GESTIONTIENDA_H_

#include <iostream>
#include <vector>
#include "productos.h"

using namespace std;

class Tienda {

public:

   // Imprimir el inventario
    void mostrarInventario(vector<Producto>& Productos) {
        int inicio(0);
        if (inicio == 0){
            cout << ":::::BIENVENIDO A BYAK CLOTHING:::::" << endl;
        }
        inicio++;
        cout << "Estos son nuestros productos:" << endl;
        for (int i=0; i < Productos.size(); i++) {
            cout << Productos[i].getDatos() << endl;
        }
    }

    //Funcion Merge para cada caso usando vectores
    void merge(vector<Producto>& Productos, int inicio, int medio, int fin, string atributo) {
        int n1 = medio - inicio + 1;
        int n2 = fin - medio;


    // Vectores temporales
    vector<Producto> izq(Productos.begin() + inicio, Productos.begin() + inicio + n1);
    vector<Producto> der(Productos.begin() + medio + 1, Productos.begin() + medio + 1 + n2);

    int i = 0, j = 0, k = inicio;
    while (i < n1 && j < n2) {
        if (atributo == "precio") {
            if (izq[i].getPrecio() <= der[j].getPrecio()) {
                Productos[k] = izq[i];
                i++;
            } else {
                Productos[k] = der[j];
                j++;
            }
        } else if (atributo == "nombre") {
            if (izq[i].getNombre() <= der[j].getNombre()) {
                Productos[k] = izq[i];
                i++;
            } else {
                Productos[k] = der[j];
                j++;
            }
        } else if (atributo == "stock") {
            if (izq[i].getStock() <= der[j].getStock()) {
                Productos[k] = izq[i];
                i++;
            } else {
                Productos[k] = der[j];
                j++;
            }
        }
        k++;
    }

    // Copiar los elementos restantes
    while (i < n1) {
        Productos[k] = izq[i];
        i++;
        k++;
    }

    while (j < n2) {
        Productos[k] = der[j];
        j++;
        k++;
    }
    }

    // Merge Sort usando vectores
    void mergeSort(vector<Producto>& Productos, int inicio, int fin, string atributo) {
        if (inicio < fin) {
            int medio = inicio + (fin - inicio) / 2;

            mergeSort(Productos, inicio, medio, atributo);
            mergeSort(Productos, medio + 1, fin, atributo);
            merge(Productos, inicio, medio, fin, atributo);
        }
    }

    // Búsqueda binaria
    int busquedaBinaria(vector<Producto>& Productos, float precioBuscado) {
        mergeSort(Productos, 0, Productos.size() - 1, "precio");
        int inicio = 0;
        int fin = Productos.size() - 1;
        while (inicio <= fin) {
            int medio = inicio + (fin - inicio) / 2;
            float precioMedio = Productos[medio].getPrecio();

            if (precioMedio == precioBuscado) {
                return medio;
            }
            if (precioMedio < precioBuscado) {
                inicio = medio + 1;
            } 
            if (precioMedio > precioBuscado) {
                fin = medio - 1;
            }
            else {
                return medio;
            }
        }
        return -1;
    }

    // Función para agregar un producto
    void add(vector<Producto> &productos, float precio, const string &nombre, int stock) {
        Producto nuevoProducto(precio, nombre, stock);
        productos.push_back(nuevoProducto);
        cout << "Producto añadido: " << nombre << " con precio $" << precio << " y stock " << stock << endl;
    }

   

};



#endif /* GESTIONTIENDA_H_ */
