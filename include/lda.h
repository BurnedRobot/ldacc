#ifndef LDACC_LDA_H_
#define LDACC_LDA_H_
#include "../include/stdafx.h"

class LDA
{
private:
    // basic parameters of lda model 
    int     topics_num;         // total number of topics
    double  alpha; 
    double  beta;
    int     iter_num;           // total number of iteration

    // this parameters will not be initialized until call Init method.
    int     docs_num;           // total number of docs
    int     words_num;          // total number of words


    //
    Zmn_MATRIX  Zmn; 
    NKm_COUNT   NKm_count; 
    NKm_SUM     NKm_sum;
    NTk_COUNT   NTk_count;
    NTk_SUM     NTk_sum;

    // 
    WORDS_MATRIX    words_matrix; 
    WORDS_BAG       words_bag;
    THETA_MATRIX    theta_matrix;
    PHI_MATRIX      phi_matrix;


    bool b_ready;     // ready to training ?

    // uncopiale
    LDA(const LDA&);
    LDA& operator = (const LDA& );

    void InitCountVariables();
    void InitTopicIndex();

    void IncreCountVariables(std::size_t index_doc, std::size_t index_word);
    void DecreCountVariables(std::size_t index_doc, std::size_t index_word);

    int  UpdateTopic(std::size_t index_doc, std::size_t index_word);
    void GibbsSampling();
    void EstimateTheta();
    void EstimatePhi();

public:
    
    LDA(int topic, double alpha, double beta, int iter):
        topics_num(topic), alpha(alpha), beta(beta), iter_num(iter),
        docs_num(0), words_num(0), b_ready(false){}


    // Init model by specifying the input data documents.
    void Init(const char* inputfile);

    // Training model.
    void Training();

    const THETA_MATRIX& GetTheta();

    const PHI_MATRIX& GetPhi();

};


#endif 

