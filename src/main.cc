#include "../include/stdafx.h"
#include "../include/utils.h"
#include "../include/preprocess.h"
#include "../include/lda.h"
#include <vector>
#include <string>
#include <set>
#include <algorithm>
#include <map>
#include <ctime>

const int kTopics = 10;
const double alpha = 50/kTopics;
const double beta = 0.1;
const int kIterNum = 1000;

int main(int argc, char* argv[])
{
    clock_t start, finish;
    double duration;
    start = clock();

    LDA lda(kTopics, alpha, beta, kIterNum);
    lda.Init("../data/document.dat");
    lda.Training();

    const THETA_MATRIX& theta = lda.GetTheta();
    const PHI_MATRIX& phi = lda.GetPhi();

    std::fprintf(stdout, "Here is theta:\n");
    for(int i = 0; i < theta.size(); i++)
    {
        for(int j = 0; j < theta[i].size(); j++)
            std::fprintf(stdout, "%lf ", theta[i][j]);
        std::fprintf(stdout, "\n");
    }
    std::fprintf(stdout, "\n");

    std::fprintf(stdout, "Here is phi:\n");
    for(int i = 0; i < phi.size(); i++)
    {
        std::fprintf(stdout,"#####################################################################\nTopic %d\n",i);
        for(int j = 0; j < 50; j++)
            std::fprintf(stdout, "%s:%lf\n", phi[i][j].first.c_str() ,phi[i][j].second);
    }

    finish = clock();
    duration = (double)(finish - start)/CLOCKS_PER_SEC;
    std::printf("Total time: %f seconds\n", duration);

    return 0;
}
