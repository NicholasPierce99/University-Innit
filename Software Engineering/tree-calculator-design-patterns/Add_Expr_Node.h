/**
 * Honor Pledge:
 *
 * I pledge that I have neither given nor received any help
 * on this assignment.
 */
//==============================================================================

#ifndef ADD_EXPR_NODE_
#define ADD_EXPR_NODE_

#include "Binary_Expr_Node.h"
class Expr_Node_Visitor;

//add expression node, builds add node for the tree
class Add_Expr_Node: public Binary_Expr_Node {
    public:
        Add_Expr_Node(Expr_Node * n1, Expr_Node * n2);
        ~Add_Expr_Node();
		
		//accept node for the visitor
        void accept(Expr_Node_Visitor & v);
		
		//execute operations
        int execute(int n1, int n2);
		
		int get_precedence();
	private:
		
		//used for stack precedence
		int precedence;
};


#endif