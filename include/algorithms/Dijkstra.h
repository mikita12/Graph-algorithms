#pragma once
#include "Graph.h"
#include "Queue.h"
#include <climits>

struct SpResult {
    int* dist;   // dist[v] = koszt najkrotszej sciezki do v
    int* prev;   // prev[v] = poprzednik v na najkrotszej sciezce
    int vertices;

    SpResult(int v) {
        vertices = v;
        dist = new int[v];
        prev = new int[v];
    }

    ~SpResult() {
        delete[] dist;
        delete[] prev;
    }

    void print(int start, int end) const {
        if (dist[end] == INT_MAX) {
            std::cout << "Brak sciezki z " << start << " do " << end << "\n";
            return;
        }
        std::cout << "Koszt: " << dist[end] << "\n";
        std::cout << "Sciezka: ";

        // odtworz sciezke przez prev[]
        int* path = new int[vertices];
        int pathSize = 0;
        int current = end;
        while (current != -1) {
            path[pathSize++] = current;
            current = prev[current];
        }
        // wypisz od konca (od start do end)
        for (int i = pathSize - 1; i >= 0; i--) {
            std::cout << path[i];
            if (i > 0) std::cout << " -> ";
        }
        std::cout << "\n";
        delete[] path;
    }
};

template<typename G>
SpResult dijkstra(G& graph, int start, int end) {
    int V = graph.numVer();
    SpResult result(V);

    // inicjalizacja - wszystkie odleglosci nieskonczone
    for (int i = 0; i < V; i++) {
        result.dist[i] = INT_MAX;
        result.prev[i] = -1;
    }
    result.dist[start] = 0;

    MinHeap<HeapNode> heap;
    heap.push({0, start});

    while (!heap.isEmpty()) {
        HeapNode current = heap.pop();
        int u = current.vertex;
        int uCost = current.cost;

        // jesli wyjelismy przestarzaly wpis - pomijamy
        if (uCost > result.dist[u]) continue;

        // jesli dotarlismy do celu - koniec
        if (u == end) break;

        // przegladamy sasiadow
        auto neighbors = graph.getNeighbors(u);
        for (int i = 0; i < neighbors.get_size(); i++) {
            int v = neighbors[i].to;
            int w = neighbors[i].weight;

            if (result.dist[u] + w < result.dist[v]) {
                result.dist[v] = result.dist[u] + w;
                result.prev[v] = u;
                heap.push({result.dist[v], v});
            }
        }
    }

    return result;
}