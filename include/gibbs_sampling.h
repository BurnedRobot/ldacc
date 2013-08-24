#ifndef LDACC_GIBBS_SAMPLING_H_
#define LDACC_GIBBS_SAMPLING_H_

#include <vector>
#include <string>
#include <map>

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
                  const std::vector<std::vector<std::string> >& word_matrix);

////////////////////////////////////////////////////////////////////////////////////
//
//  Function:       GibbsSampling
//  Parameters:     num_of_docs: total number of documents M
//                  num_of_topics: total number of topics K
//                  num_of_words: total number of words V
//                  alpha: hyperparameter alpha
//                  beta:  hyperparameter beta
//                  word_matrix: word vector reference stores the read data. {w}
//                               It is a vector whose element is a vector of string.
//  Return Value:   void
//
//  Author:         BurnedRobot
//  Email:          robotflying777@gmail.com
//  Created Time:   2013-08-19
//  Modified:       2013-08-23 add a parameter: num_of_words
//
///////////////////////////////////////////////////////////////////////////////////
void GibbsSampling(const int num_of_docs,
                   const int num_of_topics,
                   const std::size_t num_of_words,
                   const double alpha,
                   const double beta,
                   const int iter_num,
                   const std::vector<std::vector<std::string> >& word_matrix);


////////////////////////////////////////////////////////////////////////////////////
//
//  Function:       EstimateTheta
//  Parameters:     num_of_docs: total number of documents M
//                  num_of_topics: total number of topics K
//                  alpha: hyperparameter alpha
//                  beta:  hyperparameter beta
//                  theta: a vector to store the result of theta
//  Return Value:   void
//
//  Author:         BurnedRobot
//  Email:          robotflying777@gmail.com
//  Created Time:   2013-08-24
//
///////////////////////////////////////////////////////////////////////////////////
void EstimateTheta(int num_of_docs, int num_of_topics, double alpha, double beta,
                    std::vector<std::vector<double> >& theta);


////////////////////////////////////////////////////////////////////////////////////
//
//  Function:       EstimatePhi
//  Parameters:     num_of_topics: total number of topics K
//                  num_of_words:  total number of words V
//                  alpha: hyperparameter alpha
//                  beta:  hyperparameter beta
//                  phi: a vector to store the result of phi 
//  Return Value:   void
//
//  Author:         BurnedRobot
//  Email:          robotflying777@gmail.com
//  Created Time:   2013-08-24
//
///////////////////////////////////////////////////////////////////////////////////
void EstimatePhi(int num_of_topics, int num_of_words, double alpha, double beta,
                    std::vector<std::map<std::string, double> >& phi);
#endif
