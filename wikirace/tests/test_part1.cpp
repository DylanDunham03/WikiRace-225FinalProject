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
    vector<pair<int,int>> vect1{std::make_pair(1,0)};

    REQUIRE(wikirace.adj_[0] == vect1);

    vector<pair<int,int>> vect2{std::make_pair(2,0), std::make_pair(3,5)};
    REQUIRE(wikirace.adj_[1] == vect2);

    // vector<int> vect3{4, 1};
    vector<pair<int,int>> vect3{std::make_pair(4,0), std::make_pair(1,5)};
    REQUIRE(wikirace.adj_[2] == vect3);
}
