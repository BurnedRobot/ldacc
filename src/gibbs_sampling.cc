#include "../include/gibbs_sampling.h"
#include "../include/utils.h"
#include <vector>
#include <algorithm>
#include <string>
#include <set>
#include <map>
#include <ctime>
#include <cstdlib>

const int kNumofLocalVar = 5;

static std::vector<std::vector<int> > topic_index_Zmn; //z_(m,n)
static std::vector<std::vector<int> > doc_topic_count;//n^(k)_m
static std::vector<int> doc_topic_sum;//n_m
static std::vector<std::map<std::string, int> > topic_term_count; //n^(t)_k
static std::vector<int> topic_term_sum; // n_k


////////////////////////////////////////////////////////////////////////////////////
//
//  Function:       PrintCountVariable
//                  Print the specified count variable
//  Parameters:     var_no: to specify which count variable to print
//                          It must be one of the following numbers:
//                          0: all of the variables
//                          1: topic_index_Zmn
//                          2: doc_topic_count
//                          3: doc_topic_sum
//                          4: topic_term_count
//                          5: topic_term_sum
//                          default value is 0
//                  file:   which file to print
//                          default value is std::cout
//  Return Value:   void
//  Remark:         This function is just used to test 
//
//  Author:         BurnedRobot
//  Email:          robotflying777@gmail.com
//  Created Time:   2013-08-20
//
///////////////////////////////////////////////////////////////////////////////////
static void PrintCountVariable(int var_no = 0, std::ostream& file = std::cout)
{
    if(!(0 <= var_no && kNumofLocalVar >= var_no))
    {
        std::fprintf(stderr, "Error in PrintCountVariable! var_no is vaild!\n");
        std::exit(0);
    }

    bool all = false;
    if(0 == var_no)
        all = true;

    switch(var_no)
    {
    case 0:
    case 1:
        file << "topic index Z_(m,n):" << std::endl;
        for_each(topic_index_Zmn.begin(), topic_index_Zmn.end(),
                 print_container<std::vector<int>, int>(file));
        file << std::endl;
        if(!all) break;
    case 2:
        file << "document-topic-count n^(k)_m:" << std::endl;
        for_each(doc_topic_count.begin(), doc_topic_count.end(),
                 print_container<std::vector<int>, int>(file));
        file << std::endl;
        if(!all) break;
    case 3:
        file << "document-topic-sum n_m:" << std::endl;
        copy(doc_topic_sum.begin(), doc_topic_sum.end(),
             std::ostream_iterator<int>(file, " "));
        file << std::endl;
        file << std::endl;
        if(!all) break;
    case 4:
        {
            file << "topic-term-count n^(t)_k:" << std::endl;
            std::vector<std::map<std::string, int> >::const_iterator iter = topic_term_count.begin();
            std::map<std::string, int>::const_iterator itmap = iter->begin();
            for(; iter != topic_term_count.end(); ++iter)
            {
                file << iter - topic_term_count.begin() << std::endl;
                for(itmap = iter->begin(); itmap != iter->end(); ++itmap)
                {
                   file  << itmap->first << ":" << itmap->second << " " << std::endl;
                }
                file << std::endl;
            }
        }
        if(!all) break;
    case 5:
        file << "topic-term-sum n_k:" << std::endl;
        copy(topic_term_sum.begin(), topic_term_sum.end(),
             std::ostream_iterator<int>(file, " "));
        file << std::endl;
        file << std::endl;
        if(!all) break;
    }
}

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
    
    //PrintCountVariable(1);
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
    doc_topic_sum.resize(num_of_docs);

    // Init topic-term count: n^(t)_k
    topic_term_count.resize(num_of_topics);

    // Init topic-term sum: n_k
    topic_term_sum.resize(num_of_topics);
}


////////////////////////////////////////////////////////////////////////////////////
//
//  Function:       IncreDocTopicCount
//                  Increment document-topic count: n^(k)_m += 1
//                  increment document-topic sum: n_m += 1
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
inline static int IncreDocTopic(const std::size_t index_doc,
                                     const std::size_t index_word,
                                     const std::vector<std::vector<std::string> >& word_matrix)
{
    int i = topic_index_Zmn[index_doc][index_word];
    ++doc_topic_count[index_doc][i];
    ++doc_topic_sum[index_doc];   // increment document-topic sum: n_m += 1
}


