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

                // cout << "node with no outbound edges" << endl;
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

bool Wikirace::isAccessibleString(const string& file_path, string startLink, string endLink) {
    int startVertex = name_shub_[startLink];
    int endVertex = name_shub_[endLink];
    return isAccessible(file_path, startVertex, endVertex);
}

bool Wikirace::isAccessible(const string& file_path, int startVertex, int endVertex) {

    //all nodes visited = false
    vector<bool> visited;                          
    for(unsigned i = 0; i < adj_.size(); i++) {
        visited.push_back(false);
    }
    queue<int> q;

    //the start node visited = true
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
