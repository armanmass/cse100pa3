/*
Arman Massoudian
3/7/2019
Build Graph and finds shortest path between vertices in graph.
PA3
*/
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
#include <list>

using namespace std;

Graph::Graph() {}
/*
Graph destructor iterates over pairs and deletes them.
*/
Graph::~Graph() {
  for (auto itr : nodeMap)
    delete itr.second;
}

/* 
*addNode takes in two vertice ids and inserts into the map on a case by case basis.
*4 Cases: TT, TF, FT, FT
*F= in map T= not in map
*/
void Graph::addNode(int idNumber, int friendID){
  vector<Node*> newNeighbor;
  Node* idNode;
  Node* friendNode;

  if(nodeMap.find(idNumber) != nodeMap.end()){
    if(nodeMap.find(friendID) != nodeMap.end()){
      nodeMap.find(idNumber)->second->neighbors.push_back(nodeMap.find(friendID)->second);
      nodeMap.find(friendID)->second->neighbors.push_back(nodeMap.find(idNumber)->second);
    }else{
      friendNode = new Node(friendID, 0, 0, 0, false, newNeighbor);
      nodeMap.insert({friendID, friendNode});
      nodeMap.find(idNumber)->second->neighbors.push_back(nodeMap.find(friendID)->second);
      nodeMap.find(friendID)->second->neighbors.push_back(nodeMap.find(idNumber)->second);
    }
  }else{
    if(nodeMap.find(friendID) != nodeMap.end()){
      idNode = new Node(idNumber, 0, 0, 0, false, newNeighbor);
      nodeMap.insert({idNumber, idNode});
      nodeMap.find(idNumber)->second->neighbors.push_back(nodeMap.find(friendID)->second);
      nodeMap.find(friendID)->second->neighbors.push_back(nodeMap.find(idNumber)->second);
    }else{
      idNode = new Node(idNumber, 0, 0, 0, false, newNeighbor);
      friendNode = new Node(friendID, 0, 0, 0, false, newNeighbor);
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

  //parse input string reading two strings delimited by a space
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

    //convert parsed strings into integers and add to graph
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
  //searching for path from a node to itself
  if((from == to) && (from > 0)){
    o << from->id << "\n";
    return true;
  }
  
  //case if either node DNE in graph
  if(!from || !to){
    o << "\n";
    return false;
  }

  //BFS
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

//getter method for Node in map
Node* Graph::getNode(int id){
  if(nodeMap.find(id) == nodeMap.end())
    return 0;
  return nodeMap.find(id)->second;
}

/* Implement social gathering*/
//TODO
void Graph::socialgathering(vector<int>& invitees, const int& k) {
  int md = 0;
  for(auto itr : nodeMap){
    itr.second->degree = itr.second->neighbors.size();
    if(itr.second->degree > md)
      md = itr.second->degree;
  }

  std::list<Node*> output;
  std::vector<std::list<Node*>> deg(md + 1);

  for(auto itr : nodeMap)
    deg[itr.second->degree].push_back(itr.second);
  

  unsigned int max = 0;
  Node* temp = nullptr;
  for(unsigned int i = 0; i < nodeMap.size(); i++){
    temp = nullptr;
    unsigned int j = 0;
    while(deg[j].empty()) j++;
    max = max(max, j);
    temp = deg[j].front();
    deg[j].pop_front();
    output.push_back(temp);
    temp->visited = true;

    for(Node* n : temp->neighbors){
      if(!n->visited){
        n->degree--;
        deg[n->degree].push_back(n);
        deg[n->degree+1].remove(n);
      }
    }
  }

  while(!output.empty()){
    if(output.front()->degree >= k)
      invitees.push_back(output.front()->id);
    output.pop_front();
  }
  std::sort(invitees.begin(), invitees.end());
}

vector<int> Graph::cores(){
  int n, d, md, i, start, num;
  int v, u, w, du, pu, pw;

  n = nodeMap.size(); md = 0;
  cout << n << " " << endl;
  vector<int> pos(n,0);
  vector<int> bin(n,0);
  vector<int> vert(n,0);
  vector<int> deg(n,0);
  v = 1;
  cout << n << " " << endl;
  for(auto itr : nodeMap){
    deg[v] = itr.second->neighbors.size();
    if(deg[v] > md)
      md = deg[v];
    v++;
  }

  for(d = 0; d <= md; d++)
    bin[d] = 0;

  for(v = 1; v <= n; v++)
    bin[deg[v]]++;

start = 1;
for(d = 0; d <= md; d++){
  cout << d << " " << bin[d] << endl;
  num = bin[d];
  bin[d] = start;
  start += num;
 }

 for(v = 1; v <= n; v++){
   pos[v] = bin[deg[v]];
   vert[pos[v]] = v;
   bin[deg[v]]++;
 }

 for(d = md; d >= 1; d--)
   bin[d] = bin[d-1];
 bin[0] = 1;

 for(i = 1; i <= n; i++){
   v = vert[i];
   if(nodeMap.find(v) != nodeMap.end()){
   for(Node* nptr : nodeMap.find(v)->second->neighbors){
     u = nptr->id;
     if(deg[u] > deg[v]){
       du = deg[u];
       pu = pos[u];
       pw = bin[du];
       w = vert[pw];
       if(u != w){
         pos[u] = pw;
         pos[w] = pu;
         vert[pu] = w;
         vert[pw] = u;
       }
       bin[du]++;
       deg[u]--;
     }
   }
 }
 }
 return deg;
}