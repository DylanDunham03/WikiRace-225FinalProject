#include "wikirace.h"
#include "heap.h"

#include <cmath>
// #include <matplot/matplot.h>

#include <bits/stdc++.h>

#include <map>
#include <vector>
#include <iostream>
#include <utility>


using namespace std;

void adj_example1(map<int, vector<pair<int, int>>>& adj) {
    adj[0] = {make_pair(1, 1)};
    adj[1] = {make_pair(2, 1)};
    adj[2] = {make_pair(3, 1)};
    // adj[2] = {make_pair(3, 1), make_pair(4, 1)};
    adj[3] = {make_pair(0, 1)};
    adj[4] = {make_pair(5, 1)};
    adj[5] = {make_pair(6, 1)};
    adj[6] = {make_pair(4, 1)};
    adj[7] = {make_pair(6, 1), make_pair(8, 1)};
    // adj[8] = {};
}

int main(int argc,char* argv[])
{
    if (argc != 4) {
        std::cout << "Uses : ./main (pages connection file) (pages name file) (output file)" << std::endl;
        return 0;
    }
    


    std::cout << "Start building graph..." << std::endl;
    Wikirace wikirace(argv[1], argv[2]);
    std::cout << "Finished building graph..." << std::endl;

    bool correct_input = false;
    while (!correct_input) {
        std::cout << "\nWhich function do you want to run? \n [1] isAccessible \n [2] shortest_path \n [3] Components \n Please type '1', '2', or '3' :" << std::endl;
        std::string choice;
        std::cin >> choice;

        if (choice == "1") {
            std::cout << "\n Select your input type: \n [1] Node's ID (int) \n [2] Node's name (string)" << std::endl;
            string type;
            std::cin >> type;
            if (type == "1") {
                std::cout << "\n Input your source node's ID" << std::endl;
                int src_id;
                std::cin >> src_id;
                std::cout << "\n Input your destination node's ID" << std::endl;
                int dest_id;
                std::cin >> dest_id;

                correct_input = true;
                wikirace.isAccessible(argv[3], src_id, dest_id);
            } else if (type == "2") {
                std::cout << "\n Input your source node's name" << std::endl;
                string src_name;
                std::cin >> src_name;
                std::cout << "\n Input your destination node's name" << std::endl;
                string dest_name;
                std::cin >> dest_name;

                correct_input = true;
                wikirace.isAccessibleString(argv[3], src_name, dest_name);
            }

        } else if (choice == "2") {
            std::cout << "\n Select your input type: \n [1] Node's ID (int) \n [2] Node's name (string)" << std::endl;
            string type;
            std::cin >> type;
            if (type == "1") {
                std::cout << "\n Input your source node's ID" << std::endl;
                int src_id;
                std::cin >> src_id;
                std::cout << "\n Input your destination node's ID" << std::endl;
                int dest_id;
                std::cin >> dest_id;

                correct_input = true;
                wikirace.shortest_path(argv[3], src_id, dest_id);
            } else if (type == "2") {
                std::cout << "\n Input your source node's name" << std::endl;
                string src_name;
                std::cin >> src_name;
                std::cout << "\n Input your destination node's name" << std::endl;
                string dest_name;
                std::cin >> dest_name;

                correct_input = true;
                wikirace.shortest_path(argv[3], src_name, dest_name);
            }
        } else if (choice == "3") {
            correct_input = true;
            wikirace.Components(argv[3]);
        }
    }




    // time_t start_c, end_c;

    // time(&start_c); // start timer

    // cout << "Add your own tests here! Modify main.cpp" << endl;
    // // Wikirace wikirace("../test_data/test_data_small.txt", 
    // //                     "../test_data/test_name_small.txt");
    // Wikirace wikirace("../data/wiki-topcats.txt", 
    //                     "../data/wiki-topcats-page-names.txt");


    // time(&end_c); // end timer

    // double time_taken_c = double(end_c - start_c);
    // cout << "Time taken by constructor is : " << fixed
    //      << time_taken_c << setprecision(5);
    // cout << " sec " << endl;

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

    // time_t start_d, end_d;

    // time(&start_d); // start timer

    // int running_nodes = 10;

    // for (int i = 0; i <= running_nodes; ++i) {
    //     for (int j = 0; j <= running_nodes; ++j) {
    //         vector<string> shortest_path = wikirace.shortest_path(i, j);
    //         std::cout << "Path from " + std::to_string(i) + " to " + std::to_string(j) << std::endl;
    //         for (string name : shortest_path) {
    //             std::cout << name << std::endl;
    //         }
    //     }
    // }

    // time(&end_d); // end timer

    // double time_taken_d = double(end_d - start_d);
    // cout << "Time taken by Dijkstra for " << running_nodes << " nodes is : " << fixed
    //      << time_taken_d << setprecision(5);
    // cout << " sec " << endl;

    // int i = 0;
    // int j = 1;
    // vector<string> shortest_path = wikirace.shortest_path(i, j);
    // std::cout << "Path from " + std::to_string(i) + " to " + std::to_string(j) << std::endl;
    // for (string name : shortest_path) {
    //     std::cout << name << std::endl;
    // }
    
    // map<int, vector<pair<int, int>>> adj;
    // adj_example1(adj);
    // Wikirace wikirace(adj);

    // vector<set<int>> components = wikirace.Components("./output.txt");
    // for (size_t i = 0; i < components.size(); i++) {
    //    cout << "Set" << i << ": " << endl;
    //    for (auto it = components[i].begin(); it != components[i].end(); it++)
    //        cout << *it << ", ";
    //    cout << endl;
    //}

    // Wikirace wikirace("../data/wiki-topcats.txt", 
    //                     "../data/wiki-topcats-page-names.txt");
    // vector<set<int>> components = wikirace.Components();
    // for (size_t i = 0; i < components.size(); i++) {
    //     cout << "Set" << i << ": " << endl;
    //     for (auto it = components[i].begin(); it != components[i].end(); it++)
    //         cout << *it << ", ";
    //     cout << endl;
    // }
    
    return 0;
}
