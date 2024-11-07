#include <iostream>
#include <vector>
#include <iomanip> 
#include <cmath>



class NodeABB {
    public:
        int value = -1;
        // punteros (si no estoy mal evita q explote con definicion recursiva, no estamos en haskell u_u)
        NodeABB* izq = nullptr;
        NodeABB* der = nullptr;
        NodeABB() {};
        NodeABB(int v) : value(v) {};

        // La idea es crear nuevos nodos con new NodeABB, de esta forma los punteros no fallaran por scoping
        ~NodeABB() {
            delete izq;
            delete der;
        }

        bool search(int element) {
            // casos bases de la recursion
            if (value == -1) return false;
            if (value == element) return true;
            // revisar izq y der
            bool l = false;
            bool r = false;
            if (der != nullptr) l = der->search(element);
            if (izq != nullptr) r = izq->search(element);
            return (l || r);
        }


        void insert(int element) {
            // si value es vacio, insertamos en este nodo.
            if (value == -1) {
                value = element;
                return;
            }
            // si e < value: insertamos en el arbol de la izquierda
            if (element < value) {
                if (der == nullptr) der = new NodeABB(element);
                else der->insert(element);
                return;
            }
            // si e > value: insertamos en el arbol de la derecha
            if (izq == nullptr) izq = new NodeABB(element);
            else izq->insert(element);
            return;
        }


        void imprimirGrafico(int espacio = 0, int nivel = 5) {
            if (this == nullptr) {
                return;
            }

            // Aumentamos el espacio entre niveles
            espacio += nivel;

            // Primero procesamos el subárbol derecho
            if (der != nullptr) {
                der->imprimirGrafico(espacio);
            }

            // Imprimimos el nodo actual después de los espacios
            std::cout << std::endl;
            std::cout << std::setw(espacio) << value << std::endl;

            // Luego procesamos el subárbol izquierdo
            if (izq != nullptr) {
                izq->imprimirGrafico(espacio);
            }
        }
};