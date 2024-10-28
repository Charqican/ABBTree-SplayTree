// ### Tarea 2 diseño y analisis de algoritmos ###
#include <iostream>
#include <vector>
#include <iomanip> 
#include <cmath>

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


class NodeSplay {
    public: 
        int value = -1; 
        NodeSplay* izq = nullptr;
        NodeSplay* der = nullptr;
        NodeSplay* parent = nullptr;
        NodeSplay(int v) : value(v) {}

        ~NodeSplay() {
            if (izq!=nullptr) delete izq;
            if (der!= nullptr) delete der;
        }

        NodeSplay* search(int element) {
            // casos bases 
            if (value == element) {
                this->splay();
                return this;
            }
            // revisar izq y der
            if (izq != nullptr) {
                NodeSplay* l = izq->search(element);
                if (l!= nullptr) return l;
            }

            if (der != nullptr) {
                NodeSplay* r = der->search(element);
                if (r!= nullptr) return r;
            } 
            return nullptr;
        }


        NodeSplay* insert(int element) {
            // si value es vacio, insertamos en este nodo.
            // caso para nodo inicializado vacio (root).
            if (value == element) {
                return nullptr;
                std::cout<< "Insert: Value was the same: " << element << std::endl;
            }

            // si e < value: insertamos en el arbol de la izquierda
            if (element < value) {
                // si el nodo no existe, fallamos la busqueda -> insertamos y hacemos splay()
                if (izq == nullptr){
                    izq = new NodeSplay(element); // creamos el nodo de la izquierda
                    izq->parent = this; // seteamos el parent
                    NodeSplay* newRoot = izq; // el nodo apunto hacia otro lado, hacemos una copia.
                    izq->splay(); // le aplicamos splay a este nodo // 
                    return newRoot;

                } else { // si no, seguimos recursivamente
                    return izq->insert(element); 
                }

            } else { // si e > value: insertamos en el arbol de la derecha
                if (der == nullptr) {
                    der = new NodeSplay(element);
                    der->parent = this;
                    NodeSplay* newRoot = der; // el nodo apunto hacia otro lado, hacemos una copia.
                    der->splay();
                    return newRoot;
                } else {
                    return der->insert(element);
                } 
            }
            
        }

        
        // cortesia de chatgpt
        void imprimirGrafico(int espacio = 0, bool esIzquierdo = false, const std::string& prefijo = "") {
            if (this == nullptr) {
                return;
            }

            // Procesamos el subárbol derecho primero
            if (der != nullptr) {
                der->imprimirGrafico(espacio + 1, false, prefijo + (esIzquierdo ? "│   " : "    "));
            } else {
                // Imprimimos el subárbol derecho nulo como $
                std::string repetido(std::log10(value), ' ');
                std::cout << prefijo + (esIzquierdo ? "│   " : "    ") + repetido +"┌──$" << std::endl;
            }

            // Imprimimos el nodo actual
            std::cout << prefijo;

            if (esIzquierdo) {
                std::cout << "└── ";
            } else {
                std::cout << "┌── ";
            }

            std::cout << value << std::endl;

            // Procesamos el subárbol izquierdo
            if (izq != nullptr) {
                izq->imprimirGrafico(espacio + 1, true, prefijo + (esIzquierdo ? "    " : "│   "));
            } else {
                // Imprimimos el subárbol izquierdo nulo como $
                std::string repetido(std::log10(value) , ' ');

                std::cout << prefijo + (esIzquierdo ? "    " : "│   ") + repetido+"└── $" << std::endl;
            }
        }
    private:

        void splay() {
            NodeSplay* y = this->parent;
            if (y == nullptr) { // caso base
                return;
            }
            NodeSplay* z = y->parent;
            int a = y->value;
            // caso zig y zag
            if (z == nullptr) {
                if (this->value < a) {
                    zig();
                    return;
                }
                zag(); 
                return;
            }
            int b = z->value;

            if (this->value < a && a < b ) zigZig();
            else if (this->value < a && a > b) zagZig();
            else if (this-> value > a && a > b) zagZag();
            else zigZag();
            splay();
        }

        // creo que no es necesario implementar las 6, pero el enunciado asi lo pedia.
        void zigZig() {
            // asumimos la existencia de y, z
            this->zig();
            this->zig();
        }

        void zigZag() {
            this->zag();
            this->zig();
        }

        void zagZig() {
            this->zig();
            this->zag();
        }

        void zagZag() {
            this->zag();
            this->zag();
        }

        //y(a, x(b, c)) -> x(y(a, b), c)
        void zag() {
            std::cout <<"Zag" << std::endl;
            NodeSplay* y = this->parent;
            NodeSplay* yParent =  y->parent;

            if(yParent != nullptr) {
                // caso compuesto: z(y, ...) -> z(x, ...)
                if (yParent->izq == y) yParent->izq = this;
                // z(..., y) -> z(..., x)
                else yParent->der = this;
            }

            this->parent = yParent;
            y->der = this->izq; //y(a, b)
            if (this->izq != nullptr) this->izq->parent = y; // b->y
            this->izq = y; // x(y(a,b), c)
            y->parent = this; //y->x
        }

        //y(this(a, b), c)-> x(a, y(b, c))
        // esto se utiliza en dos casos, en un zig() comun y en una operacion compuesta
        void zig() {
            std::cout <<"Zig" << std::endl;
            NodeSplay* y = this->parent;
            NodeSplay* yParent = y->parent;

            if(yParent != nullptr) {
                // caso compuesto: z(y, ...) -> z(x, ...)
                if (yParent->izq == y) yParent->izq = this;
                // z(..., y) -> z(..., x)
                else yParent->der = this;
            }
            this->parent = yParent; 
            y->izq = this->der; //y(b, c)
            if (this->der != nullptr) this->der->parent = y; // b -> y
            this->der = y; // x(a, y(b, c))
            y->parent = this; //y->x
        }

};


class SplayTree {
    public:
       
        NodeSplay* root = nullptr;
        // construye el nodo root con un valor y recupera un puntero al puntero del nodo.

        SplayTree() {
        }

        // wrapper para insert de esta clase.
        void insert(int element) {
            if (root == nullptr) {
                root = new NodeSplay(element);
                return;
            }
            NodeSplay* newRoot = root->insert(element);
            if (newRoot == nullptr) {
                std::cout << "insert Failed " << std::endl; 
                return;
            } 
            
            root = newRoot;
        }

        bool search(int element) {
            if (root == nullptr) return false;
            NodeSplay* newRoot = root->search(element);
            if (newRoot == nullptr) return false; // fallo la busqueda
            root = newRoot;
            return true;
        }

        ~SplayTree() { // dijo mi amigo chatgpt q era ineficiente esto.
            if (root != nullptr) delete root;
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
    std::cout << "------------------------------------" << std::endl;
    delete root;
    SplayTree* tree = new SplayTree();
    std::vector<int> b = {5, 8, 10, 9, 2};
    for (int c : b) {
        // insert
        tree->insert(c);
        tree->root->imprimirGrafico();
        std::cout<<"--------------------------------------------" << std::endl;
    }
    tree->search(5);
    tree->root->imprimirGrafico();
}




