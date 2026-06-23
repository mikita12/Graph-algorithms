#pragma once
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

template <typename T> class Array {
private:
  T *data;
  int size;
  int capacity;

public:
  Array(int cap) {
    capacity = cap + 1;
    size =
        capacity; // tymczasowo - zeby placement new wiedzial ile inicjalizowac
    data = (T *)malloc(sizeof(T) * capacity);
    for (int i = 0; i < capacity; i++) {
      new (&data[i]) T(); // wywolaj domyslny konstruktor na kazdym elemencie
    }
    size = 0; // przywroc - tablica jest logicznie pusta
  }

  Array() {
    capacity = 4;
    data = (T *)malloc(sizeof(T) * capacity);
    for (int i = 0; i < capacity; i++) {
      new (&data[i]) T();
    }
    size = 0;
  }

  // konstruktor kopiujacy
  Array(const Array &other) {
    capacity = other.capacity;
    size = other.size;
    data = (T *)malloc(sizeof(T) * capacity);
    for (int i = 0; i < size; i++) {
      new (&data[i]) T(other.data[i]);
    }
  }

  // operator przypisania
  Array &operator=(const Array &other) {
    if (this == &other)
      return *this;
    for (int i = 0; i < size; i++) {
      data[i].~T();
    }
    free(data);
    capacity = other.capacity;
    size = other.size;
    data = (T *)malloc(sizeof(T) * capacity);
    for (int i = 0; i < size; i++) {
      new (&data[i]) T(other.data[i]);
    }
    return *this;
  }

  ~Array() {
    for (int i = 0; i < size; i++) {
      data[i].~T();
    }
    free(data);
  }

  void push_back(const T &value) {
    if (size >= capacity) {
      int oldCapacity = capacity;
      capacity *= 2;
      T *temp = (T *)malloc(sizeof(T) * capacity);
      for (int i = 0; i < size; i++) {
        new (&temp[i]) T(data[i]);
        data[i].~T();
      }
      // inicjalizuj nowe miejsca
      for (int i = oldCapacity; i < capacity; i++) {
        new (&temp[i]) T();
      }
      free(data);
      data = temp;
    }
    new (&data[size++]) T(value);
  }

  void pop_back() {
    if (size > 0) {
      data[--size].~T(); // wywolaj destruktor
    }
  }

  int get_size() const { return size; }

  T &operator[](int index) { return data[index]; }
  const T &operator[](int index) const { return data[index]; }

  T *get_data() { return data; }
};