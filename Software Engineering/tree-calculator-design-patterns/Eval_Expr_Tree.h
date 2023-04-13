/**
 * Honor Pledge:
 *
 * I pledge that I have neither given nor received any help
 * on this assignment.
 */
//==============================================================================
#ifndef EVAL_EXPR_TREE_
#define EVAL_EXPR_TREE_

#include "Expr_Node_Visitor.h"
#include "Expr_Node.h"

class Add_Expr_Node;
class Subtract_Expr_Node;
class Multiply_Expr_Node;
class Modulo_Expr_Node;
class Number_Expr_Node;
class Divide_Expr_Node;

//concrete class for visitor, provides blueprint for visiting nodes
//run visit on type of node reference
//return the result to result
class Eval_Expr_Tree : public Expr_Node_Visitor {
    public:
        Eval_Expr_Tree();
        virtual ~Eval_Expr_Tree();
        virtual void visit_add_node(Add_Expr_Node & node);
        virtual void visit_subtract_node(Subtract_Expr_Node & node);
        virtual void visit_multiply_node(Multiply_Expr_Node & node);
        virtual void visit_divide_node(Divide_Expr_Node & node);
        virtual void visit_modulo_node(Modulo_Expr_Node & node);
        virtual void visit_number_node(Number_Expr_Node & node);

        virtual int result() const;
    private:
        int result_;
};

#endif