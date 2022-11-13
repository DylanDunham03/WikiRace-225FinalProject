/* Your code here! */

#include "wikirace.h"

#include <fstream>
#include <iostream>
#include <cstring>
#include <algorithm>

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
    cout << endl<< "--------------file_data  --> file_name-------------" << endl << endl;
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