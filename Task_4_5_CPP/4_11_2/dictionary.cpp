// dictionary.cpp
#include "dictionary.h"
#include <fstream>
#include <iostream>
#include <algorithm>

void Dictionary::addWord(const std::string& word) {
    word_count[word]++;
}

void Dictionary::addWordsFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file) {
        std::cerr << "Ошибка открытия файла: " << filename << std::endl;
        return;
    }

    std::string word;
    while (file >> word) {
        addWord(word);
    }
    file.close();
}

void Dictionary::saveToFile(const std::string& filename) {
    std::ofstream file(filename);
    if (!file) {
        std::cerr << "Ошибка открытия файла для записи: " << filename << std::endl;
        return;
    }

    for (const auto& entry : word_count) {
        file << entry.first << " " << entry.second << std::endl;
    }
    file.close();
}

void Dictionary::loadFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file) {
        std::cerr << "Ошибка открытия файла: " << filename << std::endl;
        return;
    }

    word_count.clear();

    std::string word;
    int count;
    while (file >> word >> count) {
        word_count[word] = count;
    }
    file.close();
}

std::vector<std::pair<std::string, int>> Dictionary::getWordsAlphabetically() const {
    std::vector<std::pair<std::string, int>> words(word_count.begin(), word_count.end());
    return words;
}

std::vector<std::pair<std::string, int>> Dictionary::getWordsByFrequency() const {
    std::vector<std::pair<std::string, int>> words(word_count.begin(), word_count.end());
    std::sort(words.begin(), words.end(), [](const auto& a, const auto& b) {
        return b.second < a.second;
    });
    return words;
}
