#include "wikirace.h"

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

int main()
{
    map<int, vector<pair<int, int>>> adj;
    adj_example1(adj);
    Wikirace wikirace(adj);

    vector<set<int>> components = wikirace.Components("./output.txt");
    for (size_t i = 0; i < components.size(); i++) {
        cout << "Set" << i << ": " << endl;
        for (auto it = components[i].begin(); it != components[i].end(); it++)
            cout << *it << ", ";
        cout << endl;
    }

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
