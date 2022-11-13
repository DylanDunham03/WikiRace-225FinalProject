#pragma once

#include <iostream>
#include <map>
#include <vector>
#include <iterator>

#include "heap.h"

using namespace std;

class Wikirace {
    public:
        Wikirace(const string& file_data, const string& file_name);

        vector<int> shortest_path(const int src, const int dest);

        struct node{
            int id;
            string name;
        };

        map<int, vector<pair<int, int>>> adj_; // starting vertex, outgiong vertex, weight
        map<int, string> name_;

    private:
        map<int, map<int, std::pair<int, int>>> shortest_paths_; // src : [ (dest : predecessor and distance of dest in src's Dijkstra), ... ]

        void dijkstra(const int src);

        
};

