/**
 * Honor Pledge:
 *
 * I pledge that I have neither given nor received any help
 * on this assignment.
 */
//==============================================================================

#ifndef BINARY_EXPR_NODE_
#define BINARY_EXPR_NODE_

#include "Expr_Node.h"

class Expr_Node_Visitor;

//parent class for binary expressions
class Binary_Expr_Node: public Expr_Node {
    public:
        Binary_Expr_Node(Expr_Node * n1, Expr_Node * n2);
        virtual ~Binary_Expr_Node();
		
		//instructions on how to evaluate a binary node
        int eval();
        virtual void accept(Expr_Node_Visitor & v);
		
		//virtual function, goes to children
        virtual int execute(int n1, int n2) = 0;
    private:
		
		//right and left tree nodes
        Expr_Node * right_;
        Expr_Node * left_;
		
};


#endif