#ifndef LDACC_MULTI_SAMPLER_H_
#define LDACC_MULTI_SAMPLER_H_

#include <vector>
////////////////////////////////////////////////////////////////////////////////////
//
//  Function:       GenerateMultiSample
//                  generate a multinomial sample
//  Parameters:     num_of_topics: total number of topics K
//                  pro_vt: a probability vector
//  Return Value:   void
//
//  Author:         BurnedRobot
//  Email:          robotflying777@gmail.com
//  Created Time:   2013-08-22
//
///////////////////////////////////////////////////////////////////////////////////
int GenerateMultiSample(int num_of_topic, std::vector<double>& pro_vt);
#endif

