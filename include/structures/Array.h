#include <iostream>
#include <stdio.h>
#include <stdlib.h>

#pragma once

template <typename T> class Array {
private:
  T *data;
  int size;
  int capacity;

public:
  Array(int cap) {
    capacity = cap + 1; // Array<int> arr(0) problem
    size = 0;
    data = (T *)malloc(sizeof(T) * capacity);
  }

  Array(const Array<T> &other) {
    capacity = other.capacity;
    size = other.size;
    data = (T *)malloc(sizeof(T) * capacity);
    for (int i = 0; i < size; i++)
      data[i] = other.data[i];
  }

  Array(Array<T> &&other) noexcept
      : data(other.data), size(other.size), capacity(other.capacity) {
    other.data = nullptr;
    other.size = 0;
    other.capacity = 0;
  }

  Array<T> &operator=(const Array<T> &other) {
    if (this != &other) {
      free(data);
      capacity = other.capacity;
      size = other.size;
      data = (T *)malloc(sizeof(T) * capacity);
      for (int i = 0; i < size; i++)
        data[i] = other.data[i];
    }
    return *this;
  }

  Array<T> &operator=(Array<T> &&other) noexcept {
    if (this != &other) {
      free(data);
      data = other.data;
      size = other.size;
      capacity = other.capacity;
      other.data = nullptr;
      other.size = 0;
      other.capacity = 0;
    }
    return *this;
  }

  ~Array() { free(data); }

  void push_back(const T &value) {
    if (size >= capacity) {
      capacity *= 2; // rip pamiec?
      T *temp = (T *)realloc(data, capacity * sizeof(T));
      if (temp != NULL) {
        data = temp;
      } else {
        std::cout << "realloc failed\n"; // nie wiem tbh, not my problem
        return;
      }
    }
    data[size++] = value;
  }

  int get_size() const { return size; }

  T &operator[](int index) { return data[index]; }

  const T &operator[](int index) const { return data[index]; }

  T *get_data() { return data; }
};