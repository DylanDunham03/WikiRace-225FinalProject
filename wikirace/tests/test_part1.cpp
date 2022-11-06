#include <catch2/catch_test_macros.hpp>

#include <iostream>
#include <string>

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

TEST_CASE("constructor", "[weight=10]")
{
    // PronounceDict d(pronunciations);
    // vector< string > canon = {"scent", "cent", "sent"};
    // auto result = cartalk_puzzle(d, "../data/cartalk_words.txt");
    // REQUIRE(result.size() == 1);
    // vector< string > result_vec = { get<0>(result[0]),
    //                                 get<1>(result[0]),
    //                                 get<2>(result[0]) };
    // REQUIRE(is_permutation(canon.begin(), canon.end(), result_vec.begin()));
}
