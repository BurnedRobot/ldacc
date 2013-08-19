#ifndef LDACC_GIBBS_SAMPLING_H_
#define LDACC_GIBBS_SAMPLING_H_

#include <vector>
#include <string>

void InitSampling(int num_of_docs, 
                  int num_of_topics,
                  std::vector<std::vector<std::string> >& word_matrix);

void GibbsSampling();
#endif
