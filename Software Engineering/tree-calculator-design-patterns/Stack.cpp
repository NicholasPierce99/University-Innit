// $Id: Stack.cpp 827 2011-02-07 14:20:53Z hillj $

// Honor Pledge:
//
// I pledge that I have neither given nor received any help
// on this assignment.
#include "Stack.h"
#include "Array.h"
#include <iostream>
//
// Stack
// base constructor
template <typename T>
Stack <T>::Stack (void)
    //array aggregation
    //set top to 0 to make index of first element 1
    :top_(0),
    array_(new Array<T>(100))
{
    
}

//
// Stack
// I don't really know how to check for self assignment for the stack data_ member
template <typename T>
Stack <T>::Stack (const Stack & stack)
    :top_(0),
    array_(new Array<T>())
{
  if(this->array_ == stack.array_) {
  }
  else {
    this->array_ = new Array<T>(stack.array_->size());
    if(this->top_ != stack.top_) {
        this->top_ = stack.top_;
    }
    for(size_t i = stack.top_; i >= 1; i--) {
        this->array_->set(i, stack.array_->get(i)); 
    }
  }
}

//
// ~Stack
// delete array member of stack
template <typename T>
Stack <T>::~Stack (void)
{
    delete this->array_;
}

//
// push
// check for stack overflow, invoke set method, increase top by 1
template <typename T>
void Stack <T>::push (T element)
{
 
   this->top_++;       
   this->array_->set(this->top_, element);
}

//
// pop
//checks for stack being empty, then moves top pointer down 1
//throw empty exception if is_empty is true
template <typename T>
T Stack <T>::pop (void)
{
	//used to retrieve popped element
	T temp;
    //pop is now dynamic, resizes if needed by factor of 2
    if(this->is_empty()) {
        empty_exception exception_;
        throw exception_;
    }
    else {
		temp = this->array_->get(this->top_);
        this->top_--;
        //check if the top becomes 0 partway through
        if(this->is_empty()) {
        }
        
        else if(this->top_ <= this->array_->size()) {
			this->array_->resize(this->array_->size() / 2);
        }
   
    }
	return temp;
}


//
// operator =
//assigns one stack to another one IE the top value and data members
template <typename T>
const Stack <T> & Stack <T>::operator = (const Stack & rhs)
{
  // COMMENT Check for self assignment.
  //I have checked for self assignment of the array_ members
  if(this->array_ == rhs.array_) {
  }
  else {
    this->array_ = new Array<T>(rhs.array_->size());
    if(this->top_ != rhs.top_) {
        this->top_ = rhs.top_;
    }
    for(size_t i = rhs.top_; i >= 1; i--) {
        this->array_->set(i, rhs.array_->get(i)); 
    }
  }
    return *this;
}

//
// clear
// remakes new array object, sets top to 0
template <typename T>
void Stack <T>::clear (void)
{
  
}

