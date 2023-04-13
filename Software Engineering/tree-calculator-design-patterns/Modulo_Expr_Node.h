/**
 * Honor Pledge:
 *
 * I pledge that I have neither given nor received any help
 * on this assignment.
 */
//==============================================================================

#ifndef MODULO_EXPR_NODE_
#define MODULO_EXPR_NODE_

#include "Binary_Expr_Node.h"
class Expr_Node_Visitor;

//modulus node, returns mod of two numbers
class Modulo_Expr_Node: public Binary_Expr_Node {
    public:
        Modulo_Expr_Node(Expr_Node * n1, Expr_Node * n2);
        ~Modulo_Expr_Node();
		
		//accept for visitor
        void accept(Expr_Node_Visitor & v);
		
		//executes num mod num
        int execute(int n1, int n2);
		
		//returns this nodes precedence
		int get_precedence();
	private:
		int precedence;
};


#endif