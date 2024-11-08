// ### Tarea 2 diseño y analisis de algoritmos ###
#include <iostream>
#include <vector>
#include <iomanip> 
#include <cmath>
#include "./NodeABB.cpp"
#include "./SplayTree.cpp"
#include "windows.h"

void debugTree() {
    SplayTree* tree = new SplayTree();
    tree->root = new NodeSplay(76);
    tree->root->izq = new NodeSplay(54);
    tree->root->izq->parent = tree->root;
    tree->root->izq->izq = new NodeSplay(1);
    tree->root->izq->izq->parent = tree->root->izq;
    tree->root->izq->izq->der = new NodeSplay(14);
    tree->root->izq->izq->der->parent = tree->root->izq->izq;
    tree->root->izq->izq->der->der = new NodeSplay(46);
    tree->root->izq->izq->der->der->parent = tree->root->izq->izq->der;
    tree->search(46);
    tree->root->imprimirGrafico();
}

int main(){
    SetConsoleOutputCP(CP_UTF8);
    // test de ABB tree
    NodeABB* root = new NodeABB();
    std::vector<int> a = {10, 5, 3, 1, 8, 3, 8, 10, 3, 15, 17, 19, 6};
    for (int i = 0; i < 10; i++) {
        // insert
        root->insert(a[i]);
        // search
        std::cout << root->search(a[i]) << " ";
    }
    //std::cout << "------------------------------------" << std::endl;
    //delete root;
    //SplayTree* tree = new SplayTree();
    //std::vector<int> b = {5, 8, 10, 9, 2};
    //for (int c : b) {
    //    // insert
    //    tree->insert(c);
    //    tree->root->imprimirGrafico(); // para mostrar el estado f inal
    //    std::cout<<"--------------------------------------------" << std::endl;
    //}
    //tree->search(5);
    //tree->root->imprimirGrafico(); // muestra el estado final
    //delete tree;
    debugTree();
}

