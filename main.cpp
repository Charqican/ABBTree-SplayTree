// ### Tarea 2 diseño y analisis de algoritmos ###
#include <iostream>
#include <vector>
#include <iomanip> 
#include <algorithm> 
#include <cmath>
#include <chrono>
#include <random>
#include <climits>
#include "./NodeABB.cpp"
#include "./SplayTree.cpp"
#include "windows.h"


int testSplayTree() {
    SplayTree* tree = new SplayTree();
    tree->insert(1);
    tree->insert(14);
    tree->insert(76);
    tree->insert(46);
    tree->insert(54);
    std::cout << "Arbol inicial: " <<std::endl;
    tree->root->imprimirGrafico();
    tree->search(76);
    std::cout << "Search: 76" <<std::endl;
    tree->root->imprimirGrafico();
    tree->search(1);
    std::cout << "Search: 1" <<std::endl;
    tree->root->imprimirGrafico();
    tree->search(14);
    std::cout << "Search: 14" <<std::endl;
    tree->root->imprimirGrafico();
    tree->search(54);
    std::cout << "Search: 54" <<std::endl;
    tree->root->imprimirGrafico();
    tree->search(1);
    std::cout << "Search: 1" <<std::endl;
    tree->root->imprimirGrafico();
    tree->search(76);
    std::cout << "Search: 76" <<std::endl;
    tree->root->imprimirGrafico();
    tree->search(54);
    std::cout << "Search: 54" <<std::endl;
    tree->root->imprimirGrafico();
    tree->search(46);
    std::cout << "Search: 46" <<std::endl;
    tree->root->imprimirGrafico();
    tree->search(14);
    std::cout << "Search: 14" <<std::endl;
    tree->root->imprimirGrafico();
    std::cout << "Search: 76" <<std::endl;
    tree->search(76);
    tree->root->imprimirGrafico();
    delete tree;
    return 0;
}


void experiment1(int N, int M) {
    std::vector<int> A(N);
    for (int i = 0; i < N; i++) A[i] = i + 1; // Generar N enteros unicos
    std::shuffle(A.begin(), A.end(), std::mt19937{std::random_device{}()});

    // Árbol ABB
    NodeABB* abbRoot = new NodeABB(A[0]);
    SplayTree* splayTree = new SplayTree();
    
    // Insertar elementos en ambos árboles
    for (int i = 0; i < N; i++) {
        abbRoot->insert(A[i]);
        splayTree->insert(A[i]);
    }
    std::cout << "Pasó insert...\n";
    // Crear B con M/N copias de cada A[i]
    std::vector<int> B;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M / N; j++) B.push_back(A[i]);
    }

    // Generar permutación aleatoria de B
    std::shuffle(B.begin(), B.end(), std::default_random_engine());
    std::cout << "Empieza busqueda...\n";
    // Realizar las busquedas y medir tiempos
    auto start = std::chrono::high_resolution_clock::now();
    for (int element : B) abbRoot->search(element);
    std::cout << "Pasó busqueda...\n";
    auto end = std::chrono::high_resolution_clock::now();
    std::cout << "ABB: Tiempo de busqueda = "
              << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()
              << " ms\n";

    start = std::chrono::high_resolution_clock::now();
    for (int element : B) splayTree->search(element);
    end = std::chrono::high_resolution_clock::now();
    std::cout << "Splay: Tiempo de busqueda = "
              << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()
              << " ms\n";

    abbRoot->deletRoot();
    delete splayTree;
}


// Experimento 2: Inserción aleatoria y busquedas con probabilidad sesgada
void experiment2(int N, int M) {
    // Generar N elementos aleatorios para la inserción
    std::vector<int> A(N);
    for (int i = 0; i < N; i++) A[i] = i + 1;
    std::shuffle(A.begin(), A.end(), std::mt19937{std::random_device{}()});

    NodeABB* abbRoot = new NodeABB(A[0]);
    SplayTree* splayTree = new SplayTree();

    // Insertar elementos en ABB y Splay en orden aleatorio
    for (int i = 0; i < N; i++) {
        abbRoot->insert(A[i]);
        splayTree->insert(A[i]);
    }

    std::vector<int> B;
    // Llenar B aplicando la función de probabilidad sesgada
    for (long long i = 0; i < N; i++) {
        int count = static_cast<int>(M * 0.608 / ((i + 1) * (i + 1)));
        count = (count < 0) ? 0 : count;
        for (int j = 0; j < count; j++) {
            B.push_back(A[i]);
        }
    }
    std::shuffle(B.begin(), B.end(), std::mt19937{std::random_device{}()});

    // Medir tiempo de busqueda en ABB
    auto start = std::chrono::high_resolution_clock::now();
    for (int element : B) abbRoot->search(element);
    auto end = std::chrono::high_resolution_clock::now();
    std::cout << "ABB: Tiempo busqueda sesgada = "
              << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()
              << " ms\n";

    // Medir tiempo de busqueda en Splay
    start = std::chrono::high_resolution_clock::now();
    for (int element : B) splayTree->search(element);
    end = std::chrono::high_resolution_clock::now();
    std::cout << "Splay: Tiempo busqueda sesgada = "
              << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()
              << " ms\n";

    abbRoot->deletRoot();
    delete splayTree;
}


