// $Id: Array.cpp 827 2011-02-07 14:20:53Z hillj $

// Honor Pledge:
//
// I pledge that I have neither given nor received any help
// on this assignment.

#include "Array.h"
#include "Array_Base.h"
#include <iostream>
#include <stdexcept>         // for std::out_of_bounds exception

//
// Array
//
template <typename T>
Array <T>::Array (void)
	:Array_Base<T>()
{
	
}

//
// Array (size_t)
//
template <typename T>
Array <T>::Array (size_t length)
	:Array_Base<T>(length)
{
	
}

//
// Array (size_t, T)
//
template <typename T>
Array <T>::Array (size_t length, T fill)
	:Array_Base<T>(length, fill)
{
	
}

//
// Array (const Array &)
//
template <typename T>
Array <T>::Array (const Array & array)
	:Array_Base<T>(array)
{
	
}

//
// ~Array
//
template <typename T>
Array <T>::~Array (void)
{

}

//
// operator =
//
template <typename T>
const Array <T> & Array <T>::operator = (const Array<T> & rhs)
{
	if(!(this->data_ == rhs.data_)) {
  	
  	if(this->max_size_ < rhs.max_size_) {
		this->cur_size_ = rhs.cur_size_;
  		this->max_size_ = rhs.max_size_;
  		this->data_ = new T[rhs.max_size_];
	}

  	for(int i = 0; i < this->cur_size_; i++) {
  		this->data_[i] = rhs.data_[i];
  	}
  }
  return *this;
}

//
// resize
//
template <typename T>
void Array <T>::resize (size_t new_size)
{
	if (new_size > this->max_size_) {
    	//use temp array to preserve contents of original array
		T temp_[this->cur_size_];
		
		for(int i = 0; i < this->cur_size_; i++) {
			temp_[i] = this->data_[i];
		}
		 		
		delete [] this->data_;
		
		this->data_ = new T[new_size];
		
		for(int i = 0; i < this->cur_size_; i++) {
			this->data_[i] = temp_[i];
		}
		this->max_size_ = new_size;
		this->cur_size_ = new_size;

	}
}

//
// operator ==
// overloaded == operator, checks for equality of location and elements
template <typename T>
bool Array <T>::operator == (const Array<T> & rhs) const
{
	if(this->data_ == rhs.data_) {
		return true;
	}
	else {
	}
	for(int i = 0; i < this->cur_size_; i++ ) {
		if(!(this->data_[i] == rhs.data_[i])) {
			return false;
		}
	}
}

//
// operator !=
// overloaded != operator, checks if the locations are the same
template <typename T>
bool Array <T>::operator != (const Array<T> & rhs) const
{
	if(!(this->data_ == rhs.data_)) {
		return true;
	}
	else {
		return false;
	}
}
//shrinks max size to be equal to cur size
template <typename T>
void Array<T>::shrink (void)
{
  
  //check if shrink needs to be invoked
  if(this->max_size_ > this->cur_size_) {
  	char temp_[this->cur_size_];
  	
  	this->max_size_ = this->cur_size_;
  	
	//reclaim space by reassigning data with temp array and reassigning elements to data_
  	for(int i = 0; i < this->cur_size_; i++) {
  		temp_[i] = this->data_[i];
  	}
  	this->data_ = new char[this->max_size_];
  	
  	for(int i = 0; i < this->cur_size_; i++) {
  		this->data_[i] = temp_[i];
  	}
  	  	
  }
  else {
  	std::cout << "sizes are the same";
  }
}

//reverses contents of array;
template <typename T>
void Array<T>::reverse (void)
{
  int i = 0;
  int j = this->cur_size_ -1;
  
  //basic swapping function using temp 
  while(i <= j) {
  	char temp = this->data_[i];
  	this->data_[i] = this->data_[j];
  	this->data_[j] = temp;
  	
  	i++;
  	j--;
  }
}

