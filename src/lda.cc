#include "../include/lda.h"
#include "../include/preprocess.h"
#include "../include/multi_sampler.h"
#include "../include/utils.h"
#include <cstdlib>
#include <algorithm>

void  LDA::Init(const char* inputfile)
{
    if(NULL != p_words_matrix)
    {
        delete p_words_matrix;
        p_words_matrix = new WORDS_MATRIX;
    }
    else
        p_words_matrix = new WORDS_MATRIX;

    if(NULL != p_words_bag)
    {
        delete p_words_bag;
        p_words_bag = new WORDS_BAG;
    }
    else
        p_words_bag = new WORDS_BAG;


    docs_num = ReadData("../data/document.dat", *p_words_matrix, *p_words_bag);

    if(0 == docs_num && docs_num != p_words_matrix->size())
    {
        std::fprintf(stderr,"Numbers of Documents Error!\n");
        std::exit(0);
    }

    InitCountVariables();
    InitTopicIndex();

    for(int index_doc = 0; index_doc < docs_num; index_doc++)
        for(int index_word = 0; index_word < (*p_words_matrix)[index_doc].size(); index_word++)
            IncreCountVariables(index_doc, index_word);

    b_ready = true;
}


void LDA::InitCountVariables()
{
    // Init document-topic count: n^(k)_m
    if(NULL != p_NKm_count)
    {
        delete p_NKm_count;
        p_NKm_count = new NKm_COUNT;
    }
    else
        p_NKm_count = new NKm_COUNT;
    
    p_NKm_count->resize(docs_num);
    for_each(p_NKm_count->begin(), p_NKm_count->end(),
             [&](std::vector<int>& vt){ vt.resize(topics_num); });

    // Init document-topic sum: n_m
    if(NULL != p_NKm_sum)
    {
        delete p_NKm_sum;
        p_NKm_sum = new NKm_SUM;
    }
    else
        p_NKm_sum = new NKm_SUM;
    p_NKm_sum->resize(docs_num);

    // Init topic-term count: n^(t)_k
    if(NULL != p_NTk_count)
    {
        delete p_NTk_count;
        p_NTk_count = new NTk_COUNT;
    }
    else
        p_NTk_count = new NTk_COUNT;
    p_NTk_count->resize(topics_num);

    // Init topic-term sum: n_k
    if(NULL != p_NTk_sum)
    {
        delete p_NTk_sum;
        p_NTk_sum = new NTk_SUM;
    }
    else
        p_NTk_sum = new NTk_SUM;
    p_NTk_sum->resize(topics_num);
    
<<<<<<< HEAD
}


void LDA::InitTopicIndex()
{
    if(NULL != pZmn)
        delete pZmn;
    else
        pZmn = new Zmn_MATRIX;

    pZmn->resize(docs_num);

    int count = 0;
    for_each(pZmn->begin(), pZmn->end(),
            [&](std::vector<int>& vt){
                vt.resize((*p_words_matrix)[count++].size());
            });

    srand((unsigned)time(0));

    std::vector<double> pro_vt(topics_num);
    std::fill(pro_vt.begin(), pro_vt.end(), (double)(1.0)/topics_num);

    for_each(pZmn->begin(), pZmn->end(),
             [&](std::vector<int>& vt) {
                 generate(vt.begin(), vt.end(), [&]{ return GenerateMultiSample(topics_num, pro_vt); });
             });
}


=======
}


void LDA::InitTopicIndex()
{
    if(NULL != pZmn)
        delete pZmn;
    else
        pZmn = new Zmn_MATRIX;

    pZmn->resize(docs_num);

    int count = 0;
    for_each(pZmn->begin(), pZmn->end(),
            [&](std::vector<int>& vt){
                vt.resize((*p_words_matrix)[count++].size());
            });

    srand((unsigned)time(0));

    std::vector<double> pro_vt(topics_num);
    std::fill(pro_vt.begin(), pro_vt.end(), (double)(1.0)/topics_num);

    for_each(pZmn->begin(), pZmn->end(),
             [&](std::vector<int>& vt) {
                 generate(vt.begin(), vt.end(), [&]{ return GenerateMultiSample(topics_num, pro_vt); });
             });
}


>>>>>>> 86e911966133be49a4f724483ccdbe80d7b10ab5
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
void LDA::IncreCountVariables(std::size_t index_doc, std::size_t index_word)
{
    int i = (*pZmn)[index_doc][index_word];
    (*p_NKm_count)[index_doc][i]++ ;
    (*p_NKm_sum)[index_doc]++;

    std::string term = (*p_words_matrix)[index_doc][index_word];
    (*p_NTk_count)[i][term]++;
    (*p_NTk_sum)[i]++;
}


void LDA::DecreCountVariables(std::size_t index_doc, std::size_t index_word)
{
    int i = (*pZmn)[index_doc][index_word];
    (*p_NKm_count)[index_doc][i]-- ;
    (*p_NKm_sum)[index_doc]--;

    std::string term = (*p_words_matrix)[index_doc][index_word];
    (*p_NTk_count)[i][term]--;
    (*p_NTk_sum)[i]--;
}


