// ### Tarea 2 diseño y analisis de algoritmos ###
#include <iostream>
#include <vector>


// usare clases para encapsular la logica de liberar memoria 
class NodeABB {
    public:
        int value = -1;
        // punteros (si no estoy mal evita q explote con definicion recursiva, no estamos en haskell u_u)
        NodeABB* right = nullptr;
        NodeABB* left = nullptr;
        NodeABB() {};
        NodeABB(int v) : value(v) {};

        // La idea es crear nuevos nodos con new NodeABB, de esta forma los punteros no fallaran por scoping
        ~NodeABB() {
            delete right;
            delete left;
        }

        bool search(int element) {
            // casos bases de la recursion
            if (value == -1) return false;
            if (value == element) return true;
            // revisar izq y der
            bool l = false;
            bool r = false;
            if (left != nullptr) l = left->search(element);
            if (right != nullptr) r = right->search(element);
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
                if (left == nullptr) left = new NodeABB(element);
                else left->insert(element);
                return;
            }
            // si e > value: insertamos en el arbol de la derecha
            if (right == nullptr) right = new NodeABB(element);
            else right->insert(element);
            return;
        }


        std::string printTree() {
            //implementar
            return std::string("");
        }
};


int main(){
    NodeABB* root = new NodeABB();
    std::vector<int> a = {10, 5, 3, 1, 8, 3, 8, 10, 3, 15, 17, 19, 6};
    for (int i = 0; i < 10; i++) {
        // insert
        root->insert(a[i]);
        // search
        std::cout << root->search(a[i]) << " ";
    }
    // fail search
    std::cout << std::endl << root->search(100);
}




