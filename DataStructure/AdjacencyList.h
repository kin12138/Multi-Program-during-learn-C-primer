//
// Created by libin on 2025/6/24.
//

#ifndef DATASTRUCTURE_ADJACENCYLIST_H
#define DATASTRUCTURE_ADJACENCYLIST_H
#include <array>

struct Vertex{
    int v_;
};

class ArcNode;

struct ArcNode {
    Vertex v_;
    ArcNode * nextEdge_;
};

#endif //DATASTRUCTURE_ADJACENCYLIST_H
