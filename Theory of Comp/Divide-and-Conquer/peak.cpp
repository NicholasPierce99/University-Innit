#include <iostream>
#include <vector>
#include <fstream>
#include <string>

/*
algo

given an array of n elements
check if the middle element is the peak, (constant time)
if it is not the peak, check the right element: (n/2)
if the right element is greater than the middle element,
there were always be a peak in the right side
do the same principle for the left side(n/2)
resetting the middle to be the middle of the left side or right side,
element greater than middle or smaller (n/4)
etc.... repeat until we find the peak.



*/

//function prototype
int find_peak(int low_element, int high_element, std::vector<int> arr, int n);
void read_from_file(std::vector<int> & arr);


//expects ends of the array, array of numbers, size n
int find_peak(int low_element, int high_element, std::vector<int> arr, int n) {

	//find the middle element
	int middle_element =  low_element + (high_element - low_element) / 2;

	//compare with neighboring elements
	//if peak is found, return it
	if ((middle_element == 0 || arr[middle_element - 1] <= arr[middle_element]) && (middle_element == n - 1 || arr[middle_element + 1] <= arr[middle_element])) {
		return middle_element;
	}
	//else if middle element is not the peak and left neighbor is greater, must be in the left half, use middle -1 as the new high_element element 
	else if (middle_element > 0 && arr[middle_element - 1] > arr[middle_element]) {
		return find_peak(low_element, middle_element, arr, n);
	}
	//else the middle element is not the peak and right neighbor is greater, right half must have the peak, use middle + 1 as new low_element
	else {
		return find_peak(middle_element + 1, high_element, arr, n);
	}
}

//read from file
void read_from_file(std::vector<int> & arr) {
	std::string line;

	std::ifstream file_name("peak.txt");

	while (std::getline(file_name, line)) {
		int temp = std::stoi(line);
		arr.push_back(temp);
	}
	file_name.close();
}


int main() {
	std::vector<int> arr;
	read_from_file(arr);
	int n = arr.size();
	int result = find_peak(0, n - 1, arr, n);

	std::cout << "peak index is " << result  << std::endl;
	std::cout << "element is " << arr[result] << std::endl;

	return 0;
}
