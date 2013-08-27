#include "../include/stdafx.h"
#include "../include/utils.h"
#include "../include/init_model.h"
#include "../include/gibbs_sampling.h"
#include "../include/lda.h"
#include <vector>
#include <string>
#include <set>
#include <algorithm>
#include <map>

const int kTopics = 10;
const double alpha = 50/kTopics;
const double beta = 0.1;
const int kIterNum = 1000;

int main(int argc, char* argv[])
{
    LDA lda(kTopics, alpha, beta, kIterNum);
    lda.InitModel("../data/document.dat");
    WORDS_MATRIX* p_word_matrix = new WORDS_MATRIX;
    WORDS_BAG* p_bag_of_words = new WORDS_BAG;

    int documents_count = Init("../data/document.dat", *p_word_matrix, *p_bag_of_words);
    
    /*for_each(p_word_matrix->begin(), p_word_matrix->end(), 
             [](std::vector<std::string>& vt){ 
                 print_container<std::vector<std::string>, std::string>pc(std::cout);
                 pc(vt);});
    std::cout << std::endl;

    copy(p_bag_of_words->begin(), p_bag_of_words->end(),
         std::ostream_iterator<std::string>(std::cout, " "));
    std::cout << std::endl;
    std::cout << std::endl;*/

//    InitSampling(documents_count, kTopics, *p_word_matrix);   
    GibbsSampling(documents_count, kTopics, p_bag_of_words->size(), alpha, beta, kIterNum, *p_word_matrix);

    THETA_MATRIX* p_theta = new THETA_MATRIX(documents_count);
    PHI_MATRIX* p_phi_sorted = new PHI_MATRIX(kTopics);
    EstimateTheta(documents_count, kTopics, alpha, beta, *p_theta);
    EstimatePhi(kTopics, p_bag_of_words->size(), alpha, beta, *p_phi_sorted);

    delete p_phi_sorted;
    //delete p_phi;
    delete p_theta;
    delete p_bag_of_words;
    delete p_word_matrix;

    p_phi_sorted = NULL;
    //p_phi = NULL;
    p_theta = NULL;
    p_bag_of_words = NULL;
    p_word_matrix = NULL;
    return 0;
}
