#pragma once
#include "Array.h"

template<typename T>
class MinHeap {
private:
    Array<T> data;

    void bubbleUp(int i) {
        while (i > 0) {
            int parent = (i - 1) / 2;
            if (data[i] < data[parent]) {
                // zamiana
                T temp = data[i];
                data[i] = data[parent];
                data[parent] = temp;
                i = parent;
            } else {
                break;
            }
        }
    }

    void bubbleDown(int i) {
        int n = data.get_size();
        while (true) {
            int left  = 2 * i + 1;
            int right = 2 * i + 2;
            int smallest = i;

            if (left < n && data[left] < data[smallest]) {
                smallest = left;
            }
            if (right < n && data[right] < data[smallest]) {
                smallest = right;
            }

            if (smallest == i) break;  // dzieci sa wieksze - koniec

            T temp = data[i];
            data[i] = data[smallest];
            data[smallest] = temp;
            i = smallest;
        }
    }

public:
    MinHeap() : data(16) {}

    void push(const T& value) {
        data.push_back(value);
        bubbleUp(data.get_size() - 1);
    }

    T pop() {
        T top = data[0];
        // ostatni element na gore
        data[0] = data[data.get_size() - 1];
        // zmniejsz rozmiar - potrzebujesz metody w Array
        data.pop_back();
        bubbleDown(0);
        return top;
    }

    const T& top() const {
        return data[0];
    }

    bool isEmpty() const {
        return data.get_size() == 0;
    }
};