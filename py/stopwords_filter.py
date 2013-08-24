#! /usr/bin/python3
#! -*- encoding:utf-8 -*- 

STOPWORDS_PATH = "../data/stopwords.txt"


def read_stopwords(inputfile):
    stopwords_set = set()
    stopwords_set.add('')
    stopwords_set.add('\t')
    stopwords_set.add('\n')
    stopwords_set.add(' ')
    
    ifile = open(inputfile, "r", encoding = "utf-8")
    for line in ifile:
        word = line.split()
        temp = word[0].strip()
        if temp not in stopwords_set:
            stopwords_set.add(temp)

    return stopwords_set
    #print(len(stopwords_set))


class Filter(object):
    def __init__(self):
        self.__stopwords_set = read_stopwords(STOPWORDS_PATH)

    def filter(self, word_list):
        for word in word_list:
            if word in self.__stopwords_set:
                word_list.remove(word)       
        return word_list

if "__main__" == __name__:
    print(read_stopwords(STOPWORDS_PATH))
