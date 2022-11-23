#pragma once

#include <iostream>
#include <map>
#include <vector>

#include <set>
#include <stack>

using namespace std;

class Wikirace {
    public:
        Wikirace(const string& file_data, const string& file_name);

         struct node{
            int id;
            string name;
        };

        map<int, vector<pair<int, int>>> adj_; // starting vertex, outgiong vertex, weight
        map<int, string> name_;
        map<string, int> name_shub_;

        Wikirace(map<int, vector<pair<int, int>>> adj);

        /**
        * Helper function of Componets() for depth-first traversing on G
        * Build the stack of nodes finished visiting step by step
        * 
        * @param node Current visiting node
        * @param adj The adjacency list of Graph G
        * @param visited The set of nodes already visited
        * @param s The stack of nodes finished visiting
        */
        void DFS(int node, map<int, vector<pair<int, int>>>& adj, set<int>& visited, stack<int>& s);

        /**
        * Helper function of Componets() for depth-first traversing on G transpose
        * Build up one strongly connected component each time
        * 
        * @param node Current visiting node
        * @param adj The adjacency list of Graph G transpose
        * @param visited The set of nodes already visited
        * @param local The set of nodes in a single strongly connected component
        */
        void DFS(int node, map<int, vector<pair<int, int>>>& adj, set<int>& visited, set<int>& local);

        /**
        * Perform Kosaraju's Algorithm, and return a vector of set of integers.
        * Each set indicate a strongly connected component.
        * 
        * @param file_path A path that indicate where the output of the data should be 
        */
        vector<set<int>> Components(const string& file_path);
        
};

