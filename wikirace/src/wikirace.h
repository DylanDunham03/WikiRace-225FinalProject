#pragma once

#include <iostream>
#include <map>
#include <vector>
#include <iterator>
#include <queue>

#include "heap.h"

#include <set>
#include <stack>

using namespace std;

class Wikirace {
    public:
        Wikirace(const string& file_data, const string& file_name);

        /**
        * Function for finding the shortest path from one page to another page, and write to the file file_path
        * @param src The origin or source page (as a string)
        * @param dest The destination or goal page (as a string)
        * @return The shortest path from src to dest as a vector of pages' names (as strings)
        */
        vector<string> shortest_path(const string& file_path, const string src, const string dest);

        /**
        * Function for finding the shortest path from one page to another page, and write to the file file_path
        * @param src The origin or source page (as an int)
        * @param dest The destination or goal page (as an int)
        * @return The shortest path from src to dest as a vector of pages' names (as strings)
        */
        vector<string> shortest_path(const string& file_path, const int src, const int dest);

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
        
        bool isAccessible(const string& file_path, int startVertex, int endVertex);
        bool isAccessibleString(const string& file_path, string startLink, string endLink);
        
    private:
        /** A  map to store the shortest paths from each node to all other nodes
        * i.e. store the result of calling Dijkstra's on each node,
        * so we don't have to perform the algorithm again if it is called
        */ 
        map<int, map<int, std::pair<int, int>>> shortest_paths_; // src : [ (dest : predecessor and distance of dest in src's Dijkstra), ... ]

        // Helper function to perform Dijkstra's on the src node
        void dijkstra(const int src);
        
};

