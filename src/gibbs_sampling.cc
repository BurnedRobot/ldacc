#include "../include/gibbs_sampling.h"
#include "../include/utils.h"
#include <vector>
#include <algorithm>
#include <string>
#include <set>
#include <map>
#include <ctime>
#include <cstdlib>


static std::vector<std::vector<int> > topic_index_Zmn; //z_(m,n)
static std::vector<std::vector<int> > doc_topic_count;//n^(k)_m
static std::vector<int> doc_topic_sum_Nm;//n_m


////////////////////////////////////////////////////////////////////////////////////
//
//  Function:       InitTopicIndex
//                  Sample topic index z_(m,n) = k ~ Mult(1/K)
//  Parameters:     num_of_docs: total number of documents M
//                  num_of_topics: total number of topics K
//                  word_matrix: word vector reference stores the read data. {w}
//                               It is a vector whose element is a vector of string.
//  Return Value:   void
//
//  Author:         BurnedRobot
//  Email:          robotflying777@gmail.com
//  Created Time:   2013-08-19
//
///////////////////////////////////////////////////////////////////////////////////
static void InitTopicIndex(const int num_of_docs,
                           const int num_of_topics,
                           const std::vector<std::vector<std::string> >& word_matrix)
{
    topic_index_Zmn.resize(num_of_docs);

    std::vector<std::vector<int> >::iterator z_mn_iter = topic_index_Zmn.begin();
    std::vector<std::vector<std::string> >::const_iterator word_matrix_iter = word_matrix.begin();
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


////////////////////////////////////////////////////////////////////////////////////
//
//  Function:       InitCountVariables
//                  Init all count variables
//  Parameters:     num_of_docs: total number of documents M
//                  num_of_topics: total number of topics K
//                  word_matrix: word vector reference stores the read data. {w}
//                               It is a vector whose element is a vector of string.
//  Return Value:   void
//
//  Author:         BurnedRobot
//  Email:          robotflying777@gmail.com
//  Created Time:   2013-08-19
//
///////////////////////////////////////////////////////////////////////////////////
static void InitCountVariables(const int num_of_docs,
                               const int num_of_topics,
                               const std::vector<std::vector<std::string> >& word_matrix)
{
    // Init document-topic count: n^(k)_m
    doc_topic_count.resize(num_of_docs);
    for_each(doc_topic_count.begin(), doc_topic_count.end(),
             [&](std::vector<int>& vt){ vt.resize(num_of_topics); });
    
    // Init document-topic sum: n_m
    doc_topic_sum_Nm.resize(num_of_docs);
}
////////////////////////////////////////////////////////////////////////////////////
//
//  Function:       IncreDocTopicCount
//                  Increment document-topic count: n^(k)_m += 1
//  Parameters:     index_doc: document index of word_matrix
//                  index_word: word index of word_matrix
//                  word_matrix: word vector reference stores the read data. {w}
//                               It is a vector whose element is a vector of string.
//  Return Value:   void
//
//  Author:         BurnedRobot
//  Email:          robotflying777@gmail.com
//  Created Time:   2013-08-19
//
///////////////////////////////////////////////////////////////////////////////////
inline static int IncreDocTopicCount(const std::size_t index_doc,
                                   const std::size_t index_word,
                                   const std::vector<std::vector<std::string> >& word_matrix)
{
    int i = topic_index_Zmn[index_doc][index_word];
    doc_topic_count[index_doc][i]++;
}

////////////////////////////////////////////////////////////////////////////////////
//
//  Function:       InitSampling
//                  Do some initialization before gibbs sampling.
//  Parameters:     num_of_docs: total number of documents M
//                  num_of_topics: total number of topics K
//                  word_matrix: word vector reference stores the read data. {w}
//                               It is a vector whose element is a vector of string.
//  Return Value:   void
//
//  Author:         BurnedRobot
//  Email:          robotflying777@gmail.com
//  Created Time:   2013-08-19
//
///////////////////////////////////////////////////////////////////////////////////
void InitSampling(const int num_of_docs,
              const int num_of_topics,
              const std::vector<std::vector<std::string> >& word_matrix)
{
    if(0 == num_of_docs && num_of_docs != word_matrix.size())
    {
        std::fprintf(stderr,"Numbers of Documents Error!\n");
        std::exit(0);
    }
    
    InitCountVariables(num_of_docs, num_of_topics, word_matrix);

    InitTopicIndex(num_of_docs, num_of_topics, word_matrix);

    for(std::size_t index_doc = 0; index_doc < topic_index_Zmn.size(); ++index_doc)
    {
        for(std::size_t index_word = 0; index_word < topic_index_Zmn[index_doc].size(); ++index_word)
        {
            IncreDocTopicCount(index_doc, index_word, word_matrix);
            doc_topic_sum_Nm[index_doc]++;
        }
    }


    for_each(doc_topic_count.begin(), doc_topic_count.end(),
             print_container<std::vector<int>, int>(std::cout));
    std::cout << std::endl;
    copy(doc_topic_sum_Nm.begin(), doc_topic_sum_Nm.end(),
         std::ostream_iterator<int>(std::cout, " "));
    std::cout << std::endl;
}
