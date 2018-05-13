#include <iostream>
//#include <cmath>
#include "DynamicArray.h"

DynamicArray::DynamicArray(): size(100), sizeCapacity(20) {
    init(0);
}

DynamicArray::DynamicArray(int size): size(size), sizeCapacity(20) {
    init(0);
}

DynamicArray::DynamicArray(int size, int n): size(size), sizeCapacity(20) {
    init(n);
}

DynamicArray::DynamicArray(int size, int n, int sizeCapacity): size(size), sizeCapacity(sizeCapacity) {
    init(n);
}

DynamicArray::DynamicArray(const DynamicArray &other) {
    size = other.size;
    sizeCapacity = other.sizeCapacity;
    init(0);
    for (int i = 0; i < size; i++) mas[i] = other.mas[i];
}

DynamicArray::DynamicArray(DynamicArray &&other) {
    mas = other.mas;
    size = other.size;
    sizeCapacity = other.sizeCapacity;
    other.size = 0;
    other.sizeCapacity = 0;
}

DynamicArray::~DynamicArray() {
    clear();
}

void DynamicArray::init(int n) {
    mas = new int[size + sizeCapacity];
    for (int i = 0; i < size; i++) mas[i] = n;
}

void DynamicArray::clear() {
    if (size + sizeCapacity > 0) delete[] mas;
    size = 0;
}

int DynamicArray::getSize() {
    return size;
}

int &DynamicArray::operator[](int i) {
    if (size <= i) throw 1;
    return mas[i];
}

void DynamicArray::resize(int sizeNew) {
    if (sizeNew <= size + sizeCapacity) {
        int sizeChange = sizeNew - size;
        for (int i = size; i < size + sizeChange; i++) mas[i] = 0;
        size += sizeChange;
        sizeCapacity -= sizeChange;
    } else {
        int *masOld = mas;
        int sizeOld = size;
        size = sizeNew;
        init(0);
        for (int i = 0; i < fmin(sizeOld, sizeNew); i++) mas[i] = masOld[i];
        delete[] masOld;
    }
}

DynamicArray &DynamicArray::operator=(const DynamicArray &other) {
    // kopiruem
    clear();
    size = other.size;
    sizeCapacity = other.sizeCapacity;
    init(0);
    for (int i = 0; i < size; i++) mas[i] = other.mas[i];
    return *this;
}

DynamicArray &DynamicArray::operator=(DynamicArray &&other) {
    // peremeshenie
    clear();
    mas = other.mas;
    size = other.size;
    sizeCapacity = other.sizeCapacity;
    other.size = 0;
    other.sizeCapacity = 0;
    return *this;
}


bool DynamicArray::operator==(const DynamicArray &other) const {
    if (size != other.size) throw 2;
    for (int i = 0; i < size; i++) {
        if (mas[i] != other.mas[i]) return false;
    }
    return true;
}

bool DynamicArray::operator!=(const DynamicArray &other) const {
    return !(other == *this);
}

bool DynamicArray::operator<(const DynamicArray &other) const {
    if (mas < other.mas)
        return true;
    if (other.mas < mas)
        return false;
    return size < other.size;
}

bool DynamicArray::operator>(const DynamicArray &other) const {
    return other < *this;
}

bool DynamicArray::operator<=(const DynamicArray &other) const {
    return !(other < *this);
}

bool DynamicArray::operator>=(const DynamicArray &other) const {
    return !(*this < other);
}

void DynamicArray::operator+(const DynamicArray &other) {
    int sizeMem = size;
    resize(size + other.size);
    for (int i = 0; i < other.size; i++) mas[i + sizeMem] = other.mas[i];
}

std::ostream &operator<<(std::ostream &os, const DynamicArray &array) {
    os << "size: " << array.size;
    os << ", capacity: " << array.sizeCapacity;
    for (int i = 0; i < array.size; i++) os << (i == 0 ? " value=" : ", ") << array.mas[i];
    return os;
}

std::istream &operator>>(std::istream &is, const DynamicArray &array) {
    std::cout << "set " << array.size << " values:\n";
    for (int i = 0; i < array.size; i++) {
        std::cout << "mas[" << i << "] > ";
        is >> array.mas[i];
    }
    return is;
}

int DynamicArray::capacity() {
    return sizeCapacity;
}

void DynamicArray::pushBack(int x) {
    resize(size + 1);
    mas[size - 1] = x;
}

int DynamicArray::popBack() {
    int x = mas[size - 1];
    resize(size - 1);
    return x;
}
