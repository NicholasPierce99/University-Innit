/**
 * Honor Pledge:
 *
 * I pledge that I have neither given nor received any help
 * on this assignment.
 */
//==============================================================================

#include "Expr_Builder.h"
#include "Number_Expr_Node.h"
#include "Subtract_Expr_Node.h"
#include "Add_Expr_Node.h"
#include "Modulo_Expr_Node.h"
#include "Multiply_Expr_Node.h"
#include "Divide_Expr_Node.h"


#ifndef EXPR_TREE_BUILDER_
#define EXPR_TREE_BUILDER_

//concrete class, builds the expression tree
//each function returns a new node of the type 
class Expr_Tree_Builder: public Expr_Builder {
    public:
        Expr_Tree_Builder();
        virtual ~Expr_Tree_Builder();

        virtual void build_number_node(int n1, Stack<Expr_Node *> & s);
        virtual void build_add_node(Stack<Expr_Node *> & s);
        virtual void build_subtract_node(Stack<Expr_Node *> & s);
        virtual void build_modulo_node(Stack<Expr_Node *> & s);
        virtual void build_divide_node(Stack<Expr_Node *> & s);
        virtual void build_multiply_node(Stack<Expr_Node *> & s);
        virtual Expr_Node * get_root(Stack<Expr_Node *> & s);

    //private data members keep track and manage nodes in tree
    private:
        Expr_Node * root_;
};

#endif

