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
      capacity *= 2;
      T *temp = (T *)malloc(sizeof(T) * capacity);
      for (int i = 0; i < size; i++) {
        temp[i] = data[i]; // kopiuje przez operator= a nie bitowo
      }
      free(data);
      data = temp;
    }
    data[size++] = value;
  }

  void pop_back() {
    if (size > 0) size--;
  }

  int get_size() const { return size; }

  T &operator[](int index) { return data[index]; }

  const T &operator[](int index) const { return data[index]; }

  T *get_data() { return data; }
};
