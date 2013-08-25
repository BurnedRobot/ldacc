#! /usr/bin/python3
#! -*- encoding:utf-8 -*-

"""This package is used to segment a document
Usage: python3 segmenter.py [file (include path)]"""


import jieba
import os, sys
from ldacc_stopwords_filter import Filter

CORPUS_FILE_SPECIFIED = "../data/corpus/11.txt"


def analyze(input_file):
    ifile = open(input_file, "r", encoding = "utf-8")

    segment_result = []
    line = ""
    for temp in ifile:
        line += temp.strip()

    temp_result = list(jieba.cut(line.strip()))
    segment_result = segment_result + temp_result

    ifile.close()
    return segment_result


def main(input_file):
    fter = Filter()
    result = analyze(input_file)    
    result = fter.filter(result)
    return(result)

if "__main__" == __name__ :
    if len(sys.argv) < 2:
        print(__doc__)
        sys.exit(0)
    print(main(sys.argv[1]))
