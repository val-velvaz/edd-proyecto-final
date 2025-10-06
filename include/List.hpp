#pragma once
#include <stdexcept>
#include <string>
#include <utility> 

template <class T>
class List {
private:
    T* data;           
    int lastPos;
    int capacity;     

    bool isValidPos(int pos) const;
    void copyAll(const List<T>&);

public:
    List();
    ~List();
    List(const List&);
    List(List&&) noexcept;
    List<T>& operator=(const List<T>&);
    List<T>& operator=(List<T>&&) noexcept;

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
    delete[] data;
    lastPos = other.lastPos;
    capacity = other.capacity;
    data = new T[capacity];
    for (int i = 0; i <= other.lastPos; ++i) {
        data[i] = other.data[i];
    }
}

template<class T>
List<T>::List() : lastPos(-1), capacity(3000) {
    data = new T[capacity];
}

template<class T>
List<T>::~List() {
    delete[] data;
}

template<class T>
List<T>::List(const List& other) {
    data = nullptr; 
    copyAll(other);
}

template <class T>
List<T>::List(List&& other) noexcept : data(other.data), lastPos(other.lastPos), capacity(other.capacity) {
    other.data = nullptr;
    other.lastPos = -1;
    other.capacity = 0;
}

template<class T>
List<T>& List<T>::operator=(const List<T>& other) {
    if (this != &other) {
        copyAll(other);
    }
    return *this;
}

template <class T>
List<T>& List<T>::operator=(List<T>&& other) noexcept {
    if (this != &other) {
        delete[] data; 
        data = other.data;
        lastPos = other.lastPos;
        capacity = other.capacity;
        
        other.data = nullptr;
        other.lastPos = -1;
        other.capacity = 0;
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
    return lastPos == capacity - 1; 
}

template<class T>
void List<T>::add(int pos, const T& element) {
    if (full())
        throw std::overflow_error("Lista llena.");
    if (pos < 0 || pos > lastPos + 1) 
        throw std::out_of_range("Posicion invalida para agregar.");

    for (int i = lastPos; i >= pos; --i)
        data[i + 1] = data[i];

    data[pos] = element;
    lastPos++;
}

template<class T>
void List<T>::del(int pos) {
    if (!isValidPos(pos))
        throw std::out_of_range("Posicion invalida para eliminar.");

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
        result += std::to_string(i + 1) + ". " + data[i].toString() + "\n";
    } return result;
}