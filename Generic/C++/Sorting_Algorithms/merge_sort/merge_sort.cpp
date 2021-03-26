/*
Author: Logan Kilfoy

Program Details:
Implementation of Merge Sort in c++
Input: File of integer values.
Output: Sorted array of file contents.

Description of Merge Sort:

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
void merge_sort(std::vector<int> &array);
std::vector<int> merge(int left, int right);
void print_vector(std::vector<int> array);

int main(int argc, char *argv[]) {
	std::vector<int> array;
	std::string filename;
	std::clock_t start;
    double duration;

	filename = get_args(argc, argv);
	read_file_array(filename, array);
	
    start = std::clock();

	merge_sort(array);
	
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

void merge_sort(std::vector<int> &array) {
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

std::vector<int> merge(int left, int right) {
	
}

void print_vector(std::vector<int> array) {
	int i;
	try {
		if (array.size() == 0) {
			throw (0);
		}
		for (i = 0; i < array.size() - 1; i++) {
			std::cout << array[i] << ", ";
		}
		std::cout << array[i] << std::endl;
	}
	catch(...) {
		std::cout << "Vector is empty." << std::endl;
	}
}