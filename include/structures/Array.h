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
    capacity = cap + 1; // Array<int> arr(0) problem
    size = 0;
    data = (T *)malloc(sizeof(T) * capacity);
  }

  Array() {
    capacity = 4;
    size = 0;
    data = (T *)malloc(sizeof(T) * capacity);
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
