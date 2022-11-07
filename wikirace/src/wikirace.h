#pragma once

#include <iostream>
#include <map>
#include <vector>
#include <iterator>

using namespace std;

class Wikirace {
    public:
        Wikirace(const string& file_data, const string& file_name);

        struct node{
            int id;
            string name;
        };

        map<int, vector<int>> adj_;
        map<int, string> name_;

    private:

        
};

