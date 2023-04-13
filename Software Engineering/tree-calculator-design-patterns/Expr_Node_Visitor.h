/**
 * Honor Pledge:
 *
 * I pledge that I have neither given nor received any help
 * on this assignment.
 */
//==============================================================================
#ifndef EXPR_NODE_VISITOR_
#define EXPR_NODE_VISITOR_

class Add_Expr_Node;
class Subtract_Expr_Node;
class Multiply_Expr_Node;
class Modulo_Expr_Node;
class Number_Expr_Node;
class Divide_Expr_Node;

//abstract class for visitor, provides blueprint for visiting nodes
class Expr_Node_Visitor {
    public:
        Expr_Node_Visitor(){
        }
        virtual ~Expr_Node_Visitor(){
        }
        virtual void visit_add_node(Add_Expr_Node & node) = 0;
        virtual void visit_subtract_node(Subtract_Expr_Node & node) = 0;
        virtual void visit_multiply_node(Multiply_Expr_Node & node) = 0;
        virtual void visit_divide_node(Divide_Expr_Node & node) = 0;
        virtual void visit_modulo_node(Modulo_Expr_Node & node) = 0;
        virtual void visit_number_node(Number_Expr_Node & node) = 0;
        virtual int result() const = 0;

};

#endif