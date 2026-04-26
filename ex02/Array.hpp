#ifndef ARRAY_HPP
#define ARRAY_HPP

#include <exception>
#include <cstddef>

template <typename T>
class Array {
private:
    T* elements;
    unsigned int    _size;

public:
    Array() : elements(NULL), _size(0) {}

    // new T[n]() の末尾のカッコ()により、プリミティブ型もゼロ初期化（デフォルト初期化）される
    Array(unsigned int n) : elements(new T[n]()), _size(n) {}

    Array(const Array& other) : elements(NULL), _size(0) {
        *this = other;
    }

    ~Array() {
        delete[] elements;
    }

    Array& operator=(const Array& other) {
        if (this != &other) {
            delete[] elements;
            _size = other._size;
            elements = new T[_size]();
            for (unsigned int i = 0; i < _size; i++) {
                elements[i] = other.elements[i];
            }
        }
        return *this;
    }

    T& operator[](unsigned int index) {
        if (index >= _size) {
            throw OutOfBoundsException();
        }
        return elements[index];
    }

    const T& operator[](unsigned int index) const {
        if (index >= _size) {
            throw OutOfBoundsException();
        }
        return elements[index];
    }

    unsigned int size() const {
        return _size;
    }

    class OutOfBoundsException : public std::exception {
    public:
        virtual const char* what() const throw() {
            return "Array index out of bounds";
        }
    };
};

#endif
