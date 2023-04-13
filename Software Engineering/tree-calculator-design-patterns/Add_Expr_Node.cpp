/**
 * Honor Pledge:
 *
 * I pledge that I have neither given nor received any help
 * on this assignment.
 */
//==============================================================================

#include "Add_Expr_Node.h"
#include "Expr_Node_Visitor.h"


Add_Expr_Node::Add_Expr_Node(Expr_Node * n1, Expr_Node * n2)
:Binary_Expr_Node(n1, n2),
precedence(2)
{
    
}
Add_Expr_Node::~Add_Expr_Node() {
}

void Add_Expr_Node::accept(Expr_Node_Visitor & v) {
    v.visit_add_node(*this);
}

int Add_Expr_Node::execute(int n1, int n2) {
    return n1 + n2;
}
int Add_Expr_Node::get_precedence() {
	return precedence;
}
