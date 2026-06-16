#include "Graph.h"
#include "Loader.h"
#include <iostream>

void testLoader() {
  std::cout << "=== Test Loader ===\n";

  AdjencList g(4);
  loader("../test.txt", g);

  std::cout << "Wierzcholki: " << g.numVer() << " (oczekiwane: 4)\n";
  std::cout << "Krawedzie: " << g.numEdge() << " (oczekiwane: 6)\n";

  g.print();
}

int main() {
  testLoader();
  return 0;
}