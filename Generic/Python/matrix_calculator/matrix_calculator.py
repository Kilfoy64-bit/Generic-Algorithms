# Unfinished


import numpy as np

def main():
    rows = input("rows: ")
    columns = input("columns: ")

    matrix1 = np.array([])
    matrix2 = np.array([])

    for row in rows:
        for column in columns:
            value = int(input("integer: "))
            matrix1 = np.append(matrix1, value)

if __name__ == "__main__":
    main()