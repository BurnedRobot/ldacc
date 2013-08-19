#include "../include/init_model.h"
#include "../include/utils.h"
#include <fstream>
#include <ctime>


int ReadData(const char* filename, 
             std::vector<std::vector<std::string> >& word_matrix,
             std::set<std::string>& bag_of_words)
{
    std::ifstream ifile(filename);
    std::string line;
    int count = 0;
    
    while(std::getline(ifile, line))
    {
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


int Init(const char* filename,
         std::vector<std::vector<std::string> >& word_matrix,
         std::set<std::string>& bag_of_words)
{
    return ReadData(filename, word_matrix, bag_of_words);
}
