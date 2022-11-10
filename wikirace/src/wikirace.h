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

        Wikirace(map<int, vector<int>> adj);
        void DFS(int node, map<int, vector<int>>& adj, set<int>& visited, stack<int>& s);
        void DFS(int node, map<int, vector<int>>& adj, set<int>& visited);
        int Components();

    private:
        map<int, vector<int>> adj_;
        map<int, string> name_;
        
};

