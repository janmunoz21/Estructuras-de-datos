# Análisis de Código

## 1. Función `funcion`

### 1.1 ¿Qué hace `funcion`?

La función `funcion` toma un vector de estructuras `C` como argumento y calcula el promedio de los valores de los elementos `x` en todas las estructuras del vector. La estructura `C` contiene un arreglo de dos elementos flotantes `x[2]`. La función devuelve una nueva estructura `C` con los valores promedio de `x[0]` y `x[1]`.

### 1.2 Orden de complejidad de `funcion`

El orden de complejidad de la función `funcion` es **O(n)**, donde `n` es el tamaño del vector `v`. Esto se debe a que la función realiza dos bucles anidados: el primer bucle itera sobre todos los elementos del vector `v` (de tamaño `n`), y el segundo bucle itera sobre los dos elementos del arreglo `x` (constante). Por lo tanto, la complejidad es lineal respecto al tamaño del vector `v`.

```cpp
struct C {
    float x[2];
};

C funcion(std::vector<C>& v) {
    C r;
    r.x[0] = r.x[1] = 0;
    std::vector<C>::iterator iT;
    for (iT = v.begin(); iT != v.end(); iT++) {
        for (int j = 0; j < 2; j++) {
            r.x[j] += iT->x[j];
        }
    }
    for (int j = 0; j < 2; j++) {
        r.x[j] /= v.size();
    }
    return r;
}
