#include "Prim.h"
#include "Loader.h"

void testPrim() {
  std::cout << "=== Test Prim ===\n";

  AdjencList g(5);
  loaderUndirected("../test_mst.txt", g);
  g.print();

  std::cout << "\n";
  MstResult result = prim(g, 0);
  result.print();
}

int main() {
  testPrim();
  return 0;
}