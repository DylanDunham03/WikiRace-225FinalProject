#include <iostream>
#include "wikirace.h"

using namespace std;

int main()
{
    // Write your own main here
    cout << "Add your own tests here! Modify main.cpp" << endl;
    Wikirace wikirace("../test_data/test_data_small.txt", 
                        "../test_data/test_name_small.txt");

    // print name map
    for (auto pair : wikirace.name_) {
        cout << pair.first << ": " << pair.second << endl;
    }

    cout << "main before map"<< endl;

    for (auto pair : wikirace.adj_) {
        cout << "new pair" << endl;
        cout << pair.first << ": "  << endl;
        for (auto num: pair.second)
        cout << num << endl;
    }

    //print adj list
    return 0;
}
