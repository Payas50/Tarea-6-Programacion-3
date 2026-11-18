# Tarea 6 — Árboles y Grafos

**Curso:** Programación III · **Periodo:** 2026-2  
**Tema:** Árboles balanceados y recorridos iterativos  
**Lenguaje:** C++20

## Descripción

Se implementan cuatro ejercicios: un árbol binario de búsqueda (BST) con operaciones iterativas, un árbol rojo-negro (Red-Black Tree), una búsqueda en profundidad (DFS) iterativa y un recorrido por niveles (BFS) iterativo. Se incluyen pruebas en `main()`, análisis de complejidad y justificaciones matemáticas.

## Estructura del repositorio

```text
.
├── Ejercicio1.cpp
├── Ejercicio2.cpp
├── Ejercicio3.cpp
├── Ejercicio4.cpp
└── README.md
```

## Compilación y ejecución

Cada archivo contiene su propia función `main()`, por lo que debe compilarse como ejecutable independiente. Por ejemplo:

```bash
g++ -std=c++20 Ejercicio1.cpp -o ejercicio1
./ejercicio1
```

En Windows, puede ejecutarse `ejercicio1.exe` en lugar de `./ejercicio1`. Para los otros ejercicios, cambiar el número del archivo y del ejecutable. En CLion se pueden configurar cuatro ejecutables diferentes.

---

## Ejercicio 1 — BST iterativo y análisis de degradación

### Objetivo

Implementar un árbol binario de búsqueda (BST) con inserción y eliminación iterativas, recorrido *in-order* mediante `std::stack` y cálculo de altura. Probar con 20 elementos, eliminar dos y analizar la degradación al insertar datos ordenados.

### Implementación

- **Inserción iterativa:** se recorre el árbol comparando el valor con el nodo actual. Se avanza a la izquierda si es menor y a la derecha si es mayor, hasta encontrar un enlace vacío. Se ignoran duplicados.
- **Eliminación iterativa:** se busca el nodo sin recursión. Si tiene cero o un hijo, se reemplaza por ese hijo; si tiene dos, se copia el valor de su sucesor *in-order* (el menor del subárbol derecho) y se elimina dicho sucesor.
- **Recorrido in-order:** una pila `std::stack` permite visitar izquierda, raíz y derecha sin recursión. En un BST produce los valores ordenados.
- **Altura:** se usa una cola `std::queue` para recorrer los niveles. En esta implementación la altura se mide como **número de nodos** del camino más largo desde la raíz hasta una hoja; un árbol vacío tiene altura 0.
- **Preorden:** se incluye un recorrido iterativo adicional para visualizar la estructura del árbol.

### Prueba y resultados

Se insertan los enteros del **1 al 20 en orden ascendente** y se eliminan **5 y 15**.

```text
Altura inicial: 20
Inorden: 1 2 3 4 6 7 8 9 10 11 12 13 14 16 17 18 19 20
Preorden: 1 2 3 4 6 7 8 9 10 11 12 13 14 16 17 18 19 20
Altura final: 18
```

El preorden coincide con el inorden porque todos los nodos del BST resultante están encadenados hacia la derecha.

### Demostración matemática de la degradación

Al insertar la secuencia estrictamente creciente $1,2,\ldots,n$, cada elemento nuevo es mayor que todos los anteriores, por lo que se inserta como hijo derecho del último nodo. Así, el árbol es una cadena de $n$ nodos y su altura es

$$
h(n)=n.
$$

En el peor caso, una búsqueda o una inserción debe visitar los $n$ nodos de esa cadena. Si cada visita cuesta una constante $c>0$, entonces

$$
T(n)=cn+d=\Theta(n),
$$

por lo tanto también es $O(n)$. Además, construir el BST mediante $n$ inserciones ordenadas cuesta

$$
T_{\text{construcción}}(n)=\sum_{i=1}^{n}\Theta(i)=\Theta\!\left(\frac{n(n+1)}2\right)=\Theta(n^2).
$$

**Conclusión:** un BST ordinario no garantiza altura logarítmica; con datos ordenados puede tener altura lineal y operaciones de búsqueda de costo $\Theta(n)$.

---

## Ejercicio 2 — Red-Black Tree

### Objetivo

Implementar inserción en un árbol rojo-negro, con rotaciones, recoloración, corrección de violaciones, verificación formal de propiedades y cálculo de altura. Comparar su altura con la de un BST después de insertar los mismos 20 valores ascendentes.

### Propiedades verificadas

1. Cada nodo es rojo o negro.
2. La raíz es negra.
3. Ningún nodo rojo tiene hijos rojos.
4. Todos los caminos desde un nodo hasta sus hojas nulas tienen el mismo número de nodos negros.
5. Las hojas nulas son negras.

