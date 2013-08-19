#ifndef LDACC_INIT_MODEL_H_
#define LDACC_INIT_MODEL_H_

#include <string>
#include <vector>
#include <set>

int ReadData(const char* filename, 
             std::vector<std::vector<std::string> >& word_matrix,
             std::set<std::string>& bag_of_words);

int GenerateMult(int k);

int Init(const char* filename,
         std::vector<std::vector<std::string> >& word_matrix,
         std::set<std::string>& bag_of_words);
         

#endif
