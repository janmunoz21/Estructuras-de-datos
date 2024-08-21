/***********************************************************
* Fecha: 21 de agosto de 2024
* Autor: Jan Marco Muñoz Pineda
* Tema: Taller 00
* Estructuras de datos
***********************************************************/

#include <iostream>
#include <fstream>

using namespace std;

struct factura {
    string nombre;
    int cedula;
    string nombreProducto;
    int cantidad;
    double precio;
};

// Función para impresión para generar el fichero de texto
void impresionFichero(factura *p) {
    ofstream archivo("Factura.txt");
    // Verificar si se abre el archivo txt
    if (!archivo) {
        cout << "Error al abrir el archivo." << endl;
    } else {
        archivo << "Nombre del cliente: \t" << p->nombre << endl;
        archivo << "Cedula del cliente: \t" << p->cedula << endl;
        archivo << "Nombre del producto: \t" << p->nombreProducto << endl;
        archivo << "Cantidad de productos: \t" << p->cantidad << endl;
        archivo << "Precio del producto: \t" << p->precio << endl;
        archivo << "Valor a pagar: \t\t" << p->cantidad * p->precio << endl;
        // Cierre de archivo
        archivo.close();
    }
}

int main() {
    // Datos de factura encapsulados, apuntados por puntero
    factura objetoFacturas;
    factura *puntero = &objetoFacturas; // Declaración y asignación del puntero

    // Captura de datos de cliente y factura
    cout << "Ingrese nombre del cliente: ";
    cin >> puntero->nombre;
    cout << "Ingrese cedula del cliente: ";
    cin >> puntero->cedula;
    cout << "Ingrese el nombre del producto: ";
    cin >> puntero->nombreProducto;
    cout << "Ingrese la cantidad de productos: ";
    cin >> puntero->cantidad;
    cout << "Ingrese el precio del producto: ";
    cin >> puntero->precio;

    // Llamada a la función con el puntero correcto
    impresionFichero(puntero);

    return 0;
}
