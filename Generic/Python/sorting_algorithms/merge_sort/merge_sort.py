# -*- coding: utf-8 -*-
"""
Created on Thu Aug 29 14:40:17 2019

@author: logan
"""

#!/usr/bin/env python3

import random
import sys
import time


def merge(left, right):
    combined = []

    i, j = 0, 0
    for k in range(len(left) + len(right)):
        if j >= len(right) or (i < len(left) and left[i] < right[j]):
            combined.append(left[i])
            i += 1
        else:
            combined.append(right[j])
            j += 1

    return combined


def merge_sort(array):
    if len(array) <= 1:
        return array

    left = merge_sort(array[:len(array)//2])
    right = merge_sort(array[len(array)//2:])

    return merge(left, right)


def main():
    filename = sys.argv[1]

    with open(filename, 'r') as input_file:
        n = int(input_file.readline())
        array = [int(v) for v in input_file.readlines()]

    start_time = time.time()
    sorted_array = merge_sort(array)
    end_time = time.time()

    # print(all([x < y for x, y in zip(sorted_array[0::2], sorted_array[1::2])]))
    print('Elapsed time:', end_time - start_time)


if __name__ == '__main__':
    main()