<<<<<<< HEAD
=======

////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void LDA::PrintZmn()
{
    std::cout << "topic index Z_(m,n):" << std::endl;
    for_each(pZmn->begin(), pZmn->end(),
             print_container<std::vector<int>, int>(std::cout));
    std::cout << std::endl;
}


>>>>>>> 86e911966133be49a4f724483ccdbe80d7b10ab5
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void LDA::Training()
{
    if(!b_ready)
        std::fprintf(stderr, "Init Error!\n");
    //PrintZmn();
    GibbsSampling();
    EstimateTheta();
    EstimatePhi();
<<<<<<< HEAD
}


void LDA::GibbsSampling()
{
    int count = 0;
    while(count < iter_num)
    {
        count++;
        for(std::size_t index_doc = 0; index_doc < (*p_words_matrix).size(); ++index_doc)
        {
            for(std::size_t index_word = 0; index_word < (*p_words_matrix)[index_doc].size(); ++index_word)
            {
                //std::cout << "word: " << (*p_words_matrix)[index_doc][index_word] << std::endl;
                DecreCountVariables(index_doc, index_word);

                (*pZmn)[index_doc][index_word] = UpdateTopic(index_doc, index_word);

                IncreCountVariables(index_doc, index_word);
                //break;
            }
            //break;
        }

    }

}


