#include <catch2/catch_test_macros.hpp>

#include <iostream>
#include <string>
# include <fstream>

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

TEST_CASE("small test constructor1", "[weight=10]")
{
    Wikirace wikirace("../test_data/test_data_small.txt", 
                        "../test_data/test_name_small.txt");
    

    REQUIRE(wikirace.name_[0] == "Chiasmal syndrome");
    REQUIRE(wikirace.name_[2] == "Pinakion");
    REQUIRE(wikirace.name_[4] == "Zariski's main theorem");


    /////////// test adj list ///////////////////
    vector<pair<int,int>> vect1{std::make_pair(1,5)};
    REQUIRE(wikirace.adj_[0] == vect1);

    vector<pair<int,int>> vect2{std::make_pair(2,5), std::make_pair(3,10)};
    REQUIRE(wikirace.adj_[1] == vect2);

    // vector<int> vect3{4, 1};
     vector<pair<int,int>> vect3{std::make_pair(4,5), std::make_pair(1,10)};
    REQUIRE(wikirace.adj_[2] == vect3);
}

TEST_CASE("test Dijkstra - small dataset", "[weight=10]")
{
    Wikirace wikirace("../test_data/test_data_small.txt", 
                        "../test_data/test_name_small.txt");

    vector<string> vect1{"Pinakion", "Kleroterion"};
    REQUIRE(wikirace.shortest_path("./output.txt", 2, 1) == vect1);

    vector<string> vect2{"Chiasmal syndrome", "Kleroterion", "Pinakion", "Zariski's main theorem"};
    REQUIRE(wikirace.shortest_path("./output.txt", 0, 4) == vect2);

    vector<string> vect3{};
    REQUIRE(wikirace.shortest_path("./output.txt", 3, 4) == vect3);
}

TEST_CASE("test Dijkstra - medium dataset - simple", "[weight=10]")
{
    Wikirace wikirace("../test_data/test_data_medium.txt", 
                        "../test_data/test_name_medium.txt");

    vector<string> vect1{"B", "D", "A", "F"};
    REQUIRE(wikirace.shortest_path("./output.txt", 1, 5) == vect1);

    vector<string> vect2{"A", "F", "E"};
    REQUIRE(wikirace.shortest_path("./output.txt", 0, 4) == vect2);

    vector<string> vect3{"D", "A", "F", "E"};
    REQUIRE(wikirace.shortest_path("./output.txt", 3, 4) == vect3);
}

TEST_CASE("test Dijkstra - medium dataset - disconnected", "[weight=10]")
{
    Wikirace wikirace("../test_data/test_data_medium.txt", 
                        "../test_data/test_name_medium.txt");

    vector<string> vect1{};
    REQUIRE(wikirace.shortest_path("./output.txt", 1, 8) == vect1);
}

TEST_CASE("test Dijkstra - medium dataset - cycles", "[weight=10]")
{
    Wikirace wikirace("../test_data/test_data_medium.txt", 
                        "../test_data/test_name_medium.txt");


    vector<string> vect1{"I", "L"};
    REQUIRE(wikirace.shortest_path("./output.txt", 8, 11) == vect1);
    
    vector<string> vect2{"J", "K", "L", "I"};
    REQUIRE(wikirace.shortest_path("./output.txt", 9, 8) == vect2);
}

TEST_CASE("test Dijkstra - full dataset", "[weight=10]")
{
    Wikirace wikirace("../data/wiki-topcats.txt", 
                        "../data/wiki-topcats-page-names.txt");

    vector<string> vect1{"Kleroterion", "Pinakion"};
    REQUIRE(wikirace.shortest_path("./output.txt", 1, 2) == vect1);

    vector<string> vect2{"Chiasmal syndrome", "Optic chiasm"};
    REQUIRE(wikirace.shortest_path("./output.txt", 0, 10772) == vect2);

    // (732528) 732422 1791471 
    // (732528) 732477 1791471
    vector<string> vect3{"Professional video over IP", "Resource reservation protocol", "Next Steps in Signaling"};
    REQUIRE(wikirace.shortest_path("./output.txt", 732528, 1791471) == vect3);

    vector<string> vect4{"Spermatophore", "Portable Document Format", "Universal 3D", "ArchiCAD", "Cinema 4D"};
    REQUIRE(wikirace.shortest_path("./output.txt", "Spermatophore", "Cinema 4D") == vect4);
    
}

