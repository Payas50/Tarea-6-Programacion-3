# Tarea 6 — Árboles y Grafos

**Curso:** Programación III · **Periodo:** 2026-2  
**Tema:** Árboles balanceados y recorridos iterativos  

## Ejercicio 1 — BST iterativo y análisis de degradación

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

### Justificación de DFS

DFS es apropiado porque explora caminos completos antes de retroceder. Cada estado conserva la suma parcial y la secuencia de nodos, de modo que es posible verificar la condición **únicamente al alcanzar una hoja**, sin confundir un camino parcial con un camino raíz-hoja.

**Complejidad:** cada nodo se procesa una vez, pero el código copia el vector del camino al crear estados. Para una altura máxima $h$, el tiempo total es $O(nh)$ en el peor caso (y puede llegar a $O(n^2)$ en un árbol degenerado). La memoria es $O(nh)$ como cota superior conservadora por los caminos almacenados en la pila. Sin esas copias, el recorrido estructural DFS sería $O(n)$.

---

## Ejercicio 4 — BFS iterativo avanzado

### Justificación formal de BFS

BFS mantiene el siguiente invariante: **los nodos se extraen de la cola en orden no decreciente de profundidad**, y dentro de cada nivel se procesan de izquierda a derecha. Esto se cumple inicialmente con la raíz; cuando se extrae un nodo de profundidad $d$, sus hijos se añaden al final con profundidad $d+1$, después de los nodos pendientes del nivel $d$.

Como consecuencia:

1. La primera hoja encontrada tiene profundidad mínima, pues ninguna hoja de profundidad menor puede quedar sin procesar.
2. Los nodos de un mismo nivel se procesan consecutivamente, por lo que contar la cola al inicio de cada nivel permite calcular el ancho máximo.
3. El orden de izquierda a derecha permite detectar cualquier nodo que aparezca después de un hueco, lo cual viola la condición de árbol completo.

**Complejidad:** cada nodo se encola y desencola exactamente una vez, así que el tiempo es $\Theta(n)$. La cola almacena como máximo un número de nodos proporcional al ancho del árbol; por tanto, la memoria es $O(w)$, donde $w$ es el ancho máximo, y $O(n)$ en el peor caso.
