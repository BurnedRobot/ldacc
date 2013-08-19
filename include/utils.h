#ifndef UNVIERSE_UTILS_H_
#define UNVIERSE_UTILS_H_

#include <cstdio>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <iterator>
#include <set>

template<typename T, typename W>
struct print_container
{
    std::ostream& pos;

    print_container(std::ostream& os):pos(os){}
    void operator() (const T& container)
    {
        std::ostream_iterator<W> os_iter(pos, " ");
        std::copy(container.begin(), container.end(), os_iter);
        std::cout << std::endl;
    }
};


void FillWordVector(const std::string& line, 
                    std::vector<std::string>& v_word,
                    std::set<std::string>& bag_of_words);


#endif
