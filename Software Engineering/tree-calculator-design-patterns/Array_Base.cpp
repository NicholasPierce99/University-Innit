// $Id: Array.cpp 827 2011-02-07 14:20:53Z hillj $

// Honor Pledge:
//
// I pledge that I have neither given nor receieved any help
// on this assignment.

#include "Array_Base.h"
#include <stdexcept>         // for std::out_of_bounds exception

//
// Array constructor, base
//
template <typename T>
Array_Base <T>::Array_Base (void)
	:data_(nullptr),
	cur_size_(0),
	max_size_(0)
{
	
}

//
// Array (size_t)
// array constructor, sets the size to a specific length
template <typename T>
Array_Base <T>::Array_Base (size_t length)
	:data_(nullptr),
	cur_size_(0),
	max_size_(0)
{
	if(!(length == 0)) {
		data_ = new T[length];
		cur_size_ = length;
		max_size_ = length;
	}
}

//
// Array (size_t, T)
// array constructor, sets size to given length and fills with fill value
template <typename T>
Array_Base <T>::Array_Base (size_t length, T fill)
	:data_ (new T [length]), 
	cur_size_ (length), 
	max_size_ (length)
{
	for(int i = 0; i < cur_size_; i++) {
		data_[i] = fill;
	}
}

//
// Array (const Array &)
//  copy constructor for arrays
template <typename T>
Array_Base <T>::Array_Base (const Array_Base & array)
	:data_ (new T[array.max_size_]), 
	cur_size_ (array.cur_size_), 
	max_size_ (array.max_size_)
{
	
	for(int i = 0; i < cur_size_; i++) {
  		data_[i] = array.data_[i];
    }
}

//
// ~Array
// destructor, deletes array pointer container
template <typename T>
Array_Base <T>::~Array_Base (void)
{
	delete [] data_;
	
}

//
// operator =
// overloaded assignment operator
//assigns contents of an array to another one
template <typename T>
const Array_Base <T> & Array_Base <T>::operator = (const Array_Base & rhs)
{
	//check for self assignment
	if(!(data_ == rhs.data_)) {
    //check if resize needs to happen
  	if(max_size_ < rhs.max_size_) {
  		max_size_ = rhs.max_size_;
		cur_size_ = rhs.cur_size_;
  		data_ = new T[max_size_];
	}
	//perform assignment of elements
  	for(int i = 0; i < cur_size_; i++) {
  		data_[i] = rhs.data_[i];
  	}
  }
  return *this;
}

//
// operator []
// gets an element of an array
//overloads the [] operator
template <typename T>
T & Array_Base <T>::operator [] (size_t index)
{
	if (index > cur_size_) {
		throw std::out_of_range("current index size retrieval outside bounds of array");
	}
	else {
		return data_[index];
	}
}

//
// operator [] 
// gets an element of an array
//overloads the [] operator
//used for const members
template <typename T>
const T & Array_Base <T>::operator [] (size_t index) const
{
	if (index > cur_size_) {
		throw std::out_of_range("current index size retrieval outside bounds of array");
	}
	else {
		return data_[index];
	}
}

//
// get
// returns the data at a specific index
//throws out of range exception if index is out of range
template <typename T>
T Array_Base <T>::get (size_t index) const
{
	if (index > cur_size_) {
		throw std::out_of_range("current index size retrieval outside bounds of array");
	}
	else {
		return data_[index];
	}
}

//
// set
// sets the index value of an array to a given T value
//throws out of range if index is out of range
template <typename T>
void Array_Base <T>::set (size_t index, T value)
{
	if (index > max_size_) {
		throw std::out_of_range("current index size retrieval outside bounds of array");
	}
	else {
		data_[index] = value;
	}
}

//
// find (T)
// finds an element T in the current array
template  <typename T>
int Array_Base <T>::find (T value) const
{
	for(int i = 0; i < cur_size_; i++) {
		if(data_[i] == value) {
			return i;
		}
	}
	return -1;
}

//
// find (T, size_t) 
// finds a given element, but starts from a start position
template <typename T>
int Array_Base <T>::find (T val, size_t start) const
{
	//check for out of bounds
	if(start > cur_size_) {
		throw std::out_of_range("current index size retrieval outside bounds of array");
	}
	else {
		for(int i = start; i < cur_size_; i++) {
			if(data_[i] == val) {
				return i;
			}
		}
	}
	return -1;
}

//
// operator ==
// overloaded equality operator, checks individual elements and memory locations to check for equality
template <typename T>
bool Array_Base <T>::operator == (const Array_Base & rhs) const
{
	if(data_ == rhs.data_) {
		return true;
	}
	else {
	}
	for(int i = 0; i < cur_size_; i++ ) {
		if(!(data_[i] == rhs.data_[i])) {
			return false;
		}
        else {
            return true;
        }
	}
}

//
// operator !=
// overloaded inequality operators, checks for inequality
template <typename T>
bool Array_Base <T>::operator != (const Array_Base & rhs) const
{
	if(!(data_ == rhs.data_)) {
		return true;
	}
	else {
		return false;
	}
}

//
// fills the array with some element T
//
template <typename T>
void Array_Base <T>::fill (T value)
{
	for(int i = 0; i < cur_size_; i++) {
		data_[i] = value;
	}
}
