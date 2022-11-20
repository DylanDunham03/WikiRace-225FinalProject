#include <iostream>
#include "wikirace.h"
#include "heap.h"

#include <cmath>
// #include <matplot/matplot.h>

#include <bits/stdc++.h>

using namespace std;

int main()
{

    time_t start_c, end_c;

    time(&start_c); // start timer

    cout << "Add your own tests here! Modify main.cpp" << endl;
    // Wikirace wikirace("../test_data/test_data_small.txt", 
    //                     "../test_data/test_name_small.txt");
    Wikirace wikirace("../data/wiki-topcats.txt", 
                        "../data/wiki-topcats-page-names.txt");


    time(&end_c); // end timer

    double time_taken_c = double(end_c - start_c);
    cout << "Time taken by constructor is : " << fixed
         << time_taken_c << setprecision(5);
    cout << " sec " << endl;

    // print name map
    // for (auto pair : wikirace.name_) {
    //     cout << pair.first << ": " << pair.second << endl;
    // }

    // cout << "main before map"<< endl;

    // for (auto pair : wikirace.adj_) {
    //     cout << pair.first << ": "  << endl;
    //     for (auto num: pair.second) {
    //         cout << "ID : " << num.first << " & " << " Wieght : " << num.second << endl;
    //     }
    // }

    // print adj list

    time_t start_d, end_d;

    time(&start_d); // start timer

    int running_nodes = 10;

    for (int i = 0; i <= running_nodes; ++i) {
        for (int j = 0; j <= running_nodes; ++j) {
            vector<string> shortest_path = wikirace.shortest_path(i, j);
            std::cout << "Path from " + std::to_string(i) + " to " + std::to_string(j) << std::endl;
            for (string name : shortest_path) {
                std::cout << name << std::endl;
            }
        }
    }

    time(&end_d); // end timer

    double time_taken_d = double(end_d - start_d);
    cout << "Time taken by Dijkstra for " << running_nodes << " nodes is : " << fixed
         << time_taken_d << setprecision(5);
    cout << " sec " << endl;

    // int i = 0;
    // int j = 1;
    // vector<string> shortest_path = wikirace.shortest_path(i, j);
    // std::cout << "Path from " + std::to_string(i) + " to " + std::to_string(j) << std::endl;
    // for (string name : shortest_path) {
    //     std::cout << name << std::endl;
    // }
    
    return 0;
}
