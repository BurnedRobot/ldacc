#include "../include/utils.h"
#include "../include/init_model.h"
#include "../include/gibbs_sampling.h"
#include <vector>
#include <string>
#include <set>
#include <algorithm>

const int kTopics = 10;
const double alpha = 0.001;
const double beta = 0.005;
const int kIterNum = 1000;

int main(int argc, char* argv[])
{
    std::vector<std::vector<std::string> >* p_word_matrix = new std::vector<std::vector<std::string> >;
    std::set<std::string>* p_bag_of_words = new std::set<std::string>;

    int documents_count = Init("../data/text.dat", *p_word_matrix, *p_bag_of_words);
    
    for_each(p_word_matrix->begin(), p_word_matrix->end(), 
             [](std::vector<std::string>& vt){ 
                 print_container<std::vector<std::string>, std::string>pc(std::cout);
                 pc(vt);});
    std::cout << std::endl;

    copy(p_bag_of_words->begin(), p_bag_of_words->end(),
         std::ostream_iterator<std::string>(std::cout, " "));
    std::cout << std::endl;
    std::cout << std::endl;

//    InitSampling(documents_count, kTopics, *p_word_matrix);   
    GibbsSampling(documents_count, kTopics, p_bag_of_words->size(), alpha, beta, kIterNum, *p_word_matrix);
    delete p_bag_of_words;
    delete p_word_matrix;

    return 0;
}
