/***********************************************************
* Fecha: 21 de agosto de 2024
* Autor: Jan Marco Muñoz Pineda
* Tema: Taller 00
* Estructuras de datos
***********************************************************/

#include <iostream>
#include <ctime>
#include <cstdlib>

using namespace std;

struct venta{
	int cantidad;
	double precio;
};
/* Funcion que retorna un aleatorio entre 0 25 */
int aleatorio(){
	return rand()%26;
}

int main(){

	//  Se cre la semilla
	srand(time(0));

	// Se crea un array con 10 elementos
	int array [10];
	
	// Se crea el puntero (tipo entero)
	int *puntero = array;
	
	// Llenar el array
	for(int i=0; i<10; i++)
		array[i]=aleatorio();
	
	// Se imprime array con el puntero
	for(int i=0; i<10 ; i++)
		cout << "Valores en array [" << i << "] = " << *puntero++ << "\t Direcciones: " << puntero << endl;

return 0;
}