La implementación usa un nodo centinela negro `nil` para representar todas las hojas nulas. También comprueba el orden de los valores propio de un BST.

### Inserción y balanceo

Cada nodo nuevo se inserta inicialmente de color **rojo**. Si su padre es negro, no hace falta corregir nada. Si el padre es rojo, se analiza el color del tío:

- **Tío rojo:** se recolorean padre y tío de negro y abuelo de rojo; después se continúa revisando desde el abuelo.
- **Tío negro, disposición triangular:** se realiza una primera rotación para transformar la configuración en lineal.
- **Tío negro, disposición lineal:** se recolorean padre y abuelo y se realiza una rotación sobre el abuelo.

Se implementan tanto la rotación izquierda como la derecha, junto con sus casos simétricos. Al finalizar, la raíz se fuerza a negro.

### Verificación formal

El método `verificar()` comprueba que el centinela sea negro, que la raíz sea negra y que se mantengan las propiedades del árbol. La función auxiliar `validar()` revisa recursivamente los límites de las claves, la ausencia de pares padre-hijo rojos y la igualdad de alturas negras en ambos subárboles. Devuelve un valor negativo si encuentra una violación.

> Nota: la inserción, rotaciones y correcciones están implementadas en el código; las funciones auxiliares de altura, preorden y validación usan recursión, algo que el enunciado de este ejercicio no prohíbe.

### Comparación experimental

Se insertan los valores del 1 al 20 en orden ascendente en ambos árboles, **antes de eliminar elementos del BST**.

| Estructura | Nodos | Altura (nodos) |
|---|---:|---:|
| BST sin balanceo | 20 | 20 |
| Red-Black Tree | 20 | 6 |

El Red-Black Tree también muestra `Propiedades: VALIDAS`. El programa imprime su recorrido **preorden con colores**, usando `(R)` para rojo y `(N)` para negro, lo que permite reconstruir su disposición junto con las reglas de BST. El ejercicio 1 imprime el preorden del BST.

### Demostración matemática de la cota logarítmica

Sea $bh$ la **altura negra** de la raíz, entendida como el número de nodos negros en un camino descendente sin contar la raíz y contando la hoja nula. Por la igualdad de alturas negras, un subárbol de altura negra $bh$ contiene al menos

$$
n\ge 2^{bh}-1
$$

nodos internos. Esto se prueba por inducción: para $bh=0$ no se requiere ningún nodo interno; para $bh>0$, cada subárbol hijo tiene altura negra de al menos $bh-1$, por lo que el mínimo satisface $N(bh)\ge 1+2N(bh-1)$.

Como dos nodos rojos no pueden ser consecutivos, en un camino raíz-hoja hay a lo sumo tantos nodos rojos como negros. Por tanto, la altura $h$ (medida en nodos internos) satisface

$$
h\le 2bh.
$$

De la primera desigualdad,

$$
bh\le \log_2(n+1).
$$

Combinando ambas,

$$
\boxed{h\le 2\log_2(n+1)=O(\log n)}.
$$

**Conclusión:** el recoloreo y las rotaciones evitan la degeneración lineal del BST y garantizan una altura logarítmica. La inserción tiene costo $O(\log n)$.

---

## Ejercicio 3 — DFS iterativo avanzado

### Objetivo

Determinar si existe un camino **raíz-hoja** cuya suma de valores sea exactamente $K$, y devolverlo utilizando `std::stack`, sin recursión.

### Implementación

La pila guarda estados con tres componentes: nodo actual, suma acumulada y vector de valores del camino. Al extraer un estado:

1. Se comprueba si el nodo es una hoja (sin hijos).
2. Si es hoja y la suma acumulada es $K$, se devuelve el camino.
3. En caso contrario, se agregan los hijos a la pila con sus respectivas sumas y caminos actualizados.

Se apila primero el hijo derecho y luego el izquierdo, para que el izquierdo se procese primero debido al comportamiento LIFO de la pila.

### Prueba

Se utiliza el siguiente árbol:

```text
          5
         / \
        4   8
       /   / \
      11  13  4
     /  \      \
    7    2      1
```

Para $K=22$, el resultado es:

```text
Camino con suma 22: 5 4 11 2
```

Verificación:

$$
5+4+11+2=22.
$$

### Justificación de DFS

DFS es apropiado porque explora caminos completos antes de retroceder. Cada estado conserva la suma parcial y la secuencia de nodos, de modo que es posible verificar la condición **únicamente al alcanzar una hoja**, sin confundir un camino parcial con un camino raíz-hoja.

