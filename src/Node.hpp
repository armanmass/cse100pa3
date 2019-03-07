#ifndef HCNODE_HPP
#define HCNODE_HPP

#include <iostream>
#include <vector>
#include "Node.hpp"

using namespace std;

class Node {
public:
    int id;
    int dist;
    Node* prev;
    bool visited;
    std::vector<Node*> neighbors;

    Node(int id,
        int dist,
        int prev,
        bool visited,
        std::vector<Node*> neighbors)
        : id(id), dist(dist), prev(prev), visited(visited), neighbors(neighbors) { }

    ~Node();

};


#endif // HCNODE_HPP
