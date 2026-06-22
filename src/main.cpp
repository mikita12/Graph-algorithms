#include "Graph.h"
#include "Loader.h"
#include "Dijkstra.h"
#include <iostream>

void testDijkstra() {
    std::cout << "=== Test Dijkstra ===\n";

    AdjencList g(4);
    loader("../test.txt", g);
    g.print();

    std::cout << "\nNajkrotsza sciezka 0 -> 3:\n";
    SpResult result = dijkstra(g, 0, 3);
    result.print(0, 3);
}

int main() {
    testDijkstra();
    return 0;
}