int LDA::UpdateTopic(std::size_t index_doc, std::size_t index_word)
{
    int k = (*pZmn)[index_doc][index_word];

    std::string term = (*p_words_matrix)[index_doc][index_word];
    //std::cout << "Change Topic is " << k << std::endl;
    std::vector<double> temp_vt;
    for(k = 0; k < topics_num; k++) 
    {
        double denominator = 0.0;
        denominator = ((*p_NTk_sum)[k] + words_num * beta) * ((*p_NKm_sum)[index_doc] + topics_num * alpha);

        double numerator = 0.0;
        numerator = ((*p_NTk_count)[k][term] + beta)*((*p_NKm_count)[index_doc][k] + alpha);

        double probability = numerator / denominator;
        temp_vt.push_back(probability);
    }
    double sum = std::accumulate(temp_vt.begin(), temp_vt.end(), 0.0);
    //std::cout << sum << std::endl;
    std::vector<double> pro_vt;
    for_each(temp_vt.begin(), temp_vt.end(), 
                [&](double temp)
                {
                    pro_vt.push_back(temp/sum);
                });
    //copy(pro_vt.begin(), pro_vt.end(), std::ostream_iterator<double>(std::cout, " "));

    return GenerateMultiSample(topics_num, pro_vt);
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void LDA::EstimateTheta()
{
    if(NULL != p_theta_matrix)
    {
        delete p_theta_matrix;
        p_theta_matrix = new THETA_MATRIX(docs_num);
    }else
        p_theta_matrix = new THETA_MATRIX(docs_num);

    for(int i = 0; i < docs_num; i++)
    {
        (*p_theta_matrix)[i].resize(topics_num);
        for(int j = 0; j < topics_num; j++)
        {
            (*p_theta_matrix)[i][j] = ((*p_NKm_count)[i][j] + alpha) / ((*p_NKm_sum)[i] + alpha * topics_num);
        }
    }

}

void LDA::EstimatePhi()
{
    if(NULL != p_phi_matrix)
    {
        delete p_phi_matrix;
        p_phi_matrix = new PHI_MATRIX(topics_num);
    }else
        p_phi_matrix = new PHI_MATRIX(topics_num);

    std::map<std::string, int>::const_iterator iter;
    for(int i = 0; i < topics_num; i++)
    {
        for(iter = (*p_NTk_count)[i].begin(); iter != (*p_NTk_count)[i].end(); ++iter)
        {
            double phi_value = (static_cast<double>(iter->second) + beta) / ((*p_NTk_sum)[i] + beta * words_num);
            
            (*p_phi_matrix)[i].push_back(make_pair(iter->first, phi_value));
        }
        std::sort((*p_phi_matrix)[i].begin(), (*p_phi_matrix)[i].end(), 
                  [&](const std::pair<std::string, double>& x, const std::pair<std::string, double>& y) -> bool
                  {
                      return !(x.second <= y.second);
                  });
            
    }
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////

const THETA_MATRIX& LDA::GetTheta()
{
    return *p_theta_matrix;
}


=======
}


void LDA::GibbsSampling()
{
    int count = 0;
    while(count < iter_num)
    {
        count++;
        for(std::size_t index_doc = 0; index_doc < (*p_words_matrix).size(); ++index_doc)
        {
            for(std::size_t index_word = 0; index_word < (*p_words_matrix)[index_doc].size(); ++index_word)
            {
                //std::cout << "word: " << (*p_words_matrix)[index_doc][index_word] << std::endl;
                DecreCountVariables(index_doc, index_word);

                (*pZmn)[index_doc][index_word] = UpdateTopic(index_doc, index_word);

                IncreCountVariables(index_doc, index_word);
                //break;
            }
            //break;
        }

    }

}


int LDA::UpdateTopic(std::size_t index_doc, std::size_t index_word)
{
    int k = (*pZmn)[index_doc][index_word];

    std::string term = (*p_words_matrix)[index_doc][index_word];
    //std::cout << "Change Topic is " << k << std::endl;
    std::vector<double> temp_vt;
    for(k = 0; k < topics_num; k++) 
    {
        double denominator = 0.0;
        denominator = ((*p_NTk_sum)[k] + words_num * beta) * ((*p_NKm_sum)[index_doc] + topics_num * alpha);

        double numerator = 0.0;
        numerator = ((*p_NTk_count)[k][term] + beta)*((*p_NKm_count)[index_doc][k] + alpha);

        double probability = numerator / denominator;
        temp_vt.push_back(probability);
    }
    double sum = std::accumulate(temp_vt.begin(), temp_vt.end(), 0.0);
    //std::cout << sum << std::endl;
    std::vector<double> pro_vt;
    for_each(temp_vt.begin(), temp_vt.end(), 
                [&](double temp)
                {
                    pro_vt.push_back(temp/sum);
                });
    //copy(pro_vt.begin(), pro_vt.end(), std::ostream_iterator<double>(std::cout, " "));

    return GenerateMultiSample(topics_num, pro_vt);
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void LDA::EstimateTheta()
{
    if(NULL != p_theta_matrix)
    {
        delete p_theta_matrix;
        p_theta_matrix = new THETA_MATRIX(docs_num);
    }else
        p_theta_matrix = new THETA_MATRIX(docs_num);

    for(int i = 0; i < docs_num; i++)
    {
        (*p_theta_matrix)[i].resize(topics_num);
        for(int j = 0; j < topics_num; j++)
        {
            (*p_theta_matrix)[i][j] = ((*p_NKm_count)[i][j] + alpha) / ((*p_NKm_sum)[i] + alpha * topics_num);
        }
    }

}

void LDA::EstimatePhi()
{
    if(NULL != p_phi_matrix)
    {
        delete p_phi_matrix;
        p_phi_matrix = new PHI_MATRIX(topics_num);
    }else
        p_phi_matrix = new PHI_MATRIX(topics_num);

    std::map<std::string, int>::const_iterator iter;
    for(int i = 0; i < topics_num; i++)
    {
        for(iter = (*p_NTk_count)[i].begin(); iter != (*p_NTk_count)[i].end(); ++iter)
        {
            double phi_value = (static_cast<double>(iter->second) + beta) / ((*p_NTk_sum)[i] + beta * words_num);
            
            (*p_phi_matrix)[i].push_back(make_pair(iter->first, phi_value));
        }
        std::sort((*p_phi_matrix)[i].begin(), (*p_phi_matrix)[i].end(), 
                  [&](const std::pair<std::string, double>& x, const std::pair<std::string, double>& y) -> bool
                  {
                      return !(x.second <= y.second);
                  });
            
    }
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////

const THETA_MATRIX& LDA::GetTheta()
{
    return *p_theta_matrix;
}


>>>>>>> 86e911966133be49a4f724483ccdbe80d7b10ab5
const PHI_MATRIX& LDA::GetPhi()
{
    return *p_phi_matrix;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
LDA::~LDA()
{
<<<<<<< HEAD
    if(!b_exit)
        Exit();
=======
if(!b_exit)
    Exit();
>>>>>>> 86e911966133be49a4f724483ccdbe80d7b10ab5
}


void LDA::Exit()
{
    if(NULL != pZmn)
    {
        delete pZmn;
        pZmn = NULL;
    }

    if(NULL != p_NKm_count)
    {
        delete p_NKm_count;
        p_NKm_count = NULL;
    }

    if(NULL != p_NKm_sum)
    {
        delete p_NKm_sum;
        p_NKm_sum = NULL;
    }

    if(NULL != p_NTk_count)
    {
        delete p_NTk_count;
        p_NTk_count = NULL;
    } 

    if(NULL != p_NTk_sum)
    {
        delete p_NTk_sum;
        p_NTk_sum = NULL;
    }

    // 
    if(NULL != p_words_matrix)
    {
        delete p_words_matrix;
        p_words_matrix = NULL;
    }

    if(NULL != p_words_bag)
    {
        delete p_words_bag;
        p_words_bag = NULL;
    }

    if(NULL != p_theta_matrix)
    {
        delete p_theta_matrix;
        p_theta_matrix = NULL;
    }

    if(NULL != p_phi_matrix)
    {
        delete p_phi_matrix;
        p_phi_matrix = NULL;
    } 

    b_exit = true;
}

