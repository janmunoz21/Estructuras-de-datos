/****************************************
Autor: Jan MArco Muñoz Pineda
Fecha: 28 de agosto 2024
Materia: Estructura de Datos
Tema: Laboratorio Implementación BST 
****************************************/

#include <iostream>
using namespace std;

struct Nodo{
	int dato; //Dato a almacenar en el raiz
	struct Nodo *left, *right;
};	

struct Nodo *nuevoNodo(int dato){ //Estructura para crear nuevo arbol
	struct Nodo *temporal = new struct Nodo();
	temporal->dato = dato;
	temporal->left = temporal->right = NULL;
	return temporal;
}

/******* Preorder *********/
void preOrdenT(struct Nodo *raiz){ //Se recibe el arbol
	if (raiz==NULL) //Mientras el valor en el nodo no sea nulo realice lo siguiente
		return;
	cout << raiz->dato << "->";  //Imprime primero la raiz, izquierda y por ultimo derecha
	preOrdenT(raiz->left);
	preOrdenT(raiz->right);
}

/******* Postorder *********/
void postOrdenT(struct Nodo *raiz){ //Se recibe arbol
	if (raiz==NULL) //Mientras el valor en el nodo no sea nulo realice lo siguiente
		return;
	postOrdenT(raiz->left); //Imprime de primero izquierda, derecha y por ultimo raiz
	postOrdenT(raiz->right);
	cout << raiz->dato << "->"; 
}

/******* Inorder *********/
void inOrdenT(struct Nodo *raiz){ //Se recibe el arbol
	if (raiz==NULL) //Mientras el valor en el nodo no sea nulo realice lo siguiente
		return;
	inOrdenT(raiz->left); //Imprime primero izquierda, raiz y por ultimo la derecha
	cout << raiz->dato << "->"; 
	inOrdenT(raiz->right);
}

/****** Insertar nuevo nodo, dado un valor (BST) ********/
struct Nodo *insertarBST(struct Nodo *nodo, int newDato){
	if (nodo==NULL)
		return nuevoNodo(newDato);
	if (newDato < nodo->dato)
		nodo->left = insertarBST(nodo->left, newDato);
	else
		nodo->right = insertarBST(nodo->right, newDato);

	return nodo;
}


/****** función que retorna el nodo con menor valor en un BST ********/
struct Nodo *minValorNodo(struct Nodo *nodo){
	struct Nodo *actual = nodo;
	/*Se busca iterativamente el elemento menor a la izquierda*/
	while(actual && actual->left !=NULL)
		actual = actual->left;
	return actual;
}


/****** función que elimina un nodo con valor en un BST ********/
struct Nodo *borrarNodo(struct Nodo *nodo, int dato){
	/*=Arbol vacio=*/
	if(nodo == NULL)
		return nodo;
	/*=si el valor es menor a la raiz, ir por la izquierda=*/
	if(dato < nodo->dato)
		nodo->left = borrarNodo(nodo->left, dato);
	/*=si el valor es mayor a la raiz, ir por la derecha=*/
	else if (dato > nodo->dato)
		nodo->right = borrarNodo(nodo->right, dato);
	/*=el valor esta en la misma raiz=*/
	else {
		/*=Nodo con solo un hijo o sin hijos=*/	
		if(nodo->left == NULL){
			struct Nodo *temporal = nodo->right;
			free(nodo);
			return temporal;
		}else if(nodo->right == NULL){
			struct Nodo *temporal = nodo->left;
			free(nodo);
			return temporal;
		}
		/*=Nodo con ambos hijos, tomar el sucesor y borrar el nodo=*/
		struct Nodo *temp = minValorNodo(nodo->right);
		/*=copiar el contenido InOrder sucesor a el nodo=*/
		nodo->dato = temp->dato;
		/*=borrar el InOrder sucesor=*/
		nodo->right = borrarNodo(nodo->right, temp->dato);
	}
	return nodo;
}



int main(){
	struct Nodo *arbol1 = NULL; 
	arbol1 = insertarBST(arbol1, 2);
	arbol1 = insertarBST(arbol1, 12);
	arbol1 = insertarBST(arbol1, 23);
	arbol1 = insertarBST(arbol1, 48);
	arbol1 = insertarBST(arbol1, 27);
	arbol1 = insertarBST(arbol1, 17);
	arbol1 = insertarBST(arbol1, 32);
	arbol1 = insertarBST(arbol1, 72);
	
	int opcion;
	
	cout << "Seleccione orden para imprimir el arbol: " << endl;
	cout << "1. Preorden." << endl;
	cout << "2. Postorden." << endl;
	cout << "3. Inorden." << endl;
	cout << "Opcion: ";
	cin >> opcion;
	
	switch (opcion){
	case 1:
	cout << "\n -PreOrden ";  
	preOrdenT(arbol1);
	break;
	
	case 2:
	cout << "\n -PostOrden "; 
	break;
	
	postOrdenT(arbol1);
	case 3:
	cout << "\n -InOrden ";
	inOrdenT(arbol1);
	break;	
}
	cout << endl << "Se elimina el nodo(23)" << endl;
	arbol1 = borrarNodo(arbol1, 23);
	inOrdenT(arbol1);

	return 0;	
}
