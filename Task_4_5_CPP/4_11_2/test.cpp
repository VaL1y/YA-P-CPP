#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>
#include "dictionary.h"

TEST_CASE("Dictionary operations") {
Dictionary dict;

SECTION("Add single word") {
dict.addWord("hello");
auto words = dict.getWordsAlphabetically();
REQUIRE(words.size() == 1);
REQUIRE(words[0].first == "hello");
REQUIRE(words[0].second == 1);
}

SECTION("Add multiple words") {
dict.addWord("hello");
dict.addWord("world");
dict.addWord("hello");
auto words = dict.getWordsAlphabetically();
REQUIRE(words.size() == 2);
REQUIRE(words[0].first == "hello");
REQUIRE(words[0].second == 2);
REQUIRE(words[1].first == "world");
REQUIRE(words[1].second == 1);
}

SECTION("Sort by frequency") {
dict.addWord("hello");
dict.addWord("world");
dict.addWord("hello");
auto words = dict.getWordsByFrequency();
REQUIRE(words[0].first == "hello");
REQUIRE(words[0].second == 2);
REQUIRE(words[1].first == "world");
REQUIRE(words[1].second == 1);
}

SECTION("Save and load") {
dict.addWord("hello");
dict.addWord("world");
dict.saveToFile("test_dict.txt");

Dictionary newDict;
newDict.loadFromFile("test_dict.txt");
auto words = newDict.getWordsAlphabetically();
REQUIRE(words.size() == 2);
REQUIRE(words[0].first == "hello");
REQUIRE(words[0].second == 1);
REQUIRE(words[1].first == "world");
REQUIRE(words[1].second == 1);
}
}

