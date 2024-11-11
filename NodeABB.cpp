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

        void deletRoot() {
            // Usaremos una pila para hacer un recorrido iterativo
            std::stack<NodeABB*> nodeStack;
            nodeStack.push(this);
            while (!nodeStack.empty()) {
                NodeABB* node = nodeStack.top();
                nodeStack.pop();

                if (node->izq != nullptr) {
                    nodeStack.push(node->izq);
                }
                if (node->der != nullptr) {
                    nodeStack.push(node->der);
                }
                // Luego eliminamos el nodo actual
                delete node;
            }
        }
            

        //bool search(int element) {
        //    // casos bases de la recursion
        //    if (value == -1) return false;
        //    if (value == element) return true;
        //    // revisar izq y der
        //    bool l = false;
        //    bool r = false;
        //    if (der != nullptr) l = der->search(element);
        //    if (izq != nullptr) r = izq->search(element);
        //    return (l || r);
        //}


        bool search(int element) {
            NodeABB* current = this;
            int iteration = 0;
            while (current != nullptr) {
                if (current->value == element) {
                    return true;  
                }
                if (element < current->value) {
                    current = current->izq;  
                } else {
                    current = current->der; 
                }
            }
            return false;  
        }


        void insert(int element) {
            // Caso especial: si el nodo raíz está vacío, lo inicializamos
            if (this->value == -1) {
                value = element;
                return;
            }

            NodeABB* current = this;
            while (true) {
                if (element == current->value) {
                    return;  // No insertamos elementos duplicados
                }

                // Si el elemento es menor, vamos al subárbol izquierdo
                if (element < current->value) {
                    if (current->izq == nullptr) {
                        current->izq = new NodeABB(element);  // Insertar en la izquierda
                        return;
                    } else {
                        current = current->izq;  // Continuar recorriendo la izquierda
                    }
                } 
                // Si el elemento es mayor, vamos al subárbol derecho
                else {
                    if (current->der == nullptr) {
                        current->der = new NodeABB(element);  // Insertar en la derecha
                        return;
                    } else {
                        current = current->der;  // Continuar recorriendo la derecha
                    }
                }
            }
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