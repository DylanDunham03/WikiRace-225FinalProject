#include "wikirace.h"

#include <fstream>
#include <iostream>
#include <cstring>

Wikirace::Wikirace(const string& file_data, const string& file_name) {
    ifstream dataFile(file_data);
    ifstream nameFile(file_name);
    string str;

    if (dataFile.is_open()) {
        while (getline(dataFile, str)) {
            
            unsigned idx = str.find(" ");
            string first = str.substr(0, idx);
            string second = str.substr(idx);
            cout << first << " : " << second << endl;

        

        }
    }
    cout << endl<< "--------------file_data  --> file_name-------------" << endl << endl;
        if (nameFile.is_open()) {
        while (getline(nameFile, str)) {
            unsigned idx = str.find(" ");
            string id = str.substr(0, idx);
            string name = str.substr(idx);
        }
    }
}

Wikirace::Wikirace(map<int, vector<int>> adj) : adj_(adj) { }

void Wikirace::DFS(int node, map<int, vector<int>>& adj, set<int>& visited, stack<int>& s) {
    // check whether the node is already visited
    if (visited.find(node) != visited.end())
        return;
    visited.insert(node);

    // check whether the node has neighbors
    if (adj.find(node) == adj.end()) {
        s.push(node);
        return;
    }

    // Do DFS if the node has neighbors
    vector<int> adj_nodes = adj.find(node)->second;
    for (int adj_node : adj_nodes)
        DFS(adj_node, adj, visited, s);
    
    // push the node to the stack
    s.push(node);
}

void Wikirace::DFS(int node, map<int, vector<int>>& adj, set<int>& visited) {
    // check whether the node is already visited
    if (visited.find(node) != visited.end())
        return;
    visited.insert(node);

    // check whether the node has neighbors
    if (adj.find(node) == adj.end())
        return;
    
    // Do DFS if the node has neighbors
    vector<int> adj_nodes = adj.find(node)->second;
    for (int adj_node : adj_nodes)
        DFS(adj_node, adj, visited);
}

int Wikirace::Components() {
    // Do DFS on G and set up the stack
    stack<int> s;
    set<int> visited;
    for (auto it = adj_.begin(); it != adj_.end(); it++) {
        DFS(it->first, adj_, visited, s);
    }

    // Make the tranpose of the graph G
    map<int, vector<int>> adj_transpose;
    for (auto it = adj_.begin(); it != adj_.end(); it++) {
        for (int adj_node : it->second)
            adj_transpose[adj_node].push_back(it->first);
    }

    // Do DFS on G transpose and get num_components
    int num_components = 0;
    visited.clear();
    while (!s.empty()) {
        if (visited.find(s.top()) == visited.end()) {
            DFS(s.top(), adj_transpose, visited);
            num_components++;
        }
        s.pop();
    }

    return num_components;
}


// while (!s.empty()) {
//     cout << s.top() << endl;
//     s.pop();
// }

// for (auto it = adj_transpose.begin(); it != adj_transpose.end(); it++) {
//     cout << "node: " << it->first << " ---> {";
//     for (int adj_node : it->second)
//         cout << adj_node << ", ";
//     cout << "}" << endl;
// }

// cout << "num_components: " << num_components << " ---> " << s.top() << endl;