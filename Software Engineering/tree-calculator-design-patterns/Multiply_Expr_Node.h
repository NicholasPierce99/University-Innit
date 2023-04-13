/**
 * Honor Pledge:
 *
 * I pledge that I have neither given nor received any help
 * on this assignment.
 */
//==============================================================================

#ifndef MULTIPLY_EXPR_NODE_
#define MULTIPLY_EXPR_NODE_

#include "Binary_Expr_Node.h"
class Expr_Node_Visitor;


//multiply node, multiplies two children nodes
class Multiply_Expr_Node: public Binary_Expr_Node {
    public:
        Multiply_Expr_Node(Expr_Node * n1, Expr_Node * n2);
        ~Multiply_Expr_Node();
		
		//accept for visitor
        void accept(Expr_Node_Visitor & v);
		
		//runs num x num
        int execute(int n1, int n2);
		
		//return this objects precedence
		int get_precedence();
	private:
		int precedence;
};


#endif