/* Your code here! */

#include "wikirace.h"

#include <fstream>
#include <iostream>
#include <cstring>

Wikirace::Wikirace(const string& file_data, const string& file_name) {
    ifstream dataFile(file_data);
    ifstream nameFile(file_name);
    string str;
    if (dataFile.is_open()) {
        while (getline(dataFile, str)) {
            
            unsigned idx = str.find(" ");
            string first = str.substr(0, idx);
            string second = str.substr(idx);
            cout << first << " : " << second << endl;

        

        }
    }
    cout << endl<< "--------------file_data  --> file_name-------------" << endl << endl;
}



// ifstream wordsFile(filename);
// string word;
// if (wordsFile.is_open()) {
//     /* Reads a line from `wordsFile` into `word` until the file ends. */
//     while (getline(wordsFile, word)) {
//         cout << word << endl;
//     }
// }

// AnagramDict::AnagramDict(const string& filename)
// {
//     /* Your code goes here! */
//     ifstream anagram_dict(filename);
//     string line;
//     if (anagram_dict.is_open()) {
//         while (getline(anagram_dict, line)) {
//             string word = line;
//             std::sort(word.begin(), word.end());
//             dict[word].push_back(line);
//         }
//     }
// }