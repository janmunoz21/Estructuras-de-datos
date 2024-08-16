/*************************************************************************
Autor: Jan Marco Muñoz Pineda
Fecha: 22/07/2024
Descripción: Fichero c++
*************************************************************************/

#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Punto {
public:
    float x, y, z;
    Punto(float px, float py, float pz) : x(px), y(py), z(pz) {}
};

class Objeto {
public:
    vector<Punto> nubeDePuntos;
    Punto centroide;
    string indicadorVisualizacion;

    // Constructor que inicializa el centroide y calcula el indicador de visualización
    Objeto(vector<Punto> puntos) : nubeDePuntos(puntos), centroide(0, 0, 0) {
        calcularCentroide();
        indicadorVisualizacion = "nula";
    }

    // Método para calcular el centroide
    void calcularCentroide() {
        float sumX = 0, sumY = 0, sumZ = 0;
        for (Punto p : nubeDePuntos) {
            sumX += p.x;
            sumY += p.y;
            sumZ += p.z;
        }
        centroide = Punto(sumX / nubeDePuntos.size(), sumY / nubeDePuntos.size(), sumZ / nubeDePuntos.size());
    }

    // ---- Operación 1: Actualizar Indicador de Visualización ----
    string actualizarIndicadorVisualizacion(float limiteX, float limiteY, float limiteZ) {
        bool completa = true, parcial = false;
        for (Punto p : nubeDePuntos) {
            if (p.x < 0 || p.x > limiteX || p.y < 0 || p.y > limiteY || p.z < 0 || p.z > limiteZ) {
                completa = false;
                if (p.x >= 0 && p.x <= limiteX && p.y >= 0 && p.y <= limiteY && p.z >= 0 && p.z <= limiteZ) {
                    parcial = true;
                }
            }
        }
        if (completa) {
            indicadorVisualizacion = "completa";
        } else if (parcial) {
            indicadorVisualizacion = "parcial";
        } else {
            indicadorVisualizacion = "nula";
        }
        return indicadorVisualizacion;
    }
    // ---- Fin de Operación 1 ----

    // ---- Operación 2: Unión de dos Objetos ----
    static Objeto unirObjetos(const Objeto& obj1, const Objeto& obj2, float limiteX, float limiteY, float limiteZ) {
        vector<Punto> nuevaNubeDePuntos = obj1.nubeDePuntos;
        nuevaNubeDePuntos.insert(nuevaNubeDePuntos.end(), obj2.nubeDePuntos.begin(), obj2.nubeDePuntos.end());

        Objeto nuevoObjeto(nuevaNubeDePuntos);
        nuevoObjeto.actualizarIndicadorVisualizacion(limiteX, limiteY, limiteZ);

        return nuevoObjeto;
    }
    // ---- Fin de Operación 2 ----
};

int main() {
    // Creación de dos objetos con nubes de puntos
    vector<Punto> puntos1 = {Punto(1, 2, 3), Punto(4, 5, 6), Punto(7, 8, 9)};
    vector<Punto> puntos2 = {Punto(-1, -2, -3), Punto(-4, -5, -6), Punto(0, 0, 0)};

    Objeto obj1(puntos1);
    Objeto obj2(puntos2);

    // ---- Llamada a Operación 1: Actualizar Indicador de Visualización ----
    obj1.actualizarIndicadorVisualizacion(10, 10, 10);
    obj2.actualizarIndicadorVisualizacion(10, 10, 10);

    // ---- Llamada a Operación 2: Unión de dos Objetos ----
    Objeto objUnido = Objeto::unirObjetos(obj1, obj2, 10, 10, 10);

    // Salida de los resultados
    cout << "Indicador de visualización del objeto 1: " << obj1.indicadorVisualizacion << endl;
    cout << "Indicador de visualización del objeto 2: " << obj2.indicadorVisualizacion << endl;
    cout << "Indicador de visualización del objeto unido: " << objUnido.indicadorVisualizacion << endl;
    cout << "Centroide del objeto unido: (" << objUnido.centroide.x << ", " << objUnido.centroide.y << ", " << objUnido.centroide.z << ")" << endl;

    return 0;
}
