# Tarea-6-Programacion-3

Justificación Pregunta 1:

Al insertar valores estrictamente ascendentes, cada nodo nuevo queda como hijo derecho del anterior.

Por lo tanto, para \(n\) nodos, la altura medida en cantidad de nodos es:

H(n)=n

La búsqueda del último elemento requiere recorrer \(n\) nodos. Por ello:

T(n)=c_1n+c_2

Así,

T(n)=O(n)

Además, insertar los \(n\) elementos ordenados desde un árbol vacío requiere:

T_{\text{inserción}}(n)=\sum_{i=1}^{n}O(i)=O(n^2)

Esto demuestra matemáticamente la degradación del BST.
