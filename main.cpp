// ### Tarea 2 diseño y analisis de algoritmos ###
#include <iostream>
#include <vector>
#include <iomanip> 

// usare clases para encapsular la logica de liberar memoria y splay() 
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


class NodeSPlay {
    public: 
        int value = -1; 
        NodeSPlay* izq = nullptr;
        NodeSPlay* der = nullptr;
        NodeSPlay* parent = nullptr;
        NodeSPlay(int v) : value(v) {}
        NodeSPlay() {}

        ~NodeSPlay() {
            delete izq;
            delete der;
        }

        bool search(int element) {
            //caso nodo inicializado vacio
            if (value == -1) return false;
            // casos bases 
            if (value == element) this->splay(); return true;
            // revisar izq y der
            bool l = false;
            bool r = false;
            if (izq != nullptr) l = izq->search(element);
            if (der != nullptr) r = der->search(element);
            return (l || r);
        }


        void insert(int element) {
            // si value es vacio, insertamos en este nodo. // caso para nodo inicializado vacio (root).
            if (value == -1 or value == element) {
                value = element;
                return;
            }

            // si e < value: insertamos en el arbol de la izquierda
            if (element < value) {
                // si el nodo no existe, fallamos la busqueda -> insertamos y hacemos splay()
                if (izq == nullptr){
                    izq = new NodeSPlay(element);
                    izq->parent = this;
                    izq->splay();
                    return;
                } else izq->insert(element);
            }
            // si e > value: insertamos en el arbol de la derecha
            if (der == nullptr){
                der = new NodeSPlay(element);
                der->parent = this;
                der->splay();
                return;
            } else der->insert(element);
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
    
    private:

        void splay() {
            NodeSPlay* y = this->parent;
            if (y == nullptr) { // caso base
                return;
            }
            NodeSPlay* z = y->parent;
            int a = y->value;
            // caso zig y zag
            if (z == nullptr) {
                if (this->value < a) zig(); return;
                zag(); return;
            }
            int b = z->value;

            if (this->value < a && a < b ) zigZig();
            else if (this->value < a && a > b) zagZig();
            else if (this-> value > a && a > b) zagZag();
            else zigZag();
            splay();
        }

        void splay2() { // a priori utilizare solo zig y zag

            // casos bases de la recursion.
            if (parent == nullptr) {
                return;
            }

            // x: elemento, y: padre, z: padre del padre
            // sabemos que al menos y existe
            NodeSPlay* y = this->parent;
            NodeSPlay* z = y->parent; // puede ser nulo

            // caso de que y sea raiz
            if (z == nullptr) {
                if (value > parent->value) {
                        zag();
                        return;
                    }
                    zig();
                    return;
            } 

            // de otra forma: Primera operación
            if (y->value < z->value) {
                y->zig();
            } else {
                y->zag();
            }
            // Segunda operacion
            if (this->value < y->value) {
                this->zig();
            }else {
                this->zag();
            }
            // llamada recursiva hasta que lleguemos a la raiz
            splay2();
        }

        // creo que no es necesario implementar las 6, pero el enunciado asi lo pedia.
        void zigZig() {
            // asumimos la existencia de y, z
            NodeSPlay* y = this->parent;
            y->zig(); this->zag();
        }

        void zigZag() {
            NodeSPlay* y = this->parent;
            y->zig(); this->zag();
        }

        void zagZig() {
            NodeSPlay* y = this->parent;
            y->zag(); this->zig();
        }

        void zagZag() {
            NodeSPlay* y = this->parent;
            y->zag(); this->zag();
        }

        void zag() {
            NodeSPlay* y = this->parent;
            NodeSPlay* yParent =  y->parent;

            // subimos x
            this->parent = yParent;
            y->parent = this;

            // reconecatmos los hijos
            NodeSPlay* izqTemp = this->izq;
            this->izq = y;
            y->der = izqTemp;
        }

        void zig() {
            NodeSPlay* y = this->parent;
            NodeSPlay* yParent = y->parent;

            // subimos x
            this->parent = yParent;
            y->parent = this;

            // reconectar los hijos
            NodeSPlay* derTemp = this->der;
            this->der = y;
            y->izq = derTemp;
        }

};



int main(){
    // test de ABB tree
    NodeABB* root = new NodeABB();
    std::vector<int> a = {10, 5, 3, 1, 8, 3, 8, 10, 3, 15, 17, 19, 6};
    for (int i = 0; i < 10; i++) {
        // insert
        root->insert(a[i]);
        // search
        std::cout << root->search(a[i]) << " ";
    }
    // fail search
    //std::cout << std::endl << root->search(100);
    //std::cout << "------------------------------------" << std::endl;
    //root->imprimirGrafico();
    std::cout << "------------------------------------" << std::endl;

    NodeSPlay* rootsp = new NodeSPlay(5);

    std::vector<int> b = {10, 5};
    for (int c : b) {
        // insert
        rootsp->insert(c);
        std::cout << "------------------------------------" << std::endl;
        rootsp->imprimirGrafico();
        std::cout << "------------------------------------" << std::endl;
    }
}




