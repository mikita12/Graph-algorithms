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

class IncidenceMatrix : public Graph {
private:
    int** matrix;  // matrix[v][e] = +waga jesli v jest poczatkiem, -waga jesli koncem, 0 jesli nie nalezy
    int maxEdges;  // maksymalna liczba krawedzi (znana z gory)

public:
    IncidenceMatrix(int vertices, int edges)
        : Graph(vertices), maxEdges(edges) {
        // alokuj tablice 2D: V wierszy, E kolumn
        matrix = new int*[vertices];
        for (int i = 0; i < vertices; i++) {
            matrix[i] = new int[edges];
            for (int j = 0; j < edges; j++) {
                matrix[i][j] = 0;  // wypelnij zerami
            }
        }
    }

    ~IncidenceMatrix() {
        for (int i = 0; i < vertexCount; i++) {
            delete[] matrix[i];
        }
        delete[] matrix;
    }

    void addEdge(int from, int to, int weight) override {
        int e = edgeCount;  // indeks nowej krawedzi = aktualna liczba krawedzi
        matrix[from][e] = +weight;  // from jest poczatkiem
        matrix[to][e]   = -weight;  // to jest koncem
        edgeCount++;
    }

    // getNeighbors - skanuj kolumny, znajdz krawedzie wychodzace z v
    Array<Edge> getNeighbors(int v) const {
        Array<Edge> result;
        for (int e = 0; e < edgeCount; e++) {
            if (matrix[v][e] > 0) {  // v jest poczatkiem tej krawedzi
                // znajdz koniec - szukaj wiersza z ujemna wartoscia w tej kolumnie
                for (int u = 0; u < vertexCount; u++) {
                    if (matrix[u][e] < 0) {
                        Edge edge;
                        edge.to = u;
                        edge.weight = matrix[v][e];  // waga to wartosc dodatnia
                        result.push_back(edge);
                        break;
                    }
                }
            }
        }
        return result;
    }

    void print() const {
        std::cout << "Macierz incydencji [V x E]:\n";
        std::cout << "     ";
        for (int e = 0; e < edgeCount; e++) {
            std::cout << "e" << e << "   ";
        }
        std::cout << "\n";
        for (int v = 0; v < vertexCount; v++) {
            std::cout << "v" << v << " [ ";
            for (int e = 0; e < edgeCount; e++) {
                std::cout << matrix[v][e] << "   ";
            }
            std::cout << "]\n";
        }
    }
};
