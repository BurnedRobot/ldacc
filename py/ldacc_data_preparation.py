#! /usr/bin/python3
#! -*- encoding:utf-8 -*-

import os
import sys
from ldacc_Chinese_analyser import analyze
from ldacc_stopwords_filter import Filter

CORPUS_PATH = "../data/corpus2"
RESULT_FILE = "../data/document.dat"


def write_data(output_file, data):
    for word in data:
        #print(data, end = " ")
        print(word, end=" ", file=output_file)
    print(file = output_file)

def walk_dir(input_dir, output_file):
    ofile = open(output_file, 'w', encoding = "utf-8")
    fter = Filter()

    for i in os.listdir(input_dir):
        input_file = os.path.join(input_dir, i)
        print(input_file)
        result = fter.filter(analyze(input_file))
        write_data(ofile, result)

    ofile.close()

if "__main__" == __name__ :
    walk_dir(sys.argv[1], sys.argv[2])
