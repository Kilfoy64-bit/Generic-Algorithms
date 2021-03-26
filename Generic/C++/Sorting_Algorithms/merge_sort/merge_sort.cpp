/*
Author: Logan Kilfoy

Program Details:
Implementation of Merge Sort in c++
Input: File of integer values.
Output: Sorted array of file contents.

Description of Merge Sort:

MergeSort(arr[], l,  r)
If r > l
	1. Find the middle point to divide the array into two halves:  
			middle m = l+ (r-l)/2
	2. Call mergeSort for first half:   
			Call mergeSort(arr, l, m)
	3. Call mergeSort for second half:
			Call mergeSort(arr, m+1, r)
	4. Merge the two halves sorted in step 2 and 3:
			Call merge(arr, l, m, r)

Time Complexity: Sorting arrays on different machines. Merge Sort is a recursive algorithm and time complexity can be expressed as following recurrence relation. 
T(n) = 2T(n/2) + θ(n)

The above recurrence can be solved either using the Recurrence Tree method or the Master method. It falls in case II of Master Method and the solution of the recurrence is θ(nLogn). Time complexity of Merge Sort is  θ(nLogn) in all 3 cases (worst, average and best) as merge sort always divides the array into two halves and takes linear time to merge two halves.
Auxiliary Space: O(n)
Algorithmic Paradigm: Divide and Conquer
Sorting In Place: No in a typical implementation
Stable: Yes
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
std::vector<int> merge_sort(std::vector<int> array);
std::vector<int> merge(std::vector<int> left, std::vector<int> right);
std::vector<int> slice_vector(std::vector<int> &arr, int first, int last);
void print_vector(std::vector<int> array);

int main(int argc, char *argv[]) {
	std::vector<int> array;
	std::string filename;
	std::clock_t start;
    double duration;

	filename = get_args(argc, argv);
	read_file_array(filename, array);
	
	print_vector(array);
	
    start = std::clock();

	array = merge_sort(array);
	
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
		array.push_back(token);
		str.erase(0, pos + delimiter.length());
	}
}

std::vector<int> merge_sort(std::vector<int> array) {
	if (array.size() <= 1) {
		return array;
	}

	int middle_index = (array.size()/2) - 1;

	std::vector<int> left = merge_sort(slice_vector(array, 0, middle_index));
	std::vector<int> right = merge_sort(slice_vector(array, (middle_index + 1), (array.size()-1)));

	return merge(left, right);
}

std::vector<int> merge(std::vector<int> left, std::vector<int> right) {
	std::vector<int> combined;

	int i, j = 0;
	for (int k = 0; k < (left.size() + right.size()); k++) {
		if ((j >= right.size()) | ((i < left.size()) && (left[i] < right[j]))) {
			combined.push_back(left[i]);
			i++;
		} else {
			combined.push_back(right[j]);
			j++;
		}
	}
	return combined;
}

std::vector<int> slice_vector(std::vector<int> &arr, int first, int last) {
    auto start = arr.begin() + first;
    auto end = arr.begin() + last + 1;
  
    std::vector<int> result(last - first + 1);
  
    copy(start, end, result.begin());
  
    return result;
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