TEST_CASE("test Dijkstra - using name", "[weight=10]")
{
    Wikirace wikirace("../test_data/test_data_small.txt", 
                        "../test_data/test_name_small.txt");

    vector<string> vect1{"Pinakion", "Kleroterion"};
    REQUIRE(wikirace.shortest_path("./output.txt", "Pinakion", "Kleroterion") == vect1);

    vector<string> vect2{"Chiasmal syndrome", "Kleroterion", "Pinakion", "Zariski's main theorem"};
    REQUIRE(wikirace.shortest_path("./output.txt", "Chiasmal syndrome", "Zariski's main theorem") == vect2);

    vector<string> vect3{};
    REQUIRE(wikirace.shortest_path("./output.txt", "LyndonHochschildSerre spectral sequence", "Zariski's main theorem") == vect3);
}

///////////////////////////////////////////////////////// BFS FUNCTIONS IsAccessible & IsAccessibleString TEST CASES ///////////////////////////////////

TEST_CASE("test BFS IsAccessible - small dataset - simple", "[weight=10]")
{
    Wikirace wikirace("../test_data/test_data_small.txt", "../test_data/test_name_small.txt");
    
    //startVertex & endVertex are just one node apart or the same node
    REQUIRE(wikirace.isAccessible(0, 0) == true);
    REQUIRE(wikirace.isAccessible(0, 1) == true);
    REQUIRE(wikirace.isAccessible(0, 3) == true);
    REQUIRE(wikirace.isAccessible(0, 2) == true);
    REQUIRE(wikirace.isAccessible(0, 4) == true);
    REQUIRE(wikirace.isAccessible(1, 3) == true);
    REQUIRE(wikirace.isAccessible(1, 2) == true);
    REQUIRE(wikirace.isAccessible(1, 4) == true);
    REQUIRE(wikirace.isAccessible(2, 1) == true);
    REQUIRE(wikirace.isAccessible(2, 4) == true);
    REQUIRE(wikirace.isAccessible(2, 3) == true);

    REQUIRE(wikirace.isAccessible(1, 0) == false);
    REQUIRE(wikirace.isAccessible(4, 0) == false);

    //startVertex & endVertex are multiple nodes apart
    REQUIRE(wikirace.isAccessible(0, 4) == true);
    REQUIRE(wikirace.isAccessible(2, 3) == true);
}

TEST_CASE("test IsAccessibleString - small dataset - simple", "[weight=10]")
{
    Wikirace wikirace("../test_data/test_data_small.txt", "../test_data/test_name_small.txt");

    //startVertex & endVertex are just one node apart or the same node
    REQUIRE(wikirace.isAccessibleString("Chiasmal syndrome", "Kleroterion") == true);
    REQUIRE(wikirace.isAccessibleString("Kleroterion", "Pinakion") == true);
    REQUIRE(wikirace.isAccessibleString("Kleroterion", "LyndonHochschildSerre spectral sequence") == true);
    REQUIRE(wikirace.isAccessibleString("Pinakion", "Zariski's main theorem") == true);

    REQUIRE(wikirace.isAccessibleString("Zariski's main theorem", "Chiasmal syndrome") == false);

    //startVertex & endVertex are multiple nodes apart
    REQUIRE(wikirace.isAccessibleString("Chiasmal syndrome", "LyndonHochschildSerre spectral sequence") == true);
    REQUIRE(wikirace.isAccessibleString("Kleroterion", "Zariski's main theorem") == true);
    REQUIRE(wikirace.isAccessibleString("Pinakion", "LyndonHochschildSerre spectral sequence") == true);

    REQUIRE(wikirace.isAccessibleString("LyndonHochschildSerre spectral sequence", "Chiasmal syndrome") == false);
    REQUIRE(wikirace.isAccessibleString("Zariski's main theorem", "Chiasmal syndrome") == false);
}

