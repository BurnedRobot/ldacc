#! /usr/bin/python3
#! -*- encoding:utf-8 -*- 

STOPWORDS_PATH = "../data/stopwords.txt"


def read_stopwords(inputfile):
    stopwords_set = set()
    stopwords_set.add('\t')
    stopwords_set.add('\n')
    stopwords_set.add(" ")
    stopwords_set.add("　")

    ifile = open(inputfile, "r", encoding = "utf-8")
    for line in ifile:
        word = line.split()
        temp = word[0].strip()
        if temp not in stopwords_set:
            stopwords_set.add(temp)

    return stopwords_set


class Filter(object):
    def __init__(self):
        self.__stopwords_set = read_stopwords(STOPWORDS_PATH)


    def filter(self, word_list):
        new_word_list = []

        for word in word_list:
            if word not in self.__stopwords_set and not word.isdecimal():
                new_word_list.append(word)       
        return new_word_list

if "__main__" == __name__:
    result = read_stopwords(STOPWORDS_PATH)
    print(result)
    print(len(result))
