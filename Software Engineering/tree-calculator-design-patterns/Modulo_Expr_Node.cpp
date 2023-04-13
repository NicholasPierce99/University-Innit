/**
 * Honor Pledge:
 *
 * I pledge that I have neither given nor received any help
 * on this assignment.
 */
//==============================================================================

#include "Modulo_Expr_Node.h"
#include "Expr_Node_Visitor.h"


Modulo_Expr_Node::Modulo_Expr_Node(Expr_Node * n1, Expr_Node * n2)
:Binary_Expr_Node(n1, n2),
precedence(3)
{
    
}
Modulo_Expr_Node::~Modulo_Expr_Node() {
}

void Modulo_Expr_Node::accept(Expr_Node_Visitor & v) {
    v.visit_modulo_node(*this);
}

int Modulo_Expr_Node::execute(int n1, int n2) {
	//check if the function is passed a 0
    if(n2 == 0) {
        return 0;
    }
    else {
        return n1 % n2;
    }
}
int Modulo_Expr_Node::get_precedence(){
	return precedence;
}
