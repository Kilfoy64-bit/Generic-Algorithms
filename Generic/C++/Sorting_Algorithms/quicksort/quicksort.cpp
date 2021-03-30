/*
Authors:
- Lewis Smith
- Logan Kilfoy

Question 1
How many comparisons would you expect to be performed by Quicksort if we 
are lucky and always pick the median element as the pivot? You only need 
to consider the case when n = 10.

19

Question 2
How many comparisons would you expect to be performed by Quicksort if we 
are unlucky and we always pick the minimum or maximum element as the 
pivot. Consider the case when n = 10.

45

Question 3
3.  Fill in the table below. 
- the first column denotes a test file
- the remaining columns denote which variant of Quicksort you should use

For example, for the cell in the fourth row, third column you would use 
the median3 variant of Quicksort and the ordered-10000.txt file.

+==================+==========+=========+==========+==========+==========+
|       file       |  first   | median3 | random-1 | random-2 | random-3 |
+==================+==========+=========+==========+==========+==========+
| ordered-10       |       45 |      19 |       23 |       23 |       27 |
+------------------+----------+---------+----------+----------+----------+
| ordered-100      |     4950 |     480 |      611 |      649 |      680 |
+------------------+----------+---------+----------+----------+----------+
| ordered-10000    | 49995000 |49995000 |   156959 |   156786 |   154052 |
+------------------+----------+---------+----------+----------+----------+
| randomized-10    |      20  |      21 |       24 |       21 |       29 |
+------------------+----------+---------+----------+----------+----------+
| randomized-100   |     667  |     633 |      708 |      699 |      621 |
+------------------+----------+---------+----------+----------+----------+
| randomized-10000 |   158257 |  156416 |   159014 |   143560 |   153447 |
+------------------+----------+---------+----------+----------+----------+
*/

#include <chrono>
#include <cstring>
#include <fstream>
#include <iostream>
#include <random>
#include <string>
#include <vector>
#include <cmath>

using std::cout;
using std::vector;
using std::endl;
using std::ifstream; 
using std::strcmp;
using std::random_device;
using std::chrono::system_clock;
using std::default_random_engine;
using std::uniform_int_distribution;
using std::string;

// std::ostream &operator<<(std::ostream &out, vector<long> &vec)
// {
//     out << "[ ";
//     string delim("");
//     for (auto &val : vec)
//     {
//         out << delim << val;
//         delim = ", ";
//     }
//     out << "]";
//     return out;
// }

// For Debgging Purposes

// Partitions a subarray
long partition(vector<long> &, long, long);
// Helper Function for partition method
void swap(vector<long> &, long, long);
// Quicksort - First Pivot Variant
void qs_first(vector<long> &, long, long);
// Quicksort - Median Variant
void qs_median3(vector<long> &, long, long);
// Quicksort - Random Variant
void qs_random(vector<long> &, long, long, default_random_engine &);
long getMedian(vector<long> &, long, long, long);
void print(vector<long> const &input);

/* Global variable incremented every time a the
   partition method does a comparison. */
unsigned long comparisons;

int main(int argc, char *argv[])
{
    // Handle file I/O
    ifstream numFile;
    numFile.open(argv[1]);

    // Get Numbers
    vector<long> vec_of_nums;
    long dummy;
    while (numFile >> dummy)
    {
        vec_of_nums.push_back(dummy);
    }
    // cout << vec_of_nums << endl;
    // For debugging purposes
    string argum(argv[2]);
    // Handle quicksort variant arg
    if (argum == "first")
    {
        qs_first(vec_of_nums, 1, vec_of_nums.size());
    }
    else if (argum == "median3")
    {
        qs_median3(vec_of_nums, 1, vec_of_nums.size());
    }
    else if (argum == "random")
    {
        default_random_engine reng;
        reng.seed(system_clock::now().time_since_epoch().count());
        qs_random(vec_of_nums, 1, vec_of_nums.size(), reng);
    }
    // Print the number of comparisons
    // and terminate the program
    cout << comparisons << endl;
    //print(vec_of_nums);
    // For Debugging Purposes
    return 0;
}

