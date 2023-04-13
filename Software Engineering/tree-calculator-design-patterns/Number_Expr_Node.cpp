/**
 * Honor Pledge:
 *
 * I pledge that I have neither given nor received any help
 * on this assignment.
 */
//==============================================================================

#include "Number_Expr_Node.h"
#include "Expr_Node_Visitor.h"


Number_Expr_Node::Number_Expr_Node(int n1) 
:n1(n1){

}
Number_Expr_Node::~Number_Expr_Node() {
}
void Number_Expr_Node::accept(Expr_Node_Visitor & v) {
    v.visit_number_node(*this);
}

int Number_Expr_Node::eval() {
    return n1;
}
