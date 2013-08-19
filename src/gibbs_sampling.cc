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
static std::vector<std::vector<int> > document_topic_count;//n^(k)_m
static std::vector<int> document_topic_sum_Nm;//n_m


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
//  Function:       InitDocumentTopicCount
//                  Init document-topic count: n^(k)_m
//                  Init document-topic sum: n_m
//                  Init topic-term count: n^(t)_k
//                  Init topic_term sum: n_k
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
static void InitDocumentTopicCount(const int num_of_docs, const int num_of_topics)
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

    InitTopicIndex(num_of_docs, num_of_topics, word_matrix);
    InitDocumentTopicCount(num_of_docs, num_of_topics);
}
