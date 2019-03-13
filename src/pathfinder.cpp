/*
Arman Massoudian
3/7/2019
Driver method takes input files builds graph finds paths and 
print them to file.
PA3
*/
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include "Graph.hpp"
#include "Node.hpp"
using namespace std;

void usage(char* program_name) {
  cerr << program_name << " called with incorrect arguments." << endl;
  cerr << "Usage: " << program_name
       << " friendship_pairs_file test_pairs_file output_file"
       << endl;
  exit(-1);
}

int main(int argc, char* argv[]) {
  
  if (argc != 4) {
    usage(argv[0]);
  }
  

  char* graph_filename = argv[1];
  char* pairs_filename = argv[2];
  char* output_filename = argv[3];

  Graph g;
  ofstream o;
  o.open(output_filename);

  g.loadFromFile(graph_filename);
  ifstream infile(pairs_filename);

  //read strings in as ints find their nodes then find 
  //shortest path between them using BFS
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

    //convert parsed strings into integers to find node
    //then find shortest path
      int id1 = std::stoi(record[0]);
      int id2 = std::stoi(record[1]);
      Node* n1 = g.getNode(id1);
      Node* n2 = g.getNode(id2);
      g.pathfinder(n1, n2, o);
      record.clear();
  }

  o.close();
}