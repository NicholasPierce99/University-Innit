/**
 * Honor Pledge:
 *
 * I pledge that I have neither given nor received any help
 * on this assignment.
 */
//==============================================================================

//parent class for builders
//provides blueprint for building types of nodes in the tree
#include "Expr_Node.h"
#include "Stack.h"

class Expr_Builder {
    public:
        virtual void build_number_node(int n1, Stack<Expr_Node *> & s) = 0;
        virtual void build_add_node(Stack<Expr_Node *> & s) = 0;
        virtual void build_subtract_node(Stack<Expr_Node *> & s) = 0;
        virtual void build_modulo_node(Stack<Expr_Node *> & s) = 0;
        virtual void build_divide_node(Stack<Expr_Node *> & s) = 0;
        virtual void build_multiply_node(Stack<Expr_Node *> & s) = 0;
};