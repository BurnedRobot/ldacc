#include "../include/utils.h"
#include <fstream>
#include <sstream>

void FillWordVector(const std::string& line, 
                    std::vector<std::string>& word_vector,
                    std::set<std::string>& bag_of_words)
{
    std::stringstream strstream(line);
    std::string tempword;

    while(strstream >> tempword)
    {
        word_vector.push_back(tempword);
        if(bag_of_words.end() == bag_of_words.find(tempword))
            bag_of_words.insert(tempword);
    }

}