// Experimento 3: Inserción en orden y busquedas en arreglo aleatorizado
void experiment3(int N, int M) {
    // Preparar elementos ordenados para la inserción en ABB y Splay
    std::vector<int> A(N);
    for (int i = 0; i < N; i++) A[i] = i + 1;

    NodeABB* abbRoot = new NodeABB(A[0]);
    SplayTree* splayTree = new SplayTree();
    std::cout << "Insertando en ABB y Splay...\n";
    // Insertar en ABB y Splay en orden
    for (int i = 0; i < N; i++) {
        abbRoot->insert(A[i]);
        splayTree->insert(A[i]);
    }

    // Generar el arreglo de busqueda B de tamaño M, con copias de cada elemento en A
    std::vector<int> B;
    int copiesPerElement = M / N;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < copiesPerElement; j++) {
            B.push_back(A[i]);
        }
    }
    std::shuffle(B.begin(), B.end(), std::mt19937{std::random_device{}()});
    std::cout << "Buscando en ABB y Splay...\n";
    // Medir tiempo de busqueda en ABB
    auto start = std::chrono::high_resolution_clock::now();
    for (int element : B) abbRoot->search(element);
    auto end = std::chrono::high_resolution_clock::now();
    std::cout << "ABB: Tiempo de busqueda repetida = "
              << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()
              << " ms\n";

    // Medir tiempo de busqueda en Splay
    start = std::chrono::high_resolution_clock::now();
    for (int element : B) splayTree->search(element);
    end = std::chrono::high_resolution_clock::now();
    std::cout << "Splay: Tiempo de busqueda repetida = "
              << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()
              << " ms\n";

    abbRoot->deletRoot();
    delete splayTree;
}


// Experimento 4: Inserción en orden con probabilidades sesgadas de busqueda
void experiment4(int N, int M = 100) {
    // Generar arreglo aleatorio A y una copia C ordenada
    std::vector<int> A(N);
    for (int i = 0; i < N; i++) A[i] = i + 1;
    std::shuffle(A.begin(), A.end(), std::mt19937{std::random_device{}()});
    std::vector<int> C = A;
    std::sort(C.begin(), C.end());

    NodeABB* abbRoot = new NodeABB(A[0]);
    SplayTree* splayTree = new SplayTree();

    // Insertar elementos ordenados en ABB y Splay usando C
    for (int i = 0; i < N; i++) {
        abbRoot->insert(C[i]);
        splayTree->insert(C[i]);
    }

    std::vector<int> B;

    // Llenar B aplicando la función de probabilidad sesgada
    for (long long i = 0; i < N; i++) {
        int count = static_cast<int>(M * 0.608 / ((i + 1) * (i + 1)));
        for (int j = 0; j < count; j++) {
            B.push_back(A[i]);
        }
    }
    std::shuffle(B.begin(), B.end(), std::mt19937{std::random_device{}()});

    // Medir tiempo de busqueda en ABB
    auto start = std::chrono::high_resolution_clock::now();
    for (int element : B) abbRoot->search(element);
    auto end = std::chrono::high_resolution_clock::now();
    std::cout << "ABB: Tiempo busqueda sesgada = "
              << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()
              << " ms\n";

    // Medir tiempo de busqueda en Splay
    start = std::chrono::high_resolution_clock::now();
    for (int element : B) splayTree->search(element);
    end = std::chrono::high_resolution_clock::now();
    std::cout << "Splay: Tiempo busqueda sesgada = "
              << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()
              << " ms\n";

    abbRoot->deletRoot();
    delete splayTree;
}


int main(int argc, char* argv[]){
    SetConsoleOutputCP(CP_UTF8);
    if (argc == 2 and std::string(argv[1]) == "testSplay")
        testSplayTree();
    else if (argc == 4 and std::string(argv[1]) == "experiment") {
        int i = std::stoi(argv[2]);
        int N = std::stoi(argv[3]);
        if (i == 1) {
            experiment1(N, N*100);
        } else if (i == 2) {
            experiment2(N, N*100);
        } else if (i == 3){
            experiment3(N, N*100);
        } else if (i == 4) {
            experiment4(N, N*100);
        } else {
            std::cerr << "i entre 1 y 4." << std::endl;
        }
    }
    return 0;
}

