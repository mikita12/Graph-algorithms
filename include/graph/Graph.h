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

class AdjencList : public Graph { // dziedziczy po graph
private:
  Array<Array<Edge>> nodes;

public:
  AdjencList(int vertices)
      : Graph(vertices), nodes(vertices) { // lista inicjalizacyjna
  }

  ~AdjencList() {}

  void addEdge(int from, int to, int weight) override {
    Edge toAdd;
    toAdd.to = to;
    toAdd.weight = weight;
    nodes[from].push_back(toAdd);
    edgeCount++;
  }
};

class IncList : public Graph { // dziedziczy po graph
};
