#include "UserInterface.hpp"
#include "Sort.hpp"
#include <iostream>
#include <chrono>

void UserInterface::run() {
    mainMenu();
}

void UserInterface::mainMenu() {
    char option;
    do {
        std::cout << "Menu Principal" << std::endl;
        std::cout << "A. Probar algoritmos de ordenamiento" << std::endl;
        std::cout << "S. Salir" << std::endl;
        std::cout << "Seleccione una opcion: ";
        std::cin >> option;
        option = toupper(option);

        switch (option) {
            case 'A':
                testSortingAlgorithms();
                break;
            case 'S':
                std::cout << "Saliendo del programa." << std::endl;
                break;
            default:
                std::cout << "Opcion invalida. Intente de nuevo." << std::endl;
        }
    } while (option != 'S');
}

void UserInterface::testSortingAlgorithms() {
    List<BigInt> listA;
    generateRandomList(listA, 1000, 10); 

    List<BigInt> listB;

    listB = listA;
    std::cout << "Antes de Bubble Sort, la lista esta ordenada: " << (Sorters::isSort(listB, Sorters::toTop) ? "Si" : "No") << std::endl;
    auto start = std::chrono::high_resolution_clock::now();
    Sorters::bubbleSort(listB, Sorters::toTop);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> diff = end - start;
    std::cout << "Bubble Sort: " << (Sorters::isSort(listB, Sorters::toTop) ? "Ordenado" : "No Ordenado") << " en " << diff.count() << " segundos." << std::endl;

    listB = listA;
    std::cout << "Antes de Insertion Sort, la lista esta ordenada: " << (Sorters::isSort(listB, Sorters::toTop) ? "Si" : "No") << std::endl;
    start = std::chrono::high_resolution_clock::now();
    Sorters::insertSort(listB, Sorters::toTop);
    end = std::chrono::high_resolution_clock::now();
    diff = end - start;
    std::cout << "Insertion Sort: " << (Sorters::isSort(listB, Sorters::toTop) ? "Ordenado" : "No Ordenado") << " en " << diff.count() << " segundos." << std::endl;

    listB = listA;
    std::cout << "Antes de Selection Sort, la lista esta ordenada: " << (Sorters::isSort(listB, Sorters::toTop) ? "Si" : "No") << std::endl;
    start = std::chrono::high_resolution_clock::now();
    Sorters::selectSort(listB, Sorters::toTop);
    end = std::chrono::high_resolution_clock::now();
    diff = end - start;
    std::cout << "Selection Sort: " << (Sorters::isSort(listB, Sorters::toTop) ? "Ordenado" : "No Ordenado") << " en " << diff.count() << " segundos." << std::endl;

    listB = listA;
    std::cout << "Antes de Shell Sort, la lista esta ordenada: " << (Sorters::isSort(listB, Sorters::toTop) ? "Si" : "No") << std::endl;
    start = std::chrono::high_resolution_clock::now();
    Sorters::shellSort(listB, Sorters::toTop);
    end = std::chrono::high_resolution_clock::now();
    diff = end - start;
    std::cout << "Shell Sort: " << (Sorters::isSort(listB, Sorters::toTop) ? "Ordenado" : "No Ordenado") << " en " << diff.count() << " segundos." << std::endl;

    listB = listA;
    std::cout << "Antes de Merge Sort, la lista esta ordenada: " << (Sorters::isSort(listB, Sorters::toTop) ? "Si" : "No") << std::endl;
    start = std::chrono::high_resolution_clock::now();
    Sorters::mergeSort(listB, Sorters::toTop);
    end = std::chrono::high_resolution_clock::now();
    diff = end - start;
    std::cout << "Merge Sort: " << (Sorters::isSort(listB, Sorters::toTop) ? "Ordenado" : "No Ordenado") << " en " << diff.count() << " segundos." << std::endl;

    listB = listA;
    std::cout << "Antes de Quick Sort, la lista esta ordenada: " << (Sorters::isSort(listB, Sorters::toTop) ? "Si" : "No") << std::endl;
    start = std::chrono::high_resolution_clock::now();
    Sorters::quickSort(listB, Sorters::toTop);
    end = std::chrono::high_resolution_clock::now();
    diff = end - start;
    std::cout << "Quick Sort: " << (Sorters::isSort(listB, Sorters::toTop) ? "Ordenado" : "No Ordenado") << " en " << diff.count() << " segundos." << std::endl;
}

void UserInterface::generateRandomList(List<BigInt>& list, int size, int numDigits) {
    list.init();
    for (int i = 0; i < size; ++i) {
        list.add(i, BigInt::random(numDigits));
    }
}