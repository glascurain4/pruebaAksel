/*Aksel Deneken A01711966 */

#ifndef PRODUCTOS_H_
#define PRODUCTOS_H_

#include <iostream>
#include <string>
#include <iomanip> // Para std::setprecision

using namespace std;

class Producto {
  private:
    float precio;
    string nombre;
    int stock;

  public:
    Producto();
    Producto(float, string, int);
    float getPrecio() const;
    string getNombre() const;
    int getStock() const;
    string getDatos() const;

};

Producto::Producto() {
  precio = 0;
  nombre = "";
  stock = 0;
}

Producto::Producto(float pre, string nom, int sto) {
  precio = pre;
  nombre = nom;
  stock = sto;
}

float Producto::getPrecio() const {
  return precio;
}

string Producto::getNombre() const  {
  return nombre;
}

int Producto::getStock() const {
  return stock;
}

string Producto::getDatos() const {
  return  nombre + " " + " - $" + to_string(precio) + " USD  - Cantidad disponible: " + to_string(stock);
}

#endif /*PRODUCTOS_H*/