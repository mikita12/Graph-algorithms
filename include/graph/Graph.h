#pragma once

#include "Array.h"

class Graph { // klasa abstrakcyjna
protected:    // dziedziczace musza miec dostep
  int vertexCount;
  int edgeCount;

public:
  Graph(int vertices) {
    vertexCount = vertices;
    edgeCount = 0;
  }

  int numVer() const { return vertexCount; }

  int numEdge() const { return edgeCount; }

  virtual void addEdge(int from, int to, int weight) = 0;
  virtual ~Graph() = default;
};

struct Edge {
  int to;
  int weight;
};

struct HeapNode {
    int cost;
    int vertex;
    bool operator<(const HeapNode& other) const {
        return cost < other.cost;
    }
};

class AdjencList : public Graph { // dziedziczy po graph
private:
  Array<Array<Edge>> nodes;

public:
  AdjencList(int vertices)
      : Graph(vertices), nodes(vertices) { // lista inicjalizacyjna
  }

  ~AdjencList() {}

  const Array<Edge>& getNeighbors(int v) const {
    return nodes[v];
  }

  void addEdge(int from, int to, int weight) override {
    Edge toAdd;
    toAdd.to = to;
    toAdd.weight = weight;
    nodes[from].push_back(toAdd);
    edgeCount++;
  }

  void print() const {
    for (int v = 0; v < vertexCount; v++) {
        std::cout << "Wierzcholek " << v << ": ";
        for (int i = 0; i < nodes[v].get_size(); i++) {
            std::cout << "-> " << nodes[v][i].to 
                      << "(w:" << nodes[v][i].weight << ") ";
        }
        std::cout << "\n";
    }
  }
};

class IncList : public Graph { // dziedziczy po graph
};
