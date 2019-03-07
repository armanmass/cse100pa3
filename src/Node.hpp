#ifndef NODE_HPP
#define NODE_HPP

#include <iostream>
#include <vector>

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
        Node* prev,
        bool visited,
        std::vector<Node*> neighbors)
        : id(id), dist(dist), prev(prev), visited(visited), neighbors(neighbors) { }

    ~Node();

};

#endif // NODE_HPP