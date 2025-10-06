#include "UserInterface.hpp"
#include "Sort.hpp"
#include <iostream>
#include <chrono>
#include <limits>
#include <cstdlib>

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
                this->showMenu();
                break;
            case 'b':
                // modificar la lista de recetas
                this->modifyMenu();
                break;
            case 'c':
                // Eliminar la lista de recetas
                this->cleanMenu();
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

void UserInterface::showMenu() {
    std::cout << "+------------ RECETAS DESPLEGADAS ------------+" << std::endl;
    // mostrar la lista de 
}

void UserInterface::modifyMenu() {
    
}

void UserInterface::cleanMenu() {
    
}

void UserInterface::enterToContinue() {
    std::cout << "Presione Enter para continuar...";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.get();
}

void UserInterface::cleanWindow() {
    #ifdef _WIN32
        system("cls");
    #else 
        system("clear");
    #endif

    //opcion 2
    //std::cout << "\033[2J\033[H";
}