TEST_CASE("test BFS IsAccessible - medium dataset - simple", "[weight=10]") 
{
    Wikirace wikirace("../test_data/test_data_medium.txt", "../test_data/test_name_medium.txt");

    //startVertex & endVertex are just one node apart or the same node
    REQUIRE(wikirace.isAccessible(0, 0) == true);
    REQUIRE(wikirace.isAccessible(0, 1) == true);
    REQUIRE(wikirace.isAccessible(0, 5) == true);
    REQUIRE(wikirace.isAccessible(1, 2) == true);
    REQUIRE(wikirace.isAccessible(1, 3) == true);
    REQUIRE(wikirace.isAccessible(2, 7) == true);
    REQUIRE(wikirace.isAccessible(3, 0) == true);
    REQUIRE(wikirace.isAccessible(4, 2) == true);
    REQUIRE(wikirace.isAccessible(5, 4) == true);
    REQUIRE(wikirace.isAccessible(5, 6) == true);
    REQUIRE(wikirace.isAccessible(6, 4) == true);
    REQUIRE(wikirace.isAccessible(7, 4) == true);
    REQUIRE(wikirace.isAccessible(7, 6) == true);
    REQUIRE(wikirace.isAccessible(8, 9) == true);
    REQUIRE(wikirace.isAccessible(8, 11) == true);
    REQUIRE(wikirace.isAccessible(9, 10) == true);
    REQUIRE(wikirace.isAccessible(10, 11) == true);
    REQUIRE(wikirace.isAccessible(11, 8) == true);
    REQUIRE(wikirace.isAccessible(8, 8) == true);
    REQUIRE(wikirace.isAccessible(9, 9) == true);
    REQUIRE(wikirace.isAccessible(11, 11) == true);

    REQUIRE(wikirace.isAccessible(5, 0) == false);

    //startVertex & endVertex are multiple nodes apart
    REQUIRE(wikirace.isAccessible(0, 3) == true);
    REQUIRE(wikirace.isAccessible(1, 6) == true);
    REQUIRE(wikirace.isAccessible(5, 7) == true);
    REQUIRE(wikirace.isAccessible(6, 2) == true);
    REQUIRE(wikirace.isAccessible(4, 6) == true);
    REQUIRE(wikirace.isAccessible(7, 4) == true);
    REQUIRE(wikirace.isAccessible(3, 5) == true);
    REQUIRE(wikirace.isAccessible(8, 10) == true);
    REQUIRE(wikirace.isAccessible(9, 11) == true);
    REQUIRE(wikirace.isAccessible(9, 8) == true);
    REQUIRE(wikirace.isAccessible(11, 10) == true);

    REQUIRE(wikirace.isAccessible(6, 0) == false);
    REQUIRE(wikirace.isAccessible(2, 0) == false);
    REQUIRE(wikirace.isAccessible(7, 5) == false);
}

TEST_CASE("test IsAccessibleString - medium dataset - simple", "[weight=10]")
{
    Wikirace wikirace("../test_data/test_data_medium.txt", "../test_data/test_name_medium.txt");

    //startLink & endLink are just one node apart
    REQUIRE(wikirace.isAccessibleString("A", "B") == true);
    REQUIRE(wikirace.isAccessibleString("C", "H") == true);
    REQUIRE(wikirace.isAccessibleString("F", "E") == true);

    REQUIRE(wikirace.isAccessibleString("E", "A") == false);
    REQUIRE(wikirace.isAccessibleString("E", "F") == false);

    //startLink & endLink are multiple nodes apart
    REQUIRE(wikirace.isAccessibleString("A", "D") == true);
    REQUIRE(wikirace.isAccessibleString("B", "G") == true);
    REQUIRE(wikirace.isAccessibleString("G", "C") == true);
    REQUIRE(wikirace.isAccessibleString("D", "F") == true);

    REQUIRE(wikirace.isAccessibleString("G", "A") == false);
    REQUIRE(wikirace.isAccessibleString("H", "F") == false);
}

