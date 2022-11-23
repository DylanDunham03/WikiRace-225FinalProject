#include "wikirace.h"

#include <fstream>
#include <iostream>
#include <cstring>
#include <algorithm>
#include <limits>
#include <stack>
#include <stdexcept>

Wikirace::Wikirace(const string& file_data, const string& file_name) {
    ifstream dataFile(file_data);
    ifstream nameFile(file_name);
    string str;

    if (dataFile.is_open()) {
        while (getline(dataFile, str)) {
            
            unsigned idx = str.find(" ");

            // stoi converts str to int

            int first = stoi(str.substr(0, idx));
            int second = stoi(str.substr(idx));
            // cout << first << " : " << second << endl;


            if (adj_.find(first) != adj_.end()) {
                // key already found
                // assumes never adding duplicates

                adj_[first].push_back(make_pair(second, adj_[first].back().second + 5));
            } else {
                // key not found
                vector<std::pair<int,int>> vec {make_pair(second, 5)}; 
                adj_.insert({first , vec});
            }
        }
    }
    // cout << endl<< "--------------file_data  --> file_name-------------" << endl << endl;
    if (nameFile.is_open()) {
        while (getline(nameFile, str)) {
            unsigned idx = str.find(" ");
            string id = str.substr(0, idx);
            string name = str.substr(idx+1);

            name_.insert({stoi(id), name});
            name_shub_.insert({name, stoi(id)});
            if (adj_.find(stoi(id)) == adj_.end()) {
                // nodes with no outbound edges

                // cout << "node with no outbound edges" << endl;
                vector<std::pair<int,int>> vec;
                adj_.insert({stoi(id) , vec});
            }

            // cout << id << " : " << name << endl;
        }
    }
}

Wikirace::Wikirace(map<int, vector<pair<int, int>>> adj) : adj_(adj) { }

/**
 * Helper function of Componets() for depth-first traversing on G
 * Build the stack of nodes finished visiting step by step
 * 
 * @param node Current visiting node
 * @param adj The adjacency list of Graph G
 * @param visited The set of nodes already visited
 * @param s The stack of nodes finished visiting
 */
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
    for (pair<int, int>& adj_node : adj_nodes)
        DFS(adj_node.first, adj, visited, s);
    
    // push the node to the stack
    s.push(node);
}

/**
 * Helper function of Componets() for depth-first traversing on G transpose
 * Build up one strongly connected component each time
 * 
 * @param node Current visiting node
 * @param adj The adjacency list of Graph G transpose
 * @param visited The set of nodes already visited
 * @param local The set of nodes in a single strongly connected component
 */
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
    for (pair<int, int>& adj_node : adj_nodes)
        DFS(adj_node.first, adj, visited, local);
}

/**
 * Perform Kosaraju's Algorithm, and return a vector of set of integers.
 * Each set indicate a strongly connected component.
 * 
 * @param file_path A path that indicate where the output of the data should be 
 */
vector<set<int>> Wikirace::Components(const string& file_path) {
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

    // Output the data into the directed file
    ofstream myfile(file_path);
    if (myfile.is_open()) {
        for (auto& set : to_return) {
            for (auto& integer : set)
                myfile << integer << ",";
            myfile << endl;
        }
        myfile.close();
    } else {
        std::cout << "Unable to open the output destination file" << std::endl;
    }

    return to_return;
}

// vector<set<int>> Wikirace::Components() {
//     stack<int> nodes;
//     stack<int> dfs_stack;
//     set<int> visited;
//     for (auto it = adj_.begin(); it != adj_.end(); it++) {
//         dfs_stack.push(it->first);
//         while(!dfs_stack.empty()) {
//             int curr = dfs_stack.top();
//             dfs_stack.pop();
//             if (visited.find(curr) != visited.end())
//                 continue;
//             visited.insert(curr);

//             if (adj.find(curr) == adj.end()) {
//                 nodes.push(curr);
//                 continue;
//             }

//             for (auto pair : adj_[it]) {
//                 if (visited.find(pair.first) == visited.end())
//                     dfs_stack.push(pair.first);
//                     nodes.push(pair.first);
//             }
//         }
//     }
// }

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