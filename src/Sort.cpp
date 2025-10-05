#include "Sort.hpp"
#include <iostream>

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
        BigInt temp = a;
        a = b;
        b = temp;
    }
    
    int toTop(const BigInt& a, const BigInt& b) {
        if (a < b) return -1;
        if (a > b) return 1;
        return 0;
    }
    
    int toBotton(const BigInt& a, const BigInt& b) {
        if (a > b) return -1;
        if (a < b) return 1;
        return 0;
    }
    
void bubbleSort(List<BigInt>& list, int (*cmp)(const BigInt&, const BigInt&)) {
        int n = list.last();
        if (n <= 0) return;  

        bool flag;
        do {
            flag = false;
            for (int j = 0; j < n; ++j) {
                BigInt a = list.get(j);
                BigInt b = list.get(j + 1);

                if (cmp(a, b) > 0) {
                    swapData(a, b);

                    list.del(j);
                    list.add(j, a);
                    list.del(j + 1);
                    list.add(j + 1, b);

                    flag = true;
                }
            }
            n--;
        } while (flag);
    }
    
    
    void insertSort(List<BigInt>& list, int (*cmp)(const BigInt&, const BigInt&)) {
        int n = list.last();
        for (int i = 1; i <= n; ++i) {
            BigInt key = list.get(i);
            int j = i - 1;

            while (j >= 0 && cmp(list.get(j), key) > 0) {
                BigInt temp = list.get(j);
                list.del(j + 1);
                list.add(j + 1, temp);
                j--;
            }
            list.del(j + 1);
            list.add(j + 1, key);
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
                BigInt a = list.get(i);
                BigInt b = list.get(minIndex);
                BigInt temp = std::move(a);
                a = std::move(b);
                b = std::move(temp);
                list.del(i);
                list.add(i, a);
                list.del(minIndex);
                list.add(minIndex, b);
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
                    BigInt moved = list.get(j - gap);
                    list.del(j);
                    list.add(j, moved);
                }
                list.del(j);
                list.add(j, temp);
            }
        }
    }

    
    void merge(List<BigInt>& list, int left, int mid, int right, int (*cmp)(const BigInt&, const BigInt&)) {
        int n1 = mid - left + 1;
        int n2 = right - mid;
        std::vector<BigInt> L, R;
        for (int i = 0; i < n1; ++i) L.push_back(list.get(left + i));
        for (int j = 0; j < n2; ++j) R.push_back(list.get(mid + 1 + j));
        int i = 0, j = 0, k = left;
        while (i < n1 && j < n2) {
            if (cmp(L[i], R[j]) <= 0) {
                list.del(k);
                list.add(k, L[i++]);
            } else {
                list.del(k);
                list.add(k, R[j++]);
            }
            k++;
        }
        while (i < n1) {
            list.del(k);
            list.add(k, L[i++]);
            k++;
        }
        while (j < n2) {
            list.del(k);
            list.add(k, R[j++]);
            k++;
        }
    }

    void mergeSortHelper(List<BigInt>& list, int left, int right, int (*cmp)(const BigInt&, const BigInt&)) {
        if (left < right) {
            int mid = (left + right) / 2;
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