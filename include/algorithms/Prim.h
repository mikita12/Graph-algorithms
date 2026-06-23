#pragma once
#include "Graph.h"
#include "Queue.h"
#include <climits>
#include <iostream>

struct MstResult {
    int* parent;   // parent[v] = poprzednik v w MST
    int* key;      // key[v] = waga krawedzi laczacej v z MST
    int totalCost; // suma wag krawedzi MST
    int vertices;

    MstResult(int v) {
        vertices = v;
        parent = new int[v];
        key = new int[v];
        totalCost = 0;
    }

    ~MstResult() {
        delete[] parent;
        delete[] key;
    }

    void print() const {
        std::cout << "MST (Prim):\n";
        for (int v = 1; v < vertices; v++) {
            std::cout << parent[v] << " -> " << v 
                      << " (waga: " << key[v] << ")\n";
        }
        std::cout << "Koszt calkowity: " << totalCost << "\n";
    }
};

template<typename G>
MstResult prim(G& graph, int start) {
    int V = graph.numVer();
    MstResult result(V);

    bool* inMST = new bool[V];

    // inicjalizacja
    for (int i = 0; i < V; i++) {
        result.key[i] = INT_MAX;
        result.parent[i] = -1;
        inMST[i] = false;
    }
    result.key[start] = 0;

    MinHeap<HeapNode> heap;
    heap.push({0, start});

    while (!heap.isEmpty()) {
        HeapNode current = heap.pop();
        int u = current.vertex;

        if (inMST[u]) continue;  // juz w MST - pomijamy
        inMST[u] = true;

        if (u != start) {
            result.totalCost += result.key[u];
        }

        auto neighbors = graph.getNeighbors(u);
        for (int i = 0; i < neighbors.get_size(); i++) {
            int v = neighbors[i].to;
            int w = neighbors[i].weight;

            // jesli v nie jest w MST i waga jest mniejsza niz aktualna
            if (!inMST[v] && w < result.key[v]) {
                result.key[v] = w;
                result.parent[v] = u;
                heap.push({w, v});
            }
        }
    }

    delete[] inMST;
    return result;
}