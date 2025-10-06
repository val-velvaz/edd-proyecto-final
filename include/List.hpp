#pragma once
#include <stdexcept>
#include <string>

template <class T>
class List {
private:
    static const int ARRAYSIZE = 3000;
    T data[ARRAYSIZE];
    int lastPos;

    bool isValidPos(int pos) const;
    void copyAll(const List<T>&);

public:
    List();
    List(const List&);
    List(List&&) noexcept;

    List<T>& operator=(const List<T>& other);

    void init();
    bool empty() const;
    bool full() const;

    void add(int pos, const T& element);
    void del(int pos);

    T get(int pos) const;
    T& get(int pos);

    int first() const;
    int last() const;

    void cancel();
    std::string toString() const;
};

template<class T>
bool List<T>::isValidPos(int pos) const {
    return pos >= 0 && pos <= lastPos;
}

template<class T>
void List<T>::copyAll(const List<T>& other) {
    for (int i = 0; i <= other.lastPos; ++i) {
        data[i] = other.data[i];
    }
    lastPos = other.lastPos;
}

template<class T>
List<T>::List() : lastPos(-1) {}

template<class T>
List<T>::List(const List& other) {
    copyAll(other);
}

template<class T>
List<T>::List(List&& other) noexcept : lastPos(other.lastPos) {
    for (int i = 0; i <= other.lastPos; ++i) {
        data[i] = std::move(other.data[i]);
    }
    other.lastPos = -1;
}

template<class T>
List<T>& List<T>::operator=(const List<T>& other) {
    if (this != &other) {
        copyAll(other);
    }
    return *this;
}

template<class T>
void List<T>::init() {
    lastPos = -1;
}

template<class T>
bool List<T>::empty() const {
    return lastPos == -1;
}

template<class T>
bool List<T>::full() const {
    return lastPos == ARRAYSIZE - 1;
}

template<class T>
void List<T>::add(int pos, const T& element) {
    if (full())
        throw std::overflow_error("Lista llena.");
    if (pos < 0 || pos > lastPos + 1) // Corregido para permitir añadir al final
        throw std::out_of_range("Posicion invalida.");

    for (int i = lastPos; i >= pos; --i)
        data[i + 1] = data[i];

    data[pos] = element;
    lastPos++;
}

template<class T>
void List<T>::del(int pos) {
    if (!isValidPos(pos))
        throw std::out_of_range("Posicion invalida.");

    for (int i = pos; i < lastPos; ++i)
        data[i] = data[i + 1];

    lastPos--;
}

template<class T>
T List<T>::get(int pos) const {
    if (!isValidPos(pos))
        throw std::out_of_range("Posicion invalida.");
    return data[pos];
}

template<class T>
T& List<T>::get(int pos) {
    if (!isValidPos(pos))
        throw std::out_of_range("Posicion invalida.");
    return data[pos];
}

template<class T>
int List<T>::first() const {
    return empty() ? -1 : 0;
}

template<class T>
int List<T>::last() const {
    return lastPos;
}

template<class T>
void List<T>::cancel() {
    lastPos = -1;
}

template<class T>
std::string List<T>::toString() const {
    std::string result;
    for (int i = 0; i <= lastPos; ++i) {
        result += data[i].toString() + "\n";
    }
    return result;
}