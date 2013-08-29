#ifndef LDACC_STDAFX_H_
#define LDACC_STDAFX_H_
#include <vector>
#include <string>
#include <set>
#include <map>

////////////////////////////////////////////////////////////////////
//
//  It is a matrix of word;
//      col 0   1   2   ...
//  row
//  0       word     
//  1           ...
//  2
//  ...
//
//  row is the ith of document
//  col is the jth word of ith document
//
////////////////////////////////////////////////////////////////////
typedef std::vector<std::vector<std::string> > WORDS_MATRIX;

// it is a model of bag-of-words
typedef std::set<std::string> WORDS_BAG;

// matrix of theta
typedef std::vector<std::vector<double> > THETA_MATRIX;

// matrix of phi
typedef std::vector<std::vector<std::pair<std::string, double> > > PHI_MATRIX;

typedef std::vector<std::vector<int> > Zmn_MATRIX; //topic index matrix Z_(m,n)

typedef std::vector<std::vector<int> > NKm_COUNT; //n^(k)_m

typedef std::vector<int> NKm_SUM; //n_m

typedef std::vector<std::map<std::string, int> >  NTk_COUNT; // n^(t)_k

typedef std::vector<int> NTk_SUM; //n_k
#endif
