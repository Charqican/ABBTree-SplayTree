#include <iostream>
#include <vector>
#include <iomanip> 
#include <cmath>
#include <stack>


// TODO : Se debe limpiar el codigo y ordenar mas las condiciones. 
class NodeSplay {
    // Esta implementacion utiliza 3 punteros a nodos :
    // Primero tenemos 
    public: 
        int value = -1; // caso de nodos no inizializados con valor, al final ni lo uso
        NodeSplay* izq = nullptr;
        NodeSplay* der = nullptr;
        NodeSplay* parent = nullptr;
        NodeSplay(int v) : value(v) {}
        bool printTree = false;


        NodeSplay* iterativeSearch(int element) {
            NodeSplay* current = this;
            while(current != nullptr) {
                if (current->value == element){
                    current->splay();
                    return current;
                }

                if(element < current->value) {
                    current = current->izq;  
                } else {
                    current = current->der; 
                }
            }
            return nullptr;
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

        // Al crear un nodo, retornaremos una copia del valor actual del puntero izq/der.
        // esto porque al hacer splay() el parent tendra distintos hijos. 
        NodeSplay* insert(int element) {
            // si value es vacio, insertamos en este nodo.
            // caso para nodo inicializado vacio (root).
            if (value == element) {
                //std::cout<< "Insert: Value was the same: " << element << std::endl;
                return nullptr;   
            }

            // si e < value: insertamos en el arbol de la izquierda
            if (element < value) {
                // si el nodo no existe, fallamos la busqueda -> insertamos y hacemos splay()
                if (izq == nullptr){
                    izq = new NodeSplay(element); // creamos el nodo de la izquierda
                    izq->parent = this; // seteamos el parent
                    NodeSplay* newRoot = izq; 
                    //std::cout<< "Insert: " << element << std::endl;
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
                    //std::cout<< "Insert: " << element << std::endl;
                    der->splay();
                    return newRoot;
                } else {
                    return der->insert(element);
                } 
            }
            
        }


        void callImprimirGrafico() {
            if(!printTree) return;
            if (this->parent != nullptr) {
                this->parent->callImprimirGrafico();
            } else {
                imprimirGrafico();
            }
        }
        

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

                std::cout << prefijo + (esIzquierdo ? "    " : "│   ") + repetido+"└──$" << std::endl;
            }
        }
    private:


        void splay() {
            while(this->parent != nullptr) {
                NodeSplay* y = this->parent;
                NodeSplay* z = y->parent;
                int a = y->value;
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
            }
        }


        // creo que no es necesario implementar las 6, pero el enunciado asi lo pedia.
        void zigZig() {
            // asumimos la existencia de y, z
            this->zig();
            NodeSplay* z = this->parent;
            NodeSplay* c = this->der->der;
            if (z->parent != nullptr) {
                // si estamos a la derecha del abuelo
                if (z->parent->value < z->value) {
                    z->parent->der = this;
                } else {
                    z->parent->izq = this;
                }
            }
            this->parent = z->parent;
            z->parent = this->der;
            this->der->der = z;
            z->izq = c;
            if (c != nullptr) c->parent = z;
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
            NodeSplay* z = this->parent;
            NodeSplay* b = this->izq->izq;
            if (z->parent != nullptr) {
                // si estamos a la derecha del abuelo
                if (z->parent->value < z->value) {
                    z->parent->der = this;
                } else {
                    z->parent->izq = this;
                }
            }
            this->parent = z->parent;
            z->parent = this->izq;
            
            this->izq->izq = z;
            z->der = b;
            if (b != nullptr) b->parent = z;
        }

        //y(a, x(b, c)) -> x(y(a, b), c)
        void zag() {
            //callImprimirGrafico();
            NodeSplay* y = this->parent;
            NodeSplay* yParent =  y->parent;

            // conectaremos los hijos de x a y
            this->parent = yParent;
            y->der = this->izq; // y(a, x(b, c)) -> y(a, b). 
            if (this->izq != nullptr) this->izq->parent = y; //modificar parent de b
            this->izq = y; // x(b, c) -> x(y(a, b), c)
            y->parent = this; // modificamos el parent de b

            if(yParent != nullptr) {
                // caso compuesto: z(y, ...) -> z(x, ...)
                if (yParent->izq == y) yParent->izq = this;
                // z(..., y) -> z(..., x)
                else yParent->der = this;
            }
            
        }

        // y(x(a, b), c)-> x(a, y(b, c))
        void zig() {
            //callImprimirGrafico();
            NodeSplay* y = this->parent; // y parent de x
            NodeSplay* yParent = y->parent; // z abuelo de x, puede ser null.

            this->parent = yParent; 
            y->izq = this->der; //y(b, c)
            if (this->der != nullptr) this->der->parent = y; // b -> y
            this->der = y; // x(a, y(b, c))
            y->parent = this; //y->x

            if(yParent != nullptr) {
                // caso compuesto: z(y, ...) -> z(x, ...)
                if (yParent->izq == y) yParent->izq = this;
                // z(..., y) -> z(..., x)
                else yParent->der = this;
            }
        }

};

// quiza cambiar la implementacion de delete.
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
            NodeSplay* newRoot = root->iterativeSearch(element);
            if (newRoot == nullptr) return false; // fallo la busqueda
            root = newRoot;
            return true;
        }


        ~SplayTree() { 
            if (this == nullptr) return;
            std::stack<NodeSplay*> stack;
            stack.push(root);
            while (!stack.empty()) {
                NodeSplay* node = stack.top();
                stack.pop();

                // Primero, metemos los hijos en la pila (si existen)
                if (node->izq != nullptr) {
                    stack.push(node->izq);
                }
                if (node->der != nullptr) {
                    stack.push(node->der);
                }

                // Eliminamos el nodo
                delete node;
            }
        }

};