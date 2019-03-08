#include "Graph.hpp"
#include "Node.hpp"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <limits>
#include <set>
#include <sstream>
#include <string>
#include <utility>
#include <unordered_map>
#include <queue>

using namespace std;

Graph::Graph() {}

Graph::~Graph() {
  for (auto itr : nodeMap)
    delete itr.second;
}

/* Add a node to the graph representing person with id idNumber and add a connection between two nodes in the graph. */
void Graph::addNode(int idNumber, int friendID){
  vector<Node*> newNeighbor;
  Node* idNode;
  Node* friendNode;

  if(nodeMap.find(idNumber) != nodeMap.end()){
    if(nodeMap.find(friendID) != nodeMap.end()){
      nodeMap.find(idNumber)->second->neighbors.push_back(nodeMap.find(friendID)->second);
      nodeMap.find(friendID)->second->neighbors.push_back(nodeMap.find(idNumber)->second);
    }else{
      friendNode = new Node(friendID, 0, false, newNeighbor);
      nodeMap.insert({friendID, friendNode});
      nodeMap.find(idNumber)->second->neighbors.push_back(nodeMap.find(friendID)->second);
      nodeMap.find(friendID)->second->neighbors.push_back(nodeMap.find(idNumber)->second);
    }
  }else{
    if(nodeMap.find(friendID) != nodeMap.end()){
      idNode = new Node(idNumber, 0, false, newNeighbor);
      nodeMap.insert({idNumber, idNode});
      nodeMap.find(idNumber)->second->neighbors.push_back(nodeMap.find(friendID)->second);
      nodeMap.find(friendID)->second->neighbors.push_back(nodeMap.find(idNumber)->second);
    }else{
      idNode = new Node(idNumber, 0, false, newNeighbor);
      friendNode = new Node(friendID, 0, false, newNeighbor);
      nodeMap.insert({idNumber, idNode});
      nodeMap.insert({friendID, friendNode});
      nodeMap.find(idNumber)->second->neighbors.push_back(nodeMap.find(friendID)->second);
      nodeMap.find(friendID)->second->neighbors.push_back(nodeMap.find(idNumber)->second);
    }
  }
}
 
/* Read in relationships from an inputfile to create a graph */

bool Graph::loadFromFile(const char* in_filename) {
  ifstream infile(in_filename);

  while (infile) {
    string s;
    if (!getline(infile, s)) break;

    istringstream ss(s);
    vector<string> record;

    while (ss) {
      string s;
      if (!getline(ss, s, ' ')) break;
      record.push_back(s);
    }

    if (record.size() != 2) {
      continue;
    }

    //TODO - YOU HAVE THE PAIR OF IDS OF 2 FRIENDS IN 'RECORD'. WHAT DO NEED TO DO NOW? 
      int id1 = std::stoi(record[0]);
      int id2 = std::stoi(record[1]);
      addNode(id1, id2);
      record.clear();
  }

  if (!infile.eof()) {
    cerr << "Failed to read " << in_filename << "!\n";
    return false;
  }

  infile.close();
  return true;
}

/* Implement pathfinder*/
bool Graph::pathfinder(Node* from, Node* to, ostream & o) {
  for (auto itr : nodeMap) {
    itr.second->visited = false;
    itr.second->prev = 0;
  }
  vector<Node*> reverse;

  std::queue<Node*> q;
  from->visited = true;
  q.push(from);

  while(!q.empty()){
    Node* qNode = q.front();
    q.pop();

    if(qNode == to){
      while(qNode){
        reverse.push_back(qNode);
        qNode = qNode->prev;
      }

      while(!reverse.empty()) {
        o << reverse.back()->id;
        if(reverse.size() > 1)
          o << " ";
        reverse.pop_back();
      }
      o << "\n";
      while(!q.empty())
        q.pop();
      return true;
    }

    for(Node* n : qNode->neighbors){
      if(!n->visited){
        n->visited = true;
        n->prev = qNode;
        q.push(n);
      }
    }
  }
  o << "\n";
  return false;
}

Node* Graph::getNode(int id){
  return nodeMap.find(id)->second;
}

/* Implement social gathering*/
//TODO
void Graph::socialgathering(vector<string>& invitees, const int& k) {

}