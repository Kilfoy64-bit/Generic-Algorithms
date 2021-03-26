def reverseArray(a):
    array_length = len(a)
    for index in range(array_length//2):
        switch_index = array_length - index - 1
        switch = a[switch_index]
        a[switch_index] = a[index]
        a[index] = switch
    return a

if __name__ == "__main__":
    array = [10, -23, 4, 100]
    reverse_array = reverseArray(array)
    print(reverse_array)