
/**
 * Honor Pledge:
 *
 * I pledge that I have neither given nor received any help
 * on this assignment.
 */
//==============================================================================

#ifndef DIVIDE_EXPR_NODE_
#define DIVIDE_EXPR_NODE_

#include "Binary_Expr_Node.h"
class Expr_Node_Visitor;

//division node, returns division of children nodes
class Divide_Expr_Node: public Binary_Expr_Node {
    public:
        Divide_Expr_Node(Expr_Node * n1, Expr_Node * n2);
        ~Divide_Expr_Node();
		
		//accept for visitor
        void accept(Expr_Node_Visitor & v);
		
		//executes division
        int execute(int n1, int n2);
		
		//returns this objects precedence
		int get_precedence();
	private:
		int precedence;
};


#endif