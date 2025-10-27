#include "invertedIndex.hpp"
#include <fstream>
#include <sstream>
#include <algorithm>
#include <cctype>
#include <iostream>

using namespace std;

InvertedIndex::InvertedIndex(const set<string>& stopWords)
    : commonWords(stopWords) {}

string InvertedIndex::normalizeWord(const string& word) {
    string normalized;
    for (char c : word) {
        if (isalnum(static_cast<unsigned char>(c)) || c == '-')
            normalized += tolower(static_cast<unsigned char>(c));
    }
    return normalized;
}

bool InvertedIndex::isCommonWord(const string& word) const {
    return commonWords.find(word) != commonWords.end();
}

void InvertedIndex::buildFromFile(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) throw runtime_error("Error: Could not open file.");

    index.clear();

    string word;
    int position = 0;
    while (file >> word) {
        string normalized = normalizeWord(word);
        if (!normalized.empty() && !isCommonWord(normalized)) {
            index[normalized].push_back(position);
        }
        ++position;
    }
}

void InvertedIndex::saveToFile(const string& outputFilename) const {
    ofstream out(outputFilename, ios::out | ios::binary);
    if (!out.is_open()) throw runtime_error("Error: Could not open output file.");

    out << "{\n";
    bool first = true;

    for (const auto& [word, positions] : index) {
        if (!first) out << ",\n";
        first = false;

        out << "  \"" << word << "\": [";

        for (size_t i = 0; i < positions.size(); ++i) {
            out << positions[i];
            if (i + 1 < positions.size())
                out << ", ";
        }

        out << "]";
    }

    out << "\n}\n";
    out.close();
}

const map<string, vector<int>>& InvertedIndex::getIndex() const {
    return index;
}