/**
 * Honor Pledge:
 *
 * I pledge that I have neither given nor received any help
 * on this assignment.
 */
//==============================================================================

#ifndef NUMBER_EXPR_NODE_
#define NUMBER_EXPR_NODE_

#include "Expr_Node.h"

class Expr_Node_Visitor;

//number node, has a number
class Number_Expr_Node: public Expr_Node {
    public:
        Number_Expr_Node(int n1);
        ~Number_Expr_Node();
		
		//method for visitor
        void accept(Expr_Node_Visitor & v);
		
		//returns num
        int eval();
    protected:
        int n1;
};

#endif