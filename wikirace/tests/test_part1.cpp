#include <catch2/catch_test_macros.hpp>

#include <iostream>
#include <string>


#include "../src/wikirace.h"

using std::cout;
using std::endl;
using std::string;


TEST_CASE("PUT YOUR TESTS HERE!!!", "[weight=10][part1]") {
    // Feel free to use this to put your own test cases.
    // Look at other test files for inspiration!
    string expected = "I put my own test cases here.";
    string actual = "I put my own test cases here.";
    REQUIRE(expected == actual);
}

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

    vector<int> vect1{2, 1};
    REQUIRE(wikirace.shortest_path(2, 1) == vect1);

    vector<int> vect2{0, 1, 2, 4};
    REQUIRE(wikirace.shortest_path(0, 4) == vect2);

    vector<int> vect3{};
    REQUIRE(wikirace.shortest_path(3, 4) == vect3);
}

TEST_CASE("test Dijkstra - medium dataset - simple", "[weight=10]")
{
    Wikirace wikirace("../test_data/test_data_medium.txt", 
                        "../test_data/test_name_medium.txt");

    vector<int> vect1{1, 3, 0, 5};
    REQUIRE(wikirace.shortest_path(1, 5) == vect1);

    vector<int> vect2{0, 5, 4};
    REQUIRE(wikirace.shortest_path(0, 4) == vect2);

    vector<int> vect3{3, 0, 5, 4};
    REQUIRE(wikirace.shortest_path(3, 4) == vect3);
}

TEST_CASE("test Dijkstra - medium dataset - disconnected", "[weight=10]")
{
    Wikirace wikirace("../test_data/test_data_medium.txt", 
                        "../test_data/test_name_medium.txt");

    vector<int> vect1{};
    REQUIRE(wikirace.shortest_path(1, 8) == vect1);
}

TEST_CASE("test Dijkstra - medium dataset - cycles", "[weight=10]")
{
    Wikirace wikirace("../test_data/test_data_medium.txt", 
                        "../test_data/test_name_medium.txt");


    vector<int> vect1{8, 11};
    REQUIRE(wikirace.shortest_path(8, 11) == vect1);

    vector<int> vect2{9, 10, 11, 8};
    REQUIRE(wikirace.shortest_path(9, 8) == vect2);
}

TEST_CASE("test Dijkstra - using name", "[weight=10]")
{
    Wikirace wikirace("../test_data/test_data_small.txt", 
                        "../test_data/test_name_small.txt");

    vector<int> vect1{2, 1};
    REQUIRE(wikirace.shortest_path("Pinakion", "Kleroterion") == vect1);

    vector<int> vect2{0, 1, 2, 4};
    REQUIRE(wikirace.shortest_path("Chiasmal syndrome", "Zariski's main theorem") == vect2);

    vector<int> vect3{};
    REQUIRE(wikirace.shortest_path("LyndonHochschildSerre spectral sequence", "Zariski's main theorem") == vect3);
}