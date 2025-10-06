#include "UserInterface.hpp"
#include <iostream>
#include <limits>
#include <string>

UserInterface::UserInterface() {
    myBook.loadFromFile(FILENAME);
}

void UserInterface::run() {
    mainMenu();
    std::cout << "\nGuardando recetario en " << FILENAME << "..." << std::endl;
    myBook.saveToFile(FILENAME);
    std::cout << "¡Hasta luego!" << std::endl;
}

void UserInterface::mainMenu() {
    char option;
    do {
        std::cout << "\n===== GESTOR DE RECETAS =====\n"
                << "1. Mostrar recetas\n"
                << "2. Agregar nueva receta\n"
                << "3. Buscar una receta\n"
                << "4. Eliminar una receta\n"
                << "5. Ordenar recetario\n"
                << "6. Gestionar ingredientes de una receta\n"
                << "7. Eliminar TODAS las recetas\n"
                << "S. Salir y Guardar\n"
                << "=============================\n"
                << "Elige una opcion: ";
        std::cin >> option;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        switch (toupper(option)) {
            case '1': showRecipesMenu(); break;
            case '2': addRecipeMenu(); break;
            case '3': findRecipeMenu(); break;
            case '4': deleteRecipeMenu(); break;
            case '5': sortRecipeMenu(); break;
            case '6': manageIngredientsMenu(); break;
            case '7': {
                std::cout << "\n*** ¡ADVERTENCIA! ***\n¿Seguro que quieres borrar TODAS las recetas? (S/N): ";
                char confirm;
                std::cin >> confirm;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                if (toupper(confirm) == 'S') {
                    myBook.deleteAllRecipes();
                    std::cout << "Se han eliminado todas las recetas.\n";
                } else {
                    std::cout << "Operacion cancelada.\n";
                }
                pressEnterToContinue();
                break;
            }
            case 'S': break;
            default: std::cout << "Opcion no valida. Intentalo de nuevo.\n"; pressEnterToContinue();
        }
    } while (toupper(option) != 'S');
}


void UserInterface::showRecipesMenu() {
    char option;
    std::cout << "\n--- Mostrar Recetas ---\n"
            << "A. Mostrar todas\n"
            << "B. Filtrar por categoria\n"
            << "Elige una opcion: ";
    std::cin >> option;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    if (toupper(option) == 'A') {
        showAllRecipes();
    } else if (toupper(option) == 'B') {
        showFilteredRecipes();
    } else {
        std::cout << "Opcion no valida.\n";
    }
    pressEnterToContinue();
}

void UserInterface::addRecipeMenu() {
    Recipe newRecipe;
    std::cout << "\n--- Agregar Nueva Receta ---\n";
    std::cout << "Nombre del platillo: ";
    std::getline(std::cin, newRecipe.name);
    std::cout << "Autor: ";
    std::getline(std::cin, newRecipe.author);
    std::cout << "Tiempo de preparacion (minutos): ";
    std::cin >> newRecipe.prepTime;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    
    newRecipe.category = selectCategory();
    
    std::cout << "Procedimiento (escribe 'FIN' en una linea nueva para terminar):\n";
    std::string line;
    while (std::getline(std::cin, line) && line != "FIN") {
        newRecipe.procedure += line + "\n";
    }
    
    myBook.addRecipe(newRecipe);
    std::cout << "\n¡Receta '" << newRecipe.name << "' agregada con exito!\n";
    pressEnterToContinue();
}

void UserInterface::findRecipeMenu() {
    std::cout << "\n--- Buscar Receta ---\n";
    std::cout << "Introduce el nombre del platillo a buscar: ";
    std::string name;
    std::getline(std::cin, name);
    
    int index = myBook.findRecipeByName(name);
    if (index != -1) {
        std::cout << "Receta encontrada:\n";
        std::cout << myBook.getRecipe(index).toString();
    } else {
        std::cout << "No se encontro ninguna receta con ese nombre.\n";
    }
    pressEnterToContinue();
}

void UserInterface::deleteRecipeMenu() {
    std::cout << "\n--- Eliminar Receta ---\n";
    std::cout << "Introduce el nombre del platillo a eliminar: ";
    std::string name;
    std::getline(std::cin, name);
    
    int index = myBook.findRecipeByName(name);
    if (index != -1) {
        myBook.deleteRecipeByName(name);
        std::cout << "Receta '" << name << "' eliminada correctamente.\n";
    } else {
        std::cout << "No se encontro ninguna receta con ese nombre.\n";
    }
    pressEnterToContinue();
}

void UserInterface::sortRecipeMenu() {
    std::cout << "\n--- Ordenar Recetario ---\n"
            << "A. Ordenar por nombre\n"
            << "B. Ordenar por tiempo de preparacion\n"
            << "Elige una opcion: ";
    char option;
    std::cin >> option;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    
    if (toupper(option) == 'A') {
        myBook.sortRecipesByName();
        std::cout << "Recetario ordenado por nombre.\n";
    } else if (toupper(option) == 'B') {
        myBook.sortRecipesByPrepTime();
        std::cout << "Recetario ordenado por tiempo de preparacion.\n";
    } else {
        std::cout << "Opcion no valida.\n";
    }
    pressEnterToContinue();
}

