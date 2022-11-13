#include <iostream>
#include "wikirace.h"

#include <bits/stdc++.h>

using namespace std;

int main()
{

    time_t start, end;

    time(&start); // start timer

    cout << "Add your own tests here! Modify main.cpp" << endl;
    // Wikirace wikirace("../test_data/test_data_small.txt", 
    //                     "../test_data/test_name_small.txt");
    Wikirace wikirace("../data/wiki-topcats.txt", 
                        "../data/wiki-topcats-page-names.txt");


    time(&end); // end timer

    double time_taken = double(end - start);
    cout << "Time taken by program is : " << fixed
         << time_taken << setprecision(5);
    cout << " sec " << endl;

    // print name map
    // for (auto pair : wikirace.name_) {
    //     cout << pair.first << ": " << pair.second << endl;
    // }

    // cout << "main before map"<< endl;

    // for (auto pair : wikirace.adj_) {
    //     cout << "new pair" << endl;
    //     cout << pair.first << ": "  << endl;
    //     for (auto num: pair.second)
    //     cout << num << endl;
    // }

    //print adj list
    return 0;
}