**Complejidad:** cada nodo se procesa una vez, pero el código copia el vector del camino al crear estados. Para una altura máxima $h$, el tiempo total es $O(nh)$ en el peor caso (y puede llegar a $O(n^2)$ en un árbol degenerado). La memoria es $O(nh)$ como cota superior conservadora por los caminos almacenados en la pila. Sin esas copias, el recorrido estructural DFS sería $O(n)$.

---

## Ejercicio 4 — BFS iterativo avanzado

### Objetivo

Usar `std::queue`, sin recursión, para determinar si un árbol es completo, calcular su ancho máximo y encontrar su profundidad mínima.

### Implementación

BFS procesa los nodos por niveles, gracias a que la cola sigue el orden FIFO.

- **Árbol completo:** todos los niveles anteriores al último deben estar llenos y los nodos del último nivel deben ocupar posiciones consecutivas desde la izquierda. El algoritmo activa `hueco` cuando encuentra un hijo ausente. Si posteriormente aparece otro hijo, el árbol no es completo.
- **Ancho máximo:** antes de procesar cada nivel se consulta el tamaño de la cola; el máximo de esos tamaños es el mayor número de nodos en un nivel.
- **Profundidad mínima:** la primera hoja encontrada por BFS está en el nivel de menor profundidad. El programa cuenta la raíz como nivel 1.

### Prueba

```text
        1
       / \
      2   3
     / \ /
    4  5 6
```

Resultado:

```text
Completo: Si
Ancho maximo: 3
Profundidad minima: 3
```

El árbol es completo porque el último nivel contiene los nodos 4, 5 y 6, ubicados de izquierda a derecha sin espacios intermedios. Su ancho máximo es 3, y la hoja más cercana a la raíz está en el nivel 3.

### Justificación formal de BFS

BFS mantiene el siguiente invariante: **los nodos se extraen de la cola en orden no decreciente de profundidad**, y dentro de cada nivel se procesan de izquierda a derecha. Esto se cumple inicialmente con la raíz; cuando se extrae un nodo de profundidad $d$, sus hijos se añaden al final con profundidad $d+1$, después de los nodos pendientes del nivel $d$.

Como consecuencia:

1. La primera hoja encontrada tiene profundidad mínima, pues ninguna hoja de profundidad menor puede quedar sin procesar.
2. Los nodos de un mismo nivel se procesan consecutivamente, por lo que contar la cola al inicio de cada nivel permite calcular el ancho máximo.
3. El orden de izquierda a derecha permite detectar cualquier nodo que aparezca después de un hueco, lo cual viola la condición de árbol completo.

**Complejidad:** cada nodo se encola y desencola exactamente una vez, así que el tiempo es $\Theta(n)$. La cola almacena como máximo un número de nodos proporcional al ancho del árbol; por tanto, la memoria es $O(w)$, donde $w$ es el ancho máximo, y $O(n)$ en el peor caso.

---

## Resumen de complejidades

| Ejercicio | Operación principal | Tiempo | Memoria adicional |
|---|---|---|---|
| 1 — BST | Buscar o insertar en árbol degenerado | $O(n)$ | $O(1)$ para inserción iterativa |
| 1 — BST | Construir con $n$ valores ordenados | $\Theta(n^2)$ | $O(1)$ auxiliar de inserción |
| 1 — BST | Recorrido in-order iterativo | $O(n)$ | $O(h)$ |
| 2 — Red-Black Tree | Inserción | $O(\log n)$ | $O(1)$ auxiliar de inserción |
| 2 — Red-Black Tree | Verificación de propiedades | $O(n)$ | $O(h)$ por recursión |
| 3 — DFS | Buscar camino con copia de vectores | $O(nh)$ | $O(nh)$ (cota superior) |
| 4 — BFS | Analizar árbol | $O(n)$ | $O(w)$ |

Aquí $n$ representa el número de nodos, $h$ la altura del árbol y $w$ su ancho máximo. Las cotas corresponden a las implementaciones incluidas en este repositorio.

## Conclusiones generales

- La inserción de datos ordenados puede convertir un BST sin balanceo en una cadena y elevar su altura a $\Theta(n)$.
- El Red-Black Tree mantiene altura $O(\log n)$ mediante reglas de coloreo y rotaciones. En la prueba con 20 valores ascendentes, la altura fue 6 frente a 20 en el BST.
- DFS con `std::stack` permite buscar caminos raíz-hoja sin recurrir a llamadas recursivas; la copia de caminos facilita devolver el resultado, aunque aumenta el costo.
- BFS con `std::queue` es adecuado para propiedades definidas por niveles, como completitud, ancho máximo y profundidad mínima.
- Las pruebas en las funciones `main()` permiten observar el comportamiento de cada estructura y comprobar los resultados esperados.
