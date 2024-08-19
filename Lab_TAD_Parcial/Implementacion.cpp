## Implementación en C++

```cpp
/*************************************************************************
Autor: Jan Marco Muñoz Pineda
Fecha: 16/08/2024
Descripción: Implementación tipo parcial peaje c++
*************************************************************************/

#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>

// Estructura que representa un vehículo
struct Vehículo {
    std::string placa; // Placa del vehículo
    std::string tipo;  // Tipo de vehículo (ej: auto, camión)

    // Constructor para inicializar un vehículo con su placa y tipo
    Vehículo(std::string p, std::string t) : placa(p), tipo(t) {}
};

// Estructura que representa una caseta de peaje
struct Caseta {
    std::queue<Vehículo> colaVehículos; // Cola de vehículos esperando en la caseta
    float cuentaTotal = 0; // Monto total recaudado en la caseta
    std::unordered_map<std::string, float> cuentaPorTipo; // Monto recaudado por tipo de vehículo

    // Agrega un vehículo a la cola de la caseta
    void agregarVehículo(Vehículo v) {
        colaVehículos.push(v);
    }

    // Cobra el peaje para el vehículo al frente de la cola
    void cobrarPeaje(std::unordered_map<std::string, float>& tablaPeajes) {
        if (!colaVehículos.empty()) { // Verifica si hay vehículos en la cola
            Vehículo v = colaVehículos.front(); // Obtiene el primer vehículo en la cola
            colaVehículos.pop(); // Elimina el vehículo de la cola
            float peaje = tablaPeajes[v.tipo]; // Obtiene el monto del peaje según el tipo de vehículo
            cuentaTotal += peaje; // Suma el peaje al total recaudado
            cuentaPorTipo[v.tipo] += peaje; // Suma el peaje al total por tipo de vehículo
            std::cout << "Vehículo " << v.placa << " pagó " << peaje << " en peaje.\n"; // Imprime un mensaje de cobro
        }
    }

    // Realiza un arqueo de caja para la caseta y resetea las cuentas
    void realizarArqueo() {
        std::cout << "Arqueo de caja: " << cuentaTotal << "\n"; // Muestra el total recaudado
        cuentaTotal = 0; // Resetea el total recaudado
        cuentaPorTipo.clear(); // Resetea las cuentas por tipo de vehículo
    }
};

// Estructura que representa un punto de cobro con varias casetas
struct PuntoDeCobro {
    std::vector<Caseta> casetas; // Vector que contiene las casetas del punto de cobro
    std::unordered_map<std::string, float> tablaPeajes; // Tabla de peajes por tipo de vehículo

    // Constructor para inicializar la tabla de peajes
    PuntoDeCobro(std::unordered_map<std::string, float> tp) : tablaPeajes(tp) {}

    // Agrega una caseta al punto de cobro
    void agregarCaseta(Caseta c) {
        casetas.push_back(c);
    }

    // Asigna un vehículo a la caseta con la cola más corta
    void llegadaVehículo(Vehículo v) {
        int minCola = 0; // Índice de la caseta con la cola más corta
        for (int i = 1; i < casetas.size(); ++i) {
            // Encuentra la caseta con la cola más corta
            if (casetas[i].colaVehículos.size() < casetas[minCola].colaVehículos.size()) {
                minCola = i;
            }
        }
        casetas[minCola].agregarVehículo(v); // Agrega el vehículo a la caseta seleccionada
    }

    // Realiza el arqueo general del punto de cobro
    void realizarArqueoGeneral() {
        float totalRecaudado = 0; // Variable para el total recaudado en todas las casetas
        for (auto& caseta : casetas) {
            caseta.realizarArqueo(); // Realiza el arqueo de cada caseta
            totalRecaudado += caseta.cuentaTotal; // Suma lo recaudado en cada caseta
        }
        std::cout << "Total recaudado en todas las casetas: " << totalRecaudado << "\n"; // Imprime el total general recaudado
    }
};

int main() {
    // Tabla de peajes por tipo de vehículo
    std::unordered_map<std::string, float> tablaPeajes = {{"auto", 5000}, {"camion", 10000}};
    PuntoDeCobro punto(tablaPeajes); // Crea el punto de cobro con la tabla de peajes

    // Crea dos casetas de peaje y las agrega al punto de cobro
    Caseta caseta1, caseta2;
    punto.agregarCaseta(caseta1);
    punto.agregarCaseta(caseta2);

    // Crea dos vehículos con diferentes tipos
    Vehículo v1("ABC123", "auto");
    Vehículo v2("DEF456", "camion");

    // Los vehículos llegan al punto de cobro y se asignan a las casetas
    punto.llegadaVehículo(v1);
    punto.llegadaVehículo(v2);

    // Se cobra el peaje para el vehículo en cada caseta
    punto.casetas[0].cobrarPeaje(tablaPeajes);
    punto.casetas[1].cobrarPeaje(tablaPeajes);

    // Se realiza el arqueo general del punto de cobro
    punto.realizarArqueoGeneral();

    return 0;
}

```
