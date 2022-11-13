#include <iostream>
#include "wikirace.h"
#include "heap.h"

using namespace std;

int main()
{
    // Write your own main here
    cout << "Add your own tests here! Modify main.cpp" << endl;
    Wikirace wikirace("../test_data/test_data_small.txt", 
                        "../test_data/test_name_small.txt");
    // Wikirace wikirace("../data/wiki-topcats.txt", 
    //                     "../data/wiki-topcats-page-names.txt");

    // print name map
    // for (auto pair : wikirace.name_) {
    //     cout << pair.first << ": " << pair.second << endl;
    // }

    // cout << "main before map"<< endl;

    for (auto pair : wikirace.adj_) {
        cout << pair.first << ": "  << endl;
        for (auto num: pair.second) {
            cout << "ID : " << num.first << " & " << " Wieght : " << num.second << endl;
        }
    }

    // print adj list
    for (int i = 0; i <= 4; ++i) {
        for (int j = 0; j <= 4; ++j) {
            vector<int> shortest_path = wikirace.shortest_path(i, j);
            std::cout << "Path from " + std::to_string(i) + " to " + std::to_string(j) << std::endl;
            for (int id : shortest_path) {
                std::cout << id << std::endl;
            }
        }
    }

    // int i = 0;
    // int j = 1;
    // vector<int> shortest_path = wikirace.shortest_path(i, j);
    // std::cout << "Path from " + std::to_string(i) + " to " + std::to_string(j) << std::endl;
    // for (int id : shortest_path) {
    //     std::cout << id << std::endl;
    // }
    
    return 0;
}
