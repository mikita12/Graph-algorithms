#include "Loader.h"
#include <fstream>
#include <iostream>

void loader(const std::string& filename, Graph& graph){

    std::ifstream file(filename);

    if(!file.is_open()){
        std::cerr<<"nie mozna otworzuc pliku \n";
        return;
    }

    int V,E;
    file >> V >> E;
    int from, to, weight;
    int loaded = 0;
    while(file >> from >> to >> weight){
        graph.addEdge(from, to, weight);
        loaded++;
    }
}