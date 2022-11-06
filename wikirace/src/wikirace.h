#pragma once

#include <iostream>
#include <map>
#include <vector>

using namespace std;

class Wikirace {
    public:
        Wikirace(const string& file_data, const string& file_name);

        struct node{
            int vertex_id;
            string name;
        };

    private:
        map<node, vector<node>> adj_;
        
};

