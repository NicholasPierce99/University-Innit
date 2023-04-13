/**
 * Honor Pledge:
 *
 * I pledge that I have neither given nor received any help
 * on this assignment.
 */
//==============================================================================
#include "Expr_Tree_Builder.h"

Expr_Tree_Builder::Expr_Tree_Builder()
:root_(nullptr)
{

}
Expr_Tree_Builder::~Expr_Tree_Builder() {
}

void Expr_Tree_Builder::build_number_node(int n1, Stack<Expr_Node *> & s) {
    Expr_Node * temp = new Number_Expr_Node(n1);
    s.push(temp);
}
//pop two from stack, return the result to the stack
void Expr_Tree_Builder::build_add_node(Stack<Expr_Node *> & s) {
    Expr_Node * temp1 = s.pop();
	Expr_Node * temp2 = s.pop();
	
	Expr_Node * add = new Add_Expr_Node(temp2, temp1);
	s.push(add);
}
void Expr_Tree_Builder::build_subtract_node(Stack<Expr_Node *> & s) {
	Expr_Node * temp1 = s.pop();
	Expr_Node * temp2 = s.pop();
	
	Expr_Node * sub = new Subtract_Expr_Node(temp2, temp1);
	s.push(sub);
}
void Expr_Tree_Builder::build_modulo_node(Stack<Expr_Node *> & s) {
    Expr_Node * temp1 = s.pop();
	Expr_Node * temp2 = s.pop();
	
	Expr_Node * mod = new Modulo_Expr_Node(temp2, temp1);
	s.push(mod);
}
void Expr_Tree_Builder::build_divide_node(Stack<Expr_Node *> & s) {
	Expr_Node * temp1 = s.pop();
	Expr_Node * temp2 = s.pop();
	
	Expr_Node * divide = new Divide_Expr_Node(temp2, temp1);
	s.push(divide);
}
void Expr_Tree_Builder::build_multiply_node(Stack<Expr_Node *> & s) {
    Expr_Node * temp1 = s.pop();
	Expr_Node * temp2 = s.pop();
	
	Expr_Node * mult = new Multiply_Expr_Node(temp2, temp1);
	s.push(mult);
}

Expr_Node * Expr_Tree_Builder::get_root(Stack<Expr_Node *> & s) {
	root_ = s.top();
    return root_;
}
