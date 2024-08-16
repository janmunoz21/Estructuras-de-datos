# Selección Múltiple con Única Respuesta

## 2.1 Secuencia de Números Enteros

Juanito toma la secuencia de números enteros desde 1 hasta n e inserta la primera mitad en una cola y la segunda mitad en una pila. Luego llena una lista extrayendo primero los elementos de la pila, y luego los elementos de la primera cola. ¿Cómo quedan los elementos en la lista?

**Respuesta:**
b. Los segundos n/2 en orden inverso, luego los primeros n/2 en orden.

**Justificación:**
- La pila (stack) es una estructura LIFO (Last In, First Out), por lo que los elementos de la segunda mitad se extraen en orden inverso.
- La cola (queue) es una estructura FIFO (First In, First Out), por lo que los elementos de la primera mitad se extraen en el mismo orden en que fueron insertados.

## 2.2 Complejidad del Algoritmo

Para realizar un cálculo se cuenta con un algoritmo dividido en dos bloques secuenciales de instrucciones. El primer bloque de instrucciones tiene complejidad O(n), mientras que el segundo bloque de instrucciones tiene complejidad O(log10 n). ¿Cuál es la complejidad del algoritmo completo?

**Respuesta:**
a. O(n)

**Justificación:**
- Cuando se tienen dos bloques secuenciales de instrucciones con diferentes complejidades, la complejidad total del algoritmo es la del bloque con mayor complejidad.
- En este caso, O(n) es mayor que O(log10 n), por lo que la complejidad total del algoritmo es O(n).
