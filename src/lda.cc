#include "../include/lda.h"
#include "../include/preprocess.h"
#include "../include/multi_sampler.h"
#include "../include/utils.h"
#include <cstdlib>
#include <algorithm>
#include <ctime>

void  LDA::Init(const char* inputfile)
{

    docs_num = ReadData("../data/document.dat", words_matrix, words_bag);

    if(0 == docs_num && docs_num != words_matrix.size())
    {
        std::fprintf(stderr,"Numbers of Documents Error!\n");
        std::exit(0);
    }

    InitCountVariables();
    InitTopicIndex();

    for(int index_doc = 0; index_doc < docs_num; index_doc++)
        for(int index_word = 0; index_word < words_matrix[index_doc].size(); index_word++)
            IncreCountVariables(index_doc, index_word);

    b_ready = true;
}


void LDA::InitCountVariables()
{
    
    NKm_count.resize(docs_num);
    for_each(NKm_count.begin(), NKm_count.end(),
             [&](std::vector<int>& vt){ vt.resize(topics_num); });

    NKm_sum.resize(docs_num);

    NTk_count.resize(topics_num);

    NTk_sum.resize(topics_num);
    
}


void LDA::InitTopicIndex()
{

    Zmn.resize(docs_num);

    int count = 0;
    for_each(Zmn.begin(), Zmn.end(),
            [&](std::vector<int>& vt){
                vt.resize(words_matrix[count++].size());
            });

    srand((unsigned)time(0));

    std::vector<double> pro_vt(topics_num);
    std::fill(pro_vt.begin(), pro_vt.end(), (double)(1.0)/topics_num);

    for_each(Zmn.begin(), Zmn.end(),
             [&](std::vector<int>& vt) {
                 generate(vt.begin(), vt.end(), [&]{ return GenerateMultiSample(topics_num, pro_vt); });
             });
}



///////////////////////////////////////////////////////////////////////////////////////////////////////////////
void LDA::IncreCountVariables(std::size_t index_doc, std::size_t index_word)
{
    int i = Zmn[index_doc][index_word];
    (NKm_count)[index_doc][i]++ ;
    (NKm_sum)[index_doc]++;

    std::string term = words_matrix[index_doc][index_word];
    (NTk_count)[i][term]++;
    (NTk_sum)[i]++;
}


void LDA::DecreCountVariables(std::size_t index_doc, std::size_t index_word)
{
    int i = Zmn[index_doc][index_word];
    (NKm_count)[index_doc][i]-- ;
    (NKm_sum)[index_doc]--;

    std::string term = words_matrix[index_doc][index_word];
    (NTk_count)[i][term]--;
    (NTk_sum)[i]--;
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void LDA::Training()
{
    if(!b_ready)
        std::fprintf(stderr, "Init Error!\n");
    //PrintZmn();
    GibbsSampling();
    EstimateTheta();
    EstimatePhi();
}


void LDA::GibbsSampling()
{
    int count = 0;
    while(count < iter_num)
    {
        count++;
        for(std::size_t index_doc = 0; index_doc < words_matrix.size(); ++index_doc)
        {
            for(std::size_t index_word = 0; index_word < words_matrix[index_doc].size(); ++index_word)
            {
                //std::cout << "word: " << words_matrix[index_doc][index_word] << std::endl;
                DecreCountVariables(index_doc, index_word);

                Zmn[index_doc][index_word] = UpdateTopic(index_doc, index_word);

                IncreCountVariables(index_doc, index_word);
                //break;
            }
            //break;
        }

    }

}


int LDA::UpdateTopic(std::size_t index_doc, std::size_t index_word)
{
    int k = Zmn[index_doc][index_word];

    std::string term = words_matrix[index_doc][index_word];
    //std::cout << "Change Topic is " << k << std::endl;
    std::vector<double> temp_vt;
    for(k = 0; k < topics_num; k++) 
    {
        double denominator = 0.0;
        denominator = ((NTk_sum)[k] + words_num * beta) * ((NKm_sum)[index_doc] + topics_num * alpha);

        double numerator = 0.0;
        numerator = ((NTk_count)[k][term] + beta)*((NKm_count)[index_doc][k] + alpha);

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
    theta_matrix.resize(docs_num);

    for(int i = 0; i < docs_num; i++)
    {
        (theta_matrix)[i].resize(topics_num);
        for(int j = 0; j < topics_num; j++)
        {
            (theta_matrix)[i][j] = ((NKm_count)[i][j] + alpha) / ((NKm_sum)[i] + alpha * topics_num);
        }
    }

}

void LDA::EstimatePhi()
{
    phi_matrix.resize(topics_num);
    
    std::map<std::string, int>::const_iterator iter;
    for(int i = 0; i < topics_num; i++)
    {
        for(iter = (NTk_count)[i].begin(); iter != (NTk_count)[i].end(); ++iter)
        {
            double phi_value = (static_cast<double>(iter->second) + beta) / ((NTk_sum)[i] + beta * words_num);
            
            (phi_matrix)[i].push_back(make_pair(iter->first, phi_value));
        }
        std::sort((phi_matrix)[i].begin(), (phi_matrix)[i].end(), 
                  [&](const std::pair<std::string, double>& x, const std::pair<std::string, double>& y) -> bool
                  {
                      return !(x.second <= y.second);
                  });
            
    }
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const THETA_MATRIX& LDA::GetTheta()
{
    return theta_matrix;
}


const PHI_MATRIX& LDA::GetPhi()
{
    return phi_matrix;
}


