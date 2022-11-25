/* Your code here! */

#include "wikirace.h"

#include <fstream>
#include <iostream>
#include <cstring>
#include <algorithm>
#include <limits>
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

                cout << "node with no outbound edges" << endl;
                vector<std::pair<int,int>> vec;
                adj_.insert({stoi(id) , vec});
            }

            // cout << id << " : " << name << endl;
        }
    }
}



// ifstream wordsFile(filename);
// string word;
// if (wordsFile.is_open()) {
//     /* Reads a line from `wordsFile` into `word` until the file ends. */
//     while (getline(wordsFile, word)) {
//         cout << word << endl;
//     }
// }

// AnagramDict::AnagramDict(const string& filename)
// {
//     /* Your code goes here! */
//     ifstream anagram_dict(filename);
//     string line;
//     if (anagram_dict.is_open()) {
//         while (getline(anagram_dict, line)) {
//             string word = line;
//             std::sort(word.begin(), word.end());
//             dict[word].push_back(line);
//         }
//     }
// }


vector<int> Wikirace::shortest_path(const int src, const int dest) {
    if (shortest_paths_.find(src) == shortest_paths_.end()) {
        dijkstra(src);
    }

    const map<int, std::pair<int, int>>& src_dijkstra = shortest_paths_.at(src);
    vector<int> path;

    int curr = dest;
    while (curr != -1) {
        path.insert(path.begin(), curr);
        curr = src_dijkstra.at(curr).first;
    }

    if (path.at(0) != src) {
        return vector<int>();
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
 * The IsAccessible function deals with checking whether a path exists from
 * integer nodes in "wiki-topcats.txt" file.
 *
 * @param file_path     ..............................idk what to put here
 * @param startVertex   starting node of the BFS.
 * @param endVertex     ending node of the BFS   
 * @return              a boolean value of true or false if a path is found from one node to the other.
 */

bool Wikirace::isAccessible(int startVertex, int endVertex) {

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
                    return true;
                }
            }
        }
    }
    return false;
}

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

bool Wikirace::isAccessibleString(string startLink, string endLink) {
    
    //name_shub_ is a map<string, int> created from the data in "wiki-topcats-page-names.txt"
    //convert startLink and endLink into their respective integer nodes
    int startVertex = name_shub_[startLink];
    int endVertex = name_shub_[endLink];

    //Run the BFS algorithm isAccessible
    return isAccessible(startVertex, endVertex);
}
