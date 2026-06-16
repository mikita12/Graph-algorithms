#pragma once

#include "Array.h"

class Graph { // klasa abstrakcyjna
private:
  int vertexCount;
  int edgeCount;

public:
  Graph(int vertices) {
    vertexCount = vertices;
    edgeCount = 0;
  }

  int numVer() { return vertexCount; }

  int numEdge() { return edgeCount; }

  virtual void addEdge(int from, int to, int weight) = 0;
  virtual ~Graph() = default;
};

struct Edge {
  int to;
  int weight;
};

class AdjencList : public Graph { // dziedziczy po graph
private:
  Array<Array<Edge>> nodes;

public:
  AdjencList(int vertices)
      : Graph(vertices), nodes(vertices) { // lista inicjalizacyjna
  }

  ~AdjencList() { delete[] nodes; }

  void addEdge(int from, int to, int weight) override {
    Edge toAdd;
    toAdd.to = to;
    toAdd.weight = weight;
    nodes[from].push_back(toAdd)
  }
};

class IncList : public Graph { // dziedziczy po graph
};
