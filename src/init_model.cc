#include "../include/init_model.h"
#include "../include/utils.h"
#include <fstream>
#include <ctime>


////////////////////////////////////////////////////////////////////////////////////
//
//  Function:       ReadData
//                  Read data from text document.
//  Parameters:     filename: file to be read.
//                  word_matrix: Word vector reference to store the read data. {w}
//                               It is a vector whose element is a vector of string.
//                  bag_of_words: A set reference to store the parsered words.
//                                It is the implement of bag-of-words model.
//  Return Value:   (int) number of documents. M
//
//  Author:         BurnedRobot
//  Email:          robotflying777@gmail.com
//  Created Time:   2013-08-18
//
///////////////////////////////////////////////////////////////////////////////////
int ReadData(const char* filename, 
             std::vector<std::vector<std::string> >& word_matrix,
             std::set<std::string>& bag_of_words)
{
    std::ifstream ifile(filename);
    std::string line;
    int count = 0;
    
    while(std::getline(ifile, line))
    {
        if(line.empty())
            continue;
        count++ ;
        std::vector<std::string> temp_vector;
        FillWordVector(line, temp_vector, bag_of_words);
        word_matrix.push_back(temp_vector);
    }

    ifile.close();
    return count;
}


inline int GenerateMult(int k)
{
    srand((unsigned)time(0));
    return rand()%k;
}


////////////////////////////////////////////////////////////////////////////////////
//
//  Function:       Init
//                  Init LDA model.
//  Parameters:     filename: file to be read.
//                  word_matrix: Word vector reference to store the read data. {w}
//                               It is a vector whose element is a vector of string.
//                  bag_of_words: A set reference to store the parsered words.
//                                It is the implement of bag-of-words model.
//  Return Value:   (int) number of documents. M
//
//  Author:         BurnedRobot
//  Email:          robotflying777@gmail.com
//  Created Time:   2013-08-18
//
///////////////////////////////////////////////////////////////////////////////////
int Init(const char* filename,
         std::vector<std::vector<std::string> >& word_matrix,
         std::set<std::string>& bag_of_words)
{
    return ReadData(filename, word_matrix, bag_of_words);
}
