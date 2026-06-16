

#include "Array.h"

#pragma once

class Graph {//klasa abstrakcyjna
public:
    virtual int numVer() const = 0;
    virtual int numEdg() const = 0;
    virtual void addEdge(int from,int to, int weight) =0;
    virtual ~Graph() = default;
};

class AdjencList : public Graph{ //dziedziczy po graph
public:
    int numVer() const override{

    }
};

class IncList : public Graph{//dziedziczy po graph

};
