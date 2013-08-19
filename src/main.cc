#include "../include/utils.h"
#include "../include/init_model.h"
#include "../include/gibbs_sampling.h"
#include <vector>
#include <string>
#include <set>
#include <algorithm>

extern int g_documents;
extern std::vector<std::vector<std::string> > g_word_matrix;
extern std::set<std::string> g_bag_of_words;


int main(int argc, char* argv[])
{
    g_documents = Init("../data/text.dat", g_word_matrix, g_bag_of_words);
    
    for_each(g_word_matrix.begin(), g_word_matrix.end(), 
             [](std::vector<std::string>& vt){ 
                 print_container<std::vector<std::string>, std::string>pc(std::cout);
                 pc(vt);});
    std::cout << std::endl;

    copy(g_bag_of_words.begin(), g_bag_of_words.end(),
         std::ostream_iterator<std::string>(std::cout, " "));
    std::cout << std::endl;
    std::cout << std::endl;

    InitSampling(g_documents, kTopics, g_word_matrix);   
    return 0;
}
