#include <catch2/catch_test_macros.hpp>
#include <catch2/benchmark/catch_benchmark.hpp>
#include <catch2/benchmark/catch_constructor.hpp>
#include <catch2/generators/catch_generators_range.hpp>

#include "../src/invertedIndex.hpp"
#include <fstream>

using namespace std; 

TEST_CASE() {
    set<string> commonWords = {"a", "an", "and", "the", "in"};
    InvertedIndex index(commonWords);

    ofstream testFile("test_input.txt");
    testFile << "The brown cat and the blue rat live in the brown house.";
    testFile.close();

    index.buildFromFile("test_input.txt");
    const auto& result = index.getIndex();

    REQUIRE(result.count("brown") == 1);
    REQUIRE(result.at("brown") == vector<int>({1, 10}));
    REQUIRE(result.at("rat") == vector<int>({6}));
    REQUIRE(result.at("live") == vector<int>({7}));
}


TEST_CASE("benchmarks for multiple sizes") {
    set<string> stopWords = {"a", "an", "and", "the"};
    InvertedIndex index(stopWords);

    vector<int> sizes = {10, 50, 300, 1000, 1300, 5500, 10000, 213431, 893490, 100000};

    for (int size : sizes) {
        BENCHMARK("Build inverted index for " + to_string(size) + " words") {
            ofstream file("temp_input.txt");
            for (int i = 0; i < size; ++i) {
                file << "word" << (i % 100) << " ";
            }
            file.close();

            index.buildFromFile("temp_input.txt");
        };
    }
}