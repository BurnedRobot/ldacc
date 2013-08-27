#include "../include/lda.h"
#include "../include/init_model.h"

void  LDA::InitModel(const char* inputfile)
{
    docs_num = ReadData("../data/document.dat", *p_words_matrix, *p_words_bag);
}

void LDA::Training()
{
}
