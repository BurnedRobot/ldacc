#include "../include/utils.h"
#include <fstream>
#include <sstream>

////////////////////////////////////////////////////////////////////////////////////
//
//  Function:       FillWordVector
//                  Pareser a line of words.
//  Parameters:     line: A line of words to parser.
//                  v_word: Word vector reference to store the parsered words. {w}
//                  bag_of_words: A set reference to store the parsered words.
//                                It is the implement of bag-of-words model.
//  Return Value:   void
//
//  Author:         BurnedRobot
//  Email:          robotflying777@gmail.com
//  Created Time:   2013-08-18
//
///////////////////////////////////////////////////////////////////////////////////
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