TEST_CASE("test BFS IsAccessible - medium dataset - disconnected", "[weight=10]")
{
    Wikirace wikirace("../test_data/test_data_medium.txt", "../test_data/test_name_medium.txt");
    
    /*
        In medium dataset there are 2 disconnected major components when you draw the graph
        by hand. I am just checking here if nodes from those components are actually disconnected in my code
    */
    REQUIRE(wikirace.isAccessible(8, 7) == false);
    REQUIRE(wikirace.isAccessible(9, 4) == false);
    REQUIRE(wikirace.isAccessible(11, 0) == false);
}

TEST_CASE("test IsAccessibleString - medium dataset - disconnected", "[weight=10]")
{
    Wikirace wikirace("../test_data/test_data_medium.txt", "../test_data/test_name_medium.txt");
    
    REQUIRE(wikirace.isAccessibleString("I", "H") == false);
    REQUIRE(wikirace.isAccessibleString("J", "E") == false);
    REQUIRE(wikirace.isAccessibleString("L", "A") == false);
}

TEST_CASE("test BFS IsAccessible - medium dataset - cycles", "[weight=10]")
{
    Wikirace wikirace("../test_data/test_data_medium.txt", "../test_data/test_name_medium.txt");

    // Nodes 8 and 11 are cylic so just checking here if they are connected in the medium dataset
    REQUIRE(wikirace.isAccessible(8, 11) == true);
}

TEST_CASE("test IsAccessibleString - medium dataset - cycles", "[weight=10]")
{
    Wikirace wikirace("../test_data/test_data_medium.txt", "../test_data/test_name_medium.txt");

    // Nodes 8 : "I" and 11 : "L" are cylic so just checking here if they are connected in the medium dataset
    REQUIRE(wikirace.isAccessibleString("I", "L") == true);
}

TEST_CASE("test BFS IsAccessible - wiki-topcats full dataset", "[weight=10]") 
{
    Wikirace wikirace("../data/wiki-topcats.txt", "../data/wiki-topcats.txt");

    //startVertex & endVertex are just one node apart or the same node
    REQUIRE(wikirace.isAccessible(0, 10772) == true);
    REQUIRE(wikirace.isAccessible(1, 170193) == true);
    REQUIRE(wikirace.isAccessible(3, 1101724) == true);
    REQUIRE(wikirace.isAccessible(4, 1103745) == true);
    REQUIRE(wikirace.isAccessible(58, 1492353) == true);
    REQUIRE(wikirace.isAccessible(144, 599070) == true);
    REQUIRE(wikirace.isAccessible(204, 1595907) == true);
    REQUIRE(wikirace.isAccessible(250, 813722) == true);
    REQUIRE(wikirace.isAccessible(161, 788483) == true);


    //startVertex & endVertex are multiple nodes apart
    REQUIRE(wikirace.isAccessible(161, 1101062) == true);
    REQUIRE(wikirace.isAccessible(166935, 1702611) == true);
    REQUIRE(wikirace.isAccessible(1756954, 28509) == true);
}

TEST_CASE("test IsAccessibleString - wiki-topcats full dataset", "[weight=10]")
{
    Wikirace wikirace("../data/wiki-topcats.txt", "../data/wiki-topcats.txt");

    //startLink & endLink are just one node apart
    REQUIRE(wikirace.isAccessibleString("LyndonHochschildSerre spectral sequence", "Homological algebra") == true);
    REQUIRE(wikirace.isAccessibleString("Zariski's main theorem", "Finite morphism") == true);
    REQUIRE(wikirace.isAccessibleString("St Paul of the Cross Cathedral", "Pipe organ") == true);
    REQUIRE(wikirace.isAccessibleString("Philip Grosser", "Alexander Berkman") == true);

    //startLink & endLink are multiple nodes apart
    REQUIRE(wikirace.isAccessibleString("Quasiperiodicity", "PlanetMath") == true);
    REQUIRE(wikirace.isAccessibleString("Hendrik van Riessen", "Terminism") == true);
    REQUIRE(wikirace.isAccessibleString("Hossein Koushki", "Wind turbine") == true);
}

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
