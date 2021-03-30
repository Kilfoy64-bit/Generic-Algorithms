# -*- coding: utf-8 -*-
"""
Created on Thu Aug 29 14:38:53 2019

@author: logan
"""

#!/usr/bin/env python3

import random
import sys
import time


def inerstion_sort(array):
    for j, key in enumerate(array[1:], 1):
        i = j - 1
        while i >= 0 and array[i] > key:
            array[i + 1] = array[i]
            i -= 1
        array[i + 1] = key

    return array


def main():
    filename = sys.argv[1]

    with open(filename, 'r') as input_file:
        n = int(input_file.readline())
        array = [int(v) for v in input_file.readlines()]

    start_time = time.time()
    sorted_array = inerstion_sort(array)
    end_time = time.time()

    # print(all([x < y for x, y in zip(sorted_array[0::2], sorted_array[1::2])]))
    print('Elapsed time:', end_time - start_time)


if __name__ == '__main__':
    main()