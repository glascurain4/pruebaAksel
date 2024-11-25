/*Aksel Deneken A01711966 */

#include <iostream>
#include <string>
#include <vector>
#include "productos.h"
#include "GestionTienda.h"
#include <limits>
#include "Clientes.h"

using namespace std;



// Preguntar por qué atributo ordenar
void menu(){ 
cout << "\nElige una opción\n";
cout << "1. Ordenar Productos Por Precio\n";
cout << "2. Ordenar Productos Por Nombre\n";
cout << "3. Ordenar Productos Por Cantidad En Stock\n";
cout << "4. Buscar Producto por Precio\n";
cout << "5. Añadir Producto\n";
cout << "6. Ordenar Clientes Por Nombre\n";
cout << "7. Buscar Cliente Por Nombre\n";
cout << "8. Buscar Cliente Por ID\n";
cout << "9. Añadir Cliente\n";
cout << "10. Eliminar Cliente\n";
cout << "11. Agregar Productos Desde Archivo Externo\n";
cout << "12. Generar reporte de bajo Stock\n";
cout << "13. Salir\n";
}


int main() {

    Tienda tienda;
    //Inventario por default
    vector<Producto> Productos = { 
    {299.99, "Playera Oversized", 50},
    {499.50, "Jeans Negros", 30},
    {749.99, "Chamarra de Cuero", 15},
    {349.90, "Camisa Azul Old Money", 40},
    {199.99, "Gorra Gris Yankees", 25},
    {549.95, "Hoodie Negra", 20},
    {159.99, "Cinturón Verde Ferragamo", 60},
    {449.99, "Tank Top Blanco", 35},
    {399.90, "Vestido Rojo Escotado", 10},
    {259.90, "Shorts Azules", 45},
    {299.99, "Calcetas Mid Grises", 70},
    {699.50, "Zip-up Negro", 8},
    {129.99, "Calzones Calvin Klein", 100},
    {799.99, "Denim Jacket Azul", 12},
    {349.99, "Falda Negra", 25},
    {179.90, "Crocs Verdes", 50},
    {599.99, "Suéter Gris", 18},
    {399.95, "Zapatos Café", 22},
    {749.90, "Top Azul", 15},
    {129.90, "Playera Aestethic", 35}
};

    BSTCliente arbolClientes;

    // Agregamos algunos clientes al BST
    arbolClientes.insertar(Cliente("Juan", 1));
    arbolClientes.insertar(Cliente("Maria", 2));
    arbolClientes.insertar(Cliente("Carlos", 3));
    arbolClientes.insertar(Cliente("Ana", 4));


    int id = 4;
    int opcion(0);
    int resultado(0);
    float precioNuevo; 
    int stockNuevo;
    string nombreNuevo;
    string nombreABuscar;
    int idABuscar;
    string nombreAEliminar;
    Cliente* clientePorId = nullptr;
    Cliente* clienteEncontrado = nullptr;
    float precioBuscado;
    string atributo;
    string nombreArchivo;
    string nombreReporte;
    int limiteStock;

    // Mostrar el inventario sin ordenar
    cout << "Inventario original:\n";
    tienda.mostrarInventario(Productos);

   
    // Ordenar según la opción seleccionada
    
    while (opcion != 13){
        menu();
        cout << "Elige una opcion: ";
        cin >> opcion;
        switch (opcion) {
            case 1:
                atributo = "precio";
                tienda.mergeSort(Productos, 0, Productos.size() - 1, atributo);
                 cout << "\nInventario ordenado:\n";
                tienda.mostrarInventario(Productos);
                break;


            case 2:
                atributo = "nombre";
                tienda.mergeSort(Productos, 0, Productos.size() - 1, atributo);
                 cout << "\nInventario ordenado:\n";
                tienda.mostrarInventario(Productos);
                break;


            case 3:
                atributo = "stock";
                tienda.mergeSort(Productos, 0, Productos.size() - 1, atributo);
                 cout << "\nInventario ordenado:\n";
                tienda.mostrarInventario(Productos);
                break;


            case 4:
                cout << "\nIngrese el precio del producto a buscar: ";
                cin >> precioBuscado;
                resultado = tienda.busquedaBinaria(Productos, precioBuscado);
                if (resultado != -1) {
                    cout << "Producto encontrado: " << Productos[resultado].getDatos() << endl;
                } else {
                    cout << "Producto con precio $" << precioBuscado << " no encontrado.\n";
                }
                break;


            case 5:
                cout << "\nIngresa el nombre del nuevo producto: ";
                cin.ignore(); getline(cin, nombreNuevo);
                cout << "\nIngresa el precio del nuevo producto: ";
                cin >> precioNuevo;
                cout << "\nIngresa la cantidad de stock del nuevo producto: ";
                cin >> stockNuevo;
                tienda.add(Productos,precioNuevo,nombreNuevo,stockNuevo);
                tienda.mostrarInventario(Productos);
                break;


            case 6:
                // Mostrar clientes en orden alfabético
                cout << "Clientes en orden:" << endl;
                arbolClientes.mostrarClientesEnOrden();
                break;
            
            
            case 7:
                // Buscar un cliente por nombre
                cout << "\nIngrese el nombre del cliente a buscar: ";
                cin.ignore(); getline(cin, nombreABuscar);
                clienteEncontrado = arbolClientes.buscar(nombreABuscar);
                if (clienteEncontrado) {
                    cout << "Cliente encontrado: " << clienteEncontrado->getNombre() << " (ID: " << clienteEncontrado->getId() << ")" << endl;
                } else {
                    cout << "Cliente no encontrado: " << nombreABuscar << endl;
                }
                break;
            
            
           case 8:
                // Crear un bloque con llaves para encapsular las variables
                cout << "\nIngrese el ID del cliente a buscar: ";
                cin >> idABuscar;  // Cambié getline por cin, ya que idABuscar es entero
                clientePorId = arbolClientes.buscarPorId(idABuscar);
                if (clientePorId) {
                    cout << "Cliente encontrado por ID: " << clientePorId->getNombre() << " (ID: " << clientePorId->getId() << ")" << endl;
                } else {
                    cout << "Cliente no encontrado con ID: " << idABuscar << endl;
                }
                break;
            
            
            case 9:
            cout << "\nIngrese el nombre del cliente a añadir: ";
                cin.ignore(); getline(cin, nombreNuevo);
                cout << "Agregando cliente: " << nombreNuevo << endl;
                arbolClientes.insertar(Cliente(nombreNuevo, id + 1));

                // Mostrar clientes en orden después de la eliminación
                cout << "Clientes en orden después de agregar a " << nombreNuevo << ":" << endl;
                arbolClientes.mostrarClientesEnOrden();
                break;
        

            case 10:
                 // Eliminar un cliente por nombre
                cout << "\nIngrese el nombre del cliente a eliminar: ";
                cin.ignore(); getline(cin, nombreAEliminar);
                cout << "Eliminando cliente: " << nombreAEliminar << endl;
                arbolClientes.eliminar(nombreAEliminar);

                // Mostrar clientes en orden después de la eliminación
                cout << "Clientes en orden después de eliminar a " << nombreAEliminar << ":" << endl;
                arbolClientes.mostrarClientesEnOrden();
                break;
            
            case 11:
                cout <<"\nIngrese el nombre del archivo: ";
                cin.ignore(); getline(cin, nombreArchivo);
                cout << "Agregando Productos de: " << nombreArchivo << endl;
                tienda.leerInventarioDesdeArchivo(Productos, nombreArchivo);
                cout << "Productos despues de importar de " << nombreArchivo << " :" << endl;
                tienda.mostrarInventario(Productos);
                break;
            
            case 12:
                cout << "\nIngrese nombre del archivo para el reporte: ";
                cin.ignore(); getline(cin, nombreReporte);
                cout << "\nIngrese el límite de stock para el reporte: ";
                cin >> limiteStock;
                tienda.generaReporteStock(Productos, nombreReporte, limiteStock);
                break;


            case 13:
                cout << "Cerrando Programa" << endl;
                break;


            default:
             cout << "Opción Inválida" << endl;
             break;
    
        }
    }
    

    return 0;
}