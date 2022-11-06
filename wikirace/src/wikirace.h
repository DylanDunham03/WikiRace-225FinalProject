#pragma once

#include <iostream>
#include <map>
#include <vector>

using namespace std;

class Wikirace {
    public:
        Wikirace(const string& file_data, const string& file_name);

    private:
        map<int, vector<int>> adj_;
};

