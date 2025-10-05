#pragma once

#include "List.hpp"
#include "BigInt.hpp"

class UserInterface {
public:
    void run();

private:
    void mainMenu();
    void testSortingAlgorithms();
    void generateRandomList(List<BigInt>& list, int size, int numDigits);
};