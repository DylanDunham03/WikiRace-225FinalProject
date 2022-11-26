#include "wikirace.h"

#include <fstream>
#include <iostream>
#include <cstring>
#include <algorithm>
#include <limits>
#include <stack>
#include <stdexcept>

using namespace std;

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

vector<string> Wikirace::shortest_path(const string& file_path, const string src, const string dest) {
    if (name_shub_.find(src) == name_shub_.end()) {
        throw std::invalid_argument("Shortest Path: Source node does not exist");
    }
    if (name_shub_.find(dest) == name_shub_.end()) {
        throw std::invalid_argument("Shortest Path: Destination node does not exist");
    }

    return shortest_path(file_path, name_shub_.at(src), name_shub_.at(dest));
}

vector<string> Wikirace::shortest_path(const string& file_path, const int src, const int dest) {
    if (shortest_paths_.find(src) == shortest_paths_.end()) {
        dijkstra(src);
    }

    const map<int, std::pair<int, int>>& src_dijkstra = shortest_paths_.at(src);
    vector<string> path;

    int curr = dest;
    while (curr != -1) {
        path.insert(path.begin(), name_.at(curr));
        curr = src_dijkstra.at(curr).first;
    }

    if (path.at(0) != name_.at(src)) {
        path = vector<string>();
    }

    ofstream myfile(file_path);
    if (myfile.is_open()) {
        for (string& name : path) {
            myfile << name << "\n";
        }
        myfile.close();
    } else {
        std::cout << "Unable to open the output destination file" << std::endl;
    }

    return path;
}

void Wikirace::dijkstra(const int src) {
    if (name_.find(src) == name_.end())  {
        throw std::invalid_argument("Dijkstra: Source node does not exist");
    }

    std::map<int, std::pair<int, int>> p_and_d; // point - (its predecessor, its distance from src)
    std::map<int, bool> T; // point - added to T or not

    for(std::map<int, string>::iterator it = name_.begin(); it != name_.end(); ++it) {
        p_and_d[it -> first] = std::make_pair(-1, std::numeric_limits<int>::max());
        T[it -> first] = false;
    }
    p_and_d.at(src) = std::make_pair(-1, 0);

    heap<std::pair<int, int>> pq; // distance from src - Node ID
    pq.push(std::make_pair(0, src));

    while (!pq.empty()) {
        std::pair<int, int> u_pair_distfromsrc_and_ID = pq.pop();
        int u = u_pair_distfromsrc_and_ID.second;
        if (u_pair_distfromsrc_and_ID.first != p_and_d.at(u).second) {
            continue;
        }
        for (pair<int, int> v_pair_ID_and_weight : adj_.at(u)) {

            int v = v_pair_ID_and_weight.first;
            int weight_u_to_v = v_pair_ID_and_weight.second;
            int new_dist = weight_u_to_v + p_and_d.at(u).second;

            if (new_dist < p_and_d.at(v).second) {
                p_and_d.at(v) = std::make_pair(u, new_dist);
                pq.push(std::make_pair(new_dist, v));
            }
        }
    }

    shortest_paths_[src] = p_and_d;
}


////////////////////////////////////////////////////// BREADTH FIRST SEARCH(BFS) ALGORITHM BELOW //////////////////////////////

/**
 * The IsAccessibleString function converts the integer nodes from the IsAccessible function
 * to strings from the adjacency list(number_) those strings are mapped to specific values in the
 * "wiki-topcats-page-names.txt" in the data folder. Checks whether there is a path from one link to
 * another link.
 * 
 * @param file_path     ..............................idk what to put here
 * @param startLink     starting link to begin BFS.
 * @param endVertex     ending link to end BFS.   
 * @return              a boolean value of true or false if a path is found from startLink to endLink.
 */
 
bool Wikirace::isAccessibleString(const string& file_path, string startLink, string endLink) {
    //name_shub_ is a map<string, int> created from the data in "wiki-topcats-page-names.txt"
    //convert startLink and endLink into their respective integer nodes
    int startVertex = name_shub_[startLink];
    int endVertex = name_shub_[endLink];
    
    //Run the BFS algorithm isAccessible
    return isAccessible(file_path, startVertex, endVertex);
}

bool Wikirace::isAccessible(const string& file_path, int startVertex, int endVertex) {

    // Base case that checks if the user is going from the same node back to itself, the path must exist.
    if(startVertex == endVertex) {
        return true;
    }
    
    // Create a vector<bool> of the size of the adjacency list and set all nodes to be visited = false.
    vector<bool> visited;                          
    for(unsigned i = 0; i < adj_.size(); i++) {
        visited.push_back(false);
    }

    /*
        Steps
            1) Create an empty queue, set the startVertex visited as true, push startVertex to queue
            2) Run BFS algorithm that searches through the nodes in the adjacency list pair, if it is 
            a new node not visisted yet set it to visited and push it to the queue
            3) Check if the queue is not empty, if it is return false, else check the latest node at the front and pop it
            and repeat the entire process again until the queue is empty or until the node we reach is the endNode
    */
    queue<int> q;
    visited[startVertex] = true;
    q.push(startVertex);
    while(!q.empty()) {
        int currVertex = q.front();
        q.pop();
        for(auto& pair : adj_.at(currVertex)) {
            if(visited[pair.first] == false) {
                visited[pair.first] = true;
                q.push(pair.first);
                if(pair.first == endVertex) {
                    ofstream myfile(file_path);
                    if (myfile.is_open()) {
                        myfile << "true" << "\n";
                        myfile.close();
                    } else {
                        std::cout << "Unable to open the output destination file" << std::endl;
                    }

                    return true;
                }
            }
        }
    }
    ofstream myfile(file_path);
    if (myfile.is_open()) {
        myfile << "false" << "\n";
        myfile.close();
    } else {
        std::cout << "Unable to open the output destination file" << std::endl;
    }
    return false;
}