////////////////////////////////////////////////////////////////////////////////////
//
//  Function:       IncreTopicTerm
//                  Increment topic-term count: n^(t)_k += 1
//                  Increment topic-term sum: n_k += 1
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
inline static int IncreTopicTerm(const std::size_t index_doc,
                                     const std::size_t index_word,
                                     const std::vector<std::vector<std::string> >& word_matrix)
{
    int i = topic_index_Zmn[index_doc][index_word];
    std::string term = word_matrix[index_doc][index_word];
    ++topic_term_count[i][term];
    ++topic_term_sum[i];
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
            IncreDocTopic(index_doc, index_word, word_matrix);
            IncreTopicTerm(index_doc, index_word, word_matrix);
        }
    }


    //PrintCountVariable(2);
    //PrintCountVariable(3);
    //PrintCountVariable(4);
    //PrintCountVariable(5);
}


////////////////////////////////////////////////////////////////////////////////////
//
//  Function:       DecreDocTopicCount
//                  Decrement document-topic count: n^(k)_m -= 1
//                  Decrement document-topic sum: n_m -= 1
//  Parameters:     index_doc: document index of word_matrix
//                  index_word: word index of word_matrix
//                  word_matrix: word vector reference stores the read data. {w}
//                               It is a vector whose element is a vector of string.
//  Return Value:   void
//
//  Author:         BurnedRobot
//  Email:          robotflying777@gmail.com
//  Created Time:   2013-08-20
//
///////////////////////////////////////////////////////////////////////////////////
inline static int DecreDocTopic(const std::size_t index_doc,
                                     const std::size_t index_word,
                                     const std::vector<std::vector<std::string> >& word_matrix)
{
    int i = topic_index_Zmn[index_doc][index_word];
    //std::printf("index_doc:%d\tindex_word:%d\ti:%d\n", index_doc, index_word, i);
    --doc_topic_count[index_doc][i];
    --doc_topic_sum[index_doc];   // increment document-topic sum: n_m -= 1
}


////////////////////////////////////////////////////////////////////////////////////
//
//  Function:       DecreTopicTerm
//                  Decrement topic-term count: n^(t)_k -= 1
//                  Decrement topic-term sum: n_k -= 1
//  Parameters:     index_doc: document index of word_matrix
//                  index_word: word index of word_matrix
//                  word_matrix: word vector reference stores the read data. {w}
//                               It is a vector whose element is a vector of string.
//  Return Value:   void
//
//  Author:         BurnedRobot
//  Email:          robotflying777@gmail.com
//  Created Time:   2013-08-20
//
///////////////////////////////////////////////////////////////////////////////////
inline static int DecreTopicTerm(const std::size_t index_doc,
                                     const std::size_t index_word,
                                     const std::vector<std::vector<std::string> >& word_matrix)
{
    int i = topic_index_Zmn[index_doc][index_word];
    std::string term = word_matrix[index_doc][index_word];
    //std::printf("term:%s\n",term.c_str());
    --topic_term_count[i][term];
    --topic_term_sum[i];
}


////////////////////////////////////////////////////////////////////////////////////
//
//  Function:       GibbsSampling
//  Parameters:     num_of_docs: total number of documents M
//                  num_of_topics: total number of topics K
//                  alpha: hyperparameter alpha
//                  beta:  hyperparameter beta
//                  word_matrix: word vector reference stores the read data. {w}
//                               It is a vector whose element is a vector of string.
//  Return Value:   void
//
//  Author:         BurnedRobot
//  Email:          robotflying777@gmail.com
//  Created Time:   2013-08-19
//
///////////////////////////////////////////////////////////////////////////////////
void GibbsSampling(const int num_of_docs,
                   const int num_of_topics,
                   const double alpha,
                   const double beta,
                   const int iter_num,
                   const std::vector<std::vector<std::string> >& word_matrix)
{
    InitSampling(num_of_docs, num_of_topics, word_matrix);

    PrintCountVariable(0);
    //PrintCountVariable(2);
    //PrintCountVariable(3);
    //PrintCountVariable(4);
    //PrintCountVariable(5);

    int count = 999;
    while(count < iter_num)
    {
        count++;
        for(std::size_t index_doc = 0; index_doc < word_matrix.size(); ++index_doc)
        {
            for(std::size_t index_word = 0; index_word < word_matrix[index_doc].size(); ++index_word)
            {
                //PrintCountVariable(2);
                //PrintCountVariable(3);
                //PrintCountVariable(4);
                //PrintCountVariable(5);
                DecreDocTopic(index_doc, index_word, word_matrix);
                DecreTopicTerm(index_doc, index_word, word_matrix);
                //PrintCountVariable(2);
                //PrintCountVariable(3);
                //PrintCountVariable(4);
                //PrintCountVariable(5);
                break;
            }
            break;
        }

    }

    PrintCountVariable(0);
}
