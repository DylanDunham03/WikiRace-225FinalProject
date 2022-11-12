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

Wikirace::Wikirace(map<int, vector<pair<int, int>>> adj) : adj_(adj) { }

void Wikirace::DFS(int node, map<int, vector<pair<int, int>>>& adj, set<int>& visited, stack<int>& s) {
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
    vector<pair<int, int>> adj_nodes = adj.find(node)->second;
    for (pair<int, int> adj_node : adj_nodes)
        DFS(adj_node.first, adj, visited, s);
    
    // push the node to the stack
    s.push(node);
}

void Wikirace::DFS(int node, map<int, vector<pair<int, int>>>& adj, set<int>& visited, set<int>& local) {
    // check whether the node is already visited
    if (visited.find(node) != visited.end())
        return;
    visited.insert(node);
    local.insert(node);

    // check whether the node has neighbors
    if (adj.find(node) == adj.end())
        return;
    
    // Do DFS if the node has neighbors
    vector<pair<int, int>> adj_nodes = adj.find(node)->second;
    for (pair<int, int> adj_node : adj_nodes)
        DFS(adj_node.first, adj, visited, local);
}

vector<set<int>> Wikirace::Components() {
    // Do DFS on G and set up the stack
    stack<int> s;
    set<int> visited;
    for (auto it = adj_.begin(); it != adj_.end(); it++) {
        DFS(it->first, adj_, visited, s);
    }

    // Make the tranpose of the graph G
    map<int, vector<pair<int, int>>> adj_transpose;
    for (auto it = adj_.begin(); it != adj_.end(); it++) {
        for (pair<int, int> adj_node : it->second)
            adj_transpose[adj_node.first].push_back(make_pair(it->first, adj_node.second));
    }

    // Do DFS on G transpose and get local set of a strongly connected component
    vector<set<int>> to_return;
    set<int> local;
    visited.clear();
    while (!s.empty()) {
        if (visited.find(s.top()) == visited.end()) {
            DFS(s.top(), adj_transpose, visited, local);
            to_return.push_back(local);
            local.clear();
        }
        s.pop();
    }

    return to_return;
}


// while (!s.empty()) {
//     cout << s.top() << endl;
//     s.pop();
// }

// for (auto it = adj_.begin(); it != adj_.end(); it++) {
//     cout << "node: " << it->first << " ---> {";
//     for (pair<int, int> adj_node : it->second)
//         cout << "(" << adj_node.first << ", " << adj_node.second << ")" << ", ";
//     cout << "}" << endl;
// }

// cout << endl;

// for (auto it = adj_transpose.begin(); it != adj_transpose.end(); it++) {
//     cout << "node: " << it->first << " ---> {";
//     for (pair<int, int> adj_node : it->second)
//         cout << "(" << adj_node.first << ", " << adj_node.second << ")" << ", ";
//     cout << "}" << endl;
// }

// cout << "num_components: " << num_components << " ---> " << s.top() << endl;