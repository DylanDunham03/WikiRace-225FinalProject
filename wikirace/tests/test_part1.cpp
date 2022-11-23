#include <catch2/catch_test_macros.hpp>

#include <iostream>
#include <string>

#include "../src/wikirace.h"

using std::cout;
using std::endl;
using std::string;


// TEST_CASE("test Components - small dataset", "[weight=10]")
// {
//     Wikirace wikirace("../test_data/test_data_small.txt", 
//                         "../test_data/test_name_small.txt");
    
//     vector<set<int>> components = wikirace.Components("./output.txt");

//     set<set<int>> solution;
//     solution.insert({0});
//     solution.insert({1, 2});
//     solution.insert({3});
//     solution.insert({4});

//     REQUIRE(components.size() == 4);
//     for (auto set : components)
//         REQUIRE(solution.find(set) != solution.end());
// }


// TEST_CASE("test Compoents - medium dataset", "[weight=10]")
// {
//     // Include Cycle, Isolated Components, and Connected but not Strongly Connected Component
//     Wikirace wikirace("../test_data/test_data_medium.txt", 
//                         "../test_data/test_name_medium.txt");
    
//     vector<set<int>> components = wikirace.Components("./output.txt");

//     set<set<int>> solution;
//     solution.insert({0, 1, 3});
//     solution.insert({2, 4, 6, 7});
//     solution.insert({5});
//     solution.insert({8, 9, 10, 11});

//     REQUIRE(components.size() == 4);
//     for (auto set : components)
//         REQUIRE(solution.find(set) != solution.end());
// }

# include <fstream>

void splitData(const string& input_file_data, const string& input_file_name, 
                const string& output_file_data, const string& output_file_name, int num) {
    ifstream inDataFile(input_file_data);
    ofstream outDataFile(output_file_data);
    ifstream inNameFile(input_file_name);
    ofstream outNameFile(output_file_name);

    int count = 0;
    if (inDataFile.is_open()) {
        while (count < num){
            count++;
            string str;
            getline(inDataFile, str);
            outDataFile << str << endl;
        }
    }

    count = 0;
    if (inNameFile.is_open()) {
        while (count < num){
            count++;
            string str;
            getline(inNameFile, str);
            outNameFile << str << endl;
        }
    }
}

void sortBothConnectedNodes(const string& input_file_data, const string& output_file_data) {
    ifstream inDataFile(input_file_data);
    ofstream outDataFile(output_file_data);
    map<int, set<int>> map;
    string str;

    if (inDataFile.is_open()) {
        while (getline(inDataFile, str)) {
            unsigned idx = str.find(" ");
            int first = stoi(str.substr(0, idx));
            int second = stoi(str.substr(idx));
            if (map.find(first) == map.end())
                map[first] = {second};
            else
                map[first].insert(second);
            
            if (map.find(second) == map.end())
                continue;
            if(map[second].find(first) != map[second].end())
                outDataFile << first << " " << second << endl;
        }
    }
}

TEST_CASE("test Components - full dataset", "[weight=10]")
{

    splitData("../data/wiki-topcats.txt", "../data/wiki-topcats-page-names.txt", 
                "../data/wiki-topcats-cutted.txt", "../data/wiki-topcats-page-names-cutted.txt", 800000);

    sortBothConnectedNodes("../data/wiki-topcats-cutted.txt", 
                            "../data/wiki-topcats-cutted-interconnected-nodes.txt");

    Wikirace wikirace("../data/wiki-topcats-cutted.txt", 
                        "../data/wiki-topcats-page-names-cutted.txt");

    vector<set<int>> components = wikirace.Components("./output.txt");

    string file_data = "../data/wiki-topcats-cutted-interconnected-nodes.txt";
    ifstream dataFile(file_data);
    string str;

    int num = 100;
    int count = 0;
    if(dataFile.is_open()) {
        while (count < num) {
            count++;
            getline(dataFile, str);
            unsigned idx = str.find(" ");
            int first = stoi(str.substr(0, idx));
            int second = stoi(str.substr(idx));

            // if the component contains one of the two nods, it has to contain the other as well
            for (auto component : components) {
                if (component.find(first) != component.end())
                    REQUIRE(component.find(second) != component.end());
                else
                    REQUIRE(component.find(second) == component.end());
            }
        }
    }
}
