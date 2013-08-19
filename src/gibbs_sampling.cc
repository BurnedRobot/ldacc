#include "../include/gibbs_sampling.h"
#include "../include/utils.h"
#include <vector>
#include <algorithm>
#include <string>
#include <set>
#include <ctime>

const int kTopics = 10;
// 
int g_documents = 0;
std::vector<std::vector<std::string> > g_word_matrix;
std::set<std::string> g_bag_of_words;

static std::vector<std::vector<int> > topic_count_matrix;

void InitSampling(int num_of_docs,
                  int num_of_topics,
                  std::vector<std::vector<std::string> >& word_matrix)
{
    topic_count_matrix.resize(num_of_docs);
    for_each(topic_count_matrix.begin(), topic_count_matrix.end(),
             [](std::vector<int>& vt){ vt.resize(kTopics); });
    
    srand((unsigned)time(0));
    for_each(topic_count_matrix.begin(), topic_count_matrix.end(),
             [](std::vector<int>& vt){
                 generate(vt.begin(), vt.end(), []{ return rand()%kTopics; });
             });
    
    for_each(topic_count_matrix.begin(), topic_count_matrix.end(),
             print_container<std::vector<int>, int>(std::cout));
}