void UserInterface::manageIngredientsMenu() {
    std::cout << "\n--- Gestion de Ingredientes ---\n";
    std::cout << "Nombre de la receta a modificar: ";
    std::string recipeName;
    std::getline(std::cin, recipeName);

    int recipeIndex = myBook.findRecipeByName(recipeName);
    if (recipeIndex == -1) {
        std::cout << "Receta no encontrada.\n";
        pressEnterToContinue();
        return;
    }

    Recipe& recipe = myBook.getRecipe(recipeIndex);
    char option;
    do {
        std::cout << "\nModificando: '" << recipe.name << "'\n"
                << "1. Agregar ingrediente\n"
                << "2. Eliminar ingrediente\n"
                << "3. Modificar cantidad de un ingrediente\n"
                << "4. Eliminar todos los ingredientes\n"
                << "V. Volver al menu principal\n"
                << "Elige una opcion: ";
        std::cin >> option;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        switch (toupper(option)) {
            case '1': {
                Ingredient newIngredient;
                std::cout << "Nombre del ingrediente: ";
                std::getline(std::cin, newIngredient.name);
                std::cout << "Cantidad (ej. 200 gr, 1 taza): ";
                std::getline(std::cin, newIngredient.quantity);
                recipe.ingredients.add(recipe.ingredients.last() + 1, newIngredient);
                std::cout << "Ingrediente agregado.\n";
                break;
            }
            case '2': {
                std::cout << "Nombre del ingrediente a eliminar: ";
                std::string ingredientName;
                std::getline(std::cin, ingredientName);
                bool found = false;
                for (int i = 0; i <= recipe.ingredients.last(); ++i) {
                    if (recipe.ingredients.get(i).name == ingredientName) {
                        recipe.ingredients.del(i);
                        found = true;
                        std::cout << "Ingrediente eliminado.\n";
                        break;
                    }
                }
                if (!found) std::cout << "Ingrediente no encontrado.\n";
                break;
            }
            case '3': {
                std::cout << "Nombre del ingrediente a modificar: ";
                std::string ingredientName;
                std::getline(std::cin, ingredientName);
                bool found = false;
                for (int i = 0; i <= recipe.ingredients.last(); ++i) {
                     // Creamos una copia para poder modificarla
                    Ingredient tempIngredient = recipe.ingredients.get(i);
                    if (tempIngredient.name == ingredientName) {
                        std::cout << "Nueva cantidad: ";
                        std::getline(std::cin, tempIngredient.quantity);
                        // Borramos el antiguo y añadimos el nuevo
                        recipe.ingredients.del(i);
                        recipe.ingredients.add(i, tempIngredient);
                        found = true;
                        std::cout << "Cantidad modificada.\n";
                        break;
                    }
                }
                if (!found) std::cout << "Ingrediente no encontrado.\n";
                break;
            }
            case '4': {
                recipe.ingredients.init();
                std::cout << "Todos los ingredientes han sido eliminados.\n";
                break;
            }
            case 'V': break;
            default: std::cout << "Opcion no valida.\n";
        }
        if (toupper(option) != 'V') pressEnterToContinue();
    } while (toupper(option) != 'V');
}

void UserInterface::showAllRecipes() {
    const auto& recipes = myBook.getRecipes();
    if (recipes.empty()) {
        std::cout << "\nNo hay recetas en el recetario.\n";
        return;
    }
    std::cout << "\n--- Todas las Recetas ---\n";
    for (int i = 0; i <= recipes.last(); ++i) {
        std::cout << recipes.get(i).toString();
    }
}

void UserInterface::showFilteredRecipes() {
    std::cout << "\n--- Filtrar por Categoria ---\n";
    Category category = selectCategory();
    bool found = false;
    const auto& recipes = myBook.getRecipes();

    for (int i = 0; i <= recipes.last(); ++i) {
        if (recipes.get(i).category == category) {
            std::cout << recipes.get(i).toString();
            found = true;
        }
    }
    if (!found) {
        std::cout << "No se encontraron recetas en esa categoria.\n";
    }
}

Category UserInterface::selectCategory() {
    char option;
    std::cout << "Selecciona una categoria:\n"
            << "D. Desayuno\n"
            << "C. Comida\n"
            << "E. Cena\n"
            << "N. Navideno\n"
            << "Elige una opcion: ";
    std::cin >> option;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    switch (toupper(option)) {
        case 'D': return Category::DESAYUNO;
        case 'C': return Category::COMIDA;
        case 'E': return Category::CENA;
        case 'N': return Category::NAVIDENO;
        default:  return Category::NONE;
    }
}

void UserInterface::pressEnterToContinue() {
    std::cout << "\nPresiona Enter para continuar...";
    std::string dummy;
    std::getline(std::cin, dummy);
}