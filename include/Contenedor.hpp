#pragma once

#include <string>

#include "BigInt.hpp"

template <class T>
class List {
private:
    T data[3000];
    size_t last;

    bool isValidPos(const size_t&) const;
    void copyAll(const List<T>&);

public:
    List();
    List(const List&);
    List(List&&) noexcept;

    void init();
    bool empty() cont;
    bool full() const;

    void add(const size_t&, const T&);
    void del(const size_t&);

    T _return(const size_t&) const;

    size_t first() const;
    size_t last() const;

    void cancel();
    std::string toString() const;
};