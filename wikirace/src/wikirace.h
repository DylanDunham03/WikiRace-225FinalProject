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

        Wikirace(map<int, vector<pair<int, int>>> adj);
        void DFS(int node, map<int, vector<pair<int, int>>>& adj, set<int>& visited, stack<int>& s);
        void DFS(int node, map<int, vector<pair<int, int>>>& adj, set<int>& visited, set<int>& local);
        vector<set<int>> Components();

    private:
        map<int, vector<pair<int, int>>> adj_;  // pair <nodeID, weight>
        map<int, string> name_;
        
};

