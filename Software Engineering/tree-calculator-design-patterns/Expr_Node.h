/**
 * Honor Pledge:
 *
 * I pledge that I have neither given nor received any help
 * on this assignment.
 */
//==============================================================================


#ifndef EXPR_NODE_
#define EXPR_NODE_

class Expr_Node_Visitor;

//composite base class node
class Expr_Node {
    public:
        Expr_Node();
        virtual ~Expr_Node();
        virtual int eval() = 0;
		
		//accept for visitor
        virtual void accept(Expr_Node_Visitor & v) = 0;
};

#endif