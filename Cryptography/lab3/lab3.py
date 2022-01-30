import random
import string
import getopt
import os
import sys
import urllib.request

import requests

CNT_RT = 10
LEN_RT = 10 ** 6
CASES = 5

def cnt_common_letters(text1, text2):
    cnt = 0
    for char1, char2 in zip(text1, text2):
        if char1 == char2:
            cnt += 1
    return cnt


def match_percentages(text1, text2):
    return cnt_common_letters(text1, text2) / len(text1)


def letters_generator(n):
    text = ''
    while len(text) < n:
        len_word = random.randint(3, 10)
        word = ''.join(random.choice(string.ascii_letters) for _ in range(len_word))
        text += ' ' + word
    rem = len(text) - n
    if rem != 0:
        text = text[:-rem]
    return text


def words_generator(n):
    url = 'http://svnweb.freebsd.org/csrg/share/dict/words?view=co&content-type=text/plain'
    hdrs = {'User-Agent': 'Mozilla/5.0 (Macintosh; Intel Mac OS X 10_10_1) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/39.0.2171.95 Safari/537.36'}
    # response = requests.get(url, headers=headers)
    #req = urllib.request(url)
    #response = urllib.request.urlopen(url)

    req = urllib.request.Request(url, headers=hdrs)
    response = urllib.request.urlopen(req)

    words = response.read().decode()
    words = words.splitlines()
    text = ''
    while len(text) < n:
        text += ' ' + random.choice(words)
    rem = len(text) - n
    if rem != 0:
        text = text[:-rem]
    return text


def case1():
    print("Case #1: Concious text vs concious text in natural language.")
    url = 'https://www.gutenberg.org/files/1056/1056-0.txt'
    url2 = 'https://www.gutenberg.org/files/64317/64317-0.txt'
    response = urllib.request.urlopen(url)
    text1 = response.read().decode()
    response = urllib.request.urlopen(url2)
    text2 = response.read().decode()
    min_len = min(len(text1), len(text2))
    text1 = text1[:min_len]
    text2 = text2[:min_len]
    print("Text length: {0}".format(min_len))
    print("Match: {0}".format(match_percentages(text1, text2)))


def case2():
    print("Case #2: Concious text vs random letters text.")
    url = 'https://www.gutenberg.org/files/1056/1056-0.txt'
    response = urllib.request.urlopen(url)
    text1 = response.read().decode()
    s = 0
    text2 = letters_generator(len(text1))
      #  with open('./tests/case2_text_{0}'.format(i + 1), 'w') as f:
       #     f.write(text2)
    s += match_percentages(text1, text2)
    s /= CNT_RT
    print("Text length: {0}".format(len(text1)))
    print("Match: {0}".format(s))


def case3():
    print("Case #3: Concious text vs random words text.")
    url = 'http://www.gutenberg.org/files/4300/4300-0.txt'
    response = urllib.request.urlopen(url)
    text1 = response.read().decode()
    s = 0
    text2 = words_generator(len(text1))
        # with open('./tests/case3_text_{0}'.format(i + 1), 'w') as f:
          #  f.write(text2)
    s += match_percentages(text1, text2)
    s /= CNT_RT
    print("Text length: {0}".format(len(text1)))
    print("Match: {0}".format(s))


def case4():
    print("Case #4: Random letters text vs random letters text.")
    s = 0
    text1 = letters_generator(LEN_RT)
      #  with open('./tests/case4_text1_{0}'.format(i + 1), 'w') as f:
       #     f.write(text1)
    text2 = letters_generator(LEN_RT)
        #with open('./tests/case4_text2_{0}'.format(i + 1), 'w') as f:
         #   f.write(text2)
    s += match_percentages(text1, text2)
    s /= CNT_RT
    print("Text length: {0}".format(LEN_RT))
    print("Match: {0}".format(s))


def case5():
    print("Case #5: Random words text vs random words text.")
    s = 0
    text1 = words_generator(LEN_RT)
       # with open('./tests/case5_text1_{0}'.format(i + 1), 'w') as f:
        #    f.write(text1)
    text2 = words_generator(LEN_RT)
        #with open('./tests/case5_text2_{0}'.format(i + 1), 'w') as f:
         #   f.write(text2)
    s += match_percentages(text1, text2)
    s /= CNT_RT
    print("Text length: {0}".format(LEN_RT))
    print("Match: {0}".format(s))


def print_usage(message):
   # print(USAGE)
    if message:
        sys.exit('\nFATAL ERROR: ' + message)
    else:
        sys.exit(1)


def parse_args(args):
    try:
        opts, args = getopt.getopt(args, '', ['help', 'cases='])
    except getopt.GetoptError:
        print_usage('Invalid arguments.')

    cases = [i for i in range(1, CASES + 1)]

    for (opt, val) in opts:
        if opt == '--help':
            print_usage(None)
        elif opt == '--cases':
            try:
                cases = set(map(int, val.split(',')))
            except ValueError:
                print_usage('Cases must be comma separated list.')

            for i in cases:
                if i not in range(1, CASES + 1):
                    print_usage('Incorrect cases')

    return cases


if __name__ == '__main__':
    cases = parse_args(sys.argv[1:])

    for i in cases:
        if i == 1:
            case1()
        elif i == 2:
            case2()
        elif i == 3:
            case3()
        elif i == 4:
            case4()
        elif i == 5:
            case5()