// Always selects the first index as the pivot point
void qs_first(vector<long> &array, long left, long right)
{
    if ((left + 1) >= right)
    {
        return;
    }
    long pivotPoint = partition(array, left, right);

    qs_first(array, left, pivotPoint);
    qs_first(array, pivotPoint + 1, right);
}

// Determines the pivot point as the median of the left, right, and middle indices
void qs_median3(vector<long> &array, long left, long right)
{
    if ((left + 1) >= right)
    {
        return;
    }
    if (right - left > 2){
        long middle = floor((left + right) / 2);
        long median = getMedian(array, left, right, middle);
        //cout << "median: " << median << endl;

        if(array[middle] == median)
        {
            swap(array, left, middle);
        }
        else if(array[right] == median)
        {
            swap(array, left, right);
        }
    }
    long pivotPoint = partition(array, left, right);

    qs_median3(array, left, pivotPoint);
    qs_median3(array, pivotPoint + 1, right);
}

// Determines a pivot point at random
void qs_random(vector<long> &array, long left, long right, default_random_engine &reng)
{
    if ((left + 1) >= right)
    {
        return;
    }

    uniform_int_distribution<long> dis(left, right - 1);
    swap(array, dis(reng), left);
    long pivotPoint = partition(array, left, right);

    qs_random(array, left, pivotPoint, reng);
    qs_random(array, pivotPoint + 1, right, reng);
}

// For Partitioning Subarray
long partition(vector<long> &array, long left, long right)
{
    long pivotValue = array[left];

    long i = left + 1;
    for (size_t j = left + 1; j < right; j++)
    {
        if (array[j] < pivotValue)
        {
            swap(array, i, j);
            i++;
        }
        comparisons++;
    }
    swap(array, left, i - 1);
    return (i - 1);
}

// Helper Swap Function
void swap(vector<long> &array, long value1, long value2)
{
    using std::swap;
    swap(array[value1], array[value2]);
}


long getMedian(vector<long> &array, long left, long right, long middle)
{
    vector<long> threeVal {array[left], array[middle], array[right - 1]};
    for (size_t i = 0; i < 3; i++)
    {
        for(size_t k = i; k < 3; k++)
        {
            if(threeVal[i] > threeVal[k])
            {
                swap(threeVal, i, k);
            }
        }
        
    }
    
    return threeVal[1];
}

/*
long getMedian(vector<long> &array, long left, long right, long middle){
    vector<long> sub_vect {array[left], array[middle], array[right - 1]};

    cout <<"before L: " << sub_vect[0] << endl;
    cout <<"before M: " << sub_vect[1] << endl;
    cout <<"before R: " << sub_vect[2] << endl;
    if ((sub_vect[0] > sub_vect[1]) && (sub_vect[0] < sub_vect[2])){
        swap(sub_vect, 0, 1);
        cout <<"picked: " << sub_vect[1] << endl;
        return sub_vect[1];
    }
    if ((sub_vect[0] < sub_vect[1]) && (sub_vect[0] > sub_vect[2])){
        swap(sub_vect, 0, 1);
        cout <<"picked: " << sub_vect[1] << endl;
        return sub_vect[1];
    }
    if ((sub_vect[2] > sub_vect[0]) && (sub_vect[2] < sub_vect[1])){
        swap(sub_vect, 2, 1);
        cout <<"picked: " << sub_vect[1] << endl;
        return sub_vect[1];
    }
    if ((sub_vect[2] < sub_vect[0]) && (sub_vect[2] > sub_vect[1])){
        swap(sub_vect, 2, 1);
        cout <<"picked: " << sub_vect[1] << endl;
        return sub_vect[1];
    }
    cout <<"picked: " << sub_vect[1] << endl;
    return sub_vect[1];
}

void print(vector<long> const &input)
{
	for (int i = 0; i < input.size(); i++) {
		cout << input.at(i) << ' ';
	}
}
*/