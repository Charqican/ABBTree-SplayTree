# ABBTree-SplayTree
 Tarea 2 curso analisis y diseño de algoritmos. Esta tarea fue realizada utilizando c++(20).

## Comandos:

* make main ARGS="experiment i N"         

* make main ARGS="testSplay"              

* make clean


## Argumentos
* experiment: ejecuta un experimento.
* testplay: ejecuta un test.
* i: el numero de experimento correspondiente al enunciado.
* N: el numero de elementos a insertar, entre 10^5 y 10^6.

## Ejemplos
* Comando 1: corre el experimento i-esimo y entrega el tiempo de busqueda. 
    Ejemplo:  El siguiente comando corre el experimento 1 para N=100000: make main ARGS="experiment 1 100000".

    -----Output-------
    >./main experiment 2 100000\
    >ABB: Tiempo busqueda sesgada = 165 ms\
    >Splay: Tiempo busqueda sesgada = 334 ms\

* El segundo comando muestra un ejemplo de las rotaciones de un splaytree.


 ## Ejemplo de implementación de operacion: Zig

 considerar que la operación Zig se hace sobre X (this->zig())

 
![Diagrama sin título drawio](https://github.com/user-attachments/assets/79925180-3a8c-44fc-b59c-b86f0245fc9f)
