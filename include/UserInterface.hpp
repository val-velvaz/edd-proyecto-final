#pragma once

#include "List.hpp"
#include "BigInt.hpp"

class UserInterface {
public:
    void run();

private:
    void mainMenu();
    void showMenu();
    void modifyMenu();
    void cleanMenu();

    void enterToContinue();
    void cleanWindow();
};