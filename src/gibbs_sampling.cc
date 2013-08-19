#include "../include/gibbs_sampling.h"
#include "../include/utils.h"
#include <vector>
#include <algorithm>
#include <string>
#include <set>
#include <map>
#include <ctime>
#include <cstdlib>


static std::vector<std::vector<int> > topic_index_Zmn;
static std::vector<std::vector<int> > document_topic_count;
static std::vector<int> document_topic_sum_Nm;


static void InitTopicIndex(int num_of_docs,
                           int num_of_topics,
                           std::vector<std::vector<std::string> >& word_matrix)
{
    topic_index_Zmn.resize(num_of_docs);

    std::vector<std::vector<int> >::iterator z_mn_iter = topic_index_Zmn.begin();
    std::vector<std::vector<std::string> >::iterator word_matrix_iter = word_matrix.begin();
    for(; z_mn_iter != topic_index_Zmn.end(); ++z_mn_iter, ++word_matrix_iter)
        (*z_mn_iter).resize((*word_matrix_iter).size());
   
    srand((unsigned)time(0));
    for_each(topic_index_Zmn.begin(), topic_index_Zmn.end(),
             [&](std::vector<int>& vt) {
                 generate(vt.begin(), vt.end(), [&]{ return rand()%num_of_topics; });
             });
    
    for_each(topic_index_Zmn.begin(), topic_index_Zmn.end(),
             print_container<std::vector<int>, int>(std::cout));
    std::cout << std::endl;
}


static void InitDocumentTopicCount(int num_of_docs, int num_of_topics)
{
    document_topic_count.resize(num_of_docs);
    document_topic_sum_Nm.resize(num_of_docs);

    for_each(document_topic_count.begin(), document_topic_count.end(),
             [&](std::vector<int>& vt){ vt.resize(num_of_topics); });

    for(std::size_t index_row = 0; index_row < topic_index_Zmn.size(); ++index_row)
    {
        for(std::size_t index_col = 0; index_col < topic_index_Zmn[index_row].size(); ++index_col)
        {
            int i = topic_index_Zmn[index_row][index_col];
            document_topic_count[index_row][i]++;

            document_topic_sum_Nm[index_row]++;
        }
    }

    for_each(document_topic_count.begin(), document_topic_count.end(),
             print_container<std::vector<int>, int>(std::cout));
    std::cout << std::endl;
    copy(document_topic_sum_Nm.begin(), document_topic_sum_Nm.end(),
         std::ostream_iterator<int>(std::cout, " "));
    std::cout << std::endl;
}


void InitSampling(int num_of_docs,
                  int num_of_topics,
                  std::vector<std::vector<std::string> >& word_matrix)
{
    if(0 == num_of_docs && num_of_docs != word_matrix.size())
    {
        std::fprintf(stderr,"Numbers of Documents Error!\n");
        std::exit(0);
    }

    InitTopicIndex(num_of_docs, num_of_topics, word_matrix);
    InitDocumentTopicCount(num_of_docs, num_of_topics);
}
