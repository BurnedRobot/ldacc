#ifndef LDACC_LDA_H_
#define LDACC_LDA_H_
#include "../include/stdafx.h"

class LDA
{
private:
    // basic parameters of lda model 
    int topics_num;         // total number of topics
    double alpha;
    double beta;
    int iter_num;           // total number of iteration

    // this parameters will not be initialized until call InitModel method.
    int docs_num;           // total number of docs
    int words_num;          // total number of words

    
    WORDS_MATRIX* p_words_matrix;
    WORDS_BAG* p_words_bag;
    THETA_MATRIX* p_theta_matrix;
    PHI_MATRIX* p_phi_matrix;

    bool ready = false;     // ready to training ?


    // uncopiale
    LDA(const LDA&) = delete ;
    LDA& operator = (const LDA& ) = delete;
public:
    
    LDA(int topic, double alpha, double beta, int iter):
        topics_num(topic), alpha(alpha), beta(beta), iter_num(iter),
        docs_num(0), words_num(0){}

    // Init model by specifying the input data documents.
    void InitModel(const char* inputfile);
    void Training();

};


#endif 

