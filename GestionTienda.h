/*Aksel Deneken A01711966 */

#ifndef GESTIONTIENDA_H_
#define GESTIONTIENDA_H_

#include <iostream>
#include <vector>
#include "productos.h"
#include <fstream>
#include <iomanip>  
#include <algorithm> 
#include <sstream>

using namespace std;

class Tienda {

public:
   // Imprimir el inventario
   void mostrarInventario(const vector<Producto>& Productos) {
    // Encuentra la longitud máxima del nombre para alinear columnas
    size_t maxNombreLength = 0;
    for (const auto& producto : Productos) {
        maxNombreLength = max(maxNombreLength, producto.getNombre().length());
    }

    int anchoTotal = maxNombreLength + 40;

    // Imprimir encabezado
    cout << "\n" << string(anchoTotal, '=') << endl;
    cout << "                BYAK CLOTHING - INVENTARIO" << endl;
    cout << string(anchoTotal, '=') << endl;

    // Encabezados de columna
    cout << left << setw(maxNombreLength + 5) << "PRODUCTO"
         << left << setw(15) << "PRECIO (MXN)"  // Ajustamos el ancho del precio
         << "STOCK" << endl;  // Quitamos el setw para STOCK
    cout << string(anchoTotal, '-') << endl;

    // Imprimir cada producto
    for (const auto& producto : Productos) {
        cout << left << setw(maxNombreLength + 5) << producto.getNombre()
             << left << setw(15) << ("$ " + to_string(producto.getPrecio()).substr(0, 6))  // Formateamos el precio
             << producto.getStock() << endl;  // El stock se alinea naturalmente
    }

    // Pie de la tabla
    cout << string(anchoTotal, '=') << endl;
    cout << "Total de productos: " << Productos.size() << endl;
    cout << string(anchoTotal, '=') << endl << endl;
}

    // Función para leer el inventario desde un archivo
    void leerInventarioDesdeArchivo(vector<Producto>& Productos, const string& nombreArchivo) {
    ifstream archivo(nombreArchivo);
    if (!archivo) {
        cerr << "Error al abrir el archivo: " << nombreArchivo << endl;
        return;
    }

    string linea;
    while (getline(archivo, linea)) {
        // Ignorar líneas vacías
        if (linea.empty()) continue;

        stringstream ss(linea);
        string nombre;
        float precio;
        int stock;

        // Leer los valores
        if (ss >> nombre >> precio >> stock) {
            // Reemplazar guiones bajos por espacios en el nombre
            replace(nombre.begin(), nombre.end(), '_', ' ');
            
            // Verificar que los valores sean válidos
            if (precio > 0 && stock >= 0) {
                add(Productos, precio, nombre, stock);
            } else {
                cerr << "Error: Valores inválidos en la línea: " << linea << endl;
            }
        } else {
            cerr << "Error al leer la línea: " << linea << endl;
        }
    }
    archivo.close();
}

    void generaReporteStock(const vector<Producto>& Productos, const string& nombreArchivo, int limiteStock){
        ofstream archivo(nombreArchivo);
        if(!archivo){
            cout << "Error al crear el archivo" << nombreArchivo << endl;
            return;
        }

        time_t now = time(0);
        char* dt = ctime(&now);

        archivo << "REPORTE DE PROUCTOS CON BAJO STOCK - BYAK CLOTHING" << endl;
        archivo << "Fecha de reporte: " << dt << endl;
        archivo << "Todos los productos con menor stock a: " << limiteStock << " unidades." << endl;
        archivo << string(50, '=') << endl << endl;

        int productosEnAlerta = 0;
    float valorTotalEnRiesgo = 0.0;

    // Revisar cada producto
    for (const auto& producto : Productos) {
        if (producto.getStock() < limiteStock) {
            archivo << "PRODUCTO: " << producto.getNombre() << endl;
            archivo << "Stock actual: " << producto.getStock() << endl;
            archivo << "Precio unitario: $" << fixed << setprecision(2) << producto.getPrecio() << endl;
            archivo << "Valor en inventario: $" << producto.getPrecio() * producto.getStock() << endl;
            archivo << "Unidades necesarias para alcanzar nivel óptimo: " << limiteStock - producto.getStock() << endl;
            archivo << string(30, '-') << endl << endl;

            productosEnAlerta++;
            valorTotalEnRiesgo += producto.getPrecio() * producto.getStock();
        }
    }

    // Resumen al final del reporte
    archivo << "\nRESUMEN DEL REPORTE" << endl;
    archivo << string(30, '-') << endl;
    archivo << "Total de productos en alerta: " << productosEnAlerta << endl;
    archivo << "Valor total del inventario en riesgo: $" << fixed << setprecision(2) << valorTotalEnRiesgo << endl;
    archivo << "Porcentaje del inventario en alerta: " << 
               (productosEnAlerta * 100.0) / Productos.size() << "%" << endl;

    archivo.close();
    cout << "Reporte generado exitosamente en '" << nombreArchivo << "'" << endl;
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
    // Primero ordenamos el vector por precio
    mergeSort(Productos, 0, Productos.size() - 1, "precio");
    
    int inicio = 0;
    int fin = Productos.size() - 1;
    
    while (inicio <= fin) {
        int medio = inicio + (fin - inicio) / 2;
        float precioMedio = Productos[medio].getPrecio();
        
        // Usamos una pequeña tolerancia para la comparación de flotantes
        float tolerancia = 0.01;
        if (abs(precioMedio - precioBuscado) < tolerancia) {
            return medio;
        }
        else if (precioMedio < precioBuscado) {
            inicio = medio + 1;
        }
        else {
            fin = medio - 1;
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
