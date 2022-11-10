#include "wikirace.h"

#include <map>
#include <vector>
#include <iostream>


using namespace std;

void adj_example1(map<int, vector<int>>& adj) {
    adj[0] = {1};
    adj[1] = {2};
    adj[2] = {3, 4};
    adj[3] = {0};
    adj[4] = {5};
    adj[5] = {6};
    adj[6] = {4};
    adj[7] = {6, 8};
    // adj[8] = {};
}

int main()
{
    // Write your own main here
    cout << "Add your own tests here! Modify main.cpp" << endl;
    // Wikirace wikirace("../test_data/test_data_small.txt", 
    //                     "../test_data/test_name_small.txt");

    map<int, vector<int>> adj;
    adj_example1(adj);
    Wikirace wikirace(adj);

    int num_components = wikirace.Components();
    cout << "num_components: " << num_components << endl;

    return 0;
}
