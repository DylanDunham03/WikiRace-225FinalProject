#pragma once

#include <iostream>
#include <map>
#include <vector>
#include <iterator>
#include <queue>

using namespace std;

class Wikirace {
    public:
        Wikirace(const string& file_data, const string& file_name);

        map<int, vector<pair<int, int>>> adj_;
        // starting vertex, outgiong vertex, weight
        map<int, string> name_;

        bool isAccessible(int startVertex, int endVertex);
        bool isAccessibleString(string startLink, string endLink);
        
    private:

        
};

