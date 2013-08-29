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
    int     docs_num = 0;           // total number of docs
    int     words_num = 0;          // total number of words


    //
    Zmn_MATRIX* pZmn = NULL; 
    NKm_COUNT*  p_NKm_count = NULL; 
    NKm_SUM*    p_NKm_sum = NULL;
    NTk_COUNT*  p_NTk_count = NULL;
    NTk_SUM*    p_NTk_sum = NULL;

    // 
    WORDS_MATRIX*   p_words_matrix = NULL; 
    WORDS_BAG*      p_words_bag = NULL;
    THETA_MATRIX*   p_theta_matrix = NULL;
    PHI_MATRIX*     p_phi_matrix = NULL;


    bool b_ready = false;     // ready to training ?
    bool b_exit = false;     // resources have already exited ?


    // uncopiale
    LDA(const LDA&) = delete ;
    LDA& operator = (const LDA& ) = delete;

    void InitCountVariables();
    void InitTopicIndex();

    void IncreCountVariables(std::size_t index_doc, std::size_t index_word);
    void DecreCountVariables(std::size_t index_doc, std::size_t index_word);

    int  UpdateTopic(std::size_t index_doc, std::size_t index_word);
    void GibbsSampling();
    void EstimateTheta();
    void EstimatePhi();

    void PrintZmn();
public:
    
    LDA(int topic, double alpha, double beta, int iter):
        topics_num(topic), alpha(alpha), beta(beta), iter_num(iter){}

    ~LDA();

    // Init model by specifying the input data documents.
    void Init(const char* inputfile);

    // Training model.
    void Training();

    // Exit model.
    void Exit();

    const THETA_MATRIX& GetTheta();

    const PHI_MATRIX& GetPhi();

};


#endif 

