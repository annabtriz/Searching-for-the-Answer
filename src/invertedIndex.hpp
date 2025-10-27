#ifndef INVERTED_INDEX_HPP
#define INVERTED_INDEX_HPP

#include <string>
#include <map>
#include <vector>
#include <set>

using namespace std;

class InvertedIndex {
public:
    explicit InvertedIndex(const set<string>& stopWords = {});
    void buildFromFile(const string& filename);
    void saveToFile(const string& outputFilename) const;
    const map<string, vector<int>>& getIndex() const;

private:
    map<string, vector<int>> index;
    set<string> commonWords;

    string normalizeWord(const string& word);
    bool isCommonWord(const string& word) const;
};

#endif 