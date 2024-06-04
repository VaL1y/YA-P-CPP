//
// Created by Валерий on 02.06.2024.
//

#ifndef INC_4_11_2_DICTIONARY_H
#define INC_4_11_2_DICTIONARY_H

#include <map>
#include <string>
#include <vector>

class Dictionary {
private:
    std::map<std::string, int> word_count;

public:
    void addWord(const std::string& word);
    void addWordsFromFile(const std::string& filename);
    void saveToFile(const std::string& filename);
    void loadFromFile(const std::string& filename);
    std::vector<std::pair<std::string, int>> getWordsAlphabetically() const;
    std::vector<std::pair<std::string, int>> getWordsByFrequency() const;
};

#endif //INC_4_11_2_DICTIONARY_H
