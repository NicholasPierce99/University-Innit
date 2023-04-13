/**
 * Honor Pledge:
 *
 * I pledge that I have neither given nor received any help
 * on this assignment.
 */
//==============================================================================

#include "Multiply_Expr_Node.h"
#include "Expr_Node_Visitor.h"


Multiply_Expr_Node::Multiply_Expr_Node(Expr_Node * n1, Expr_Node * n2)
:Binary_Expr_Node(n1, n2),
precedence(3)
{
    
}
Multiply_Expr_Node::~Multiply_Expr_Node() {
}

int Multiply_Expr_Node::execute(int n1, int n2) {
    return n1 * n2;
}
void Multiply_Expr_Node::accept(Expr_Node_Visitor & v) {
    v.visit_multiply_node(*this);
}
int Multiply_Expr_Node::get_precedence(){
	return precedence;
}