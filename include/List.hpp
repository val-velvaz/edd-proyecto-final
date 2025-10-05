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
    bool empty() const;
    bool full() const;

    void add(const size_t&, const T&);
    void del(const size_t&);

    T _return(const size_t&) const;

    size_t first() const;
    size_t last() const;

    void cancel();
    std::string toString() const;
};

template<class T>
bool List<T>::isValidPos(const size_t&) const {
    
}

template<class T>
List<T>::List() {
    
}

template<class T>
List<T>::List(const List&) {
    
}

template<class T>
List<T>::List(List&&) noexcept {
    
}

template<class T>
void List<T>::init() {
    
}

template<class T>
bool List<T>::empty() const {
    
}

template<class T>
bool List<T>::full() const {
    
}

template<class T>
void List<T>::add(const size_t&, const T&) {
    
}

template<class T>
void List<T>::del(const size_t&) {
    
}

template<class T>
T List<T>::_return(const size_t&) const {
    
}

template<class T>
size_t List<T>::first() const {
    
}

template<class T>
size_t List<T>::last() const {
    
}

template<class T>
void List<T>::cancel() {
    
}

template<class T>
std::string List<T>::toString() const {
    
}


