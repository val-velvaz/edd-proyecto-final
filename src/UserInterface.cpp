#include "UserInterface.hpp"
#include "Sort.hpp"
#include <iostream>
#include <chrono>

void UserInterface::run() {
    mainMenu();
}

void UserInterface::mainMenu() {
    char op;
    char ultima_op; // igualar a algo 

    do {
        std::cout << "+------------- SISTEMA DE RECETAS --------------+" << std::endl;
        std::cout << "| a. Mostrar la lista de recetas.               |" << std::endl;
        std::cout << "| b. Modificar la lista de recetas.             |" << std::endl;
        std::cout << "| c. Eliminar la lista de recetas.              |" << std::endl;
        std::cout << "+-----------------------------------------------+" << std::endl;
        std::cout << "Para salir presione 's'." << std::endl;

        std::cout << std::endl;
        std::cout << "Seleccione su opcion: "; std::cin >> op;

        op = tolower(op);
        switch (op) {
            case 'a': 
                // mostrar la lista de recetas
                break;
            case 'b':
                // modificar la lista de recetas
                break;
            case 'c':
                // Eliminar la lista de recetas
                break;
            case 's':
                // salir del programa
                std::cout << "Saliendo del programa" << std::endl;
                break;
            default:
                std::cout << "Seleccione una opcion valida." << std::endl;
        }
    } while (op != 's');
}

