#! /usr/bin/python3
#! -*- encoding:utf-8 -*-

import jieba
import os
from stopwords_filter import Filter

CORPUS_PATH = "../corpus/change"
CORPUS_FILE_SPECIFIED = "../corpus/change/310.txt"

def list_dir(dir):
    for i in os.listdir(dir):
        file = os.path.join(dir, i)
        print(file)


def segment_file(input_file):
    ifile = open(input_file, "r", encoding = "utf-8")

    segment_result = []
    for line in ifile:
        temp_result = list(jieba.cut(line))
        segment_result = segment_result + temp_result

    return segment_result


def main(input_file):
    fter = Filter()
    result = segment_file(input_file)    
    #print(result)

    result = fter.filter(result)
    print(result)

if "__main__" == __name__ :
    #list_dir(CORPUS_PATH)
    #segment_file(CORPUS_FILE_SPECIFIED)
    main(CORPUS_FILE_SPECIFIED)
