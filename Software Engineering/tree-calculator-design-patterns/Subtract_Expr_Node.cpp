/**
 * Honor Pledge:
 *
 * I pledge that I have neither given nor received any help
 * on this assignment.
 */
//==============================================================================

#include "Subtract_Expr_Node.h"
#include "Expr_Node_Visitor.h"


Subtract_Expr_Node::Subtract_Expr_Node(Expr_Node * n1, Expr_Node * n2)
:Binary_Expr_Node(n1, n2),
precedence(3)
{
    
}
Subtract_Expr_Node::~Subtract_Expr_Node() {
}
void Subtract_Expr_Node::accept(Expr_Node_Visitor & v) {
    v.visit_subtract_node(*this);
}

int Subtract_Expr_Node::execute(int n1, int n2) {
    return n1 - n2;
}
int Subtract_Expr_Node::get_precedence(){
	return precedence;
}
