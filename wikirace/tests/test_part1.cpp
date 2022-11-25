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

