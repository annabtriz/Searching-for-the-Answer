#include "src/invertedIndex.hpp"

#include <iostream>
#include <set>

using namespace std;

int main() {
    set<string> commonwords = {
        "a", "an", "and", "the", "they", "to", "for", "you", "your", "in", "of"
    };

    InvertedIndex index(commonwords);
    try {
        index.buildFromFile("test_input.txt");
        index.saveToFile("output_index.txt");
        cout << "Inverted index successfully saved as output_index.txt\n";
    } 
    catch (const exception& e) {
        cerr << e.what() << '\n';
        return 1;
    }
    return 0;
}