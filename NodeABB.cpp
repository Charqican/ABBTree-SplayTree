#include <iostream>
#include <vector>
#include <iomanip> 
#include <cmath>
#include <stack>


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
            // Usaremos una pila para hacer un recorrido iterativo
            std::stack<NodeABB*> nodeStack;
            nodeStack.push(this);

            while (!nodeStack.empty()) {
                NodeABB* current = nodeStack.top();
                nodeStack.pop();

                // Primero empujamos los hijos a la pila, si existen
                if (current->izq != nullptr) {
                    nodeStack.push(current->izq);
                }
                if (current->der != nullptr) {
                    nodeStack.push(current->der);
                }

                // Luego eliminamos el nodo actual
                delete current;
            }
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


        bool iterativeSearch(int element) {
            NodeABB* current = this;
            while(current!=nullptr) {
                NodeABB* left = current->izq;
                NodeABB* right = current->der;
                
                if (current->value == element) {
                    return true;
                    
                } else if (current->value < element ) {
                    current = left;

                } else {
                    current = right;
                }
            }
            return false;
        }


        void iterativeInsert(int element) {
            if (this->value == -1) {
                value = element;
                return;
            }
            NodeABB* current = this;
            while(true) {
                NodeABB* left = current->izq;
                NodeABB* right = current->der;
                if (current->value == element) {
                    return;
                    
                } else if (current->value < element && left != nullptr ) {
                    current = left;

                } else if (current->value > element && right != nullptr) {
                    current = right;

                } else if (left == nullptr ) {
                    current->izq = new NodeABB(element);
                    return;

                } else if (right == nullptr ) {
                    current->der = new NodeABB(element);
                    return;
                }
            }
        }

        void insert(int element) {
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