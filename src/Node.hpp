/*
Arman Massoudian
3/7/2019
Node Header
PA3
*/
#ifndef NODE_HPP
#define NODE_HPP

#include <iostream>
#include <vector>

using namespace std;

class Node {
public:
    int id;
    int core;
    int degree;
    Node* prev;
    bool visited;
    std::vector<Node*> neighbors;

    Node(int id,
        int core,
        int degree,
        Node* prev,
        bool visited,
        std::vector<Node*> neighbors)
        : id(id), core(core), degree(degree), prev(prev), visited(visited), neighbors(neighbors) { }

    ~Node() { }

    bool operator<(const Node& other) {
        if(other.degree < this->degree)
             return true;

        if(other.degree == this->degree) {
           if(this->id < other.id)
              return true;
        }    
        return false;
    }
};

#endif // NODE_HPP