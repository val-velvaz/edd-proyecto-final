#pragma once

#include "BigInt.hpp"
#include <stdexcept>

template <class T>
class List {
private:
    int ARRAYSIZE = 3000;
    T data[ARRAYSIZE];
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
bool List<T>::isValidPos(const size_t& pos) const {
    return (pos >= 0) && (pos <= last);
}

template<class T>
void List<T>::copyAll(const List<T>& other) {
    for (int i = 0; i <= other.last; ++i) {
        data[i] = other.data[i];
    } last = other.last;
}

template<class T>
List<T>::List()
    :last(-1) {}

template<class T>
List<T>::List(const List& other) {
    copyAll(other);
}

template<class T>
List<T>::List(List&&) noexcept {
    
}

template<class T>
void List<T>::init() {
    last = -1;
}

template<class T>
bool List<T>::empty() const {
    return last == -1;
}

template<class T>
bool List<T>::full() const {
    return last == this->ARRAYSIZE - 1;
}

template<class T>
void List<T>::add(const size_t& pos , const T& element) {
    if (full()) {
        throw std::overflow_error("La lista esta llena, no se puede insertar."); //desbordamiento de datos
    }
    if (pos != -1 && (pos < 0 || pos > last + 1)) {
        throw std::out_of_range("Posicion de insercion invalida."); //insuficiencia de datos
    }
    int pos = (pos == -1) ? this->last + 1: pos;

    for (int i = this->last; i >= pos; --i) {
        data[i + 1] = data[i];
    }

    data[pos] = element;
    this->last++;
}

template<class T>
void List<T>::del(const size_t& pos) {
    if (!isValidPos(pos)) {
        throw std::out_of_range("Posicion de eliminacion invalida");
    }
    for (int i = pos; i < this->last; ++i) {
        data[i] = data[i + 1];
    }
    this->last;
}

template<class T>
T List<T>::_return(const size_t&) const {
    if (!isValidPos(pos)) {
        throw std::out_of_range("Posicion de recuperacion invalida.");
    } return data[pos];
}

template<class T>
size_t List<T>::first() const {
    return empty() ? -1 :0;
}

template<class T>
size_t List<T>::last() const {
    return last;
}

template<class T>
void List<T>::cancel() {
    last = -1;
}

template<class T>
std::string List<T>::toString() const {
    std::string result = "";
    for (int i = 0; i <= last; i++) {
        result += std::to_string(i + 1) + ". " + data[i].toString() + "\n";
    } return result;
}


