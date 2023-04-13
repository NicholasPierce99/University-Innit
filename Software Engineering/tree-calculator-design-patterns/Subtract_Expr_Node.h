/**
 * Honor Pledge:
 *
 * I pledge that I have neither given nor received any help
 * on this assignment.
 */
//==============================================================================

#ifndef SUBTRACT_EXPR_NODE
#define SUBTRACT_EXPR_NODE

#include "Binary_Expr_Node.h"

class Expr_Node_Visitor;

//subtract node subtracts two children
class Subtract_Expr_Node: public Binary_Expr_Node {
    public:
        Subtract_Expr_Node(Expr_Node * n1, Expr_Node * n2);
        ~Subtract_Expr_Node();
		
		//accept for visitor
        void accept(Expr_Node_Visitor & v);
		
		//executes n1 - n2
        int execute(int n1, int n2);
		
		//get the current nodes precedence
		int get_precedence();
	private:
		int precedence;
};


#endif