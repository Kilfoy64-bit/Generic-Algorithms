/*
Author: Logan Kilfoy

Program Details:
Implementation of insertion sort in c++
Input: File of integer values.
Output: Sorted array of file contents.

Description of Insertion Sort:
To sort an array of size n in ascending order: 
1: Iterate from arr[1] to arr[n] over the array. 
2: Compare the current element (key) to its predecessor. 
3: If the key element is smaller than its predecessor, compare it to the elements before. Move the greater elements one position up to make space for the swapped element.

Time Complexity: O(n*2) 
Auxiliary Space: O(1)
Boundary Cases: Insertion sort takes maximum time to sort if elements are sorted in reverse order. And it takes minimum time (Order of n) when elements are already sorted.
Algorithmic Paradigm: Incremental Approach
Sorting In Place: Yes
Stable: Yes

https://www.geeksforgeeks.org/insertion-sort/ 
*/

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdio>
#include <ctime>

std::string get_args(int argc, char *argv[]);
void read_file_array(std::string filename, std::vector<int> &array);
void convert_str_to_vec(std::vector<int> &array, std::string str, std::string delimiter=",");
void insertion_sort(std::vector<int> &array);
void print_vector(std::vector<int> array);

int main(int argc, char *argv[]) {
	std::vector<int> array;
	std::string filename;
	std::clock_t start;
    double duration;

	filename = get_args(argc, argv);
	read_file_array(filename, array);
	
    start = std::clock();

	insertion_sort(array);
	
    duration = ( std::clock() - start ) / (double) CLOCKS_PER_SEC;

	print_vector(array);
    std::cout<<"Time elapsed: "<< duration << std::endl;

	return 0;
}

std::string get_args(int argc, char *argv[]) {
	std::string filename;
	if(argc == 2) {
		filename = argv[1];
	}
	return filename;
}

void read_file_array(std::string filename, std::vector<int> &array) {
	std::fstream file(filename);
	std::string line;
	std::string str_array;

	while(std::getline(file, line)) {
		std::cout << line << std::endl;
		str_array += line;
	}

	file.close();
	convert_str_to_vec(array, str_array);
}

void convert_str_to_vec(std::vector<int> &array, std::string str, std::string delimiter) {
	int token;
	size_t pos = 0;
    while ((pos = str.find(delimiter)) != std::string::npos) {
		token = std::stoi(str.substr(0, pos));
		std::cout << token << std::endl;
		array.push_back(token);
		str.erase(0, pos + delimiter.length());
	}
}

void insertion_sort(std::vector<int> &array) {
	int i, key;
	for (int j = 1; j < array.size(); j++) {
		key = array[j];
		i = j - 1;
		
		while ((i >= 0) && (array[i] > key)) {
			array[i+1] = array[i];
			i -= 1;
		}
		array[i+1] = key;
	}
}

void print_vector(std::vector<int> array) {
	int i;
	for (i = 0; i < array.size() - 1; i++) {
		std::cout << array[i] << ", ";
	}
	std::cout << array[i] << std::endl;
}