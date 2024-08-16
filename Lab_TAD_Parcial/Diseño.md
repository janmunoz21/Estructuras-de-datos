# Diseño e Implementación de TADs para el Cobro de Peajes

## Descripción del Sistema

El sistema de cobro de peajes se encarga de gestionar el mantenimiento y expansión de la infraestructura vial inter-municipal a través de concesiones. Los tramos específicos son entregados a empresas privadas que los mantienen en condiciones adecuadas para el tránsito de vehículos. El sistema debe modelar la llegada de vehículos, el cobro del peaje y el arqueo de caja de las casetas.

## TADs

### TAD Vehículo
**Descripción**: Representa un vehículo que transita por el punto de cobro.

**Atributos**:
- `placa`: Identificación única del vehículo.
- `tipo`: Tipo de vehículo (determina el valor del peaje).

**Operaciones**:
- `crearVehículo(placa, tipo)`: Crea un nuevo vehículo con la placa y tipo especificados.
- `obtenerPlaca()`: Retorna la placa del vehículo.
- `obtenerTipo()`: Retorna el tipo del vehículo.

### TAD Caseta
**Descripción**: Representa una caseta de cobro en el punto de peaje.

**Atributos**:
- `colaVehículos`: Cola de vehículos esperando para pagar el peaje.
- `cuentaTotal`: Total de dinero recaudado.
- `cuentaPorTipo`: Total de dinero recaudado por tipo de vehículo.

**Operaciones**:
- `crearCaseta()`: Crea una nueva caseta de cobro.
- `agregarVehículo(vehículo)`: Agrega un vehículo a la cola de la caseta.
- `cobrarPeaje()`: Realiza el cobro del peaje para el vehículo en la parte frontal de la cola.
- `realizarArqueo()`: Realiza el arqueo de caja y reinicia las cuentas.

### TAD PuntoDeCobro
**Descripción**: Representa el punto de cobro de peaje con varias casetas.

**Atributos**:
- `casetas`: Lista de casetas en el punto de cobro.
- `tablaPeajes`: Tabla con los valores de peaje por tipo de vehículo.

**Operaciones**:
- `crearPuntoDeCobro(tablaPeajes)`: Crea un nuevo punto de cobro con la tabla de peajes especificada.
- `agregarCaseta(caseta)`: Agrega una caseta al punto de cobro.
- `llegadaVehículo(vehículo)`: Modela la llegada de un vehículo al punto de cobro.
- `realizarArqueoGeneral()`: Realiza el arqueo de caja de todas las casetas y retorna el monto total recaudado.

# Diagrma de relación.

```mermaid
classDiagram
    class Vehículo {
        - string placa
        - string tipo
        + crearVehículo(placa, tipo)
        + obtenerPlaca()
        + obtenerTipo()
    }

    class Caseta {
        - queue~Vehículo~ colaVehículos
        - float cuentaTotal
        - unordered_map~string, float~ cuentaPorTipo
        + crearCaseta()
        + agregarVehículo(vehículo)
        + cobrarPeaje(tablaPeajes)
        + realizarArqueo()
    }

    class PuntoDeCobro {
        - vector~Caseta~ casetas
        - unordered_map~string, float~ tablaPeajes
        + crearPuntoDeCobro(tablaPeajes)
        + agregarCaseta(caseta)
        + llegadaVehículo(vehículo)
        + realizarArqueoGeneral()
    }

    Vehículo --> Caseta : se encuentra en
    Caseta --> PuntoDeCobro : pertenece a
    PuntoDeCobro --> Caseta : contiene

```

## Implementación en C++

```cpp
#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>

struct Vehículo {
    std::string placa;
    std::string tipo;

    Vehículo(std::string p, std::string t) : placa(p), tipo(t) {}
};

struct Caseta {
    std::queue<Vehículo> colaVehículos;
    float cuentaTotal = 0;
    std::unordered_map<std::string, float> cuentaPorTipo;

    void agregarVehículo(Vehículo v) {
        colaVehículos.push(v);
    }

    void cobrarPeaje(std::unordered_map<std::string, float>& tablaPeajes) {
        if (!colaVehículos.empty()) {
            Vehículo v = colaVehículos.front();
            colaVehículos.pop();
            float peaje = tablaPeajes[v.tipo];
            cuentaTotal += peaje;
            cuentaPorTipo[v.tipo] += peaje;
            std::cout << "Vehículo " << v.placa << " pagó " << peaje << " en peaje.\n";
        }
    }

    void realizarArqueo() {
        std::cout << "Arqueo de caja: " << cuentaTotal << "\n";
        cuentaTotal = 0;
        cuentaPorTipo.clear();
    }
};

struct PuntoDeCobro {
    std::vector<Caseta> casetas;
    std::unordered_map<std::string, float> tablaPeajes;

    PuntoDeCobro(std::unordered_map<std::string, float> tp) : tablaPeajes(tp) {}

    void agregarCaseta(Caseta c) {
        casetas.push_back(c);
    }

    void llegadaVehículo(Vehículo v) {
        int minCola = 0;
        for (int i = 1; i < casetas.size(); ++i) {
            if (casetas[i].colaVehículos.size() < casetas[minCola].colaVehículos.size()) {
                minCola = i;
            }
        }
        casetas[minCola].agregarVehículo(v);
    }

    void realizarArqueoGeneral() {
        float totalRecaudado = 0;
        for (auto& caseta : casetas) {
            caseta.realizarArqueo();
            totalRecaudado += caseta.cuentaTotal;
        }
        std::cout << "Total recaudado en todas las casetas: " << totalRecaudado << "\n";
    }
};

int main() {
    std::unordered_map<std::string, float> tablaPeajes = {{"auto", 5000}, {"camion", 10000}};
    PuntoDeCobro punto(tablaPeajes);

    Caseta caseta1, caseta2;
    punto.agregarCaseta(caseta1);
    punto.agregarCaseta(caseta2);

    Vehículo v1("ABC123", "auto");
    Vehículo v2("DEF456", "camion");

    punto.llegadaVehículo(v1);
    punto.llegadaVehículo(v2);

    punto.casetas[0].cobrarPeaje(tablaPeajes);
    punto.casetas[1].cobrarPeaje(tablaPeajes);

    punto.realizarArqueoGeneral();

    return 0;
}
```
