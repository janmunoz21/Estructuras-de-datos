# Modelos de llegada de vehículo, cobrar vehiculo y arqueo de caja.

## 3.2.1 Modelar la Llegada de un Vehículo

### Descripción
Modelar la llegada de un vehículo al punto de cobro. Los vehículos que llegan se ubican en la cola de la caseta que tiene menos vehículos esperando.

### Implementación en C++

```cpp
void PuntoDeCobro::llegadaVehículo(Vehículo v) {
    int minCola = 0;
    for (int i = 1; i < casetas.size(); ++i) {
        if (casetas[i].colaVehículos.size() < casetas[minCola].colaVehículos.size()) {
            minCola = i;
        }
    }
    casetas[minCola].agregarVehículo(v);
}
```

## 3.2.2 Modelar el Cobro del Peaje en una Caseta Dada
### Descripción
Modelar el cobro del peaje para un vehículo en una caseta dada. De acuerdo al tipo del vehículo que está adelante en la cola, se almacena su información de identificación y el valor cobrado como peaje, se actualiza la cuenta individual de la caseta especificada, y se retira el vehículo de la cola.

### Implementación en C++
```cpp
void Caseta::cobrarPeaje(std::unordered_map<std::string, float>& tablaPeajes) {
    if (!colaVehículos.empty()) {
        Vehículo v = colaVehículos.front();
        colaVehículos.pop();
        float peaje = tablaPeajes[v.tipo];
        cuentaTotal += peaje;
        cuentaPorTipo[v.tipo] += peaje;
        std::cout << "Vehículo " << v.placa << " pagó " << peaje << " en peaje.\n";
    }
}
```


## 3.2.3 Realizar el Arqueo de Caja del Punto de Cobro
### Descripción
Realizar el arqueo de caja de las casetas del punto de cobro. Se recopila la información de las cuentas individuales de cada caseta para averiguar el monto total recibido hasta el momento por concepto de peajes, discriminado también de acuerdo a los tipos de vehículo especificados en la tabla del punto de cobro.

### Implementación en C++
```cpp
void PuntoDeCobro::realizarArqueoGeneral() {
    float totalRecaudado = 0;
    std::unordered_map<std::string, float> totalPorTipo;
    for (auto& caseta : casetas) {
        totalRecaudado += caseta.cuentaTotal;
        for (const auto& [tipo, total] : caseta.cuentaPorTipo) {
            totalPorTipo[tipo] += total;
        }
        caseta.realizarArqueo();
    }
    std::cout << "Total recaudado en todas las casetas: " << totalRecaudado << "\n";
    for (const auto& [tipo, total] : totalPorTipo) {
        std::cout << "Total recaudado para tipo " << tipo << ": " << total << "\n";
    }
}
```
