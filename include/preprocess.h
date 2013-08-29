#ifndef LDACC_INIT_MODEL_H_
#define LDACC_INIT_MODEL_H_

#include <string>
#include <vector>
#include <set>

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
             std::set<std::string>& bag_of_words);

#endif
