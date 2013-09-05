#include "../include/multi_sampler.h"
#include <iostream>
#include <vector>
#include <iterator>
#include <cstdlib>
#include <ctime>
#include <algorithm>

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
//  Created Time:   2013-08-23
//
///////////////////////////////////////////////////////////////////////////////////
int GenerateMultiSample(int num_of_topics, std::vector<double>& pro_vt)
{
    std::vector<double> distri_vt;
    std::vector<double>::const_iterator iter1 = pro_vt.begin();

    double sum = 0.0;

    for(; iter1 != pro_vt.end(); ++iter1)
    {
        sum += *iter1;
        //std::cout << sum << std::endl;
        distri_vt.push_back(sum);
    }

    //copy(distri_vt.begin(), distri_vt.end(), std::ostream_iterator<double>(std::cout, " "));
    //std::cout << std::endl;

    //srand((unsigned)time(0));

    int random = rand();

    //std::cout << "random: " << random % num_of_topics << std::endl;
    double temp = ((double)random / RAND_MAX);

    //std::cout << temp << std::endl;

    auto iter_start = distri_vt.begin();
    auto iter_stop = lower_bound(distri_vt.begin(), distri_vt.end(), temp);

    //std::cout << iter_stop - iter_start << std::endl;
    return (iter_stop - iter_start);

}
