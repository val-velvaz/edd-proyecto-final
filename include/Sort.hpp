#pragma once 

#include "List.hpp"
#include "BigInt.hpp"

namespace Sorters {
    bool isSort(const List<BigInt>& list, int (*cmp)(const BigInt&, const BigInt&));

    void swapData(BigInt&, BigInt&);

    int toTop(const BigInt&, const BigInt&);
    int toBotton(const BigInt&, const BigInt&);

    void bubbleSort(List<BigInt>& list, int (*cmp)(const BigInt&, const BigInt&));
    void insertSort(List<BigInt>& list, int (*cmp)(const BigInt&, const BigInt&));
    void selectSort(List<BigInt>& list, int (*cmp)(const BigInt&, const BigInt&));
    void shellSort(List<BigInt>& list, int (*cmp)(const BigInt&, const BigInt&));
    void mergeSort(List<BigInt>& list, int (*cmp)(const BigInt&, const BigInt&));
    void quickSort(List<BigInt>& list, int (*cmp)(const BigInt&, const BigInt&));
}