/**
 * Honor Pledge:
 *
 * I pledge that I have neither given nor received any help
 * on this assignment.
 */
//==============================================================================

#include "Divide_Expr_Node.h"
#include "Expr_Node_Visitor.h"

Divide_Expr_Node::Divide_Expr_Node(Expr_Node * n1, Expr_Node * n2)
:Binary_Expr_Node(n1, n2),
precedence(3)
{
    
}
Divide_Expr_Node::~Divide_Expr_Node() {
}
void Divide_Expr_Node::accept(Expr_Node_Visitor & v) {
    v.visit_divide_node(*this);
}

int Divide_Expr_Node::execute(int n1, int n2) {
    if(n2 == 0) {
        return 0;
    }
    else {
        return n1 / n2;
    }
}
int Divide_Expr_Node::get_precedence(){
	return precedence;
}