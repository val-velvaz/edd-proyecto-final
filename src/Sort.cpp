#include "Sort.hpp"
#include <iostream>
#include <vector> 

namespace Sorters {
    bool isSort(const List<BigInt>& list, int (*cmp)(const BigInt&, const BigInt&)) {
        int n = list.last();
        if (n <= 0) return true;

        for (int i = 0; i < n; ++i) {
            if (cmp(list.get(i), list.get(i + 1)) > 0) {
                return false;
            }
        }
        return true;
    }

    void swapData(BigInt& a, BigInt& b) {
        BigInt temp = std::move(a);
        a = std::move(b);
        b = std::move(temp);
    }

    int toTop(const BigInt& a, const BigInt& b) {
        return a.compare(b);
    }

    int toBotton(const BigInt& a, const BigInt& b) {
        return b.compare(a);
    }

    void bubbleSort(List<BigInt>& list, int (*cmp)(const BigInt&, const BigInt&)) {
        int n = list.last();
        if (n <= 0) return;

        bool swapped;
        for (int i = 0; i < n; i++) {
            swapped = false;
            for (int j = 0; j < n - i; j++) {
                if (cmp(list.get(j), list.get(j + 1)) > 0) {
                    swapData(list.get(j), list.get(j + 1));
                    swapped = true;
                }
            }
            if (!swapped) break;
        }
    }

    void insertSort(List<BigInt>& list, int (*cmp)(const BigInt&, const BigInt&)) {
        int n = list.last();
        for (int i = 1; i <= n; ++i) {
            BigInt key = list.get(i);
            int j = i - 1;

            while (j >= 0 && cmp(list.get(j), key) > 0) {
                list.get(j + 1) = list.get(j);
                j--;
            }
            list.get(j + 1) = key;
        }
    }

    void selectSort(List<BigInt>& list, int (*cmp)(const BigInt&, const BigInt&)) {
        int n = list.last();
        for (int i = 0; i < n; ++i) {
            int minIndex = i;
            for (int j = i + 1; j <= n; ++j) {
                if (cmp(list.get(j), list.get(minIndex)) < 0) {
                    minIndex = j;
                }
            }
            if (minIndex != i) {
                swapData(list.get(i), list.get(minIndex));
            }
        }
    }

    void shellSort(List<BigInt>& list, int (*cmp)(const BigInt&, const BigInt&)) {
        int n = list.last() + 1;
        for (int gap = n / 2; gap > 0; gap /= 2) {
            for (int i = gap; i < n; ++i) {
                BigInt temp = list.get(i);
                int j;
                for (j = i; j >= gap && cmp(list.get(j - gap), temp) > 0; j -= gap) {
                    list.get(j) = list.get(j - gap);
                }
                list.get(j) = temp;
            }
        }
    }

    void merge(List<BigInt>& list, int left, int mid, int right, int (*cmp)(const BigInt&, const BigInt&)) {
        int n1 = mid - left + 1;
        int n2 = right - mid;
        std::vector<BigInt> L(n1), R(n2);

        for (int i = 0; i < n1; ++i) L[i] = list.get(left + i);
        for (int j = 0; j < n2; ++j) R[j] = list.get(mid + 1 + j);

        int i = 0, j = 0, k = left;
        while (i < n1 && j < n2) {
            if (cmp(L[i], R[j]) <= 0) {
                list.get(k) = L[i++];
            } else {
                list.get(k) = R[j++];
            }
            k++;
        }
        while (i < n1) list.get(k++) = L[i++];
        while (j < n2) list.get(k++) = R[j++];
    }

    void mergeSortHelper(List<BigInt>& list, int left, int right, int (*cmp)(const BigInt&, const BigInt&)) {
        if (left < right) {
            int mid = left + (right - left) / 2;
            mergeSortHelper(list, left, mid, cmp);
            mergeSortHelper(list, mid + 1, right, cmp);
            merge(list, left, mid, right, cmp);
        }
    }

    void mergeSort(List<BigInt>& list, int (*cmp)(const BigInt&, const BigInt&)) {
        if (list.last() > 0)
            mergeSortHelper(list, 0, list.last(), cmp);
    }

    int partition(List<BigInt>& list, int low, int high, int (*cmp)(const BigInt&, const BigInt&)) {
        BigInt pivot = list.get(high);
        int i = low - 1;

        for (int j = low; j < high; ++j) {
            if (cmp(list.get(j), pivot) <= 0) {
                i++;
                swapData(list.get(i), list.get(j));
            }
        }
        swapData(list.get(i + 1), list.get(high));
        return i + 1;
    }

    void quickSortHelper(List<BigInt>& list, int low, int high, int (*cmp)(const BigInt&, const BigInt&)) {
        if (low < high) {
            int pi = partition(list, low, high, cmp);
            quickSortHelper(list, low, pi - 1, cmp);
            quickSortHelper(list, pi + 1, high, cmp);
        }
    }

    void quickSort(List<BigInt>& list, int (*cmp)(const BigInt&, const BigInt&)) {
        if (list.last() > 0)
            quickSortHelper(list, 0, list.last(), cmp);
    }
}