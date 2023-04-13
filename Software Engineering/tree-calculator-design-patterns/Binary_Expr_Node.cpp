/**
 * Honor Pledge:
 *
 * I pledge that I have neither given nor received any help
 * on this assignment.
 */
//==============================================================================

#include "Binary_Expr_Node.h"
#include "Expr_Node_Visitor.h"

Binary_Expr_Node::Binary_Expr_Node(Expr_Node * n1, Expr_Node * n2)
:left_(n1),
right_(n2) {
}
//clear the nodes 
Binary_Expr_Node::~Binary_Expr_Node() {
    delete this->left_;
    delete this->right_;
}
void Binary_Expr_Node::accept(Expr_Node_Visitor & v) {
}

//eval left, eval right, run execute
int Binary_Expr_Node::eval() {
    int n1 = this->left_->eval();
    int n2 = this->right_->eval();
    int result = this->execute(n1, n2);

    return result;
}
