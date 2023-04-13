// -*- C++ -*-
// $Id: Stack.inl 827 2011-02-07 14:20:53Z hillj $

// Honor Pledge:
//
// I pledge that I have neither given nor received any help on
// this assignment.

//
// size returns top_ which is the number of elements on stack
//
template <typename T>
inline
size_t Stack <T>::size (void) const
{
    return top_;
}

//
// top, invokes get method
//
template <typename T>
inline
T Stack <T>::top (void) const
{
    empty_exception exception_;
    if(top_ == 0) {
        throw exception_;
    }
    else {
        return this->array_->get(top_);
    }
}

//
// is_empty checks for top equaling 0
//
template <typename T>
inline
bool Stack <T>::is_empty (void) const
{
    if(top_ == 0) {
        return true;
    }
    else {
        return false;
    }
}
