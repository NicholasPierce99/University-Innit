/**
 * Honor Pledge:
 *
 * I pledge that I have neither given nor received any help
 * on this assignment.
 */
//==============================================================================

#include "Unary_Expr_Node.h"

Unary_Expr_Node::Unary_Expr_Node(Expr_Node * n1) 
:child_(n1){

}
Unary_Expr_Node::~Unary_Expr_Node() {
    delete this->child_;
}
int Unary_Expr_Node::eval() {
    if(this->child_) {
        return this->child_->eval();
    }
}