/*************************************************************************
Autor: Jan Marco Muñoz Pineda
Fecha: 19/08/2024
Descripción: Fichero c++
*************************************************************************/

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

class Palabra {
private:
    string valor;      // Valor de la palabra
    unsigned int linea; // Número de la línea donde se encuentra la palabra

public:
    // Método para fijar el valor y la línea de la palabra
    void Fijar(const string& value, unsigned int line) {
        valor = value; // Asigna el valor
        linea = line;  // Asigna el número de línea
    }

    // Método para obtener el valor de la palabra
    string ObtenerValor() const {
        return valor; // Retorna el valor de la palabra
    }

    // Método para obtener el número de línea
    unsigned int ObtenerLinea() const {
        return linea; // Retorna el número de línea
    }
};

class ArchivoTexto {
private:
    vector<string> lineasTexto; // Vector que contiene las líneas del archivo

public:
    // Método para fijar las líneas leídas del archivo
    void FijarListaLineas(const vector<string>& lineas) {
        lineasTexto = lineas; // Asigna las líneas al vector
    }

    // Método para buscar palabras que comienzan con una subcadena
    void BuscarPrincipio(const string& subcadena) {
        cout << "\n=== Búsqueda de palabras que comienzan con '" << subcadena << "' ===\n";
        unsigned int count = 0; // Contador para palabras encontradas
        // Itera sobre cada línea del texto
        for (unsigned int i = 0; i < lineasTexto.size(); ++i) {
            string linea = lineasTexto[i]; // Toma la línea actual
            istringstream iss(linea); // Crea un flujo de entrada a partir de la línea
            string palabra; // Variable para almacenar la palabra actual
            // Extrae cada palabra de la línea
            while (iss >> palabra) {
                // Verifica si la palabra comienza con la subcadena dada
                if (palabra.find(subcadena) == 0) {
                    cout << " - Palabra: '" << palabra << "' en línea " << (i + 1) << endl;
                    count++; // Incrementa el contador
                }
            }
        }
        cout << "Total de palabras que comienzan con '" << subcadena << "': " << count << "\n";
    }

    // Método para buscar palabras que contienen una subcadena
    void BuscarContiene(const string& subcadena) {
        cout << "\n=== Búsqueda de palabras que contienen '" << subcadena << "' ===\n";
        unsigned int count = 0; // Contador para palabras encontradas
        // Itera sobre cada línea del texto
        for (unsigned int i = 0; i < lineasTexto.size(); ++i) {
            string linea = lineasTexto[i]; // Toma la línea actual
            istringstream iss(linea); // Crea un flujo de entrada a partir de la línea
            string palabra; // Variable para almacenar la palabra actual
            // Extrae cada palabra de la línea
            while (iss >> palabra) {
                // Verifica si la palabra contiene la subcadena dada
                if (palabra.find(subcadena) != string::npos) {
                    cout << " - Palabra: '" << palabra << "' en línea " << (i + 1) << endl;
                    count++; // Incrementa el contador
                }
            }
        }
        cout << "Total de palabras que contienen '" << subcadena << "': " << count << "\n";
    }

    // Método para buscar palabras que contienen la subcadena invertida
    void BuscarContieneInvertida(const string& subcadena) {
        string subcadena_invertida = string(subcadena.rbegin(), subcadena.rend()); // Invierte la subcadena
        cout << "\n=== Búsqueda de palabras que contienen la subcadena invertida '" << subcadena_invertida << "' ===\n";
        unsigned int count = 0; // Contador para palabras encontradas
        // Itera sobre cada línea del texto
        for (unsigned int i = 0; i < lineasTexto.size(); ++i) {
            string linea = lineasTexto[i]; // Toma la línea actual
            istringstream iss(linea); // Crea un flujo de entrada a partir de la línea
            string palabra; // Variable para almacenar la palabra actual
            // Extrae cada palabra de la línea
            while (iss >> palabra) {
                // Verifica si la palabra contiene la subcadena invertida
                if (palabra.find(subcadena_invertida) != string::npos) {
                    cout << " - Palabra: '" << palabra << "' en línea " << (i + 1) << endl;
                    count++; // Incrementa el contador
                }
            }
        }
        cout << "Total de palabras que contienen la subcadena invertida '" << subcadena_invertida << "': " << count << "\n";
    }
};

int main() {
    const string nombreArchivo = "entrada1.txt"; // Nombre del archivo directamente en el código

    ifstream archivo(nombreArchivo); // Abre el archivo para lectura
    if (!archivo.is_open()) { // Verifica si el archivo se ha abierto correctamente
        cerr << "Error al abrir el archivo." << endl; // Muestra un mensaje de error
        return 1; // Sale del programa con error
    }

    unsigned int n; // Variable para el número inicial
    string subcadena; // Variable para la subcadena a buscar
    archivo >> n >> subcadena; // Lee el número y la subcadena desde el archivo
    archivo.ignore(); // Ignora el salto de línea después de leer la subcadena

    ArchivoTexto archivoTexto; // Crea un objeto para manejar el texto
    vector<string> lineas; // Vector para almacenar las líneas
    string linea; // Variable para leer la línea actual

    // Lee líneas del archivo y las almacena en el vector
    while (getline(archivo, linea)) {
        lineas.push_back(linea); // Agrega la línea leída al vector
    }

    archivoTexto.FijarListaLineas(lineas); // Fija las líneas en el objeto de texto

    // Realiza las búsquedas y muestra los resultados
    archivoTexto.BuscarPrincipio(subcadena);
    archivoTexto.BuscarContiene(subcadena);
    archivoTexto.BuscarContieneInvertida(subcadena);

    return 0;
}
